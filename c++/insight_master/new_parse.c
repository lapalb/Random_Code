#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "filter_list.h"
#include "filter.h"

/*
 *
 * 2018/03/27 20:44:56.481 {chasync_R0-0}{1}: [chasync] [16185]: UUID: 0, ra: 0, TID: 0 (note):  MASTERSHIP: CLOSE_WRITE-CLOSE standby-rp-state
 *
 */


struct l_cache {
   int index;
   char last_lines[MAX_LINE_CACHE][LINE_LENGTH];
} lines_cache;

insert_line(char *line)
{
   int i;

   i = lines_cache.index;
   snprintf(lines_cache.last_lines[i],LINE_LENGTH,"%s",line);
   i = (i+1) % MAX_LINE_CACHE;
   lines_cache.index = i;
}

/*-----------*/

is_similar(char *part_log, int len1)
{
   int i, d;

   for (i=0;i<lines_cache.index;i++) {
       d = distance(part_log, len1, lines_cache.last_lines[i], strlen(lines_cache.last_lines[i]));
//fprintf(stderr,"Distance between ==%s== and ==%s== is: %d\n",part_log,lines_cache.last_lines[i],d);
       if (d <= SIMILAR_DISTANCE) {
           return 1;
       }
   }
   return 0;
}

/*-------*/


//2018/05/10 
#define DATE_LENGTH_CHECK 10

int parse_line(char *line, int line_no, char *date, char *log_time, char *proc, char *proct, int *pid, char *log)
{

  char *cp=line;
  int r, colon_count,i;
  char cpid[PID_LENGTH];
  static char prev_line[LINE_LENGTH];
  static int prev_failed,first_print;

  while (*cp && !isdigit(*cp)) cp++; 

  if (!cp) return -1;

  r = sscanf(line,"%s %s %s %s %s",date,log_time,proc,proct,cpid);
  if ( (r != 5) || (strlen(date) < DATE_LENGTH_CHECK) ) { // Invalid line
     if (prev_failed && first_print) {
          fprintf(stderr,"%s %d. %s",prev_line,line_no,line);
          first_print = 0;
     }
     else {
          fprintf(stderr,"%d. %s",line_no,line);
     }
     prev_failed = 1;
     return -1;
  }
  
  prev_failed = 0;
  first_print = 1;

  cp = strchr(proc,':');
  if (cp) *cp = '\0';

  *pid = 0;

  cp = strchr(cpid,':');
  if (cp) *cp = '\0';

  cp = strchr(cpid,'[');
  if (cp) *cp = ' ';

  cp = strchr(cpid,']');
  if (cp) *cp = '\0';

  *pid = atoi(cpid);

  cp = line;
  cp += 24;

  /* We are here now.
   *
   * {chasync_R0-0}{1}: [chasync] [16185]: UUID: 0, ra: 0, TID: 0 (note):  MASTERSHIP: CLOSE_WRITE-CLOSE standby-rp-state 
   * 
   */

  colon_count = 0;
  while ( (*cp) && (colon_count < 6)) {
      if ( *cp == ':' ) colon_count++;
      cp++;
  }

  if ( (colon_count < 6) && !(*cp)) return -1;

  strcpy(log,cp);

  snprintf(prev_line,sizeof(prev_line),"%s",line);

  return 0;
}

/*-----------*/


int to_be_filtered(char *log_line)
{

    int i;

    for (i=0;filter_list[i];i++) {
          if ( strstr(log_line,filter_list[i]) ) return 1;
    }
    return 0;
}

/*-----------*/

#define SUBSYS_LEN 256
#define FORMAT_LENGTH 32
#define FILE_NAME_LENGTH 128
#define FILE_NAME_LENGTH 128
#define TAG_LENGTH 32
#define TIME_REF_LENGTH 32

struct prog_options {
   char sub_sys[SUBSYS_LEN];
   char format[FORMAT_LENGTH]; // html | seq | text
   char white_list_file[FILE_NAME_LENGTH];
   char black_list_file[FILE_NAME_LENGTH];
   char time_ref[TIME_REF_LENGTH];
   int before_msec;
   int logs_before;
   int logs_after;
   char trace_file_name[FILE_NAME_LENGTH];
   char tag[TAG_LENGTH];
};

/*--------*/


//char line[256] = "2018/03/27 20:44:56.481 {chasync_R0-0}{1}: [chasync] [16185]: UUID: 0, ra: 0, TID: 0 (note):  MASTERSHIP: CLOSE_WRITE-CLOSE standby-rp-state";

struct parse_filters_info g_parse_filters;

int parse_log_file(FILE *fp, struct prog_options *opts)
{
    char line[LINE_LENGTH];
    char date[DATE_LENGTH],log_time[TIME_LENGTH];
    char log[LOG_LENGTH];
    char proc_name_1[PROC_NAME_1];
    char proc_name_2[PROC_NAME_2];
    int pid, parse_fails=0;
    int line_no=1;
    char cache_check[SUBLINE_LENGTH];
    char *cp;

    #ifdef GENERATE_INCLUDE_LOGS
        FILE *fp_logs;
        char include_filters_name[64];
        time_t t;

        t = time((time_t*) 0);
        snprintf(include_filters_name,sizeof(include_filters_name),"generated_inc_filter_%d.c", t % 1024);
        fp_logs = fopen(include_filters_name,"w");
        fprintf(fp_logs,"const char *include_filters[] = {\n");
    #endif

    while ( fgets(line,sizeof(line),fp) ) {

         if ( parse_line(line, line_no, date, log_time, proc_name_1, 
                         proc_name_2, &pid, log) == -1 ) {
                parse_fails++;
                line_no++;
                fprintf(stderr,"IGNORED due parse failure: %s\n",line);
                continue;
         }

         /* If subsys filter is set allow only those */
         if ( ! filter_include_subsys(line, &g_parse_filters) ) {
                line_no++;
                fprintf(stderr,"IGNORED due to subsys filter: %s\n",line);
                continue;
         }

         if ( to_be_filtered(line) ) {
                line_no++;
                fprintf(stderr,"IGNORED due to blacklist filter: %s\n",line);
                continue;
         }

         /* Check Levenstein's distance to prune out similar logs */
         if (opts -> tag[0]) {
              snprintf(cache_check,sizeof(cache_check),"%s %s",opts -> tag,log);
         }
         else {
              snprintf(cache_check,sizeof(cache_check),"%s",log);
         }

         if ( is_similar(cache_check, strlen(cache_check)) ) {
             insert_line(cache_check);
             line_no++;
             fprintf(stderr,"IGNORED: %d. Similar!! Previous substring: %s Line: %s\n",line_no,line,cache_check);
             continue;
         }
 
         line_no++;
         insert_line(cache_check);

         if (opts -> tag[0]) {
             fprintf(stdout,"%s %s L%d %s %s %d :: [%s] %s",date,log_time,line_no,proc_name_1,proc_name_2,pid,opts -> tag,log);
         }
         else {
             fprintf(stdout,"%s %s L%d %s %s %d :: %s",date,log_time,line_no,proc_name_1,proc_name_2,pid,log);
         }

        #ifdef GENERATE_INCLUDE_LOGS
             cp = strchr(log,'\n');
             if (cp) *cp = '\0'; 
             fprintf(fp_logs,"    \"%s\",\n",log);
        #endif


    }
    fprintf(stderr,"Warning: Unsuccessful parses: %d Total parsed: %d\n",parse_fails,line_no);

        #ifdef GENERATE_INCLUDE_LOGS
            fclose(fp_logs);
        #endif


    return 0;
}

/*-----------*/

/*
 * insight [-s=iomd,ios,cman,ccmn..,all] [-t 10:30:45] [-m dddddd (in msecs)] [-b ddd] [-a ddd] [-f=html|seq|text] [-e=blacklist] [-i=whitelist] -g tag bt_all.txt
 */


void set_default_options(struct prog_options *opts, int argc)
{
    bzero( (void*)opts,sizeof(*opts));

    strcpy(opts -> sub_sys,"all");
    strcpy(opts -> format,"text");
    opts -> before_msec = 0;
    opts -> logs_before = 0;
    opts -> logs_after = 0;
    opts -> white_list_file[0] = '\0';
    opts -> black_list_file[0] = '\0';
    opts -> time_ref[0] = '\0';
    opts -> tag[0] = '\0';
    opts -> trace_file_name[0] = '\0';
}

/*--------*/

void print_options(struct prog_options *opts)
{
    fprintf(stderr,"\n\nSub_sys: %s\nFormat: %s\nbefore_msec: %d\nlogs_before: %d\nlogs_after:%d\nWhite list: %s\nBlack list: %s\ntime_ref: %s\ntrace_file_name: %s\nTag: %s\n\n",
            opts -> sub_sys,
            opts -> format,
            opts -> before_msec,
            opts -> logs_before, 
            opts -> logs_after,
            opts -> white_list_file, 
            opts -> black_list_file, 
            opts -> time_ref, 
            opts -> trace_file_name,
            opts -> tag
          );
}

/*--------*/

void help(char *prog_name)
{
    fprintf(stdout,"\n\nHelp\n\n%s -s subsys -t time_ref -m before_msec -b n_before_time_ref -a n_after_time_ref -f html|seq|text -e black_list_file_name -i white_list_file_name trace_file.txt\n\n", prog_name);
}

/*--------*/

/* "s:t:m:b:a:f:e:i:g:h" */

#define PROG_OPTIONS "s:t:m:b:a:f:e:i:g:h"


int parse_options(int argc, char *argv[], struct prog_options *opts)
{

  int c;

  opterr = 0;

  set_default_options(opts, argc);
  bzero((void*) &g_parse_filters, sizeof(g_parse_filters));

  if (argc == 1) {
     help(argv[0]);
     exit(0);
  }

  while ((c = getopt (argc, argv, PROG_OPTIONS)) != -1) {
    switch (c) {
      case 's':
            strcpy(opts -> sub_sys,optarg);
            set_subsys_filters(opts -> sub_sys, &g_parse_filters);
  fprintf(stderr,"opts -> sub_sys: %s\n",opts -> sub_sys);
            break;
      case 't':
            strcpy(opts -> time_ref,optarg);
            break;
      case 'f':
            strcpy(opts -> format,optarg);
            break;
      case 'm':
            opts -> before_msec = atoi(optarg);
            break;
      case 'b':
            opts -> logs_before = atoi(optarg);
            break;
      case 'a':
            opts -> logs_after = atoi(optarg);
            break;
      case 'i':
            strcpy(opts -> white_list_file,optarg);
            break;
      case 'e':
            strcpy(opts -> black_list_file,optarg);
            break;
      case 'g':
            strcpy(opts -> tag,optarg);
            break;
      case 'h':
        help(argv[0]);
        exit(0);
      default:
        help(argv[0]);
        exit(0);
   }
 }

 strcpy(opts -> trace_file_name,argv[argc-1]);

 print_options(opts);

 return 0;

}

/*-----------*/

int main(int argc, char *argv[]){

    struct prog_options opts;
    FILE *fp;

    parse_options(argc, argv, &opts);

    fp = fopen(opts.trace_file_name, "r");
    if (!fp) {
        fprintf(stderr,"File %s does not exist\n",argv[1]);
        exit(1);
    }

    parse_log_file(fp, &opts);

    fclose(fp);
}

/*-----------*/


#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "filter_list.h"

/*
 *
 * 2018/03/27 20:44:56.481 {chasync_R0-0}{1}: [chasync] [16185]: UUID: 0, ra: 0, TID: 0 (note):  MASTERSHIP: CLOSE_WRITE-CLOSE standby-rp-state
 *
 */

struct l_cache {
   int index;
   char last_lines[MAX_LINE_CACHE][LINE_LENGTH];
} lines_cache;

void insert_line(char *line)
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


//char line[256] = "2018/03/27 20:44:56.481 {chasync_R0-0}{1}: [chasync] [16185]: UUID: 0, ra: 0, TID: 0 (note):  MASTERSHIP: CLOSE_WRITE-CLOSE standby-rp-state";

int parse_log_file(FILE *fp, char *tag)
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

#ifdef GENERATE_INCLUDE_LOGS //Can be ingnored
    FILE *fp_logs;
    char include_filters_name[64];
    time_t t;

    t = time((time_t*) 0);
    snprintf(include_filters_name,sizeof(include_filters_name),"inc_filter_%d.c", t % 1024);
    fp_logs = fopen(include_filters_name,"w");
    fprintf(fp_logs,"const char *include_filters[] = {\n");
#endif

    while ( fgets(line,sizeof(line),fp) ) {

         if ( parse_line(line, line_no, date, log_time, proc_name_1,
                         proc_name_2, &pid, log) == -1 ) {
                parse_fails++;
                line_no++;
                continue;
         }

         if ( to_be_filtered(line) ) {
                line_no++;
                continue;
         }

         /* Check Lavenstein's distance to prune out similar logs */
         if (tag) {
              snprintf(cache_check,sizeof(cache_check),"%s %s",tag,log);
         }
         else {
              snprintf(cache_check,sizeof(cache_check),"%s",log);
         }

         if ( is_similar(cache_check, strlen(cache_check)) ) {
             insert_line(cache_check);
             fprintf(stderr,"%d. Similar!! Ignored. Previous substring: %s Line: %s\n",line_no,line,cache_check);
             line_no++;
             continue;
         }

         line_no++;
         insert_line(cache_check);

         if (tag) {
             fprintf(stdout,"%s %s L%d %s %s %d :: [%s] %s",date,log_time,line_no,proc_name_1,proc_name_2,pid,tag,log);
         }
         else {
             fprintf(stdout,"%s %s L%d %s %s %d :: %s",log_time,line_no,proc_name_1,proc_name_2,pid,log);
         }

#        ifdef GENERATE_INCLUDE_LOGS
             cp = strchr(log,'\n');
             if (cp) *cp = '\0';
             fprintf(fp_logs,"    \"%s\",\n",log);
#        endif


    }
    fprintf(stderr,"Warning: Unsuccessful parses: %d Total parsed: %d\n",parse_fails,line_no);

#ifdef GENERATE_INCLUDE_LOGS
    fclose(fp_logs);
 #endif


    return 0;
}

/*-----------*/

int main(int argc, char *argv[])
{

    FILE *fp;
    char *tag = (char*)NULL;

    if ( (argc != 2) && (argc != 3)) {
        fprintf(stderr,"Help: %s log_file [tag]\n",argv[0]);
        exit(1);
    }

    if (argc == 3 ) {
        tag = argv[2];
    }

    fp = fopen(argv[1],"r");
    if (!fp) {
        fprintf(stderr,"File %s does not exist\n",argv[1]);
        exit(1);
    }

    parse_log_file(fp, tag);

    fclose(fp);
}
/*-----------*/

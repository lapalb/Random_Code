///
/*
  insight - A smart distributed log analyser
  Company: Cisco
  Mentored by: Ganesh Shankar
  Intern_Name: Ashish Jha
*/
///

//Including Header Files
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "filter_list.h"

/// Defining a cache to hold log lines so that we can remove similar log message

struct l_cache {
   int index;
   char last_lines[MAX_LINE_CACHE][LINE_LENGTH];
} lines_cache;

///This function insert the current line into Circular Cache.
void insert_line(char *line)
{
   int i;

   i = lines_cache.index;
   snprintf(lines_cache.last_lines[i],LINE_LENGTH,"%s",line);
   i = (i+1) % MAX_LINE_CACHE;
   lines_cache.index = i;
}
///Compare the current line with data present in last 128 Cache Line
int is_similar(char *part_log, int len1)
{
   int i, d;

   for (i=0;i<lines_cache.index;i++) {
       d = distance(part_log, len1, lines_cache.last_lines[i], strlen(lines_cache.last_lines[i]));

       if (d <= SIMILAR_DISTANCE) {
           return 1;
       }
   }
   return 0;
}

/*-------*/

int lowBound(char * log_time, char * str, int time_delta) {
 char log_times[15];
 strcpy(log_times,log_time);
 int log_timei=0;
 char *ptr=strtok(log_times,":.");
 int i=1;
 while(ptr!=NULL)
 {
  if(i<=3600)
   {
       log_timei+= atoi(ptr)*3600*1000/i;
       ptr=strtok(NULL,":.");
       i*=60;     
   }
  else
   {
       log_timei+= atoi(ptr);
       ptr=strtok(NULL,":.");
   }
 }
 
 char strs[15];
 strcpy(strs,str);
 int stri=0;
 ptr=strtok(strs,":.");
 int j=1;
 while(ptr!=NULL)
 {
  if(j<=3600)
   {
       stri+= atoi(ptr)*3600*1000/j; 
       ptr=strtok(NULL,":.");j*=60;
   }
 else
 { stri+= atoi(ptr);
   ptr=strtok(NULL,":.");
   }
 }
printf("%d\t%d\t\n",log_timei,stri);
stri=stri - time_delta;
if(log_timei>stri)return 1;
else
return 0;
 }


int upBound(char * log_time, char * str, int time_delta) {
  char str1[15];
  strcpy(str1, str);
  char * pch;
  int num[4], i1 = 0;
  pch = strtok(str1, ":.");
  while (pch != NULL) {
    num[i1] = atoi(pch);
    pch = strtok(NULL, ":,");
    i1++;
  }
  int rs=((num[3] + time_delta) / 1000);
  num[3] = (num[3] + time_delta) % 1000;
  int rm=(num[2] + rs) / 60;
  num[2] = (num[2] + rs) % 60;
  int rh=(num[1] +rm) / 60;
  num[1] = (num[1] +rm) % 60;
  num[0] = (num[0] + rh)% 60;
  //printf("%d\t%d\t%d\t%d\n", num[0], num[1], num[2], num[3]);
  char upTime[12];
  for (int i = 0; i < 4; i++) {
    if (i == 3) {
      upTime[3 * i] = num[i] / 100 + '0';
      num[i] = num[i] % 100;
      upTime[3 * i + 1] = num[i] / 10 + '0';
      upTime[3 * i + 2] = num[i] % 10 + '0';
    } else {
      upTime[3 * i] = num[i] / 10 + '0';
      upTime[3 * i + 1] = num[i] % 10 + '0';
      upTime[3 * i + 2] = ':';
    }

  }
  //puts(str);puts(upTime);
  //puts(log_time);
  if (strcmp(log_time, upTime) < 0 && strcmp(log_time, str) > 0) return 1;
  else return 0;

}
     

//2018/05/10 
#define DATE_LENGTH_CHECK 10

int time_filter(char *line, int line_no, char *date, char *log_time, char *proc, char *proct, int *pid, char *log,char * t, int time_delta)
{

  char *cp=line;
  int r, colon_count,i;
  char cpid[PID_LENGTH];
  static char prev_line[LINE_LENGTH];
  static int prev_failed,first_print;
// 2018/03/27 20:44:56.481 {chasync_R0-0}{1}: [chasync] [16185]: UUID: 0, ra: 0, TID: 0 (note):  MASTERSHIP: CLOSE_WRITE-CLOSE standby-rp-state

  while (*cp && !isdigit(*cp)) cp++; 

  if (!cp) return -1;

  r = sscanf(line,"%s %s %s %s %s",date,log_time,proc,proct,cpid);
  if(!upBound(log_time,t,time_delta))return -10;
  if(!lowBound(log_time,t,time_delta))return -10;
  if ( (r != 5) || (strlen(date) < DATE_LENGTH_CHECK))
   {
   // Invalid line
return -1;
     if (prev_failed && first_print) {
          fprintf(stderr,"uc%s %d. %s",prev_line,line_no,line);
          first_print = 0;
     }
     else {
          fprintf(stderr,"uc%d. %s",line_no,line);
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

int parse_log_file(FILE *fp, char *t, int time_delta,char *format, char * blacklist,char *whitelist)
{
    // For Parsing the individual lines
    char line[LINE_LENGTH];
    char date[DATE_LENGTH],log_time[TIME_LENGTH];
    char log[LOG_LENGTH];
    char proc_name_1[PROC_NAME_1];
    char proc_name_2[PROC_NAME_2];
    int pid, parse_fails=0;
    int line_no=1;
    char cache_check[SUBLINE_LENGTH];
    char *cp;

    // Filtering Variables of insight
  int fin=0;int f=0;int iss=0,tf=0;
    while ( fgets(line,sizeof(line),fp) ) {

         int ret=time_filter(line, line_no, date, log_time, proc_name_1, 
                         proc_name_2, &pid, log, t , time_delta) ; 
    if(ret==-1){
                parse_fails++;
                line_no++;
                continue;
         }
if(ret==-10){line_no++;tf++ ;continue; };

         if ( to_be_filtered(line) ) {
                line_no++;f++;
                continue;
         }

         /* Check Lavenstein's distance to prune out similar logs */
                      snprintf(cache_check,sizeof(cache_check),"%s",log);
         

         if ( is_similar(cache_check, strlen(cache_check)) ) {
             insert_line(cache_check);
             fprintf(stderr,"iss%d. Similar!! Ignored. Previous substring: %s Line: %s\n",line_no,line,cache_check);
             line_no++;iss++;
             continue;
         }
 
         line_no++;
         insert_line(cache_check);fin++;
             fprintf(stdout,"pp%s %s L%d %s %s %d :: %s",date,log_time,line_no,proc_name_1,proc_name_2,pid,log);
         

#        ifdef GENERATE_INCLUDE_LOGS
             cp = strchr(log,'\n');
             if (cp) *cp = '\0'; 
             fprintf(fp_logs,"    \"%s\",\n",log);
#        endif


    }
     fprintf(stdout,"---------------------Insight--------------------------------\n");
    fprintf(stdout,"Unsuccessful Parsed : %-25d\n",parse_fails);
    fprintf(stdout,"Filtered due to BlackList : %-25d\n",f);
    fprintf(stdout,"Filtered due to Similarity : %-25d\n",iss);
    fprintf(stdout,"Successful Parsed : %-25d\n",fin);
    fprintf(stdout,"Total Parsed : %-25d\n",line_no);
     fprintf(stdout,"Filteres due to Time : %-25d\n",tf);
    fprintf(stdout,"---------------------Analysis--------------------------------\n");

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
  char *t=argv[1];
  int time_delta=atoi(argv[2]);
  char * format=argv[3];
  char * blacklist=argv[4];
  char * whitelist=argv[5];
  fp=fopen(argv[6],"r");
      if (!fp) {
          fprintf(stderr,"File %s does not exist\n",argv[6]);
          exit(1);
     }

      parse_log_file(fp,t,time_delta,format,blacklist,whitelist);

}
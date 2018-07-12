#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "filter_list.h"

/*---------*/

FILE *seq_uml_prologue()
{
    FILE *fp;

    fp = fopen(UML_FILE_NAME,"w");
    if (!fp) {
        fprintf(stderr,"Failed to create %s file\n",UML_FILE_NAME);
        return (FILE *)0;
    }

    fprintf(fp,"@startuml\n");

    return fp;
}

/*---------*/

int seq_uml_epilogue(FILE *fp)
{
   fprintf(fp,"@enduml\n");
   fclose(fp); 
} 

/*---------*/

/* Replace unacceptable plant uml chars */

void replace_chars(char *str)
{
   char *cp;

   cp = str;

   if (!cp) return;

   while (*cp) {
       switch (*cp) {
           case '/':
           case '{':
           case '}':
           case '-':
               *cp = '_';
               break;
           case '[':
           case ']':
           case '%':
           //case ':':
               *cp = '_';
               break;
           default:
               break;
      }
      cp++;
   }
}

/*---------*/
#define TIME_COLOR "#FF0000"
#define PROC_COLOR "#FF8833"
#define LOG_COLOR "#0000FF"
#define SEQUENCE_COLOR "#000000"
#define ACT_STD_COLOR "#23AB67"
#define ERROR_LOG_COLOR "#FF0000"
#define WARNING_LOG_COLOR "#FFAA00"

int add_seq_log_entry(FILE *fp, char *date, char *log_time,char *tag, char *proc_name_1, char *proc_name_2, int pid,char *log)
{
   /* Running sequence number to help track the events while browsing the web page */
   static int seq_no; 
   char *log_color;

   replace_chars(proc_name_1);
   replace_chars(proc_name_2);
   replace_chars(log_time);
   replace_chars(log);


   /* Show it as self loop, proc_name_1 to proc_name_1 */
   if (strcasestr(log,"err ") || strcasestr(log,"error") || strcasestr(log,"fail") ) {
      log_color = ERROR_LOG_COLOR;
   }
   else if (strcasestr(log,"warning") ) {
      log_color = WARNING_LOG_COLOR;
   }
   else {
      log_color = LOG_COLOR;
   }
   fprintf(fp,"%s%s -> %s%s : <color %s>%s</color> [<color %s>**%d**</color>] [<color %s>%s</color>] <color %s>%s</color>\n", 
              tag,proc_name_1,tag,proc_name_1,
              TIME_COLOR, log_time,
              SEQUENCE_COLOR, seq_no,    
              PROC_COLOR,proc_name_2,
              log_color,log);

   seq_no++;

   return 0;
}

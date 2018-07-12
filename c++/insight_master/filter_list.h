#ifndef FILTER_LIST_H
#define FILTER_LIST_H
#define UML_FILE_NAME "seq_uml.dot"
#define LINE_LENGTH 2048
#define DATE_LENGTH 32
#define TIME_LENGTH 32
#define LOG_LENGTH 2048
#define PROC_NAME_1 64
#define PROC_NAME_2 64
#define PID_LENGTH 32
#define MAX_LINE_CACHE 128
#define SIMILAR_DISTANCE 4
#define SUBLINE_LENGTH 64
#define INCLUDE_DISTANCE 40
#define ALL_TXT "bt_all.txt"



extern const char *filter_list[];
extern const char *include_filter_list[];

extern FILE *seq_uml_prologue();
extern int seq_uml_epilogue(FILE *fp);

extern int add_seq_log_entry(FILE *fp, char *date, char *log_time,  char *tag,  char *proc_name_1,char *proc_name_2, int pid, char *log);
extern int distance1 (const char * word1,int len1,const char * word2, int len2);

#endif

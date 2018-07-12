#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE * fp;
    fp=fopen("data.txt","a+");
    if(fp)printf("Successfully Opened the File");
    else printf("Failed to Locate the resource");

    puts("\nEnter The string to be written");
    char str[50];
    gets(str);
    fputs(str,fp);
    if(fclose(fp)
}

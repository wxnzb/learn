#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int main(int argc,char *argv[])
{
    char file_name[60];
    char ch;
    scanf("%s",file_name);
    FILE *pf=fopen(file_name,"r+");
    while((ch=getc(pf))!=EOF)
    {
         fseek(pf,-1,SEEK_CUR);
          putc(toupper(ch),pf);
    }
    fclose(pf);
}
//11
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define Size 256
int main(int argc,char *argv[])
{
    char buffer[Size];
    char *seek;
    seek=argv[1];
    FILE *pf=fopen(argv[2],"r");
    assert(pf);
    while(fgets(pf,Size,seek)!=NULL)
    {
    if(strstr(buffer,seek))
    puts(buffer);
    }
    fclose(pf);
    return 0;
}
//10
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Size 256
int main(void)
{
    char file_name[Size];
    long position;
    char buffer[Size];
    FILE *pf=fopen(file_name,"r");
    scanf("%s",file_name);
    while(scanf("%ld",&position)==1&&position>0)
    {
        feek(pf,position,SEEK_SET);
        if(fgets(buffer,Size,file_name)1=NULL);
        {
          printf("%s",buffer);
        }
    }
    fclose(pf);}


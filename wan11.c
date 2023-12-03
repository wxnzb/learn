//第十一章
//9法1
#include<stdio.h>
 #include<string.h>
 void ZFC(char a[],int n);
 int main()
 {
    char a[30];
    int i=0;
    gets(a);
   i=strlen(a);
   ZFC(a,i);
   return 0;
 }
 void ZFC(char a[],int n)
 {
   for(int j=n-1;j>=0;j--)
   printf("%c",a[j]);
 }
 //9法2
 #include<stdio.h>
 #include<string.h>
 void ZFC(char a[],int n);
 int main()
 {
    char a[30];
    int i=0;
    char b=0;
    while((b=getchar())!='\n')
    a[i++]=b;
   ZFC(a,i);
   return 0;
 }
 void ZFC(char a[],int n)
 {
   for(int j=n-1;j>=0;j--)
   printf("%c",a[j]);
 }
#include<stdio.h>
int main(int argc,char *argv[])
{
   if(argc<2)
   printf("Error!");
   else
   {
      for(int i=argc-1;i>0;i--)
      printf("%s  ",argv[i]);
   }
   return 0;
}
//lianxi
#include<stdio.h>
#include<string.h>
int main()
{
    char ch1[10]="qwer";
    char ch2[4]="o";
    char *ret=strstr(ch1,ch2);
    if(ret==NULL)
    printf("no");
    else
    printf("%s",ret);
    return 0;
}
#include<stdio.h>
#include<string.h>
#include<ctype.h>
void Printf(char *ch);
void up(char *ch);
int main(int argc,char *argv[])
{
    char c;
    if(argc<2)
    c='p';
    else
    c=argv[1][1];
    char ch[256];
    fgets(ch,256,stdin);
    switch(c)
    {
        case  'p'  :
        case  'P' :  
        Printf(ch);
        break;
        case   'u':
        case  'U':
        up(ch);
        break;
        }
        return 0;
}
void Printf(char *ch)
{
    printf("%s",ch);
}
void up(char *ch)
{
    while(*ch!=EOF&&*ch!='\0')
    putchar(toupper(*ch++));
}


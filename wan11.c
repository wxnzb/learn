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



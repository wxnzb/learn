#include<stdio.h>
#include<string.h>
#include<malloc.h>
int main()
{
    char* s=(char*)malloc(sizeof(char)*10000);
    scanf("%s",s);
    char ch[10000];
    int n=strlen(s);
    int cnt=0;
    for(int i=0;i<n;i++)
    {
        if(s[i]<='z'&&s[i]>='a')
        ch[cnt++]=s[i];
        else
        {
           const char* number="number";
           for(int j=0;j<6;j++)
           {
               ch[cnt++]=number[j];
           }
        }
    }
    ch[cnt]='\0';
    printf("%s\n",ch);
    free(s);
    return 0;
}

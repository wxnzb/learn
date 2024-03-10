//方法错误，建议用动态规划
void swap(char** p1,char** p2)
{
    char* p;
    p=*p1;
    *p1=*p2;
    *p2=p;
}
bool wordBreak(char* s, char** wordDict, int wordDictSize) {
    for(int i=0;i<wordDictSize-1;i++)
    {
        for(int j=0;j<wordDictSize-i-1;j++)
        {
            if(strcmp(wordDict[j],wordDict[j+1])>0)
            {
             swap(&wordDict[j],&wordDict[j+1]);
            }
        }
    }
   int n=strlen(s);
   int cnt=0;
   //这个aaaaaaa通过不了的原因是先aaa ，然后后面只剩4个a，但还是从三个a开始匹配，当然匹配上了，但剩下最后一个a该何去何从呢？
   for(int i=0;i<n;i++)
   {
       for(int j=0;j<wordDictSize;j++)
       {
           int m=strlen(wordDict[j]);
           if(!strncmp(&s[i],wordDict[j],m))
           {
           cnt+=m;
           i+=m-1;
           break;
           }

       }
   }
   return cnt==n;
}

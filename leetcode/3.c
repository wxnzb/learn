char* removeDuplicates(char* s) {
    int n=strlen(s);
    char* a=(char*)malloc(n+1);
    int j=0;
    a[j++]=s[0];
    for(int i=1;i<n;i++)
    {
      if(j>0&&a[j-1]==s[i])
      j--;
      else
      a[j++]=s[i];
    }
    a[j]='\0';
    return a;
}

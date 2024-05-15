int compareVersion(string version1, string version2) {
      int i=0;
      int j=0;
      while(i<version1.size()||j<version2.size())
      {
        long long num1=0;
        long long num2=0;
        while(i<version1.size()&&version1[i]!='.')
        {
            num1+=10*num1+version1[i++]-'0';
        }
         while(j<version2.size()&&version2[j]!='.')
        {
            num2+=10*num2+version2[j++]-'0';
        }
        if(num1>num2)
        return 1;
        else if(num1<num2)
        return -1;
        i++;
        j++;
      }
      return 0;
    }
};

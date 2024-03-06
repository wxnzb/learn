int digitOneInNumber(int num) {
  long long base=1;
  int res=0;
  while(base<=num)
  {
      int a=num/base;
      int b=num%base;
      int cur=a%10;
      a/=10;
      if(cur>1)
      res+=(a+1)*base;
      if(cur==1)
      res+=a*base+b+1;
      if(cur<1)
      res+=a*base;
      base*=10;
  }
  return res;
}

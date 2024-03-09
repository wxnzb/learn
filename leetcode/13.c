bool isUgly(int n) {
    while(n)
    {
  if(n%2==0)
  n/=2;
  else if(n%5==0)
  n/=5;
  else if(n%3==0)
  n/=3;
  else
  break;
    }
    return n==1;
}

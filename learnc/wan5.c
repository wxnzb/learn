//第五章
//7
#include<stdio.h>
void cbm(double cbm);
int main()
{
  double n;
  scanf("%lf",&n);
  cbm(n);
  return 0;
}
void cbm(double cbm)
{
  printf("%lf",cbm*cbm*cbm);
}
//8
#include<stdio.h>
int main()
{
  int first,second;
  printf("This program computes moduli.\n");
  scanf("%d %d",&first,&second);
  printf("Enter an integer to serve as the secnd operand:%d\n",first);
  printf("Now enter the first operand:%d\n",second);
  while(second>0)
  {
    printf("%d %% %d is %d\n",second,first,second%first);
    scanf("%d",&second);
    printf("Enter next number for first operand:%d\n",second);
  }
  printf("done");
  return 0;
}
//2
#include<stdio.h>
int main()
{
  int n;
  scanf("%d",&n);
  int m=n+10;
  while(n++<m)
  {
    printf("%d  ",n);
  }
  return 0;
}

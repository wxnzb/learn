//第四章
//4
#include<stdio.h>'
int main()
{
  char name[30];                                          
  float cm,m;
  scanf("%s %f",name,&cm);
  m=cm/100;
  printf("%s,you are %.3f meter tall",name,m);
  return 0;
}
//6
#include<stdio.h>
#include<string.h>
int main()
{
  char name[20];
  char surname[20];
  scanf("%s %s",name,surname);
  printf("%s %s\n",name,surname);
  printf("%*d %*d\n",strlen(name),strlen(name),strlen(surname),strlen(surname));
  printf("%s %s\n",name,surname);
  printf("%-*d %-*d",strlen(name),strlen(name),strlen(surname),strlen(surname));
  return 0;
}
//7
#include<stdio.h>
#include<float.h>
int main()
{
  double a=1.0/3.0;
  float  b=1.0/3.0;
  printf("%.6lf %.6f\n",a,b);
  printf("%.12lf %.12f\n",a,b);
  printf("%.16lf %.16f\n",a,b);
  printf("%d %d",FLT_DIG,DBL_DIG);
  return 0;
}

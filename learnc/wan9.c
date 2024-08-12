//第九章
//11
#include<stdio.h>
int main()
{
    int n,c,a,b;
         a=1;
         b=1;
    scanf("%d",&n);
    if(n==1||n==2)
    printf("%d",1);
    else 
    for(int i=3;i<=n;i++)
    {
        c=a+b;
        a=b;
        b=c;
    }
    printf("%d",c);
    return 0;
}
//5
#include<stdio.h>
void larger_of(double *a,double *b);
int main()
{
    double a,b;
    scanf("%lf  %lf",&a,&b);
    printf("a=%lf   b=%lf",a,b);
    larger_of(&a,&b);
    printf("a=%lf   b=%lf",a,b);
    return 0;
}
void larger_of(double *a,double *b)
{
   if(*a>*b)
   *b=*a;
   else
   *a=*b;
}

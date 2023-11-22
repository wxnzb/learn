//第七章
//3
#include<stdio.h>
int main()
{
    int a,cnt1=0,cnt2=0,sum1=0,sum2=0;
    scanf("%d",&a);
    while(a!=0)
    {
      if(a%2)
      {
        cnt1++;
        sum1+=a;
      }
      else
      {
        cnt2++;
        sum2+=a;
      }
      scanf("%d",&a);
    }
    printf("odd:%d averge odd:%f\n",cnt1,1.0*sum1/cnt1);
    printf("even:%d averge even:%d\n",cnt2,sum2/cnt2);
    return 0;
}
//7
#include<stdio.h>
#define b300 0.15
#define a300 0.2
#define a450 0.25
int main()
{
    printf("Please enter the number of working hours per week:");
    int week,totalsalary,netincome;
    scanf("%d",&week);
    if(week<=40)
    totalsalary=week*1000;
    else
    totalsalary=40000+(week-40)*1500;
    printf("total salary =%d\n",totalsalary);
    int taxrevenue;
    if(totalsalary<=300)
    {
        taxrevenue=totalsalary*b300;
        printf("tax revenue:%d\n",taxrevenue);
    }
    else if(totalsalary>300&&totalsalary<=450)
    {
        taxrevenue=300*b300+(totalsalary-300)*(a300);
        printf("tax revenue:%d\n",taxrevenue);
    }
    else(totalsalary>450);
    {
        taxrevenue=300*b300+(450-300)*(a300)+(totalsalary-450)*a450;
        printf("tax revenue:%d\n",taxrevenue);
    }
    printf("net income:%d",totalsalary-taxrevenue);
    return 0;
}

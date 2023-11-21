//第十章
//11
#include<stdio.h>
void yuan(int a[3][5]);
void zeng(int(*b)[5]);
int main()
{
   int c[3][5]={{1,2,3,4,5},{2,3,4,5,6},{3,4,5,6,7},{4,5,6,7,8},{5,6,7,8,9}};
   yuan(c);
   zeng(c);
   return 0;
}
void yuan(int a[3][5])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            printf("%d  ",a[i][j]);
        }
        printf("\n");
    }
}
void zeng(int (*b)[5])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            printf("%d  ",b[i][j]*2);
        }
        printf("\n");
    }
}
//3
#include<stdio.h>
int MAX(int a[],int n);
int main()
{
    int b[30]={1,2,3,4,5};
    int c;
    c=MAX(b,5);
    printf("%d",c);
    return 0;
}
int MAX(int a[],int n)
{
    int max=a[0];
    for(int k=0;k<n;k++)
    {
        if(max<a[k])
        max=a[k];
    }
    return max;
}


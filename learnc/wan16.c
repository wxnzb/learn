#include<stdio.h>
#define PING(X,Y)  (1/((1/(X)+1/(Y))/2))
int main()
{
    double X,Y;
    printf("请输入");
    scanf("%f %f",&X,&Y);
    printf("%f and %f 调和平均数为 %f",X,Y,PING(X,Y));
    return 0;
}

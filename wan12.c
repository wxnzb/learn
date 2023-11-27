//第十二章
//4
#include<stdio.h>
static int count=0;
int counter(void);
int main()
{
    for(int i=0;i<100;i++)
    printf("%d\n",counter());
    return 0;
}
int counter(void)
{
    return ++count;
}
//5
#include<stdio.h>
#include<stdlib.h>
void sort(int arr[]);
int main()
{
    int arr[100];
    srand ((unsigned int)time(0));
    for(int i=0;i<100;i++)
    {
        arr[i]=rand()%10+1;
    }
    void sort(arr);
}
void sort(int arr[])
{
     int inserted;
    for(int i=1;i<100;i++)
    {
        inserted=arr[i];
        int j=i-1;
        for(;j>=0&&arr[j]>inserted;j--)
        {
            arr[j+1]=arr[j];
        }
        arr[j+1]=inserted;
    }
    for(int i=0;i<100;i++)
    {printf("%d",arr[i]);
    }
}


//第十五章
//3
// #include<stdio.h>
// int shu(int n)
// {   int ret=1;
//     while(n/=2)
//     ret++;
//     return ret;
// }
// int main()
// {
//     int n;
//     scanf("%d",&n);
//     printf("%d",shu(n));
//     return 0;
// }
//4
// #include<stdio.h>
// int find(int x,int n);
// int main()
// {
//     int n;
//     printf("请输入数");
//     scanf("%d",&n);
//     printf("请输入要查找的位");
//     int i;
//     scanf("%d",&i);
//     printf("%d",find(n,i));
// }
// int find(int x,int i)
// {
//     int l=x;
//     int ret=1;
//     while(l/=2)
//     ret++;
//     int arr[ret];
//     for(int j=ret-1;j>=0;j--)
//     {
//         arr[j]=x%2;
//         x/=2;
//     }
//     return arr[i-1];
// }

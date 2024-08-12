//第二章
//（8）
#include<stdio.h>
int main()
{
  int a,b;
  a=5;
  b=2;//表示把2赋给了b
  b=a;//把a的值5赋给了b
  a=b;//把b的5赋给了a
  printf("%d %d\n",b,a);
  return 0;
}
//7
#include<stdio.h>
void smile(void);
int main()
{
  smile();smile();smile();
  printf("\n");
  smile();smile();
  printf("\n");
  smile();
  printf("\n");
  return 0;
}
void smile(void)
{
  printf("Smile!");
}
//8
#include<stdio.h>
void one_three(void);
void two(void);
int main()
{
  one_three();
  two();
  printf("done!");
  return 0;
}
void one_three(void)
{
  printf("starting now;\n");
}
void two(void)
{
  printf("one;\ntwo;\nthree;\n");
}

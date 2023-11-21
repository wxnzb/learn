//第六章
//4
#include<stdio.h>
int main()
{
  char a='A';
  for(int i=0;i<6;i++)
  {
    for(int j=0;j<=i;j++,a++)
    {
      printf("%c",a);
    }
    printf("\n");
  }
  return 0;
}
//15
#include<stdio.h>
int main()
{
  char a[256];
  printf("Enter the char in the line:");
  int i=0;
  do{
    scanf("%c",&a[i]);
  }
  while(a[i]!='\n'&&++i);
  for(i--;i>=0;i--)
  printf("%c",a[i]);
  return 0;
}
//17
#include<stdio.h>
#include<string.h>
int main()
{
  float chuckie=100;
  int year=0;
  do
  {
    chuckie=chuckie+chuckie*0.08;
    chuckie-=10;
    year++;
    printf("%f\n",chuckie);
  } while(chuckie>9);
  printf("%d years later. Chuckie's account %f \n",year,chuckie);
  printf("%d years later.Chuckie's account is null",++year);
  return 0;
}

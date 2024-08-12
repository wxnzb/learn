//第三章
//3
#include<stdio.h>
int main()
{
  printf("\aStartled by the sudden sound, Sally shouted,\n\"By the Great Pumpkin, what was that!\"");
  return 0;
}
//4
#include<stdio.h>
int main()
{
  float a;
  scanf("%f",&a);
  printf("Enter a floating-point value: %.2f\n",a);
  printf("fixed-point notation: %f\n",a);
  printf("exponential notation: %e\n",a);
  printf("p notation: %a",a);
  return 0;
}
//5
#include<stdio.h>
#define a 3.156e7
int main()
{
   int year;
   scanf("%d",&year);
   printf("%e",year*a);
   return 0;
}

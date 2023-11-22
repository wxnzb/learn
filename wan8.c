#include<stdio.h>
// int main()
// {
//     printf("Please enter a positive interger:");
//     int n;
//     int flat=1;
//     scanf("%d",&n);
//     for(int i=2;i<=n;i++)
//     {
//         for(int j=2;j<i;j++)
//         if(i%j==0)
//         {
//             flat=0;
//             break;
//         }
//     if(flat)
//     printf("%d  ",i);
//     }
//     return 0;
// }
// #include<stdio.h>
// int main()
// {
//     char ch;
//     int lowercase=0;
//     int uppercase=0;
//     while((ch=getchar())!=EOF)
//     {
//       if(ch>='a'&&ch<='z')
//       lowercase++;
//       if(ch>='A'&&ch<='Z')
//       uppercase++;
//     }
//       printf("There are %d lowercase and %d uppercase in that file",lowercase,uppercase);
//     return 0;
// }
// #include<stdio.h>
// char get_choice(void);
// char get_first(void);
// int get_int(void);
// void count(void);
// int main()
// {
//     int choice;
//     void count (void);
//     while((choice=get_choice())!='q')
//     {
//         switch(choice)
//         {
//             case 'a':
//             printf("Buy low,shell high");
//             break;
//             case 'b':
//             putchar('\a');
//             break;
//             case 'c':
//             count();
//             break;
//             default:
//             printf("programe error");
//             break;
//         }
//     }
//     printf("bye");
//     return 0;
// }
// void count (void)
// {
//     int n,i;
//     printf("Enter an integer");
//     n=get_int();
//     for(i=1;i<=n;i++)
//     {
//         printf("%d",i);
//     }
//     while(getchar()!='\n')
//     continue;
// }
// char get_choice(void)
// {
//     int ch;
//     printf("Enter the letter of your choice:\n");
//     printf("a. advice        b.bell\n");
//     printf("c. count         d.quit\n");
//     ch=get_first();
//     while((ch<'a'||ch>'c')&&ch!='q')
//     {
//         printf("Please respond with a,b,c or q.\n");
//         ch=get_first();
//     }
//     return ch;
// }
// char get_first(void)
// {
//     int ch;
//     ch=getchar();
//     while(getchar()!='\n')
//     continue;
//     return ch;
// }
// int get_int(void)
// {
//     int input;
//     char ch;
//     while(scanf("%d",&input)!=1)
//     {
//         while((ch=getchar())!=1)
//         putchar(ch);
//         printf("is not an integer.\nPlease enter an");
//         printf("integer value,such as 25,74");
//     }
//     return input;
// }

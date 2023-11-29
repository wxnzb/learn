//第十四章
//    #include<stdio.h>
// #include<string.h>
// char S(char *st,int n);
// struct book
// {
//     char bname[30];
//     char name[30];
//     float value;
// };
// int main()
// {
//     struct book library;
//     S(library.bname,30);
//     printf("%s\n",library.bname);
//     S(library.name,30);
//     printf("%s\n",library.name);
//     scanf("%f",&library.value);
//     printf("%f",library.value);
//     return 0;
// }
// char S(char *st,int n)
// {
//    char ret_val;
//    char *find;
//    ret_val=fgets(st,n,stdin);
//    find=strchr(st,'\n');
//   if(ret_val)
//   {
//     if(find)
//     {
//         *find='\0';
//     }
//     else
//     while(getchar()!='\n')
//     continue;
//   }
//   return ret_val;
// }
    // #include<stdio.h>
    // struct student 
    // {
    //     char name[30];
    //     int age;
    // };
    // int main()
    // {
    //     struct  student W={
    //         .name="wx",
    //         .age=18,
    //     };
    //     printf("%s\n %d",W.name,W.age);
    //     return 0;
    // }
    //5
// #include <stdio.h>
// #include <string.h>
// #define CSIZE 4
// #define NLEN 10
 
// struct name{
// 	char first[NLEN];
// 	char last[NLEN];
// };
 
// struct student{
// 	struct name hm;
// 	float grade[3];
// 	float avg;
// };
 
// char * s_gets(char * st, int n);
// void Print_ifm(const struct student * p, int n);
 
// int main(void)
// {
// 	struct student guy[CSIZE];
// 	int count = 0;
// 	int i;
	
// 	puts("Enter a student name:");
// 	while ( count < CSIZE && s_gets(guy[count].hm.last, NLEN) != NULL 
// 				&& guy[count].hm.last[0] != '\0' )
// 	{
// 		puts("Enter the student first name:");
// 		s_gets(guy[count].hm.first, NLEN);
		
// 		puts("Enter the student that three grades:");
// 		for ( i = 0; i < 3; i++)
// 			scanf("%f", &guy[count].grade[i]);
// 		guy[count].avg = (guy[count].grade[0] + guy[count].grade[1] +
// 								guy[count].grade[2]) / 3;
// 		while ( getchar() != '\n' )
// 			continue;
			
// 		puts("Enter the next student name:(Enter empty line to quit)");
// 		count++;
// 	}
	
// 	Print_ifm(guy, count);
// 	printf("All avg:%-8.2f.", (guy[0].avg + guy[1].avg + guy[2].avg)/3 );
	
// 	return 0; 
// }
 
// char * s_gets(char * st, int n)
// {
//     char * ret_val;
//     char * find;
    
//     ret_val = fgets(st, n, stdin);
//     if (ret_val)
//     {
//         find = strchr(st, '\n');   
//         if (find)                 
//             *find = '\0';         
//         else
//             while (getchar() != '\n')
//                 continue;          
//     }
//     return ret_val;
// }
 
// void Print_ifm(const struct student * p, int n)
// {
// 	int i;
	
// 	for ( i = 0; i < n; i++)
// 		printf( "%s %s:  exam1:%-8.2f exam2:%-8.2f exam3:%-8.2f  avg:%-5.2f.\n", (p + i)->hm.first, 
// 					(p + i)->hm.last, (p + i)->grade[0], (p + i)->grade[1], (p + i)->grade[2],
// 					(p + i)->avg );
// }
#include <stdio.h>
#include <string.h>
 
#define LEN 20
 
struct names{
	char first[LEN];
	char center[LEN];
	char last[LEN];
};
 
struct guy{
	unsigned int sty;
	struct names handle;
};
 
void Print(const struct guy * p);
 
int main(void)
{
	struct guy ifm[5] ={
		{
			302039823,
			{ .first = "Zeep", .last = "Po" },
		},
		{
			302039823,
			{ "Emo", .last = "Tao" },
		},
		{
			302039823,
			{ "Jun", "Hao", "Zhu" },
		},
		{
			302039823,
			{ "Zhong", "Zheng", "Chen" },
		},
		{
			302039823,
			{ "P", .last = "W" },
		}	
	};
	
	Print(ifm);
	
	return 0;
}
 
void Print(const struct guy p[])		 
{
	int i;
	
	for ( i = 0; i < 5; i++ )
	{
		if ( !strlen((p + i)->handle.center) )
			printf("%s.%s -- %d\n", (p + i)->handle.last, (p + i)->handle.first, (p + i)->sty);
		else
			printf("%s.%s %c. -- %d\n", (p + i)->handle.last, (p + i)->handle.first, 
								(p + i)->handle.center[0], (p + i)->sty);	
	} 
}

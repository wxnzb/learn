#include <stdio.h>//printf,perror
#include <unistd.h>//fork,waitpid,read,write
#include<sys/types.h>//
#include<sys/stat.h>
#include<fcntl.h>
#include<ctype.h>
#include <stdlib.h>//malloc,free,exit
#include<wait.h>
#include<string.h>
#include<signal.h>//singal
//#include<readline/readline.h>//用于命令行输入和历史记录
//#include<readline/history.h>//提供了访问历史记录的函数原型
//exit(0)为正常退出，而exit(1)为异常退出
char path[1000];//路径
void Printname()//打印自己信息
{
    char* name="sweet@sweet";
    printf("\033[1m\033[32m%s\033[0m",name); 
    getcwd(path,sizeof(path));
    printf("\033[1m\033[34m%s\033[0m",path);
    fflush(stdout); //清空缓
}
int Panduan(char* argv[],int argc)
{
     int flag=8;
     for(int i=0;i<argc;i++)
     {
        if(!strcmp("cd",argv[i]))
        flag=1;
        else if(!strcmp(">",argv[i]))
        flag=2;
        else if(!strcmp("|",argv[i]))
        flag=3;
        else if(!strcmp(">>",argv[i]))
        flag=4;
        else if(!strcmp("<",argv[i]))
        flag=5;
        else if(!strcmp("<<",argv[i]))
        flag=6;
     }
     return flag;
}
void Cd(char* argv[])
{
   char pre[520];
   getcwd(pre,sizeof(pre));
   if(argv[1]==NULL)
   {
    chdir(getenv("HOME"));
   }
   else if(!strcmp("-",argv[1]))//返回到上一层
   {
    //   char cur[520];
    //   getcwd(cur,sizeof(cur));
    //   chdir(pre);
    //   strcpy(pre,cur);
    chdir("..");
   }
   else if(!strcmp("~",argv[1]))
   {
    chdir("home/sweet");
   }
   else
   {
    chdir(argv[1]);
   }
}
void Chong2(char* argv[],int argc)
{
    return;
}
void Chong1(char* argv[])
{
    char* qian[520]={NULL};
    int i=0;
    while(strcmp(">",argv[i]))
    {
       qian[i]=argv[i];
       i++;
    }
    int k=i;
    int flag=Panduan(qian,k);
    i++;//找出文件
    int rout=dup(1);//复制标准输出
    int out_fd=open(argv[i],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR); 
    //1,只写方式打开文件2文件如果不存在，那就创建他3文件存在，就清空他4表示文件的权限，对所有者拥有读写权
    dup2(out_fd,STDOUT_FILENO);//让标准输出到相应的文件，fd复制到文件描述符1,也就是1和文件相同
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork error");
        exit(1);
    }
    if(pid==0)//子孩子
    {
        if(flag==3)
         Chong2(qian,k);
        else
        execvp(qian[0],qian);
    }
    else if(pid>0)
    {
        waitpid(pid,NULL,0);
    }
    dup2(rout,STDOUT_FILENO);//保存了之前标准输出到终端的描述符，现在让标准输出不到文件，而是终端
}
void Chong3(char* argv[])
{
    return;
}
void Chong4(char* argv[])//>>
{
    return;
}
void Chong5(char* argv[])//<
{
    char* qian[520];
    int i=0;
    while(strcmp(">",argv[i]))
    {
       qian[i]=argv[i];
       i++;
    }
    int k=i;
    int flag=Panduan(qian,k);
    i++;//找出文件
    int in_fd=open(argv[i],O_RDONLY);//只能读取数据
    dup2(in_fd,STDIN_FILENO);//将标准输入重定向到文件
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork error");
        exit(1);
    }
    if(pid==0)//子孩子
    {
        if(flag==3)
        Chong2(qian,k);
        else
        execvp(qian[0],qian);
    }
    else if(pid>0)
    {
        waitpid(pid,NULL,0);
    }
    close(in_fd);
}
void History()
{
    int num=0;
   // HIST_ENTRY **h;//声明一个指向历史条目的双重指针
   // h=history_list;//指向第一个历史条目
   // while(h[i])
    //printf("%-3d  %s",i,h[i++]->line);
    return ;
}
void Chuli(char* argv[],int argc)
{
    int flag=Panduan(argv,argc);//只查出了最后一个
    if(!strcmp("history",argv[0]))
     History();
    if(!strcmp("exit",argv[0]))
    {
        perror("exit");
        exit(0);
    }
    switch(flag)
    {
    case 1:Cd(argv);break; 
    case 2:Chong1(argv);break;
    case 3:Chong2(argv,argc);break;
    case 4:Chong3(argv);break;
    case 5:Chong4(argv);break;
    case 6:Chong5(argv);break;
    }
    if(flag==8)
    {
        // if(!strcmp("ll",argv[0]))
        // {
        //     strcpy(argv[0],"ls");
        //     argv[argc++]="-l";
        // }
        // else if(!strcmp("ls",argv[0]))
        // {
        //     argv[argc++]="--color=auto";
        // }
         pid_t pid=fork();
        if(pid<0)
        {
            perror("fork perror");
            exit(1);
        }
        else if(pid==0)
        {
        execvp(argv[0],argv);
        }
        else if(pid>0)
        waitpid(pid,NULL,0);
    }
}
int main()
{
   // read_history(NULL);
    signal(SIGINT,SIG_IGN);//忽略contral c;
    signal(SIGHUP,SIG_IGN);//忽略控制终端关闭的信号
    while(1)
    {
         Printname();
        int argc=1;//命令数
        char* argv[100]={NULL};//各命令字符串
        //怎样获取命令呢？
        char* input=NULL;
        ssize_t bufsize=0;
        getline(&input,&bufsize,stdin);
     // char* input=read_line("sweet:");
 //     add_history(input);
   //   write_history(NULL);
      argv[0]=strtok(input," ");
      while(argv[argc]=strtok(NULL," "))
      argc++;
      Chuli(argv,argc);
      free(input);
    }
}

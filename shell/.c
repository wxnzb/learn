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
void Chuli(char* argv[],int argc);
char path[1000];//路径
int hou=0;
int count=0;
char history[100][100];
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
        else if(!strcmp("&",argv[i]))
        {
          hou=6;
          argv[i]=NULL;
        }
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
//fd[0]管道的读端
//fd[1]管道的写端
void Chong2(char *argv[], int count)
{
  pid_t pid;
  int ret[10];    // 存放每个管道的下标
  int number = 0; // 统计管道个数
  for (int i = 0; i < count; i++)
  {
    if (!strcmp(argv[i], "|"))
    {
      ret[number++] = i;
    }
  }
  int cmd_count = number + 1; // 命令个数
  char *cmd[cmd_count][10];
  int ch[10];
  for (int i = 0; i < cmd_count; i++) // 将命令以管道分割存放组数组里
  {
    if (i == 0) // 第一个命令
    {
      int n = 0;
      for (int j = 0; j < ret[i]; j++)
      {
        cmd[i][n++] = argv[j];
      }
      cmd[i][n] = NULL;
      ch[i]=n;
    }
    else if (i == number) // 最后一个命令
    {
      int n = 0;
      for (int j = ret[i - 1] + 1; j < count; j++)
      {
        cmd[i][n++] = argv[j];
      }
      cmd[i][n] = NULL;
      ch[i]=n;
    }
    else
    {
      int n = 0;
      for (int j = ret[i - 1] + 1; j < ret[i]; j++)
      {
        cmd[i][n++] = argv[j];
      }
      cmd[i][n] = NULL;
      ch[i]=n;
    }
  }                                // 经过上述操作，我们已经将指令以管道为分隔符分好,下面我们就可以创建管道了
  int fd[number][2];               // 存放管道的描述符
  for (int i = 0; i < number; i++) // 循环创建多个管道
  {
    pipe(fd[i]);
  }
  int i = 0;
  for (i = 0; i < cmd_count; i++) // 父进程循环创建多个并列子进程
  {
    pid = fork();
    if (pid == 0) // 子进程直接退出循环，不参与进程的创建
      break;
  }
  if (pid == 0) // 子进程
  {
    if (number)
    {
      if (i == 0) // 第一个子进程
      {
        dup2(fd[0][1], 1); // 绑定写端`
        close(fd[0][0]);   // 关闭读端
        // 其他进程读写端全部关闭
        for (int j = 1; j < number; j++)
        {
          close(fd[j][1]);
          close(fd[j][0]);
        }
      }
      else if (i == number) // 最后一个进程
      {
        dup2(fd[i - 1][0], 0); // 打开读端
        close(fd[i - 1][1]);   // 关闭写端
                             // 其他进程读写端全部关闭
        for (int j = 0; j < number - 1; j++)
        {
          close(fd[j][1]);
          close(fd[j][0]);
        }
      }
      else // 中间进程
      {
        dup2(fd[i - 1][0], 0); // 前一个管道的读端打开
        close(fd[i - 1][1]);   // 前一个写端关闭
        dup2(fd[i][1], 1);     // 后一个管道的写端打开
        close(fd[i][0]);       // 后一个读端关闭
        // 其他的全部关闭
        for (int j = 0; j < number; j++)
        {
          if (j != i && j != (i - 1))
          {
            close(fd[j][0]);
            close(fd[j][1]);
          }
        }
      }
    }
    Chuli(cmd[i],ch[i]);// 执行命令
    perror("execvp");
    exit(1);
  }
  // 父进程什么都不干，把管道的所有口都关掉
  for (i = 0; i < number; i++)
  {
    close(fd[i][0]);
    close(fd[i][1]); // 父进程端口全部关掉
  }
  if (hou == 6)
  {
    hou = 0;
    printf("%d\n", pid);
    return;
  }
  for (int j = 0; j < cmd_count; j++) // 父进程等待子进程
    wait(NULL);
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
        if(hou==6)
      {
        hou=0;
        printf("%d\n",pid);
        return;
      }
        waitpid(pid,NULL,0);
    }
    dup2(rout,STDOUT_FILENO);//保存了之前标准输出到终端的描述符，现在让标准输出不到文件，而是终端
}
void Chong3(char* argv[])//>>
{
     char* qian[520]={NULL};
    int i=0;
    while(strcmp(">>",argv[i]))
    {
       qian[i]=argv[i];
       i++;
    }
    int k=i;
    int flag=Panduan(qian,k);
    i++;//找出文件
    int rout=dup(1);//复制标准输出
    //  out_fd=fopen(argv[i],"a");//文件存在，文件指针定位到文件末尾,但是他是FILE*的
    int out_fd=open(argv[i],O_WRONLY|O_APPEND|O_CREAT,0664);
    //2表示追加模式
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
        if(hou==6)
      {
        hou=0;
        printf("%d\n",pid);
        return;
      }
        waitpid(pid,NULL,0);
    }
    dup2(rout,STDOUT_FILENO);//保存了之前标准输出到终端的描述符，现在让标准输出不到文件，而是终端
}
void Chong4(char* argv[])//<
{
    char* qian[520]={NULL};
    int i=0;
    while(strcmp("<",argv[i]))
    {
       qian[i]=argv[i];
       i++;
    }
    int k=i;
    int flag=Panduan(qian,k);
    i++;//找出文件
    int rin=dup(0);//复制标准输出
    int in_fd=open(argv[i],O_RDONLY);//只能读取数据
    dup2(in_fd,STDIN_FILENO);//将标准输入重定向到文件
    pid_t pid=fork();
    if(pid<0)
    {
        if(hou==6)
      {
        hou=0;
        printf("%d\n",pid);
        return;
      }
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
    dup2(rin,STDIN_FILENO);//保存了之前标准输出到终端的描述符，现在让标准输出不到文件，而是终端
}
void History()
{
    for(int i=count-1;i>=0;i--)
    {
      printf("%d\t%s\n",count-i,history[count-i-1]);
    }
    return ;
}
void Chuli(char* argv[],int argc)
{
    int flag=Panduan(argv,argc);//只查出了最后一个
    if(hou==6)
    argc--;
    if(!strcmp("history",argv[0]))
    {
     History();
     return;
    }
    if(!strcmp("exit",argv[0]))
    {
        exit(0);
    }
    switch(flag)
    {
    case 1:Cd(argv);break; 
    case 2:Chong1(argv);break;
    case 3:Chong2(argv,argc);break;
    case 4:Chong3(argv);break;
    case 5:Chong4(argv);break;
    }
    if(flag==8)
    {
         pid_t pid=fork();
        if(pid<0)
        {
            perror("fork perror");
            exit(1);
        }
        else if(pid==0)
        {
        execvp(argv[0],argv);
        perror("execvp");
        printf("%s:命令输入错误\n",argv[0]);//如果子进程未执行，则会报错并退出
        exit(1);
        }
        else if(pid>0)
        {
               if(hou==6)
            {
              hou=0;
              printf("%d\n",pid);
              return;
            }
            waitpid(pid,NULL,0);
        }
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
         char input[1000];
        fgets(input,sizeof(input),stdin);
        strcpy(history[count++],input);
        input[strcspn(input, "\n")] = '\0'; // 去除换行符
        if(input==NULL)//防止啥也没输
        continue;
     // char* input=read_line("sweet:");
 //     add_history(input);
   //   write_history(NULL);
      argv[0]=strtok(input," ");
      while(argv[argc]=strtok(NULL," "))
      argc++;
      Chuli(argv,argc);
    }
    return 0;
}

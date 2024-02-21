#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include<stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include<string.h>
#include<limits.h>
#define Ls_a   0b1
#define Ls_l   0b10
#define Ls_R   0b100
#define Ls_t   0b1000
#define Ls_r   0b10000
#define Ls_i   0b100000
#define Ls_s   0b1000000
static int  aim=0;
void Gouls(char*path);
void Printf(struct stat*st,char*filename);
char*Mode(struct stat *st);
int main(int argc,char**argv)
{
    int flag=1;
    for(int i=1;i<argc;i++)
    {
        if(argv[i][0]=='-')
        {
            int cnt=0;
            while(argv[i][++cnt])
            {
                switch(argv[i][cnt])
                {
                    case 'a':aim|=Ls_a;break;
                    case 'l':aim|=Ls_l;break;
                    case 'R':aim|=Ls_R;break;
                    case 't':aim|=Ls_t;break;
                    case 'r':aim|=Ls_r;break;
                    case 'i':aim|=Ls_i;break;
                    case 's':aim|=Ls_s;break;
                    default:
                    printf("参数错误");
                }
            }
        }
        else 
        {
            Gouls(argv[i]);
            flag=0;
        }
    }
    if(flag)
    Gouls(".");
    return 0;
}
void Gouls( char *path) {
   DIR* dir=opendir(path);
    if(!dir)
    {
        closedir(dir);
        if(!(aim&Ls_R))
        {
        struct stat st;
        if(stat(path,&st)!=-1)
        Printf(&st,path);
        printf("\n");
        }
        return;
    }
    struct A{
    	    char filename[NAME_MAX];
            time_t time;
    };
    int i=0;
    struct A*B=(struct A*)malloc(sizeof(struct A)*PATH_MAX);
    struct dirent*entry;
    int size=PATH_MAX;
    while((entry = readdir(dir)) != NULL) {
        if(i>=size)
        {
            size*=2;
            B=realloc(B,sizeof(struct A)*size);
        }
        if(!(aim&Ls_a)&&*entry->d_name=='.')
        continue;
        struct stat st;
        strcpy(B[i].filename,entry->d_name);
        stat(entry->d_name,&st);
        B[i].time=st.st_mtime;
        i++;
       }
       int c[i];
       for(int k=0;k<i;k++)
       {
        c[k]=k;
       }
       //paixu r t
        if(aim&Ls_t==1)
        {
            for(int m=0;m<i-1;m++)
            {
                for(int n=0;n<i-m-1;n++)
                {
                    if(B[c[n]].time>B[c[n+1]].time)
                    {
                    int tmp;
                    tmp=c[n];
                    c[n]=c[n+1];
                    c[n+1]=tmp;
                    }
                }
            }
        }
        else if(aim&Ls_r)
        {
          for(int m=0;m<i-1;m++)
            {
                for(int n=0;n<i-m-1;n++)
                {
                    if(strcmp(B[c[n]].filename,B[c[n+1]].filename)<0)
                    {
                    int tmp;
                    tmp=c[n];
                    c[n]=c[n+1];
                    c[n+1]=tmp;
                    }
                }
            }  
        }
        printf("%s:\n",path);
        // //输出
        for(int j=0;j<i;j++)
         {
        struct stat st;
	    char ph[PATH_MAX];
        sprintf(ph,"%s/%s",path,B[c[j]].filename);
            stat(ph,&st);
            Printf(&st,B[c[j]].filename);
            printf(aim & Ls_l || j% 5 == 4 ? "\n" : "  \t");
         }
        printf(aim&Ls_l?"\n":"\n\n");
       free(B);
     struct dirent*entr;
     closedir(dir);
     dir=opendir(path);
     if(aim&Ls_R)
     {
    while ((entr = readdir(dir)) != NULL) {
        if (strcmp(entr->d_name, ".") == 0 || strcmp(entr->d_name, "..") == 0)
            continue;
        char ph[PATH_MAX];
        snprintf(ph, PATH_MAX, "%s/%s", path, entr->d_name);
        struct stat st;
        if (lstat(ph, &st) < 0) {
            perror("lstat");
            continue;
        }
        if (S_ISDIR(st.st_mode)) {
            Gouls(ph);
    }
    }
     }
    closedir(dir);
}
void Printf(struct stat*st,char*filename)
{
    if(aim&Ls_i)
    printf("%8lu  ",st->st_ino);
    if(aim&Ls_s)
    printf("%4ld  ",st->st_blocks/2);
    if(aim&Ls_l)
    {
        printf("%s  %4ld  %-8s  %-8s  %8ld  ",
                   Mode(st), st->st_nlink,  getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name,
                   st->st_size);
                   char buff_time[32];
        strcpy(buff_time,ctime(&st->st_mtime));
        buff_time[strlen(buff_time)-1]='\0'; //buff_time自带换行，因此要去掉后面的换行符
        printf("  %s  ",buff_time);
    }
    printf(S_ISDIR(st->st_mode) ? "\033[1;34m%-10s\033[0m" : (S_IXGRP&st->st_mode)?"\033[0;32m%-10s\033[0m":"%-10s", filename);
    }
    char* Mode(struct stat *st)
{
           static char mode[] = "----------";
            mode_t perm = st->st_mode;
            if (S_ISDIR(perm))
                mode[0] = 'd';//目录显示；
            if (S_ISCHR(perm))//字符设置
                mode[0] = 'c';
            if (S_ISBLK(perm))//块设备
                mode[0] = 'b';
            if (perm & S_IRUSR)
                mode[1] = 'r';
            if (perm & S_IWUSR)
                mode[2] = 'w';
            if (perm & S_IXUSR)
                mode[3] = 'x';
            if (perm & S_IRGRP)
                mode[4] = 'r';
            if (perm & S_IWGRP)
                mode[5] = 'w';
            if (perm & S_IXGRP)
                mode[6] = 'x';
            if (perm & S_IROTH)
                mode[7] = 'r';
            if (perm & S_IWOTH)
                mode[8] = 'w';
            if (perm & S_IXOTH)
                mode[9] = 'x';
                return mode;
}



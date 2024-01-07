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
void list_files_recursive(const char *path);
int Ls_a(const char * pathname)
{
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    // 打开目录流
    dir = opendir(pathname); //"."指的就是当前目录下的目录流

    // 检查目录流是否成功打开
    if (dir == NULL)
    {
        perror("opendir"); // 打印opendir函数相关的错误信息
        return 1;          // 相当于exit(EXIT_FAILURE)退出程序
    }
    while ((entry = readdir(dir)) != NULL)
    {
        // printf("%s\n", entry->d_name);
        if (stat(entry->d_name, &st) == 0)
        {
            if (S_ISREG(st.st_mode))
            {
                if (st.st_mode & S_IXGRP)
                    printf("\033[0;32m%-15s\033[0m", entry->d_name);
                else
                    printf("\033[0;37m%-15s\033[0m", entry->d_name);
            }
            else if (S_ISDIR(st.st_mode))
                printf("\033[0;34m%-15s\033[0m", entry->d_name);
            else
                printf("\033[0;37m%-15s\033[0m", entry->d_name);
        }
}
return 0;
}
int Ls_l(const char*pathname)
{
    DIR *dir;
    dir = opendir(pathname);
    if (dir == NULL)
    {
        perror("opendir");
        return 1;
    }
    struct dirent *entry;
    struct stat st;
    while ((entry = readdir(dir)) != 0)
    {
        if (stat(entry->d_name, &st) == 0)
        {
            char mode[] = "----------";
            mode_t perm = st.st_mode;
            if (S_ISDIR(perm))
                mode[0] = 'd';
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
            // 获取文件所有者和群组
            struct passwd *pw = getpwuid(st.st_uid);
            struct group *gr = getgrgid(st.st_gid);

            // 获取格式化的时间
            char time_str[20];
            strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&st.st_mtime));

            // 输出格式化信息
            printf("%s %2ld %-8s %-8s %8ld %s %s\n",
                   mode, st.st_nlink, pw->pw_name, gr->gr_name,
                   st.st_size, time_str, entry->d_name);
        }
    }
    closedir(dir); // 你也可以写的更细，判断是否关闭成功
    return 0;
}
void Ls_R(const char*path)
{
     DIR *dir;
    struct dirent *entry;
    int cnt=0;
    if (!(dir = opendir(path))) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat statbuf;
        if (stat(full_path, &statbuf) == -1) {
            perror("stat");
            closedir(dir);
            return;
        }

        if (S_ISDIR(statbuf.st_mode)) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                printf("Directory: %s\n", full_path);
                list_files_recursive(full_path);
            }
        } else {
            printf("File:%-25s\n", full_path);
            cnt++;
            if(cnt%2==0)
            printf("\n");
        }
    }

    closedir(dir);
}
void list_files_recursive(const char *path) {
        Ls_R(path);
}
void Ls_i(const char *pathname)
{
     DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    if ((dir = opendir(pathname)) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", pathname, entry->d_name);

        if (stat(fullpath, &statbuf) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        printf("%lu\t%s\n", (unsigned long)statbuf.st_ino, entry->d_name);
    }

    closedir(dir);
}
void Ls_s(const char *pathname)
{
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    if ((dir = opendir(pathname)) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", pathname, entry->d_name);

        if (stat(fullpath, &statbuf) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        if (S_ISREG(statbuf.st_mode)) {
            printf("%ld\t%s\n", statbuf.st_size, entry->d_name);
        }
    }

    closedir(dir);
}
int main(int argc, char *argv[])
{
    const char *path;

    if (argc > 1)
    {
        path = argv[2];
    }
    else
    {
        // 如果没有提供路径，则使用当前目录
        path = ".";
    }

    if (access(path, F_OK) == -1)
    {
        perror("路径不存在");
        return EXIT_FAILURE;
    }
    int opt;
    while((opt=getopt(argc,argv,"alRrtis"))!=-1)
    {
        switch(opt){
            case'a':
            Ls_a(path);
            break;
            case 'l':
            Ls_l(path);
            case 'R':
            Ls_R(path);
            break;
            //case 'r':
            //Ls_r(path);
            //case 't':
            //ls_t(path);
            case 'i':
            Ls_i(path);
            break;
            case 's':
            Ls_s(path);
            break;
        }
    }
    return 0;
}

#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <sys/socket.h>
#include <mysql/mysql.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include "chat.h"
#include "json.h"
#define HOST "127.0.0.1"
#define PORT 8888
#define USER "root"
#define PASSWD "WwL200488"
#define DBNAME "qq"
#define SERVER_PORT 8888
pthread_mutex_t lock_jy;
pthread_cond_t cond_jy;
pthread_mutex_t lock_login;
pthread_cond_t cond_login;
pthread_mutex_t lock_add;
pthread_cond_t cond_add;
pthread_mutex_t lock_block;
pthread_cond_t cond_block;
pthread_mutex_t lock_delete;
pthread_cond_t cond_delete;
pthread_mutex_t lock_show;
pthread_cond_t cond_show;
pthread_mutex_t lock_friendnotice;
pthread_cond_t cond_friendnotice;
pthread_mutex_t lock_unblock;
pthread_cond_t cond_unblock;
pthread_mutex_t lock_msg;
pthread_cond_t cond_msg;
pthread_mutex_t lock_create;
pthread_cond_t cond_create;
pthread_mutex_t lock_deletegroup;
pthread_cond_t cond_deletegroup;
pthread_mutex_t lock_removeuser;
pthread_cond_t cond_removeuser;
pthread_mutex_t lock_grouplist;
pthread_cond_t cond_grouplist;
pthread_mutex_t lock_iingroup;
pthread_cond_t cond_iingroup;
pthread_mutex_t lock_admanager;
pthread_cond_t cond_admanager;
pthread_mutex_t lock_applyaddgroup;
pthread_cond_t cond_applyaddgroup;
pthread_mutex_t lock_noticegroup;
pthread_cond_t cond_noticegroup;
pthread_mutex_t lock_friendrecord;
pthread_cond_t cond_friendrecord;
pthread_mutex_t lock_chatgrouprecord;
pthread_cond_t cond_chatgrouprecord;
pthread_mutex_t lock_checkfile;
pthread_cond_t cond_checkfile;
pthread_mutex_t lock_groupmsg;
pthread_cond_t cond_groupmsg;
pthread_mutex_t lock_receivefile;
pthread_cond_t cond_receivefile;
int ssockfd;
using namespace std;
int a = 0;
int login_f = -1;
int private_f = -1;
int group_f = -1;
int sendfile_f = -1;
int ynfile_f = -1;
unsigned long long fsize = 0;
int id;
bool isStringNumeric(const std::string &str)
{
    for (char c : str)
    {
        if (!std::isdigit(c))
        {
            return false; // 如果遇到非数字字符，返回false
        }
    }
    return true; // 如果字符串只包含数字，返回true
}

class ChatClient
{
public:
    ChatClient(const char *server_ip, int port);
    ~ChatClient();
    //  void *func(void *arg);
    void run();
    int sockfd;

private:
    struct sockaddr_in server_addr;

    void displayMenu1();
    void displayMenu2();
    void displayMenu3();
    void displayMenu4();
    void registerUser();
    void loginUser();
    void logoffUser();
    void addFriend(); // 加好友
    void blockFriend();
    void deleteFriend();     // 删除好友
    void statusFriend();     // 展示好友在线状态
    void privateChat();      // 私聊
    void friendNotice();     // 查看好友请求
    void unblockFriend();    // 解除屏蔽
    void chatfriendRecord(); // 查看好友聊天记录

    void createGroup();     // 创建群聊
    void deleteGroup();     // 删除群聊
    void removeUser();      // 移除群聊成员
    void groupList();       // 查看群聊列表
    void iinGroup();        // 查看自己所在的群
    void adManager();       // 增加删除管理员
    void applyaddGroup();   // 申请加群
    int noticeGroup();      // 查看群聊请求
    void groupChat();       // 群聊
    void chatgroupRecord(); // 查看群聊记录

    int sendFile();     // 发送文件
    void receiveFile(); // 接收文件    // void trueFile(struct protocol msg);           //  void receiveFile();// 接收文件
};

ChatClient::ChatClient(const char *server_ip, int port)
{
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(port);
    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
}

ChatClient::~ChatClient()
{
    close(sockfd);
}
void *func(void *arg)
{
    int sockfd = *((int *)arg);
    struct protocol msg, msgback;
    while (1)
    {
        msgback = receive_data(sockfd);
        if (msgback.state == NOCONTINUE)
        {
            cout << msgback.data << endl;
            continue;
        }
        if (msgback.state == YNCHAT)
        {
            std::cout << "你为啥不打印" << std::endl;
            std::cout << msgback.id << ":" << msgback.data << std::endl;
            continue;
        }
        // 正确处理
        if (msgback.state == AGREEFRIENDNEED)
        {
            std::cout << "id为" << msgback.id << "同意了你的好友请求" << std::endl;
            continue;
        }
        if (msgback.state == REFUSEFRIENDNEED)
        {
            std::cout << "id为" << msgback.id << "拒绝了你的好友请求" << std::endl;
            continue;
        }
        if (msgback.state == YNGROUPCHAT)
        {
            std::cout << msgback.name << "里的" << msgback.id << ":" << msgback.data << std::endl;
            continue;
        }
        if (msgback.state == REQUEST)
        {
            std::cout << "id为" << msgback.id << msgback.data << std::endl;
            continue;
        }
        if (msgback.state == SENDFILE_OK)
        {
            std::cout << "文件发送成功" << std::endl;
            continue;
        }
        if (a == 1) // 注册
        {
            pthread_mutex_lock(&lock_jy);
            if (msgback.state == OP_OK)
            {
                cout << "Registration successful! Your special ID is " << msgback.id << endl;
                id = msgback.id;
                login_f = 1;
            }
            else
            {
                cout << "Registration failed! Please try again!" << endl;
                login_f = 0;
            }
            pthread_cond_signal(&cond_jy); // 阻塞等待验证完成
            pthread_mutex_unlock(&lock_jy);
        }
        if (a == 2) // 登录
        {
            pthread_mutex_lock(&lock_login);
            if (msgback.state != OP_OK)
            {
                login_f = 0;
                if (msgback.state == USER_NOT_REGIST)
                {
                    cout << "用户未注册！" << endl;
                }
                if (msgback.state == USER_LOGED)
                {
                    cout << "用户已在线！" << endl;
                }
                if (msgback.state == PASSWORD_ERROR)
                {
                    cout << "密码错误！" << endl;
                }
            }
            else
            {
                cout << "Login successful!" << endl;
                login_f = 1;
            }
            pthread_cond_signal(&cond_login); // 阻塞等待验证完成
            pthread_mutex_unlock(&lock_login);
        }
        if (a == 3) // 注销
        {
            pthread_mutex_lock(&lock_jy);
            if (msgback.state != OP_OK)
            {
                if (msgback.state == USER_NOT_REGIST)
                {
                    cout << "用户未注册！" << endl;
                }
                /*  if (msgback.state == USER_LOGED) {
                      cout << "用户已在线！" << endl;
                  } else*/
                if (msgback.state == PASSWORD_ERROR)
                {
                    cout << "密码错误！" << endl;
                }
            }
            else
            {
                cout << "Logoff successful!" << endl;
                login_f = -1;
            }
            pthread_cond_signal(&cond_jy); // 阻塞等待验证完成
            pthread_mutex_unlock(&lock_jy);
        }
        if (a == 7) // 加好友//错误判断
        {
            pthread_mutex_lock(&lock_add);
            if (msgback.state != OP_OK)
            {

                if (msgback.state == USER_NOT_REGIST)
                {
                    std::cout << "用户未注册！" << std::endl;
                }
                if (msgback.state == MYSELF)
                {
                    std::cout << "不能添加自己为好友" << std::endl;
                }
                if (msgback.state == ISFRIEND)
                {
                    std::cout << "已经是好友了" << std::endl;
                }
                if (msgback.state == NOCONTINUE)
                {
                    cout << msgback.data << endl;
                }
            }
            else
                std::cout << "等待对方同意" << std::endl;
            pthread_cond_signal(&cond_add); // 阻塞等待验证完成
            pthread_mutex_unlock(&lock_add);
        }
        if (a == 8) // 屏蔽好友
        {
            std::cout << "屏蔽好友" << std::endl;
            pthread_mutex_lock(&lock_block);
            if (msgback.state != OP_OK)
            {
                if (msgback.state == USER_NOT_REGIST)
                {
                    std::cout << "用户未注册！" << std::endl;
                }
                if (msgback.state == MYSELF)
                {
                    std::cout << "不能屏蔽自己" << std::endl;
                }
                if (msgback.state == NOTFRIEND)
                {
                    std::cout << "还不是好友啦" << std::endl;
                }
                if (msgback.state == ISBLOCKED)
                {
                    std::cout << "已经屏蔽了，无需再屏蔽了" << std::endl;
                }
            }
            else
            {
                std::cout << "屏蔽好友成功" << std::endl;
            }
            pthread_cond_signal(&cond_block); // 阻塞等待验证完成
            pthread_mutex_unlock(&lock_block);
        }
        if (a == 9) // 删除好友
        {
            std::cout << "删除好友" << std::endl;
            pthread_mutex_lock(&lock_delete);
            if (msgback.state != OP_OK)
            {
                if (msgback.state == USER_NOT_REGIST)
                {
                    std::cout << "用户未注册！" << std::endl;
                }
                if (msgback.state == MYSELF)
                {
                    std::cout << "不能删除自己" << std::endl;
                }
                if (msgback.state == NOTFRIEND)
                {
                    std::cout << "还不是好友啦" << std::endl;
                }
            }
            else
            {
                std::cout << "删除好友成功" << std::endl;
            }
            pthread_cond_signal(&cond_delete); // 阻塞等待验证完成
            pthread_mutex_unlock(&lock_delete);
        }
        if (a == 10) // 展示好友是否在线
        {
            if (msgback.state == STATUSFRIEND_OK)
            {
                std::cout << "id     name      status" << std::endl;
                std::cout << msgback.id << "     " << msgback.name << "        " << msgback.data << std::endl;
            }
            if (msgback.state == OP_OK)
            {
                pthread_mutex_lock(&lock_show);
                pthread_cond_signal(&cond_show);
                pthread_mutex_unlock(&lock_show);
            }
        }
        // if (msgback.state == YNCHAT)
        // {
        //     std::cout << "你为啥不打印" << std::endl;
        //     std::cout << msgback.id << ":" << msgback.data << std::endl;
        // }

        if (a == 11) // 私聊
        {
            if (msgback.state == CHATFRIENDRECORD_OK)
            {
                std::cout << msgback.id << ":" << msgback.data << std::endl;
            }
            // if (msgback.state != OP_OK)
            else
            {
                if (msgback.state == USER_NOT_REGIST)
                {
                    std::cout << "用户未注册！" << std::endl;
                    private_f = 1;
                    std::cout << "请按任意健退出" << std::endl;
                }
                if (msgback.state == MYSELF)
                {
                    std::cout << "不能和自己聊天" << std::endl;
                    private_f = 1;
                    std::cout << "请按任意健退出" << std::endl;
                }
                if (msgback.state == NOTFRIEND)
                {
                    std::cout << "还不是好友啦" << std::endl;
                    private_f = 1;
                    std::cout << "请按任意健退出" << std::endl;
                }
                if (msgback.state == FRIEND_OFFLINE)
                {
                    if (private_f == 2)
                        continue;
                    std::cout << "好友不在线" << std::endl;
                    private_f = 2;
                }
                pthread_mutex_lock(&lock_msg);
                pthread_cond_signal(&cond_msg);
                pthread_mutex_unlock(&lock_msg);
            }
            // pthread_cond_signal(&cond_msg);
            // pthread_mutex_unlock(&lock_msg);
        }
        if (a == 12)
        {
            if (msgback.state == OP_OK)
            {
                std::cout << "所有消息已通知完" << std::endl;
                pthread_mutex_lock(&lock_friendnotice);
                pthread_cond_signal(&cond_friendnotice); // 阻塞等待验证完成
                pthread_mutex_unlock(&lock_friendnotice);
                continue;
            }
            std::cout << "好友通知" << std::endl;
            struct protocol msg;
            cout << msgback.id << ":" << msgback.data << endl;
            cout << "你是否同意添加好友？(y/n)";
            char choice;
            cin >> choice;
            msg.cmd = YNACCEPT;
            msg.id = msgback.id;
            if (choice == 'y')
            {
                msg.data = "Y";
            }
            else
            {
                msg.data = "N";
            }
            send_data(msg, sockfd);
        }
        if (a == 13)
        {
            std::cout << "解除屏蔽好友" << std::endl;
            pthread_mutex_lock(&lock_unblock);
            if (msgback.state != OP_OK)
            {
                if (msgback.state == USER_NOT_REGIST)
                {
                    std::cout << "用户未注册！" << std::endl;
                }
                if (msgback.state == MYSELF)
                {
                    std::cout << "不能解除屏蔽自己" << std::endl;
                }
                if (msgback.state == NOTFRIEND)
                {
                    std::cout << "还不是好友啦" << std::endl;
                }
                if (msgback.state == ISUNBLOCKED)
                {
                    std::cout << "好友未被屏蔽" << std::endl;
                }
            }
            else
            {
                std::cout << "屏蔽好友成功" << std::endl;
            }
            pthread_cond_signal(&cond_unblock); // 阻塞等待验证完成
            pthread_mutex_unlock(&lock_unblock);
        }
        if (a == 14)
        {
            //       pthread_mutex_lock(&lock_friendrecord);
            if (msgback.state == CHATFRIENDRECORD_OK)
            {
                std::cout << msgback.id << ":" << msgback.data << std::endl;
            }
            else
            {
                if (msgback.state == OP_OK)
                {
                    std::cout << "聊天记录展示完毕！" << std::endl;
                }
                if (msgback.state == USER_NOT_REGIST)
                {
                    std::cout << "用户未注册！" << std::endl;
                }
                if (msgback.state == MYSELF)
                {
                    std::cout << "不能看自己的聊天记录" << std::endl;
                }
                if (msgback.state == NOTFRIEND)
                {
                    std::cout << "还不是好友啦" << std::endl;
                }
                pthread_mutex_lock(&lock_friendrecord);
                pthread_cond_signal(&cond_friendrecord); // 阻塞等待验证完成
                pthread_mutex_unlock(&lock_friendrecord);
            }
        }
        if (a == 15)
        {
            pthread_mutex_lock(&lock_create);
            if (msgback.state == OP_OK)
            {
                cout << "Registration successful! " << endl;
            }
            else
            {
                cout << "群已存在，请重新起名" << endl;
            }
            pthread_cond_signal(&cond_create); // 阻塞等待验证完成
            pthread_mutex_unlock(&lock_create);
        }
        if (a == 16)
        {
            pthread_mutex_lock(&lock_deletegroup);
            if (msgback.state == OP_OK)
            {
                if (msgback.cmd == LENDER)
                    cout << "你是群主，删除群成功" << endl;
                if (msgback.cmd == ORDINARY)
                    cout << "退出成功" << endl;
            }
            else if (msgback.state == GROUP_NOT_EXIST)
            {
                cout << "群聊不存在" << endl;
            }
            else if (msgback.state == GROUPNOTPERSON)
            {
                cout << "你不在群里面" << endl;
            }
            pthread_cond_signal(&cond_deletegroup); // 阻塞等待验证完成
            pthread_mutex_unlock(&lock_deletegroup);
        }
        if (a == 17)
        {
            pthread_mutex_lock(&lock_removeuser);
            if (msgback.state != OP_OK)
            {
                if (msgback.state == GROUP_NOT_EXIST)
                    std::cout << "群聊不存在" << endl;
                if (msgback.state == GROUPNOTPERSON)
                    cout << "你不在群里面" << endl;
                if (msgback.state == GROUPNOTPERSON1)
                    cout << "你要删除的人不在群里面" << endl;
                if (msgback.state == NOTRIGHT)
                    cout << "你没有权限" << endl;
            }
            else
                std::cout << "删除群成员成功" << std::endl;
            pthread_cond_signal(&cond_removeuser); // 阻塞等待验证完成
            pthread_mutex_unlock(&lock_removeuser);
        }
        if (a == 18)
        {
            // std::cout << "群聊列表" << std::endl;
            if (msgback.state == GROUPLIST_OK)
            {

                std::cout << "userid         type" << std::endl;
                std::cout << msgback.id << "                           " << msgback.cmd << std::endl;
            }
            else
            {
                if (msgback.state == GROUP_NOT_EXIST)
                    std::cout << "群聊不存在" << std::endl;
                if (msgback.state == GROUPNOTPERSON)
                    cout << "你不在群里面" << endl;
                pthread_mutex_lock(&lock_grouplist);
                pthread_cond_signal(&cond_grouplist);
                pthread_mutex_unlock(&lock_grouplist);
            }
        }
        if (a == 19)
        {
            // std::cout << "查看自己所在的群" << std::endl;
            if (msgback.state == IINGROUP_OK)
            {
                std::cout << "name:    " << msgback.name << std::endl;
            }
            else
            {
                pthread_mutex_lock(&lock_iingroup);
                pthread_cond_signal(&cond_iingroup);
                pthread_mutex_unlock(&lock_iingroup);
            }
        }
        if (a == 20)
        {
            pthread_mutex_lock(&lock_admanager);
            if (msgback.state != OP_OK)
            {
                if (msgback.state == GROUP_NOT_EXIST)
                    std::cout << "群聊不存在" << endl;
                if (msgback.state == GROUPNOTPERSON)
                    cout << "你不在群里面" << endl;
                if (msgback.state == ISNOTLENDER)
                    cout << "没有权利哦" << endl;
                if (msgback.state == GROUPNOTPERSON1)
                    cout << "你要删除的人不在群里面" << endl;
                if (msgback.state == ISMANAGER)
                    cout << "你要添加的人已经是管理员" << endl;
                if (msgback.state == NOTMANAGER)
                    cout << "你要取消的他本来就不是管理员" << endl;
            }
            else
            {
                std::cout << "操作成功" << std::endl;
            }
            pthread_cond_signal(&cond_admanager); // 阻塞等待验证完成
            pthread_mutex_unlock(&lock_admanager);
        }
        if (msgback.state == AGREEGROUP)
        {
            std::cout << "id为" << msgback.id << "同意了你的进群请求" << "恭喜你，加入了" << msgback.name << std::endl;
            continue;
        }
        if (msgback.state == REFUSEGROUP)
        {
            std::cout << "id为" << msgback.id << "拒绝了你的进群请求" << "很遗憾，你没加入" << msgback.name << std::endl;
            continue;
        }
        if (a == 21)
        {
            pthread_mutex_lock(&lock_applyaddgroup);
            if (msgback.state != OP_OK)
            {
                if (msgback.state == GROUP_NOT_EXIST)
                    std::cout << "群聊不存在" << endl;
                if (msgback.state == ISINGROUP)
                    cout << "你已经在群里面" << endl;
            }
            else
            {
                std::cout << "等待对方同意" << std::endl;
            }
            pthread_cond_signal(&cond_applyaddgroup); // 阻塞等待验证完成
            pthread_mutex_unlock(&lock_applyaddgroup);
        }
        if (a == 22)
        {

            if (msgback.state == OP_OK)
            {
                std::cout << "群的申请已经处理完毕" << std::endl;
                pthread_mutex_lock(&lock_noticegroup);
                pthread_cond_signal(&cond_noticegroup); // 阻塞等待验证完成
                pthread_mutex_unlock(&lock_noticegroup);
                continue;
            }
            cout << " 申请人:" << msgback.id << "想加入群:" << msgback.name << "原因:" << msgback.data << endl;
            cout << "你是否同意此人进群？(y/n)";
            char choice;
            cin >> choice;
            msg.cmd = YNACCEPTGROUP;
            msg.id = msgback.id;
            msg.name = msgback.name;
            if (choice == 'y')
            {
                msg.data = "Y";
            }
            else
            {
                msg.data = "N";
            }
            send_data(msg, sockfd);
        }
        if (a == 23) // 群聊
        {
            if (msgback.state == CHATGROUPRECORD_OK)
            {
                std::cout << msgback.name << "里的" << msgback.id << ":" << msgback.data << std::endl;
            }
            else
            {

                if (msgback.state == GROUP_NOT_EXIST)
                {
                    cout << "群聊不存在" << endl;
                    group_f = 1;
                    std::cout << "请按任意健退出" << std::endl;
                }
                if (msgback.state == GROUPNOTPERSON)
                {
                    cout << "你不在群里面" << endl;
                    group_f = 1;
                    std::cout << "请按任意健退出" << std::endl;
                }
                pthread_mutex_lock(&lock_groupmsg);
                pthread_cond_signal(&cond_groupmsg); // 阻塞等待验证完成
                pthread_mutex_unlock(&lock_groupmsg);
            }
        }
        if (a == 24)
        {
            if (msgback.state == CHATGROUPRECORD_OK)
            {
                std::cout << msgback.name << "里的" << msgback.id << ":" << msgback.data << std::endl;
            }
            else
            {
                if (msgback.state == OP_OK)
                {
                    std::cout << "聊天记录展示完毕！" << std::endl;
                }
                if (msgback.state == GROUP_NOT_EXIST)
                {
                    cout << "群聊不存在" << endl;
                }
                if (msgback.state == GROUPNOTPERSON)
                {
                    cout << "你不在群里面" << endl;
                }
                pthread_mutex_lock(&lock_chatgrouprecord);
                pthread_cond_signal(&cond_chatgrouprecord); // 阻塞等待验证完成
                pthread_mutex_unlock(&lock_chatgrouprecord);
            }
        }
        if (a == 6) // 少了一个判断法送给自己
        {
            if (msgback.state == USER_NOT_REGIST)
            {
                cout << "用户不存在" << endl;
            }
            else if (msgback.state == NOTFRIEND)
            {
                cout << "不是好友" << endl;
            }
            else if (msgback.state == GROUP_NOT_EXIST)
            {
                cout << "群聊不存在" << endl;
            }
            else if (msgback.state == GROUPNOTPERSON)
            {
                cout << "你不在群里面" << endl;
            }
            else if (msgback.state == OP_OK)
            {
                cout << "请输入文件路径" << endl;
                sendfile_f = 1;
            }
            pthread_mutex_lock(&lock_checkfile);
            pthread_cond_signal(&cond_checkfile); // 阻塞等待验证完成
            pthread_mutex_unlock(&lock_checkfile);
        }
        if (a == 25)
        {
            if (msgback.state == RECEIVEFILE_OK)
            {
                std::cout << msgback.id << ":" << msgback.data << std::endl;
                continue;
            }
            else
            {
                if (msgback.state == NOFILE)
                {
                    cout << "文件不存在" << endl;
                    ynfile_f = 1;
                    pthread_mutex_lock(&lock_receivefile);
                    pthread_cond_signal(&cond_receivefile); // 阻塞等待验证完成
                    pthread_mutex_unlock(&lock_receivefile);
                }

                if (msgback.state == RECEIVEFILE_END)
                {
                    cout << "未接收的文件展示完成" << endl;
                    pthread_mutex_lock(&lock_receivefile);
                    pthread_cond_signal(&cond_receivefile); // 阻塞等待验证完成
                    pthread_mutex_unlock(&lock_receivefile);
                }
                if (msgback.state == OP_OK)
                {
                    cout << "开始接收文件" << endl;

                    std::string filename;
                    filename = msgback.filename + ".client";
                    FILE *fp = fopen(filename.c_str(), "wb");
                    if (fp == NULL)
                    {
                        std::cerr << "Failed to open file for writing" << std::endl;
                    }

                    int original_flags = fcntl(sockfd, F_GETFL, 0);

                    if (fcntl(sockfd, F_SETFL, original_flags & ~O_NONBLOCK) == -1)
                    {
                        std::cerr << "Failed to set file descriptor to blocking mode: " << strerror(errno) << std::endl;
                        fclose(fp);
                    }
                    int len;
                    char buffer[1024];
                    off_t total_received = 0;
                    while (total_received < msgback.filesize)
                    {
                        std::cout << total_received << std::endl;
                        len = recv(sockfd, buffer, sizeof(buffer), 0);
                        if (len <= 0)
                        {
                            if (len < 0)
                            {
                                perror("recv");
                            }
                        }

                        fwrite(buffer, 1, len, fp);
                        total_received += len;
                        std::cout << "\r" << filename << ": " << (int)(((float)total_received / msgback.filesize) * 100) << "%" << std::endl;
                    }
                    fclose(fp);
                    if (total_received == msgback.filesize)
                    {
                        std::cout << "File received successfully" << std::endl;
                    }
                    else
                    {
                        std::cerr << "File size mismatch" << std::endl;
                    }
                    pthread_mutex_lock(&lock_receivefile);
                    pthread_cond_signal(&cond_receivefile); // 阻塞等待验证完成
                    pthread_mutex_unlock(&lock_receivefile);
                }
                // pthread_mutex_lock(&lock_receivefile);
                // pthread_cond_signal(&cond_receivefile); // 阻塞等待验证完成
                // pthread_mutex_unlock(&lock_receivefile);
            }
        }
    }
    return nullptr;
}
void ChatClient::registerUser()
{ // 注册
    struct protocol msg, msgback;
    msg.cmd = REGISTE;

    cout << "Input your name: ";
    cin >> msg.name; // 名字
    cout << msg.name << endl;
    cout << "Input your password: ";
    cin >> msg.data; // 密码
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_jy);
    pthread_cond_wait(&cond_jy, &lock_jy); // 阻塞等待验证完成
    if (login_f = 1)
    {
        displayMenu2();
    }
    pthread_mutex_unlock(&lock_jy);
    return;
}

void ChatClient::loginUser()
{ // 登录
    string ch;
    struct protocol msg;
    msg.cmd = LOGIN;
    cout << "Input your ID: ";
    while (1)
    {
        cin >> ch;
        if (isStringNumeric(ch))
        {
            msg.id = atoi(ch.c_str());
            id = msg.id;
            break;
        }
        else
        {
            cout << "输入有误！！！,请重新输入" << endl;
        }
    }
    cout << "Input your password: ";
    cin >> msg.data;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_login);
    pthread_cond_wait(&cond_login, &lock_login); // 阻塞等待验证完成
    if (login_f == 1)
    {
        std::cout << "登录成功！" << endl;
        displayMenu2();
    }
    else
    {
        std::cout << "登录失败！" << endl;
    }
    pthread_mutex_unlock(&lock_login);
    return;
}
void ChatClient::logoffUser()
{ // 注销
    string ch;
    struct protocol msg;
    msg.cmd = LOGOFF;
    cout << "Input your ID: ";
     while (1)
    {
        cin >> ch;
        if (isStringNumeric(ch))
        {
            msg.id = atoi(ch.c_str());
            break;
        }
        else
        {
            cout << "输入有误！！！,请重新输入" << endl;
        }
    }
    cout << "Input your password: ";
    cin >> msg.data;
    send_data(msg, sockfd);
    return;
}
// void ChatClient::logoutUser() {
//     close(sockfd);
//     login_f = -1;
// }
void ChatClient::addFriend() // 加好友
{
    string ch;
    struct protocol msg;
    msg.cmd = ADDFRIEND;
    cout << "Input your friend's ID: ";
    while (1)
    {
        cin >> ch;
        if (isStringNumeric(ch))
        {
            msg.id = atoi(ch.c_str());
            break;
        }
        else
        {
            cout << "输入有误！！！,请重新输入" << endl;
        }
    }
    std::cout << "Enter the message: ";
    std::cin >> msg.data;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_add);
    pthread_cond_wait(&cond_add, &lock_add); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_add);
    return;
}
// 屏蔽好友
void ChatClient::blockFriend()
{
    string ch;
    struct protocol msg;
    msg.cmd = BLOCKFRIEND;
    cout << "Input your friend's ID: ";
    while (1)
    {
        cin >> ch;
        if (isStringNumeric(ch))
        {
            msg.id = atoi(ch.c_str());
            break;
        }
        else
        {
            cout << "输入有误！！！,请重新输入" << endl;
        }
    }
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_block);
    pthread_cond_wait(&cond_block, &lock_block); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_block);
    return;
}
void ChatClient::deleteFriend() // 删除好友
{
    string ch;
    struct protocol msg;
    msg.cmd = DELETEFRIEND;
    cout << "Input your friend's ID: ";
    while (1)
    {
        cin >> ch;
        if (isStringNumeric(ch))
        {
            msg.id = atoi(ch.c_str());
            break;
        }
        else
        {
            cout << "输入有误！！！,请重新输入" << endl;
        }
    }
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_delete);
    pthread_cond_wait(&cond_delete, &lock_delete); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_delete);
    return;
}
void ChatClient::statusFriend() // 展示好友在线状态
{
    struct protocol msg, msgback;
    msg.cmd = STATUSFRIEND;
    //  msg.id = id;
    std::cout << "好友在线情况,0表示在线，1表示不在线" << std::endl;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_show);
    pthread_cond_wait(&cond_show, &lock_show);
    printf("==================\n");
    pthread_mutex_unlock(&lock_show);
    return;
}
void ChatClient::privateChat()
{
    string ch;
    private_f = -1;
    struct protocol msg;
    msg.cmd = PRIVATECHAT;
    cout << "Input your friend's ID: ";
    while (1)
    {
        cin >> ch;
        if (isStringNumeric(ch))
        {
            msg.id = atoi(ch.c_str());
            break;
        }
        else
        {
            cout << "输入有误！！！,请重新输入" << endl;
        }
    }
    msg.state = CHATFRIENDRECORD_OK;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_msg);
    pthread_cond_wait(&cond_msg, &lock_msg);
    pthread_mutex_unlock(&lock_msg);
    msg.state = OP_OK;
    printf("[Q或q退出聊天]->:");
    std::cout << "Enter the message: ";
    std::cin >> msg.data;
    while (strcmp(msg.data.c_str(), "Q") && strcmp(msg.data.c_str(), "q"))
    {
        if (private_f == 1)
        {
            break;
        }
        send_data(msg, sockfd);
        std::cout << msg.data << std::endl;
        std::cin >> msg.data;
    }
    // pthread_mutex_lock(&lock_msg);
    // pthread_cond_wait(&cond_msg, &lock_msg);
    // pthread_mutex_unlock(&lock_msg);
    // 如果发送来的消息sender和talkuser一致 或为0  (未处于聊天界面) 直接打印
    // 如果不相等存入未读消息

    return;
}
void ChatClient::friendNotice() // 好友通知
{

    struct protocol msg;
    msg.cmd = FRIENDNOTICE;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_friendnotice);
    pthread_cond_wait(&cond_friendnotice, &lock_friendnotice); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_friendnotice);
}
void ChatClient::unblockFriend() // 取消屏蔽好友
{
    string ch;
    struct protocol msg, msgback;
    msg.cmd = UNBLOCKFRIEND;
    cout << "Input you want to unblock friend's ID: ";
    while (1)
    {
        cin >> ch;
        if (isStringNumeric(ch))
        {
            msg.id = atoi(ch.c_str());
            break;
        }
        else
        {
            cout << "输入有误！！！,请重新输入" << endl;
        }
    }
    std::cout << "Enter the message: ";
    std::cin >> msg.data;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_unblock);
    pthread_cond_wait(&cond_unblock, &lock_unblock); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_unblock);
    return;
}
void ChatClient::chatfriendRecord() // 查看好友聊天记录
{
    string ch;
    struct protocol msg, msgback;
    msg.cmd = CHATFRIENDRECORD;
    cout << "Input your friend's ID: ";
     while (1)
    {
        cin >> ch;
        if (isStringNumeric(ch))
        {
            msg.id = atoi(ch.c_str());
            break;
        }
        else
        {
            cout << "输入有误！！！,请重新输入" << endl;
        }
    }
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_friendrecord);
    pthread_cond_wait(&cond_friendrecord, &lock_friendrecord); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_friendrecord);
}

void ChatClient::createGroup() // 创建群组
{
    struct protocol msg;
    msg.cmd = CREATEGROUP;
    cout << "Input you want to create group's name: ";
    cin >> msg.name;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_create);
    pthread_cond_wait(&cond_create, &lock_create); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_create);
}
void ChatClient::deleteGroup() // 删除群组
{
    struct protocol msg;
    msg.cmd = DELETEGROUP;
    cout << "Input you want to delete group's name: ";
    cin >> msg.name;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_deletegroup);
    pthread_cond_wait(&cond_deletegroup, &lock_deletegroup); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_deletegroup);
}
void ChatClient::removeUser() // 删除用户
{
    string ch;
    struct protocol msg;
    msg.cmd = REMOVEUSER;
    cout << "Input you want to remove whitch group's user: ";
    cin >> msg.name;
    cout << "Input you want to remove user's ID: ";
    while (1)
    {
        cin >> ch;
        if (isStringNumeric(ch))
        {
            msg.id = atoi(ch.c_str());
            break;
        }
        else
        {
            cout << "输入有误！！！,请重新输入" << endl;
        }
    }
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_removeuser);
    pthread_cond_wait(&cond_removeuser, &lock_removeuser); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_removeuser);
}
void ChatClient::groupList() // 查看群组列表
{
    struct protocol msg, msgback;
    msg.cmd = GROUPLIST;
    cout << "Input you want to look whitch group's list: " << endl;
    cin >> msg.name;
    std::cout << "群聊列表" << std::endl;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_grouplist);
    pthread_cond_wait(&cond_grouplist, &lock_grouplist); // 阻塞等待验证完成
    printf("==================\n");
    pthread_mutex_unlock(&lock_grouplist);
}
void ChatClient::iinGroup() // 查看我所在的群的列表
{
    struct protocol msg, msgback;
    msg.cmd = IINGROUP;
    msg.id = id;
    std::cout << "你所在的群有" << std::endl;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_iingroup);
    pthread_cond_wait(&cond_iingroup, &lock_iingroup); // 阻塞等待验证完成
    printf("==================\n");
    pthread_mutex_unlock(&lock_iingroup);
}
void ChatClient::adManager() // 添加删除管理员
{
    string ch;
    struct protocol msg;
    msg.cmd = ADMANAGER;
    cout << "Input you want to  group's name: ";
    cin >> msg.name;
    cout << "Input you want to  manager's ID: ";
    while (1)
    {
        cin >> ch;
        if (isStringNumeric(ch))
        {
            msg.id = atoi(ch.c_str());
            break;
        }
        else
        {
            cout << "输入有误！！！,请重新输入" << endl;
        }
    }
    cout << "你是想添加还是删除管理员?2添加,3删除";
    while (1)
    {
        cin >> ch;
        if (isStringNumeric(ch))
        {
            if (atoi(ch.c_str()) == 2 || atoi(ch.c_str()) == 3)
            {
                msg.state = atoi(ch.c_str());
                break;
            }
            else{
                cout << "输入有误！！！,请重新输入" << endl;
            }
        }
        else
        {
            cout << "输入有误！！！,请重新输入" << endl;
        }
    }
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_admanager);
    pthread_cond_wait(&cond_admanager, &lock_admanager); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_admanager);
}
void ChatClient::applyaddGroup() // 申请加入群组
{
    struct protocol msg;
    msg.cmd = APPLYADDGROUP;
    cout << "Input you want to apply add group's name: ";
    cin >> msg.name;
    cout << "Input you want to apply add group's reason: ";
    cin >> msg.data;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_applyaddgroup); // 阻塞等待验证完成
    pthread_cond_wait(&cond_applyaddgroup, &lock_applyaddgroup);
    pthread_mutex_unlock(&lock_applyaddgroup);
}
int ChatClient::noticeGroup() // 是否同意同意加群
{
    struct protocol msg;
    msg.cmd = GROUPNOTICE;
    msg.id = id;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_noticegroup);
    pthread_cond_wait(&cond_noticegroup, &lock_noticegroup); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_noticegroup);
    return 0;
}
// 群聊
void ChatClient::groupChat()
{
    group_f = -1;
    struct protocol msg;
    msg.cmd = GROUPCHAT;
    cout << "Input you want to chat group's name: ";
    cin >> msg.name;
    msg.state = CHATGROUPRECORD_OK;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_groupmsg);
    pthread_cond_wait(&cond_groupmsg, &lock_groupmsg);
    pthread_mutex_unlock(&lock_groupmsg);
    msg.state = OP_OK;
    printf("[Q或q退出聊天]->:");
    std::cout << "Enter the message: ";
    std::cin >> msg.data;
    while (strcmp(msg.data.c_str(), "Q") && strcmp(msg.data.c_str(), "q"))
    {
        if (group_f == 1)
            break;
        send_data(msg, sockfd);
        std::cout << msg.data << std::endl;
        std::cin >> msg.data;
    }
    return;
}

void ChatClient::chatgroupRecord() // 查看群聊天记录
{
    struct protocol msg;
    msg.cmd = GROUPCHATRECORD;
    cout << "Input you want to look whitch group's record: " << endl;
    cin >> msg.name;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_chatgrouprecord);
    pthread_cond_wait(&cond_chatgrouprecord, &lock_chatgrouprecord); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_chatgrouprecord);
}
void trueFile(struct protocol msg)
{
    // int sfd;
    // struct sockaddr_in server;
    // sfd = socket(PF_INET, SOCK_STREAM, 0);
    // server.sin_family = AF_INET;
    // server.sin_addr.s_addr = inet_addr("127.0.0.1");
    // server.sin_port = htons(8888);
    // connect(sfd, (struct sockaddr *)&server, sizeof(server));
    if (!std::filesystem::exists(msg.filename))
    {
        std::cout << "File does not exist" << std::endl;
        return;
    }
    int file = open(msg.filename.c_str(), O_RDONLY);
    if (file == -1)
    {
        std::cerr << "Failed to open file" << std::endl;
        return;
    }
    // 获取文件大小
    struct stat file_stat;
    fstat(file, &file_stat);
    msg.filesize = file_stat.st_size; // 获取文件大小
    msg.cmd = SENDFILE;
    send_data(msg, ssockfd);
    // 使用 sendfile 发送文件
    off_t offset = 0;
    ssize_t bytes_sent = 0;
    // 循环发送文件
    while (offset < file_stat.st_size)
    {
        bytes_sent = sendfile(ssockfd, file, &offset, file_stat.st_size - offset);
        if (bytes_sent < 0)
        {
            std::cerr << "Sendfile error: " << strerror(errno) << "\n";
            break;
        }
        std::cout << "Sent " << bytes_sent << " bytes, total sent: " << offset << " bytes\n";
    }

    // 关闭文件和 socket
    close(file);
    // close(sfd);
    return;
}
int ChatClient::sendFile() // 发送文件
{
    string ch;
    sendfile_f = -1;
    struct protocol msg;
    msg.cmd = CHECKFILE;
    std::cout << "选择发送文件给1:好友 2:群聊" << std::endl;
    int choice;
    cin >> ch;
    while (1)
    {
        cin >> ch;
        if (isStringNumeric(ch))
        {
            choice = atoi(ch.c_str());
            if (choice == 1 || choice == 2)
            {
                break;
            }
            else
            {
                cout << "输入有误！！！,请重新输入" << endl;
            }
        }
        else
        {
            cout << "输入有误！！！,请重新输入" << endl;
        }
    }
    if (choice == 1)
    {
        std::cout << "Enter the friend's ID: ";
        while (1)
        {
            cin >> ch;
            if (isStringNumeric(ch))
            {
                    msg.id = atoi(ch.c_str());
                    break;
            }
            else
            {
                cout << "输入有误！！！,请重新输入" << endl;
            }
        }
    }
    else if (choice == 2)
    {
        std::cout << "Enter the group's name: ";
        std::cin >> msg.name;
    }
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_checkfile);
    pthread_cond_wait(&cond_checkfile, &lock_checkfile); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_checkfile);
    ssockfd = sockfd;
    if (sendfile_f == 1) // 这可能会存在线程竞争的问题！！
    {
        std::cin >> msg.filename;
        std::thread thread(trueFile, msg);
        thread.detach();
    }
    return 0;
}
void ChatClient::receiveFile() // 接收文件
{
    ynfile_f = -1;
    struct protocol msg;
    // 先打引出未收到的文件
    msg.cmd = RECEIVEFILE;
    msg.state = RECEIVEFILE_OK;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_receivefile);
    pthread_cond_wait(&cond_receivefile, &lock_receivefile); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_receivefile);
    if (ynfile_f == 1)
    {
        ynfile_f = -1;
        return;
    }
    std::cout << "请输入你要接收的文件名: " << std::endl;
    msg.state = OP_OK;
    std::cin >> msg.filename;
    send_data(msg, sockfd);
    pthread_mutex_lock(&lock_receivefile);
    pthread_cond_wait(&cond_receivefile, &lock_receivefile); // 阻塞等待验证完成
    pthread_mutex_unlock(&lock_receivefile);
    return;
}
void ChatClient::displayMenu1()
{
    int sel = -1;
    string ch;
    while (sel)
    {
        cout << "\t 1 注册" << endl;
        cout << "\t 2 登录" << endl;
        cout << "\t 3 注销" << endl;
        cout << "\t 0 退出" << endl;
        cin >> ch;
        if (isStringNumeric(ch))
        {
            sel = atoi(ch.c_str());
            switch (sel)
            {
            case 1:
                a = 1;
                registerUser();
                break;
            case 2:
                a = 2;
                loginUser();
                break;
            case 3:
                a = 3;

                logoffUser();
                break;
            }
        }
        else
        {
            std::cout << "输入错误，请重新输入" << std::endl;
        }
    }
    return;
}
void ChatClient::displayMenu2()
{
    int sel = -1;
    string ch;
    while (sel)
    {
        cout << "\t 4 好友管理 " << endl;
        cout << "\t 5 群组管理" << endl;
        cout << "\t 6 文件发送" << endl;
        cout << "\t 25 文件接收" << endl;
        cin >> ch;
        if (isStringNumeric(ch))
        {
            sel = atoi(ch.c_str());
            switch (sel)
            {
            case 4:
                displayMenu3();
                break;
            case 5:
                displayMenu4();
                break;
            case 6:
                a = 6;
                sendFile();
                break;
            case 25:
                a = 25;
                receiveFile();
                break;
            }
        }
        else
        {
            std::cout << "输入错误，请重新输入" << std::endl;
        }
    }
    return;
}
void ChatClient::displayMenu3()
{
    int sel = -1;
    string ch;
    while (sel)
    {
        cout << "\t 7 添加好友" << endl;
        cout << "\t 8 屏蔽好友" << endl;
        cout << "\t 9 删除好友" << endl;
        cout << "\t 10 在线列表" << endl;
        cout << "\t 11 私聊" << endl;
        cout << "\t 12 好友通知" << endl;
        cout << "\t 13 取消屏蔽好友" << endl;
        cout << "\t 14 查看聊天记录" << endl;
        cout << "\t 0 返回上一级页面" << endl;
        cin >> ch;
        if (isStringNumeric(ch))
        {
            sel = atoi(ch.c_str());
            if (sel == 0)
                break;
            switch (sel)
            {
            case 7:
                a = 7;
                addFriend();
                break;
            case 8:
                a = 8;
                blockFriend();
                break;
            case 9:
                a = 9;
                deleteFriend();
                break;
            case 10:
                a = 10;
                statusFriend();
                break;
            case 11:
                a = 11;
                privateChat();
                break;
            case 12:
                a = 12;
                friendNotice();
                break;
            case 13:
                a = 13;
                unblockFriend();
                break;
            case 14:
                a = 14;
                chatfriendRecord();
                break;
            }
        }
        else
        {
            std::cout << "输入错误，请重新输入" << std::endl;
        }
    }
    return;
}

void ChatClient::displayMenu4()
{
    int sel = -1;
    string ch;
    while (sel)
    {
        cout << "\t 15 建新群 " << endl;
        cout << "\t 16 退群/解散群" << endl;
        cout << "\t 17 移除有户" << endl;
        cout << "\t 18 查群列表" << endl;
        cout << "\t 19 查自己所在的群" << endl;
        cout << "\t 20 群主对管理员的增加和删除" << endl;
        cout << "\t 21 申请加群" << endl;
        cout << "\t 22 群通知信息" << endl;
        cout << "\t 23  群聊" << endl;
        cout << "\t 24 查看群聊天记录" << endl;
        cout << "\t 0 返回上一级页面" << endl;

        cin >> ch;
        if (isStringNumeric(ch))
        {
            sel = atoi(ch.c_str());
            if (sel == 0)
                break;
            switch (sel)
            {
            case 15:
                a = 15;
                createGroup();
                break;
            case 16:
                a = 16;
                deleteGroup();
                break;
            case 17:
                a = 17;
                removeUser();
                break;
            case 18:
                a = 18;
                groupList();
                break;
            case 19:
                a = 19;
                iinGroup();
                break;
            case 20:
                a = 20;
                adManager();
                break;
            case 21:
                a = 21;
                applyaddGroup();
                break;
            case 22:
                a = 22;
                noticeGroup();
                break;
            case 23:
                a = 23;
                groupChat();
                break;
            case 24:
                a = 24;
                chatgroupRecord();
                break;
            }
        }
        else
        {
            std::cout << "输入错误，请重新输入" << std::endl;
        }
    }
    return;
}
void ChatClient::run()
{
    displayMenu1();
}

int main(int argc, char **argv)
{
    pthread_mutex_init(&lock_jy, NULL);
    pthread_cond_init(&cond_jy, NULL);
    pthread_mutex_init(&lock_login, NULL);
    pthread_cond_init(&cond_login, NULL);
    pthread_mutex_init(&lock_add, NULL);
    pthread_cond_init(&cond_add, NULL);
    pthread_mutex_init(&lock_block, NULL);
    pthread_cond_init(&cond_block, NULL);
    pthread_mutex_init(&lock_delete, NULL);
    pthread_cond_init(&cond_delete, NULL);
    pthread_mutex_init(&lock_show, NULL);
    pthread_cond_init(&cond_show, NULL);
    pthread_mutex_init(&lock_friendnotice, NULL);
    pthread_cond_init(&cond_friendnotice, NULL);
    pthread_mutex_init(&lock_unblock, NULL);
    pthread_cond_init(&cond_unblock, NULL);
    pthread_mutex_init(&lock_msg, NULL);
    pthread_cond_init(&cond_msg, NULL);
    pthread_mutex_init(&lock_create, NULL);
    pthread_cond_init(&cond_create, NULL);
    pthread_mutex_init(&lock_deletegroup, NULL);
    pthread_cond_init(&cond_deletegroup, NULL);
    pthread_mutex_init(&lock_removeuser, NULL);
    pthread_cond_init(&cond_removeuser, NULL);
    pthread_mutex_init(&lock_grouplist, NULL);
    pthread_cond_init(&cond_grouplist, NULL);
    pthread_mutex_init(&lock_admanager, NULL);
    pthread_cond_init(&cond_admanager, NULL);
    pthread_mutex_init(&lock_applyaddgroup, NULL);
    pthread_cond_init(&cond_applyaddgroup, NULL);
    pthread_mutex_init(&lock_noticegroup, NULL);
    pthread_cond_init(&cond_noticegroup, NULL);
    pthread_mutex_init(&lock_friendrecord, NULL);
    pthread_cond_init(&cond_friendrecord, NULL);
    pthread_mutex_init(&lock_chatgrouprecord, NULL);
    pthread_cond_init(&cond_chatgrouprecord, NULL);
    pthread_mutex_init(&lock_checkfile, NULL);
    pthread_cond_init(&cond_checkfile, NULL);
    pthread_mutex_init(&lock_groupmsg, NULL);
    pthread_cond_init(&cond_groupmsg, NULL);
    pthread_mutex_init(&lock_receivefile, NULL);
    pthread_cond_init(&cond_receivefile, NULL);
    std::string server_addr = "127.0.0.1";
    if (argc >= 2)
    {
        server_addr = argv[1];
    }
    ChatClient client(server_addr.c_str(), PORT);
    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, func, &client.sockfd);

    client.run();
    return 0;
}
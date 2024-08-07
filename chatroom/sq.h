
#include <mysql/mysql.h>
#include <iostream>
#include "chat.h"
#include <fstream>
class Person
{
public:
    Person(MYSQL *mysql, protocol &msg, int sockfd);
    ~Person();

    int addUser();    // 加人
    int deleteUser(); // 删人

    void offline(); // 离线
    void upline();  // 上线
    int findId();   // 通过客户端的cfd找id
    int findCfd(int id);  // 通过id找cfd,为了给好友发送信息
    int isFriend(); // 已经是朋友阿
    int isMyself(); // 是自己
    int sq_addFriend();
    int sq_blockFriend();
    int sq_deleteFriend();
    int sq_statusFriend(int id);
    int sq_unblockFriend();
    int sq_restoreFriend();   //// 先将好友发送的消息存起来
   // int senddatatoFriend();   // 将存储在数据库的信息发送给好友
    void registerUser();      // 注册
    bool checkUserExists();   // 用户是否存在
    bool checkUserOnline(int id);   // 是否已经在线
    bool checkUserPassword(); // 检查密码
    void loginUser();         // 登录
    void logoffUser();        // 注销
    void addFriend();         // 加好友
    int ynAccept();           // 接受好友
    void blockFriend();       // 屏蔽好友
    void deleteFriend();      // 删除好友
    void statusFriend();      // 好友状态
    void privateChat();       // 私聊
    void unblockFriend();     // 解除屏蔽
    int sq_isBlocked();       // 是否被屏蔽
    int friendNotice(); // 好友通知
    int sq_chatfriendRecord();
    void chatfriendRecord();//好友聊天记录

    int groupynMe(int id); // 判断是否在群里
    void createGroup();    // 创建群
    int checkGroup();      // 检查群是否存在
    void deleteGroup();    // 删除群
    void removeUser();     // 移除群成员
    void sq_groupList();
    void groupList(); // 群列表
    void iinGroup();  // 查看自己所在的群
    void sq_adManager();
    void adManager(); // 添加删除管理员
    int sq_applyaddGroup();
    void applyaddGroup(); // 申请加群
    int ynacceptGroup(); // 是否同意加群
    int groupNotice();// 群通知
    int sq_restoreGroup();
    int groupChat();// 群聊
    int sq_chatgroupRecord();
    void groupchatRecord();//查找群聊记录

    void checkFile(); // 检查接收文件的人或群
    void sendFile();//发送文件
private:
    MYSQL *mysql;
    struct protocol &msg;
    int sockfd; // 客户端描述符
};

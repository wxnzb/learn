#ifndef _TCP_CHAT  
#define _TCP_CHAT  

#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <pthread.h>  
#include <stdlib.h>  
#include <cstring>  
#include <string>  
#include <vector>  
#include <iostream>  
#include <filesystem>
#include <sys/sendfile.h>


// C/S 通信的结构体  
struct protocol {   
    int cmd=0;      // 命令  
    int state=0;    // 存储命令返回信息  
    std::string name ;// 用户名  
    std::string data; // 数据  
    int id=0;       // 区分用户的关键 
    std::string filename;//文件名 
    unsigned long long filesize=0;//文件偏移量
 
};  
#define RECEIVEOK -4 //为了改变map里面第二个状态
#define RECEIVEFILE_OK -3 //为了给服务端让他知道是要打印为接收的消息
#define RECEIVEFILE -2//接收文件

#define  SENDFILEEND -1//发送文件结束,因为你把state当作偏移量给服务端了，所以这里用-1来表示
#define BROADCAST 1   //广播数据
#define PRIVATECHAT 2     //私聊
#define REGISTE 3     //注册账号
#define LOGIN 4    //登录
#define ONLINEUSER     5//显示在线用户
#define LOGOFF    6   //退出
#define ADDFRIEND 7//添加好友
#define BLOCKFRIEND 8//屏蔽好友
#define DELETEFRIEND 9//删除好友
#define STATUSFRIEND 10//查询好友状态
#define PLEASEPRIVATECHAT 11//请求私聊
#define YNACCEPT 12 //同意或拒绝好友请求
#define UNBLOCKFRIEND 13//取消屏蔽好友
#define CREATEGROUP 14//创建群聊
#define DELETEGROUP 15//删除群聊
#define LENDER  16//删除群时是群主
#define ORDINARY 17//删除群时是普通成员
#define REMOVEUSER 18//删除群中的管理员或用户
#define IINGROUP 19//显示自己所在的群聊
#define ADMANAGER 20//添加删除管理员
#define APPLYADDGROUP 21//申请加入群聊
#define YNACCEPTGROUP 22//同意或拒绝此人加入群聊
#define FRIENDNOTICE 23//好友通知
#define GROUPNOTICE 24//群聊通知
#define CHATFRIENDRECORD 25//好友聊天记录
#define GROUPCHAT 26//群聊
#define GROUPCHATRECORD 27//群聊记录
#define SENDFILE 28//发送文件
#define CHECKFILE 29//检查发送文件给的人是否存在什么的
//#define  SENDFILEEND 29//发送文件结束



/*return code*/
#define OP_OK    30        //操作成功

#define STATUSFRIEND_OK    31  //显示在线用户，未结
#define ONLINEUSER_OVER  32  //显示在线用户，已经发送完毕
#define NAME_EXIST 33       //注册信息，用户名已经存在
#define PASSWORD_ERROR 34 //登录时，输入的用户名密码不对
#define USER_LOGED 35     //登录时，提示该用户已经在线
#define USER_NOT_REGIST 36  //登录时，提示用户没有注册
#define OFFLINE 37//用户下线
#define GROUPLIST 38//显示群聊列表


#define  MYSELF 39
#define ISFRIEND 40
#define NOTFRIEND 41
#define FRIEND_OFFLINE 42//在进行聊天室，显示好友没在线
#define AGREEPRIVATECHAT 43//同意私聊
#define REGISTE_OK 44//注册成功
#define REGISTE_ERROR 45//注册失败`
#define NOCONTINUE 46//不要重复发送好友申请
#define AGREEFRIENDNEED 47//同意好友请求
#define REFUSEFRIENDNEED 48//拒绝好友请求
#define ISUNBLOCKED 49  //没有屏蔽好友，无需再取消屏蔽了
#define ISBLOCKED 50//已经屏蔽好友，无需再屏蔽了
#define YNCHAT 51//是否同意私聊
#define GROUP_NOT_EXIST 52//群聊不存在
#define GROUPNOTPERSON 53//不是群聊成员
#define GROUPNOTPERSON1 54//要删除的人不再此群聊中
#define NOTRIGHT 55//没有权力删除人，你权限不够
#define GROUPLIST_OK    56  //显示群成员，未结束
#define IINGROUP_OK  57//显示自己所在的群聊，未结束
#define ISMANAGER 58//是管理员
#define NOTMANAGER 59//不是管理员
#define ISNOTLENDER 60//不是群主
#define ISINGROUP 61//加群的时候你已经在群聊中
#define AGREEGROUP 62//同意加入群聊
#define REFUSEGROUP 63//拒绝加入群聊
#define CHATFRIENDRECORD_OK 64//好友聊天记录，未结束
#define YNGROUPCHAT 65//是否同意群聊
#define CHATGROUPRECORD_OK 66//群聊记录，未结束
#define REQUEST 67//实时有到加好友请求或是群聊请求
#define SENDFILE_OK 68//发送文件成功
#define NOFILE 69//没有文件
#define RECEIVEFILE_END 70//接收文件结束
#define OLDSEND 71//表明你想加的人他先给你已经发了好友申请了













#endif // _TCP_CHAT
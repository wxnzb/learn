#include "sq.h"
#include <cstring>
#include <iostream>
#include "chat.h"
#include "json.h"
Person::Person(MYSQL *Mysql, protocol &Msg, int Sockfd) : mysql(Mysql), msg(Msg), sockfd(Sockfd)
{
}

Person::~Person()
{
}

// 加人
int Person::addUser()
{
    char sql_cmd[256];
    std::cout << msg.name << msg.data << std::endl;
    std::cout << sockfd << std::endl;
    std::cout<<"不是，别这样"<<std::endl;
    snprintf(sql_cmd, sizeof(sql_cmd), "insert into userdata(username, password,cfd,status) values('%s', '%s','%d','%d');",msg.name.c_str(), msg.data.c_str(), sockfd, 1);

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql insert error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    int insert_id = mysql_insert_id(mysql);
    std::cout << "insert_id: " << insert_id << std::endl;
    return insert_id;
    return 1;
}
// 减人
int Person::deleteUser()
{
    std::cout << msg.name << msg.data << std::endl;
    char sql_cmd[256];
    std::cout << msg.name << msg.data << std::endl;
    std::cout << sockfd << std::endl;
    snprintf(sql_cmd, sizeof(sql_cmd), "delete from userdata where id='%d';", msg.id);

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql insert error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    return 0;
}
// 根据cfd找id
int Person::findId()
{
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select id from userdata where cfd = '%d';", sockfd);

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql insert error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    MYSQL_RES *result = mysql_store_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != nullptr)
    {
        return atoi(row[0]);
    }
    return 0;
}
// 根据id找cfd
int Person::findCfd()
{
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select cfd from userdata where id = '%d';", msg.id);

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql insert error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    MYSQL_RES *result = mysql_store_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != nullptr)
    {
        return atoi(row[0]);
    }
    return 0;
}
// 是自己
int Person::isMyself()
{
    if (msg.id == findId())
    {
        return 1;
    }
    return 0;
}
// SELECT * FROM frendslist
// WHERE (usera = 'your_usera_value' AND userb = 'your_userb_value')
// OR (usera = 'your_userb_value' AND userb = 'your_usera_value');
// SELECT IF(EXISTS(SELECT 1 FROM frendslist
// WHERE (usera = 'your_usera_value' AND userb = 'your_userb_value')
// OR (usera = 'your_userb_value' AND userb = 'your_usera_value')), 1, 0);
// 已经是好朋友啦
int Person::isFriend()
{
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select 1 from friendlist where (usera = '%d' and userb = '%d')or (usera = '%d' and userb = '%d');", findId(), msg.id, msg.id, findId());

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql insert error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    MYSQL_RES *result = mysql_store_result(mysql);
    bool exists = (mysql_fetch_row(result) != nullptr);
    mysql_free_result(result);
    return exists;
}
// 添加好友
int Person::sq_addFriend()
{
    std::cout << "别放弃！" << std::endl;
    int sender = findId();
    struct protocol msgback;
    // 先判断是否发过请求
    // status=0表示发的请求，1表示同意，2表示拒绝，3表示信息
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select * from  datamessage where (inid = %d and  toid = %d);", sender, msg.id);
    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql select error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    MYSQL_RES *result = mysql_store_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != nullptr)
    {
        msgback.data = "已经发过请求了,等待对方验证";
        msgback.state = NOCONTINUE;
        send_data(msgback, sockfd);
        return 0;
    }
    // 现存在数据库中
    char sql_cmd1[256];
    snprintf(sql_cmd1, sizeof(sql_cmd1), "insert into datamessage(inid, toid,message,status) values('%d','%d','%s','%d');", findId(), msg.id, msg.data.c_str(), 0);
    ret = mysql_query(mysql, sql_cmd1);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql insert error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    else
    {
        printf("[%d]对[%d]好友请求存入数据库\n", sender, msg.id);
    }
    return 0;
}
// 屏蔽好友
int Person::sq_blockFriend()
{
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "update friendlist set status=%d where (usera = '%d' and userb = '%d')or (usera = '%d' and userb = '%d');", 0, findId(), msg.id, msg.id, findId());

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql update error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    return 0;
}
// 删除好友
int Person::sq_deleteFriend()
{
    std::cout << msg.name << msg.data << std::endl;
    char sql_cmd[256];
    std::cout << msg.name << msg.data << std::endl;
    std::cout << sockfd << std::endl;
    snprintf(sql_cmd, sizeof(sql_cmd), "delete from friendlist where (usera = '%d' and userb = '%d')or (usera = '%d' and userb = '%d');", findId(), msg.id, msg.id, findId());

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql delete error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    return 0;
}
// 根据id查好友的名字和状态
int Person::sq_statusFriend(int id)
{
    struct protocol msg_back;
    msg_back.cmd = STATUSFRIEND;
    std::cout << "id:" << id << std::endl;
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select username,status from userdata where id = '%d';", id);
    std::cout << "1" << std::endl;
    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql query error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    MYSQL_RES *result = mysql_store_result(mysql);
    if (result == NULL)
    {
        std::cerr << "[ERR] mysql store result error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }

    int num_rows = mysql_num_rows(result);
    std::cout << "Number of rows: " << num_rows << std::endl;
    for (int i = 0; i < num_rows; i++)
    {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row == NULL)
        {
            std::cerr << "[ERR] mysql fetch row error: " << mysql_error(mysql) << std::endl;
            break;
        }
        msg_back.name = row[0];
        msg_back.data = row[1];
        msg_back.id = id;
        msg_back.state = STATUSFRIEND_OK; // 表示好友状态显示还没结束
        send_data(msg_back, sockfd);
        std::cout << "好友名字: " << row[0] << std::endl;
        std::cout << "好友状态: " << row[1] << std::endl;
    }

    mysql_free_result(result);
    return 0;
}
// 先将好友发送的消息存起来
int Person::sq_restoreFriend()
{
    // int status = 0;
    // int len = msg.data.length();
    // int i, j;
    // for (i = 0; i < len; i++)
    // {
    //     if (msg.data[i] == '\'')
    //     {
    //         status = 1;
    //         printf("----- --- %c\n", msg.data[i]);
    //         break;
    //     }
    // }
    // if (status)
    // {
    //     msg.data[len + 1] = '\0';
    //     for (j = len; j > i; j--)
    //     {
    //         msg.data[j] = msg.data[j - 1];
    //     }
    // }
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "insert into datamessage (inid,toid,status,message) values('%d','%d','%d','%s')", findId(), msg.id, 3, msg.data.c_str());

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql insert error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    else
        printf("[%d]和[%d]聊天记录成功录入数据库\n", findId(), msg.id);
    return 0;
}
// 将存储在数据库的信息发送给好友
// int Person::senddatatoFriend()
// {
//     char sql_cmd[256];
//     snprintf(sql_cmd, sizeof(sql_cmd), "select  * from  messagedata where (inid = %d and  toid = %d and status = %d)", findId(), msg.id, 3); // 3未发送
//     int ret = mysql_query(mysql, sql_cmd);
//     if (ret != 0)
//     {
//         std::cerr << "[ERR] mysql select error: " << mysql_error(mysql) << std::endl;
//         return -1; // Error indicator
//     }
//     MYSQL_RES *result = mysql_store_result(mysql);
//     MYSQL_ROW row;
//     // 循环读取每一行数据
//     while (row = mysql_fetch_row(result))
//     {
//         char sql_cmd1[256];
//         snprintf(sql_cmd1, sizeof(sql_cmd1), "update messagedata set status = %d where (inid = %d and toid = %d and id=%d)", 4, findId(), msg.id, atoi(row[4])); // 4已经发送
//         int ret = mysql_query(mysql, sql_cmd1);
//         if (ret != 0)
//         {
//             std::cerr << "[ERR] mysql insert error: " << mysql_error(mysql) << std::endl;
//             return -1; // Error indicator
//         }
//         else
//         {
//             struct protocol msg_back;
//             msg_back.id = findId();
//             msg_back.state = OP_OK;
//             msg_back.data = row[2];
//             send_data(msg_back, findCfd());
//             printf("[%d]对[%d]消息发送成功\n", findId(), msg.id);
//         }
//     }
//     return 0;
// }
int Person::sq_unblockFriend() // 解除屏蔽好友
{
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "update friendlist set status = %d where (usera = %d and userb = %d) or (usera = %d and userb = %d)", 1, findId(), msg.id, msg.id, findId());
    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql update error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    return 0;
}
// 下线
void Person::offline()
{
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "update userdata set status=%d where cfd='%d';",0, sockfd);

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql update error: " << mysql_error(mysql) << std::endl;
    }
}
// 上线
void Person::upline()
{
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "update userdata set status=%d ,cfd=%d where id='%d';", 1, sockfd, msg.id);

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql update error: " << mysql_error(mysql) << std::endl;
    }
}

// 注册
void Person::registerUser()
{
    struct protocol msg_back;
    msg_back.cmd = REGISTE;
    msg_back.id = addUser();
    printf("%d\n", sockfd);
    std::cout << msg_back.cmd << std::endl;
    msg_back.state = OP_OK;
    // 发给客户端
    send_data(msg_back, sockfd);
    return;
}

// 用户是否存在
bool Person::checkUserExists()
{
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select 1 from userdata where id = '%d';", msg.id);

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql query error: " << mysql_error(mysql) << std::endl;
        return false;
    }

    MYSQL_RES *result = mysql_store_result(mysql);
    bool exists = (mysql_fetch_row(result) != nullptr);
    mysql_free_result(result);
    return exists;
}
// 查找想屏蔽的好友是否已经屏蔽
int Person::sq_isBlocked()
{
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select status from friendlist where (usera = %d and userb = %d) or (usera = %d and userb = %d);", findId(), msg.id, msg.id, findId());
    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql select error: " << mysql_error(mysql) << std::endl;
        return false;
    }

    MYSQL_RES *result = mysql_store_result(mysql);
    bool isblock = false;
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != nullptr)
    {
        isblock = (atoi(row[0]) == 0);
    }
    mysql_free_result(result);
    return isblock;
}
// 用户是否已经在线
bool Person::checkUserOnline()
{
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select status from userdata where id ='%d';", msg.id);

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql query error: " << mysql_error(mysql) << std::endl;
        return false;
    }

    MYSQL_RES *result = mysql_store_result(mysql);
    bool online = false;
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != nullptr)
    {
        online = (atoi(row[0]) == 1);
    }
    mysql_free_result(result);
    return online;
}

// 检查密码是否正确
bool Person::checkUserPassword()
{
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select password from userdata where id ='%d';", msg.id);

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql query error: " << mysql_error(mysql) << std::endl;
        return false;
    }

    MYSQL_RES *result = mysql_store_result(mysql);
    bool password_correct = false;
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != nullptr)
    {
        password_correct = (strcmp(row[0], msg.data.c_str()) == 0);
    }
    mysql_free_result(result);
    return password_correct;
}

// 登录
void Person::loginUser()
{
    struct protocol msg_back;
    msg_back.cmd = LOGIN;

    if (checkUserExists())
    {
        if (checkUserOnline())
        {
            msg_back.state = USER_LOGED;
        }
        else
        {
            if (checkUserPassword())
            {
                upline();
                msg_back.state = OP_OK;
            }
            else
            {
                msg_back.state = PASSWORD_ERROR;
            }
        }
    }
    else
    {
        msg_back.state = USER_NOT_REGIST;
    }
    send_data(msg_back, sockfd);
}
// 注销
void Person::logoffUser()
{
    std::cout << "logoff" << std::endl;
    struct protocol msg_back;
    msg_back.cmd = LOGOFF;

    if (checkUserExists())
    {
        /*if (checkUserOnline()) {
            msg_back.state = USER_LOGED;
        } else */
        if (checkUserPassword())
        {
            deleteUser();
            msg_back.state = OP_OK;
        }
        else
        {
            msg_back.state = PASSWORD_ERROR;
        }
    }
    else
    {
        msg_back.state = USER_NOT_REGIST;
    }
    send_data(msg_back, sockfd);
}
// 是否接受好友请求
int Person::ynAccept()
{
    struct protocol msg_back;
    msg_back.id = findId();
    if (msg.data == "Y")
    {
        char sql_cmd[256];
        std::cout << msg.id << std::endl;
        std::cout << findId() << std::endl;
        snprintf(sql_cmd, sizeof(sql_cmd), "update datamessage set status=%d where(inid=%d and toid=%d and status=%d);", 1, msg.id, findId(), 0); // 同意好友请求
        int ret = mysql_query(mysql, sql_cmd);
        if (ret != 0)
        {
            std::cerr << "[ERR] mysql update error: " << mysql_error(mysql) << std::endl;
            return false;
        }

        char sql_cmd1[256];
        snprintf(sql_cmd1, sizeof(sql_cmd1), "insert into friendlist(usera,userb,status) values(%d,%d,1);", msg.id, findId()); // 添加好友
        ret = mysql_query(mysql, sql_cmd1);
        if (ret != 0)
        {
            std::cerr << "[ERR] mysql insert error: " << mysql_error(mysql) << std::endl;
            return false;
        }
        msg_back.state = AGREEFRIENDNEED;
    }
    else
    {
        char sql_cmd2[256];
        snprintf(sql_cmd2, sizeof(sql_cmd2), "update datamessage set status=%d where(inid=%d and toid=%d and status=%d);", 2, msg.id, findId(), 0); // 拒绝好友请求
        int ret = mysql_query(mysql, sql_cmd2);
        if (ret != 0)
        {
            std::cerr << "[ERR] mysql updata error: " << mysql_error(mysql) << std::endl;
            return false;
        }
        msg_back.state = REFUSEFRIENDNEED;
    }
    send_data(msg_back, findCfd());
    return 0;
}
void Person::addFriend() // 添加好友
{
    struct protocol msg_back;
    msg_back.cmd = ADDFRIEND;

    if (checkUserExists())
    {
        if (isMyself())
        {
            msg_back.state = MYSELF; // 是自己
        }
        if (isFriend())
        {
            msg_back.state = ISFRIEND; // 已经是好友
        }
        else
        {
            sq_addFriend();
            msg_back.state = OP_OK;
        }
    }
    else
    {
        msg_back.state = USER_NOT_REGIST;
    }
    send_data(msg_back, sockfd);
}
// 屏蔽好友
void Person::blockFriend()
{
    struct protocol msg_back;
    msg_back.cmd = BLOCKFRIEND;

    if (checkUserExists())
    {
        if (isMyself())
        {
            msg_back.state = MYSELF; // 是自己
        }
        else if (isFriend())
        {
            if (!sq_isBlocked())
            {
                sq_blockFriend();
                msg_back.state = OP_OK; // 屏蔽好友成功
            }
            else
            {
                msg_back.state = ISBLOCKED; // 已经屏蔽好友
            }
        }
        else
        {
            msg_back.state = NOTFRIEND; // 不是好友
        }
    }
    else
    {
        msg_back.state = USER_NOT_REGIST;
    }
    send_data(msg_back, sockfd);
}
void Person::deleteFriend() // 删除好友
{
    struct protocol msg_back;
    msg_back.cmd = BLOCKFRIEND;

    if (checkUserExists())
    {
        if (isMyself())
        {
            msg_back.state = MYSELF; // 是自己
        }
        else if (isFriend())
        {
            sq_deleteFriend();
            msg_back.state = OP_OK; // 删除好友成功
        }
        else
        {
            msg_back.state = NOTFRIEND; // 不是好友
        }
    }
    else
    {
        msg_back.state = USER_NOT_REGIST;
    }
    send_data(msg_back, sockfd);
}
void Person::statusFriend() // 查看好友状态
{
    struct protocol msg_back;
    msg_back.cmd = STATUSFRIEND;
    std::vector<int> friendid;
    std::cout << "status" << std::endl;
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select usera from friendlist where userb='%d' union select userb from friendlist where usera='%d';", msg.id, msg.id);

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql select error: " << mysql_error(mysql) << std::endl;
    }
    MYSQL_RES *result = mysql_store_result(mysql);
    if (result == NULL)
    {
        std::cerr << "[ERR] mysql store result error: " << mysql_error(mysql) << std::endl;
        return;
    }

    int num_rows = mysql_num_rows(result);
    for (int i = 0; i < num_rows; i++)
    {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row == NULL)
        {
            std::cerr << "[ERR] mysql fetch row error: " << mysql_error(mysql) << std::endl;
            break;
        }
        friendid.push_back(atoi(row[0]));
        std::cout << "friend: " << friendid[i] << std::endl;
        //    sq_statusFriend(atoi(row[0]));
    }

    mysql_free_result(result);
    for (int i = 0; i < friendid.size(); i++)
    {
        sq_statusFriend(friendid[i]);
    }
    msg_back.state = OP_OK;
    send_data(msg_back, sockfd);
    return;
}
void Person::privateChat() // 私聊
{
    std::cout << "privateChat" << std::endl;
    int flag = 1;
    struct protocol msg_back1, msg_back2;
    msg_back1.cmd = PRIVATECHAT;

    if (checkUserExists())
    {
        if (isMyself())
        {
            msg_back1.state = MYSELF; // 是自己
        }
        else if (isFriend())
        {
            sq_restoreFriend();
            if (checkUserOnline())
            {
                msg_back1.state = OP_OK; // 对方在线
                msg_back2.state = YNCHAT;
                msg_back2.id = findId(); // 发送者id
                std::cout << findCfd() << std::endl;
                std::cout << "这的问题" << msg_back2.id << std::endl; // 发送者id
                msg_back2.data = msg.data;
                send_data(msg_back2, findCfd());
                std::cout << "你别认输阿！" << std::endl;
                flag = 0;
            }
            else
                msg_back1.state = FRIEND_OFFLINE; // 对方不在线
        }
        else
        {
            msg_back1.state = NOTFRIEND; // 不是好友
        }
    }
    else
    {
        msg_back1.state = USER_NOT_REGIST;
        std::cout << "user not regist" << std::endl;
    }
    if (flag)
    {

        send_data(msg_back1, sockfd); // 发送消息
        std::cout << "别放弃！" << std::endl;
    }
}
void Person::unblockFriend() // 取消屏蔽好友
{
    struct protocol msg_back;
    msg_back.cmd = UNBLOCKFRIEND;

    if (checkUserExists())
    {
        if (isMyself())
        {
            msg_back.state = MYSELF; // 是自己
        }
        else if (isFriend())
        {
            if (sq_isBlocked())
            {
                sq_unblockFriend();
                msg_back.state = OP_OK; // 解除屏蔽好友成功
            }
            else
            {
                msg_back.state = ISUNBLOCKED; // 已经屏蔽该好友没有屏蔽该好友
            }
        }
        else
        {
            msg_back.state = NOTFRIEND; // 不是好友
        }
    }
    else
    {
        msg_back.state = USER_NOT_REGIST;
    }
    send_data(msg_back, sockfd);
}
int Person::friendNotice()// 好友通知
{
     int id=findId();
     struct protocol msg_back;
     char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select inid,message from datamessage where (toid = '%d' and status ='%d');", id, 0);
    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql select error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    MYSQL_RES *result = mysql_store_result(mysql);
    if (result == NULL)
    {
        std::cerr << "[ERR] mysql store result error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    int num_rows = mysql_num_rows(result);
    for (int i = 0; i < num_rows; i++)
    {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row == NULL)
        {
            std::cerr << "[ERR] mysql fetch row error: " << mysql_error(mysql) << std::endl;
            break;
        }
        std::cout << atoi(row[0]) << ":" << row[1] << std::endl;
        msg_back.id=atoi(row[0]);
        msg_back.data=row[1];
        send_data(msg_back, sockfd);
        std::cout<<"hahaha"<<std::endl;
    }
        msg_back.state=OP_OK;
        send_data(msg_back, sockfd);
    mysql_free_result(result);
    return 0;
}
void Person::createGroup() // 创建群聊
{
    struct protocol msg_back;
    msg_back.cmd = CREATEGROUP;
    if (!checkGroup())
    {
        msg_back.state = OP_OK;
        char sql_cmd[256];
        std::cout << msg.name << std::endl;
        std::cout << sockfd << std::endl;
        snprintf(sql_cmd, sizeof(sql_cmd), "insert into groupdata(name,userid,type) values('%s','%d','%d');",
                 msg.name.c_str(), findId(), 1);

        int ret = mysql_query(mysql, sql_cmd);
        if (ret != 0)
        {
            std::cerr << "[ERR] mysql insert error: " << mysql_error(mysql) << std::endl;
        }
    }
    // 发给客户端
    send_data(msg_back, sockfd);
    return;
}
int Person::checkGroup() // 群是否存
{
    std::cout << "checkGroup" << std::endl;
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select * from groupdata where name='%s';", msg.name.c_str());

    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql query error: " << mysql_error(mysql) << std::endl;
        return 0;
    }
    MYSQL_RES *result = mysql_store_result(mysql);
    if (result == NULL) // 这个只是收集结果，还需判断是否有行
    {
        std::cerr << "[ERR] mysql store result error: " << mysql_error(mysql) << std::endl;
    }
    if (mysql_num_rows(result) == 0)
    {
        mysql_free_result(result); // 释放结果集占用的内存
        return 0;                  // 没有找到群组
    }

    mysql_free_result(result); // 释放结果集占用的内存
    return 1;                  // 找到群组
}
int Person::groupynMe(int id) // 群中是否有我
{
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select type from groupdata where (userid='%d' and name='%s');", id, msg.name.c_str());
    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql select error: " << mysql_error(mysql) << std::endl;
    }
    MYSQL_RES *result = mysql_store_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != NULL)
    {
        return atoi(row[0]);
    }
    return 0;
}
void Person::deleteGroup() // 退出/ 删除群聊//群是否存在,群里是否不存在这个人，是否是群主
{
    std::cout << findId() << std::endl;

    std::cout << msg.name.c_str() << std::endl;
    struct protocol msg_back;
    msg_back.cmd = DELETEGROUP;
    if (checkGroup())
    {
        if (groupynMe(findId()))
        {
            msg_back.state = OP_OK;
            if (groupynMe(findId()) == 1) // 是群主，将群一删
            {
                msg_back.cmd = LENDER;
                char sql_cmd[256];
                snprintf(sql_cmd, sizeof(sql_cmd), "delete from groupdata where name='%s';", msg.name.c_str());
                int ret = mysql_query(mysql, sql_cmd);
                if (ret != 0)
                {
                    std::cerr << "[ERR] mysql delete error: " << mysql_error(mysql) << std::endl;
                }
            }
            else // 不是群主，自己退出
            {
                msg_back.cmd = ORDINARY;
                char sql_cmd1[256];
                snprintf(sql_cmd1, sizeof(sql_cmd1), "delete from groupdata where (userid='%d' and name='%s');", findId(), msg.name.c_str());

                int ret = mysql_query(mysql, sql_cmd1);
                if (ret != 0)
                {
                    std::cerr << "[ERR] MySQL delete error: " << mysql_error(mysql) << std::endl;
                }
            }
        }
        else
        {
            msg_back.state = GROUPNOTPERSON;
        }
    }
    else
    {
        msg_back.state = GROUP_NOT_EXIST;
    }
    send_data(msg_back, sockfd);
}
void Person::removeUser() // 先看群是否存在，你和要删除的人是否在群里面，删除群成员,群主可删除所有，管理员不能删除管理员，管理员可以删除普通成员,普通员工不可以删除任何人
{
    struct protocol msg_back;
    msg_back.cmd = REMOVEUSER;
    if (checkGroup())
    {
        std::cout << findId() << std::endl;
        std::cout << msg.id << std::endl;
        if (groupynMe(findId()) && groupynMe(msg.id)) // 自己和要删除的人都存在
        {
            std::cout << groupynMe(findId()) << std::endl;
            std::cout << groupynMe(msg.id) << std::endl;
            if (groupynMe(findId()) < groupynMe(msg.id)) // 自己权限大于要删除的人
            {
                msg_back.state = OP_OK;
                char sql_cmd[256];
                snprintf(sql_cmd, sizeof(sql_cmd), "delete from groupdata where (userid='%d' and name='%s');", msg.id, msg.name.c_str());
                int ret = mysql_query(mysql, sql_cmd);
                if (ret != 0)
                {
                    std::cerr << "[ERR] MySQL delete error: " << mysql_error(mysql) << std::endl;
                }
            }
            else
            {
                msg_back.state = NOTRIGHT;
            }
        }
        else if (groupynMe(findId()) == 0) // 你不再群里面
        {
            msg_back.state = GROUPNOTPERSON;
        }
        else if (groupynMe(msg.id) == 0) // 要删除的人不在群里面
        {
            msg_back.state = GROUPNOTPERSON1;
        }
    }
    else
    {
        msg_back.state = GROUP_NOT_EXIST;
    }
    send_data(msg_back, sockfd);
}
void Person::sq_groupList()
{
    struct protocol msg_back1;
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select userid,type from groupdata where name='%s';", msg.name.c_str());
    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql select error: " << mysql_error(mysql) << std::endl;
    }
    MYSQL_RES *result = mysql_store_result(mysql);
    if (result == NULL)
    {
        std::cerr << "[ERR] mysql store result error: " << mysql_error(mysql) << std::endl;
        return;
    }

    int num_rows = mysql_num_rows(result);
    for (int i = 0; i < num_rows; i++)
    {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row == NULL)
        {
            std::cerr << "[ERR] mysql fetch row error: " << mysql_error(mysql) << std::endl;
            break;
        }
        std::cout << "userid" << row[0] << "    " << "usertype" << row[1] << std::endl;
        msg_back1.id = atoi(row[0]);
        msg_back1.cmd = atoi(row[1]);
        msg_back1.state = GROUPLIST_OK;
        send_data(msg_back1, sockfd);
        std::cout << "userid" << row[0] << "    " << "usertype" << row[1] << std::endl;
    }

    mysql_free_result(result);
    return;
}
void Person::groupList() // 查看群成员,先看有没有这个群，然后再看你是不是群成员
{
    struct protocol msg_back;
    msg_back.cmd = GROUPLIST;
    if (checkGroup())
    {
        if (groupynMe(findId())) // 你在群里面
        {
            sq_groupList();
            msg_back.state = OP_OK;
        }
        else
        {
            msg_back.state = GROUPNOTPERSON;
        }
    }
    else
    {
        msg_back.state = GROUP_NOT_EXIST;
    }
    send_data(msg_back, sockfd);
}
void Person::iinGroup()
{
    struct protocol msg_back;
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select name from groupdata where userid='%d';", msg.id);
    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql select error: " << mysql_error(mysql) << std::endl;
    }
    MYSQL_RES *result = mysql_store_result(mysql);
    if (result == NULL)
    {
        std::cerr << "[ERR] mysql store result error: " << mysql_error(mysql) << std::endl;
        return;
    }

    int num_rows = mysql_num_rows(result);
    // if (num_rows == 0)
    // {
    //     msg_back.state = NOGROUP;
    // }
    for (int i = 0; i < num_rows; i++)
    {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row == NULL)
        {
            std::cerr << "[ERR] mysql fetch row error: " << mysql_error(mysql) << std::endl;
            break;
        }
        std::cout << "name" << row[0] << std::endl;
        msg_back.state = IINGROUP_OK;
        msg_back.name = row[0];
        send_data(msg_back, sockfd);
    }
    msg_back.state = OP_OK;
    send_data(msg_back, sockfd);
    mysql_free_result(result);
}
void Person::sq_adManager()
{
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "update groupdata set type='%d' where userid='%d' and name='%s';", msg.state, msg.id, msg.name.c_str());
    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql update error: " << mysql_error(mysql) << std::endl;
    }
    return;
}
void Person::adManager() // 这个群是否存在，你和他是否在里面，你是否是群主，你要加，他是否已经是管理员，你要删除，他是否已经不是管理员
{
    struct protocol msg_back;
    msg_back.cmd = ADMANAGER;
    if (checkGroup())
    {
        if (groupynMe(findId())) // 你在群里面
        {
            if (groupynMe(findId()) == 1) // 你是群主
            {
                if (groupynMe(msg.id)) // 你要加的人是群成员
                {
                    if (msg.state == 2) // 你要加
                    {
                        if (groupynMe(msg.id) == 3) // 你要加的人不是管理员
                        {
                            sq_adManager();
                            msg_back.state = OP_OK;
                        }
                        else
                        {
                            msg_back.state = ISMANAGER;
                        }
                    }
                    if (msg.state == 3) // 你要删除
                    {
                        if (groupynMe(msg.id) == 2) // 你要删除的人是管理员
                        {
                            sq_adManager();
                            msg_back.state = OP_OK;
                        }
                        else
                        {
                            msg_back.state = NOTMANAGER;
                        }
                    }
                }
                else
                {
                    msg_back.state = GROUPNOTPERSON1;
                }
            }
            else
            {
                msg_back.state = ISNOTLENDER;
            }
        }
        else
        {
            msg_back.state = GROUPNOTPERSON;
        }
    }
    else
    {
        msg_back.state = GROUP_NOT_EXIST;
    }
    send_data(msg_back, sockfd);
}
int Person::sq_applyaddGroup()
{
    int id=findId();
    std::cout<<findId()<<std::endl;
    struct protocol msgback;
    // 先判断是否已经发送过请求了
    char sql_cmd[256];
    snprintf(sql_cmd, sizeof(sql_cmd), "select * from groupmessage where inid='%d' and name='%s';", id, msg.name.c_str());
    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql select error: " << mysql_error(mysql) << std::endl;
        return -1;
    }
    MYSQL_RES *res = mysql_store_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row != NULL)
    {
        msgback.data = "已经发过请求了,等待对方验证";
        msgback.state = NOCONTINUE;
        send_data(msgback, sockfd);
        return 0;
    }
     std::cout<<findId()<<std::endl;
    // 现在将请求存到数据库中
    char sql_cmd1[256];
    snprintf(sql_cmd1, sizeof(sql_cmd1), "insert into groupmessage (inid, name, message, status) values('%d','%s','%s','%d');", id, msg.name.c_str(), msg.data.c_str(), 0);
    ret = mysql_query(mysql, sql_cmd1);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql insert error: " << mysql_error(mysql) << std::endl;
        return -1;
    }
    else
    {
          printf("[%d]对[%s]请求存入数据库\n", id, msg.name.c_str());
    }
    return 0;
}
void Person::applyaddGroup() // 申请加群//群是否存在，你是否已经在群里面了
{
    // status=0表示发的请求，1表示同意，2表示拒绝，3表示信息
    std::cout<<findId()<<std::endl;
    struct protocol msg_back;
    msg_back.cmd = APPLYADDGROUP;
    if (checkGroup())
    {
        if (!groupynMe(findId())) // 你不在群里面
        {
            sq_applyaddGroup();
            msg_back.state = OP_OK;
        }
        else
        {
            msg_back.state = ISINGROUP;
        }
    }
    else
    {
        msg_back.state = GROUP_NOT_EXIST;
    }
    send_data(msg_back, sockfd);
}
int Person::ynacceptGroup()
{
    struct protocol msg_back;
    if (msg.data == "Y")
    {
        char sql_cmd[256];
        std::cout << msg.id << std::endl; // msg.id是发送请求的人的id
        msg_back.id=findId();//同意的那个人的id
        msg_back.name = msg.name;
        snprintf(sql_cmd, sizeof(sql_cmd), "update groupmessage set status=%d where(inid='%d' and name='%s' and status='%d');", 1, msg.id, msg.name.c_str(), 0); // 同意此人加入群聊
        int ret = mysql_query(mysql, sql_cmd);
        if (ret != 0)
        {
            std::cerr << "[ERR] mysql update error: " << mysql_error(mysql) << std::endl;
            return false;
        }

        char sql_cmd1[256];
        std::cout <<"haha"<< msg.id << std::endl; 
        snprintf(sql_cmd1, sizeof(sql_cmd1), "insert into groupdata(name,userid,type) values('%s','%d','%d');", msg.name.c_str(), msg.id,3); // 将此人加入群聊
        ret = mysql_query(mysql, sql_cmd1);
        if (ret != 0)
        {
            std::cerr << "[ERR] mysql insert error: " << mysql_error(mysql) << std::endl;
            return false;
        }
        msg_back.state = AGREEGROUP;
    }
    else
    {
        char sql_cmd2[256];
        snprintf(sql_cmd2, sizeof(sql_cmd2), "update datamessage set status=%d where(inid='%d' and name='%s' and status='%d');", 2, msg.id,msg.name.c_str(), 0); // 拒绝好友请求
        int ret = mysql_query(mysql, sql_cmd2);
        if (ret != 0)
        {
            std::cerr << "[ERR] mysql updata error: " << mysql_error(mysql) << std::endl;
            return false;
        }
        msg_back.state = REFUSEGROUP;
    }
    send_data(msg_back, findCfd());
    return 0;
}
int  Person::groupNotice()
{
    int id=findId();
    std::cout<<id<<std::endl;
    char sql_cmd[256];
    struct protocol msg_back;
    snprintf(sql_cmd, sizeof(sql_cmd), "select inid,message,name from groupmessage where  status ='%d';", 0); // 找到所有status=0的
    int ret = mysql_query(mysql, sql_cmd);
    if (ret != 0)
    {
        std::cerr << "[ERR] mysql select error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    MYSQL_RES *result = mysql_store_result(mysql);
    if (result == NULL)
    {
        std::cerr << "[ERR] mysql store result error: " << mysql_error(mysql) << std::endl;
        return -1; // Error indicator
    }
    int num_rows = mysql_num_rows(result);
    std::cout << "num_rows: " << num_rows << std::endl;
    for (int i = 0; i < num_rows; i++)
    {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row == NULL)
        {
            std::cerr << "[ERR] mysql fetch row error: " << mysql_error(mysql) << std::endl;
            return -1; // Error indicator
        }
        char sql_cmd1[256];
        snprintf(sql_cmd1, sizeof(sql_cmd1), "select *from groupdata where  (name ='%s' and userid='%d' and type='%d') or (name ='%s' and userid='%d' and type='%d');", row[2], id, 1, row[2], id, 2); // 找到该群中该用户是否为管理员或群主
        int ret1 = mysql_query(mysql, sql_cmd1);
        if (ret1 != 0)
        {
            std::cerr << "[ERR] mysql select error: " << mysql_error(mysql) << std::endl;
            return -1;
        }
        MYSQL_RES *result1 = mysql_store_result(mysql);
        if (result1 == NULL)
        {
            std::cerr << "[ERR] mysql store result error: " << mysql_error(mysql) << std::endl;
            return -1;
        }
        int num_rows1 = mysql_num_rows(result1); // 没在这个群中或者不是管理员或群主
        if (num_rows1 == 0)
        {

            continue;
        }
        else
        {
            msg_back.id = atoi(row[0]);
            msg_back.data = row[1];
            msg_back.name = row[2]; // 群名
        }
    }
    msg_back.state = OP_OK;
    send_data(msg_back, findCfd());
    return 0;
}

#include "json.h"
#include <iostream>
#include "json.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "chat.h"
using json = nlohmann::json;
//自己写的
// void send_data(protocol &p, int sockfd)
// {
//   json json_obj;
//   json_obj["cmd"] = p.cmd;
//   json_obj["name"] = p.name;
//   json_obj["data"] = p.data;
//   json_obj["id"] = p.id;
//   json_obj["state"] = p.state;
//   std::string s = json_obj.dump();
//   std::cout << "发送的 " << s << std::endl;
//   send(sockfd, s.c_str(), s.length(), 0);
//   return;
// }

// protocol receive_data(int &sockfd)
// {
//   char ch[1024];
//   std::memset(ch, 0, sizeof(ch)); // 清空缓冲区
//   protocol p;
//   int len = recv(sockfd, ch, sizeof(ch), 0);
//   if (len <= 0)
//   {
//     p.state = OFFLINE;
//     return p;
//   }
//   std::string str(ch, len);
//   std::cout << "收到的 " << str << std::endl;
//   json json_obj = json::parse(str);
//   std::cout << "收到的" << json_obj << std::endl;
//   p.cmd = json_obj["cmd"].get<int>();
//   p.name = json_obj["name"].get<std::string>();
//   p.data = json_obj["data"].get<std::string>();
//   p.id = json_obj["id"].get<int>();
//   p.state = json_obj["state"].get<int>();
//   return p;
// }
//改的
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <nlohmann/json.hpp>

struct MessageHeader
{
    int length; // 消息体的长度
};

void send_data(protocol &p, int sockfd)
{
    json json_obj;
    json_obj["cmd"] = p.cmd;
    json_obj["name"] = p.name;
    json_obj["data"] = p.data;
    json_obj["id"] = p.id;
    json_obj["state"] = p.state;
    std::string message_body = json_obj.dump();

  //  std::cout << "发送的 " << message_body << std::endl; // 打印即将发送的 JSON 字符串

    MessageHeader header;
    header.length = message_body.length();

    // 发送消息头
    send(sockfd, reinterpret_cast<const char *>(&header), sizeof(header), 0);

    // 发送消息体
    send(sockfd, message_body.c_str(), message_body.length(), 0);
     std::cout << "发送的 " << message_body << std::endl; // 打印即将发送的 JSON 字符串
}

protocol receive_data(int &sockfd)
{
    MessageHeader header;
    protocol p;
    std::cout << "22222 "<< std::endl;
    int header_len = recv(sockfd, reinterpret_cast<char *>(&header), sizeof(header), 0);
     std::cout << "11111 "<< std::endl;
    if (header_len <= 0)
    {
        p.state = OFFLINE;
        return p;
    }

    // 根据消息头中的长度接收消息体
    std::vector<char> message_body(header.length + 1); // 使用vector避免栈溢出
    int total_body_len = 0;
    while (total_body_len < header.length)
    {
        int body_len = recv(sockfd, message_body.data() + total_body_len, header.length - total_body_len, 0);
        if (body_len <= 0)
        {
            p.state = OFFLINE;
            return p;
        }
        total_body_len += body_len;
    }
    message_body[header.length] = '\0'; // 确保字符串正确结束

    std::string str(message_body.data());
    std::cout << "收到的 " << str << std::endl;
    try
    {
        json json_obj = json::parse(str);
        p.cmd = json_obj["cmd"].get<int>();
        p.name = json_obj["name"].get<std::string>();
        p.data = json_obj["data"].get<std::string>();
        p.id = json_obj["id"].get<int>();
        p.state = json_obj["state"].get<int>();
        return p;
    }
        catch (json::parse_error &e)
    {
        // 处理解析错误
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        p.state = -1; // 设置错误状态
        return p;
    }
}
//加油！！！
// struct MessageHeader {
//     int length; // 消息体的长度
// };
// void send_data(protocol &p, int sockfd)
// {
//     json json_obj;
//     json_obj["cmd"] = p.cmd;
//     json_obj["name"] = p.name;
//     json_obj["data"] = p.data;
//     json_obj["id"] = p.id;
//     json_obj["state"] = p.state;
//     std::string message_body = json_obj.dump();

//     MessageHeader header;
//     header.length = message_body.length();

//     // 构建完整的消息字符串（消息头 + 消息体）
//     std::string full_message = std::to_string(header.length) + "|" + message_body;
//     std::cout<<"发送的 " << full_message << std::endl;
//     // 发送完整的消息字符串
//     send(sockfd, full_message.c_str(), full_message.length(), 0);
// }
// protocol receive_data(int &sockfd)
// {
//     std::cout << "开始接收数据" << std::endl;
//     MessageHeader header;
//     protocol p;
//     int header_len = recv(sockfd, reinterpret_cast<char *>(&header), sizeof(header), 0);
//     if (header_len <= 0)
//     {
//         p.state = OFFLINE;
//         return p;
//     }

//     // 根据消息头中的长度接收消息体
//     std::string message_body(header.length + 1, '0'); // 使用string避免栈溢出
//     int total_body_len = 0;
//     while (total_body_len < header.length)
//     {
//         int body_len = recv(sockfd, message_body.data() + total_body_len, header.length - total_body_len, 0);
//         if (body_len <= 0)
//         {
//             p.state = OFFLINE;
//             return p;
//         }
//         total_body_len += body_len;
//     }
//     message_body[header.length] = '\0'; // 确保字符串正确结束

//     std::string str(message_body.data());
//     std::cout << "收到的 " << str << std::endl;
//     try
//     {
//         json json_obj = json::parse(str);
//         p.cmd = json_obj["cmd"].get<int>();
//         p.name = json_obj["name"].get<std::string>();
//         p.data = json_obj["data"].get<std::string>();
//         p.id = json_obj["id"].get<int>();
//         p.state = json_obj["state"].get<int>();
//         return p;
//     }
//     catch (json::parse_error &e)
//     {
//         // 处理解析错误
//         std::cerr << "JSON parse error: " << e.what() << std::endl;
//         p.state = -1; // 设置错误状态
//         return p;
//     }
// }

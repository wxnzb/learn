#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // 创建socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);//创建了一个基于ipv4地址族和tcp协议的socket套字节
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    // 绑定
    struct sockaddr_in server_addr;//存储服务器地址信息
    server_addr.sin_family = AF_INET;//地址族
    server_addr.sin_addr.s_addr = INADDR_ANY;//可以监视所有的网络接口（ip地址）
    server_addr.sin_port = htons(8080);//端口号
    
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding");
        exit(EXIT_FAILURE);
    }
    
    // 监听
    if (listen(server_socket, 5) == -1) {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }
    
    // 接受客户端连接
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket == -1) {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }
    
    // 接收客户端数据
    char buffer[1024];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    }
    
    // 将数据打印出来%s\n", buffer);
    
    printf("Received data from client: ");
    close(client_socket);
    close(server_socket);
    
    return 0;
}

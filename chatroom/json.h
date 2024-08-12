#include <iostream>
//#include "json.hpp"
#include <nlohmann/json.hpp>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "chat.h"
using json = nlohmann::json;
void send_data(protocol &p, int sockfd);
protocol receive_data(int &sockfd);
//
//  kbcServer.cpp
//  screenshot
//
//  Created by 7070m on 2020/5/11.
//  Copyright © 2020 7070m. All rights reserved.
//

#include "kbcServer.hpp"
#include <sys/unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string>

using namespace std;

void
client() {
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    // 要连接服务器 ip 和 端口
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = 0x00000000;
    serverAddress.sin_port = 0xBEAF;
    
    //客户端直接连接服务器， 无需其他设置
    connect(socketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    
    //
    string data = "KuaiBianCheng.com";
    send(socketFd, data.c_str(), data.length(), 0);
    
}

int
main() {
    client();
    
    return 0;
}

// 编译方法 c++ mac  clang++  *.cpp

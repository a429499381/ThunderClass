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

void
server() {
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    // ip 和 端口
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = 0x00000000;
    serverAddress.sin_port = 0xBEAF;
    
    // 想 os 申请  端口
    bind(socketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    // 第二个参数无脑写 6， 不要关心
    listen(socketFd, 6);
    
    
    struct sockaddr_in clientAddress;
    socklen_t len = sizeof(clientAddress);
    int connection = accept(socketFd, (struct sockaddr *)&clientAddress, &len);
    
    // 执行到这里，说明已经创建了连接， 可以直接读取客户端发过来数据
    const int size = 100;
    char data[100];
    recv(connection, data, size, 0);
    printf("rect: (%s)\n", data);
    
}

int
main() {
   //server();
    
    return 0;
}

// 编译方法 c++ mac  clang++  *.cpp

/*
    颜色的表示
    每个像素 4 字节
    包含 r g b a
    10 * 10 = 100
    400 字节
*/

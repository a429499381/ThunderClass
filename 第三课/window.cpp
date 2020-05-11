#include <iostream>

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>

using namespace std;

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
    server();
    
    return 0;
}

// 编译方法 c++ mac  clang++  *.cpp

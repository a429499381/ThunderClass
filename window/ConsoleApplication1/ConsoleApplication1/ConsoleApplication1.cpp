// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
#include <iostream>

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

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
    bind(socketFd, (struct sockaddr*) & serverAddress, sizeof(serverAddress));
    // 第二个参数无脑写 6， 不要关心
    listen(socketFd, 6);


    struct sockaddr_in clientAddress;
    socklen_t len = sizeof(clientAddress);
    int connection = accept(socketFd, (struct sockaddr*) & clientAddress, &len);

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

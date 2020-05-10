#include "kbcClient.h"
#include "kbcSocket.h"

#include "utils.h"


void
client() {
#ifndef __APPLE__
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    int socketId = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = 0x0100007F;
    serverAddress.sin_port = 0xBEAF;

    // 这个程序功能是连接服务器然后给服务器发一个长度 18 的字符串
    connect(socketId, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    // data 有 17 个字符，末尾还有一个看不到的 0 表示字符串结尾
    // 所以 size 要加上这个 0 发出去
    const char *data = "KuaiBianCheng.com";
    size_t size = strlen(data) + 1;
    int n = send(socketId, data, size, 0);
    log("send size ", n);
}

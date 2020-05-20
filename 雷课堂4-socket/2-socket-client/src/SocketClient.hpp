//
//  SocketClient.hpp
//  2-socket-client
//
//  Created by 7070m on 2020/5/20.
//  Copyright © 2020 kuaibiancheng.com. All rights reserved.
//

#ifndef SocketClient_hpp
#define SocketClient_hpp

#include "utils.h"

#ifdef __APPLE__
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netinet/tcp.h>
#else
    #include <tchar.h>
    #include <winsock2.h>
    #include <windows.h>
    #include <WS2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")
#endif


#endif /* SocketClient_hpp */


class SockentClient {
public:
    void
    client(const char *data) {
//        log("data", data);
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

        size_t size = strlen(data) + 1;
        int n = send(socketId, data, size, 0);
        log("send size ", n);
    }
};

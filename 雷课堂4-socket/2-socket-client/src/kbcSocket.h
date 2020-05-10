//
//  kbcNetwork.h
//  socket1
//
//  Created by gua on 2020/04/28.
//  Copyright © 2020 kuaibiancheng.com. All rights reserved.
//

#ifndef kbcSocket_h
#define kbcSocket_h


#ifdef __APPLE__
    #include <sys/socket.h>
    #include <arpa/inet.h>
#else
    #include <tchar.h>
    #include <winsock2.h>
    #include <windows.h>
    #include <WS2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")
#endif


#endif

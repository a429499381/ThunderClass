#include "kbcServer.h"
#include "kbcSocket.h"

#include "utils.h"


void
server() {
#ifndef __APPLE__
	// windows socket 套路
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	int socketId = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	// ip 0.0.0.0 表示接受任意连接
	// 因为一台电脑可以有多个网卡多个 ip
	serverAddress.sin_addr.s_addr = 0x00000000;
	// 端口 0xBEAF 实际表示的是 0xAFBE 也就是 44990
	// 这是因为我们用的 CPU 通常用 小端字节序
	// 网络传输用 大端字节序
	// 不重要，感兴趣可以自行搜索
	serverAddress.sin_port = 0xBEAF;
	// BEEF 是一个单词，但是看着眼花
	// BEAF 不是一个单词，但是方便看
	// 代码是代码，切莫 “英编”

	/*
	 根据上面的信息，如果我们要表示 192.168.100.1 这个 IP
	 应该用下面的方式
	 0x0164A8C0
	 由于这样的计算比较麻烦，我们可以用下面的位运算来直观实现
	 (192 << 0) + (168 << 8) + (100 << 16) + (1 << 24)
	 */

	bind(socketId, (struct sockaddr*) & serverAddress, sizeof(serverAddress));
	// 上课讲了，第二个参数可直接填 6，暂且当作规定即可
	listen(socketId, 6);
	// 用无限循环来处理客户端的连接请求
	while (true) {
		log("accept \n");
		// 等待客户端的连接
		struct sockaddr_in clientAddress;
		socklen_t len = sizeof(clientAddress);
		// accept 会停在这里等待客户端连接上了再返回
		int connection = accept(socketId, (struct sockaddr*) & clientAddress, &len);

		// 在这个示例服务器程序中，我们对每个连接只接受最多 100 个字节的数据
		// 然后就不管这个连接了
		const int size = 100;
		// 用 new 申请 size 字节的内存
		char* buff = new char[size];
		size_t n = recv(connection, buff, size, 0);
		log("recv size: ", n, "data: ", buff);
		// delete [] 释放刚才的申请的内存
		delete[] buff;
	}
}

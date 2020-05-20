#include "SocketClient.hpp"

int 
main() {
    SockentClient *S1 = new SockentClient();
    const char *data = "KuaiBianCheng.com";
  
    S1->client(data);
}

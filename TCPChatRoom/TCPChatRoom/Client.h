#pragma once
#include"TCPChatroom.h"

class Client:public TCPChatRoom {
public:
    Client(const string &);
    void startClient();
    void split(char*, const char*);
private:
    SOCKADDR_IN addr;
    string confirm;
    char message[2000];
    int r;
    WSAData wsaData;
    WORD DLLVersion;
    int addlen = sizeof(addr);
};

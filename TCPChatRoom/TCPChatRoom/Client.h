#pragma once
#include"TCPChatroom.h"
class Client:public TCPChatRoom {
    friend class UI;
public:
    Client(const string &);
    void startClient(const string &);
    void setUserName(const string &);
    
    void sendUserName();
    void recvOnlineUserList();
    void split(char*, const char*);
private:
    SOCKADDR_IN addr;
    string confirm;
    char message[2000];
    int r;
    WSAData wsaData;
    WORD DLLVersion;
    int addlen = sizeof(addr);
    string userName;
    char *onlineUser;
};

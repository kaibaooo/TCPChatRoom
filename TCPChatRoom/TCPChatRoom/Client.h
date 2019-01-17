#pragma once
#include"TCPChatroom.h"
#include"Instruction.h"
#include"Personality.h"
class Client:public TCPChatRoom,public Instruction,public Personality {
public:
    Client(const string &);
	virtual void start(const string &) ;
    //void startClient(const string &);
    void setUserName(const string &);
    void sendUserName();
    void recvOnlineUserList();
    void split(char*, const char*);
private:
    SOCKADDR_IN addr;
    //string confirm;
    char message[2000];
    int r;
    WSAData wsaData;
    WORD DLLVersion;
    int addlen = sizeof(addr);
    string userName;
    char *onlineUser;
};

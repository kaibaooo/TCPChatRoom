#pragma once
#include"TCPChatroom.h"
#include<map>
class Server:public TCPChatRoom{
public:
    Server(const string &chatroomName);
    void startServer();

protected:
    vector<pair<string, string>> msgs; //destname,msgs
    //vector<pair<string, string>> onlineUser;//ip+port,username
    //vector<pair<string, string>>::iterator iter;
    map<string, string> onlineUser;
    map<string, string>::iterator iter;
    string userNameList;//¦^¶Çµ¹clinet
private:
    char serverIP[20];
    int serverPort;
    int r;
    WSAData wsaData;
    WORD DLLVSERION;
    SOCKADDR_IN addr;
    int addrlen = sizeof(addr);
    SOCKET sListen;
    SOCKET sConnect;
    SOCKADDR_IN clinetAddr;
};

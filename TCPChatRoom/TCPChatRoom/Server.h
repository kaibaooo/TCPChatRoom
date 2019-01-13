#pragma once
#include"TCPChatroom.h"
#include<map>
class Server:public TCPChatRoom{

public:
    Server(const string &chatroomName);
    void startServer();
	void addNewUser(char*);
	void recvMsg(char*);
    
protected:
    vector<string> msgs; //sourcename,msgs
    //vector<pair<string, string>> onlineUser;//ip+port,username
    vector<pair<string, string>>::iterator iter2;
    map<string, string> onlineUser;
    map<string, string>::iterator iter;
    vector<string>::iterator iterMsgs;
    string userNameList;//�^또돌clinet
	string allChatList;//�^또돌clinet
private:
    char serverIP[20];
    int serverPort;
    int r;
	int msgsNum;
    WSAData wsaData;
    WORD DLLVSERION;
    SOCKADDR_IN addr;
    int addrlen = sizeof(addr);
    SOCKET sListen;
    SOCKET sConnect;
    SOCKADDR_IN clinetAddr;
};

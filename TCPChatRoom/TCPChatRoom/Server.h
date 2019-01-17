#pragma once
#include"TCPChatroom.h"
#include<map>
class Server:public TCPChatRoom{

public:
    Server(const string &chatroomName);
    void startServer();
	void addNewUser(char*);
	void recvMsg(char*);
	void recvPrivateMsg(char*);
    void sendPrivateMsg(char*);
	void recvUserStatus(char*);
	void sendUserStatus();
	void deletUser(char*);
	
    void sendUserList();
    struct privateMsg {
        char *sender;
        char *recver;
        char *msg;
    };
protected:
    vector<string> msgs; //sourcename,msgs
	vector<string> privateMsgs;
    //vector<privateMsg> priMsgs;
    //vector<pair<string, string>> onlineUser;//ip+port,username
    vector<pair<string, string>>::iterator iter2;
	vector<pair<string, string>> userStatus;
    map<string, string> onlineUser;
    map<string, string>::iterator iter;
	vector<pair<string, string>>::iterator iterStatus;
    vector<string>::iterator iterMsgs;
    string userNameList;//�^또돌client
	string allChatList;//�^또돌client
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

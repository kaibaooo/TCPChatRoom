#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <iostream>
#include<utility>
#include<vector>
#include<string>

#pragma warning(disable:4996)
using namespace std;
class TCPChatRoom {
public:
    TCPChatRoom(const string&);
    void setRoomName(const string&);
    string getRoomName();
    virtual void start(const string &)=0;
private:
    string roomName;
};


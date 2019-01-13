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
    friend class UI;
public:
    TCPChatRoom(const string&);
    void setRoomName(const string&);
    string getRoomName();
private:
    string roomName;
};


#include"TCPChatroom.h"
#include"Client.h"
#include"Server.h"
int main() {
    int executeType = 0;
    cout << "which excuting type do you want[1]Server [2]Client : ";
    cin >> executeType;
    if (executeType == 1) {
        TCPChatRoom *TCPserver;
        Server server("NUK_CSIE_OOP_PROJ");
        TCPserver = &server;
        cout << "Welcome to " << server.getRoomName() << " server" << endl;
		TCPserver->start("demo");
    }
    else {
        TCPChatRoom *TCPclient;
        Client client("NUK_CSIE_OOP_PROJ");
        TCPclient = &client;
        string usrName;
        cout << "Welcome to " << client.getRoomName() <<" client"<< endl;
        cout << "Please Input Your ID : " << endl;
        cin >> usrName;
        getchar();
		TCPclient->start(usrName);
    }

    return 0;
}
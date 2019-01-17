#include"TCPChatroom.h"
#include"Client.h"
#include"Server.h"
int main() {
    int executeType = 0;
    cout << "which excuting type do you want[1]Server [2]Client : ";
    cin >> executeType;
    if (executeType == 1) {
        Server server("NUK_CSIE_OOP_PROJ");
        cout << "Welcome to " << server.getRoomName() << " server" << endl;
        server.startServer();
    }
    else {
        Client client("NUK_CSIE_OOP_PROJ");
        string usrName;
        cout << "Welcome to " << client.getRoomName() <<" client"<< endl;
        cout << "Please Input Your ID : " << endl;
        cin >> usrName;
        getchar();
        client.startClient(usrName);
    }

    return 0;
}
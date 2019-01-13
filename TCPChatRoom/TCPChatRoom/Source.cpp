#include"TCPChatroom.h"
#include"Client.h"
#include"Server.h"
int main() {
    int executeType = 0;
    cout << "which excuting type do you want[1]Server [2]Client : ";
    cin >> executeType;
    if (executeType == 1) {
        Server server("discord");
        cout << "Welcome to " << server.getRoomName() << " server" << endl;
        server.startServer();
    }
    else {
        Client client("discord");
        cout << "Welcome to " << client.getRoomName() <<" client"<< endl;
        client.startClient();
    }

    return 0;
}
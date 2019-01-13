#include"Server.h"
#include<map>

Server::Server(const string &serverName)
:TCPChatRoom(serverName){
    int r;
    DLLVSERION = MAKEWORD(2, 1);
    r = WSAStartup(DLLVSERION, &wsaData);
    sConnect = socket(AF_INET, SOCK_STREAM, NULL);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(15501);
    sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);
}
void Server::startServer() {
    while (true) {
        char message[200];
        char userNameinput[200];
        cout << "waiting..." << endl;
        if (sConnect = accept(sListen, (SOCKADDR*)&clinetAddr, &addrlen)) {
            //RECV
            ZeroMemory(userNameinput, 200);
            r = recv(sConnect, userNameinput, sizeof(userNameinput), 0);
            userNameList = userNameList + string(userNameinput) + ":";
            onlineUser[userNameinput] = string(inet_ntoa(clinetAddr.sin_addr)) + ":" + to_string(clinetAddr.sin_port);
                //.push_back(make_pair(string(inet_ntoa(clinetAddr.sin_addr)) + ":" + to_string(clinetAddr.sin_port) + ":", userNameinput));
            for (iter = onlineUser.begin(); iter != onlineUser.end(); iter++) {
                cout << iter->first << " " << iter->second << endl;
            }
            cout << "all list " << userNameList.c_str() << endl;
            //SEND
            send(sConnect, userNameList.c_str(), userNameList.length(), 0);
            cout << userNameList.length() << endl;
            cout << "a connection was found" << endl;
            printf("server: got connection from %s\n", inet_ntoa(addr.sin_addr));
            if (message == "@RefreshPLZ") {

            }
            const char *sendbuf = "Response From Server";
            send(sConnect, sendbuf, (int)strlen(sendbuf), 0);
            closesocket(sConnect);
        }
    }
}
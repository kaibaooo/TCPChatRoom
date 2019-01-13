#include"Client.h"

Client::Client(const string &chatroomName):TCPChatRoom(chatroomName) {
    DLLVersion = MAKEWORD(2, 1);
    r = WSAStartup(DLLVersion, &wsaData);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Set TCP
    addr.sin_family = AF_INET; //Set TCP
    addr.sin_port = htons(15501); //Set Port
}
void Client::startClient() {
    while (1) {
        SOCKET sConnect;
        sConnect = socket(AF_INET, SOCK_STREAM, NULL);
        cout << "Refresh[R] or SendMsg[S]" << endl;
        cin >> confirm;
        connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
        if (confirm == "R") {
            send(sConnect, "@RefreshPLZ", (int)strlen("@RefreshPLZ"), 0);
            ZeroMemory(message, 200);
            r = recv(sConnect, message, sizeof(message), 0);
            cout << message << endl;
        }
        else if (confirm == "S") {
            string sendbuf;
            cout << "Input Your Msg : ";
            cin >> sendbuf;
            cout << "I send " << sendbuf << endl;
            send(sConnect, sendbuf.c_str(), (int)strlen(sendbuf.c_str()), 0);
            ZeroMemory(message, 2000);
            r = recv(sConnect, message, sizeof(message), 0);
            const char *spliter = ":";
            split(message, spliter);
        }
        closesocket(sConnect);
    }
}
void Client::split(char * str, const char * s) {
    int iCurName = 0;
    char * newName[100];
    char *token = strtok(str, s);
    while (token != NULL) {
        printf("%s\n", token);
        newName[iCurName] = (char *)malloc(strlen(token) + 1);
        strcpy(newName[iCurName], token);
        iCurName++;
        token = strtok(NULL, s);
    }
}
#include"Client.h"
#include"UI.h"
//UI ui;
Client::Client(const string &chatroomName):TCPChatRoom(chatroomName) {
    DLLVersion = MAKEWORD(2, 1);
    r = WSAStartup(DLLVersion, &wsaData);
    addr.sin_addr.s_addr = inet_addr("192.168.0.107"); //Set TCP
    addr.sin_family = AF_INET; //Set TCP
    addr.sin_port = htons(15501); //Set Port
    
}
void Client::startClient(const string &usrName_) {
    //��l�ƨϥΪ̦W��
    setUserName(usrName_);
    //�e�ϥΪ̦W�浹Server
    //�����A���^�Ǫ��u�W�ϥΪ̦W��
    sendUserName();
    //recvOnlineUserList();
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
            //ui.print(message);
            cout << message << endl;
            
        }
        else if (confirm == "S") {
            string sendbuf;
            cout << "Input Your Msg : ";
            cin >> sendbuf;
            //cout << "I send " << sendbuf << endl;
            send(sConnect, ("&"+ userName+" : " +sendbuf + "\n").c_str(), ("&" + userName + " : " + sendbuf + "\n").length(), 0);
            //for (int i = 0; i < 10; i++) {
            ZeroMemory(message, 2000);
            r = recv(sConnect, message, sizeof(message), 0);
            //ui.print(message);
            cout << message << endl;
            //}
            //const char *spliter = ":";
            //split(message, spliter);
        }
        closesocket(sConnect);
    }
}
void Client::setUserName(const string &userName_) {
    userName = userName_;
}
void Client::sendUserName() {
    SOCKET sConnect;
    sConnect = socket(AF_INET, SOCK_STREAM, NULL);
    connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
    send(sConnect, ("^" + userName).c_str(), ("^" + userName).length(), 0);
    ZeroMemory(message, 2000);
    r = recv(sConnect, message, sizeof(message), 0);
    onlineUser = message;
    //ui.print("");
    
    cout << "�ثe�b�u�W���W�欰 : ";
    cout << message << endl;
    closesocket(sConnect);
}
void Client::recvOnlineUserList() {
    
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
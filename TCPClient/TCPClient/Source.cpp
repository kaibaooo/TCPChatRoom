#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996)
#include <WinSock2.h>
#include <iostream>
#include <string>

using namespace std;
void split(char *, const char *);
int main() {
    string confirm;
    char message[2000];

    //開始 Winsock-DLL
    int r;
    WSAData wsaData;
    WORD DLLVersion;
    DLLVersion = MAKEWORD(2, 1);
    r = WSAStartup(DLLVersion, &wsaData);

    //宣告給 socket 使用的 sockadder_in 結構
    SOCKADDR_IN addr;

    int addlen = sizeof(addr);

    

    //設定 addr 資料
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(15501);
    while (1) {
        //設定 socket
        SOCKET sConnect;
        //AF_INET: internet-family
        //SOCKET_STREAM: connection-oriented socket
        sConnect = socket(AF_INET, SOCK_STREAM, NULL);
        cout << "Refresh[R] or SendMsg[S]" << endl;
        cin >> confirm;
        connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
        if (confirm == "R") {
            
            send(sConnect, "@RefreshPLZ", (int)strlen("@RefreshPLZ"), 0);
            ZeroMemory(message, 200);
            r = recv(sConnect, message, sizeof(message), 0);
            cout << message << endl;
            //closesocket(sConnect);
        }
        else if (confirm == "S") {
            string sendbuf;
            cout << "Input Your Msg : ";
            cin >> sendbuf;
            cout << "I send " << sendbuf << endl;
            //const char *sendbuf = "Message From Client";
            //connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
            send(sConnect, sendbuf.c_str(), (int)strlen(sendbuf.c_str()), 0);
            ZeroMemory(message, 2000);
            r = recv(sConnect, message, sizeof(message), 0);
            const char *spliter = ":";
            split(message, spliter);
            //cout << message << endl;
            //closesocket(sConnect);
        }
        closesocket(sConnect);
    }

}
void split(char * str,const char * s) {
    int iCurName = 0;
    char * newName[100];
    char *token = strtok(str, s);
    while (token != NULL) {
        printf(" %s\n", token);
        newName[iCurName] = (char *)malloc(strlen(token) + 1);
        strcpy(newName[iCurName], token);
        iCurName++;
        token = strtok(NULL, s);
    }
}
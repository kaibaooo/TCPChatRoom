#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <iostream>
#include<utility>
#include<vector>
#include<string>

#pragma warning(disable:4996)
using namespace std;

vector<pair<string, string>> msgs; //destname,msgs
vector<pair<string, string>> onlineUser;//ip+port,username
vector<pair<string, string>>::iterator iter;
string userNameList;//回傳給clinet

int main() {
    int r;
    WSAData wsaData;
    WORD DLLVSERION;
    DLLVSERION = MAKEWORD(2, 1);//Winsocket-DLL 版本

                                //用 WSAStartup 開始 Winsocket-DLL
    r = WSAStartup(DLLVSERION, &wsaData);

    //宣告 socket 位址資訊(不同的通訊,有不同的位址資訊,所以會有不同的資料結構存放這些位址資訊)
    SOCKADDR_IN addr;
    int addrlen = sizeof(addr);

    //建立 socket
    SOCKET sListen; //listening for an incoming connection
    SOCKET sConnect; //operating if a connection was found

                     //AF_INET：表示建立的 socket 屬於 internet family
                     //SOCK_STREAM：表示建立的 socket 是 connection-oriented socket 
    sConnect = socket(AF_INET, SOCK_STREAM, NULL);

    //設定位址資訊的資料
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(15501);

    //設定 Listen
    sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);//SOMAXCONN: listening without any limit

                               //等待連線
    SOCKADDR_IN clinetAddr;
    while (true) {
        char message[200];
        char userNameinput[200];
		
        cout << "waiting..." << endl;

        if (sConnect = accept(sListen, (SOCKADDR*)&clinetAddr, &addrlen)) {
			
            ZeroMemory(userNameinput, 200);
			r = recv(sConnect, userNameinput, sizeof(userNameinput), 0);
			userNameList = userNameList+string(userNameinput) + ":";
			//cout << string(inet_ntoa(clinetAddr.sin_addr)) + to_string(clinetAddr.sin_port) << "  " << userNameinput<<endl;
			onlineUser.push_back(make_pair(string(inet_ntoa(clinetAddr.sin_addr))+":"+ to_string(clinetAddr.sin_port)+":", userNameinput));
			for (iter = onlineUser.begin(); iter != onlineUser.end(); iter++) {
				cout << iter->first << " " << iter->second << endl;
			}
			cout << "all list " << userNameList.c_str() <<endl;
			send(sConnect, userNameList.c_str(), userNameList.length(), 0);
            cout << userNameList.length() << endl;
			//cout<< onlineUser.begin()->first << "  and  " << onlineUser.begin()->second << endl;
			//pair<string, int> p("favorite h-game", 9800);  p.first p.second
            //ZeroMemory(message, 200);
            //r = recv(sConnect, message, sizeof(message), 0);
            cout << "a connection was found" << endl;
            printf("server: got connection from %s\n", inet_ntoa(addr.sin_addr));
            //cout << message << endl;
			if (message == "@RefreshPLZ") {

			}
            //傳送訊息給 client 端
            const char *sendbuf = "Response From Server";
            send(sConnect, sendbuf, (int)strlen(sendbuf), 0);
            closesocket(sConnect);
        }
    }

    //getchar();
}

#include"Server.h"
#include <string.h>
#include<map>

Server::Server(const string &serverName)
:TCPChatRoom(serverName){
    int r;
	msgsNum = 0;
    DLLVSERION = MAKEWORD(2, 1);
    r = WSAStartup(DLLVSERION, &wsaData);
    sConnect = socket(AF_INET, SOCK_STREAM, NULL);
    addr.sin_addr.s_addr = inet_addr("192.168.0.107");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(15501);
    sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

}
void Server::startServer() {
    while (true) {
        char message[200];
		//^新增使用者
		//&新增訊息
        cout << "waiting..." << endl;
        if (sConnect = accept(sListen, (SOCKADDR*)&clinetAddr, &addrlen)) {
            //RECV
            ZeroMemory(message, 200);

            r = recv(sConnect, message, sizeof(message), 0);
			if (message[0] == '^') {
				addNewUser(message);
			}
			else if(message[0] == '&') {
				recvMsg(message);
			}
			else if (message[0] == '@') {//refresh
				send(sConnect, allChatList.c_str(), allChatList.length(), 0);
			}
			else if (message[0] == '/') {
				recvPrivateMsg(message);
			}
			else if (message[0] == '$') {
                //cout << "YEEEEEEEEEEEEEEEE" << endl;
				sendPrivateMsg(message);
			}
			/*
            userNameList = userNameList + string(userNameinput) + ":";
            onlineUser[userNameinput] = string(inet_ntoa(clinetAddr.sin_addr)) + ":" + to_string(clinetAddr.sin_port);
                //.push_back(make_pair(string(inet_ntoa(clinetAddr.sin_addr)) + ":" + to_string(clinetAddr.sin_port) + ":", userNameinput));
            for (iter = onlineUser.begin(); iter != onlineUser.end(); iter++) {
                cout << iter->first << " " << iter->second << endl;
            }
            cout << "all list " << userNameList.c_str() << endl;
            //SEND 線上人員
            send(sConnect, userNameList.c_str(), userNameList.length(), 0);
            cout << userNameList.length() << endl;
			//收訊息
			r = recv(sConnect, message, sizeof(message), 0);
			msgs.push_back(make_pair(userNameinput, message));
			allChatList = allChatList + string(userNameinput) + ":" + string(message) + " ";
			for (iter2 = msgs.begin(); iter2 != msgs.end(); iter2++){
				cout << iter2->first << " " << iter2->second << endl;
			}
			*/
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
void Server::addNewUser(char *message) {
	char userNameinput[200];
	ZeroMemory(userNameinput, 200);
	for (int i = 1; i < strlen(message); i++) {
		userNameinput[i - 1] = message[i];
	}
	cout <<"new user "<<userNameinput << "is online." << endl;
	userNameList = userNameList + string(userNameinput) + ":";
	onlineUser[userNameinput] = string(inet_ntoa(clinetAddr.sin_addr)) + ":" + to_string(clinetAddr.sin_port);
	send(sConnect, userNameList.c_str(), userNameList.length(), 0);
	cout << userNameList.c_str() << endl;
}
void Server::recvMsg(char *message) {	
	char oneTalk[200];
	ZeroMemory(oneTalk, 200);
	for (int i = 1; i < strlen(message); i++) {
		oneTalk[i - 1] = message[i];//talk=name+message
	}
	msgsNum++;
	msgs.push_back(oneTalk);
	cout << oneTalk;
	allChatList.clear();
	if (msgsNum >= 10) {
		for (iterMsgs = msgs.begin() + msgsNum - 10; iterMsgs != msgs.end(); iterMsgs++) {
			allChatList = allChatList + *iterMsgs;
		}
	}
	else {
		for (iterMsgs = msgs.begin(); iterMsgs != msgs.end(); iterMsgs++) {
			allChatList = allChatList + *iterMsgs;
		}
	}
	send(sConnect, allChatList.c_str(), allChatList.length(), 0);
}
void Server::recvPrivateMsg(char*message) {
    /*
    struct privateMsg {
        char *sender;
        char *recver;
        char *msg;
    };
    */
	char sourName[200];
	char destName[200];//first
	char privateMsga[200];
	ZeroMemory(privateMsga, 200);
	ZeroMemory(destName, 200);
	ZeroMemory(sourName, 200);
	int flag = 0;
	int num[3] = { 0,0,0 };
	for (int i = 1; i <= strlen(message); i++) {
		if (flag == 0) {
			if (message[i] != '/') {
				destName[num[0]] = message[i];
				num[0]++;
			}
			else {
				destName[num[0]] = '\0';
				flag = 1;
				i++;
			}
		}
		if (flag == 1) {
			if (message[i] != '/') {
				sourName[num[1]] = message[i];
				num[1]++;
			}
			else {
				sourName[num[1]] = '\0';
				flag = 2;
				i++;
			}
		}
		if (flag == 2) {
			privateMsga[num[2]] = message[i];
			num[2]++;
		}
	}
	/*
	privateMsg privateMsgTemp;
	privateMsgTemp.sender = sourName;
	privateMsgTemp.recver = destName;
	privateMsgTemp.msg = privateMsga;
    priMsgs.push_back(privateMsgTemp);
	*/
    privateMsgs.push_back(make_pair(string(destName), string(sourName)+ string(privateMsga)));
	for (iter2 = privateMsgs.begin(); iter2 != privateMsgs.end(); iter2++) {
		cout << iter2->first << " " << iter2->second << endl;
	}

}
void Server::sendPrivateMsg(char *message) {
	char name[20];
	string sendMsg;
	for (int i = 1; i <=strlen(message); i++) {
		name[i - 1] = message[i];//
	}
    for (iter2 = privateMsgs.begin(); iter2 != privateMsgs.end(); iter2++) {
		if (iter2->first == string(name)) {
			sendMsg = sendMsg + iter2->second;
		}
    }	
	send(sConnect, sendMsg.c_str(), sendMsg.length(), 0);
}
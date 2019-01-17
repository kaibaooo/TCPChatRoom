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
		//^新增使用者
		//&新增訊息
        //@重整
        //$私訊
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
			else if (message[0] == '$') {//當client要看私訊 傳回她和朋友的訊息
                //cout << "YEEEEEEEEEEEEEEEE" << endl;
				sendPrivateMsg(message);
			}
			else if (message[0] == '*') {
				recvUserStatus(message);
			}
			else if (message[0] == '~') {
				sendUserStatus();
			}
            else if (message[0] == '=') {
                sendUserList();
			}
			else if (message[0]='#') {
				deletUser(message);
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
            const char *sendbuf = "Success";
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
	//控制大聊天室只有20筆資料
	if (msgsNum >= 20) {
		for (iterMsgs = msgs.begin() + msgsNum - 20; iterMsgs != msgs.end(); iterMsgs++) {
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
	privateMsgs.push_back(string(message));

	/*原版本
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
	
	
    privateMsgs.push_back(make_pair(string(destName), string(sourName)+ string(privateMsga)));
	for (iter2 = privateMsgs.begin(); iter2 != privateMsgs.end(); iter2++) {
		cout << iter2->first << " " << iter2->second << endl;
	}
	*/
}

void Server::sendPrivateMsg(char *message) {
	string sourName;//來源的人
	string destName;//frien
	string s = string(message);
	int pos = 1;
	string suber = "/";
	string token;
	s = s.substr(1);

	while ((pos = s.find(suber)) != string::npos) {
		token = s.substr(0, pos);
		sourName = token;
		s.erase(0, pos + suber.length());
	}
	destName = s;
	int flag = 0;
	string sendMsg;//要送出的字串
    for (iterMsgs = privateMsgs.begin(); iterMsgs != privateMsgs.end(); iterMsgs++) {
		//解析privateMsgs的資料
		string che_sourName;
		string che_destName;
		string che_privateMsga;
		string s = *iterMsgs;//歷史所有的私訊疊代器
		
		int pos = 1;
		string suber = "/";
		string token;
		s = s.substr(1);
		int flat = 0;
		while ((pos = s.find(suber)) != string::npos) {
			token = s.substr(0, pos);
			if (flat == 0) {
				che_sourName = token;
				flat++;
			}
			else if (flat == 1) {
				che_destName = token;
			}
			s.erase(0, pos + suber.length());
			che_privateMsga=s;
		}

		//判斷是不是
		if (destName == che_destName&& sourName == che_sourName) {
			sendMsg = sendMsg + destName + "->" + sourName + ":" + che_privateMsga + "\n";
        }
        else if (destName == che_sourName && sourName== che_destName) {
			sendMsg = sendMsg + sourName + "->" + destName + ":" + che_privateMsga + "\n";
        }
    }	
	if (sendMsg.length()==0) {
		sendMsg = "No one want to send a message to you, Nerd";
	}
	send(sConnect, sendMsg.c_str(), sendMsg.length(), 0);
}
void Server::recvUserStatus(char*message) {
	string name;
	string status;
	string sendMsg = "Set successfully!\n";
	string s = string(message);
	int pos = 1;
	string suber = "/";
	string token;
	s = s.substr(1);
	while ((pos = s.find(suber)) != string::npos) {
		token = s.substr(0, pos);
		name = token;
		s.erase(0, pos + suber.length());
	}
	status = s;
	//判斷此使用者有沒有宣告過status
	int flat = 0;
	for (iterStatus = userStatus.begin(); iterStatus != userStatus.end(); iterStatus++)
	{
		if (name == iterStatus->first) {
			iterStatus->second = status;
			flat = 1;
		}
	}
	if (flat == 0) {
		userStatus.push_back(make_pair(name, status));
	}
	send(sConnect, sendMsg.c_str(), sendMsg.length(), 0);
}
void Server::sendUserStatus() {
	string s = userNameList;
    string sendMsg;
	cout << userNameList << endl;
	int pos = 1;
	string suber = ":";
	string token;

	while ((pos = s.find(suber)) != string::npos) {
		token = s.substr(0, pos);
		int flat = 0;
		for (iterStatus = userStatus.begin(); iterStatus != userStatus.end(); iterStatus++)
		{
            cout << token<< endl;
			if (token == iterStatus->first) {
				sendMsg = sendMsg + iterStatus->first+"=>"+ iterStatus->second + "\n";
				flat = 1;
			}
		}
		if (flat == 0) {
			sendMsg = sendMsg + token + "=>" + "null" + "\n";
		}
		s.erase(0, pos + suber.length());
	}
	int flat = 0;
	/*
	for (iterStatus = userStatus.begin(); iterStatus != userStatus.end(); iterStatus++)
	{
		if (s == iterStatus->first) {
			sendMsg = sendMsg + iterStatus->first + "=>" + iterStatus->second + "\n";
			flat = 1;
		}
	}
	if (flat == 0) {
		sendMsg = sendMsg + token + "=>" + "null" + "\n";
	}
	*/
	
	send(sConnect, sendMsg.c_str(), sendMsg.length(), 0);
}
void Server::deletUser(char*message) {
	string s;
	s = userNameList;
	string name;
	name = string(message).substr(1);
	int pos = 1;
	string suber = ":";
	string token;
	int mun = 0;
	int flat = 0;
	while ((pos = s.find(suber)) != string::npos) {
		token = s.substr(0, pos);
        cout << "token : " << token << endl;
		if (name == token) {
			flat = 1;
		}
		else if (flat == 0) {
			mun = mun + pos + 1;
		}
		s.erase(0, pos + suber.length());
	}
	userNameList.erase(mun, name.length() + 1);
}

void Server::sendUserList() {
	cout << "in sendUserList : " << userNameList << endl;
    send(sConnect, userNameList.c_str(), userNameList.length(), 0);
}
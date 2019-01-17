#include"Client.h"
//UI ui;
Client::Client(const string &chatroomName):TCPChatRoom(chatroomName) {
    DLLVersion = MAKEWORD(2, 1);
    r = WSAStartup(DLLVersion, &wsaData);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Set TCP
    addr.sin_family = AF_INET; //Set TCP
    addr.sin_port = htons(15501); //Set Port
    
}
void Client::startClient(const string &usrName_) {
    //初始化使用者名稱
    if (usrName_ == "Guest" || usrName_ == "guest") {
        group = "guest";
    }
    setUserName(usrName_);
    //送使用者名單給Server
    //收伺服器回傳的線上使用者名單
    sendUserName();
    //recvOnlineUserList();
    while (1) {
        //system("cls");
        string confirm;
        SOCKET sConnect;
        sConnect = socket(AF_INET, SOCK_STREAM, NULL);
        cout << "Refresh[R] or SendMsg[S] or RefreshPri[L] or SendPriMsg[P] or editStatus[U] or updateStatus[Q] or exit[E] "<< endl;
        cin >> confirm;
		//Input();
		//checkInstruction();
        connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
        if (confirm == "R") { //refresh message
            send(sConnect, "@", (int)strlen("@"), 0);
            ZeroMemory(message, 200);
            r = recv(sConnect, message, sizeof(message), 0);
            //ui.print(message);
            cout << message << endl;
            
        }
        else if (confirm == "S") { //send general message
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
        else if (confirm == "P") { //send private message
            string sendbuf;
            string toWho;
            cout << "To who?" << endl;
            cin >> toWho;
            cout << "Input Your Msg : ";
            cin >> sendbuf;
            //私訊傳送格式
            send(sConnect, ("/" + toWho +"/"+userName+"/" + sendbuf).c_str(), ("/" + toWho + "/" + userName + "/" + sendbuf).length(), 0);
            ZeroMemory(message, 2000);
            r = recv(sConnect, message, sizeof(message), 0);
            cout << message << endl;
            //}
            //const char *spliter = ":";
            //split(message, spliter);
        }
        else if (confirm == "L") { //refresh private message
            string withWho;
            cout << "With who : ";
            cin >> withWho;
            send(sConnect, ("$" + userName + '/' + withWho).c_str(), ("$" + userName + '/' + withWho).length(), 0);
            ZeroMemory(message, 2000);
            r = recv(sConnect, message, sizeof(message), 0);
            //ui.print(message);
            cout << message << endl;
            //}
            //const char *spliter = ":";
            //split(message, spliter);
        }
        else if (confirm == "U") { //refresh private message
            string status;
            cout << "New Status : ";
            cin >> status;
            send(sConnect, ("*" + userName + "/" + status).c_str(), ("*" + userName + "/" + status).length(), 0);
            ZeroMemory(message, 2000);
            r = recv(sConnect, message, sizeof(message), 0);
            //ui.print(message);
            cout << message << endl;
            //}
            //const char *spliter = ":";
            //split(message, spliter);
        }
        else if (confirm == "Q") {
            send(sConnect, "~", strlen("~"), 0);
            ZeroMemory(message, 2000);
            r = recv(sConnect, message, sizeof(message), 0);
            cout << message << endl;
        }
        else if (confirm == "E") {
            send(sConnect, "#", strlen("#"), 0);
            exit;
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
    cout << "目前在線上的名單為 : ";
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
/*
void Client::checkInstruction() {
	int len = detail.size();
	if (len < 2) {
		cout << original << "is an illagle instruction." << endl;
	}
	else if (detail[0] == "set") {
		if (detail[1] == "addfriend") {
			if (len == 3) {
				Addfriend(detail[2]);
			}
			else {
				cout << original << "is an illagle instruction." << endl;
			}
		}
		else if (detail[1] == "deletefriend") {
			if (len == 3) {
				Deletefriend(detail[2]);
			}
			else {
				cout << original << "is an illagle instruction." << endl;
			}
		}
		else if (detail[1] == "setstate") {
			Setstate();
		}
		else {
			cout << detail[1] << "is invaild instruction" << endl;
		}
	}
	else if (detail[0] == "show") {
		if (detail[1] == "online") {
			sendUserName();
		}
		else if (detail[1] == "allmember") {
			Showallmember();
		}
		else if (detail[1] == "signaters") {
			ShowEveryPersonalitySignature();
		}
		else if (detail[1] == "friends") {
			Showfriends();
		}
		else {
			cout << detail[1] << "is invaild instruction" << endl;
		}
	}
	else if (detail[0] == "send") {
		if (detail[1] == "group") {
			cout << "function is not finished yet." << endl;
		}
		else if (detail[1] == "friend") {
			cout << "function is not finished yet." << endl;
			Input();
		}
	}
	else {
		cout << detail[0] << "is invaild instruction" << endl;
		Input();
	}

}
}
*/
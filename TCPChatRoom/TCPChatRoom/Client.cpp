#include"Client.h"
//UI ui;
Client::Client(const string &chatroomName):TCPChatRoom(chatroomName) {
    DLLVersion = MAKEWORD(2, 1);
    r = WSAStartup(DLLVersion, &wsaData);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Set TCP
    addr.sin_family = AF_INET; //Set TCP
    addr.sin_port = htons(15501); //Set Port
    
}
void Client::start(const string &usrName_)  {
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
		gotoxy(90, 2);
		cout << "Welecome! " << userName;
		//string confirm;
		SOCKET sConnect;
		sConnect = socket(AF_INET, SOCK_STREAM, NULL);
		//cout << "Refresh[R] or SendMsg[S] or RefreshPri[L] or SendPriMsg[P]" << endl;
		//cin >> confirm;
		Input();
		system("cls");
		int len = detail.size();
		if (len < 2) {
			cout << original << " is an illagle instruction." << endl;
		}
		else if (detail[0] == "set") {
			if (detail[1] == "addfriend") {
				if (len == 3) {
					Addfriend(detail[2]);
				}
				else {
					cout << original << " is an illagle instruction." << endl;
				}
			}
			else if (detail[1] == "deletefriend") {
				if (len == 3) {
					Deletefriend(detail[2]);
				}
				else {
					cout << original << " is an illagle instruction." << endl;
				}
			}
			else if (detail[1] == "signater") {
				if (detail.size() == 3) {
					connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
					//Setstate();
					/*string status;
					cout << "New Status : ";
					cin >> status;*/
					//send(sConnect, ("*" + userName + "/" + status).c_str(), ("*" + userName + "/" + status).length(), 0);
					send(sConnect, ("*" + userName + "/" + detail[2]).c_str(), ("*" + userName + "/" + detail[2]).length(), 0);
					ZeroMemory(message, 2000);
					r = recv(sConnect, message, sizeof(message), 0);
					//ui.print(message);
					cout << message << endl;
					closesocket(sConnect);
					//}
					//const char *spliter = ":";
					//split(message, spliter);
				}
				else {
					cout << original << " is an illagle instruction." << endl;
				}
			}
			else if (detail[1] == "exit") {
				connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
				send(sConnect, ("#"+userName).c_str(), ("#" + userName).length(), 0);
				exit(1);
				//closesocket(sConnect);
			}
			else {
				cout << detail[1] << " is illagle instruction." << endl;
			}
		}
		else if (detail[0] == "show") {
			if (detail[1] == "online") {
                recvOnlineUserList();
			}
			else if (detail[1] == "allmember") {
				Showallmember();
			}
			else if (detail[1] == "allsignaters") {
				//ShowEveryPersonalitySignature();
				connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
				send(sConnect, "~", strlen("~"), 0);
				ZeroMemory(message, 2000);
				r = recv(sConnect, message, sizeof(message), 0);
				cout << message << endl;
				closesocket(sConnect);
			}
			else if (detail[1] == "friends") {
				Showfriends();
			}
			else if (detail[1] == "message") {
				if (detail.size() == 3) {
					if (detail[2] == "group") {//refresh general message
						connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
						send(sConnect, "@", (int)strlen("@"), 0);
						ZeroMemory(message, 200);
						r = recv(sConnect, message, sizeof(message), 0);
						//ui.print(message);
						cout << message;
						closesocket(sConnect);
					}
					else {
						connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
						string withWho;
						/*cout << "With who : ";
						cin >> withWho;*/
						//send(sConnect, ("$" + userName + '/' + withWho).c_str(), ("$" + userName + '/' + withWho).length(), 0);
						send(sConnect, ("$" + userName + '/' + detail[2]).c_str(), ("$" + userName + '/' + detail[2]).length(), 0);
						ZeroMemory(message, 2000);
						r = recv(sConnect, message, sizeof(message), 0);
						//ui.print(message);
						cout << message;
						closesocket(sConnect);
					}
					//const char *spliter = ":";
					//split(message, spliter);
				}
			}
			else {
				cout << detail[1] << " is illagle instruction." << endl;
			}
		}
		else if (detail[0] == "send") {
			if (detail[1] == "group") {
				if (detail.size() == 3) {
					connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
					//string sendbuf;
					//cout << "Input Your Msg : ";
					//cin >> sendbuf;
					//cout << "I send " << sendbuf << endl;
					send(sConnect, ("&" + userName + " : " + detail[2] + "\n").c_str(), ("&" + userName + " : " + detail[2] + "\n").length(), 0);
					//for (int i = 0; i < 10; i++) {
					ZeroMemory(message, 2000);
					r = recv(sConnect, message, sizeof(message), 0);
					//ui.print(message);
					cout << message << endl;
					closesocket(sConnect);
					//}
					//const char *spliter = ":";
					//split(message, spliter);
				}
				else {
					cout << original << "is illagle instruction.";
				}
			}
			else if (detail[1] == "friend") {
				if (detail.size() == 4) {
					//string sendbuf;
					//string toWho;
					//cout << "To who?" << endl;
					//cin >> toWho;
					//cout << "Input Your Msg : ";
					//cin >> sendbuf;
					//私訊傳送格式
					connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
					send(sConnect, ("/" + detail[2] + "/" + userName + "/" + detail[3]).c_str(), ("/" + detail[2] + "/" + userName + "/" + detail[3]).length(), 0);
					ZeroMemory(message, 2000);
					r = recv(sConnect, message, sizeof(message), 0);
					cout << message << endl;
					closesocket(sConnect);
					//}
					//const char *spliter = ":";
					//split(message, spliter);	
				}
				else {
					cout << original << " is illagle instruction.";
				}
			}
			else {
				cout << detail[1] << "is illagle instruction." << endl;
			}

		}
		else {
			cout << original << "is illagle instruction." << endl;
		}
        /*
		else if (confirm == "U") { //refresh private signature
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
		else if (confirm == "Q") {//show all signatue
			send(sConnect, "~", strlen("~"), 0);
			ZeroMemory(message, 2000);
			r = recv(sConnect, message, sizeof(message), 0);
			cout << message << endl;
		}
		else if (confirm == "E") {
			send(sConnect, "#", strlen("#"), 0);
			exit;
		}
        */
		//closesocket(sConnect);
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
    SOCKET sConnect;
    sConnect = socket(AF_INET, SOCK_STREAM, NULL);
    connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
    send(sConnect, "=", strlen("="), 0);
    ZeroMemory(message, 2000);
    r = recv(sConnect, message, sizeof(message), 0);
    onlineUser = message;
    cout << "目前在線上的名單為 : ";
    cout << message << endl;
    closesocket(sConnect);
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

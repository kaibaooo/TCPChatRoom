#include"UI.h"
#include<iostream>
using namespace std;

UI::UI()
:Client(roomName){
    
}
void UI::print(const char *msgs) {
    system("cls");
    cout << "Welcome to " << getRoomName() << endl;
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("目前使用者 : ");
    printUsers(onlineUser);
    printMsgQueue(msgs);

}
void UI::printUsers(const char* users) {
    cout << users << endl;
}
void UI::printMsgQueue(const char *msgs) {
    cout << msgs << endl;
}
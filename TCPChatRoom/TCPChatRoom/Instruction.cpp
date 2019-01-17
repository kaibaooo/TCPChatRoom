#include<iostream>
#include<windows.h>
#include<string>
#include<sstream>
#include<vector>
#include"Instruction.h"

using namespace std;

void Instruction::Input() {
	ShowInstruction();
	detail.clear();
	original.clear();
	gotoxy(0, 25);
	cout << ">> ";
	getline(cin, original);
	cutInput();
}

void Instruction::cutInput() {
	stringstream buf;
	string text;
	buf << original;
	int i = 0;
	while (getline(buf, text, '/')) {
		detail.push_back(text);
		cout << text << endl;
	}
	//checkInstruction();
}


void Instruction::gotoxy(int xpos, int ypos) {
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void Instruction::ShowInstruction() {
	for (int i = 0; i < 25; i++) {
		gotoxy(88, i);
		cout << "¢k";
	}

	gotoxy(90, 4);
	cout << "All Instruction";

	gotoxy(90, 6);
	cout << "SET" << endl;
	gotoxy(90, 7);
	cout << "set/addfriend/name" << endl;
	gotoxy(90, 8);
	cout << "set/deletefriend/name" << endl;
	gotoxy(90, 9);
	cout << "set/signater/string" << endl;
	gotoxy(90, 10);
	cout << "set/exit" << endl;

	gotoxy(90, 12);
	cout << "SEND MESSAGE" ;
	gotoxy(90, 13);
	cout << "send/group/string" ;
	gotoxy(90, 14);
	cout << "send/friend/name/string" ;

	gotoxy(90, 16);
	cout << "SHOW" << endl;
	gotoxy(90, 17);
	cout << "show/online" << endl;
	gotoxy(90, 18);
	cout << "show/allmember" << endl;
	gotoxy(90, 19);
	cout << "show/allsignaters" << endl;
	gotoxy(90, 20);
	cout << "show/friends" << endl;
	gotoxy(90, 21);
	cout << "show/message/friendname" << endl;
	gotoxy(90, 22);
	cout << "show/message/group" << endl;
	
	gotoxy(0, 24);
	for (int i = 0; i < 44; i++) {
		cout << "¢f";
	}

}



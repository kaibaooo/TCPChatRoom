#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include"Instruction.h"

using namespace std;

Instruction::Instruction() {
}

Instruction::~Instruction() {
}

void Instruction::Input() {
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
	}
	checkInstruction();
}


void Instruction::checkInstruction() {//用personality的function
	int len = detail.size();
	if (len < 2) {
		cout << original << "is an illagle instruction." << endl;
	}
	else if (detail[0] == "set") {
		if (detail[1]=="addfriend") {

		}
		else if (detail[1] == "deletefriend") {

		}
		else if (detail[1] == "setstate") {

		}
		else {
			cout << detail[1] << "is invaild instruction" << endl;
		}
	}
	else if (detail[0] == "show") {
		if (detail[1] == "online") {

		}
		else if (detail[1] == "allmember") {

		}
		else if (detail[1] == "instruction") {

		}
		else if (detail[1] == "signater") {

		}
		else {
			cout << detail[1] << "is invaild instruction" << endl;
		}
	}
	else if (detail[0] == "send") {
		//還沒寫
	}
	else {
		cout << detail[0] << "is invaild instruction" << endl;
	}
	
}

void Instruction::refresh() {
	system("cls");
}

void Instruction::showformat() {
	cout << "SET" << endl;
	cout << "set/addfriend/name" << endl;
	cout << "set/deletefriend/name" << endl;
	cout << "setstate/state" << endl << endl;

	cout << "SEND MESSAGE" << endl;
	cout << "send/group/name/message" << endl;
	cout << "send/friend/name/message" << endl << endl;

	cout << "SHOW" << endl;
	cout << "show/online" << endl;
	cout << "show/allmember" << endl;
	cout << "show/instruction" << endl;
	cout << "show/signater" << endl;
}


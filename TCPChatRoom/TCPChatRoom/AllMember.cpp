#include"AllMember.h"
using namespace std;

void AllMember::InitialSight() {
	cout << "輸入名字" << endl;
	cin >> Name;
	Loadaccount(Name);
}
void AllMember::Loadaccount(string name) {
	
	for (int i = 0; i < 5; i++){
		if (name == Allmember[i]) {
			Online[i] = name;
			Showinstruction();
			break;
		}
		else {
			if (i == 4) {
				cout << "Wrong account" << endl;
				InitialSight();
			}
		}
	}
}
void AllMember::Offaccount(string name) {
	for (int i = 0; i < 5; i++){
		if (Online[i] == name) {
			Online[i] = "0";
			break;
		}
	}
	InitialSight();
}
void AllMember::Showonline() {
	for (int i = 0; i < 5; i++){
		if (Online[i] == "0"){
			continue;
		}
		else {
			cout << Online[i] << endl;
		}
	}
	Showinstruction();
}
void AllMember::Showallmember() {
	for (int i = 0; i < 5; i++) {
		cout << Allmember[i] << endl;
	}
	Showinstruction();
}
void AllMember::Showinstruction() {
	//交給你了~
}
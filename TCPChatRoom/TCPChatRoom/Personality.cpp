#include"Personality.h"
using namespace std;

void Personality::Addfriend(string name) {
	for (int i = 0; i < 5; i++){
		if (Allmember[i] == name) {
			for (int j = 0; j < 5; j++){
				if (friends[j] == name) {
					cout << name << " has been added to your friends' list." << endl;
					break;
				}
				else if (j == 4 && friends[j] != name) {
					for (int k = 0; k < 5; k++){
						if (friends[k] == "0") {
							friends[k] = name;
							cout << name << "is added to your friends' list successfully¡I" << endl;
							break;
						}
					}
				}
			}
			break;
		}
		else if(i == 4 && Allmember[i] != name){
			cout << name << " is not in member\n";
		}
	}
	//Showinstruction();
}
void Personality::Deletefriend(string name) {
	for (int i = 0; i < 5; i++) {
		if (Allmember[i] == name) {
			for (int j = 0; j < 5; j++) {
				if (friends[j] == name) {
					friends[j] = "0";
					cout << name << " is deleted to your friends' list successfully¡I" << endl;
					break;
				}
				else if (j == 4 && friends[j] != name) {
					cout << name << " is not your friend¡I" << endl;
				}
			}
			break;
		}
		else if (i == 4 && Allmember[i] != name) {
			cout << name << " is not in member\n";
		}
	}
	//Input();
}
void Personality::Setstate() {
	cout << "enter your personality signature¡I\n";
	cin >> setstate;
}
void Personality::Showfriends() {
	bool lonely = true;
	for (int i = 0; i < 5; i++) {
		if (friends[i] == "0") {
			continue;
		}
		else {
			cout << friends[i] << endl;
			lonely = false;
		}
	}
	if (lonely == true)
		cout << "You don't have any friend.QQ" << endl;
	//Input();
}

void Personality::setGroup(string &grp) {
    group = grp;
}
string Personality::getGroup() {
    return group;
}
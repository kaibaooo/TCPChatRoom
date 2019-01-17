#pragma once
#ifndef PERSONALITY_H
#define PERSONALITY_H

#include"AllMember.h"

using namespace std;

class Personality :public AllMember
{
public:
	void Addfriend(string); //(新增好友)
	void Deletefriend(string); //(刪除好友)
	//void Showfriendagree(); //(顯示好友確認)
	void Setstate(); //(設定個簽)
	void Showfriends(); //(顯示好友列表)
    void setGroup(string &);
    string getGroup();
    string group;
	string setstate; //(個人狀態)
	string friends[5] = {"0"}; //(好友列表)

};


#endif // !ALLMEMBER_H


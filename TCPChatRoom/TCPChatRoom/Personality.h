#pragma once
#ifndef PERSONALITY_H
#define PERSONALITY_H

#include"AllMember.h"

using namespace std;

class Personality :public AllMember
{
public:
	void Addfriend(string); //(�s�W�n��)
	void Deletefriend(string); //(�R���n��)
	//void Showfriendagree(); //(��ܦn�ͽT�{)
	void Setstate(); //(�]�w��ñ)
	void Showfriends(); //(��ܦn�ͦC��)
    void setGroup(string &);
    string getGroup();
    string group;
	string setstate; //(�ӤH���A)
	string friends[5] = {"0"}; //(�n�ͦC��)

};


#endif // !ALLMEMBER_H


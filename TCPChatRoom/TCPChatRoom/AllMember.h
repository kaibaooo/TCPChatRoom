#pragma once
#ifndef ALLMEMBER_H
#define ALLMEMBER_H

#include<iostream>
#include<string>

using namespace std;
class AllMember
{
public:
	
	//void Setaccount(string, string, string); //(�s�W�|��)
	void InitialSight();
	void Loadaccount(string); //(�n�J�|��)
	void Offaccount(string); //(�n�X�|��)
	void Showonline(); //(��ܽu�W���H)
	void Showallmember(); //(��ܩҦ��H)
	void Showinstruction(); //(��ܫ��O)
	void ShowEveryPersonalitySignature();//(��ܩҦ��H����ñ)�٨S�gXD


	//string Setaccount; //(�]�w�b��)
	//string Setpassword; //(�]�w�K�X)
	//string Setname; //(�]�w�W�r)
	//string Account; //(�b��)
	//string Password; //(�K�X)
	string Name; //(�W�l)
	//char allmemberaccount[5]; //(�����Ҧ��|���b�K�W��)
	string Allmember[5] = { "�i�t��","����M","���ͭ�","����T","�ڷQ�Y�b��" }; //(�Ҧ��|��)
	string Online[5] = { "0" }; //(�{�b�b�u�W���H)

};

#endif // !ALLMEMBER_H




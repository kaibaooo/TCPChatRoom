#pragma once
#ifndef ALLMEMBER_H
#define ALLMEMBER_H

#include<iostream>
#include<string>

using namespace std;
class AllMember
{
public:
	
	//void Setaccount(string, string, string); //(新增會員)
	void InitialSight();
	void Loadaccount(string); //(登入會員)
	void Offaccount(string); //(登出會員)
	void Showonline(); //(顯示線上的人)
	void Showallmember(); //(顯示所有人)
	void Showinstruction(); //(顯示指令)
	void ShowEveryPersonalitySignature();//(顯示所有人的個簽)還沒寫XD


	//string Setaccount; //(設定帳號)
	//string Setpassword; //(設定密碼)
	//string Setname; //(設定名字)
	//string Account; //(帳號)
	//string Password; //(密碼)
	string Name; //(名子)
	//char allmemberaccount[5]; //(紀錄所有會員帳密名稱)
	string Allmember[5] = { "張宇翔","潘彥霖","黃凱倫","邱思蓉","我想吃豚醬" }; //(所有會員)
	string Online[5] = { "0" }; //(現在在線上的人)

};

#endif // !ALLMEMBER_H




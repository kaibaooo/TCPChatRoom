#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Instruction {
public:
	void Input();
	void cutInput();
	void refresh();
	void ShowInstruction();
	//virtual void checkInstruction();//�]�����禡�A��@Personality
	void gotoxy(int, int);

protected:
	string original;
	vector<string> detail;
};
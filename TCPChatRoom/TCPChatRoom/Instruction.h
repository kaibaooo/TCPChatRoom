#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Instruction {
public:
	Instruction();
	~Instruction();
	void Input();
	void cutInput();
	void refresh();
	virtual void checkInstruction();//�]�����禡�A��@Personality
	void showformat();

protected:
	string original;
	vector<string> detail;


};
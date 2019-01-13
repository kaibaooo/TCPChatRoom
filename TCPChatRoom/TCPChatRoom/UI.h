#pragma once
#include"Client.h"
class UI : public Client{
    
public:
    UI();
    //users msgs
    void print(const char*);
    void printUsers(const char*);
    void printMsgQueue(const char* );
protected:

private:
    
};
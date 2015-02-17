#pragma once
#include<iostream>
#include "instructions.h"
using namespace std;
class stack
{
public:
	stack(void);
	~stack(void);
	int push(int x);
	int pop();
	int gettop();
	bool isempty();
	bool isfull();
	//int p;			//栈的自由指针
	//private: 
	int data[500];	//栈主体
	int top;		//栈顶
};


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
	//int p;			//ջ������ָ��
	//private: 
	int data[500];	//ջ����
	int top;		//ջ��
};


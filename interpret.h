#pragma once
#include"instructions.h"
#include "stack.h"
#include "file.h"
#include<fstream>
class interpret
{
public:
	interpret(void);
	~interpret(void);
	void start();
private:
	int base(int l, stack *s, int b);//Í¨¹ý²ã´Î²î£¬
};


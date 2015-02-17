#pragma once
#include <string>
using namespace std;
class uncertainadd
{
public:
	uncertainadd();
	~uncertainadd(void);
	uncertainadd(int,string s1);
	int codeadr;//指令中的地址
	string name;//要使用的名字
	string proc;//查询改名字的函数名
};


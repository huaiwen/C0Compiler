#pragma once
#include <string>
#include <iostream>
#include "Lex.h"
#include "instructions.h"
#include "nametable.h"
#include "uncertainadd.h"
#include "interpret.h"
#include<fstream>
using namespace std;
class Block
{
public:
	Block(void);
	~Block(void);
	void main();
	void inswriter();
	char inspri;
	char allstr;
private:
	int mainblock(int, bool*);//函数声明处理，从中调用变量声明处理	
	void init();//初始化
	void insprint();//中间代码打印
	int uncertain();
	int gen(enum fct, int, int);//生成指令
	int enter(enum object, int, int *);//登记名字表
	int position(string, object);//在名字表中查找标识符
	int variable(int, int *);//变量声明处理
	int statement(bool*);//语句
	int statements(bool*);//语句序列
	int expression(bool*);//表达式
	int term(bool*);//项
	int factor(bool*);//因子
	int test(bool*, bool*);//测试
	void symprint(symbol);
	void symcopy(bool*, bool*);

	interpret inter;//解释器
	Set ss;//集合
	Lex lex;//词法分析
	uncertainadd unadd[20];
	int pun;

	int tx;//名字表指针
	bool stabegsys[symnum];//语句开始符集
	bool facbegsys[symnum];//因子开始符集
	bool delbegsys[symnum];//定义开始符集

	bool terbegsys[symnum];//项开始符集
	bool expbegsys[symnum];//表达式开始符集
	bool varbegsys[symnum];//变量开始符集
	bool allfalse[symnum];//全部为false，用来初始化集合
	//指令数组
	int pcode;//指令指针
	string codechar[15];//指令枚举类型对应的字符类型
	nametable table[20];//名字表
	ins code[200];//中间代码表
	fstream error_txt;
};


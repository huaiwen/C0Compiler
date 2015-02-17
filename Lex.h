//常量声明，类型声明，获取源文件内容的一个类
#pragma once
#include<string>
#include "Set.h"
using namespace std;
const int symnum = 42;
enum symbol
{
	number, plu, sub, mul, dive, beginsym, endsym, varsym, intsym, ident, comma, semicolon,
	//数字，+，-，*，/，{，}，自定义函数，主函数，变量定义，整型，自定义符号，逗号，分号
	mainsym, voidsym, ifstasym, whilestasym, restasym, readstasym, writestasym,
	//分程序，主程序，空类型，语句序列，语句，如果语句，循环语句，赋值语句，返回语句，读语句，写语句，自定义函数调用语句
	ifsym, elsesym, whilesym, eqlsym, scanfsym, printfsym, leftsym, rightsym, nul, resym, period,
	//if,表达式，else,while,自定义函数调用，=,输入，输出，项，因子，( ,),未知,return,.
};

class Lex
{
public:
	Lex(void);
	~Lex(void);
	void getsym();
	int getSYM();
	string getstr();
	int readfile();
	symbol sym;  //符号
	string id;		//自定义符号
	int num;	  //值
	string str;
	string all;    //全部源文
private:
	int al;//自定义符号的最大长度
	char *a; /* 临时符号 */
	Set ss;
	fstream *in;
	char ch;		//单独判断
	int pos;//每次查找下一个单词时要起始的位置
	string word[9];
	symbol wsym[9];
	//enum symbol wsym[norw]; /* 保留字对应的符号值 */
	enum symbol ssym[256]; /* 单字符的符号值 */
	int star;//字符开始
	int end;//字符结束
	int len;//字符串长度
	int currentloc;//当前指向all哪一位置的指针
	void getch(int loc=-1);
};

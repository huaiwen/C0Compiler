#pragma once
#include <string>
using namespace std;
enum object
{
	var,
	procedur,
	intprocedur,
	//名字表中类型，变量，程序
};
class nametable
{
public:
	nametable();
	~nametable(void);
	nametable(string, int, int, string);//变量用  名字,值，层次,属于的函数
	nametable(string, int, string);//函数用  名字，层次，属于的函数
	string name;//名字
	enum object kind;//类型
	int level;//层次
	int adr;//地址
	int size;//大小
	string belongto;//属于哪个函数

};
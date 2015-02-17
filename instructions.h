#pragma once
enum fct
{
	LIT,
	LOD,
	STO,
	CAL,
	INT,
	JMP,
	JPC,
	ADD,
	SUB,
	MUL,
	DIV,
	RED,
	WRT,
	RET,
	NUL
};
class ins
{
public:
	ins(void);
	ins(enum fct, int, int);
	~ins(void);
	void set(enum fct, int, int);
public:
	enum fct f;				//虚拟机代码指令
	int l;					//引用层与声明层的层次差
	int a;					//根据f的不同而不同
};


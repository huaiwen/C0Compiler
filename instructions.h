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
	enum fct f;				//���������ָ��
	int l;					//���ò���������Ĳ�β�
	int a;					//����f�Ĳ�ͬ����ͬ
};


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
	int mainblock(int, bool*);//���������������е��ñ�����������	
	void init();//��ʼ��
	void insprint();//�м�����ӡ
	int uncertain();
	int gen(enum fct, int, int);//����ָ��
	int enter(enum object, int, int *);//�Ǽ����ֱ�
	int position(string, object);//�����ֱ��в��ұ�ʶ��
	int variable(int, int *);//������������
	int statement(bool*);//���
	int statements(bool*);//�������
	int expression(bool*);//���ʽ
	int term(bool*);//��
	int factor(bool*);//����
	int test(bool*, bool*);//����
	void symprint(symbol);
	void symcopy(bool*, bool*);

	interpret inter;//������
	Set ss;//����
	Lex lex;//�ʷ�����
	uncertainadd unadd[20];
	int pun;

	int tx;//���ֱ�ָ��
	bool stabegsys[symnum];//��俪ʼ����
	bool facbegsys[symnum];//���ӿ�ʼ����
	bool delbegsys[symnum];//���忪ʼ����

	bool terbegsys[symnum];//�ʼ����
	bool expbegsys[symnum];//���ʽ��ʼ����
	bool varbegsys[symnum];//������ʼ����
	bool allfalse[symnum];//ȫ��Ϊfalse��������ʼ������
	//ָ������
	int pcode;//ָ��ָ��
	string codechar[15];//ָ��ö�����Ͷ�Ӧ���ַ�����
	nametable table[20];//���ֱ�
	ins code[200];//�м�����
	fstream error_txt;
};


//����������������������ȡԴ�ļ����ݵ�һ����
#pragma once
#include<string>
#include "Set.h"
using namespace std;
const int symnum = 42;
enum symbol
{
	number, plu, sub, mul, dive, beginsym, endsym, varsym, intsym, ident, comma, semicolon,
	//���֣�+��-��*��/��{��}���Զ��庯�������������������壬���ͣ��Զ�����ţ����ţ��ֺ�
	mainsym, voidsym, ifstasym, whilestasym, restasym, readstasym, writestasym,
	//�ֳ��������򣬿����ͣ�������У���䣬�����䣬ѭ����䣬��ֵ��䣬������䣬����䣬д��䣬�Զ��庯���������
	ifsym, elsesym, whilesym, eqlsym, scanfsym, printfsym, leftsym, rightsym, nul, resym, period,
	//if,���ʽ��else,while,�Զ��庯�����ã�=,���룬���������ӣ�( ,),δ֪,return,.
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
	symbol sym;  //����
	string id;		//�Զ������
	int num;	  //ֵ
	string str;
	string all;    //ȫ��Դ��
private:
	int al;//�Զ�����ŵ���󳤶�
	char *a; /* ��ʱ���� */
	Set ss;
	fstream *in;
	char ch;		//�����ж�
	int pos;//ÿ�β�����һ������ʱҪ��ʼ��λ��
	string word[9];
	symbol wsym[9];
	//enum symbol wsym[norw]; /* �����ֶ�Ӧ�ķ���ֵ */
	enum symbol ssym[256]; /* ���ַ��ķ���ֵ */
	int star;//�ַ���ʼ
	int end;//�ַ�����
	int len;//�ַ�������
	int currentloc;//��ǰָ��all��һλ�õ�ָ��
	void getch(int loc=-1);
};

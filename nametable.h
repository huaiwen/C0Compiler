#pragma once
#include <string>
using namespace std;
enum object
{
	var,
	procedur,
	intprocedur,
	//���ֱ������ͣ�����������
};
class nametable
{
public:
	nametable();
	~nametable(void);
	nametable(string, int, int, string);//������  ����,ֵ�����,���ڵĺ���
	nametable(string, int, string);//������  ���֣���Σ����ڵĺ���
	string name;//����
	enum object kind;//����
	int level;//���
	int adr;//��ַ
	int size;//��С
	string belongto;//�����ĸ�����

};
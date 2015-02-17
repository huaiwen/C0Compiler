#include "Lex.h"
#include<fstream>
#include <iostream>
using namespace std;

Lex::Lex(void)
{
	pos = 0;
	//int void main if while return scanf printf 
	//�ؼ��֣���ĸ˳�����򣬶�����
	word[0] = "else";
	word[1] = "if";
	word[2] = "int";
	word[3] = "main";
	word[4] = "printf";
	word[5] = "return";
	word[6] = "scanf";
	word[7] = "void";
	word[8] = "while";

	wsym[0] = elsesym;
	wsym[1] = ifsym;
	wsym[2] = intsym;
	wsym[3] = mainsym;
	wsym[4] = printfsym;
	wsym[5] = resym;
	wsym[6] = scanfsym;
	wsym[7] = voidsym;
	wsym[8] = whilesym;
}
Lex::~Lex(void)
{
}

void Lex::getsym()//��һ������
{
	//string str;
	str = getstr();
	if (str == "")
	{
		sym = period;
		return;
	}
	int i = 0;
	ch = str[i];
	if (ch >= 'a' && ch <= 'z')//�����֣��Զ����
	{
		while ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
		{
			i++;
			ch = str[i];
			if (i > 30){ return; }//��ʶ��̫��
		}
		pos = star + i;
		if (all[pos] == ' ')pos++;
		//id = str.substr(0,i);
		id = str.substr(0, pos - star);
		i = 0;
		int j = 8;
		int k;
		do //���ֲ���
		{
			k = (i + j) / 2;
			if (id.compare(word[k]) <= 0)
			{
				j = k - 1;
			}
			if (id.compare(word[k]) >= 0)
			{
				i = k + 1;
			}
		} while (i <= j);
		if (i - 1 > j)
		{
			sym = wsym[k];
			//cout<<word[k]<<endl;
		}
		else
		{
			sym = ident;
			id = str.substr(0, pos - star);
		}
	}
	else
	{
		if (ch >= '0' && ch <= '9')//����
		{
			while (ch >= '0' && ch <= '9')
			{
				i++;
				ch = str[i];
				if (i > 10){ return; }//̫��
			}
			pos = star + i;
			sym = number;
			str = str.substr(0, i);
			num = atoi(str.c_str());
		}
		else
		{
			switch (ch)
			{
			case ',':sym = comma; break;
			case ';':sym = semicolon; break;
			case '+':sym = plu; break;
			case '-':sym = sub; break;
			case '*':sym = mul; break;
			case '/':sym = dive; break;
			case '{':sym = beginsym; break;
			case '}':sym = endsym; break;
			case '(':sym = leftsym; break;
			case ')':sym = rightsym; break;
			case '=':sym = eqlsym; break;
			case '.':sym = period; return;
			default:sym = nul; cout << "δ�ҵ��˷���" << endl;
				break;
			}
			pos = star + 1;
			if (all[pos] == ' ')pos++;
		}
	}
}
string Lex::getstr()
{
	while (all[pos] == ' '||all[pos]=='\t'||all[pos]=='\n')
	{
		pos++;
	}
	star = pos;
	end = all.find(' ', pos);//���ؿո���±�
	len = end - star;
	pos = end + 1;
	string temp = all.substr(star, len);
	return temp;
}
int Lex::readfile()//����c0Դ���ļ�
{
	fstream in;
	string s;
	cout << "������C0��Դ�����ļ�����" << endl;
	cin >> s;
	in.open(s, ios::in);//�ļ���
	if (!in)
	{
		cout <<s<< " �ļ������ڣ�" << endl;
		return -1;
	}
	while (getline(in, s))//�����س��ͻ���
	{
		if (s == "" || s == "\n")continue;
		all += s;
		all += '\n';
	}
	in.close();
	return 0;
}

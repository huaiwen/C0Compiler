#include "file.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
file::file(void)
{
}
file::~file(void)
{
}
int file::read(ins code[200])
{
	char buffer[80];
	fstream out;
	out.open("code.txt", ios::in);
	//if (out == NULL)
	//{
	//	cout<<"code文件不存在"<<endl;
	//	return -1;
	//}
	int ii = 0;
	while (!out.eof())
	{
		out.getline(buffer, 80, '\n');
		char cmd[50], str[50];
		int lev;
		int val;
		int k = 0, m = 0;
		int len = strlen(buffer);
		buffer[len] = ' ';
		buffer[len + 1] = '\0';
		for (unsigned int i = 0; i < strlen(buffer); i++)
		{
			if (buffer[i] == ' ')
			{
				str[m] = '\0';
				switch (k)
				{
				case 1:
					strcpy_s(cmd, str);
					break;
				case 2:
					lev = atoi(str);
					break;
				case 3:
					val = atoi(str);
					k = 0;
					break;
				}
				m = 0;
				strcpy_s(str, "");
				k++;
			}
			else
				str[m++] = buffer[i];
		}
		if (!strcmp("LIT", cmd))
			code[ii].f = LIT;
		if (!strcmp("LOD", cmd))
			code[ii].f = LOD;
		if (!strcmp("STO", cmd))
			code[ii].f = STO;
		if (!strcmp("CAL", cmd))
			code[ii].f = CAL;
		if (!strcmp("INT", cmd))
			code[ii].f = INT;
		if (!strcmp("JMP", cmd))
			code[ii].f = JMP;
		if (!strcmp("JPC", cmd))
			code[ii].f = JPC;
		if (!strcmp("JMP", cmd))
			code[ii].f = JMP;
		if (!strcmp("ADD", cmd))
			code[ii].f = ADD;
		if (!strcmp("SUB", cmd))
			code[ii].f = SUB;
		if (!strcmp("MUL", cmd))
			code[ii].f = MUL;
		if (!strcmp("DIV", cmd))
			code[ii].f = DIV;
		if (!strcmp("RED", cmd))
			code[ii].f = RED;
		if (!strcmp("WRT", cmd))
			code[ii].f = WRT;
		if (!strcmp("RET", cmd))
			code[ii].f = RET;
		if (!strcmp("NUL", cmd))
			code[ii].f = NUL;
		code[ii].l = lev;
		code[ii].a = val;
		ii++;
	}
	out.close();
	return 0;
}
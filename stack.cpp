#include "stack.h"
stack::stack(void)
{
	top = -1;
}
stack::~stack(void)//��������
{
}
int stack::push(int x)          //��ջ����
{
	top++;
	if (top >= 500)
	{
		cout << "ջ���� !" << endl;
		return -99999999;
	}
	data[top] = x;
	return data[top];
}
int stack::pop()          //��ջ����
{
	top--;
	if (top < 0)
	{
		cout << "ջ����!" << endl;
		return -99999999;
	}
	return data[top + 1];
}
int stack::gettop()//�õ�ջ��Ԫ�� 
{
	return data[top];
}

bool stack::isempty()//�ж��Ƿ�Ϊ�� 
{
	return top == -1 ? true : false;
}
bool stack::isfull()//�ж��Ƿ����� 
{
	return top > 500 ? true : false;
}
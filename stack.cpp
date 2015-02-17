#include "stack.h"
stack::stack(void)
{
	top = -1;
}
stack::~stack(void)//Îö¹¹º¯Êı
{
}
int stack::push(int x)          //ÈëÕ»º¯Êı
{
	top++;
	if (top >= 500)
	{
		cout << "Õ»ÂúÀ² !" << endl;
		return -99999999;
	}
	data[top] = x;
	return data[top];
}
int stack::pop()          //³öÕ»º¯Êı
{
	top--;
	if (top < 0)
	{
		cout << "Õ»ÏÂÒç!" << endl;
		return -99999999;
	}
	return data[top + 1];
}
int stack::gettop()//µÃµ½Õ»¶¥ÔªËØ 
{
	return data[top];
}

bool stack::isempty()//ÅĞ¶ÏÊÇ·ñÎª¿Õ 
{
	return top == -1 ? true : false;
}
bool stack::isfull()//ÅĞ¶ÏÊÇ·ñÒÑÂú 
{
	return top > 500 ? true : false;
}
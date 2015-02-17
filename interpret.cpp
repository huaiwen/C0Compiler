#include "interpret.h"
#include<string>
#include<iostream>
using namespace std;
interpret::interpret(void)
{
}
interpret::~interpret(void)
{
}
int interpret::base(int l, stack *s, int b)//层次差，运行栈指针，当前函数数据域基址
{
	int bl;
	bl = b;
	while (l > 0)
	{
		//bl=s[bl];
		bl = s->data[bl];
		l--;
	}
	return bl;
}
void interpret::start()
{
	fstream inte;
	inte.open("result.txt", ios::out);
	ins code[200];//指令数组
	file f;
	if (f.read(code))
		return;
	int i = 0;//为code表的指针
	stack st;//运行栈
	stack *pst;//当前运行栈的指针
	pst = &st;
	int bas = 0;		//基址，当前函数的数据域基地址
	int a1, a2;
	int temp;
	while (i >= 0)//不停的取code的下一个元素
	{
		if (i >= 200)
		{
			cout << "指令下标越界!" << endl;
			inte << "指令下标越界!" << "\n";
			return;
		}
		switch (code[i].f)
		{
		default:cout << "指令中出现非法符号!" << endl;
			return;
		case LIT://将常数值取到栈顶，a为常数值
			st.push(code[i].a);
			break;
		case LOD://将变量值取到栈顶，a为相对地址，t为层数
			st.push(st.data[base(code[i].l, pst, bas) + code[i].a]);
			break;
		case STO://将栈顶内容送入某变量单元中，a为相对地址，t为层数
			st.data[base(code[i].l, pst, bas) + code[i].a] = st.pop();
			break;
		case CAL://调用函数，a为函数地址
		{
					 st.push(base(code[i].l, pst, bas));//静态链，谁定义的
					 st.push(bas);//动态链，谁调用的
					 st.push(i + 1);//父过程下一步要执行的code数组指令
					 bas = st.top - 2;
					 //st.top += code[i].a;
					 i = code[i].a;//跳到的code数组地址
					 i--;//底下写了i++
					 break;
		}
		case INT://在运行栈中为被调用的过程开辟a个单元的数据区
		{
					 if (bas == 0)//public的时候
					 {
						 temp = code[i].a;
						 while (temp > 0)
						 {
							 st.push(-2);
							 temp--;
							 if (st.isfull())return;
						 }
					 }
					 else//函数调用过来的
					 {
						 temp = code[i].a - 3;//不用再压三个sl，tl，ra了
						 while (temp > 0)
						 {
							 st.push(-2);
							 temp--;
							 if (st.isfull())return;
						 }
					 }
					 break;
		}
		case JMP://无条件跳转至a地址
			i = code[i].a;
			i--;
			break;
		case JPC://条件跳转，当栈顶值为0，则跳转至a地址，否则顺序执行
			if (st.gettop() == 0)
			{
				i = code[i].a;
				i--;
			}
			break;
		case ADD://次栈顶与栈顶相加，退两个栈元素，结果值进栈
			a1 = st.pop();
			a2 = st.pop();
			st.push(a2 + a1);
			break;
		case SUB://次栈顶减去栈顶，退两个栈元素，结果值进栈
			a1 = st.pop();
			a2 = st.pop();
			//cout << "  栈顶的值是"<<a2-a1;
			st.push(a2 - a1);
			break;
		case MUL://次栈顶乘以栈顶，退两个栈元素，结果值进栈
			a1 = st.pop();
			a2 = st.pop();
			st.push(a2*a1);
			break;
		case DIV://次栈顶除以栈顶，退两个栈元素，结果值进栈
			a1 = st.pop();
			a2 = st.pop();
			st.push(a2 / a1);
			break;
		case RED://从命令行读入一个输入置于栈顶
			inte << "请输入!" << "\n";
			cout << "请输入：";
			cin >> a1;
			inte << a1 << "\n";
			st.push(a1);
			break;
		case WRT://栈顶值输出至屏幕并换行
		{
					 int temp_pop = st.pop();
					 cout << temp_pop << endl;
					 inte << temp_pop << "\n";
					 break;
		}
		case RET://函数调用结束后,返回调用点并退栈
		{
					 int temp = i;
					 st.data[bas] = st.gettop();//将st.data(top)赋值给data(bas)，把当前函数栈顶的值给  位于 这个函数数据域基址位置上的 单元
					 st.top = bas;//栈顶指针下移。
					
					 i = st.data[st.top + 2];//刚刚，调用的时候，存进去的父函数的即将执行的下一条指令
					 i--;//抵消i++的
					 bas = st.data[st.top + 1];//刚刚调用的时候，填入的父函数的bas指针
					 //
					 if (code[temp].a == 0)//void
					 {
						 st.top--;
					 }
					 break;
		}
		case NUL://cout<<"符号位NULL!"<<endl;
			break;
		}
		if (code[i].f == NUL)
		{
			break;
		}
		i++;
	}
	cout << "执行完毕!" << endl;
	inte <<  "执行完毕!" << "\n";
	inte.close();
}
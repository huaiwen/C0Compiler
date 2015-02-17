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
int interpret::base(int l, stack *s, int b)//��β����ջָ�룬��ǰ�����������ַ
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
	ins code[200];//ָ������
	file f;
	if (f.read(code))
		return;
	int i = 0;//Ϊcode���ָ��
	stack st;//����ջ
	stack *pst;//��ǰ����ջ��ָ��
	pst = &st;
	int bas = 0;		//��ַ����ǰ���������������ַ
	int a1, a2;
	int temp;
	while (i >= 0)//��ͣ��ȡcode����һ��Ԫ��
	{
		if (i >= 200)
		{
			cout << "ָ���±�Խ��!" << endl;
			inte << "ָ���±�Խ��!" << "\n";
			return;
		}
		switch (code[i].f)
		{
		default:cout << "ָ���г��ַǷ�����!" << endl;
			return;
		case LIT://������ֵȡ��ջ����aΪ����ֵ
			st.push(code[i].a);
			break;
		case LOD://������ֵȡ��ջ����aΪ��Ե�ַ��tΪ����
			st.push(st.data[base(code[i].l, pst, bas) + code[i].a]);
			break;
		case STO://��ջ����������ĳ������Ԫ�У�aΪ��Ե�ַ��tΪ����
			st.data[base(code[i].l, pst, bas) + code[i].a] = st.pop();
			break;
		case CAL://���ú�����aΪ������ַ
		{
					 st.push(base(code[i].l, pst, bas));//��̬����˭�����
					 st.push(bas);//��̬����˭���õ�
					 st.push(i + 1);//��������һ��Ҫִ�е�code����ָ��
					 bas = st.top - 2;
					 //st.top += code[i].a;
					 i = code[i].a;//������code�����ַ
					 i--;//����д��i++
					 break;
		}
		case INT://������ջ��Ϊ�����õĹ��̿���a����Ԫ��������
		{
					 if (bas == 0)//public��ʱ��
					 {
						 temp = code[i].a;
						 while (temp > 0)
						 {
							 st.push(-2);
							 temp--;
							 if (st.isfull())return;
						 }
					 }
					 else//�������ù�����
					 {
						 temp = code[i].a - 3;//������ѹ����sl��tl��ra��
						 while (temp > 0)
						 {
							 st.push(-2);
							 temp--;
							 if (st.isfull())return;
						 }
					 }
					 break;
		}
		case JMP://��������ת��a��ַ
			i = code[i].a;
			i--;
			break;
		case JPC://������ת����ջ��ֵΪ0������ת��a��ַ������˳��ִ��
			if (st.gettop() == 0)
			{
				i = code[i].a;
				i--;
			}
			break;
		case ADD://��ջ����ջ����ӣ�������ջԪ�أ����ֵ��ջ
			a1 = st.pop();
			a2 = st.pop();
			st.push(a2 + a1);
			break;
		case SUB://��ջ����ȥջ����������ջԪ�أ����ֵ��ջ
			a1 = st.pop();
			a2 = st.pop();
			//cout << "  ջ����ֵ��"<<a2-a1;
			st.push(a2 - a1);
			break;
		case MUL://��ջ������ջ����������ջԪ�أ����ֵ��ջ
			a1 = st.pop();
			a2 = st.pop();
			st.push(a2*a1);
			break;
		case DIV://��ջ������ջ����������ջԪ�أ����ֵ��ջ
			a1 = st.pop();
			a2 = st.pop();
			st.push(a2 / a1);
			break;
		case RED://�������ж���һ����������ջ��
			inte << "������!" << "\n";
			cout << "�����룺";
			cin >> a1;
			inte << a1 << "\n";
			st.push(a1);
			break;
		case WRT://ջ��ֵ�������Ļ������
		{
					 int temp_pop = st.pop();
					 cout << temp_pop << endl;
					 inte << temp_pop << "\n";
					 break;
		}
		case RET://�������ý�����,���ص��õ㲢��ջ
		{
					 int temp = i;
					 st.data[bas] = st.gettop();//��st.data(top)��ֵ��data(bas)���ѵ�ǰ����ջ����ֵ��  λ�� ��������������ַλ���ϵ� ��Ԫ
					 st.top = bas;//ջ��ָ�����ơ�
					
					 i = st.data[st.top + 2];//�ոգ����õ�ʱ�򣬴��ȥ�ĸ������ļ���ִ�е���һ��ָ��
					 i--;//����i++��
					 bas = st.data[st.top + 1];//�ոյ��õ�ʱ������ĸ�������basָ��
					 //
					 if (code[temp].a == 0)//void
					 {
						 st.top--;
					 }
					 break;
		}
		case NUL://cout<<"����λNULL!"<<endl;
			break;
		}
		if (code[i].f == NUL)
		{
			break;
		}
		i++;
	}
	cout << "ִ�����!" << endl;
	inte <<  "ִ�����!" << "\n";
	inte.close();
}
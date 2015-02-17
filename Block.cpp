#include "Block.h"
Block::Block(void)
{
}
Block::~Block(void)
{
}
void Block::init()
{
	tx = 1;
	pcode = 1;
	pun = 0;
	int i;
	table[0].name = "";//当成全局变量
	table[0].level = 5;
	///////////////////////////
	table[1].name = "public";
	table[1].level = 0;
	//////////////////////////
	code[0].f = JMP;//code第一个 jump
	code[0].l = 0;
	code[0].a = 0;
	/////////////////////////
	codechar[LIT] = "LIT";//指令枚举类型对应的字符类型
	codechar[LOD] = "LOD";
	codechar[STO] = "STO";
	codechar[CAL] = "CAL";
	codechar[INT] = "INT";
	codechar[JMP] = "JMP";
	codechar[JPC] = "JPC";
	codechar[ADD] = "ADD";
	codechar[SUB] = "SUB";
	codechar[MUL] = "MUL";
	codechar[DIV] = "DIV";
	codechar[RED] = "RED";
	codechar[WRT] = "WRT";
	codechar[RET] = "RET";
	codechar[NUL] = "NUL";
	//////////////////////////
	for (i = 0; i < symnum; i++)
	{
		stabegsys[i] = false;
		facbegsys[i] = false;
		delbegsys[i] = false;
		terbegsys[i] = false;
		expbegsys[i] = false;
		varbegsys[i] = false;
		allfalse[i] = false;
	}
	/////////////////////////
	//声明开始符 int void
	delbegsys[intsym] = true;
	delbegsys[voidsym] = true;
	/////////////////////////
	//语句开始符
	stabegsys[ifsym] = true;
	stabegsys[whilesym] = true;
	stabegsys[ident] = true;
	stabegsys[resym] = true;
	stabegsys[scanfsym] = true;
	stabegsys[printfsym] = true;
	stabegsys[beginsym] = true;
	/////////////////////////
	//因子开始符
	facbegsys[ident] = true;
	facbegsys[leftsym] = true;
	facbegsys[number] = true;
	//////////////////////////
	//项开始符集
	terbegsys[ident] = true;
	terbegsys[leftsym] = true;
	terbegsys[number] = true;
	////////////////////////////
	//表达式开始符集
	expbegsys[plu] = true;
	expbegsys[sub] = true;
	expbegsys[ident] = true;
	expbegsys[leftsym] = true;
	expbegsys[number] = true;
	//////////////////////////////
	//变量开始符集
	varbegsys[intsym] = true;
	//////////////////////////////
	//找不到这个函数，将这个函数存到unadd数组里，最后对这个数组进行处理
	for (i = 0; i < 20; i++)
	{
		unadd[i].codeadr = -1;
		unadd[i].name = "";
		unadd[i].proc = "";
	}
	while (lex.readfile())//读c0源文件
	{
		cout << "请重新输入文件名：" << endl;
	}
}
int Block::mainblock(int lev, bool* fsys)//层次，当前状态符号集
{
	int dx;//相对地址
	int tx0;//保留此程序最开始名字表位置
	int pcode0;//保留此程序最开始指令位置
	bool nxtlev[symnum];//向下传的符号集

	dx = 3;
	tx0 = tx;//名字表指针

	lex.getsym();//读一个单词

	if (lex.sym == period)//遇到结束符则结束
	{
		return 0;
	}

	symcopy(fsys, nxtlev);
	while (delbegsys[lex.sym])//声明  变量，函数，直至所有声明全部解析
	{
		if (lex.sym == intsym)//变量或者自定义函数
		{
			lex.getsym();//是ident

			fsys[ident] = true;
			fsys[beginsym] = true;
			if (test(fsys, delbegsys))
			{
				cout << table[tx0].name;
				cout << " 中声明开始含非法符号" << endl;
				error_txt << table[tx0].name << " 中声明开始含非法符号" << "\n";
				return -1;
			}
			switch (lex.sym)
			{
			case ident:
				break;//没出错
			case beginsym:
			{
							 cout << table[tx0].name;
							 cout << " 中声明错误" << endl;
							 error_txt << table[tx0].name << " 中声明错误" << "\n";
							 lex.getsym();
							 continue;
							 break;
			}
			default:
			{
					   cout << table[tx0].name;
					   cout << " 中声明错误" << endl;
					   error_txt << table[tx0].name << " 中声明错误" << "\n";
					   //lex.getsym();
			}
				continue;
				break;
			}
			fsys[ident] = false;
			fsys[beginsym] = false;
			//int x(){    int x,x;
			lex.getsym();//可能是（  或者逗号 或者分号 或者等号  不是(   认为不是函数
			if (lex.sym == leftsym)//左括号的话 是函数
			{
				string s1 = lex.id;//存下函数名字
				fsys[rightsym] = true;
				fsys[beginsym] = true;
				lex.getsym();//右括号

				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " 中声明开始含非法符号" << endl;
					error_txt << table[tx0].name << " 中声明开始含非法符号" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case rightsym:break;//(){   ,x;
				case beginsym:
				{
								 cout << table[tx0].name;
								 cout << " 中函数缺少右括号" << endl;
								 error_txt << table[tx0].name << " 中函数缺少右括号" << "\n";
								 lex.getsym();
								 continue;
								 break;
				}
				default:
				{
						   cout << table[tx0].name;
						   cout << " 中声明错误" << endl;
						   error_txt << table[tx0].name << " 中声明错误" << "\n";
						   //lex.getsym();
						   continue;
						   break;
				}
				}
				lex.getsym();//左花括号 {
				fsys[rightsym] = false;
				//fsys[beginsym] = false;
				fsys[beginsym] = true;
				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " 中声明开始含非法符号" << endl;
					error_txt << table[tx0].name << " 中声明开始含非法符号" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case beginsym:break;
				default:
				{
						   cout << table[tx0].name;
						   cout << " 中缺少开始符" << endl;
						   error_txt << table[tx0].name << " 中缺少开始符" << "\n";
						   //lex.getsym();
						   continue;
						   break;
				}
				}
				fsys[beginsym] = false;

				enter(intprocedur, lev, &dx);//函数登陆名字表
				table[tx].belongto = table[tx0].name;
				table[tx].name = s1;
				if (-1 == mainblock(lev + 1, nxtlev))
				{
					return -1;
				}
				//正确出来的话肯定是  }
				lex.getsym();		//接下来找声明
				continue;
			}
			else//不是左括号，是变量
			{
				while (1)
				{
					if (lex.sym == comma)//逗号
					{
						variable(lev, &dx);//登陆名字表，并再读一个字，tx变了
						table[tx].belongto = table[tx0].name;//多个函数可以定义相同名字的变量，但belongto 可以讲他们区别开
						//cout<<table[tx].name<<" "<<table[tx].level<<""<<table[tx].belongto<<endl;
						lex.getsym();//再读一个字
						continue;
					}
					if (lex.sym == semicolon)
					{
						variable(lev, &dx);//登陆名字表，并再读一个字，tx变了
						table[tx].belongto = table[tx0].name;//多个函数可以定义相同名字的变量，但belongto 可以讲他们区别开
						//cout<<table[tx].name<<" "<<table[tx].level<<""<<table[tx].belongto<<endl;
						break;
					}
					if (lex.sym == eqlsym)
					{
						variable(lev, &dx);
						//table[tx].val = lex.num;
						table[tx].belongto = table[tx0].name;
						expression(fsys);
						//cout<<"11"<<endl;
						if (gen(STO, 0, dx - 1) == -1)return -1;
						{
							lex.getsym();//ident
							lex.getsym();//逗号或分号
						}
						if (lex.sym == semicolon)
							break;
					}
					if (lex.sym == ident)//int a b
					{
						cout << table[tx0].name;
						cout << " 中 " << lex.id << " *之前缺少逗号" << endl;
						error_txt << table[tx0].name << " 中 " << lex.id << " *之前缺少逗号" << "\n";
						variable(lev, &dx);
						table[tx].belongto = table[tx0].name;
						//lex.getsym();//
					}
					else
					{
						cout << table[tx0].name;
						cout << " 中 " << lex.id << " *后有非法符号" << endl;
						error_txt << table[tx0].name << " 中 " << lex.id << " *后有非法符号" << "\n";
						symcopy(allfalse, nxtlev);
						//nxtlev[period] = true;
						nxtlev[semicolon] = true;
						//nxtlev[endsym] = true;
						nxtlev[ident] = true;
						if (test(delbegsys, nxtlev))
							break;						//后跟符，  .  ;  }    test要有个停止条件
						//找声明开始符，找到了则仍进入大循环，找不到就进入其他的
						if (lex.sym == intsym || lex.sym == voidsym)
							break;
					}
				}
				continue;
			}

		}


		if (lex.sym == voidsym)//自定义函数或者主函数
		{
			lex.getsym();
			if (lex.sym != mainsym  && lex.sym != ident)
			{
				cout << table[tx0].name;
				cout << " 中 " << lex.id << "声明错误" << endl;
				error_txt << table[tx0].name << " 中 " << lex.id << " 声明错误" << "\n";
				fsys[beginsym] = true;
				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " 中声明开始含非法符号" << endl;
					error_txt << table[tx0].name << " 中声明开始含非法符号"<< "\n";
					return -1;
				}
				fsys[beginsym] = false;
				switch (lex.sym)
				{
				case beginsym:
					cout << table[tx0].name;
					cout << " 中void函数声明错误" << endl;
					error_txt << table[tx0].name << " 中void函数声明错误" << "\n";
					continue;
					break;
				default:
					cout << table[tx0].name;
					cout << " 中void函数声明错误" << endl;
					cout << " 中void函数缺少开始符" << endl;
					error_txt << table[tx0].name << " 中void函数声明错误" << "\n";
					error_txt << table[tx0].name << " 中void函数缺少开始符" << "\n";
					continue;
					break;
				}
			}
			if (lex.sym == mainsym)//主函数
			{
				string s1 = lex.id;
				/*if (lex.sym != leftsym)
				{
				cout<<table[tx0].name;
				cout<<" 中缺少左括号"<<endl;
				}

				symcopy(allfalse,nxtlev);
				//symcopy(stabegsys,nxtlev);
				ss.addset(nxtlev,delbegsys,stabegsys,symnum);
				nxtlev[beginsym] = true;
				nxtlev[rightsym] = true;
				nxtlev[endsym] = true;
				if(test(delbegsys,nxtlev))
				{
				cout<<table[tx0].name;
				cout<<" 中main函数定义错误"<<endl;
				return -1;
				}//如果找不到声明，语句 {  函数错误，返回
				if (lex.sym == intsym || lex.sym == voidsym)
				{
				cout<<table[tx0].name;
				cout<<" 中缺少右括号"<<endl;
				cout<<" 中缺少开始括号"<<endl;
				continue;
				}
				if (lex.sym == endsym)
				{
				cout<<table[tx0].name;
				cout<<" 中缺少右括号"<<endl;
				cout<<" 中缺少开始括号"<<endl;

				if(test(delbegsys,stabegsys))
				{
				cout<<table[tx0].name;
				cout<<" 中main函数定义错误"<<endl;
				return -1;
				}
				}
				/*if (lex.sym != beginsym)
				{
				cout<<table[tx0].name;
				cout<<" 中缺少开始括号!"<<endl;
				}*/
				/*if (lex.sym != rightsym)
				{
				cout<<table[tx0].name;
				cout<<" 中缺少右括号"<<endl;
				if (lex.sym != beginsym)
				{
				cout<<table[tx0].name;
				cout<<" 中缺少开始括号"<<endl;
				}
				}
				//lex.getsym();
				symcopy(allfalse,nxtlev);
				//znxtlev[]f
				if(test(delbegsys,stabegsys))
				{
				cout<<table[tx0].name;
				cout<<" 中main函数定义错误"<<endl;
				return -1;
				}
				if (lex.sym != beginsym)
				{
				cout<<table[tx0].name;
				cout<<" 中缺少开始括号"<<endl;
				}*/
				fsys[leftsym] = true;
				fsys[beginsym] = true;
				lex.getsym();
				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " 中声明开始含非法符号" << endl;
					error_txt << table[tx0].name << " 中声明开始含非法符号" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case leftsym:break;//(){   ,x;
				case beginsym:
				{
								 cout << table[tx0].name;
								 cout << " 中main函数缺少左括号" << endl;
								 error_txt << table[tx0].name << " 中main函数缺少左括号" << "\n";
								 lex.getsym();
								 continue;
								 break;
				}
				default:
				{
						   cout << table[tx0].name;
						   cout << " 中声明错误" << endl;
						   error_txt << table[tx0].name << " 中声明错误" << "\n";
						   //lex.getsym();
						   continue;
						   break;
				}
				}


				lex.getsym();
				fsys[leftsym] = false;
				//fsys[beginsym] = false;
				fsys[rightsym] = true;
				fsys[beginsym] = true;
				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " 中声明开始含非法符号" << endl;
					error_txt << table[tx0].name << " 中声明开始含非法符号" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case rightsym:break;
				case beginsym:
				{
								 cout << table[tx0].name;
								 cout << " 中main函数缺少右括号" << endl;
								 error_txt << table[tx0].name << " 中main函数缺少右括号" << "\n";
								 lex.getsym();
								 continue;
								 break;
				}
				default:
				{
						   cout << table[tx0].name;
						   cout << " 中缺少开始符" << endl;
						   error_txt << table[tx0].name << " 中缺少开始符" << "\n";
						   //lex.getsym();
						   continue;
						   break;
				}
				}
				fsys[rightsym] = false;

				lex.getsym();
				fsys[beginsym] = true;
				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " 中声明开始含非法符号" << endl;
					error_txt << table[tx0].name << " 中声明开始含非法符号" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case beginsym:break;
				default:
				{
						   cout << table[tx0].name;
						   cout << " 中缺少开始符" << endl;
						   error_txt << table[tx0].name << " 中缺少开始符" << "\n";
						   //lex.getsym();
						   continue;
						   break;
				}
				}
				fsys[beginsym] = false;
				//lex.getsym();

				enter(procedur, lev, &dx);
				table[tx].belongto = table[tx0].name;
				table[tx].name = s1;
				if (-1 == mainblock(lev + 1, nxtlev))
				{
					return -1;
				}
				if (gen(RET, 0, 0) == -1)return -1;
				lex.getsym();
			}
			else//自定义函数
			{
				string s1 = lex.id;
				/*lex.getsym();
				if (lex.sym != leftsym)
				{
				cout<<table[tx0].name;
				cout<<" 中缺少左括号"<<endl;
				}

				symcopy(allfalse,nxtlev);
				ss.addset(nxtlev,delbegsys,stabegsys,symnum);
				nxtlev[beginsym] = true;
				nxtlev[rightsym] = true;
				nxtlev[endsym] = true;
				if(test(delbegsys,nxtlev))
				{
				cout<<table[tx0].name;
				cout<<" 中函数定义错误!"<<endl;
				return -1;
				}//如果找不到声明，语句 {  函数错误，返回
				if (lex.sym == intsym || lex.sym == voidsym)
				continue;
				if (lex.sym == endsym)
				return 0;
				/*if (lex.sym != beginsym)
				{
				cout<<table[tx0].name;
				cout<<" 中缺少开始括号!"<<endl;
				}*/
				/*if (lex.sym != rightsym)
				{
				cout<<table[tx0].name;
				cout<<" 中缺少右括号"<<endl;
				}
				if (lex.sym != beginsym)
				{
				cout<<table[tx0].name;
				cout<<" 中缺少开始括号"<<endl;
				}*/
				/*lex.getsym();
				if (lex.sym != rightsym)
				{
				cout<<"缺少右括号!"<<endl;
				return -1;
				}
				lex.getsym();
				if (lex.sym != beginsym)
				{
				cout<<"缺少开始括号!"<<endl;
				return -1;
				}*/


				fsys[leftsym] = true;
				fsys[beginsym] = true;
				lex.getsym();
				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " 中声明开始含非法符号" << endl;
					error_txt << table[tx0].name << " 中声明开始含非法符号" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case leftsym:break;//(){   ,x;
				case beginsym:
				{
								 cout << table[tx0].name;
								 cout << " 中函数缺少左括号" << endl;
								 error_txt << table[tx0].name << " 中函数缺少左括号" << "\n";
								 lex.getsym();
								 continue;
								 break;
				}
				default:
				{
						   cout << table[tx0].name;
						   cout << " 中声明错误" << endl;
						   error_txt << table[tx0].name << " 中声明错误" << "\n";
						   //lex.getsym();
						   continue;
						   break;
				}
				}


				lex.getsym();
				fsys[leftsym] = false;
				//fsys[beginsym] = false;
				fsys[rightsym] = true;
				fsys[beginsym] = true;
				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " 中声明开始含非法符号" << endl;
					error_txt << table[tx0].name << " 中声明开始含非法符号" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case rightsym:break;
				case beginsym:
				{
								 cout << table[tx0].name;
								 cout << " 中函数缺少右括号" << endl;
								 error_txt << table[tx0].name << " 中函数缺少右括号" << "\n";
								 lex.getsym();
								 continue;
								 break;
				}
				default:
				{
						   cout << table[tx0].name;
						   cout << " 中函数缺少开始符" << endl;
						   error_txt << table[tx0].name << " 中函数缺少开始符" << "\n";
						   //lex.getsym();
						   continue;
						   break;
				}
				}
				fsys[rightsym] = false;


				lex.getsym();
				fsys[beginsym] = true;
				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " 中声明开始含非法符号" << endl;
					error_txt << table[tx0].name << " 中声明开始含非法符号" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case beginsym:break;
				default:
				{
						   cout << table[tx0].name;
						   cout << " 中函数缺少开始符" << endl;
						   error_txt << table[tx0].name << " 中函数缺少开始符" << "\n";

						   //lex.getsym();
						   continue;
						   break;
				}
				}
				fsys[beginsym] = false;
				//lex.getsym();

				enter(procedur, lev, &dx);
				table[tx].belongto = table[tx0].name;
				table[tx].name = s1;
				if (-1 == mainblock(lev + 1, nxtlev))
				{
					return -1;
				}
				if (gen(RET, 0, 0) == -1)return -1;
				lex.getsym();
			}
		}

	}
	table[tx0].adr = pcode;//code表指针
	table[tx0].size = dx;//函数的大小，里边的变量
	pcode0 = pcode;
	if (tx0 == 0)
	{
		return 0;
	}

	if (gen(INT, 0, dx) == -1)return -1;//初始化，分配栈的变量空间
	table[0].adr = tx0;//将这个父过程名字表的下标，存入全局变量里
	if (table[tx0].name == "public")
	{
		code[0].a = pcode - 1;
		int i;
		i = position("main", procedur);
		gen(CAL, 0, table[i].adr);
		gen(RET, 0, 0);
		return 0;
	}


	if (table[tx0].kind == intprocedur)
	{
		table[0].level = 0;//如果是带返回类型的函数，尚不能确定  是否漏写ruturn，设一标志位，为0。
	}
	if (statements(nxtlev) == -1)return -1;//如果带返回类型函数写了return，则标志位置1
	if (lex.sym != endsym)
	{
		cout << table[tx0].name;
		cout << " 中函数缺少结束符" << endl;
		error_txt << table[tx0].name << " 中函数缺少结束符" << "\n";

	}
	if (table[tx0].kind == intprocedur)
	{
		if (table[0].level == 1)//如果带返回类型函数标志位为0，漏写return
		{
			table[0].level = 5;
			gen(RET, 0, 1);
			return 0;
		}
		else
		{
			cout << table[tx0].name;
			cout << " 中缺少return" << endl;
			error_txt << table[tx0].name << " 中缺少return" << "\n";

			return -1;
		}
	}
	return 0;
}
int Block::gen(fct x, int y, int z)
{
	if (pcode >= 300)
	{
		cout << "程序太长" << endl;
		error_txt << "程序太长" << endl;
		return -1;
	}
	code[pcode].f = x;
	code[pcode].l = y;
	code[pcode].a = z;
	pcode++;
	return 0;
}
int Block::enter(enum object k, int lev, int *pdx)
{
	tx++;
	//endtx++;
	table[tx].name = lex.id;
	table[tx].kind = k;
	//table[tx].level = lev;
	switch (k)
	{
	case var:
		table[tx].level = lev;
		table[tx].adr = (*pdx);
		(*pdx)++;
		break;
	case procedur:
		table[tx].level = lev;
		break;
	case intprocedur:
		table[tx].level = lev;
		break;
	default:
		break;
	}
	//cout<<table[tx].name<<" "<<table[tx].level<<endl;
	return 0;
}
int Block::position(string id, object k)
{//tx名字表尾  
	int i = tx;
	if (k == var)
	{
		while (i > 0)
		{
			if (table[i].name == id)
			{
				if (k == table[i].kind)
				{
					if (table[i].belongto == "public")
					{
						return i;
					}
					if (table[i].belongto == table[table[0].adr].name)
					{
						return i;
					}
				}
			}
			i--;
		}
		return 0;
	}
	else
	{
		while (i > 0)
		{
			if (table[i].name == id)
			{
				if (table[i].kind == intprocedur || table[i].kind == procedur)
				{
					if (table[i].belongto == "public")
					{
						return i;
					}
					if (table[i].belongto == table[table[0].adr].name)
					{
						return i;
					}
				}
			}
			i--;
		}
		//cin>>i;
		unadd[pun].codeadr = pcode;
		unadd[pun].name = id;
		unadd[pun].proc = table[table[0].adr].name;
		pun++;
		return 0;
	}
	return -1;

}
int Block::variable(int lev, int *pdx)
{
	enter(var, lev, pdx);
	lex.getsym();
	return 0;
}
int Block::statement(bool* fsys)//一条一条的分析
{
	if (lex.sym == semicolon)
	{
		lex.getsym();
	}
	bool nxtlev[symnum];

	int i;
	switch (lex.sym)
	{
	case ident://使用自定义变量 或者 使用自定义函数
	{

				   i = position(lex.id, var);//当成变量去查，如果查不到的话，不是函数，就是不存在
				   if (i != 0)//存在这样的变量
				   {
					  //// i = position(lex.id, var);//当变量查一查
					  // if (i == 0)//没查到这样的变量
					  // {
						 //  cout << table[table[0].adr].name;
						 //  cout << " 中引用了未定义变量" << lex.id << endl;
						 //  lex.getsym();
						 //  fsys[semicolon] = true;
						 //  if (test(fsys, stabegsys))
						 //  {
							//   cout << table[table[0].adr].name;
							//   cout << " 中含有非法符号" << endl;
							//   return -1;
						 //  }
						 //  fsys[semicolon] = false;
						 //  return 1;//走了
					  // }
					   lex.getsym();//再读一个
					   if (lex.sym == eqlsym)//赋值
					   {
						   lex.getsym();
						   ss.addset(fsys, expbegsys, fsys, symnum);
						   if (test(fsys, stabegsys))
						   {
							   cout << table[table[0].adr].name;
							   cout << " 中含有非法符号" << endl;
							   error_txt << table[table[0].adr].name << " 中含有非法符号" << "\n";

							   return -1;
						   }
						   ss.subset(fsys, expbegsys, fsys, symnum);

						   if (expression(nxtlev))//表达式处理，并再往下读一个字
						   {
							   cout << table[table[0].adr].name;
							   cout << " 赋值语句包含无效表达式" << endl;
							   error_txt << table[table[0].adr].name << " 赋值语句包含无效表达式" << "\n";


						   }

						   if (lex.sym != semicolon)
						   {
							   lex.getsym();
							   if (lex.sym != semicolon)
							   {
								   cout << table[table[0].adr].name;
								   cout << " 中缺少分号" << endl;
								   error_txt << table[table[0].adr].name << " 中缺少分号" << "\n";

								   if (test(fsys, stabegsys))
								   {
									   cout << table[table[0].adr].name;
									   cout << " 中含有非法符号" << endl;
									   error_txt << table[table[0].adr].name << " 中含有非法符号" << "\n";

									   return -1;
								   }
							   }
						   }
						   gen(STO, table[table[0].adr].level + 1 - table[i].level, table[i].adr);//算算结果，并赋值
						   //table[table[0].adr].level +1 - table[i].level
					   }
					   else//不是赋值，当成出错
					   {
						   if (test(fsys, stabegsys))
						   {
							   cout << table[table[0].adr].name;
							   cout << " 中出现非法符号" << endl;
							   error_txt << table[table[0].adr].name << " 中含有非法符号" << "\n";

							   return 1;
						   }
					   }

				   }
				   else//自定义函数
				   {
					   fsys[semicolon] = true;
					   lex.getsym();//读取左括号
					   switch (lex.sym)
					   {
					   case leftsym://是个函数，但不知道是不是定义过的，需要查

						   break;
					   case rightsym://是个函数，但不知道是不是定义过的，需要查，输出错误信息

						   break;
					   default://未定义变量
						   cout << "使用了未定义的变量" << endl;
						   error_txt << "使用了未定义的变量" << "\n";
						   return -1;
						   break;
					   }
					   if (lex.sym == leftsym)
					   {
						//	cout << "自定义函数调用" << endl;
						   	i = position(lex.id,procedur);//再次调用，查查看
						   //	if ( i!=0 )
						  // 	{
						//	  if (table[i].kind == procedur)
						//		{
						//	   cout << table[table[0].adr].name;
						//	   cout << " 中调用了一个无返回值的函数，若参与运算或者赋值，可能会发生错误" << endl;
						//		}
						//   }
						   gen(CAL, table[table[0].adr].level + 1 - table[i].level, table[i].adr);//函数调用
						   //table[table[0].adr].level +1 - table[i].level
						   lex.getsym();//右括号
						   if (lex.sym != rightsym)
						   {
							   cout << table[table[0].adr].name;
							   cout << " 中函数缺少右括号" << endl;
							   error_txt << table[table[0].adr].name << " 中函数缺少右括号" << "\n";

							   break;
						   }
						   lex.getsym();//在读一个
					   }
					   else
					   {
						   if (test(fsys, stabegsys))
						   {
							   cout << table[table[0].adr].name;
							   cout << " 中含有非法符号" << endl;
							   error_txt << table[table[0].adr].name << " 中含有非法符号" << "\n";

							   return -1;
						   }
						   if (lex.sym != semicolon)
						   {
							   cout << table[table[0].adr].name;
							   cout << " 中函数调用缺少分号" << endl;
							   error_txt << table[table[0].adr].name << " 中函数调用缺少分号" << "\n";

							   break;
						   }
						   lex.getsym();
					   }
				   }
	}

		break;
	case whilesym:
	{
					 lex.getsym();
					 if (lex.sym != leftsym)//while
					    {
						 cout << table[table[0].adr].name;
						 cout << " 中while缺少左括号" << endl;
						 error_txt << table[table[0].adr].name << " while缺少左括号" << "\n";

						 ss.addset(fsys, expbegsys, fsys, symnum);
						 fsys[beginsym] = true;
						 fsys[rightsym] = true;
						    if (test(fsys, stabegsys))
						   {
							 cout << table[table[0].adr].name;
							 cout << " 中含有非法符号" << endl;
							 error_txt << table[table[0].adr].name << " 中含有非法符号" << "\n";

							 return -1;
						    }
						 switch (lex.sym)
						    {
						     case rightsym:
								 lex.getsym();
								 break;
						     case beginsym:
										  cout << table[table[0].adr].name;
										  cout << " 中while缺少右括号" << endl;
										  error_txt << table[table[0].adr].name << " 中while缺少右括号" << "\n";

										  break;
						      default:
									cout << table[table[0].adr].name;
									cout << " 中while缺少右括号" << endl;
									error_txt << table[table[0].adr].name << " 中while缺少右括号" << "\n";

									//cout<<table[table[0].adr].name;
									//cout<<" 中while缺少右括号"<<endl;
									break;
						     }

						 if (lex.sym != beginsym)
						    {
							 cout << table[table[0].adr].name;
							 cout << " 中while缺少开始符" << endl;
							 error_txt << table[table[0].adr].name << " 中while缺少开始符" << "\n";

							 statements(fsys);
						    }
						 else
						    {
							 lex.getsym();
							 statements(fsys);
						     }
					    }
					 else//while(
					 {
						 lex.getsym();
						 if (!facbegsys[lex.sym])
						    {
							 cout << table[table[0].adr].name;
							 cout << " 中while缺少判断表达式" << endl;
							 error_txt << table[table[0].adr].name << " 中while缺少判断表达式" << "\n";

						     }
						    int i = pcode;
						    expression(fsys);//表达式处理
						    if (lex.sym != rightsym)
						    {
							 cout << table[table[0].adr].name;
							 cout << " 中while缺少右括号" << endl;
							 error_txt << table[table[0].adr].name << " 中while缺少右括号" << "\n";

							 fsys[beginsym] = true;
							    if (test(fsys, stabegsys))
							    {
								 cout << table[table[0].adr].name;
								 cout << " 中含有非法符号 " << endl;
								 error_txt << table[table[0].adr].name << " 中含有非法符号" << "\n";

								 return -1;
							    }
							    else
							    {
								 if (lex.sym != beginsym)
								   {
									 cout << table[table[0].adr].name;
									 cout << " 中while缺少开始符" << endl;
									 error_txt << table[table[0].adr].name << " 中while缺少开始符" << "\n";

									 statements(fsys);
								    }
								      else
								      {
										lex.getsym();
									    statements(fsys);
								       }
							    }
						    }
						 else//while(),是右括号
						 {
							 int jpc_pcode = pcode;
							 gen(JPC, 0, 0);
							 lex.getsym();
							 if (lex.sym != beginsym)
							    {
								 cout << table[table[0].adr].name;
								 cout << " 中while缺少开始符" << endl;
								 error_txt << table[table[0].adr].name << " 中while缺少开始符" << "\n";

							    }
							 else//是 {
							 {
								 lex.getsym();//再读一个字
							 }
							 statements(fsys);//看是解析while里的语句
							 gen(JMP, 0, i);//跳到开始while判断的地方 
							 code[jpc_pcode].a = pcode;
						 }


					 }
					 if (lex.sym != endsym)
					 {
						 cout << table[table[0].adr].name;
						 cout << " 中while缺少结束符" << endl;
						 error_txt << table[table[0].adr].name << " 中while缺少结束符" << "\n";

					 }
					 else
					 {
						 lex.getsym();
					 }
	}
		break;
	case ifsym:
	{
				  lex.getsym();//读左括号
				  int jpccode;
				  if (lex.sym != leftsym)
				    {
					  cout << table[table[0].adr].name;
					  cout << " if中缺少左括号" << endl;
					  error_txt << table[table[0].adr].name << "  if中缺少左括号" << "\n";
					  fsys[beginsym] = true;
					  if (test(fsys, stabegsys))
							 {
								 cout << table[table[0].adr].name;
								 cout << " 中含有非法符号" << endl;
								 error_txt << table[table[0].adr].name << "  中含有非法符号" << "\n";

								  return -1;
							 }
					  if (lex.sym != beginsym)
							 {
								  cout << table[table[0].adr].name;
								 cout << " if中缺少开始符" << endl;
								 error_txt << table[table[0].adr].name << "  if中缺少开始符" << "\n";

								  statements(fsys);
							}
					  else
							 {
								 lex.getsym();
								 statements(fsys);
							  }
				   }
				  else//if(
					 {
					  lex.getsym();//再读一个字
					  expression(fsys);//开始表达式解析
					  int i = pcode;//code表当前指针
					  gen(JPC, 0, 0);
					  if (lex.sym != rightsym)//if(
						 {
						  cout << table[table[0].adr].name;
						  cout << " 中if缺少右括号" << endl;
						  error_txt << table[table[0].adr].name << "  if缺少右括号" << "\n";

						  fsys[beginsym] = true;
						  if (test(fsys, stabegsys))
							  {
							  cout << table[table[0].adr].name;
							  cout << " 中含有非法符号 " << endl;
							  error_txt << table[table[0].adr].name << "  中含有非法符号" << "\n";

							  return -1;
								}
							if (lex.sym != beginsym)
								{
									cout << table[table[0].adr].name;
									cout << " 中if缺少开始符" << endl;
									error_txt << table[table[0].adr].name << "  if缺少开始符" << "\n";

									statements(fsys);
								}
								else
								{
									lex.getsym();
									statements(fsys);
								}
						}
					  else//if() 解析完if里的表达式
					  {
						  lex.getsym();//再读一个
							if (lex.sym != beginsym)
								{
									cout << table[table[0].adr].name;
									cout << " 中if缺少开始符" << endl;
									error_txt << table[table[0].adr].name << "  if缺少开始符" << "\n";

									statements(fsys);
								}
						  else
								{
									lex.getsym();
									statements(fsys);
									jpccode = i;
									code[jpccode].a = pcode;
								}
					   }
				  }
				  if (lex.sym != endsym)//if(){
				  {
					  cout << table[table[0].adr].name;
					  cout << " 中if缺少结束符 " << endl;
					  error_txt << table[table[0].adr].name << "  if缺少结束符" << "\n";

				  }
				  //if(){}处理完毕
				  else//if(){}
				  {
					  lex.getsym();
				  }

				  if (lex.sym == elsesym)
				  {
					  lex.getsym();
					  if (lex.sym != beginsym)//else
					  {
						  cout << table[table[0].adr].name;
						  cout << " 中else缺少开始括号" << endl;
						  error_txt << table[table[0].adr].name << " else缺少开始括号" << "\n";
					  }
					  else//else{
					  {
						  lex.getsym();
					  }
					  int elsepcode = pcode;
					  gen(JMP, 0, 0);
					  code[jpccode].a++;
					  statements(fsys);
					  code[elsepcode].a = pcode;
					  if (lex.sym != endsym)
					  {
						  cout << table[table[0].adr].name;
						  cout << " 中else缺少结束括号" << endl;
						  error_txt << table[table[0].adr].name << " else缺少结束括号" << "\n";

					  }
					  else
					  {
						  lex.getsym();
					  }
				  }
	}
		break;
	case scanfsym:
	{
					 //fsys[leftsym] = true;
					 //fsys[rightsym] = true;
					 ///fsys[ident] = true;
					 fsys[semicolon] = true;

					 /*if (test(fsys,fsys))
					 {
					 cout<<table[table[0].adr].name;
					 cout<<" scanf中含有非法符号 "<<endl;
					 if(test(stabegsys,delbegsys))
					 {
					 return -1;
					 }
					 else
					 {
					 if (lex.sym == ident)
					 {
					 return 0;
					 }
					 }
					 }
					 else
					 {
					 if (lex.sym != leftsym)
					 {
					 cout<<table[table[0].adr].name;
					 cout<<" scanf中缺少左括号"<<endl;
					 }

					 }*/

					 lex.getsym();
					 if (lex.sym != leftsym)//直接找到分号或者语句开头，进行下一个语句处理
					 {
						 cout << table[table[0].adr].name;
						 cout << " 中scanf缺少左括号" << endl;
						 error_txt << table[table[0].adr].name << " 中scanf缺少左括号" << "\n";

						 if (test(fsys, stabegsys))
						 {
							 cout << table[table[0].adr].name;
							 cout << " 中含有非法符号 " << endl;
							 error_txt << table[table[0].adr].name << " 中含有非法符号" << "\n";

							 return -1;
						 }
						 else
						 {
							 if (lex.sym != semicolon)
							 {
								 cout << table[table[0].adr].name;
								 cout << " 中scanf缺少分号" << endl;
								 error_txt << table[table[0].adr].name << " 中scanf缺少分号" << "\n";

								 break;
							 }
							 lex.getsym();
						 }
					 }
					 else//scanf(
					 {
						 lex.getsym();
						 if (lex.sym != ident)//直接找到分号或者语句开头，进行下一个语句处理
						 {
							 cout << table[table[0].adr].name;
							 cout << " 中scanf缺少变量" << endl;
							 error_txt << table[table[0].adr].name << " 中scanf缺少变量" << "\n";

							 if (test(fsys, stabegsys))
							 {
								 cout << table[table[0].adr].name;
								 cout << " 中含有非法符号 " << endl;
								 error_txt << table[table[0].adr].name << "中含有非法符号" << "\n";

								 return -1;
							 }
							 else
							 {
								 switch (lex.sym)
								 {
								 case rightsym:lex.getsym(); break;
								 case semicolon:
								 {
												   cout << table[table[0].adr].name;
												   cout << " 中scanf缺少右括号" << endl;
												   error_txt << table[table[0].adr].name << " 中scanf缺少右括号" << "\n";

												   break;
								 }
								 default:
								 {
											cout << table[table[0].adr].name;
											cout << " 中scanf缺少右括号" << endl;
											error_txt << table[table[0].adr].name << " 中scanf缺少右括号" << "\n";

											//cout<<table[table[0].adr].name;
											//cout<<" 中scanf缺少分号"<<endl;
											break;
								 }

								 }
								 if (lex.sym != semicolon)
								 {
									 cout << table[table[0].adr].name;
									 cout << " 中scanf缺少分号" << endl;
									 error_txt << table[table[0].adr].name << " 中scanf缺少分号" << "\n";

								 }
								 else
								 {
									 lex.getsym();
								 }
							 }
						 }
						 else//scanf(x
						 {
							 //生成
							 int i;
							 i = position(lex.id, var);
							 if (i == 0)
							 {
								 cout << table[table[0].adr].name;
								 cout << " 中scanf使用未定义变量" << endl;
								 error_txt << table[table[0].adr].name << " 中scanf使用未定义变量" << "\n";
							 }
							 else
							 {
								 gen(RED, 0, 0);
								 gen(STO, table[table[0].adr].level + 1 - table[i].level, table[i].adr);
								 //table[table[0].adr].level +1 - table[i].level

							 }
							 lex.getsym();
							 switch (lex.sym)
							 {
							 case rightsym:
							 {
											  lex.getsym();
											  if (lex.sym != semicolon)
											  {
												  cout << table[table[0].adr].name;
												  cout << " 中scanf缺少分号" << endl;
												  error_txt << table[table[0].adr].name << " 中scanf缺少分号" << "\n";

											  }
											  else
											  {
												  lex.getsym();
											  }
											  break;
							 }
							 case semicolon:
							 {
											   lex.getsym();
											   cout << table[table[0].adr].name;
											   cout << " 中scanf缺少右括号" << endl;
											   error_txt << table[table[0].adr].name << " 中scanf缺少右括号" << "\n";

											   break;
							 }
							 default:
							 {
										cout << table[table[0].adr].name;
										cout << " 中scanf缺少右括号" << endl;
										error_txt << table[table[0].adr].name << " 中scanf缺少右括号" << "\n";

										cout << table[table[0].adr].name;
										cout << " 中scanf缺少分号" << endl;
										error_txt << table[table[0].adr].name << " 中scanf缺少分号" << "\n";

							 }
								 break;
							 }

						 }
					 }
	}
		break;
	case printfsym:
	{
					  lex.getsym();
					  if (lex.sym != leftsym)//直接找到分号或者语句开头，进行下一个语句处理
					  {
						  cout << table[table[0].adr].name;
						  cout << " 中printf缺少左括号" << endl;
						  error_txt << table[table[0].adr].name << " 中printf缺少左括号" << "\n";

						  fsys[semicolon] = true;
						  fsys[endsym] = true;
						  if (test(fsys, stabegsys))
						  {
							  cout << table[table[0].adr].name;
							  cout << " 中含有非法符号 " << endl;
							  error_txt << table[table[0].adr].name << " 中含有非法符号" << "\n";

							  return -1;
						  }
						  else
						  {
							  if (lex.sym != semicolon)
							  {
								  cout << table[table[0].adr].name;
								  cout << " 中printf缺少分号" << endl;
								  error_txt << table[table[0].adr].name << " 中printf缺少分号" << "\n";


								  break;
							  }
							  else
								  lex.getsym();
						  }
					  }
					  else//printf(
					  {
						  lex.getsym();
						  if (!expbegsys[lex.sym])
						  {
							  cout << table[table[0].adr].name;
							  cout << " 中printf缺少表达式" << endl;
							  error_txt << table[table[0].adr].name << " 中printf缺少表达式" << "\n";

						  }
						  expression(fsys);
						  gen(WRT, 0, 0);
						  //printf()
						  switch (lex.sym)
						  {
						  case rightsym:
						  {
										   lex.getsym();
										   break;
						  }
						  case semicolon:
						  {
											cout << table[table[0].adr].name;
											cout << " 中printf缺少右括号" << endl;
											error_txt << table[table[0].adr].name << " 中printf缺少右括号" << "\n";

											break;
						  }
						  default:
						  {
									 cout << table[table[0].adr].name;
									 cout << " 中printf缺少右括号" << endl;
									 error_txt << table[table[0].adr].name << " 中printf缺少右括号" << "\n";

									 //cout<<table[table[0].adr].name;
									 //cout<<" 中printf缺少分号"<<endl;
						  }
							  break;
						  }

						  if (lex.sym != semicolon)
						  {
							  cout << table[table[0].adr].name;
							  cout << " 中printf缺少分号" << endl;
							  error_txt << table[table[0].adr].name << " 中printf缺少分号" << "\n";

							  //break;
						  }
						  else
							  lex.getsym();
					  }
	}
		break;
	case resym:
	{
				  table[0].level = 1;
				  fsys[semicolon] = true;
				  fsys[rightsym] = true;
				  fsys[endsym] = true;
				  lex.getsym();
				  if (lex.sym != leftsym) //return  找到分号或者下一个语句开头
				  {
					  cout << table[table[0].adr].name;
					  cout << " 中return缺少左括号" << endl;
					  error_txt << table[table[0].adr].name << "  中return缺少左括号" << "\n";

					  if (test(fsys, stabegsys))
					  {
						  cout << table[table[0].adr].name;
						  cout << " 中含有非法符号 " << endl;
						  error_txt << table[table[0].adr].name << "中含有非法符号" << "\n";

						  return -1;
					  }
					  else
					  {
						  if (!expbegsys[lex.sym])
						  {
							  cout << table[table[0].adr].name;
							  cout << " 中return缺少表达式" << endl;
							  error_txt << table[table[0].adr].name << "  中return缺少表达式" << "\n";

						  }
						  expression(fsys);
						  switch (lex.sym)
						  {
						  case rightsym:lex.getsym(); break;
						  case semicolon:
						  {
											cout << table[table[0].adr].name;
											cout << " 中return缺少右括号" << endl;
											error_txt << table[table[0].adr].name << "  中return缺少右括号" << "\n";

											//lex.getsym();
											break;
						  }
						  default:
						  {
									 cout << table[table[0].adr].name;
									 cout << " 中return缺少右括号" << endl;
									 error_txt << table[table[0].adr].name << "  中return缺少右括号" << "\n";

									 //cout<<table[table[0].adr].name;
									 //cout<<" 中return缺少分号"<<endl;
									 break;

						  }

						  }
						  if (lex.sym != semicolon)
						  {
							  cout << table[table[0].adr].name;
							  cout << " 中return缺少分号" << endl;
							  error_txt << table[table[0].adr].name << "  中return缺少分号" << "\n";

							  //break;
						  }
						  else
							  lex.getsym();
					  }
				  }
				  else//return(
				  {
					  lex.getsym();
					  expression(fsys);
					  switch (lex.sym)
					  {
					  case rightsym:
					  {
									   lex.getsym();
									   if (lex.sym != semicolon)
									   {
										   cout << table[table[0].adr].name;
										   cout << " 中return缺少分号" << endl;
										   error_txt << table[table[0].adr].name << "  中return缺少分号" << "\n";

									   }
									   else
									   {
										   lex.getsym();
									   }
									   break;
					  }
					  case semicolon:
					  {
										lex.getsym();
										cout << table[table[0].adr].name;
										cout << " 中return缺少右括号" << endl;
										error_txt << table[table[0].adr].name << "  中return缺少右括号" << "\n";

										break;
					  }
					  default:
					  {
								 cout << table[table[0].adr].name;
								 cout << " 中return缺少右括号" << endl;
								 error_txt << table[table[0].adr].name << "  中return缺少右括号" << "\n";

								 cout << table[table[0].adr].name;
								 cout << " 中return缺少分号" << endl;
								 error_txt << table[table[0].adr].name << "  中return缺少分号" << "\n";

					  }
						  break;
					  }

				  }
	}
		break;
	case period:
	{
				   return 0;

				   break;
	}
	case elsesym:
	{
					cout << table[table[0].adr].name;
					cout << " 中出现无匹配的else" << endl;
					error_txt << table[table[0].adr].name << "  中出现无匹配的else" << "\n";

					if (test(fsys, stabegsys))
					{
						cout << table[table[0].adr].name;
						cout << " 中含有非法符号 " << endl;
						error_txt << table[table[0].adr].name << "  中含有非法符号" << "\n";

						return -1;
					}
					break;
	}
	case endsym:
	{
				   //lex.getsym();
				   break;
	}
	default:
	{
			   cout << table[table[0].adr].name;
			   cout << " 中出现非法成分" << endl;
			   error_txt << table[table[0].adr].name << "  中出现非法成分" << "\n";

			   test(stabegsys, delbegsys);
			   return -1;
			   break;
	}
	}
	return 0;
}
int Block::expression(bool* fsys)
{
	symbol addop;
	bool nxtlev[symnum];
	symcopy(fsys, nxtlev);
	ss.addset(nxtlev, terbegsys, nxtlev, symnum);
	if (lex.sym == plu || lex.sym == sub)
	{
		addop = lex.sym;
		lex.getsym();
		term(nxtlev);
		if (addop == sub)
		{
			gen(LIT, 0, -1);
			gen(MUL, 0, 0);
		}

	}
	else
	{
		term(nxtlev);
	}
	while (lex.sym == plu || lex.sym == sub)
	{
		addop = lex.sym;
		lex.getsym();
		term(nxtlev);
		if (addop == plu)
		{
			gen(ADD, 0, 0);
		}
		else
		{
			gen(SUB, 0, 0);
		}

	}
	return 0;
}
int Block::term(bool* fsys)
{
	symbol addop;
	bool nxtlev[symnum];
	symcopy(fsys, nxtlev);
	ss.addset(nxtlev, facbegsys, nxtlev, symnum);
	factor(nxtlev);

	while (lex.sym == dive || lex.sym == mul)
	{
		addop = lex.sym;
		lex.getsym();
		factor(nxtlev);
		if (addop == dive)
		{
			gen(DIV, 0, 0);
		}
		else
		{
			gen(MUL, 0, 0);
		}
	}
	return 0;
}
int Block::factor(bool* fsys)
{
	int i;
	bool nxtlev[symnum];
	symcopy(fsys, nxtlev);
	//fsys[rightsym] = true;
	while (facbegsys[lex.sym])
	{
		switch (lex.sym)
		{
		case ident:
		{
					  lex.getsym();
					  if (lex.sym == leftsym)
					  {
						  //cout<<"自定义函数调用"<<endl;
						  i = position(lex.id, procedur);
						  if (i != 0)
						  {
							  if (table[i].kind == procedur)
							  {
								  cout << table[table[0].adr].name;
								  cout << " 中调用了一个无返回值的函数，若参与运算或者赋值，可能会发生错误" << endl;
							  }
						  }
						  gen(CAL, table[table[0].adr].level + 1 - table[i].level, table[i].adr);
						  lex.getsym();
						  if (lex.sym != rightsym)
						  {
							  cout << table[table[0].adr].name;
							  cout << " 中函数缺少右括号" << endl;
							  error_txt << table[table[0].adr].name << "  中函数缺少右括号" << "\n";


							  break;
						  }
						  lex.getsym();
					  }
					  else
					  {
						  //cout<<"变量调用"<<endl;
						  i = position(lex.id, var);
						  if (i == 0)
						  {
							  cout << table[table[0].adr].name;
							  cout << " 中使用未定义变量  " << lex.id << endl;
							  error_txt << table[table[0].adr].name << "  中使用未定义变量" << "\n";

							  if (test(fsys, facbegsys))
							  {
								  cout << table[table[0].adr].name;
								  cout << " 中含有非法符号 " << endl;
								  error_txt << table[table[0].adr].name << "  中含有非法符号" << "\n";

								  return -1;
							  }
							  break;
						  }
						  else
						  {
							  gen(LOD, table[table[0].adr].level + 1 - table[i].level, table[i].adr);
							  //lex.getsym();
							  //return 0;
						  }

					  }
		}
			break;
		case number:
		{
					   gen(LIT, 0, lex.num);
					   lex.getsym();
		}
			break;
		case leftsym:
		{
						lex.getsym();
						if (expression(fsys))
						{
							cout << table[table[0].adr].name;
							cout << " 中含有非法表达式" << endl;
							error_txt << table[table[0].adr].name << "  中含有非法表达式" << "\n";

							if (test(fsys, stabegsys))
							{
								cout << table[table[0].adr].name;
								cout << " 中含有非法符号" << endl;
								error_txt << table[table[0].adr].name << "  中含有非法符号" << "\n";

								return -1;
							}
							break;
						}
						if (lex.sym != rightsym)
						{
							cout << table[table[0].adr].name;
							cout << " 中表达式缺少右括号" << endl;
							error_txt << table[table[0].adr].name << "  中表达式缺少右括号" << "\n";

							break;
							//return 1;
						}
						lex.getsym();
		}
			break;
		case rightsym:
			//cout<<"因子中读取到）"<<endl;
			//cout<<"自定义函数调用"<<endl;
			/*i = position(lex.id,procedur);
			if (i==0)
			{
			cout<<"无此函数"<<endl;
			}
			gen(CAL,table[i].level - table[table[0].adr].level,table[i].adr);*/
		{
						 cout << table[table[0].adr].name;
						 cout << " 中含有非法右括号" << endl;
						 error_txt << table[table[0].adr].name << "  中含有非法右括号" << "\n";

						 lex.getsym();
						 return 0;
		}
		default:
		{
				   /*cout<<table[table[0].adr].name;
				   cout<<" 中含有非法符号"<<endl;
				   bool fsys1[symnum];
				   symcopy(stabegsys,fsys1);//语句开始，分号，. ，}，+，-，/，*，
				   fsys1[semicolon] = true;
				   fsys1[period] = true;
				   fsys1[endsym] = true;
				   fsys1[plus] = true;
				   fsys1[sub] = true;
				   fsys1[dive] = true;
				   fsys1[mul] = true;*/
				   return 0;
		}
			break;
		}
	}
	return 0;
}
int Block::statements(bool* fsys)
{
	fsys[endsym] = true;
	bool nxtlev[symnum];
	symcopy(fsys, nxtlev);
	if (test(fsys, stabegsys))
	{
		cout << table[table[0].adr].name;
		cout << " 中缺少结束符号" << endl;
		error_txt << table[table[0].adr].name << "  中缺少结束符号" << "\n";

		return -1;
	}

	while (1)
	{
		/*if (lex.sym == intsym || lex.sym == voidsym)
		{
		return 0;//遇到声明就返回
		}*/
		switch (lex.sym)
		{
		case period:return 0;
		case intsym:return 0;
		case voidsym:return 0;
		case endsym:return 0;
		case plu:return 0;
		case sub:return 0;
		case dive:return 0;
		case mul:return 0;
		case number:return 0;
			//case beginsym:lex.getsym();break;
		default:
			break;
		}
		statement(nxtlev);
		if (test(stabegsys, fsys))
		{
			cout << table[table[0].adr].name;
			cout << " 中缺少结束符号" << endl;
			error_txt << table[table[0].adr].name << "  中缺少结束符号" << "\n";

			return -1;
		}
	}
	//return 0;
}
void Block::symprint(symbol s)
{
	switch (s)
	{
	case number:cout << "number" << endl;
		break;
	case plu:cout << "plus" << endl;
		break;
	case sub:cout << "sub" << endl;
		break;
	case mul:cout << "mul" << endl;
		break;
	case dive:cout << "dive" << endl;
		break;
		//	case procsym:cout<<"procsym"<<endl;
		break;
	case beginsym:cout << "beginsym" << endl;
		break;
	case endsym:cout << "endsym" << endl;
		break;
		//	case selfprocsym:cout<<"selfprocsym"<<endl;
		break;
		//	case mainprocsym:cout<<"mainprocsym"<<endl;
		break;
	case varsym:cout << "varsym" << endl;
		break;
	case intsym:cout << "intsym" << endl;
		break;
	case ident:cout << "ident" << endl;
		break;
	case comma:cout << "comma" << endl;
		break;
	case semicolon:cout << "semicolon" << endl;
		break;
		//	case partprocsym:cout<<"partprocsym"<<endl;
		break;
	case mainsym:cout << "mainsym" << endl;
		break;
	case voidsym:cout << "voidsym" << endl;
		break;
		//	case sstasym:cout<<"sstasym"<<endl;
		break;
		//	case stasym:cout<<"stasym"<<endl;
		break;
	case ifstasym:cout << "ifstasym" << endl;
		break;
	case whilestasym:cout << "whilestasym" << endl;
		break;
		//	case assstasym:cout<<"assstasym"<<endl;
		break;
	case restasym:cout << "restasym" << endl;
		break;
	case readstasym:cout << "readstasym" << endl;
		break;
	case writestasym:cout << "writestasym" << endl;
		break;
		//	case callselfprocstasym:cout<<"callselfprocstasym"<<endl;
		break;
	case ifsym:cout << "ifsym" << endl;
		break;
		//	case exprsym:cout<<"exprsym"<<endl;
		break;
	case elsesym:cout << "elsesym" << endl;
		break;
	case whilesym:cout << "whilesym" << endl;
		break;
		//	case callselfprocsym:cout<<"callselfprocsym"<<endl;
		break;
	case eqlsym:cout << "eqlsym" << endl;
		break;
	case scanfsym:cout << "scanfsym" << endl;
		break;
	case printfsym:cout << "printfsym" << endl;
		break;
		//case term:
		//break;
		//case factor:
		//break;
	case leftsym:cout << "leftsym" << endl;
		break;
	case rightsym:cout << "rightsym" << endl;
		break;
	case nul:cout << "nul" << endl;
		break;
	case resym:cout << "resym" << endl;
		break;
	case period:cout << "period" << endl;
		break;
	default:
		break;
	}
}
void Block::insprint()
{
	int i = 0;
	while (i < pcode)
	{
		cout << i << " ";
		switch (code[i].f)
		{
		case	LOD:cout << "LOD" << "  "; break;
		case	STO:cout << "STO" << "  "; break;
		case	CAL:cout << "CAL" << "  "; break;
		case	INT:cout << "INT" << "  "; break;
		case	JMP:cout << "JMP" << "  "; break;
		case	JPC:cout << "JPC" << "  "; break;
		case    ADD:cout << "ADD" << "  "; break;
		case	SUB:cout << "SUB" << "  "; break;
		case	MUL:cout << "MUL" << "  "; break;
		case	DIV:cout << "DIV" << "  "; break;
		case	RED:cout << "RED" << "  "; break;
		case	WRT:cout << "WRT" << "  "; break;
		case	RET:cout << "RET" << "  "; break;
		case	NUL:return;
		case    LIT:cout << "LIT" << "  "; break;
		default:
			return;
		}
		cout << code[i].l << "  " << code[i].a << endl;
		i++;
	}


}
void Block::symcopy(bool* s1, bool* s2)
{
	int i = 0;
	for (i = 0; i < symnum; i++)
	{
		s2[i] = s1[i];
	}
}
void Block::main()
{
	cout << "考虑到循环执行的话，如果中间一个程序的编译出问题，剩下的都会受到影响\n所以，没有改成table_(x).txt形式。" << endl;
	cout << "本程序，执行后，生成的中间代码在：code.txt中\n运行情况在result.txt, 错误信息在error.txt中" << endl;
	cout << "本程序在错误处理方面尚有欠缺，但文档中要求的所有功能都以实现。" << endl;
	cout << "欢迎测试C0编译器--张怀文版" << endl;
	error_txt.open("error.txt", ios::out);
	fstream inte;
	inte.open("result.txt", ios::out);
	bool b[symnum];//开始符号集
	symcopy(allfalse, b);
	ss.addset(b, stabegsys, delbegsys, symnum);//语句和声明的集合
	b[period] = true;//结束的.
	init();//做一些初始化

	allstr = 'y';
	cout << "是否列出源码? Y/N" << endl;
	inte << "是否列出源码? Y/N" <<"\n";
	cin >> allstr;
	inte << allstr << "\n";
	inspri = 'y';
	cout << "是否列出指令? Y/N" << endl;
	inte << "是否列出指令? Y/N" << "\n";
	cin >> inspri;
	inte << inspri << "\n";
	mainblock(0, b);
	//检查有无main函数
	//把unsertain 中的东西填上，若填不上，则报错
	uncertain();
	if (allstr == 'Y' || allstr == 'y')
	{
		cout << "源码为：" << endl;
		for (int i = 0; i < lex.all.length(); i++)
		{
			cout << lex.all[i];
		}
		cout << endl << endl;
	}
	if (inspri == 'Y' || inspri == 'y')
	{
		insprint();//输出指令
		cout << endl;
	}
       inswriter();//把指令写到codetxt里
	   inte.close();
	   inter.start();//从code.txt里读入指令执行
	   error_txt.close();
}




void Block::inswriter()
{
	fstream out;
	out.open("code.txt", ios::out);
	int i = 0;
	while (i < pcode)
	{
		out << i << " ";
		switch (code[i].f)
		{
			case LIT:out << "LIT "; break;
			case LOD:out << "LOD "; break;
			case STO:out << "STO "; break;
			case CAL:out << "CAL "; break;
			case INT:out << "INT "; break;
			case JMP:out << "JMP "; break;
			case JPC:out << "JPC "; break;
			case ADD:out << "ADD "; break;
			case SUB:out << "SUB "; break;
			case MUL:out << "MUL "; break;
			case DIV:out << "DIV "; break;
			case RED:out << "RED "; break;
			case WRT:out << "WRT "; break;
			case RET:out << "RET "; break;
			case NUL:out.close(); return;
			default:
			out.close(); return;
		}
		//将 l a 写入文件
		out << code[i].l << " " << code[i].a << "\n";
		i++;
		if (i >= 200)
		{
			cout << "指令过长" << endl;
			out.close();
			return;
		}
	}
	out.close();
}
int Block::test(bool*s1, bool*s2)
{
	if (!s1[lex.sym])
	{
		while ((!s1[lex.sym]) && (!s2[lex.sym]))
		{
			lex.getsym();
			if (lex.sym == nul || lex.sym == period)
			{
				return 1;
			}
		}
	}
	return 0;
}

int Block::uncertain()
{
	int i;
	int p,p1;
	for (i = 0; i < 20; i++)
	{
		if (unadd[i].codeadr == -1)
			break;
		else
		{
			p = position(unadd[i].name, procedur);
			if (p == 0)
			{
				cout << unadd[i].proc << " 中调用了未定义函数 " << unadd[i].name << endl;
				unadd[i+1].codeadr = -1;
			}
			else
			{
				// gen(STO, table[table[0].adr].level + 1 - table[i].level, table[i].adr);
				p1 = position(unadd[i].proc, procedur);
				code[unadd[i].codeadr].a = table[p].adr;
				code[unadd[i].codeadr].l = table[p1].level + 1 - table[p].level;
			}
		}
	}
	return 0;
}
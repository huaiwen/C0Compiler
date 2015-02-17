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
	table[0].name = "";//����ȫ�ֱ���
	table[0].level = 5;
	///////////////////////////
	table[1].name = "public";
	table[1].level = 0;
	//////////////////////////
	code[0].f = JMP;//code��һ�� jump
	code[0].l = 0;
	code[0].a = 0;
	/////////////////////////
	codechar[LIT] = "LIT";//ָ��ö�����Ͷ�Ӧ���ַ�����
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
	//������ʼ�� int void
	delbegsys[intsym] = true;
	delbegsys[voidsym] = true;
	/////////////////////////
	//��俪ʼ��
	stabegsys[ifsym] = true;
	stabegsys[whilesym] = true;
	stabegsys[ident] = true;
	stabegsys[resym] = true;
	stabegsys[scanfsym] = true;
	stabegsys[printfsym] = true;
	stabegsys[beginsym] = true;
	/////////////////////////
	//���ӿ�ʼ��
	facbegsys[ident] = true;
	facbegsys[leftsym] = true;
	facbegsys[number] = true;
	//////////////////////////
	//�ʼ����
	terbegsys[ident] = true;
	terbegsys[leftsym] = true;
	terbegsys[number] = true;
	////////////////////////////
	//���ʽ��ʼ����
	expbegsys[plu] = true;
	expbegsys[sub] = true;
	expbegsys[ident] = true;
	expbegsys[leftsym] = true;
	expbegsys[number] = true;
	//////////////////////////////
	//������ʼ����
	varbegsys[intsym] = true;
	//////////////////////////////
	//�Ҳ����������������������浽unadd������������������д���
	for (i = 0; i < 20; i++)
	{
		unadd[i].codeadr = -1;
		unadd[i].name = "";
		unadd[i].proc = "";
	}
	while (lex.readfile())//��c0Դ�ļ�
	{
		cout << "�����������ļ�����" << endl;
	}
}
int Block::mainblock(int lev, bool* fsys)//��Σ���ǰ״̬���ż�
{
	int dx;//��Ե�ַ
	int tx0;//�����˳����ʼ���ֱ�λ��
	int pcode0;//�����˳����ʼָ��λ��
	bool nxtlev[symnum];//���´��ķ��ż�

	dx = 3;
	tx0 = tx;//���ֱ�ָ��

	lex.getsym();//��һ������

	if (lex.sym == period)//���������������
	{
		return 0;
	}

	symcopy(fsys, nxtlev);
	while (delbegsys[lex.sym])//����  ������������ֱ����������ȫ������
	{
		if (lex.sym == intsym)//���������Զ��庯��
		{
			lex.getsym();//��ident

			fsys[ident] = true;
			fsys[beginsym] = true;
			if (test(fsys, delbegsys))
			{
				cout << table[tx0].name;
				cout << " ��������ʼ���Ƿ�����" << endl;
				error_txt << table[tx0].name << " ��������ʼ���Ƿ�����" << "\n";
				return -1;
			}
			switch (lex.sym)
			{
			case ident:
				break;//û����
			case beginsym:
			{
							 cout << table[tx0].name;
							 cout << " ����������" << endl;
							 error_txt << table[tx0].name << " ����������" << "\n";
							 lex.getsym();
							 continue;
							 break;
			}
			default:
			{
					   cout << table[tx0].name;
					   cout << " ����������" << endl;
					   error_txt << table[tx0].name << " ����������" << "\n";
					   //lex.getsym();
			}
				continue;
				break;
			}
			fsys[ident] = false;
			fsys[beginsym] = false;
			//int x(){    int x,x;
			lex.getsym();//�����ǣ�  ���߶��� ���߷ֺ� ���ߵȺ�  ����(   ��Ϊ���Ǻ���
			if (lex.sym == leftsym)//�����ŵĻ� �Ǻ���
			{
				string s1 = lex.id;//���º�������
				fsys[rightsym] = true;
				fsys[beginsym] = true;
				lex.getsym();//������

				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " ��������ʼ���Ƿ�����" << endl;
					error_txt << table[tx0].name << " ��������ʼ���Ƿ�����" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case rightsym:break;//(){   ,x;
				case beginsym:
				{
								 cout << table[tx0].name;
								 cout << " �к���ȱ��������" << endl;
								 error_txt << table[tx0].name << " �к���ȱ��������" << "\n";
								 lex.getsym();
								 continue;
								 break;
				}
				default:
				{
						   cout << table[tx0].name;
						   cout << " ����������" << endl;
						   error_txt << table[tx0].name << " ����������" << "\n";
						   //lex.getsym();
						   continue;
						   break;
				}
				}
				lex.getsym();//������ {
				fsys[rightsym] = false;
				//fsys[beginsym] = false;
				fsys[beginsym] = true;
				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " ��������ʼ���Ƿ�����" << endl;
					error_txt << table[tx0].name << " ��������ʼ���Ƿ�����" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case beginsym:break;
				default:
				{
						   cout << table[tx0].name;
						   cout << " ��ȱ�ٿ�ʼ��" << endl;
						   error_txt << table[tx0].name << " ��ȱ�ٿ�ʼ��" << "\n";
						   //lex.getsym();
						   continue;
						   break;
				}
				}
				fsys[beginsym] = false;

				enter(intprocedur, lev, &dx);//������½���ֱ�
				table[tx].belongto = table[tx0].name;
				table[tx].name = s1;
				if (-1 == mainblock(lev + 1, nxtlev))
				{
					return -1;
				}
				//��ȷ�����Ļ��϶���  }
				lex.getsym();		//������������
				continue;
			}
			else//���������ţ��Ǳ���
			{
				while (1)
				{
					if (lex.sym == comma)//����
					{
						variable(lev, &dx);//��½���ֱ����ٶ�һ���֣�tx����
						table[tx].belongto = table[tx0].name;//����������Զ�����ͬ���ֵı�������belongto ���Խ���������
						//cout<<table[tx].name<<" "<<table[tx].level<<""<<table[tx].belongto<<endl;
						lex.getsym();//�ٶ�һ����
						continue;
					}
					if (lex.sym == semicolon)
					{
						variable(lev, &dx);//��½���ֱ����ٶ�һ���֣�tx����
						table[tx].belongto = table[tx0].name;//����������Զ�����ͬ���ֵı�������belongto ���Խ���������
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
							lex.getsym();//���Ż�ֺ�
						}
						if (lex.sym == semicolon)
							break;
					}
					if (lex.sym == ident)//int a b
					{
						cout << table[tx0].name;
						cout << " �� " << lex.id << " *֮ǰȱ�ٶ���" << endl;
						error_txt << table[tx0].name << " �� " << lex.id << " *֮ǰȱ�ٶ���" << "\n";
						variable(lev, &dx);
						table[tx].belongto = table[tx0].name;
						//lex.getsym();//
					}
					else
					{
						cout << table[tx0].name;
						cout << " �� " << lex.id << " *���зǷ�����" << endl;
						error_txt << table[tx0].name << " �� " << lex.id << " *���зǷ�����" << "\n";
						symcopy(allfalse, nxtlev);
						//nxtlev[period] = true;
						nxtlev[semicolon] = true;
						//nxtlev[endsym] = true;
						nxtlev[ident] = true;
						if (test(delbegsys, nxtlev))
							break;						//�������  .  ;  }    testҪ�и�ֹͣ����
						//��������ʼ�����ҵ������Խ����ѭ�����Ҳ����ͽ���������
						if (lex.sym == intsym || lex.sym == voidsym)
							break;
					}
				}
				continue;
			}

		}


		if (lex.sym == voidsym)//�Զ��庯������������
		{
			lex.getsym();
			if (lex.sym != mainsym  && lex.sym != ident)
			{
				cout << table[tx0].name;
				cout << " �� " << lex.id << "��������" << endl;
				error_txt << table[tx0].name << " �� " << lex.id << " ��������" << "\n";
				fsys[beginsym] = true;
				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " ��������ʼ���Ƿ�����" << endl;
					error_txt << table[tx0].name << " ��������ʼ���Ƿ�����"<< "\n";
					return -1;
				}
				fsys[beginsym] = false;
				switch (lex.sym)
				{
				case beginsym:
					cout << table[tx0].name;
					cout << " ��void������������" << endl;
					error_txt << table[tx0].name << " ��void������������" << "\n";
					continue;
					break;
				default:
					cout << table[tx0].name;
					cout << " ��void������������" << endl;
					cout << " ��void����ȱ�ٿ�ʼ��" << endl;
					error_txt << table[tx0].name << " ��void������������" << "\n";
					error_txt << table[tx0].name << " ��void����ȱ�ٿ�ʼ��" << "\n";
					continue;
					break;
				}
			}
			if (lex.sym == mainsym)//������
			{
				string s1 = lex.id;
				/*if (lex.sym != leftsym)
				{
				cout<<table[tx0].name;
				cout<<" ��ȱ��������"<<endl;
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
				cout<<" ��main�����������"<<endl;
				return -1;
				}//����Ҳ������������ {  �������󣬷���
				if (lex.sym == intsym || lex.sym == voidsym)
				{
				cout<<table[tx0].name;
				cout<<" ��ȱ��������"<<endl;
				cout<<" ��ȱ�ٿ�ʼ����"<<endl;
				continue;
				}
				if (lex.sym == endsym)
				{
				cout<<table[tx0].name;
				cout<<" ��ȱ��������"<<endl;
				cout<<" ��ȱ�ٿ�ʼ����"<<endl;

				if(test(delbegsys,stabegsys))
				{
				cout<<table[tx0].name;
				cout<<" ��main�����������"<<endl;
				return -1;
				}
				}
				/*if (lex.sym != beginsym)
				{
				cout<<table[tx0].name;
				cout<<" ��ȱ�ٿ�ʼ����!"<<endl;
				}*/
				/*if (lex.sym != rightsym)
				{
				cout<<table[tx0].name;
				cout<<" ��ȱ��������"<<endl;
				if (lex.sym != beginsym)
				{
				cout<<table[tx0].name;
				cout<<" ��ȱ�ٿ�ʼ����"<<endl;
				}
				}
				//lex.getsym();
				symcopy(allfalse,nxtlev);
				//znxtlev[]f
				if(test(delbegsys,stabegsys))
				{
				cout<<table[tx0].name;
				cout<<" ��main�����������"<<endl;
				return -1;
				}
				if (lex.sym != beginsym)
				{
				cout<<table[tx0].name;
				cout<<" ��ȱ�ٿ�ʼ����"<<endl;
				}*/
				fsys[leftsym] = true;
				fsys[beginsym] = true;
				lex.getsym();
				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " ��������ʼ���Ƿ�����" << endl;
					error_txt << table[tx0].name << " ��������ʼ���Ƿ�����" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case leftsym:break;//(){   ,x;
				case beginsym:
				{
								 cout << table[tx0].name;
								 cout << " ��main����ȱ��������" << endl;
								 error_txt << table[tx0].name << " ��main����ȱ��������" << "\n";
								 lex.getsym();
								 continue;
								 break;
				}
				default:
				{
						   cout << table[tx0].name;
						   cout << " ����������" << endl;
						   error_txt << table[tx0].name << " ����������" << "\n";
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
					cout << " ��������ʼ���Ƿ�����" << endl;
					error_txt << table[tx0].name << " ��������ʼ���Ƿ�����" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case rightsym:break;
				case beginsym:
				{
								 cout << table[tx0].name;
								 cout << " ��main����ȱ��������" << endl;
								 error_txt << table[tx0].name << " ��main����ȱ��������" << "\n";
								 lex.getsym();
								 continue;
								 break;
				}
				default:
				{
						   cout << table[tx0].name;
						   cout << " ��ȱ�ٿ�ʼ��" << endl;
						   error_txt << table[tx0].name << " ��ȱ�ٿ�ʼ��" << "\n";
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
					cout << " ��������ʼ���Ƿ�����" << endl;
					error_txt << table[tx0].name << " ��������ʼ���Ƿ�����" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case beginsym:break;
				default:
				{
						   cout << table[tx0].name;
						   cout << " ��ȱ�ٿ�ʼ��" << endl;
						   error_txt << table[tx0].name << " ��ȱ�ٿ�ʼ��" << "\n";
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
			else//�Զ��庯��
			{
				string s1 = lex.id;
				/*lex.getsym();
				if (lex.sym != leftsym)
				{
				cout<<table[tx0].name;
				cout<<" ��ȱ��������"<<endl;
				}

				symcopy(allfalse,nxtlev);
				ss.addset(nxtlev,delbegsys,stabegsys,symnum);
				nxtlev[beginsym] = true;
				nxtlev[rightsym] = true;
				nxtlev[endsym] = true;
				if(test(delbegsys,nxtlev))
				{
				cout<<table[tx0].name;
				cout<<" �к����������!"<<endl;
				return -1;
				}//����Ҳ������������ {  �������󣬷���
				if (lex.sym == intsym || lex.sym == voidsym)
				continue;
				if (lex.sym == endsym)
				return 0;
				/*if (lex.sym != beginsym)
				{
				cout<<table[tx0].name;
				cout<<" ��ȱ�ٿ�ʼ����!"<<endl;
				}*/
				/*if (lex.sym != rightsym)
				{
				cout<<table[tx0].name;
				cout<<" ��ȱ��������"<<endl;
				}
				if (lex.sym != beginsym)
				{
				cout<<table[tx0].name;
				cout<<" ��ȱ�ٿ�ʼ����"<<endl;
				}*/
				/*lex.getsym();
				if (lex.sym != rightsym)
				{
				cout<<"ȱ��������!"<<endl;
				return -1;
				}
				lex.getsym();
				if (lex.sym != beginsym)
				{
				cout<<"ȱ�ٿ�ʼ����!"<<endl;
				return -1;
				}*/


				fsys[leftsym] = true;
				fsys[beginsym] = true;
				lex.getsym();
				if (test(fsys, delbegsys))
				{
					cout << table[tx0].name;
					cout << " ��������ʼ���Ƿ�����" << endl;
					error_txt << table[tx0].name << " ��������ʼ���Ƿ�����" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case leftsym:break;//(){   ,x;
				case beginsym:
				{
								 cout << table[tx0].name;
								 cout << " �к���ȱ��������" << endl;
								 error_txt << table[tx0].name << " �к���ȱ��������" << "\n";
								 lex.getsym();
								 continue;
								 break;
				}
				default:
				{
						   cout << table[tx0].name;
						   cout << " ����������" << endl;
						   error_txt << table[tx0].name << " ����������" << "\n";
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
					cout << " ��������ʼ���Ƿ�����" << endl;
					error_txt << table[tx0].name << " ��������ʼ���Ƿ�����" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case rightsym:break;
				case beginsym:
				{
								 cout << table[tx0].name;
								 cout << " �к���ȱ��������" << endl;
								 error_txt << table[tx0].name << " �к���ȱ��������" << "\n";
								 lex.getsym();
								 continue;
								 break;
				}
				default:
				{
						   cout << table[tx0].name;
						   cout << " �к���ȱ�ٿ�ʼ��" << endl;
						   error_txt << table[tx0].name << " �к���ȱ�ٿ�ʼ��" << "\n";
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
					cout << " ��������ʼ���Ƿ�����" << endl;
					error_txt << table[tx0].name << " ��������ʼ���Ƿ�����" << "\n";
					return -1;
				}
				switch (lex.sym)
				{
				case beginsym:break;
				default:
				{
						   cout << table[tx0].name;
						   cout << " �к���ȱ�ٿ�ʼ��" << endl;
						   error_txt << table[tx0].name << " �к���ȱ�ٿ�ʼ��" << "\n";

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
	table[tx0].adr = pcode;//code��ָ��
	table[tx0].size = dx;//�����Ĵ�С����ߵı���
	pcode0 = pcode;
	if (tx0 == 0)
	{
		return 0;
	}

	if (gen(INT, 0, dx) == -1)return -1;//��ʼ��������ջ�ı����ռ�
	table[0].adr = tx0;//��������������ֱ���±꣬����ȫ�ֱ�����
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
		table[0].level = 0;//����Ǵ��������͵ĺ������в���ȷ��  �Ƿ�©дruturn����һ��־λ��Ϊ0��
	}
	if (statements(nxtlev) == -1)return -1;//������������ͺ���д��return�����־λ��1
	if (lex.sym != endsym)
	{
		cout << table[tx0].name;
		cout << " �к���ȱ�ٽ�����" << endl;
		error_txt << table[tx0].name << " �к���ȱ�ٽ�����" << "\n";

	}
	if (table[tx0].kind == intprocedur)
	{
		if (table[0].level == 1)//������������ͺ�����־λΪ0��©дreturn
		{
			table[0].level = 5;
			gen(RET, 0, 1);
			return 0;
		}
		else
		{
			cout << table[tx0].name;
			cout << " ��ȱ��return" << endl;
			error_txt << table[tx0].name << " ��ȱ��return" << "\n";

			return -1;
		}
	}
	return 0;
}
int Block::gen(fct x, int y, int z)
{
	if (pcode >= 300)
	{
		cout << "����̫��" << endl;
		error_txt << "����̫��" << endl;
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
{//tx���ֱ�β  
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
int Block::statement(bool* fsys)//һ��һ���ķ���
{
	if (lex.sym == semicolon)
	{
		lex.getsym();
	}
	bool nxtlev[symnum];

	int i;
	switch (lex.sym)
	{
	case ident://ʹ���Զ������ ���� ʹ���Զ��庯��
	{

				   i = position(lex.id, var);//���ɱ���ȥ�飬����鲻���Ļ������Ǻ��������ǲ�����
				   if (i != 0)//���������ı���
				   {
					  //// i = position(lex.id, var);//��������һ��
					  // if (i == 0)//û�鵽�����ı���
					  // {
						 //  cout << table[table[0].adr].name;
						 //  cout << " ��������δ�������" << lex.id << endl;
						 //  lex.getsym();
						 //  fsys[semicolon] = true;
						 //  if (test(fsys, stabegsys))
						 //  {
							//   cout << table[table[0].adr].name;
							//   cout << " �к��зǷ�����" << endl;
							//   return -1;
						 //  }
						 //  fsys[semicolon] = false;
						 //  return 1;//����
					  // }
					   lex.getsym();//�ٶ�һ��
					   if (lex.sym == eqlsym)//��ֵ
					   {
						   lex.getsym();
						   ss.addset(fsys, expbegsys, fsys, symnum);
						   if (test(fsys, stabegsys))
						   {
							   cout << table[table[0].adr].name;
							   cout << " �к��зǷ�����" << endl;
							   error_txt << table[table[0].adr].name << " �к��зǷ�����" << "\n";

							   return -1;
						   }
						   ss.subset(fsys, expbegsys, fsys, symnum);

						   if (expression(nxtlev))//���ʽ�����������¶�һ����
						   {
							   cout << table[table[0].adr].name;
							   cout << " ��ֵ��������Ч���ʽ" << endl;
							   error_txt << table[table[0].adr].name << " ��ֵ��������Ч���ʽ" << "\n";


						   }

						   if (lex.sym != semicolon)
						   {
							   lex.getsym();
							   if (lex.sym != semicolon)
							   {
								   cout << table[table[0].adr].name;
								   cout << " ��ȱ�ٷֺ�" << endl;
								   error_txt << table[table[0].adr].name << " ��ȱ�ٷֺ�" << "\n";

								   if (test(fsys, stabegsys))
								   {
									   cout << table[table[0].adr].name;
									   cout << " �к��зǷ�����" << endl;
									   error_txt << table[table[0].adr].name << " �к��зǷ�����" << "\n";

									   return -1;
								   }
							   }
						   }
						   gen(STO, table[table[0].adr].level + 1 - table[i].level, table[i].adr);//������������ֵ
						   //table[table[0].adr].level +1 - table[i].level
					   }
					   else//���Ǹ�ֵ�����ɳ���
					   {
						   if (test(fsys, stabegsys))
						   {
							   cout << table[table[0].adr].name;
							   cout << " �г��ַǷ�����" << endl;
							   error_txt << table[table[0].adr].name << " �к��зǷ�����" << "\n";

							   return 1;
						   }
					   }

				   }
				   else//�Զ��庯��
				   {
					   fsys[semicolon] = true;
					   lex.getsym();//��ȡ������
					   switch (lex.sym)
					   {
					   case leftsym://�Ǹ�����������֪���ǲ��Ƕ�����ģ���Ҫ��

						   break;
					   case rightsym://�Ǹ�����������֪���ǲ��Ƕ�����ģ���Ҫ�飬���������Ϣ

						   break;
					   default://δ�������
						   cout << "ʹ����δ����ı���" << endl;
						   error_txt << "ʹ����δ����ı���" << "\n";
						   return -1;
						   break;
					   }
					   if (lex.sym == leftsym)
					   {
						//	cout << "�Զ��庯������" << endl;
						   	i = position(lex.id,procedur);//�ٴε��ã���鿴
						   //	if ( i!=0 )
						  // 	{
						//	  if (table[i].kind == procedur)
						//		{
						//	   cout << table[table[0].adr].name;
						//	   cout << " �е�����һ���޷���ֵ�ĺ�����������������߸�ֵ�����ܻᷢ������" << endl;
						//		}
						//   }
						   gen(CAL, table[table[0].adr].level + 1 - table[i].level, table[i].adr);//��������
						   //table[table[0].adr].level +1 - table[i].level
						   lex.getsym();//������
						   if (lex.sym != rightsym)
						   {
							   cout << table[table[0].adr].name;
							   cout << " �к���ȱ��������" << endl;
							   error_txt << table[table[0].adr].name << " �к���ȱ��������" << "\n";

							   break;
						   }
						   lex.getsym();//�ڶ�һ��
					   }
					   else
					   {
						   if (test(fsys, stabegsys))
						   {
							   cout << table[table[0].adr].name;
							   cout << " �к��зǷ�����" << endl;
							   error_txt << table[table[0].adr].name << " �к��зǷ�����" << "\n";

							   return -1;
						   }
						   if (lex.sym != semicolon)
						   {
							   cout << table[table[0].adr].name;
							   cout << " �к�������ȱ�ٷֺ�" << endl;
							   error_txt << table[table[0].adr].name << " �к�������ȱ�ٷֺ�" << "\n";

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
						 cout << " ��whileȱ��������" << endl;
						 error_txt << table[table[0].adr].name << " whileȱ��������" << "\n";

						 ss.addset(fsys, expbegsys, fsys, symnum);
						 fsys[beginsym] = true;
						 fsys[rightsym] = true;
						    if (test(fsys, stabegsys))
						   {
							 cout << table[table[0].adr].name;
							 cout << " �к��зǷ�����" << endl;
							 error_txt << table[table[0].adr].name << " �к��зǷ�����" << "\n";

							 return -1;
						    }
						 switch (lex.sym)
						    {
						     case rightsym:
								 lex.getsym();
								 break;
						     case beginsym:
										  cout << table[table[0].adr].name;
										  cout << " ��whileȱ��������" << endl;
										  error_txt << table[table[0].adr].name << " ��whileȱ��������" << "\n";

										  break;
						      default:
									cout << table[table[0].adr].name;
									cout << " ��whileȱ��������" << endl;
									error_txt << table[table[0].adr].name << " ��whileȱ��������" << "\n";

									//cout<<table[table[0].adr].name;
									//cout<<" ��whileȱ��������"<<endl;
									break;
						     }

						 if (lex.sym != beginsym)
						    {
							 cout << table[table[0].adr].name;
							 cout << " ��whileȱ�ٿ�ʼ��" << endl;
							 error_txt << table[table[0].adr].name << " ��whileȱ�ٿ�ʼ��" << "\n";

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
							 cout << " ��whileȱ���жϱ��ʽ" << endl;
							 error_txt << table[table[0].adr].name << " ��whileȱ���жϱ��ʽ" << "\n";

						     }
						    int i = pcode;
						    expression(fsys);//���ʽ����
						    if (lex.sym != rightsym)
						    {
							 cout << table[table[0].adr].name;
							 cout << " ��whileȱ��������" << endl;
							 error_txt << table[table[0].adr].name << " ��whileȱ��������" << "\n";

							 fsys[beginsym] = true;
							    if (test(fsys, stabegsys))
							    {
								 cout << table[table[0].adr].name;
								 cout << " �к��зǷ����� " << endl;
								 error_txt << table[table[0].adr].name << " �к��зǷ�����" << "\n";

								 return -1;
							    }
							    else
							    {
								 if (lex.sym != beginsym)
								   {
									 cout << table[table[0].adr].name;
									 cout << " ��whileȱ�ٿ�ʼ��" << endl;
									 error_txt << table[table[0].adr].name << " ��whileȱ�ٿ�ʼ��" << "\n";

									 statements(fsys);
								    }
								      else
								      {
										lex.getsym();
									    statements(fsys);
								       }
							    }
						    }
						 else//while(),��������
						 {
							 int jpc_pcode = pcode;
							 gen(JPC, 0, 0);
							 lex.getsym();
							 if (lex.sym != beginsym)
							    {
								 cout << table[table[0].adr].name;
								 cout << " ��whileȱ�ٿ�ʼ��" << endl;
								 error_txt << table[table[0].adr].name << " ��whileȱ�ٿ�ʼ��" << "\n";

							    }
							 else//�� {
							 {
								 lex.getsym();//�ٶ�һ����
							 }
							 statements(fsys);//���ǽ���while������
							 gen(JMP, 0, i);//������ʼwhile�жϵĵط� 
							 code[jpc_pcode].a = pcode;
						 }


					 }
					 if (lex.sym != endsym)
					 {
						 cout << table[table[0].adr].name;
						 cout << " ��whileȱ�ٽ�����" << endl;
						 error_txt << table[table[0].adr].name << " ��whileȱ�ٽ�����" << "\n";

					 }
					 else
					 {
						 lex.getsym();
					 }
	}
		break;
	case ifsym:
	{
				  lex.getsym();//��������
				  int jpccode;
				  if (lex.sym != leftsym)
				    {
					  cout << table[table[0].adr].name;
					  cout << " if��ȱ��������" << endl;
					  error_txt << table[table[0].adr].name << "  if��ȱ��������" << "\n";
					  fsys[beginsym] = true;
					  if (test(fsys, stabegsys))
							 {
								 cout << table[table[0].adr].name;
								 cout << " �к��зǷ�����" << endl;
								 error_txt << table[table[0].adr].name << "  �к��зǷ�����" << "\n";

								  return -1;
							 }
					  if (lex.sym != beginsym)
							 {
								  cout << table[table[0].adr].name;
								 cout << " if��ȱ�ٿ�ʼ��" << endl;
								 error_txt << table[table[0].adr].name << "  if��ȱ�ٿ�ʼ��" << "\n";

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
					  lex.getsym();//�ٶ�һ����
					  expression(fsys);//��ʼ���ʽ����
					  int i = pcode;//code��ǰָ��
					  gen(JPC, 0, 0);
					  if (lex.sym != rightsym)//if(
						 {
						  cout << table[table[0].adr].name;
						  cout << " ��ifȱ��������" << endl;
						  error_txt << table[table[0].adr].name << "  ifȱ��������" << "\n";

						  fsys[beginsym] = true;
						  if (test(fsys, stabegsys))
							  {
							  cout << table[table[0].adr].name;
							  cout << " �к��зǷ����� " << endl;
							  error_txt << table[table[0].adr].name << "  �к��зǷ�����" << "\n";

							  return -1;
								}
							if (lex.sym != beginsym)
								{
									cout << table[table[0].adr].name;
									cout << " ��ifȱ�ٿ�ʼ��" << endl;
									error_txt << table[table[0].adr].name << "  ifȱ�ٿ�ʼ��" << "\n";

									statements(fsys);
								}
								else
								{
									lex.getsym();
									statements(fsys);
								}
						}
					  else//if() ������if��ı��ʽ
					  {
						  lex.getsym();//�ٶ�һ��
							if (lex.sym != beginsym)
								{
									cout << table[table[0].adr].name;
									cout << " ��ifȱ�ٿ�ʼ��" << endl;
									error_txt << table[table[0].adr].name << "  ifȱ�ٿ�ʼ��" << "\n";

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
					  cout << " ��ifȱ�ٽ����� " << endl;
					  error_txt << table[table[0].adr].name << "  ifȱ�ٽ�����" << "\n";

				  }
				  //if(){}�������
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
						  cout << " ��elseȱ�ٿ�ʼ����" << endl;
						  error_txt << table[table[0].adr].name << " elseȱ�ٿ�ʼ����" << "\n";
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
						  cout << " ��elseȱ�ٽ�������" << endl;
						  error_txt << table[table[0].adr].name << " elseȱ�ٽ�������" << "\n";

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
					 cout<<" scanf�к��зǷ����� "<<endl;
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
					 cout<<" scanf��ȱ��������"<<endl;
					 }

					 }*/

					 lex.getsym();
					 if (lex.sym != leftsym)//ֱ���ҵ��ֺŻ�����俪ͷ��������һ����䴦��
					 {
						 cout << table[table[0].adr].name;
						 cout << " ��scanfȱ��������" << endl;
						 error_txt << table[table[0].adr].name << " ��scanfȱ��������" << "\n";

						 if (test(fsys, stabegsys))
						 {
							 cout << table[table[0].adr].name;
							 cout << " �к��зǷ����� " << endl;
							 error_txt << table[table[0].adr].name << " �к��зǷ�����" << "\n";

							 return -1;
						 }
						 else
						 {
							 if (lex.sym != semicolon)
							 {
								 cout << table[table[0].adr].name;
								 cout << " ��scanfȱ�ٷֺ�" << endl;
								 error_txt << table[table[0].adr].name << " ��scanfȱ�ٷֺ�" << "\n";

								 break;
							 }
							 lex.getsym();
						 }
					 }
					 else//scanf(
					 {
						 lex.getsym();
						 if (lex.sym != ident)//ֱ���ҵ��ֺŻ�����俪ͷ��������һ����䴦��
						 {
							 cout << table[table[0].adr].name;
							 cout << " ��scanfȱ�ٱ���" << endl;
							 error_txt << table[table[0].adr].name << " ��scanfȱ�ٱ���" << "\n";

							 if (test(fsys, stabegsys))
							 {
								 cout << table[table[0].adr].name;
								 cout << " �к��зǷ����� " << endl;
								 error_txt << table[table[0].adr].name << "�к��зǷ�����" << "\n";

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
												   cout << " ��scanfȱ��������" << endl;
												   error_txt << table[table[0].adr].name << " ��scanfȱ��������" << "\n";

												   break;
								 }
								 default:
								 {
											cout << table[table[0].adr].name;
											cout << " ��scanfȱ��������" << endl;
											error_txt << table[table[0].adr].name << " ��scanfȱ��������" << "\n";

											//cout<<table[table[0].adr].name;
											//cout<<" ��scanfȱ�ٷֺ�"<<endl;
											break;
								 }

								 }
								 if (lex.sym != semicolon)
								 {
									 cout << table[table[0].adr].name;
									 cout << " ��scanfȱ�ٷֺ�" << endl;
									 error_txt << table[table[0].adr].name << " ��scanfȱ�ٷֺ�" << "\n";

								 }
								 else
								 {
									 lex.getsym();
								 }
							 }
						 }
						 else//scanf(x
						 {
							 //����
							 int i;
							 i = position(lex.id, var);
							 if (i == 0)
							 {
								 cout << table[table[0].adr].name;
								 cout << " ��scanfʹ��δ�������" << endl;
								 error_txt << table[table[0].adr].name << " ��scanfʹ��δ�������" << "\n";
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
												  cout << " ��scanfȱ�ٷֺ�" << endl;
												  error_txt << table[table[0].adr].name << " ��scanfȱ�ٷֺ�" << "\n";

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
											   cout << " ��scanfȱ��������" << endl;
											   error_txt << table[table[0].adr].name << " ��scanfȱ��������" << "\n";

											   break;
							 }
							 default:
							 {
										cout << table[table[0].adr].name;
										cout << " ��scanfȱ��������" << endl;
										error_txt << table[table[0].adr].name << " ��scanfȱ��������" << "\n";

										cout << table[table[0].adr].name;
										cout << " ��scanfȱ�ٷֺ�" << endl;
										error_txt << table[table[0].adr].name << " ��scanfȱ�ٷֺ�" << "\n";

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
					  if (lex.sym != leftsym)//ֱ���ҵ��ֺŻ�����俪ͷ��������һ����䴦��
					  {
						  cout << table[table[0].adr].name;
						  cout << " ��printfȱ��������" << endl;
						  error_txt << table[table[0].adr].name << " ��printfȱ��������" << "\n";

						  fsys[semicolon] = true;
						  fsys[endsym] = true;
						  if (test(fsys, stabegsys))
						  {
							  cout << table[table[0].adr].name;
							  cout << " �к��зǷ����� " << endl;
							  error_txt << table[table[0].adr].name << " �к��зǷ�����" << "\n";

							  return -1;
						  }
						  else
						  {
							  if (lex.sym != semicolon)
							  {
								  cout << table[table[0].adr].name;
								  cout << " ��printfȱ�ٷֺ�" << endl;
								  error_txt << table[table[0].adr].name << " ��printfȱ�ٷֺ�" << "\n";


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
							  cout << " ��printfȱ�ٱ��ʽ" << endl;
							  error_txt << table[table[0].adr].name << " ��printfȱ�ٱ��ʽ" << "\n";

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
											cout << " ��printfȱ��������" << endl;
											error_txt << table[table[0].adr].name << " ��printfȱ��������" << "\n";

											break;
						  }
						  default:
						  {
									 cout << table[table[0].adr].name;
									 cout << " ��printfȱ��������" << endl;
									 error_txt << table[table[0].adr].name << " ��printfȱ��������" << "\n";

									 //cout<<table[table[0].adr].name;
									 //cout<<" ��printfȱ�ٷֺ�"<<endl;
						  }
							  break;
						  }

						  if (lex.sym != semicolon)
						  {
							  cout << table[table[0].adr].name;
							  cout << " ��printfȱ�ٷֺ�" << endl;
							  error_txt << table[table[0].adr].name << " ��printfȱ�ٷֺ�" << "\n";

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
				  if (lex.sym != leftsym) //return  �ҵ��ֺŻ�����һ����俪ͷ
				  {
					  cout << table[table[0].adr].name;
					  cout << " ��returnȱ��������" << endl;
					  error_txt << table[table[0].adr].name << "  ��returnȱ��������" << "\n";

					  if (test(fsys, stabegsys))
					  {
						  cout << table[table[0].adr].name;
						  cout << " �к��зǷ����� " << endl;
						  error_txt << table[table[0].adr].name << "�к��зǷ�����" << "\n";

						  return -1;
					  }
					  else
					  {
						  if (!expbegsys[lex.sym])
						  {
							  cout << table[table[0].adr].name;
							  cout << " ��returnȱ�ٱ��ʽ" << endl;
							  error_txt << table[table[0].adr].name << "  ��returnȱ�ٱ��ʽ" << "\n";

						  }
						  expression(fsys);
						  switch (lex.sym)
						  {
						  case rightsym:lex.getsym(); break;
						  case semicolon:
						  {
											cout << table[table[0].adr].name;
											cout << " ��returnȱ��������" << endl;
											error_txt << table[table[0].adr].name << "  ��returnȱ��������" << "\n";

											//lex.getsym();
											break;
						  }
						  default:
						  {
									 cout << table[table[0].adr].name;
									 cout << " ��returnȱ��������" << endl;
									 error_txt << table[table[0].adr].name << "  ��returnȱ��������" << "\n";

									 //cout<<table[table[0].adr].name;
									 //cout<<" ��returnȱ�ٷֺ�"<<endl;
									 break;

						  }

						  }
						  if (lex.sym != semicolon)
						  {
							  cout << table[table[0].adr].name;
							  cout << " ��returnȱ�ٷֺ�" << endl;
							  error_txt << table[table[0].adr].name << "  ��returnȱ�ٷֺ�" << "\n";

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
										   cout << " ��returnȱ�ٷֺ�" << endl;
										   error_txt << table[table[0].adr].name << "  ��returnȱ�ٷֺ�" << "\n";

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
										cout << " ��returnȱ��������" << endl;
										error_txt << table[table[0].adr].name << "  ��returnȱ��������" << "\n";

										break;
					  }
					  default:
					  {
								 cout << table[table[0].adr].name;
								 cout << " ��returnȱ��������" << endl;
								 error_txt << table[table[0].adr].name << "  ��returnȱ��������" << "\n";

								 cout << table[table[0].adr].name;
								 cout << " ��returnȱ�ٷֺ�" << endl;
								 error_txt << table[table[0].adr].name << "  ��returnȱ�ٷֺ�" << "\n";

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
					cout << " �г�����ƥ���else" << endl;
					error_txt << table[table[0].adr].name << "  �г�����ƥ���else" << "\n";

					if (test(fsys, stabegsys))
					{
						cout << table[table[0].adr].name;
						cout << " �к��зǷ����� " << endl;
						error_txt << table[table[0].adr].name << "  �к��зǷ�����" << "\n";

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
			   cout << " �г��ַǷ��ɷ�" << endl;
			   error_txt << table[table[0].adr].name << "  �г��ַǷ��ɷ�" << "\n";

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
						  //cout<<"�Զ��庯������"<<endl;
						  i = position(lex.id, procedur);
						  if (i != 0)
						  {
							  if (table[i].kind == procedur)
							  {
								  cout << table[table[0].adr].name;
								  cout << " �е�����һ���޷���ֵ�ĺ�����������������߸�ֵ�����ܻᷢ������" << endl;
							  }
						  }
						  gen(CAL, table[table[0].adr].level + 1 - table[i].level, table[i].adr);
						  lex.getsym();
						  if (lex.sym != rightsym)
						  {
							  cout << table[table[0].adr].name;
							  cout << " �к���ȱ��������" << endl;
							  error_txt << table[table[0].adr].name << "  �к���ȱ��������" << "\n";


							  break;
						  }
						  lex.getsym();
					  }
					  else
					  {
						  //cout<<"��������"<<endl;
						  i = position(lex.id, var);
						  if (i == 0)
						  {
							  cout << table[table[0].adr].name;
							  cout << " ��ʹ��δ�������  " << lex.id << endl;
							  error_txt << table[table[0].adr].name << "  ��ʹ��δ�������" << "\n";

							  if (test(fsys, facbegsys))
							  {
								  cout << table[table[0].adr].name;
								  cout << " �к��зǷ����� " << endl;
								  error_txt << table[table[0].adr].name << "  �к��зǷ�����" << "\n";

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
							cout << " �к��зǷ����ʽ" << endl;
							error_txt << table[table[0].adr].name << "  �к��зǷ����ʽ" << "\n";

							if (test(fsys, stabegsys))
							{
								cout << table[table[0].adr].name;
								cout << " �к��зǷ�����" << endl;
								error_txt << table[table[0].adr].name << "  �к��зǷ�����" << "\n";

								return -1;
							}
							break;
						}
						if (lex.sym != rightsym)
						{
							cout << table[table[0].adr].name;
							cout << " �б��ʽȱ��������" << endl;
							error_txt << table[table[0].adr].name << "  �б��ʽȱ��������" << "\n";

							break;
							//return 1;
						}
						lex.getsym();
		}
			break;
		case rightsym:
			//cout<<"�����ж�ȡ����"<<endl;
			//cout<<"�Զ��庯������"<<endl;
			/*i = position(lex.id,procedur);
			if (i==0)
			{
			cout<<"�޴˺���"<<endl;
			}
			gen(CAL,table[i].level - table[table[0].adr].level,table[i].adr);*/
		{
						 cout << table[table[0].adr].name;
						 cout << " �к��зǷ�������" << endl;
						 error_txt << table[table[0].adr].name << "  �к��зǷ�������" << "\n";

						 lex.getsym();
						 return 0;
		}
		default:
		{
				   /*cout<<table[table[0].adr].name;
				   cout<<" �к��зǷ�����"<<endl;
				   bool fsys1[symnum];
				   symcopy(stabegsys,fsys1);//��俪ʼ���ֺţ�. ��}��+��-��/��*��
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
		cout << " ��ȱ�ٽ�������" << endl;
		error_txt << table[table[0].adr].name << "  ��ȱ�ٽ�������" << "\n";

		return -1;
	}

	while (1)
	{
		/*if (lex.sym == intsym || lex.sym == voidsym)
		{
		return 0;//���������ͷ���
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
			cout << " ��ȱ�ٽ�������" << endl;
			error_txt << table[table[0].adr].name << "  ��ȱ�ٽ�������" << "\n";

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
	cout << "���ǵ�ѭ��ִ�еĻ�������м�һ������ı�������⣬ʣ�µĶ����ܵ�Ӱ��\n���ԣ�û�иĳ�table_(x).txt��ʽ��" << endl;
	cout << "������ִ�к����ɵ��м�����ڣ�code.txt��\n���������result.txt, ������Ϣ��error.txt��" << endl;
	cout << "�������ڴ�����������Ƿȱ�����ĵ���Ҫ������й��ܶ���ʵ�֡�" << endl;
	cout << "��ӭ����C0������--�Ż��İ�" << endl;
	error_txt.open("error.txt", ios::out);
	fstream inte;
	inte.open("result.txt", ios::out);
	bool b[symnum];//��ʼ���ż�
	symcopy(allfalse, b);
	ss.addset(b, stabegsys, delbegsys, symnum);//���������ļ���
	b[period] = true;//������.
	init();//��һЩ��ʼ��

	allstr = 'y';
	cout << "�Ƿ��г�Դ��? Y/N" << endl;
	inte << "�Ƿ��г�Դ��? Y/N" <<"\n";
	cin >> allstr;
	inte << allstr << "\n";
	inspri = 'y';
	cout << "�Ƿ��г�ָ��? Y/N" << endl;
	inte << "�Ƿ��г�ָ��? Y/N" << "\n";
	cin >> inspri;
	inte << inspri << "\n";
	mainblock(0, b);
	//�������main����
	//��unsertain �еĶ������ϣ�����ϣ��򱨴�
	uncertain();
	if (allstr == 'Y' || allstr == 'y')
	{
		cout << "Դ��Ϊ��" << endl;
		for (int i = 0; i < lex.all.length(); i++)
		{
			cout << lex.all[i];
		}
		cout << endl << endl;
	}
	if (inspri == 'Y' || inspri == 'y')
	{
		insprint();//���ָ��
		cout << endl;
	}
       inswriter();//��ָ��д��codetxt��
	   inte.close();
	   inter.start();//��code.txt�����ָ��ִ��
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
		//�� l a д���ļ�
		out << code[i].l << " " << code[i].a << "\n";
		i++;
		if (i >= 200)
		{
			cout << "ָ�����" << endl;
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
				cout << unadd[i].proc << " �е�����δ���庯�� " << unadd[i].name << endl;
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
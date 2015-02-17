#include "uncertainadd.h"


uncertainadd::uncertainadd()
{
	codeadr = -1;
	name = "";
	proc = "";
}
uncertainadd::uncertainadd(int a, string s1)
{
	codeadr = a;
	name = s1;
}


uncertainadd::~uncertainadd(void)
{
}

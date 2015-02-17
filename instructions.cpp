#include "instructions.h"
ins::ins(void)
{
	f = NUL;
	l = -1;
	a = -1;
}
ins::~ins(void)
{
}
ins::ins(enum fct ff, int ll, int aa)
{
	f = ff;
	l = ll;
	a = aa;
}
void ins::set(enum fct ff, int ll, int aa)
{
	f = ff;
	l = ll;
	a = aa;
}
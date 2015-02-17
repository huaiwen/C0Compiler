#include "nametable.h"
nametable::nametable()
{
	//val = -99999999;
	adr = -99999999;
	name = "";
}
nametable::~nametable(void)
{
}
nametable::nametable(string s1, int a, int b, string s2)
{
	name = s1;
	//val = a;
	level = b;
	belongto = s2;
	kind = var;
	adr = -1;
}
nametable::nametable(string s1, int a, string s2)
{
	name = s1;
	level = a;
	belongto = s2;
	kind = procedur;
	adr = -1;
	size = -1;
}

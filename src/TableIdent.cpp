#include "../include/TableIdent.h"
#include <string.h>


int Table_ident::put(const char *buf)
{
	for (int j = 1; j < top; j++)
		if (!strcmp(buf, p[j].get_name()))
			return j;
	p[top].put_name(buf);
	++top;
	return top - 1;
}
Table_ident::Table_ident(int max_size)
{
	p = new Ident[size = max_size];
	top = 1;
}

Ident& Table_ident::operator[](int k){
	return p[k];
}

Table_ident::~Table_ident()
{
	delete[]p;
}

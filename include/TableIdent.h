#ifndef TABLEIDENT_H
#define TABLEIDENT_H
#include "Ident.h"

class Table_ident
{
	Ident      * p;
	int          size;
	int          top;
public:
	Table_ident(int);
	Table_ident() {};
	~Table_ident();
	Ident      & operator[] (int);
	int          put(const char *);
};

#endif

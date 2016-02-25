#ifndef POLIZ_H
#define POLIZ_H
#include "Token.h"

class Poliz
{
	Token        * p;
	int          size;
	int          free;
public:
	Poliz(int);
	~Poliz();
	void         put_lex(Token token);
	void         put_lex(Token token, int place);
	void         blank();
	int          get_free();
	Token        & operator[] (int index);
	void         print();
};
#endif // !POILZ_H


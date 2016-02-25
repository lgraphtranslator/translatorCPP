#include "../include/Poliz.h"

Poliz::Poliz(int max_size)
{
	p = new Token[size = max_size];
	free = 0;
}
Poliz::~Poliz() { delete[] p; }

void         Poliz::put_lex(Token token)
{
	p[free] = token;
	free++;
}
void        Poliz::put_lex(Token token, int place) { p[place] = token; }
void         Poliz::blank() { free++; }
int          Poliz::get_free() { return free; }
Token &       Poliz:: operator[] (int index)
{
	if (index > size)
		throw "POLIZ:out of array";
	else
		if (index > free)
			throw "POLIZ:indefinite element of array";
		else
			return p[index];
}
void         Poliz::print()
{
	for (int i = 0; i < free; ++i)
		cout << p[i];
}

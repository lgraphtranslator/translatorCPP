#ifndef TOKEN_H
#define TOKEN_H
#include "TokenType.h"
#include <iostream>
using namespace std;

class Token
{
	type_of_token token_type;
	int value;
public:
	Token(type_of_token type = TOKEN_NULL, int value = 0);
	type_of_token  get_type();
	int          get_value();
	friend ostream & operator<< (ostream&, Token);
};
#endif


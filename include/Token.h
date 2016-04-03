#ifndef TOKEN_H
#define TOKEN_H
#include "TokenType.h"
#include <iostream>
using namespace std;

class Token
{
	type_of_token token_type;
	int value;
	string str;
public:
	Token(type_of_token type = TOKEN_NULL, int value = 0);
	Token(type_of_token type , string str);
	type_of_token  get_type();
	int          get_value();
	string get_string();
	~Token() { }
	friend ostream & operator<< (ostream&, Token);
};
#endif


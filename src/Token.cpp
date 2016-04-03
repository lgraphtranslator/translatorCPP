#include "../include/Token.h"

Token::Token(type_of_token type , int value ) :token_type(type), value(value),str(){
}

Token::Token(type_of_token type, string str) : token_type(type), str(str),value(0) {
}

type_of_token Token::get_type() {
	return token_type;
}

int Token::get_value() {
	return value;
}

string Token::get_string()
{
	return str;
}

ostream& operator<<(ostream & stream, Token token) {
	stream << '(' << token.token_type << ',' << token.value << ");";
	return stream;
}

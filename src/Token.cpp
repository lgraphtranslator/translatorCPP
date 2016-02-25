#include "../include/Token.h"

Token::Token(type_of_token type , int value ) :token_type(type), value(value)
{

}

type_of_token Token::get_type() {
	return token_type;
}

int Token::get_value() {
	return value;
}

ostream& operator<<(ostream & stream, Token token) {
	stream << '(' << token.token_type << ',' << token.value << ");";
	return stream;
}

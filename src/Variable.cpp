#include "../include/Variable.h"
#include <string>


char Variable::getCharValue() {
	return chValue;
}
void Variable::putCharValue(char ch) {
	chValue = ch;
}
void Variable::putIntValue(int val) {
	value = val;
}
int Variable::getValue() {
	return value;
}
type_state Variable::getType() {
	return type;
}
void Variable::putType(type_state tstate) {
	type = tstate;
}
Variable::Variable(int value):Variable() {
	this->value = value;
}


Variable& Variable::operator=(Variable var)
{
	value = var.value;
	type = var.type;
	str = var.str;
	chValue = var.chValue;
	return *this;
}

Variable::~Variable() { }


Variable::Variable():str() {
	value = 0;
	chValue = 'a';
	type = INT;
}

std::string Variable::getStringValue()
{
	return str;
}

void Variable::putStringValue(std::string stri)
{
	str = stri;
}

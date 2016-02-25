#include "../include/Variable.h"

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
Variable::Variable(int value) {
	this->value = value;
}
Variable&  Variable::operator=(Variable var) {
	value = var.value;
	chValue = var.chValue;
	type = var.type;
	return *this;
}

Variable::Variable() {}

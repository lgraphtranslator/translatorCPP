#ifndef VARIABLE_H
#define VARIABLE_H

enum type_state {CHAR,BOOL,INT};
class Variable
{
private:
		int value;
		char chValue;
		type_state type;
public:
	char getCharValue();
	void putCharValue(char ch);
	void putIntValue(int val);
	int getValue();
	type_state getType();
	void putType(type_state tstate);
	Variable(int value);
	Variable&  operator=(Variable var);
	Variable();
};
#endif 
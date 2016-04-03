#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>


enum type_state {CHAR,BOOL,INT,STRING};
class Variable
{
private:
		int value;
		char chValue;
		type_state type;
		std::string  str;
public:
	char getCharValue();
	void putCharValue(char ch);
	std::string getStringValue();
	void putStringValue(std::string str);
	void putIntValue(int val);
	int getValue();
	type_state getType();
	void putType(type_state state);
	Variable(int value);
	Variable&  operator=(Variable var);
	~Variable();
	Variable();
};
#endif 

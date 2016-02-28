#ifndef EXECUTER_H
#define EXECUTER_H
#include "Token.h"
#include "Poliz.h"
#include <stack>
#include "Variable.h"
#include "TableIdent.h"

class Executer
{
	Token       ex_token;
	Table_ident* TID;
public:
	void         execute(Poliz & prog,Table_ident* TID);
	Variable& POP(stack<Variable> * stack);
};
#endif

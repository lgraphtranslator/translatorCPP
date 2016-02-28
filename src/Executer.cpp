#define _CRT_SECURE_NO_WARNINGS
#include "../include/Executer.h"
#include <stdio.h>
#include <cstring>

Variable& Executer::POP(stack<Variable>* stack)
{
	Variable& current = stack->top();
	stack->pop();
	return current;
}


void Executer::execute(Poliz & prog,Table_ident* TID)
{
	this->TID = TID;
	Variable var;
	char ch;
	int val;
	stack<Variable> args;
	int i, j, index = 0, size = prog.get_free();
	while (index < size)
	{
		ex_token = prog[index];
		switch (ex_token.get_type())
		{
		case POLIZ_ADDRESS:
		case POLIZ_LABEL:
			args.push(ex_token.get_value());
			break;
		case TOKEN_NUM:
			val = (int)ex_token.get_value();
			var.putIntValue(val);
			var.putType(INT);
			args.push(var);
			break;
		case TOKEN_TRUE:case TOKEN_FALSE:
			val = (int)ex_token.get_value();
			var.putIntValue(val);
			var.putType(BOOL);
			args.push(var);
			break;
		case TOKEN_CHAR:
			ch = (char)ex_token.get_value();
			var.putCharValue(ch);
			var.putType(CHAR);
			args.push(var);
			break;
		case TOKEN_ID:
			i = ex_token.get_value();
			if ((*TID)[i].get_assign())
			{
				args.push((*TID)[i].get_value());
				break;
			}
			else
				throw "POLIZ: indefinite identifier";
		case TOKEN_NOT:
			args.push(!POP(&args).getValue());
			break;
		case TOKEN_OR:
			i = POP(&args).getValue();
			args.push(POP(&args).getValue() || i);
			break;
		case TOKEN_AND:
			i = POP(&args).getValue();
			args.push(POP(&args).getValue() && i);
			break;
		case POLIZ_GO:
			index = POP(&args).getValue() - 1;
			break;
		case POLIZ_FGO:
			i = POP(&args).getValue();
			if (!POP(&args).getValue()) 
				index = i - 1;
			break;
		case TOKEN_WRITE:
			var = POP(&args);
			if (var.getType() == CHAR )
				cout << var.getCharValue() << endl;
			else
				cout << var.getValue() << endl;
			break;
		case TOKEN_READ:
		{
			Variable localVar;
			char* str = new char[20];
			i = POP(&args).getValue();
			if (((*TID)[i].get_type() == TOKEN_INT) || ((*TID)[i].get_type() == TOKEN_CHAR))
			{
				
				cout << "Input  value for " << (*TID)[i].get_name() << endl;
				if ((*TID)[i].get_type() == TOKEN_INT)
				{
					cout << " (INT) :";
					int localINT;
					cin >>localINT;
					localVar.putIntValue(localINT);
					localVar.putType (INT);
				}
				else if ((*TID)[i].get_type() == TOKEN_CHAR)
				{
					cout << "(CHAR) :";
					char localChar;
					cin >> localChar;
					cin.get();
					localVar.putCharValue(localChar);
					localVar.putType(CHAR);
				}
			}
			else
			{			
				cout << "Input boolean value (true or false) for "<< (*TID)[i].get_name() << endl;
				cin >> str;
				if (!strcmp(str, "true"))
				{
					localVar.putIntValue(1); 
					localVar.putType(BOOL);
				}
				else
					if (!strcmp(str, "false"))
					{
						localVar.putIntValue(0); 
						localVar.putType(BOOL);
					}
					else
						throw "Error in input:true/false";
			}
			(*TID)[i].put_value(localVar);
			(*TID)[i].put_assign();
			break;
		}
		case TOKEN_PLUS:
			args.push(POP(&args).getValue() + POP(&args).getValue());
			break;
		case TOKEN_TIMES:
			args.push(POP(&args).getValue() * POP(&args).getValue());
			break;
		case TOKEN_MINUS:
			i = POP(&args).getValue();
			args.push(POP(&args).getValue() - i);
			break;
		case TOKEN_SLASH:
			i = POP(&args).getValue();
			if (i != 0)
			{
				args.push(POP(&args).getValue() / i);
				break;
			}
			else
				throw "POLIZ:divide by zero";
		case TOKEN_EQ:
			args.push(POP(&args).getValue() == POP(&args).getValue());
			break;
		case TOKEN_LSS:
			i = POP(&args).getValue();
			args.push(POP(&args).getValue() < i);
			break;
		case TOKEN_GTR:
			i = POP(&args).getValue();
			args.push(POP(&args).getValue() > i);
			break;
		case TOKEN_LEQ:
			i = POP(&args).getValue();
			args.push(POP(&args).getValue() <= i);
			break;
		case TOKEN_GEQ:
			i = POP(&args).getValue();
			args.push(POP(&args).getValue() >= i);
			break;
		case TOKEN_NEQ:
			i = POP(&args).getValue();
			args.pop();
			args.push(POP(&args).getValue() != i);
			break;
		case TOKEN_ASSIGN:
			var = POP(&args);
			j = POP(&args).getValue();
			(*TID)[j].put_value(var);
			(*TID)[j].put_assign();
			break;
		default:
			throw "POLIZ: unexpected elem";
		}
		++index;
	};
	cout << "Finish of executing!!!" << endl;
}

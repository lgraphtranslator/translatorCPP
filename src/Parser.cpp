#include "../include/Parser.h"


Parser::Parser(const char* program):scanner(program),poliz(100)
{
	TID = scanner.getTID();
}

Table_ident* Parser::getTID()
{
	return TID;
}

void Parser::Reset(stack<int> *stack)
{
	while (!stack->empty())
		stack->pop();
}

void Parser::declare(type_of_token type)
{
	int i;
	while (!st_int.empty())
	{
		i = st_int.top();
		st_int.pop();
		if ((*TID)[i].get_declare())
			throw "twice";
		else
		{
			(*TID)[i].put_declare();
			(*TID)[i].put_type(type);
		}
	}
}

bool Parser::CheckHeadHooks(int hook)
{
	if (!hooks.empty())
	{
		int currentHead = hooks.top();
		if (currentHead == hook)
		{
			hooks.pop();
			return true;
		}	
	}
	return false;
}

void        Parser::gl()
{
	token = scanner.get_token();
	c_type = token.get_type();
	c_val = token.get_value();
}


void Parser::PopulatePoliz()
{
	LGRAPH state = H;
	gl();
	while (token.get_type() != TOKEN_FIN)
	{
		switch (state)
		{
		case H:
			if (token.get_type() == TOKEN_PROGRAM)
				state = D;
			else
				throw "Exception program";
			break;
		case D:
			if (token.get_type() == TOKEN_VAR)
			{
				Reset(&st_int);
				state = D1;
			}
			else
				throw "Exception var";
			break;
		case D1:
			if (token.get_type() == TOKEN_ID)
			{
				state = D2;
				st_int.push(c_val);
			}
			else
				throw "Exception Ident";
			break;
		case D2:
			if (token.get_type() == TOKEN_COLON)
			{
				state = D3;
				break;
			}
			if (token.get_type() == TOKEN_COMMA)
			{
				state = D1;
				break;
			}
			else
				throw "Exception colon or comma";
			break;
		case D3:
			if (token.get_type() == TOKEN_INT)
			{
				state = D4;
				declare(TOKEN_INT);
				break;
			}
			if (token.get_type() == TOKEN_CHAR)
			{
				state = D4;
				declare(TOKEN_CHAR);
				break;
			}
			if (token.get_type() == TOKEN_BOOL)
			{
				state = D4;
				declare(TOKEN_BOOL);
				break;
			}
			else
				throw "Invalid type";
			break;
		case D4:
			if (token.get_type() == TOKEN_SEMICOLON)
			{
				state = B;
				break;
			}
			else
				throw "Exception semicolon";
			break;
		case B:
			if (token.get_type() == TOKEN_BEGIN)
			{
				state = S;
				hooks.push(1); //put (b
				break;
			}
			if (token.get_type() == TOKEN_VAR)
			{
				state = D1;
				Reset(&st_int);
				break;
			}
			else
				throw "Exception break";
			break;
		case S:
			if (token.get_type() == TOKEN_ID)
			{
				state = M1;
				poliz.put_lex(Token(POLIZ_ADDRESS, c_val));
				break;
			}
			if (token.get_type() == TOKEN_END)
			{
				state = E;
				break;
			}
			if (token.get_type() == TOKEN_WRITE)
			{
				state = W1;
				break;
			}
			if (token.get_type() == TOKEN_READ)
			{
				state = R1;
				break;
			}
			else
				throw "invalid begin end";
			break;
		case R1:
			if (token.get_type() == TOKEN_LPAREN)
			{
				state = R2;
				break;
			}
			else
				throw "Exception R1 -> R2";
		case R2:
			if (token.get_type() == TOKEN_ID)
			{
				state = R3;
				poliz.put_lex(Token(POLIZ_ADDRESS, c_val));
				break;
			}
		case R3:
			if (token.get_type() == TOKEN_RPAREN)
			{
				state = SF;
				poliz.put_lex(Token(TOKEN_READ));
				break;
			}
		case W1:
			if (token.get_type() == TOKEN_LPAREN)
			{
				state = V1;
				break;
			}
			else
				throw "Exception W1 -> V1";
		case M1:
			if (token.get_type() == TOKEN_ASSIGN)
			{
				state = V1;
				hooks.push(2); // put (=
				break;
			}
			throw "Exception assign";
		case V1:
			state = B1;
			hooks.push(3);// put (3
			continue;
		case B1:
			if (token.get_type() == TOKEN_ID)
			{
				state = B2;
				poliz.put_lex(Token(TOKEN_ID, c_val));
				break;
			}
			if (token.get_type() == TOKEN_NUM)
			{
				state = B2;
				poliz.put_lex(token);
				break;
			}
			if (token.get_type() == TOKEN_LPAREN)
			{
				state = S1;
				hooks.push(6);
				break;
			}
			if (token.get_type() == TOKEN_TRUE)
			{
				state = B2;
				poliz.put_lex(Token(TOKEN_TRUE, 1));
				break;
			}
			if (token.get_type() == TOKEN_FALSE)
			{
				state = B2;
				poliz.put_lex(Token(TOKEN_FALSE, 0));
				break;
			}
			if (token.get_type() == TOKEN_CHAR)
			{
				state = B2;
				poliz.put_lex(Token(TOKEN_CHAR, c_val));
				break;
			}
			if (token.get_type() == TOKEN_NOT)
			{
				state = B1;
				hooks.push(14);
				break;
			}
			else
				throw "Invalid B1->B2 ";
		case B2:
			if (CheckHeadHooks(7))
				poliz.put_lex(Token(TOKEN_TIMES));
			else
				if (CheckHeadHooks(8))
					poliz.put_lex(Token(TOKEN_SLASH));
				else
					if (CheckHeadHooks(14))
						poliz.put_lex(Token(TOKEN_NOT));
			state = A2;
			continue;
		case A2:
			if (token.get_type() == TOKEN_TIMES)
			{
				state = A1;
				hooks.push(7);
				break;
			}
			if (token.get_type() == TOKEN_SLASH)
			{
				state = A1;
				hooks.push(8);
				break;
			}
			if (CheckHeadHooks(4))
				poliz.put_lex(Token(TOKEN_PLUS));
			else
				if (CheckHeadHooks(5))
					poliz.put_lex(Token(TOKEN_MINUS));
			state = S2;
			continue;
		case A1:
			state = B1;
			continue;
		case S1:
			state = B1;
			continue;
		case S2:
			if (token.get_type() == TOKEN_PLUS)
			{
				state = S1;
				hooks.push(4);
				break;
			}
			if (token.get_type() == TOKEN_MINUS)
			{
				state = S1;
				hooks.push(5);
				break;
			}
			if (token.get_type() == TOKEN_RPAREN)
			{
				state = B2;
				if (CheckHeadHooks(6))
					break;
				else
				{
					state = V2;
					continue;
				}
			}
			if (token.get_type() == TOKEN_LEQ)
			{
				state = B1;
				hooks.push(10);
				break;
			}
			if (token.get_type() == TOKEN_GEQ)
			{
				state = B1;
				hooks.push(9);
				break;
			}
			if (token.get_type() == TOKEN_LSS)
			{
				state = B1;
				hooks.push(12);
				break;
			}
			if (token.get_type() == TOKEN_GTR)
			{
				state = B1;
				hooks.push(11);
				break;
			}
			if (token.get_type() == TOKEN_EQ)
			{
				state = B1;
				hooks.push(13);
				break;
			}
			if (CheckHeadHooks(3))
			{
				state = V2;
				continue;
			}
			// 9 = '>=' 10 = '<=' 11 = '>' 12 = '<' 13 = '='
			if (CheckHeadHooks(9))
			{
				state = S2;
				poliz.put_lex(Token(TOKEN_GEQ));
				continue;
			}
			if (CheckHeadHooks(10))
			{
				state = S2;
				poliz.put_lex(Token(TOKEN_LEQ));
				continue;
			}
			if (CheckHeadHooks(11))
			{
				state = S2;
				poliz.put_lex(Token(TOKEN_GTR));
				continue;
			}
			if (CheckHeadHooks(12))
			{
				state = S2;
				poliz.put_lex(Token(TOKEN_LSS));
				continue;
			}
			if (CheckHeadHooks(13))
			{
				state = S2;
				poliz.put_lex(Token(TOKEN_EQ));
				continue;
			}
			else
				throw "Exception S2";
		case V2:
			if (token.get_type() == TOKEN_RPAREN)
			{
				state = W2;
				break;
			}
			state = SF;
			poliz.put_lex(Token(TOKEN_ASSIGN));
			continue;
		case W2:
			state = SF;
			poliz.put_lex(Token(TOKEN_WRITE));
			continue;
		case SF:
			if (token.get_type() == TOKEN_SEMICOLON)
			{
				state = S;
				break;
			}
			if (token.get_type() == TOKEN_END)
			{
				state = E;
				break;
			}
			break;
		case E:
			break;
		case F:
			break;
		}
		gl();
	}
}

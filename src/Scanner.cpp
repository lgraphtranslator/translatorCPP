#define _CRT_SECURE_NO_WARNINGS
#include "../include/Scanner.h"
#include <stack>
#include <cstring>
#include <stdio.h>

using namespace std;


Table_ident* Scanner::getTID()
{
	return TID;
}

Scanner::Scanner(const char * program)
{
	TID = new Table_ident(100);
	fp = fopen(program, "r");
	CS = H;
	clear();
	gc();
}

void    Scanner::clear()
{
	buf_top = 0;
	for (int j = 0; j < 80; j++)
		buf[j] = '\0';
}

void        Scanner::add()
{
	buf[buf_top++] = c;
}

int          Scanner::look(const char *buf, char **list)
{
	int i = 0;
	while (list[i])
	{
		if (!strcmp(buf, list[i]))
			return i;
		++i;
	}
	return 0;
}

void Scanner::gc()
{
	c = fgetc(fp);
}

Token Scanner::get_token()
{
	int d, j;

	CS = H;
	do
	{
		switch (CS)
		{
		case H:
			if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
				gc();
			else if (isalpha(c))
			{
				clear();
				add();
				gc();
				CS = IDENT;
			}
			else if (isdigit(c))
			{
				d = c - '0';
				gc();
				CS = NUMB;
			}
			else if (c == '{')
			{
				gc();
				CS = COM;
			}
			else if (c == '\'')
			{
				gc();
				CS = Z;
			}
			else if (c == ':' || c == '<' || c == '>')
			{
				clear();
				add();
				gc();
				CS = ALE;
			}
			else if (c == '@')
				return Token(TOKEN_FIN);
			else if (c == '!')
			{
				clear();
				add();
				gc();
				CS = NEQ;
			}
			else
				CS = DELIM;
			break;
		case IDENT:
			if (isalpha(c) || isdigit(c))
			{
				add();
				gc();
			}
			else if (j = look(buf, TW))
				return Token(words[j], j);
			else
			{
				j = (*TID).put(buf);
				return Token(TOKEN_ID, j);
			}
			break;
		case Z:
			if (isalpha(c) || isdigit(c))
			{
				char ch = c; //saving current char value 
				gc();
				if (c == '\'')
				{
					CS = H;
					gc();
					return Token(TOKEN_CHAR, ch);
				}
			}
			else throw c;
			break;
		case NUMB:
			if (isdigit(c))
			{
				d = d * 10 + (c - '0'); gc();
			}
			else
				return Token(TOKEN_NUM, d);
			break;
		case COM:
			if (c == '}')
			{
				gc();
				CS = H;
			}
			else if (c == '@' || c == '{')
				throw c;
			else
				gc();
			break;
		case ALE:
			if (c == '=')
			{
				add();
				gc();
				j = look(buf, TD);
				return Token(dlms[j], j);
			}
			else
			{
				j = look(buf, TD);
				return Token(dlms[j], j);
			}
			break;
		case NEQ:
			if (c == '=')
			{
				add();
				gc();
				j = look(buf, TD);
				return Token(TOKEN_NEQ, j);
			}
			else
				throw '!';
			break;
		case DELIM:
			clear();
			add();
			if (j = look(buf, TD))
			{
				gc();
				return Token(dlms[j], j);
			}
			else
				throw c;
			break;
		}
	} while (true);

}


char *
Scanner::TW[] = { "", "and", "begin", "bool","char","do","else", "end", "if", "false", "int", "not", "or", "program",
"read", "then", "true", "var", "while", "write", NULL };

type_of_token
Scanner::words[] = { TOKEN_NULL, TOKEN_AND, TOKEN_BEGIN, TOKEN_BOOL,TOKEN_CHAR, TOKEN_DO, TOKEN_ELSE, TOKEN_END, TOKEN_IF, TOKEN_FALSE, TOKEN_INT,
TOKEN_NOT, TOKEN_OR, TOKEN_PROGRAM, TOKEN_READ, TOKEN_THEN, TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE, TOKEN_WRITE,TOKEN_NULL };

char *
Scanner::TD[] = { "", "@", ";", ",", ":", ":=", "(", ")", "=", "<", ">", "+", "-", "*", "/", "<=", "!=", ">=", NULL };

type_of_token
Scanner::dlms[] = { TOKEN_NULL, TOKEN_FIN, TOKEN_SEMICOLON, TOKEN_COMMA, TOKEN_COLON, TOKEN_ASSIGN, TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_EQ,
TOKEN_LSS, TOKEN_GTR, TOKEN_PLUS, TOKEN_MINUS, TOKEN_TIMES,TOKEN_SLASH, TOKEN_LEQ, TOKEN_NEQ, TOKEN_GEQ, TOKEN_NULL };

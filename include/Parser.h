#ifndef PARSER_H
#define PARSER_H
#include "Scanner.h"
#include "Poliz.h"
#include "LGRAPH.h"
#include <stack>


class Parser
{
private:
	Scanner scanner;
	stack <int> st_int;
	stack <int> hooks;
	stack <int> be;
	Token token;
	Table_ident* TID;
	type_of_token c_type;
	int c_val;
public:
	Poliz poliz;
	Parser(const char*);
	void PopulatePoliz();
	void declare(type_of_token);
	void         gl();
	Table_ident* getTID();
	bool CheckHeadHooks(int hook);
	void	Reset(stack<int>* stack);
	bool checkBeginEnd();
	bool checkElse();
	bool checkWhile();

};

#endif
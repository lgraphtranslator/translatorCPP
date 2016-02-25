#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H
#include "Parser.h"
#include "Executer.h"


class Interpretator
{
	Parser   pars;
	Executer E;
public:
	Interpretator(const char* program) :pars(program) {}
	void     interpretation();
};
#endif

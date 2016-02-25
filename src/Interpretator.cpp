#include "../include/Interpretator.h"

void Interpretator::interpretation()
{
	pars.PopulatePoliz();
	E.execute(pars.poliz,pars.getTID());
}

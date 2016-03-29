#include "../include/Interpretator.h"
#include <iostream>
int main(int count,char ** args)
{
	Interpretator inter("testdata/recursive.txt");
	inter.interpretation();
	return 0;
}

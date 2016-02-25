#include "../include/Interpretator.h"
#include <iostream>
int main()
{
	Interpretator inter("testprogram.txt");
	inter.interpretation();
	int k;
	std::cin>> k;
	return 0;
}

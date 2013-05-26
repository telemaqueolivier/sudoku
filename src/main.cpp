//============================================================================
// Name        : sudoku.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "grid.h"

using namespace std;

int main()
{
	srand(time(NULL));
	grid g;
	g.randomize();
	cout << "end main" << endl;
	return 0;
}

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
#include "utils.h"
#include "game.h"

using namespace std;

int main()
{
	srand(time(NULL));
	game sudoku(EASY);
	sudoku.run();
	cout << "end main" << endl;
	return 0;
}

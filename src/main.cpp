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

	try {
//		game sudoku(EASY);
		game sudoku;
		sudoku.run();
	} catch (unable_to_launch_game &e) {
		cout << e.what() << endl;
	}

	return 0;
}

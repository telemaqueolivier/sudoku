/*
 * grid.h
 *
 *  Created on: 25 mai 2013
 *      Author: telemaque
 */

#ifndef GRID_H_
#define GRID_H_

#include <vector>

#define NUM_CELLS_GRID 81
#define NUM_CELLS_PER_LINE 9
#define NUM_CELLS_NEIGHBORHOOD 9
#define NUM_CELLS_PER_NEIGHBORHOOD_LINE 3
#define EMPTY_CELL_VALUE 0
#define MIN_CELL_VALUE 1
#define MAX_CELL_VALUE 9

enum type_line
{
	HORIZONTAL, VERTICAL
};

class grid
{
private:
	std::vector<int> matrix;

public:
	grid();
	int& cell_at(unsigned int i, unsigned int j);
	int& cell_at(unsigned int i);
	std::vector<int> cell_neighborhood(unsigned int i, unsigned int j);
	std::vector<int> cells_on_line(type_line type, unsigned int line);
	void randomize();
	virtual ~grid();

};

#endif /* GRID_H_ */

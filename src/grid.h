/*
 * grid.h
 *
 *  Created on: 25 mai 2013
 *      Author: telemaque
 */

#ifndef GRID_H_
#define GRID_H_

#include <vector>

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
	std::vector<int> cell_neighborhood(unsigned int i, unsigned int j);
	std::vector<int> cells_on_line(type_line type, unsigned int line);
	void randomize();
	virtual ~grid();

};

#endif /* GRID_H_ */

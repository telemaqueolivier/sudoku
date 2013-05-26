/*
 * grid.cpp
 *
 *  Created on: 25 mai 2013
 *      Author: telemaque
 */
#include <algorithm>
#include <iterator>
#include "grid.h"
#include "utils.h"

#define NUM_CELLS_GRID 81
#define NUM_CELLS_PER_LINE 9
#define NUM_CELLS_NEIGHBORHOOD 9
#define NUM_CELLS_PER_NEIGHBORHOOD_LINE 3
#define EMPTY_CELL_VALUE -1
#define MIN_CELL_VALUE 1
#define MAX_CELL_VALUE 9

grid::grid() :
		matrix(NUM_CELLS_GRID, EMPTY_CELL_VALUE)
{
}

int& grid::cell_at(unsigned int i, unsigned int j)
{
	return matrix[j * NUM_CELLS_PER_LINE + i];
}

std::vector<int> grid::cell_neighborhood(unsigned int i, unsigned int j)
{
	std::vector<int> neighborhood(NUM_CELLS_NEIGHBORHOOD);
	unsigned int m = 0;
	unsigned int first_neighbor_i = i / NUM_CELLS_PER_NEIGHBORHOOD_LINE * NUM_CELLS_PER_NEIGHBORHOOD_LINE;
	unsigned int first_neighbor_j = j / NUM_CELLS_PER_NEIGHBORHOOD_LINE * NUM_CELLS_PER_NEIGHBORHOOD_LINE;

	for (unsigned int k = first_neighbor_i; k < first_neighbor_i + NUM_CELLS_PER_NEIGHBORHOOD_LINE; ++k) {
		for (unsigned int l = first_neighbor_j; l < first_neighbor_j + NUM_CELLS_PER_NEIGHBORHOOD_LINE; ++l) {
			neighborhood[m] = cell_at(k, l);
			++m;
		}
	}

	return neighborhood;
}

std::vector<int> grid::cells_on_line(type_line type, unsigned int line)
{
	std::vector<int> cells(NUM_CELLS_PER_LINE);
	unsigned int l = 0;

	for (unsigned int k = 0; k < NUM_CELLS_PER_LINE; ++k) {
		switch (type) {
		case HORIZONTAL:
			cells[l] = cell_at(k, line);
			break;
		case VERTICAL:
			cells[l] = cell_at(line, k);
			break;
		}

		++l;
	}

	return cells;
}

void grid::randomize()
{
	for (unsigned int i = 0; i < NUM_CELLS_PER_LINE; ++i) {
		for (unsigned int j = 0; j < NUM_CELLS_PER_LINE; ++j) {
			std::vector<int> constraint_cells = cell_neighborhood(i, j);
			std::vector<int> temp_cells = cells_on_line(HORIZONTAL, j);
			std::vector<int> possible_values;

			copy(temp_cells.begin(), temp_cells.end(), std::back_inserter(constraint_cells));
			temp_cells = cells_on_line(VERTICAL, i);
			copy(temp_cells.begin(), temp_cells.end(), std::back_inserter(constraint_cells));
			constraint_cells.erase(std::remove(constraint_cells.begin(), constraint_cells.end(), EMPTY_CELL_VALUE), constraint_cells.end());
			possible_values = all_missing_integers_in_interval(constraint_cells, MIN_CELL_VALUE, MAX_CELL_VALUE);
			cell_at(i, j) = possible_values[generate_bounded_random_integer(0, possible_values.size() - 1)];
		}
	}
}

grid::~grid()
{
	// TODO Auto-generated destructor stub
}


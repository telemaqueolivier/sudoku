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

grid::grid() :
		matrix(NUM_CELLS_GRID, EMPTY_CELL_VALUE)
{
}

int& grid::cell_at(unsigned int i, unsigned int j)
{
	return matrix[j * NUM_CELLS_PER_LINE + i];
}

int& grid::cell_at(unsigned int i)
{
	return matrix[i];
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

#include <iostream>
void grid::randomize()
{
	for (unsigned int i = 0; i < NUM_CELLS_PER_LINE; ++i) {
		for (unsigned int j = 0; j < NUM_CELLS_PER_LINE; ++j) {
			std::vector<int> constraint_cells = cell_neighborhood(i, j);
			std::vector<int> temp_cells = cells_on_line(HORIZONTAL, j);
			std::vector<int> possible_values;

			print_vector("cell neighborhood:", constraint_cells);
			print_vector("temp cells horizontal:", temp_cells);

			copy(temp_cells.begin(), temp_cells.end(), std::back_inserter(constraint_cells));
			temp_cells = cells_on_line(VERTICAL, i);

			print_vector("temp cells vertical:", temp_cells);

			copy(temp_cells.begin(), temp_cells.end(), std::back_inserter(constraint_cells));

			print_vector("constraint_cells before erase:", constraint_cells);

			constraint_cells.erase(std::remove(constraint_cells.begin(), constraint_cells.end(), EMPTY_CELL_VALUE), constraint_cells.end());

			print_vector("constraint_cells after erase:", constraint_cells);

			possible_values = all_missing_integers_in_interval(constraint_cells, MIN_CELL_VALUE, MAX_CELL_VALUE);

			print_vector("possible values ::", possible_values);

			if (possible_values.size() > 0)
				cell_at(i, j) = possible_values[generate_bounded_random_integer(0, possible_values.size() - 1)];
			else
				std::cout << "bug" << std::endl;

			std::cout << "cell_at(" << i << "," << j << ") = " << cell_at(i, j) << std::endl;
		}
	}
}

grid::~grid()
{
	// TODO Auto-generated destructor stub
}


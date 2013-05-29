/*
 * core.cpp
 *
 *  Created on: 26 mai 2013
 *      Author: telemaque
 */
#include <algorithm>
#include <exception>
#include <iostream>
#include "core.h"
#include "utils.h"

core::core(grid *g) :
		resolved_grid(g)
{
	map_difficulty[EASY] = 9;
	map_difficulty[NORMAL] = 18;
	map_difficulty[DIFFICULT] = 36;
}

void core::mask_cells(difficulty d)
{
	int num_cells_to_mask = map_difficulty[d];
	unsigned index;
	std::vector<int> possible_indexes(NUM_CELLS_GRID);

	current_grid = *resolved_grid;
	std::generate(possible_indexes.begin(), possible_indexes.end(),
			increment(0));
	for (unsigned int i = 0; i < num_cells_to_mask; ++i)
		try {
			index = generate_bounded_random_integer(0, NUM_CELLS_GRID - 1 - i);
			current_grid.cell_at(possible_indexes[index]) = EMPTY_CELL_VALUE;
			possible_indexes.erase(possible_indexes.begin() + index);
		} catch (std::exception const &e) {
			std::cout << e.what() << std::endl;
		}
}

void core::possible_values_for_cell(unsigned int line, unsigned int column,
		std::vector<int> &values)
{
	std::vector<int> constraint_cells = current_grid.cell_neighborhood(line,
			column);
	std::vector<int> temp_cells = current_grid.cells_on_line(HORIZONTAL,
			column);

	copy(temp_cells.begin(), temp_cells.end(),
			std::back_inserter(constraint_cells));
	temp_cells = current_grid.cells_on_line(VERTICAL, line);
	copy(temp_cells.begin(), temp_cells.end(),
			std::back_inserter(constraint_cells));
	constraint_cells.erase(
			std::remove(constraint_cells.begin(), constraint_cells.end(),
					EMPTY_CELL_VALUE), constraint_cells.end());
	values = all_missing_integers_in_interval(constraint_cells, MIN_CELL_VALUE,
			MAX_CELL_VALUE);
}

void core::fill_grid_under_constraint(unsigned int line, unsigned int column,
		int val) throw (bad_cell, bad_cell_value, no_possible_cell_value)
{
	int curr_val = current_grid.cell_at(line, column);

	if (curr_val != EMPTY_CELL_VALUE || line >= NUM_CELLS_PER_LINE
			|| column >= NUM_CELLS_PER_LINE)
		throw bad_cell(line, column);
	else if (val < MIN_CELL_VALUE || val > MAX_CELL_VALUE)
		throw bad_cell_value(val);
	else {
		std::vector<int> possible_values;

		possible_values_for_cell(line, column, possible_values);
		if (possible_values.size() == 0)
			throw no_possible_cell_value(line, column);
		else if (std::find(possible_values.begin(), possible_values.end(), val)
				== possible_values.end())
			throw bad_cell_value(val);
		else
			current_grid.cell_at(line, column) = val;
	}
}

bool core::is_grid_fully_filled()
{
	for (unsigned int i = 0; i < NUM_CELLS_PER_LINE; ++i)
		for (unsigned int j = 0; j < NUM_CELLS_PER_LINE; ++j)
			if (current_grid.cell_at(i, j) == EMPTY_CELL_VALUE)
				return false;
	// std::find could be use but the design is not enough suitable

	return true;
}

grid const& core::get_current_grid() const
{
	return current_grid;
}

core::~core()
{
// TODO Auto-generated destructor stub
}


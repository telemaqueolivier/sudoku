/*
 * game.cpp
 *
 *  Created on: 26 mai 2013
 *      Author: telemaque
 */

#include "game.h"
#include <fstream>
#include <iostream>
#include <exception>
#include "utils.h"

game::game(difficulty d) :
		c(&g)
{
	load_grid_from_file("partie.txt");
	c.mask_cells(d);
}

void game::load_grid_from_file(std::string const &file_name)
{
	std::fstream file(file_name.c_str());

	if (file.is_open())
		for (unsigned int i = 0; i < NUM_CELLS_PER_LINE; ++i) {
			for (unsigned int j = 0; j < NUM_CELLS_PER_LINE; ++j) {
				if (!file.eof())
					file >> g.cell_at(i, j);
			}
		}
}

std::string const& game::choose_file_randomly_from_dir(std::vector<std::string> const &file_names)
{
	return std::string();
}

void game::run()
{
	unsigned int line, column;
	int val;

	while (!c.is_grid_fully_filled()) {
		std::cout << c.current_grid;
		std::cout << "line column value ?" << std::endl;
		std::cin >> line >> column >> val;

		try {
			c.fill_grid_under_constraint(line, column, val);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
}

game::~game()
{
	// TODO Auto-generated destructor stub
}


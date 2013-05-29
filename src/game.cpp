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
#include <cstdlib>

game::game(difficulty d) throw (unable_to_launch_game):
		c(&g) {
	load_grid_file_names("grid_names.txt");
	try {
		load_grid_randomly();
	} catch (std::exception &e) {
		throw unable_to_launch_game(e.what());
	}
	c.mask_cells(d);
}

void game::load_grid_randomly() throw (no_grid_to_load, unable_to_load_grid) {
	try {
		std::fstream grid_file(choose_file_randomly().c_str());
		int val;

		if (grid_file.is_open()) {
			for (unsigned int i = 0; i < NUM_CELLS_PER_LINE; ++i)
				for (unsigned int j = 0; j < NUM_CELLS_PER_LINE; ++j) {
					if (grid_file >> val)
						g.cell_at(i, j) = val;
				}

			grid_file.close();
		} else {
			grid_file.close();
			throw unable_to_load_grid();
		}
	} catch (no_grids_found &e) {
		throw no_grid_to_load();
	}
}

void game::load_grid_file_names(std::string const &conf_file_name) {
	std::fstream conf_file(conf_file_name.c_str());
	std::string grid_name;

	if (conf_file.is_open())
		while (conf_file >> grid_name)
			grid_file_names.push_back(grid_name);

	conf_file.close();
}

std::string const& game::choose_file_randomly() const throw (no_grids_found) {
	try {
		return grid_file_names[generate_bounded_random_integer(0,
				grid_file_names.size() - 1)];
	} catch (bad_interval &e) {
		throw no_grids_found();
	}
}

void game::run() {
	unsigned int line, column;
	int val;

	while (!c.is_grid_fully_filled()) {
		clear_terminal();
		std::cout << c.current_grid;
		std::cout << "line column value ?" << std::endl;
		std::cin >> line >> column >> val;

		try {
			c.fill_grid_under_constraint(line, column, val);
		} catch (std::exception const &e) {
			std::cout << e.what() << std::endl;
		}
	}
}

game::~game() {
	// TODO Auto-generated destructor stub
}


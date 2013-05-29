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

game::game()
{
	try {
		load_grid(SAVED_GAME_FILE_NAME);
	} catch (unable_to_load_grid const &e) {
		throw unable_to_launch_game(e.what());
	}
	c.set_current_grid(g);
}

game::game(difficulty d) throw (unable_to_launch_game) :
		c(d)
{
	load_grid_file_names(GRID_NAMES_FILE_NAME);
	try {
		load_grid_randomly();
	} catch (std::exception &e) {
		throw unable_to_launch_game(e.what());
	}
	c.set_current_grid(g);
}

void game::save() const
{
	std::fstream saved_game_file(SAVED_GAME_FILE_NAME,
			std::fstream::in | std::fstream::out | std::fstream::trunc);
	grid const& gr = c.get_current_grid();

	for (unsigned int i = 0; i < NUM_CELLS_PER_LINE; ++i)
		for (unsigned int j = 0; j < NUM_CELLS_PER_LINE; ++j)
			saved_game_file << gr.cell_at(i, j) << std::endl;

	saved_game_file.close();
}

void game::run()
{
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

void game::load_grid(std::string const &file_name)
{
	std::fstream grid_file(file_name.c_str());

	if (grid_file.is_open()) {
		fill_grid_with_file_data(grid_file);
		grid_file.close();
	} else {
		grid_file.close();
		throw unable_to_load_grid();
	}
}

void game::load_grid_randomly() throw (no_grid_to_load, unable_to_load_grid)
{
	load_grid(choose_file_randomly());
}

void game::load_grid_file_names(std::string const &conf_file_name)
{
	std::fstream conf_file(conf_file_name.c_str());
	std::string grid_name;

	if (conf_file.is_open())
		while (conf_file >> grid_name)
			grid_file_names.push_back(grid_name);

	conf_file.close();
}

void game::fill_grid_with_file_data(std::fstream &file)
{
	int val;
	for (unsigned int i = 0; i < NUM_CELLS_PER_LINE; ++i)
		for (unsigned int j = 0; j < NUM_CELLS_PER_LINE; ++j) {
			if (file >> val)
				g.cell_at(i, j) = val;
		}
}

std::string const& game::choose_file_randomly() const throw (no_grids_found)
{
	try {
		return grid_file_names[generate_bounded_random_integer(0,
				grid_file_names.size() - 1)];
	} catch (bad_interval &e) {
		throw no_grids_found();
	}
}

/*
 * game.h
 *
 *  Created on: 26 mai 2013
 *      Author: telemaque
 */

#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <vector>
#include <fstream>
#include "grid.h"
#include "core.h"

#define SAVED_GAME_FILE_NAME "saved_game.txt"
#define GRID_NAMES_FILE_NAME "grid_names.txt"

struct no_grids_found: public enriched_exception
{
	no_grids_found()
	{
		set_msg("no grids found");
	}
};

struct no_grid_to_load: public enriched_exception
{
	no_grid_to_load()
	{
		set_msg("no grid to load");
	}
};

struct unable_to_launch_game: public enriched_exception
{
	unable_to_launch_game(std::string const &msg)
	{
		set_msg("enable to launch game cause : " + msg);
	}
};

struct unable_to_load_grid: public enriched_exception
{
	unable_to_load_grid()
	{
		set_msg("enable to load grid");
	}
};

class game
{
private:
	grid g;
	core c;
	std::vector<std::string> grid_file_names;

	void load_grid(std::string const &file_name);
	void load_grid_randomly() throw (no_grid_to_load, unable_to_load_grid);
	void load_grid_file_names(std::string const &conf_file_name);
	std::string const& choose_file_randomly() const throw (no_grids_found);
	void fill_grid_with_file_data(std::fstream &file);
public:
	game();
	game(difficulty d) throw (unable_to_launch_game);
	void save() const;
	void run();
};

#endif /* GAME_H_ */

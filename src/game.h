/*
 * game.h
 *
 *  Created on: 26 mai 2013
 *      Author: telemaque
 */

#ifndef GAME_H_
#define GAME_H_

#include <string>
#include "grid.h"
#include "core.h"

class game
{
private:
	grid g;
	core c;

public:
	game(difficulty d);
	void load_grid_from_file(std::string const &file_name);
	std::string const& choose_file_randomly_from_dir(std::vector<std::string> const &file_names);
	void run();
	virtual ~game();
};

#endif /* GAME_H_ */

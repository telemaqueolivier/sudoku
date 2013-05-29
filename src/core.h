/*
 * core.h
 *
 *  Created on: 26 mai 2013
 *      Author: telemaque
 */

#ifndef CORE_H_
#define CORE_H_

#include <map>
#include "grid.h"
#include <sstream>
#include "utils.h"

struct bad_cell_value: public enriched_exception {
	bad_cell_value(int val) {
		std::stringstream ss;
		ss << "bad cell value = " << val;
		set_msg(ss.str());
	}
};

struct bad_cell: public enriched_exception {
	bad_cell(unsigned int line, unsigned column) {
		std::stringstream ss;
		ss << "bad cell at (" << line << "," << column << ")";
		set_msg(ss.str());
	}
};

struct no_possible_cell_value: public enriched_exception {
	no_possible_cell_value(unsigned int line, unsigned column) {
		std::stringstream ss;
		ss << "no possible value for cell at (" << line << "," << column << ")";
		set_msg(ss.str());
	}
};

enum difficulty {
	EASY, NORMAL, DIFFICULT
};

class core {
public:
	grid *resolved_grid;
	grid current_grid;
	std::map<int, int> map_difficulty;
	void possible_values_for_cell(unsigned int line, unsigned int column,
			std::vector<int> &values);

public:
	core(grid *g);
	void mask_cells(difficulty d);
	void fill_grid_under_constraint(unsigned int line, unsigned int column,
			int val) throw (bad_cell, bad_cell_value, no_possible_cell_value);
	bool is_grid_fully_filled();
	virtual ~core();
};
#endif /* CORE_H_ */

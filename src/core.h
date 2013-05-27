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

enum difficulty
{
	EASY, NORMAL, DIFFICULT
};

class core
{
public:
	grid *resolved_grid;
	grid current_grid;
	std::map<int, int> map_difficulty;
	void possible_values_for_cell(unsigned int line, unsigned int column, std::vector<int> &values);

public:
	core(grid *g);
	void mask_cells(difficulty d);
	void fill_grid_under_constraint(unsigned int line, unsigned int column, int val);
	bool is_grid_fully_filled();
	virtual ~core();
};

struct bad_cell_value: public std::exception
{
	int val;
	bad_cell_value(int val) : val(val){}
	virtual const char* what() const throw ()
	{
		static std::string buf;
		std::stringstream ss;
		ss << "bad cell value = " << val;
		buf = ss.str();
		return buf.c_str();
	}
};

struct cell_exception : public std::exception
{
	unsigned int line;
	unsigned int column;
	cell_exception(unsigned int line, unsigned column) : line(line), column(column){}
};

struct bad_cell: public cell_exception
{
	bad_cell(unsigned int line, unsigned column) : cell_exception(line, column){}
	virtual const char* what() const throw ()
	{
		static std::string buf;
		std::stringstream ss;
		ss << "bad cell at (" << line << "," << column << ")";
		buf = ss.str();
		return buf.c_str();
	}
};

struct no_possible_cell_value: public cell_exception
{
	no_possible_cell_value(unsigned int line, unsigned column) : cell_exception(line, column){}
	virtual const char* what() const throw ()
	{
		static std::string buf;
		std::stringstream ss;
		ss << "no possible value for cell at (" << line << "," << column << ")";
		buf = ss.str();
		return buf.c_str();
	}
};

#endif /* CORE_H_ */

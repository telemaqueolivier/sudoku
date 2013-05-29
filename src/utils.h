/*
 * utils.h
 *
 *  Created on: 25 mai 2013
 *      Author: telemaque
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <exception>
#include <string>
#include <cstdio>
#include <sstream>
#include "grid.h"

struct increment
{
	int n;
	increment(int beginning) :
			n(beginning - 1)
	{
	}
	int operator()()
	{
		return ++n;
	}
};

class enriched_exception: public std::exception
{
	std::string msg;

protected:
	void set_msg(std::string const &m)
	{

		msg = m;
	}

	std::string const& get_msg() const
	{
		return msg;
	}

public:
	virtual const char* what() const throw ()
	{
		return msg.c_str();
	}

	virtual ~enriched_exception() throw ()
	{
	}
	;
};

struct bad_interval: public enriched_exception
{
	bad_interval(int bound_min, int bound_max)
	{
		std::stringstream ss;
		ss << "bad interval [" << bound_min << "," << bound_max << "]";
		set_msg(ss.str());
	}
};

unsigned int generate_bounded_random_integer(unsigned int a, unsigned int b)
		throw (bad_interval);
std::vector<int> all_missing_integers_in_interval(
		std::vector<int> curr_integers, int bound_min, int bound_max);
void clear_terminal();
std::ostream& operator<<(std::ostream &os, grid const &g);

#endif /* UTILS_H_ */

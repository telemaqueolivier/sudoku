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

unsigned int generate_bounded_random_integer(unsigned int a, unsigned int b);
std::vector<int> all_missing_integers_in_interval(std::vector<int> curr_integers, int bound_min, int bound_max);
void clear_terminal();

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

void print_vector(std::string const &s, std::vector<int> v);

#include "grid.h"
std::ostream& operator<<(std::ostream &os, grid &g);

class bad_interval: public std::exception
{
private:
	int min;
	int max;

public:
	bad_interval(int bound_min, int bound_max) :
			min(bound_min), max(bound_max)
	{
	}

	virtual const char* what() const throw ()
	{
		std::stringstream ss("bad interval [");
		ss << min << "," << max << "]";
		return ss.str().c_str();
	}
};

#endif /* UTILS_H_ */

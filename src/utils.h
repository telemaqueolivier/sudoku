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

unsigned int generate_bounded_random_integer(unsigned int a, unsigned int b);
std::vector<int> all_missing_integers_in_interval(std::vector<int> curr_integers, int bound_min, int bound_max);

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
		char buf[100];
		snprintf(buf, sizeof(buf), "bad interval [%d,%d]", min, max);
		return buf;
	}
};

#endif /* UTILS_H_ */

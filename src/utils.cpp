/*
 * utils.cpp
 *
 *  Created on: 25 mai 2013
 *      Author: telemaque
 */
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "utils.h"

unsigned int generate_bounded_random_integer(unsigned int a, unsigned int b)
{
	return rand() % (b - a + 1) + a;
}

struct increment
{
	int n;
	increment() :
			n(0)
	{
	}
	int operator()()
	{
		return ++n;
	}
};

std::vector<int> all_missing_integers_in_interval(std::vector<int> curr_integers, int bound_min, int bound_max)
{
	if (bound_min == bound_max) {
		throw bad_interval(bound_min, bound_max);
	} else {
		unsigned int curr_size = curr_integers.size();
		std::vector<int> missing_integers(bound_max - bound_min + 1 - curr_size);

		std::generate(missing_integers.begin(), missing_integers.end(), increment());
		for (unsigned int i = 0; i < curr_size; ++i) {
			missing_integers.erase(std::remove(missing_integers.begin(), missing_integers.end(), curr_integers[i]));
		}

		return missing_integers;
	}
}


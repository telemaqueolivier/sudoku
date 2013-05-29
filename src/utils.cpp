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

unsigned int generate_bounded_random_integer(unsigned int a, unsigned int b) throw (bad_interval)
{
	if (a == b)
		return a;
	else if (a < b)
		return rand() % (b - a + 1) + a;
	else
		throw bad_interval(a, b);
}

#include <iostream>
#include <iterator>
#include <string>
void print_vector(std::string const &s, std::vector<int> v)
{
	std::cout << s << std::endl;
	copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, "\n"));
}

std::ostream& operator<<(std::ostream &os, grid &g)
{
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (g.cell_at(i, j) == 0)
				std::cout << " |";
			else
				std::cout << g.cell_at(i, j) << "|";
		}

		std::cout << std::endl;
		for (int k = 0; k < 18; ++k) {
			std::cout << "-";
		}
		std::cout << std::endl;
	}

	return os;
}

std::vector<int> all_missing_integers_in_interval(std::vector<int> curr_integers, int bound_min, int bound_max)
{
	if (bound_min == bound_max)
		throw bad_interval(bound_min, bound_max);
	else {
		unsigned int curr_size = curr_integers.size();
		std::vector<int> missing_integers(bound_max - bound_min + 1);

		std::generate(missing_integers.begin(), missing_integers.end(), increment(1));
		for (unsigned int i = 0; i < curr_size; ++i)
			missing_integers.erase(std::remove(missing_integers.begin(), missing_integers.end(), curr_integers[i]), missing_integers.end());

		return missing_integers;
	}
}


void clear_terminal()
{
#ifdef __unix__
//	system("clear");
#elif _WIN32
	system("cls");
#endif
}


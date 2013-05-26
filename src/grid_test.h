/*
 * grid_test.cpp
 *
 *  Created on: 25 mai 2013
 *      Author: telemaque
 */
#include "grid.h"

namespace ns_test
{
	class test
	{
	public:
		virtual void setup() = 0;
		virtual void free() = 0;
		virtual ~test(){}
	};

	class grid_test : public test
	{
	private:
		grid g;

	public:
		void setup()
		{

		}

		void method_cell_at()
		{

		}
		void free()
		{

		}
	}
}

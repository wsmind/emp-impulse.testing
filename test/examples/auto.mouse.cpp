/*******************************************************************************
 *                                                                             *
 * This file is part of the EMP Impulse project                                *
 *                                                                             *
 * Copyright (C) 2010 ElectroMagnetic Potatoes (EMP)                           *
 * See the AUTHORS file for more information.                                  *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.       *
 *                                                                             *
 ******************************************************************************/

/**
 * \file
 * 
 * This file demonstrates the use of the PEEL library for the writing of
 * automated unit tests. Being automated means that we will be able to
 * execute them at every push on the central repository, reporting errors
 * as early as possible in the production process.
 * 
 * To be recognized as such, every automated test must be prefixed by "auto.".
 * Using that notation, the build server will run it and filter the output
 * for strings "[OK]" and "[FAILED]", counting and reporting them in the end.
 * Printing things not containing one of these strings is therefore not a
 * problem, and will show up verbatim in the log.
 * 
 * To see the results of the last pushes, go to http://build.emp.fr.nf
 * 
 * If you need something more flexible than simple boolean assertions to test
 * your code, you can write non-automated tests, where the use of PEEL is
 * not mandatory. See cheese.cpp for an example of this.
 */

#include <peel.hpp> // test library

#include <cmath> // for example calculations

/**
 * \class Mouse
 * \brief Fake class (would be included in a real test, not written here)
 */
class Mouse
{
	public:
		Mouse()
		{
			this->age = 42;
		}
		
		void becomeOlder(int years)
		{
			this->age += years;
		}
		
		void drinkMagicLiquid()
		{
			this->age = 12;
		}
		
		int getAge() const
		{
			return this->age;
		}
		
		float getSize()
		{
			// yup, the size of a mouse is the square root of its age
			return sqrt((float)this->age);
		}
		
	private:
		int age;
};

int main()
{
	Mouse mouse;
	
	// initial age
	CHECK(mouse.getAge() == 42);
	
	// drink liquid
	mouse.drinkMagicLiquid();
	CHECK(mouse.getAge() == 12);
	
	// become old again
	mouse.becomeOlder(100);
	CHECK(mouse.getAge() == 112);
	
	// measure mouse size
	CHECK(FLOAT_EQUAL(mouse.getSize(), sqrt(112.0f)));
	
	return 0;
}

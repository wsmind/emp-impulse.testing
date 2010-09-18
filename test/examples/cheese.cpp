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
 * This is a simple, non-automated test example. For non-automated tests, the
 * use of PEEL is not mandatory. Nevertheless, feel free to use it if you need
 * boolean assertions or if you plan to transform your test may evolve to
 * an automated one.
 * 
 * Non-automated tests allow you to try some features that could not be
 * easily fit into a boolean expression, such as texture drawing or sound
 * playback.
 */

#include <iostream>

/**
 * \class Cheese
 * \brief Fake class (would be included in a real test, not written here)
 */
class Cheese
{
	public:
		Cheese()
		{
			std::cout << "A new cheese was created" << std::endl;
		}
		
		/**
		 * \brief This method cannot be checked easily with a boolean expression
		 */
		void displayHoles()
		{
			std::cout << " ______ " << std::endl;
			std::cout << "/  o   \\" << std::endl;
			std::cout << "\\   o   |" << std::endl;
			std::cout << " | o   /" << std::endl;
			std::cout << "/   oo |" << std::endl;
			std::cout << "\\_o____|" << std::endl;
		}
};

int main()
{
	Cheese cheese;
	
	std::cout << "Please inspect the cheese holes..." << std::endl;
	cheese.displayHoles();
	
	return 0;
}

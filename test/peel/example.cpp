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
 * \file PEEL example unit test
 *
 * This file is used as a test for the PEEL library, as well as an example
 * of how to use it. By reading through it, you should be able to figure
 * out how to write unit tests for the Impulse project.
 */
#include <peel.hpp>

int main()
{
	// simple pass case
	CHECK((int)false == 0);
	
	// simple error case
	CHECK(42 == 43);
	
	// special check for float equality
	CHECK(FLOAT_EQUAL(2.0f, 2.000001f));
	
	// other float test
	CHECK(FLOAT_EQUAL(2.0f, 42.0f));
	
	return 0;
}


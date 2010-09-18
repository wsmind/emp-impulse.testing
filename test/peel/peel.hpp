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

#ifndef __PEEL_HPP__
#define __PEEL_HPP__

#include <iostream>
#include <cmath>

#define CHECK(expression) \
	{ \
		if (expression) \
			std::cout << "[OK] " << #expression << std::endl; \
		else \
			std::cerr << "[FAILED] " << #expression << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl; \
	}

#define FLOAT_EPSILON 0.001f

#define FLOAT_EQUAL(f1, f2) \
	(fabs(f1 - f2) < FLOAT_EPSILON)

#endif // __PEEL_HPP__


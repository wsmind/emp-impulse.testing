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
 * \brief Problem Elusive Examination Library
 * 
 * This header is a lightweight, stand-alone test library. It is used throughout
 * EMP projects, to implement automated unit tests.
 */

#ifndef __PEEL_HPP__
#define __PEEL_HPP__

#include <iostream>
#include <cmath>

/**
 * \def CHECK(expression)
 * \brief Assert the given \a expression and print the result to stdout or stderr
 * 
 * The behavior of this macro depends upon the result of the evaluation of the
 * given expression. If it evaluates to true, the string "[OK]" followed by
 * the expression is output on stdout. On the other hand, when the result is
 * false, an error is output on stderr with the format
 * "[FAILED] expression (file:line)".
 */
#define CHECK(expression) \
	{ \
		if (expression) \
			std::cout << "[OK] " << #expression << std::endl; \
		else \
			std::cerr << "[FAILED] " << #expression << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl; \
	}

//! Accepted float error for comparisons
#define FLOAT_EPSILON 0.001f

#define FLOAT_EQUAL(f1, f2) \
	(fabs(f1 - f2) < FLOAT_EPSILON)

#endif // __PEEL_HPP__


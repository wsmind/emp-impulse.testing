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
 * \brief Type definitions
 * \author Remi Papillie
 *
 * This file contains redefinitions of common types, to avoid relying on
 * platform-specific type size.
 */

#ifndef __TYPES_HPP__
#define __TYPES_HPP__

// TODO (low-priority): specialize this for specific platforms (or play with C99
//                      fixed-size types such as uint32_t, etc.)

// signed integer types
typedef signed char             i8;
typedef signed short int        i16;
typedef signed long int         i32;
typedef signed long long int    i64;

// unsigned integer types
typedef unsigned char           u8;
typedef unsigned short int      u16;
typedef unsigned long int       u32;
typedef unsigned long long int  u64;

// floating-point types
typedef float                   f32;
typedef double                  f64;
typedef long double             f80;

// forward declaration helpers

#define IMPULSE_FORWARD_DECLARE0(classname) \
	class classname;

#define IMPULSE_FORWARD_DECLARE1(ns1, classname) \
	namespace ns1 { class classname; }

#define IMPULSE_FORWARD_DECLARE2(ns1, ns2, classname) \
	namespace ns1 { namespace ns2 { class classname; } }

#define IMPULSE_FORWARD_DECLARE3(ns1, ns2, ns3, classname) \
	namespace ns1 { namespace ns2 { namespace ns3 { class classname; } } }

#endif // __TYPES_HPP__


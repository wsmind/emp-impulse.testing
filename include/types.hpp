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

#include <stdint.h>

// signed integer types
typedef int8_t      i8;
typedef int16_t     i16;
typedef int32_t     i32;
typedef int64_t     i64;
typedef intptr_t    iptr;

// unsigned integer types
typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;
typedef uintptr_t   uptr;

// floating-point types
typedef float       f32;
typedef double      f64;
typedef long double f80;

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


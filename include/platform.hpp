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
 * \brief Platform detection (system and compiler)
 * \author Remi Papillie
 */

#ifndef __PLATFORM_HPP__
#define __PLATFORM_HPP__

// operating system
#if defined(_WIN32)
#	define IMPULSE_OS_WIN32
#elif defined(__APPLE__)
#	define IMPULSE_OS_MAC
#else
#	define IMPULSE_OS_LINUX
#endif

// compiler
#if defined (__GNUC__)
#	define IMPULSE_COMPILER_GCC
#elif defined (_MSC_VER)
#	define IMPULSE_COMPILER_MSVC
#endif

// dll exports
#ifdef IMPULSE_COMPILER_MSVC
#	define IMPULSE_API_IMPORT __declspec(dllimport)
#	define IMPULSE_API_EXPORT __declspec(dllexport)
#else
#	define IMPULSE_API_IMPORT
#	define IMPULSE_API_EXPORT
#endif

#endif // __PLATFORM_HPP__

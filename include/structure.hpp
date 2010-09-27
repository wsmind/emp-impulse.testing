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
 * \brief DllExport/Import defines, for each library
 * \author Remi Papillie
 * 
 * This file is called 'structure' because its content includes a listing
 * of every physical artifact of the project. It might be extended with other
 * structural information in the future.
 */

#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

#include "platform.hpp"

#ifdef BUILDING_IMPULSE_MATH
#	define IMPULSE_MATH_EXPORT IMPULSE_API_EXPORT
#else
#	define IMPULSE_MATH_EXPORT IMPULSE_API_IMPORT
#endif

#ifdef BUILDING_IMPULSE_ENGINE
#	define IMPULSE_ENGINE_EXPORT IMPULSE_API_EXPORT
#else
#	define IMPULSE_ENGINE_EXPORT IMPULSE_API_IMPORT
#endif

#ifdef BUILDING_IMPULSE_SCENE
#	define IMPULSE_SCENE_EXPORT IMPULSE_API_EXPORT
#else
#	define IMPULSE_SCENE_EXPORT IMPULSE_API_IMPORT
#endif

#ifdef BUILDING_IMPULSE_GAME
#	define IMPULSE_GAME_EXPORT IMPULSE_API_EXPORT
#else
#	define IMPULSE_GAME_EXPORT IMPULSE_API_IMPORT
#endif

#endif // __STRUCTURE_HPP__


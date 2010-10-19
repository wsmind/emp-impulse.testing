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

#ifndef __DATAFILE_HPP__
#define __DATAFILE_HPP__

#include <common.hpp>
#include <string>
#include <iostream>
#include <fstream>

namespace engine {

/**
 * \class DataFile
 * \author Jonathan Giroux
 * 
 * \brief The DataFile class reads data from a file.
 * 
 * This class reads endianness-independant, type-friendly data from a file. 
 */
class IMPULSE_ENGINE_EXPORT DataFile
{
	public:
		
		bool load(const std::string & filename);

		i8 readI8();
		
		u8 readU8();
		
		u32 readU32();
		
		f32 readF32();
		
		std::string readString();
		
	private:
		
		std::ifstream file;
};

} // engine namespace
#endif // __DATAFILE_HPP__

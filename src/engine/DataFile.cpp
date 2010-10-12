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

#include <engine/DataFile.hpp>

namespace engine {

bool DataFile::load(const std::string & filename)
{
	this->file.open(filename.c_str(), std::ios_base::in | std::ios::binary);
	return this->file.good();
}

i8 DataFile::readI8()
{
	char c;
	this->file.get(c);
	return (i8)c;
}

u8 DataFile::readU8()
{
	return (u8)this->readI8();
}

u32 DataFile::readU32()
{
	u32 val = 0;
	val |= (u32)((u32)this->readU8() << 24);
	val |= (u32)((u32)this->readU8() << 16);
	val |= (u32)((u32)this->readU8() << 8);
	val |= (u32)((u32)this->readU8() << 0);
	return val;
}

f32 DataFile::readF32()
{
	u32 val = this->readU32();
	return *(f32 *)(void *)&val;
}


std::string DataFile::readString()
{
	std::string str;
	u32 len = this->readU32();
	str.reserve(len);
	for (u32 i = 0; i < len; ++i)
	{
		str.append(1, this->readU8());
	}
	return str;
}

} // engine namespace

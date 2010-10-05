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

#include <math/Random.hpp>

#include <ctime>
#include <cmath>

namespace math {

Random::Random()
{
	this->regenerateSeed();
}

Random::Random(u32 seed) : seed(seed)
{
}

void Random::regenerateSeed()
{
	this->seed = (u32)time(0);
}

void Random::setSeed(u32 seed)
{
	this->seed = seed;
}

void Random::next()
{
	/*
	 * All the magic is here!
	 * It is the generator found in older versions of glibc.
	 */
	this->seed = 69069 * this->seed + 1;
}

bool Random::nextBool()
{
	this->next();
	return (this->seed & 1);
}

f32 Random::nextF32(f32 min, f32 max)
{
	this->next();
	return min + (this->seed & 0x7FFFFF) * ((max - min) / 0x800000U);
}

i32 Random::nextI32(i32 min, i32 max)
{
	return (i32)floor(this->nextF32((f32)min, (f32)max));
}

u32 Random::nextU32()
{
	this->next();
	return this->seed;
}

} // math namespace


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

#include <peel.hpp>
#include <math/Random.hpp>

using namespace math;

int main()
{
	Random random;
	int classes[10] = {};
	
	for (int i = 0; i < 10000; ++i)
	{
		++classes[(int)floor(random.nextF32() * 10)];
	}
	
	f32 max = 0;
	for (int i = 0; i < 10; ++i)
	{
		std::cout << i << "\t" << classes[i] << std::endl;
		f32 delta = fabs((f32)(classes[i] - 1000));
		if (delta > max)
		{
			max = delta;
		}
	}
	
	CHECK(max < 100);
	
	return 0;
}


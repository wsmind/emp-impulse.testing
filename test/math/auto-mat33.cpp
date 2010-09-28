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
#include <math/Mat33.hpp>
#include <math/Vec3.hpp>

using namespace math;

int main()
{
	Mat33 translate;
	translate.v[2] = 2.0f;
	translate.v[5] = 4.0f;
	
	Mat33 scale;
	scale.v[0] = 2.0f;
	scale.v[4] = 0.5f;
	
	Vec3 v(42.0f, 12.0f, 1.0f);
	Vec3 v2 = translate * scale * v;
	
	CHECK(FLOAT_EQUAL(v2.x, 86.0f));
	CHECK(FLOAT_EQUAL(v2.y, 10.0f));
	
	return 0;
}


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
#include <math/Vec2.hpp>

using namespace math;

int main()
{
	Vec2 v1(1.0f, 5.4f);
	Vec2 v2(-2.2f, 4.2f);
	
	Vec2 add = v1 + v2;
	Vec2 sub = v1 - v2;
	Vec2 mul = v1 * v2;
	Vec2 mul2 = v1 * 42.0f;
	f32 dot = v1.dot(v2);
	f32 area = v1.area(v2);
	f32 norm = v1.norm();
	f32 norm2 = v1.norm2();
	
	CHECK(FLOAT_EQUAL(add.x, -1.2f));
	CHECK(FLOAT_EQUAL(add.y, 9.6f));
	CHECK(FLOAT_EQUAL(sub.x, 3.2f));
	CHECK(FLOAT_EQUAL(sub.y, 1.2f));
	CHECK(FLOAT_EQUAL(mul.x, -2.2f));
	CHECK(FLOAT_EQUAL(mul.y, 22.68f));
	CHECK(FLOAT_EQUAL(mul2.x, 42.0f));
	CHECK(FLOAT_EQUAL(mul2.y, 226.8f));
	CHECK(FLOAT_EQUAL(dot, 20.48f));
	CHECK(FLOAT_EQUAL(area, 16.08f));
	CHECK(FLOAT_EQUAL(norm, 5.491812087f));
	CHECK(FLOAT_EQUAL(norm2, 30.16f));
	CHECK(FLOAT_EQUAL(v2.normalize().norm(), 1.0f));
	
	return 0;
}


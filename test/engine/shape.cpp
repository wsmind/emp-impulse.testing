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

#include <engine/CollisionShape.hpp>
#include <iostream>
#include <peel.hpp>

using namespace engine;

int main()
{
	std::vector<math::Vec2> points;
	points.push_back(math::Vec2(1.0f, 1.0f));
	points.push_back(math::Vec2(-3.0f, 4.2f));
	points.push_back(math::Vec2(-4.0, -10.0f));
	CollisionShape shape(points);
	
	math::Vec2 outsider = math::Vec2(12.0f, 12.0f);
	math::Vec2 insider = math::Vec2(0.5f, 0.5f);
	math::Vec2 borderer = math::Vec2(1.0f, 1.0f);
	
	CHECK(shape.isInside(outsider, NULL, NULL, NULL) == false);
	CHECK(shape.isInside(insider, NULL, NULL, NULL) == true);
	CHECK(shape.isInside(borderer, NULL, NULL, NULL) == true);
	
	std::cout << "Plop" << std::endl;
	return 0;
}


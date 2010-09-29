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
	std::cout << "Plop" << std::endl;
	
	/*std::vector<math::Vec2> points1;
	points1.push_back(math::Vec2(1.0f, 1.0f));
	points1.push_back(math::Vec2(-3.0f, 4.0f));
	points1.push_back(math::Vec2(4.0, 10.0f));
	CollisionShape shape1(points1);
	
	math::Vec2 outsider = math::Vec2(12.0f, 12.0f);
	math::Vec2 insider = math::Vec2(0.5f, 0.5f);
	math::Vec2 borderer = math::Vec2(1.0f, 1.0f);
	
	CHECK(shape1.isInside(outsider, NULL, NULL) == false);
	CHECK(shape1.isInside(insider, NULL, NULL) == true);
	CHECK(shape1.isInside(borderer, NULL, NULL) == true);
	
	std::vector<math::Vec2> points2;
	points2.push_back(math::Vec2(1.0f, -1.0f));
	points2.push_back(math::Vec2(3.0f, 1.0f));
	points2.push_back(math::Vec2(-1.0f, 1.0f));
	points2.push_back(math::Vec2(-1.0f, -1.0f));
	CollisionShape shape2(points2);
	
	math::Vec2 ins[] = {
		math::Vec2(0.0f, -0.5f),
		math::Vec2(1.5f, 0.0f),
		math::Vec2(-0.8f, 0.6f)
	};
	
	for (int i = 0; i < 3; i++)
	{
		math::Vec2 normal;
		float distance;
		bool result = shape2.isInside(ins[i], &normal, &distance);
		CHECK(result == true);
		std::cout << "point: " << ins[i] << std::endl;
		std::cout << "normal: " << normal << std::endl;
		std::cout << "distance: " << distance << std::endl;
	}*/
	
	std::vector<math::Vec2> points1;
	points1.push_back(math::Vec2(0.0f, 0.0f));
	points1.push_back(math::Vec2(0.0f, -1.0f));
	points1.push_back(math::Vec2(2.0f, -3.0f));
	points1.push_back(math::Vec2(3.0f, -3.0f));
	points1.push_back(math::Vec2(3.0f, 0.0f));
	CollisionShape shape1(points1);
	
	std::vector<math::Vec2> points2;
	points2.push_back(math::Vec2(4.0f, -3.0f));
	points2.push_back(math::Vec2(4.0f, 0.0f));
	points2.push_back(math::Vec2(2.5f, -1.5f));
	CollisionShape shape2(points2);
	
	std::vector<math::Vec2> points3;
	points3.push_back(math::Vec2(-1.0f, -0.5f));
	points3.push_back(math::Vec2(1.0f, -0.5f));
	points3.push_back(math::Vec2(1.5f, 1.0f));
	points3.push_back(math::Vec2(-1.0f, 1.0f));
	CollisionShape shape3(points3);
	
	std::vector<math::Vec2> points4;
	points4.push_back(math::Vec2(1.0f, -3.0f));
	points4.push_back(math::Vec2(1.5f, -1.5f));
	points4.push_back(math::Vec2(1.0f, -1.5f));
	CollisionShape shape4(points4);
	
	Contact contact;
	u32 intersectionCount = shape1.detectCollision(&shape4, &contact);
	if (intersectionCount > 0)
	{
		std::cout << "Intersection count: " << intersectionCount << std::endl;
		std::cout << "Contact point: " << contact.contactPoint << std::endl;
		std::cout << "Normal: " << contact.normal << std::endl;
		std::cout << "Interpenetration: " << contact.interpenetration << std::endl;
	}
	
	return 0;
}


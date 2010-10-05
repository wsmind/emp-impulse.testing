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
#include <SFML/Graphics.hpp>

using namespace engine;
using namespace math;

int main()
{
	// Create the main rendering window
	sf::RenderWindow rendy(sf::VideoMode(1024, 768, 32), "Plop window");
	
	std::vector<Vec2> points1;
	points1.push_back(Vec2(0.0f, 0.0f));
	points1.push_back(Vec2(300.0f, 0.0f));
	points1.push_back(Vec2(300.0f, 400.0f));
	points1.push_back(Vec2(0.0f, 400.0f));
	CollisionShape cshape1(points1);
	sf::Shape shape1;
	for (unsigned int i = 0; i < points1.size(); i++)
		shape1.AddPoint(points1[i].x, points1[i].y, sf::Color(255, 0, 0), sf::Color(0, 0, 0));
	shape1.SetOutlineWidth(1.0f);
	
	cshape1.setScale(Vec2(0.2f, 0.3f));
	
	std::vector<Vec2> points2;
	points2.push_back(Vec2(-100.0f, 0.0f));
	points2.push_back(Vec2(100.0f, -100.0f));
	points2.push_back(Vec2(100.0f, 100.0f));
	CollisionShape cshape2(points2);
	sf::Shape shape2;
	for (unsigned int i = 0; i < points2.size(); i++)
		shape2.AddPoint(points2[i].x, points2[i].y, sf::Color(255, 255, 0), sf::Color(0, 0, 0));
	shape2.SetOutlineWidth(1.0f);
	
	cshape2.setPosition(Vec2(500.0f, 400.0f));

	sf::Shape line;
	
	sf::Clock clock;
	sf::Clock clock2;
	while (rendy.IsOpened())
	{
		float elapsedTime = clock2.GetElapsedTime();
		clock2.Reset();
		
		// Process events
		sf::Event event;
		while (rendy.GetEvent(event))
		{
			// Close window : exit
			if (event.Type == sf::Event::Closed)
				rendy.Close();
		}
		
		cshape2.setRotation(clock.GetElapsedTime() * 20.0f);
		
		if (rendy.GetInput().IsKeyDown(sf::Key::Left))
			cshape1.setPosition(Vec2(cshape1.getPosition().x - 200.0f * elapsedTime, cshape1.getPosition().y));
		if (rendy.GetInput().IsKeyDown(sf::Key::Right))
			cshape1.setPosition(Vec2(cshape1.getPosition().x + 200.0f * elapsedTime, cshape1.getPosition().y));
		if (rendy.GetInput().IsKeyDown(sf::Key::Up))
			cshape1.setPosition(Vec2(cshape1.getPosition().x, cshape1.getPosition().y - 200.0f * elapsedTime));
		if (rendy.GetInput().IsKeyDown(sf::Key::Down))
			cshape1.setPosition(Vec2(cshape1.getPosition().x, cshape1.getPosition().y + 200.0f * elapsedTime));
		
		Contact contact;
		if (cshape2.detectCollision(&cshape1, &contact))
		{
			shape1.SetOutlineWidth(5.0f);
			shape2.SetOutlineWidth(5.0f);
			//line = sf::Shape::Line(contact.contactPoint.x, contact.contactPoint.y, contact.contactPoint.x + contact.normal.x * 100.0f, contact.contactPoint.y + contact.normal.y * 100.0f, 10.0f, sf::Color(255, 255, 255), 1.0f);
			cshape1.setPosition(cshape1.getPosition() + contact.normal * contact.interpenetration); 
		}
		else
		{
			shape1.SetOutlineWidth(1.0f);
			shape2.SetOutlineWidth(1.0f);
			line = sf::Shape::Line(0.0f, 0.0f, 0.0f, 0.0f, 10.0f, sf::Color(255, 255, 255), 1.0f); 
		}
		
		shape1.SetPosition(cshape1.getPosition().x, cshape1.getPosition().y);
		shape2.SetPosition(cshape2.getPosition().x, cshape2.getPosition().y);
		shape1.SetRotation(cshape1.getRotation());
		shape2.SetRotation(cshape2.getRotation());
		shape1.SetScale(cshape1.getScale().x, cshape1.getScale().y);
		shape2.SetScale(cshape2.getScale().x, cshape2.getScale().y);
		
		rendy.Clear(sf::Color(100, 100, 200));
		
		rendy.Draw(shape1);
		rendy.Draw(shape2);
		//rendy.Draw(line);

		rendy.Display();
	}
	
	return 0;
}


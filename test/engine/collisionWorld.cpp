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
	
	// Define a hero
	std::vector<Vec2> heroPoints;
	heroPoints.push_back(Vec2(0.0f, 0.0f));
	heroPoints.push_back(Vec2(100.0f, 0.0f));
	heroPoints.push_back(Vec2(100.0f, 200.0f));
	heroPoints.push_back(Vec2(0.0f, 200.0f));
	CollisionShape heroBox(heroPoints);
	sf::Shape hero;
	for (unsigned int i = 0; i < heroPoints.size(); i++)
		hero.AddPoint(heroPoints[i].x, heroPoints[i].y, sf::Color(255, 0, 0), sf::Color(0, 0, 0));
	hero.SetOutlineWidth(1.0f);
	
	heroBox.setScale(Vec2(0.5f, 0.5f));
	heroBox.setPosition(Vec2(0.0f, 500.0f));
	
	// Define the ground
	std::vector<Vec2> groundPoints;
	groundPoints.push_back(Vec2(0.0f, 600.0f));
	groundPoints.push_back(Vec2(900.0f, 600.0f));
	groundPoints.push_back(Vec2(900.0f, 768.0f));
	groundPoints.push_back(Vec2(0.0f, 768.0f));
	CollisionShape groundBox(groundPoints);
	sf::Shape ground;
	for (unsigned int i = 0; i < groundPoints.size(); i++)
		ground.AddPoint(groundPoints[i].x, groundPoints[i].y, sf::Color(0, 255, 0), sf::Color(0, 0, 0));
	ground.SetOutlineWidth(1.0f);
	
	// Add a rock
	std::vector<Vec2> rockPoints;
	rockPoints.push_back(Vec2(400.0f, 400.0f));
	rockPoints.push_back(Vec2(600.0f, 400.0f));
	rockPoints.push_back(Vec2(625.0f, 500.0f));
	rockPoints.push_back(Vec2(600.0f, 600.0f));
	rockPoints.push_back(Vec2(400.0f, 600.0f));
	rockPoints.push_back(Vec2(380.0f, 550.0f));
	rockPoints.push_back(Vec2(380.0f, 490.0f));
	CollisionShape rockBox(rockPoints);
	sf::Shape rock;
	for (unsigned int i = 0; i < rockPoints.size(); i++)
		rock.AddPoint(rockPoints[i].x, rockPoints[i].y, sf::Color(125, 125, 125), sf::Color(0, 0, 0));
	rock.SetOutlineWidth(1.0f);

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
		
		if (rendy.GetInput().IsKeyDown(sf::Key::Left))
			heroBox.setPosition(Vec2(heroBox.getPosition().x - 200.0f * elapsedTime, heroBox.getPosition().y));
		if (rendy.GetInput().IsKeyDown(sf::Key::Right))
			heroBox.setPosition(Vec2(heroBox.getPosition().x + 200.0f * elapsedTime, heroBox.getPosition().y));
		if (rendy.GetInput().IsKeyDown(sf::Key::Up))
			heroBox.setPosition(Vec2(heroBox.getPosition().x, heroBox.getPosition().y - 200.0f * elapsedTime));
		if (rendy.GetInput().IsKeyDown(sf::Key::Down))
			heroBox.setPosition(Vec2(heroBox.getPosition().x, heroBox.getPosition().y + 200.0f * elapsedTime));
		
		// Collision between the ground
		Contact contact;
		if (groundBox.detectCollision(&heroBox, &contact))
		{
			hero.SetOutlineWidth(5.0f);
			ground.SetOutlineWidth(5.0f);
			line = sf::Shape::Line(contact.contactPoint.x, contact.contactPoint.y, contact.contactPoint.x + contact.normal.x * 100.0f, contact.contactPoint.y + contact.normal.y * 100.0f, 10.0f, sf::Color(255, 255, 255), 1.0f);
			heroBox.setPosition(heroBox.getPosition() + contact.normal * contact.interpenetration); 
		}
		else
		{
			hero.SetOutlineWidth(1.0f);
			ground.SetOutlineWidth(1.0f);
			line = sf::Shape::Line(0.0f, 0.0f, 0.0f, 0.0f, 10.0f, sf::Color(255, 255, 255), 1.0f); 
		}
		
		// Collision between the hero and the rock
		if (rockBox.detectCollision(&heroBox, &contact))
		{
			hero.SetOutlineWidth(5.0f);
			rock.SetOutlineWidth(5.0f);
			line = sf::Shape::Line(contact.contactPoint.x, contact.contactPoint.y, contact.contactPoint.x + contact.normal.x * 100.0f, contact.contactPoint.y + contact.normal.y * 100.0f, 10.0f, sf::Color(255, 255, 255), 1.0f);
			heroBox.setPosition(heroBox.getPosition() + contact.normal * contact.interpenetration); 
		}
		else
		{
			hero.SetOutlineWidth(1.0f);
			rock.SetOutlineWidth(1.0f);
			line = sf::Shape::Line(0.0f, 0.0f, 0.0f, 0.0f, 10.0f, sf::Color(255, 255, 255), 1.0f); 
		}
		
		
		hero.SetPosition(heroBox.getPosition().x, heroBox.getPosition().y);
		ground.SetPosition(groundBox.getPosition().x, groundBox.getPosition().y);
		rock.SetPosition(rockBox.getPosition().x, rockBox.getPosition().y);
		hero.SetRotation(heroBox.getRotation());
		ground.SetRotation(groundBox.getRotation());
		rock.SetRotation(rockBox.getRotation());
		hero.SetScale(heroBox.getScale().x, heroBox.getScale().y);
		ground.SetScale(groundBox.getScale().x, groundBox.getScale().y);
		rock.SetScale(rockBox.getScale().x, rockBox.getScale().y);
		
		rendy.Clear(sf::Color(100, 100, 200));
		
		rendy.Draw(hero);
		rendy.Draw(ground);
		rendy.Draw(rock);
		rendy.Draw(line);

		rendy.Display();
	}
	
	return 0;
}


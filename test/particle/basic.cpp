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

#include <SFML/Graphics.hpp>
#include <engine/ParticleSystem.hpp>

#include <math/Vec2.hpp>

int main()
{
    // Create the main rendering window
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML Graphics");
	
	// Load the sprite image from a file
	sf::Image particleImage;
	if (!particleImage.LoadFromFile("particle.png"))
	{
		std::cout << "Error loading the particle." << std::endl;
	}
	
	//Set the sprite
	sf::Sprite sprite;
	sprite.SetImage(particleImage);
	
	//Create a sprite
	engine::ParticleSystem particleSystem;
	
	particleSystem.setCapacity(10);
	particleSystem.setParticleSprite(sprite);
	particleSystem.setPosition(100,100);
	particleSystem.setSpawnRate(1.f);
	particleSystem.setParticleLifeTime(10);
	particleSystem.setParticleInitSpeed(30,0);
	particleSystem.setParticleAcceleration(0,0);
	particleSystem.setParticleAlphaDecay(0,0,0,-20);
	particleSystem.setActive(true);
	
	math::Vec2 totalForces(0.f,9.8f);
	
	// Start game loop
	while (window.IsOpened())
	{
		float elapsedTime = window.GetFrameTime();
		
		particleSystem.update(elapsedTime,totalForces);
		
		// Process events
		sf::Event event;
		while (window.GetEvent(event))
		{
			// Close window : exit
			if (event.Type == sf::Event::Closed)
			{
				window.Close();
			}
		}
		
		// Clear the screen (fill it with white color)
		window.Clear(sf::Color(255, 255, 255));
		
		particleSystem.draw(window);
		
		// Display window contents on screen
		window.Display();
	}
	
	return EXIT_SUCCESS;
}

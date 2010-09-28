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
#include <engine/Particle.hpp>

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
	engine::Particle p(100,100);
	
	// Start game loop
	while (window.IsOpened())
	{
		float elapsedTime = window.GetFrameTime();
		
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
		
		p.draw(window, sprite);
		
		// Display window contents on screen
		window.Display();
	}
	
	return EXIT_SUCCESS;
}

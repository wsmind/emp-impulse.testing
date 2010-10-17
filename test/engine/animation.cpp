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

#include <common.hpp>
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <engine/AnimationData.hpp>
#include <engine/AnimationState.hpp>

int main()
{
	sf::Image image;

	if (!image.LoadFromFile("../test-data/bounce.png"))
	{
		std::cerr << "Unable to load animation image." << std::endl;
		return EXIT_FAILURE;
	}

	sf::Sprite sprite(image);

	engine::AnimationData data;

	if (!data.load("../test-data/bounce.anim"))
	{
		std::cerr << "Unable to load animation data." << std::endl;
		return EXIT_FAILURE;
	}

	engine::AnimationState state(&data);

	state.setCurrentSequence("bounce");

	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Animation system");
	window.SetFramerateLimit(60);

	f32 x = 800 / 2;
	f32 y = 600 / 2;
	f32 scale = 0.2f;
	
	sprite.SetScale(scale, scale);
	
	while (window.IsOpened())
	{
		float elapsedTime = window.GetFrameTime();

		state.update(elapsedTime);

		std::string e;
		while (state.hasEvent(&e))
		{
			std::cout << "Event '" << e << "' occured." << std::endl;
		}

		// Process events
		sf::Event event;
		while (window.GetEvent(event))
		{
			// Close window : exit
			if (event.Type == sf::Event::Closed)
			{
				window.Close();
			}
			
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Left && state.getCurrentSequence() != "walk_left")
			{
				state.setCurrentSequence("walk_left");
			}
			
			if (event.Type == sf::Event::KeyReleased && event.Key.Code == sf::Key::Left)
			{
				state.setCurrentSequence("bounce");
			}
		}

		// Clear the screen (fill it with black color)
		window.Clear(sf::Color(255, 255, 255));

		const engine::AnimationRect *rect = state.getRect();
		if (rect)
		{
			sprite.SetSubRect(sf::IntRect(rect->left, rect->top, rect->right, rect->bottom));
			sprite.SetPosition(x - rect->xOffset * scale, y - rect->yOffset * scale);
	
			window.Draw(sprite);
		}
		
		// Display window contents on screen
		window.Display();
	}

	return EXIT_SUCCESS;
}

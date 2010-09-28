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

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <engine/AnimationData.hpp>
#include <engine/AnimationState.hpp>

int main()
{
	sf::Image image;

	if (!image.LoadFromFile("resources/bounce.png"))
	{
		std::cerr << "Unable to load animation image." << std::endl;
		return EXIT_FAILURE;
	}

	sf::Sprite sprite(image);

	engine::AnimationData data;

	if (!data.load("resources/bounce.data"))
	{
		std::cerr << "Unable to load animation data." << std::endl;
		return EXIT_FAILURE;
	}

	engine::AnimationState state(&data);

	state.setSequence("bounce");

	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Animation system");
	window.SetFramerateLimit(60);

	int x = 800 / 2;
	int y = 600 / 2;

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
		}

		// Clear the screen (fill it with black color)
		window.Clear(sf::Color(255, 255, 255));

		sprite.SetSubRect(state.getRect()->rect);
		sprite.SetPosition(x - state.getRect()->offset.x, y - state.getRect()->offset.y);

		window.Draw(sprite);

		// Display window contents on screen
		window.Display();

	}

	data.unload();

	return EXIT_SUCCESS;
}

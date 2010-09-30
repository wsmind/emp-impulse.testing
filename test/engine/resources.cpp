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

#include <engine/ResourceManager.hpp>
#include <peel.hpp>

using namespace engine;

int main()
{
	ResourceManager *rm = new ResourceManager;
	
	sf::Image *image = rm->loadImage("water.png");
	sf::Image *image2 = rm->loadImage("water.png");
	CHECK(image == image2);
	
	sf::Image *image3 = rm->loadImage("wave.png");
	CHECK(image != image3);
	
	rm->releaseImage(image);
	rm->releaseImage(image2);
	rm->releaseImage(image3);
	
	delete rm;
	
	return 0;
}


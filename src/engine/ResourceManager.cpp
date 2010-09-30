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
#include <iostream>
#include <SFML/Graphics.hpp>

namespace engine {

sf::Image *ResourceManager::loadImage(std::string filename)
{
	// try to find an existing objet
	sf::Image *image = this->images.addReference(filename);
	
	// load if necessary
	if (!image)
	{
		// create new object
		image = new sf::Image;
		
		// try to load it
		if (!image->LoadFromFile(filename))
		{
			std::cerr << "Loading of resource '" << filename << "' failed!" << std::endl;
			delete image;
			return NULL;
		}
		
		// store it in the reference counter
		this->images.createResource(filename, image);
	}
	
	return image;
}

void ResourceManager::releaseImage(sf::Image *image)
{
	std::string name = this->images.findResourceName(image);
	if (name == "")
	{
		std::cerr << "Trying to unload an image not managed by the resource manager" << std::endl;
	}
	
	if (this->images.removeReference(name))
	{
		// actual object destruction
		this->images.destroyResource(name);
		delete image;
	}
}

} // engine namespace

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

sf::Image *ResourceManager::loadImage(std::string name)
{
	// record the new reference
	this->images.addReference(name);
	
	// load if necessary
	if (this->images.getReferenceCount(name) == 1)
	{
		// try to load
		sf::Image *image = new sf::Image;
		if (!image->LoadFromFile(name))
		{
			std::cerr << "Loading of image '" << name << "' failed!" << std::endl;
			delete image;
			image = NULL;
		}
		
		// storage
		this->images.storeResourceObject(name, image);
	}
	
	return this->images.retrieveResourceObject(name);;
}

void ResourceManager::releaseImage(std::string name)
{
	// destroy is necessary
	if (this->images.getReferenceCount(name) == 1)
	{
		sf::Image *image = this->images.retrieveResourceObject(name);
		delete image;
	}
	
	// reference removal
	this->images.removeReference(name);
}

void ResourceManager::printLoadedResources()
{
	std::cout << "== Images ==" << std::endl;
	this->images.printReferencedNames();
	std::cout << std::endl;
}

} // engine namespace

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
#include <engine/AnimationData.hpp>

namespace engine {

ResourceManager *ResourceManager::resourceManager = NULL;

void ResourceManager::createInstance()
{
	// if the instance does not exist, create it
	if ( resourceManager == NULL )
	{
		resourceManager = new ResourceManager;
	}
}

void ResourceManager::destroyInstance()
{
		delete resourceManager;
		resourceManager = NULL;
}

ResourceManager *ResourceManager::getInstance()
{
	return resourceManager;
}

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
	// print images
	std::cout << "== Images ==" << std::endl;
	this->images.printReferencedNames();
	std::cout << std::endl;
	
	// print animationDatas
	std::cout << "== AnimationDatas ==" << std::endl;
	this->animationDatas.printReferencedNames();
	std::cout << std::endl;
}

AnimationData *ResourceManager::loadAnimationData(std::string name)
{
	// record the new reference
	this->animationDatas.addReference(name);
	
	// load if necessary
	if (this->animationDatas.getReferenceCount(name) == 1)
	{
		// try to load
		AnimationData *animationData = new AnimationData;
		if (!animationData->load(name))
		{
			std::cerr << "Loading of animationData '" << name << "' failed!" << std::endl;
			delete animationData;
			animationData = NULL;
		}
		
		// storage
		this->animationDatas.storeResourceObject(name, animationData);
	}
	
	return this->animationDatas.retrieveResourceObject(name);;
}

void ResourceManager::releaseAnimationData(std::string name)
{
	// destroy is necessary
	if (this->animationDatas.getReferenceCount(name) == 1)
	{
		AnimationData *animationData = this->animationDatas.retrieveResourceObject(name);
		delete animationData;
	}
	
	// reference removal
	this->animationDatas.removeReference(name);
	
}



} // engine namespace

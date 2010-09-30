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

#ifndef __RESOURCEMANAGER_HPP__
#define __RESOURCEMANAGER_HPP__

#include <common.hpp>

#include <string>

#include <engine/ReferenceCounter.hpp>

IMPULSE_FORWARD_DECLARE1(sf, Image)

namespace engine {

/**
 * \class ResourceManager
 * \author Remi Papillie
 */
class IMPULSE_ENGINE_EXPORT ResourceManager
{
	public:
		// TODO: other resources types (duplicate these two methods, and add
		// other reference counters)
		sf::Image *loadImage(std::string filename);
		void releaseImage(sf::Image *image);
	
	private:
		ReferenceCounter<sf::Image> images;
};

} // engine namespace

#endif // __RESOURCEMANAGER_HPP__

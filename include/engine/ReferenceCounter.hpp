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

#ifndef __REFERENCECOUNTER_HPP__
#define __REFERENCECOUNTER_HPP__

#include <common.hpp>
#include <string>
#include <map>

namespace engine {

/**
 * \class ResourceManager
 * \author Remi Papillie
 */
template <class ResourceType>
class ReferenceCounter
{
	public:
		void createResource(std::string name, ResourceType *resource);
		void destroyResource(std::string name);
		std::string findResourceName(ResourceType *resource); // return "" if not found
		
		ResourceType *addReference(std::string name); // return NULL if not known
		bool removeReference(std::string name); // return true if must be destroyed (don't check resource existence)
		
	private:
		struct Descriptor
		{
			ResourceType *resource;
			int referenceCount;
		};
		
		typedef std::map<std::string, Descriptor> DescriptorMap;
		DescriptorMap descriptors;
};

} // engine namespace

#include <engine/ReferenceCounter.template.hpp>

#endif // __REFERENCECOUNTER_HPP__

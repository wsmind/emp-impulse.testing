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

#include <iostream>
#include <cstdio>

namespace engine {

template <class ResourceType>
void ReferenceCounter<ResourceType>::addReference(std::string name)
{
	typename DescriptorMap::iterator it = this->descriptors.find(name);
	if (it != this->descriptors.end())
	{
		// increase reference count for existing name
		++it->second.referenceCount;
	}
	else
	{
		// create a new descriptor (with counter initialized to 1)
		Descriptor desc;
		desc.resource = NULL;
		desc.referenceCount = 1;
		
		this->descriptors[name] = desc;
	}
}

template <class ResourceType>
void ReferenceCounter<ResourceType>::removeReference(std::string name)
{
	typename DescriptorMap::iterator it = this->descriptors.find(name);
	if (it != this->descriptors.end())
	{
		// decrease reference count for existing name
		--it->second.referenceCount;
		
		// destroy if necesarry
		if (it->second.referenceCount == 0)
			this->descriptors.erase(it);
	}
	else
	{
		// not referenced before
		std::cerr << "Trying to remove a reference to '" << name << "', which is not currently referenced" << std::endl;
	}
}

template <class ResourceType>
u32 ReferenceCounter<ResourceType>::getReferenceCount(std::string name)
{
	// if the name can be found, if is currently referenced
	typename DescriptorMap::iterator it = this->descriptors.find(name);
	if (it != this->descriptors.end())
		return it->second.referenceCount;
	
	// otherwise, it is not
	return 0;
}

template <class ResourceType>
void ReferenceCounter<ResourceType>::storeResourceObject(std::string name, ResourceType *resource)
{
	// ignore non-referenced names
	typename DescriptorMap::iterator it = this->descriptors.find(name);
	if (it != this->descriptors.end())
		it->second.resource = resource;
}

template <class ResourceType>
ResourceType *ReferenceCounter<ResourceType>::retrieveResourceObject(std::string name)
{
	// try to find a referenced name
	typename DescriptorMap::iterator it = this->descriptors.find(name);
	if (it != this->descriptors.end())
		return it->second.resource;
	
	return NULL;
}

template <class ResourceType>
void ReferenceCounter<ResourceType>::printReferencedNames()
{
	// referenced names are the only ones stored in the map
	typename DescriptorMap::iterator it;
	for (it = this->descriptors.begin(); it != this->descriptors.end(); ++it)
		printf("%3d %s\n", it->second.referenceCount, it->first.c_str());
}

} // engine namespace


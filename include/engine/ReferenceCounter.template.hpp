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

namespace engine {

template <class ResourceType>
void ReferenceCounter<ResourceType>::createResource(std::string name, ResourceType *resource)
{
	// create first reference
	Descriptor desc;
	desc.resource = resource;
	desc.referenceCount = 1;
	
	this->descriptors[name] = desc;
}

template <class ResourceType>
void ReferenceCounter<ResourceType>::destroyResource(std::string name)
{
	typename DescriptorMap::iterator i = this->descriptors.find(name);
	this->descriptors.erase(i);
}

template <class ResourceType>
std::string ReferenceCounter<ResourceType>::findResourceName(ResourceType *resource)
{
	typename DescriptorMap::iterator i = this->descriptors.begin();
	
	while (i != this->descriptors.end())
	{
		if (i->second.resource == resource)
			return i->first;
		
		i++;
	}
	
	return "";
}

template <class ResourceType>
ResourceType *ReferenceCounter<ResourceType>::addReference(std::string name)
{
	typename DescriptorMap::iterator i = this->descriptors.find(name);
	if (i == this->descriptors.end())
		return NULL;
	
	Descriptor &desc = i->second;
	desc.referenceCount++;
	
	return desc.resource;
}

template <class ResourceType>
bool ReferenceCounter<ResourceType>::removeReference(std::string name)
{
	typename DescriptorMap::iterator i = this->descriptors.find(name);
	
	Descriptor &desc = i->second;
	desc.referenceCount--;
	
	return (desc.referenceCount == 0);
}

} // engine namespace


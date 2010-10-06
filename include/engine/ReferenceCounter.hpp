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
 * \class ReferenceCounter
 * \author Remi Papillie
 *
 * Stores resource names along with a reference counter. A pointer to a resource
 * object can be provided for referenced names, too.
 */
template <class ResourceType>
class ReferenceCounter
{
	public:
		/**
		 * \brief Add a reference to the given resource name
		 */
		void addReference(std::string name);
		
		/**
		 * \brief Remove a reference to the given name
		 *
		 * Removing a reference to a name not referenced prints a warning on
		 * stderr, and does nothing.
		 */
		void removeReference(std::string name);
		
		/**
		 * \brief Read the reference counter of the given resource
		 *
		 * If a name to an unknown (i.e never referenced) resource is provided,
		 * the returned value will be 0. Each call to addReference() will
		 * increase this value, and removeReference() will decrement it.
		 */
		u32 getReferenceCount(std::string name);
		
		/**
		 * \brief Store an object pointer along with the reference counter
		 *
		 * Note that only resources with at least one reference can store
		 * an object pointer. If the reference counter goes down to zero,
		 * this pointer will be definitely lost.
		 *
		 * Nothing is done if the given name is not referenced.
		 */
		void storeResourceObject(std::string name, ResourceType *resource);
		
		/**
		 * \brief Query an object previously stored
		 * \return the stored object, or NULL if the name is not referenced
		 *
		 * \see storeResourceObject()
		 *
		 * If a name has just been referenced for the first time, its initial
		 * stored pointer is NULL.
		 */
		ResourceType *retrieveResourceObject(std::string name);
		
		/**
		 * \brief Print referenced names on stdout
		 */
		void printReferencedNames();
		
	private:
		struct Descriptor
		{
			ResourceType *resource;
			u32 referenceCount;
		};
		
		typedef std::map<std::string, Descriptor> DescriptorMap;
		DescriptorMap descriptors;
};

} // engine namespace

#include <engine/ReferenceCounter.template.hpp>

#endif // __REFERENCECOUNTER_HPP__

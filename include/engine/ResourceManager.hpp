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
IMPULSE_FORWARD_DECLARE1(engine, AnimationData)

namespace engine {

/**
 * \class ResourceManager
 * \author Remi Papillie
 * \author Maxime Viry
 *
 * Non generic implementation of resource management. For each managed object
 * types, you can use the loadXXX() and releaseXXX() methods (where XXX is the
 * type) to respectively ask for and release a resource.
 *
 * Note that for reference counting, the resource manager does not make
 * a special case for resources that failed to load. That means that if you
 * call one of the load() methods and NULL is returned, you still have to
 * make a corresponding release() or the name will remain referenced.
 *
 * The resourceManager is a singleton, to create it you have to call
 * createInstance() and to delete it you call destroyInstance().
 * To get it there is getInstance which return NULL if no instance exists
 */
class IMPULSE_ENGINE_EXPORT ResourceManager
{
	public:
	
		/**
		* \brief Request the creation of the ResourceManager
		*/
		static void createInstance(std::string basePath = ".");
		
		/**
		* \brief Request the deletion of the ResourceManager
		*/
		static void destroyInstance();
		
		/**
		* \return the existing resourceManager, or NULL if no instance
		* exist
		*/
		static ResourceManager *getInstance();
		
		/**
		 * \brief Ask for an image resource
		 * \return the loaded image object, or NULL if loading failed
		 */
		sf::Image *loadImage(std::string name);
		
		/**
		 * \brief Release a previously loaded image
		 */
		void releaseImage(std::string name);
		
		/**
		* \brief Ask for an animationData ressource
		* \return the loaded animationData object, or NULL if loading 
		* failed
		*/
		AnimationData *loadAnimationData(std::string name);
		
		/**
		* \brief Release a previously loaded image
		*/
		void releaseAnimationData(std::string name);	
		
		/**
		 * \brief Loaded resources summary (for checking purposes)
		 */
		void printLoadedResources();
		
	private:
		/// unique instance
		static ResourceManager *resourceManager;
		
		// managed resource types
		ReferenceCounter<sf::Image> images;
		ReferenceCounter<AnimationData> animationDatas;
		
		/// base resource path, with trailing slash
		std::string basePath;
		
		ResourceManager(std::string basePath);
		~ResourceManager();
};

} // engine namespace

#endif // __RESOURCEMANAGER_HPP__

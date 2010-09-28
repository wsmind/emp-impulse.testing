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

#ifndef __ANIMATIONDATA_HPP__
#define __ANIMATIONDATA_HPP__

#include <map>

#include <common.hpp>

namespace engine {

class AnimationSequence;

/**
 * \class AnimationData
 * \author Jonathan Giroux
 *
 * \brief The AnimationData class holds animation data.
 *
 * Animation data contain a list of AnimationSequence objects.
 *
 * The animation data file is created by the animation exporter tool.
 *
 * AnimationData object is initialized with load(), and on success, has to be
 * released with unload(). Do not use an uninitialized object to create
 * AnimationState objects.
 */
class AnimationData
{
public:

	/**
	 * \brief Type for the sequence map.
	 */
	typedef std::map<std::string, AnimationSequence *> SequenceMap;

	/**
	 * \brief Sequence map.
	 *
	 * The key is the sequence name.
	 */
	SequenceMap sequences;

	/**
	 * \brief Loads an animation data file.
	 * \param filename file name.
	 * \return true if loaded, false otherwise.
	 *
	 * The animation data file have to be created using the animation exporter
	 * tool. No validity check is made.
	 */
	bool load(const std::string & filename);

	/**
	 * \brief Unloads
	 */
	void unload();
};

}

#endif // __ANIMATIONDATA_HPP__

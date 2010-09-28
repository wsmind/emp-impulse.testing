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
 * \class
 * \author Jonathan Giroux
 *
 * \brief The AnimationData class holds animation data.
 */
class AnimationData
{
public:

	typedef std::map<std::string, AnimationSequence *> SequenceMap;
	SequenceMap sequences;

	bool load(const std::string & filename);

	void unload();
};

}

#endif // __ANIMATIONDATA_HPP__

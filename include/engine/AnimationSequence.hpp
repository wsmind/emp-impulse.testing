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

#ifndef __ANIMATIONSEQUENCE_HPP__
#define __ANIMATIONSEQUENCE_HPP__

#include <map>
#include <string>

#include <common.hpp>

namespace engine {

struct AnimationRect;

/**
 * \author Jonathan Giroux
 *
 * \brief The AnimationSequence class defines a sequence of rectangles and
 * events.
 */
struct AnimationSequence
{
public:

	typedef std::multimap<f32, std::string> EventMap;
	EventMap events;

	AnimationRect *rects;

	u32 rectCount;

	f32 frameDuration;

	f32 totalDuration;
};

}

#endif // __ANIMATIONSEQUENCE_HPP__

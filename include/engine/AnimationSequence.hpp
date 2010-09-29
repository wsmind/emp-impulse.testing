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

#include <common.hpp>
#include <map>
#include <string>

IMPULSE_FORWARD_DECLARE1(engine, AnimationRect)

namespace engine {

/**
 * \author Jonathan Giroux
 *
 * \brief The AnimationSequence class defines a sequence of rectangles and
 * events.
 *
 * A sequence is a timeline with frames, where each frame defines a rectangle.
 * Frames share the same duration.
 *
 * A sequence also defines a list of events, each of them associated with a
 * time. These times do not need to be a multiple of the frame duration. They
 * have to be in range [0, totalDuration] to be handled.
 */
struct AnimationSequence
{
	public:
		
		/**
		 * \brief Type for the event list.
		 */
		typedef std::multimap<f32, std::string> EventMap;

		/**
		 * \brief Event list.
		 */
		EventMap events;

		/**
		 * \brief Rectangle array.
		 */
		AnimationRect *rects;

		/**
		 * \brief Rectangle count.
		 *
		 * Size of rects.
		 */
		u32 rectCount;

		/**
		 * \brief Frame duration.
		 */
		f32 frameDuration;

		/**
		 * \brief Total duration.
		 *
		 * Equal to frameDuration * rectCount.
		 */
		f32 totalDuration;
};

} // engine namespace

#endif // __ANIMATIONSEQUENCE_HPP__

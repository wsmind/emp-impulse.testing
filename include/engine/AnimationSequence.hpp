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
#include <queue>
#include <string>

IMPULSE_FORWARD_DECLARE1(engine, AnimationRect)
IMPULSE_FORWARD_DECLARE1(engine, DataFile)

namespace engine {

/**
 * \class AnimationSequence
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
 * have to be in range [0, totalDuration] to be handled. For convenience, one
 * can declare events at time totalDuration: they occur at the same time that
 * events at time 0, except for the first play.
 */
class AnimationSequence
{
	public:

		/**
		 * \brief Constructs an animation sequence.
		 * 
		 */
		AnimationSequence(DataFile *file);

		/**
		 * \brief Destructs the animation sequence.
		 */
		~AnimationSequence();
		
		/**
		 * \brief Extracts informations from the sequence.
		 * \param startTime start of the time interval.
		 * \param duration length of the time interval.
		 * \param[out] rect rectangle at time \a startTime + \a duration.
		 * \param[out] events events which occur during time interval
		 * [\a startTime, \a startTime + \a duration[.
		 * \return \a startTime + \a duration, wrapped if necessary.
		 * 
		 * This function extracts informations from the sequence for the time
		 * interval [\a startTime, \a startTime + \a duration[. It gives back:
		 * \li the rectangle at time \a startTime + \a duration.
		 * \li the events which occur during time interval [\a startTime,
		 * \a startTime + \a duration[.
		 * 
		 * This function does not clear \a events.
		 * 
		 * This class only provides informations: no state is kept with this
		 * function.
		 */
		f32 extractInformations(f32 startTime, f32 duration, AnimationRect *rect, std::queue<std::string> *events) const;
		
	private:

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

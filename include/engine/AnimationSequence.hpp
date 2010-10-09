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
 * have to be in range [0, totalDuration] to be handled.
 */
class AnimationSequence
{
	public:

		/**
		 * \brief Constructs an animation sequence.
		 * 
		 */
		AnimationSequence(u32 rectCount, f32 frameDuration);

		/**
		 * \brief Destructs the animation sequence.
		 */
		~AnimationSequence();
		
		/**
		 * \brief Sets a rectangle.
		 * \param index rectangle index.
		 * \param rect rectangle.
		 */
		void setRect(u32 index, const AnimationRect *rect);

		/**
		 * \brief Gets a rectangle.
		 * \param index rectangle index.
		 * \returns rectangle.
		 */
		const AnimationRect *getRect(u32 index) const;
		
		/**
		 * \brief Adds an event to the sequence.
		 * \param time occurence time.
		 * \param event event.
		 */
		void addEvent(f32 time, const std::string & event);

		/**
		 * \brief Updates animation state.
		 * \param elapsedTime elapsed time since last call.
		 * \param[in,out] time playing time.
		 * \param[out] rectIndex rectangle index.
		 * \param events event queue.
		 */
		void update(f32 elapsedTime, f32 *time, u32 *rectIndex, std::queue<std::string> *events) const;
		
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

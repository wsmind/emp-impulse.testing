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

#ifndef __ANIMATIONSTATE_HPP__
#define __ANIMATIONSTATE_HPP__

#include <queue>
#include <string>

#include <common.hpp>
#include <engine/AnimationRect.hpp>

IMPULSE_FORWARD_DECLARE1(engine, AnimationData)

namespace engine {

/**
 * \class AnimationState
 * \author Jonathan Giroux
 *
 * \brief The AnimationState class defines an object running an animation.
 *
 * A state follows animations, which are defined in a AnimationData object.
 *
 * A typical use is:
 * \li call setSequence() to set the current sequence, e.g. when a particular
 * event occured.
 * \li call update() regularly.
 * \li after an update, call getRect() to obtain current rectangle and offset,
 * allowing for sprite modification.
 * \li after an update, call hasEvent() to retrieve the events which occured
 * during update.
 *
 * Example:
 * \code
 * state.setSequence("run");
 *
 * while (window.IsOpened())
 * {
 * 	float elapsedTime = window.GetFrameTime();
 *
 * 	state.update(elapsedTime);
 *
 * 	std::string event;
 * 	while (state.hasEvent(&event))
 * 	{
 * 		processEvent(event);
 * 	}
 *
 * 	sprite.SetSubRect(state.getRect()->rect);
 * 	sprite.SetPosition(x - state.getRect()->offset.x, y - state.getRect()->offset.y);
 *
 * 	...
 * }
 * \endcode
 */
class AnimationState
{
	public:
		
		/**
		 * \brief Constructs an AnimationState.
		 * \param data animation data object.
		 *
		 * The object has no playing sequence, so call setSequence() before calling
		 * update().
		 */
		AnimationState(AnimationData *data);

		/**
		 * \brief Sets current sequence.
		 * \param sequence new sequence.
		 */
		void setCurrentSequence(std::string sequence);

		/**
		 * \brief Gets current sequence.
		 * \return current sequence.
		 */
		std::string getCurrentSequence();

		/**
		 * \brief Updates the state.
		 * \param elapsedTime elapsed time since last call, in second.
		 *
		 * The update may change the given rectangle and may trigger events. So
		 * after the call, you should call getRect() and hasEvent(). See the above
		 * example.
		 *
		 * You may also give a modified elapsed time, to accelerate or decelerate
		 * animation speed.
		 */
		void update(f32 elapsedTime);

		/**
		 * \brief Gets the current rectangle and offset.
		 * \return current rectangle and offset.
		 *
		 * \see update
		 */
		const AnimationRect *getRect() const;

		/**
		 * \brief Iterates over triggered events.
		 * \param[out] event triggered event.
		 * \return true if there is still an event to handle, false otherwise.
		 *
		 * During updating, events may be triggered, so use this function to
		 * iterate over them. They are given in the order they have occurred. See
		 * the above example.
		 *
		 * \see update
		 */
		bool hasEvent(std::string *event);

	private:
		
		/**
		 * \brief Played animation data.
		 */
		AnimationData *data;
		
		/**
		 * \brief List of triggered events.
		 */
		std::queue<std::string> events;

		/**
		 * \brief Current sequence.
		 */
		const AnimationSequence *currentSequence;

		/**
		 * \brief Current sequence name.
		 */
		std::string currentSequenceName;
		
		/**
		 * \brief Current rectangle;
		 */
		u32 rectIndex;

		/**
		 * \brief Current animation time.
		 */
		f32 time;
};

} // engine namespace

#endif // __ANIMATIONSTATE_HPP__

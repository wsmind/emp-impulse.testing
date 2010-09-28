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

namespace engine {

class AnimationData;

/**
 * \class AnimationState
 * \author Jonathan Giroux
 *
 * \brief The AnimationState class defines an object running an animation.
 */
class AnimationState
{
public:

	AnimationState(AnimationData *data);

	void setSequence(std::string sequence);

	void update(f32 elapsedTime);

	const AnimationRect *getRect() const;

	bool hasEvent(std::string *event);

private:

	AnimationData *data;

	std::queue<std::string> events;

	std::string sequence;

	AnimationRect rect;

	f32 time;
};

}

#endif // __ANIMATIONSTATE_HPP__

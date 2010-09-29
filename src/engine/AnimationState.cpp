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

#include <engine/AnimationSequence.hpp>
#include <engine/AnimationData.hpp>
#include <engine/AnimationState.hpp>

namespace engine {

AnimationState::AnimationState(AnimationData *data) : data(data)
{
}

void AnimationState::setCurrentSequence(std::string sequence)
{
	this->currentSequence = data->getSequence(sequence);
	this->time = 0;
}

void AnimationState::update(f32 elapsedTime)
{
	if (this->currentSequence == NULL)
	{
		return;
	}

	this->currentSequence->update(elapsedTime, &this->time, &this->rectIndex, &this->events);
}

const AnimationRect *AnimationState::getRect() const
{
	if (this->currentSequence == NULL)
	{
		return NULL;
	}
	
	return this->currentSequence->getRect(this->rectIndex);
}

bool AnimationState::hasEvent(std::string *event)
{
	if (this->events.empty())
	{
		return false;
	}

	*event = this->events.front();
	this->events.pop();
	
	return true;
}

} // engine namespace

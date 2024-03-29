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

AnimationState::AnimationState(AnimationData *data) : data(data), currentSequence(NULL)
{
}

void AnimationState::setCurrentSequence(std::string sequence)
{
	this->currentSequenceName = sequence;
	this->currentSequence = data->getSequence(sequence);
	this->time = 0;
}

std::string AnimationState::getCurrentSequence()
{
	return this->currentSequenceName;
}

void AnimationState::update(f32 elapsedTime)
{
	if (this->currentSequence == NULL)
	{
		return;
	}

	this->time = this->currentSequence->extractInformations(this->time, elapsedTime, &this->rect, &this->events);
}

const AnimationRect *AnimationState::getRect() const
{
	if (this->currentSequence == NULL)
	{
		return NULL;
	}
	
	return &this->rect;
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

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

void AnimationState::setSequence(std::string sequence)
{
	this->sequence = sequence;
	this->time = 0;
}

void AnimationState::update(f32 elapsedTime)
{
	AnimationSequence *sequence = data->sequences[this->sequence];
	if (sequence == NULL)
	{
		return;
	}

	f32 baseTime = this->time;
	this->time += elapsedTime;

	while (this->time > sequence->totalDuration)
	{
		for (AnimationSequence::EventMap::const_iterator it = sequence->events.lower_bound(baseTime); it != sequence->events.upper_bound(sequence->totalDuration); ++it)
		{
			this->events.push(it->second);
		}
		this->time -= sequence->totalDuration;
		baseTime = 0;
	}

	for (AnimationSequence::EventMap::const_iterator it = sequence->events.lower_bound(baseTime); it != sequence->events.lower_bound(this->time); ++it)
	{
		this->events.push(it->second);
	}

	i32 index = this->time / sequence->frameDuration;
	this->rect = sequence->rects[index];
}

const AnimationRect *AnimationState::getRect() const
{
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

}

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
#include <engine/AnimationRect.hpp>

namespace engine {

AnimationSequence::AnimationSequence(u32 rectCount, f32 frameDuration) : rectCount(rectCount), frameDuration(frameDuration)
{
	this->rects = new AnimationRect[this->rectCount];
	
	this->totalDuration = this->frameDuration * this->rectCount;
}

AnimationSequence::~AnimationSequence()
{
	delete [] this->rects;
}

void AnimationSequence::setRect(u32 index, const AnimationRect *rect)
{
	if (index < this->rectCount)
	{
		this->rects[index] = *rect;
	}
}

const AnimationRect *AnimationSequence::getRect(u32 index) const
{
	if (index < this->rectCount)
	{
		return &this->rects[index];
	}
	return NULL;
}

void AnimationSequence::addEvent(f32 time, const std::string & event)
{
	this->events.insert(std::pair<f32, std::string>(time, event));
}

void AnimationSequence::update(f32 elapsedTime, f32 *time, u32 *rectIndex, std::queue<std::string> *events) const
{
	f32 baseTime = *time;
	*time += elapsedTime;
	
	while (*time >= this->totalDuration)
	{
		for (EventMap::const_iterator it = this->events.lower_bound(baseTime); it != this->events.upper_bound(this->totalDuration); ++it)
		{
			events->push(it->second);
		}
		*time -= this->totalDuration;
		baseTime = 0;
	}

	for (EventMap::const_iterator it = this->events.lower_bound(baseTime); it != this->events.lower_bound(*time); ++it)
	{
		events->push(it->second);
	}

	*rectIndex = *time / this->frameDuration;
}

} // engine namespace

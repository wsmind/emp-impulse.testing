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
#include <engine/DataFile.hpp>

namespace engine {

AnimationSequence::AnimationSequence(DataFile *file)
{
	this->frameDuration = file->readF32();

	this->rectCount = file->readU32();

	this->rects = new AnimationRect[this->rectCount];
	
	this->totalDuration = this->frameDuration * this->rectCount;
	
	for (u32 j = 0; j < this->rectCount; ++j)
	{
		AnimationRect *rect = &this->rects[j];
		
		rect->left = file->readU32();
		rect->top = file->readU32();
		rect->right = file->readU32();
		rect->bottom = file->readU32();
		rect->xOffset = file->readU32();
		rect->yOffset = file->readU32();
	}

	u32 eventCount = file->readU32();

	for (u32 j = 0; j < eventCount; ++j)
	{
		f32 time = file->readF32();
		std::string event = file->readString();
		this->events.insert(std::pair<f32, std::string>(time, event));
	}
}

AnimationSequence::~AnimationSequence()
{
	delete [] this->rects;
}

f32 AnimationSequence::extractInformations(f32 startTime, f32 duration, AnimationRect *rect, std::queue<std::string> *events) const
{
	f32 baseTime = startTime;
	f32 time = startTime + duration;
	
	while (time >= this->totalDuration)
	{
		for (EventMap::const_iterator it = this->events.lower_bound(baseTime); it != this->events.upper_bound(this->totalDuration); ++it)
		{
			events->push(it->second);
		}
		time -= this->totalDuration;
		baseTime = 0;
	}

	for (EventMap::const_iterator it = this->events.lower_bound(baseTime); it != this->events.lower_bound(time); ++it)
	{
		events->push(it->second);
	}

	u32 rectIndex = time / this->frameDuration;
	*rect = this->rects[rectIndex];
	
	return time;
}

} // engine namespace

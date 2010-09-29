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

#include <engine/AnimationData.hpp>
#include <iostream>
#include <fstream>
#include <engine/DataFile.hpp>
#include <engine/AnimationRect.hpp>
#include <engine/AnimationSequence.hpp>

namespace engine {

bool AnimationData::load(const std::string & filename)
{
	DataFile file;

	if (!file.load(filename))
	{
		return false;
	}

	u32 sequenceCount = file.readU32();

	for (u32 i = 0; i < sequenceCount; ++i)
	{
		std::string name = file.readString();

		f32 frameDuration = file.readF32();

		u32 rectCount = file.readU32();

		AnimationSequence *sequence = new AnimationSequence(rectCount, frameDuration);

		for (u32 j = 0; j < rectCount; ++j)
		{
			u32 left = file.readU32();
			u32 top = file.readU32();
			u32 right = file.readU32();
			u32 bottom = file.readU32();
			u32 xOffset = file.readU32();
			u32 yOffset = file.readU32();
			
			AnimationRect rect(left, top, right, bottom, xOffset, yOffset);
			sequence->setRect(j, &rect);
		}

		u32 eventCount = file.readU32();

		for (u32 j = 0; j < eventCount; ++j)
		{
			f32 time = file.readF32();
			std::string event = file.readString();
			sequence->addEvent(time, event);
		}

		this->sequences[name] = sequence;
	}

	return true;
}

const AnimationSequence *AnimationData::getSequence(const std::string & name) const
{
	SequenceMap::const_iterator it = this->sequences.find(name);
	
	if (it == this->sequences.end())
	{
		return NULL;
	}
	
	return it->second;
}

} // engine namespace

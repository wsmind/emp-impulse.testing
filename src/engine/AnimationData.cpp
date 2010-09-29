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

#include <iostream>
#include <fstream>

#include <engine/AnimationRect.hpp>
#include <engine/AnimationSequence.hpp>
#include <engine/AnimationData.hpp>

static u8 readU8(std::ifstream & file)
{
	char c;
	file.get(c);
	return (u8)c;
}

static u32 readU32(std::ifstream & file)
{
	u32 val = 0;
	val |= (u32)((u32)readU8(file) << 24);
	val |= (u32)((u32)readU8(file) << 16);
	val |= (u32)((u32)readU8(file) << 8);
	val |= (u32)((u32)readU8(file) << 0);
	return val;
}

static f32 readF32(std::ifstream & file)
{
	u32 val = readU32(file);
	return *(f32 *)(void *)&val;
}

static std::string readString(std::ifstream & file)
{
	char c;
	i32 len = readU32(file);
	std::string str;
	str.reserve(len);
	for (int i = 0; i < len; ++i)
	{
		file.get(c);
		str.append(1, c);
	}
	return str;
}

namespace engine {

bool AnimationData::load(const std::string & filename)
{
	std::ifstream file(filename.c_str(), std::ios_base::out | std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	u32 sequenceCount = readU32(file);

	for (u32 i = 0; i < sequenceCount; ++i)
	{
		std::string name = readString(file);

		AnimationSequence *sequence = new AnimationSequence;

		sequence->frameDuration = readF32(file);

		sequence->rectCount = readU32(file);

		sequence->rects = new AnimationRect[sequence->rectCount];

		sequence->totalDuration = sequence->frameDuration * sequence->rectCount;

		for (u32 j = 0; j < sequence->rectCount; ++j)
		{
			AnimationRect *rect = &sequence->rects[j];

			rect->rect.Left = readU32(file);
			rect->rect.Top = readU32(file);
			rect->rect.Right = readU32(file);
			rect->rect.Bottom = readU32(file);

			rect->offset.x = readU32(file);
			rect->offset.y = readU32(file);
		}

		u32 eventCount = readU32(file);

		for (u32 j = 0; j < eventCount; ++j)
		{
			f32 time = readF32(file);
			std::string event = readString(file);
			sequence->events.insert(std::pair<f32, std::string>(time, event));
		}

		this->sequences[name] = sequence;
	}

	return true;
}

void AnimationData::unload()
{
	for (SequenceMap::iterator it = this->sequences.begin(); it != this->sequences.end(); ++it)
	{
		delete it->second->rects;
	}
}

}

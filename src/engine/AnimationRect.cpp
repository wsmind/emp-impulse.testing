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

#include <engine/AnimationRect.hpp>

namespace engine {

AnimationRect::AnimationRect() : left(0), top(0), right(0), bottom(0), xOffset(0), yOffset(0)
{
}

AnimationRect::AnimationRect(u32 left, u32 top, u32 right, u32 bottom, u32 xOffset, u32 yOffset) : left(left), top(top), right(right), bottom(bottom), xOffset(xOffset), yOffset(yOffset)
{
}

u32 AnimationRect::getLeft() const
{
	return this->left;
}

u32 AnimationRect::getTop() const
{
	return this->top;
}

u32 AnimationRect::getRight() const
{
	return this->right;
}

u32 AnimationRect::getBottom() const
{
	return this->bottom;
}

i32 AnimationRect::getXOffset() const
{
	return this->xOffset;
}

i32 AnimationRect::getYOffset() const
{
	return this->yOffset;
}

}

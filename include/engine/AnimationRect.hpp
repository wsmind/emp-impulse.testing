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

#ifndef __ANIMATIONRECT_HPP__
#define __ANIMATIONRECT_HPP__

#include <common.hpp>
#include <math/Vec2.hpp>

namespace engine {

/**
 * \class AnimationRect
 * \author Jonathan Giroux
 *
 * \brief The AnimationRect struct defines a single animation frame.
 *
 * A frame contains:
 * \li a rectangle, defining the position of the frame image inside the
 * animation image.
 * \li an offset, for the sprite to stay in place.
 */
class AnimationRect
{
	public:
		
		/**
		 * \brief Constructs an empty animation rectangle.
		 */
		AnimationRect();
		
		/**
		 * \brief Constructs an animation rectangle.
		 */
		AnimationRect(u32 left, u32 top, u32 right, u32 bottom, u32 xOffset, u32 yOffset);
		
		/**
		 * \brief Gets left coordinate of the rectangle.
		 */
		u32 getLeft() const;

		/**
		 * \brief Gets top coordinate of the rectangle.
		 */
		u32 getTop() const;

		/**
		 * \brief Gets right coordinate of the rectangle.
		 */
		u32 getRight() const;

		/**
		 * \brief Gets bottom coordinate of the rectangle.
		 */
		u32 getBottom() const;

		/**
		 * \brief Gets x coordinate of the offset.
		 */
		i32 getXOffset() const;

		/**
		 * \brief Gets Y coordinate of the offset.
		 */
		i32 getYOffset() const;
		
	private:
		
		u32 left;
		
		u32 top;
		
		u32 right;
		
		u32 bottom;

		/**
		 * \brief X offset.
		 */
		i32 xOffset;

		/**
		 * \brief Y offset.
		 */
		i32 yOffset;
};

} // engine namespace

#endif // __ANIMATIONRECT_HPP__

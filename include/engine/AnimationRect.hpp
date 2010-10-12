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
 * \author Jonathan Giroux
 *
 * \brief The AnimationRect struct defines a single animation frame.
 *
 * A frame contains:
 * \li a rectangle, defining the position of the frame image inside the
 * animation image.
 * \li an offset, for the sprite to stay in place.
 */
struct AnimationRect
{
	/**
	 * \brief Left coordinate of the rectangle.
	 */
	u32 left;

	/**
	 * \brief Top coordinate of the rectangle.
	 */
	u32 top;

	/**
	 * \brief Right coordinate of the rectangle.
	 */
	u32 right;

	/**
	 * \brief Bottom coordinate of the rectangle.
	 */
	u32 bottom;

	/**
	 * \brief X coordinate of the offset.
	 */
	i32 xOffset;

	/**
	 * \brief Y coordinate of the offset.
	 */
	i32 yOffset;
};

} // engine namespace

#endif // __ANIMATIONRECT_HPP__

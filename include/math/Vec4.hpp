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

#ifndef __VEC4_HPP__
#define __VEC4_HPP__

#include <common.hpp>
#include <math/Vec3.hpp>

namespace math {

/**
 * \class Vec4
 * \brief 4D vector (cartesian space)
 * \author Remi Papillie
 *
 * This class implements a 4D vector. The values are stored as 32-bits floats.
 * Along with other math classes, this class shows as public its coordinate
 * members, to let the user directly access those data.
 */
class Vec4
{
	public:
		//! \brief The x coordinate of the vector (in cartesian space)
		f32 x;
		//! \brief The y coordinate of the vector (in cartesian space)
		f32 y;
		//! \brief The z coordinate of the vector (in cartesian space)
		f32 z;
		//! \brief The w coordinate of the vector (in cartesian space)
		f32 w;
		
		/**
		 * \brief Construct a vector (0, 0, 0, 0)
		 */
		Vec4();
		
		/**
		 * \brief Construct a vector from a Vec2 object
		 * \param v the 3D vector
		 * \param w the third coordinate of the vector being constructed
		 */
		Vec4(const Vec3& v, f32 w);
		
		/**
		 * \brief Construct a vector (x, y, z, w)
		 */
		Vec4(f32 x, f32 y, f32 z, f32 w);
		
		/**
		 * \brief Text output
		 */
		friend std::ostream& operator <<(std::ostream& out, const Vec4& v);
};

} // math namespace

#include <math/Vec4.inline.hpp>

#endif // __VEC4_HPP__

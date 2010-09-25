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

#ifndef __VEC3_HPP__
#define __VEC3_HPP__

#include <common.hpp>
#include <math/Vec2.hpp>

namespace math {

/**
 * \class Vec3
 * \brief 3D vector (cartesian space)
 * \author Remi Papillie
 * \author Jonathan Giroux
 *
 * This class implements a 3D vector. The values are stored as 32-bits floats.
 * Along with other math classes, this class shows as public its coordinate
 * members, to let the user directly access those data.
 */
class Vec3
{
	public:
		//! \brief The x coordinate of the vector (in cartesian space)
		f32 x;
		//! \brief The y coordinate of the vector (in cartesian space)
		f32 y;
		//! \brief The z coordinate of the vector (in cartesian space)
		f32 z;
		
		/**
		 * \brief Construct a vector (0, 0, 0)
		 */
		Vec3();
		
		/**
		 * \brief Construct a vector from a Vec2 object
		 * \param v the 2D vector
		 * \param z the third coordinate of the vector beeing constructed
		 */
		Vec3(const Vec2& v, f32 z);
		
		/**
		 * \brief Construct a vector (x, y, z)
		 * \param x the x coordinate of the new vector
		 * \param y the y coordinate of the new vector
		 * \param z the z coordinate of the new vector
		 */
		Vec3(f32 x, f32 y, f32 z);
		
		/**
		 * \brief Addition of two vectors (per-component)
		 */
		Vec3 operator +(const Vec3& v) const;
		
		/**
		 * \brief Addition of two vectors (per-component)
		 */
		Vec3& operator +=(const Vec3& v);
		
		/**
		 * \brief Unary minus operator
		 */
		Vec3 operator -() const;
		
		/**
		 * \brief Subtraction of two vectors (per-component)
		 */
		Vec3 operator -(const Vec3& v) const;
		
		/**
		 * \brief Subtraction of two vectors (per-component)
		 */
		Vec3& operator -=(const Vec3& v);
		
		/**
		 * \brief Multiplication of two vectors (per-component)
		 */
		Vec3 operator *(const Vec3& v) const;
		
		/**
		 * \brief Multiplication of two vectors (per-component)
		 */
		Vec3& operator *=(const Vec3& v);
		
		/**
		 * \brief Multiplication by a real number
		 */
		Vec3 operator *(f32 k) const;
		Vec3& operator *=(f32 k);
		friend Vec3 operator *(f32 k, const Vec3& v);
		
		/**
		 * \brief Division by a real number
		 */
		Vec3 operator /(f32 k) const;
		Vec3& operator /=(f32 k);
		friend Vec3 operator /(f32 k, const Vec3& v);

		/**
		 * \brief Usual 3-dimensional dot product
		 * \param v the second vector of the dot product operation
		 */
		f32 dot(const Vec3& v) const;
		
		/**
		 * \brief Norm of the vector
		 */
		f32 norm() const;
		
		/**
		 * \brief Square of the norm of the vector
		 *
		 * This version should be preferred if there is no need for the real
		 * norm, as it avoids a square root.
		 */
		f32 norm2() const;
		
		/**
		 * \brief Normalization of the vector
		 * \return the normalized vector (of length 1)
		 *
		 * If the length of the original vector is 0, the returned vector is
		 * (0, 0, 0).
		 */
		Vec3 normalize() const;
		
		/**
		 * \brief Usual 3D cross product
		 * \param v the second vector
		 */
		Vec3 cross(const Vec3& v) const;

		/**
		 * \brief Text output
		 */
		friend std::ostream& operator <<(std::ostream& out, const Vec3& v);
};

} // math namespace

#include <math/Vec3.inline.hpp>

#endif // __VEC3_HPP__

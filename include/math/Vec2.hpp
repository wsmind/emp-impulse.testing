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

#ifndef __VEC2_HPP__
#define __VEC2_HPP__

#include <common.hpp>
#include <iostream>

namespace math {

/**
 * \class Vec2
 * \brief 2D vector (cartesian space)
 * \author Remi Papillie
 * \author Jonathan Giroux
 *
 * This class implements a 2D vector. The values are stored as 32-bits floats.
 * Along with other math classes, this class shows as public its coordinate
 * members, to let the user directly access those data.
 */
class IMPULSE_MATH_EXPORT Vec2
{
	public:
		//! \brief The x coordinate of the vector (in cartesian space)
		f32 x;
		//! \brief The y coordinate of the vector (in cartesian space)
		f32 y;
		
		/**
		 * \brief Construct a vector (0, 0)
		 */
		Vec2();
		
		/**
		 * \brief Construct a vector (x, 0)
		 * \param x the x coordinate of the new vector
		 */
		Vec2(f32 x);
		
		/**
		 * \brief Construct a vector (x, y)
		 * \param x the x coordinate of the new vector
		 * \param y the y coordinate of the new vector
		 */
		Vec2(f32 x, f32 y);
		
		/**
		 * \brief Addition of two vectors (per-component)
		 */
		Vec2 operator +(const Vec2& v) const;
		
		/**
		 * \brief Add another vector to this one
		 */
		Vec2& operator +=(const Vec2& v);
		
		/**
		 * \brief Unary minus operator
		 */
		Vec2 operator -() const;
		
		/**
		 * \brief Subtraction of two vectors (per-component)
		 */
		Vec2 operator -(const Vec2& v) const;
		
		/**
		 * \brief Subtract another vector to this one
		 */
		Vec2& operator -=(const Vec2& v);
		
		/**
		 * \brief Multiplication of two vectors (per-component)
		 */
		Vec2 operator *(const Vec2& v) const;
		
		/**
		 * \brief Multiplication another vector to this one
		 */
		Vec2& operator *=(const Vec2& v);
		
		/**
		 * \brief Multiplication by a real number
		 */
		Vec2 operator *(f32 k) const;
		Vec2& operator *=(f32 k);
		friend Vec2 operator *(f32 k, const Vec2& v);
		
		/**
		 * \brief Division by a real number
		 */
		Vec2 operator /(f32 k) const;
		Vec2& operator /=(f32 k);
		friend Vec2 operator /(f32 k, const Vec2& v);
		
		/**
		 * \brief Usual 2-dimensional dot product
		 * \param v the second vector of the dot product operation
		 */
		f32 dot(const Vec2& v) const;
		
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
		 * (0, 0).
		 */
		Vec2 normalize() const;
		
		/**
		 * \brief The signed area of the parallelogram formed by the two vectors
		 * \return the signed area
		 *
		 * This operation is the 2D equivalent to the 3D cross-product, and also
		 * equals the determinant of the 2x2 matrix formed by the two given
		 * vectors.
		 */
		f32 area(const Vec2& v) const;
		
		/**
		 * \brief Text output
		 */
		friend std::ostream& operator <<(std::ostream& out, const Vec2& v);
};

} // math namespace

#include <math/Vec2.inline.hpp>

#endif // __VEC2_HPP__


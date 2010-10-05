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

#ifndef __MAT33_HPP__
#define __MAT33_HPP__

#include <common.hpp>
#include <math/Vec2.hpp>
#include <math/Vec3.hpp>

namespace math {

/**
 * \class Mat33
 * \brief 3x3 Matrix
 * \author Remi Papillie
 * \author Jonathan Giroux
 *
 * This class represents a 3x3 matrix. The values are stored as 32-bits floats.
 * Along with other math classes, this class shows as public its coordinate
 * members, to let the user directly access those data.
 */
class Mat33
{
	public:
		//! \brief The 9 values
		f32 v[9];
		
		/**
		 * \brief Construct the 3x3 identity matrix
		 */
		Mat33();
		
		/**
		 * \brief Construct a matrix from three Vec3 objects
		 * \param r1 the first row
		 * \param r2 the second row
		 * \param r2 the third row
		 */
		Mat33(const Vec3& r1, const Vec3& r2, const Vec3& r3);
		
		/**
		 * \brief Construct a matrix from 9 values
		 */
		Mat33(f32 x0, f32 x1, f32 x2, f32 x3, f32 x4, f32 x5, f32 x6, f32 x7, f32 x8);
		
		/**
		 * \brief Construct a matrix from a 9-value array
		 */
		Mat33(f32 values[9]);
		
		/**
		 * \brief Addition of two matrices (per-component)
		 */
		Mat33 operator +(const Mat33& m) const;
		
		/**
		 * \brief Addition of two matrices (per-component)
		 */
		Mat33& operator +=(const Mat33& m);
		
		/**
		 * \brief Unary minus operator
		 */
		Mat33 operator -() const;
		
		/**
		 * \brief Subtraction of two matrices (per-component)
		 */
		Mat33 operator -(const Mat33& m) const;
		
		/**
		 * \brief Subtraction of two matrices (per-component)
		 */
		Mat33& operator -=(const Mat33& m);
		
		/**
		 * \brief Multiplication by a real number
		 */
		Mat33 operator *(f32 k) const;
		Mat33& operator *=(f32 k);
		friend Mat33 operator *(f32 k, const Mat33& m);
		
		/**
		 * \brief Usual 3x3 matrix multiplication
		 */
		Mat33 operator *(const Mat33& m) const;
		
		/**
		 * \brief Usual 3x3 matrix multiplication
		 */
		Mat33& operator *=(const Mat33& m);
		
		/**
		 * \brief 2D vector transformation
		 */
		Vec2 operator *(const Vec2& v) const;
		
		/**
		 * \brief 3D vector transformation
		 */
		Vec3 operator *(const Vec3& v) const;
		
		/**
		 * \brief Usual 3x3 determinant
		 * \return the matrix determinant
		 */
		f32 determinant() const;
		
		/**
		 * \brief Matrix transpose
		 */
		Mat33 transpose() const;
		
		/**
		 * \brief Matrix inverse
		 */
		Mat33 inverse() const;
		
		/**
		 * \brief Translation vector in homogeneous coordinates
		 * \return translation vector
		 */
		Vec2 translationVector() const;
		
		/**
		 * \brief Text output
		 */
		friend std::ostream& operator <<(std::ostream& out, const Mat33& m);
};

} // math namespace

#include <math/Mat33.inline.hpp>

#endif // __MAT33_HPP__

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

namespace math {

inline Mat33::Mat33()
{
	this->v[0] = 1.0f;
	this->v[1] = 0.0f;
	this->v[2] = 0.0f;
	this->v[3] = 0.0f;
	this->v[4] = 1.0f;
	this->v[5] = 0.0f;
	this->v[6] = 0.0f;
	this->v[7] = 0.0f;
	this->v[8] = 1.0f;
}

inline Mat33::Mat33(const Vec3& r1, const Vec3& r2, const Vec3& r3)
{
	this->v[0] = r1.x;
	this->v[1] = r1.y;
	this->v[2] = r1.z;
	this->v[3] = r2.x;
	this->v[4] = r2.y;
	this->v[5] = r2.z;
	this->v[6] = r3.x;
	this->v[7] = r3.y;
	this->v[8] = r3.z;
}

inline Mat33::Mat33(f32 x0, f32 x1, f32 x2, f32 x3, f32 x4, f32 x5, f32 x6, f32 x7, f32 x8)
{
	this->v[0] = x0;
	this->v[1] = x1;
	this->v[2] = x2;
	this->v[3] = x3;
	this->v[4] = x4;
	this->v[5] = x5;
	this->v[6] = x6;
	this->v[7] = x7;
	this->v[8] = x8;
}

inline Mat33::Mat33(f32 values[9])
{
	this->v[0] = values[0];
	this->v[1] = values[1];
	this->v[2] = values[2];
	this->v[3] = values[3];
	this->v[4] = values[4];
	this->v[5] = values[5];
	this->v[6] = values[6];
	this->v[7] = values[7];
	this->v[8] = values[8];
}

inline Mat33 Mat33::operator +(const Mat33& m) const
{
	return Mat33(
		this->v[0] + m.v[0], this->v[1] + m.v[1], this->v[2] + m.v[2],
		this->v[3] + m.v[3], this->v[4] + m.v[4], this->v[5] + m.v[5],
		this->v[6] + m.v[6], this->v[7] + m.v[7], this->v[8] + m.v[8]
	);
}

inline Mat33& Mat33::operator +=(const Mat33& m)
{
	return (*this = *this + m);
}

inline Mat33 Mat33::operator -() const
{
	return Mat33(
		-this->v[0], -this->v[1], -this->v[2],
		-this->v[3], -this->v[4], -this->v[5],
		-this->v[6], -this->v[7], -this->v[8]
	);
}

inline Mat33 Mat33::operator -(const Mat33& m) const
{
	return Mat33(
		this->v[0] - m.v[0], this->v[1] - m.v[1], this->v[2] - m.v[2],
		this->v[3] - m.v[3], this->v[4] - m.v[4], this->v[5] - m.v[5],
		this->v[6] - m.v[6], this->v[7] - m.v[7], this->v[8] - m.v[8]
	);
}

inline Mat33& Mat33::operator -=(const Mat33& m)
{
	return (*this = *this - m);
}

inline Mat33 Mat33::operator *(f32 k) const
{
	return Mat33(
		this->v[0] * k, this->v[1] * k, this->v[2] * k,
		this->v[3] * k, this->v[4] * k, this->v[5] * k,
		this->v[6] * k, this->v[7] * k, this->v[8] * k
	);
}

inline Mat33& Mat33::operator *=(f32 k)
{
	return (*this = *this * k);
}

inline Mat33 operator *(f32 k, const Mat33& m)
{
	return m * k;
}

inline Mat33 Mat33::operator *(const Mat33& m) const
{
	return Mat33(
		this->v[0] * m.v[0] + this->v[1] * m.v[3] + this->v[2] * m.v[6], this->v[0] * m.v[1] + this->v[1] * m.v[4] + this->v[2] * m.v[7], this->v[0] * m.v[2] + this->v[1] * m.v[5] + this->v[2] * m.v[8],
		this->v[3] * m.v[0] + this->v[4] * m.v[3] + this->v[5] * m.v[6], this->v[3] * m.v[1] + this->v[4] * m.v[4] + this->v[5] * m.v[7], this->v[3] * m.v[2] + this->v[4] * m.v[5] + this->v[5] * m.v[8],
		this->v[6] * m.v[0] + this->v[7] * m.v[3] + this->v[8] * m.v[6], this->v[6] * m.v[1] + this->v[7] * m.v[4] + this->v[8] * m.v[7], this->v[6] * m.v[2] + this->v[7] * m.v[5] + this->v[8] * m.v[8]
	);
}

inline Mat33& Mat33::operator *=(const Mat33& m)
{
	return (*this = *this * m);
}

inline Vec2 Mat33::operator *(const Vec2& v) const
{
	return Vec2(
		this->v[0] * v.x + this->v[1] * v.y + this->v[2],
		this->v[3] * v.x + this->v[4] * v.y + this->v[5]
	);
}

inline Vec3 Mat33::operator *(const Vec3& v) const
{
	return Vec3(
		this->v[0] * v.x + this->v[1] * v.y + this->v[2] * v.z,
		this->v[3] * v.x + this->v[4] * v.y + this->v[5] * v.z,
		this->v[6] * v.x + this->v[7] * v.y + this->v[8] * v.z
	);
}

inline f32 Mat33::determinant() const
{
	return this->v[0] * this->v[4] * this->v[8] + this->v[1] * this->v[5] * this->v[6] + this->v[2] * this->v[3] * this->v[7] - this->v[0] * this->v[5] * this->v[7] - this->v[1] * this->v[3] * this->v[8] - this->v[2] * this->v[4] * this->v[6];
}

inline Mat33 Mat33::transpose() const
{
	return Mat33(
		this->v[0], this->v[3], this->v[6],
		this->v[1], this->v[4], this->v[7],
		this->v[2], this->v[5], this->v[8]
	);
}

inline Mat33 Mat33::inverse() const
{
	f32 c[9]; // cofactor matrix
	c[0] = (this->v[4] * this->v[8] - this->v[5] * this->v[7]);
	c[1] = -(this->v[3] * this->v[8] - this->v[5] * this->v[6]);
	c[2] = (this->v[3] * this->v[7] - this->v[4] * this->v[6]);
	c[3] = -(this->v[1] * this->v[8] - this->v[2] * this->v[7]);
	c[4] = (this->v[0] * this->v[8] - this->v[2] * this->v[6]);
	c[5] = -(this->v[0] * this->v[7] - this->v[1] * this->v[6]);
	c[6] = (this->v[1] * this->v[5] - this->v[2] * this->v[4]);
	c[7] = -(this->v[0] * this->v[5] - this->v[2] * this->v[3]);
	c[8] = (this->v[0] * this->v[4] - this->v[1] * this->v[3]);
	
	f32 determinant = this->v[0] * c[0] + this->v[1] * c[1] + this->v[2] * c[2];
	
	return 1.0f / determinant * Mat33(c).transpose();
}

inline Vec2 Mat33::translationVector() const
{
	return Vec2(this->v[2], this->v[5]);
}

inline std::ostream& operator <<(std::ostream& out, const Mat33& m)
{
	out << m.v[0] << ", " << m.v[1] << ", " << m.v[2] << std::endl;
	out << m.v[3] << ", " << m.v[4] << ", " << m.v[5] << std::endl;
	out << m.v[6] << ", " << m.v[7] << ", " << m.v[8] << std::endl;

	return out;
}

} // math namespace

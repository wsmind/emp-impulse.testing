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

#ifndef __VEC3_INLINE_HPP__
#define __VEC3_INLINE_HPP__

namespace math {

inline Vec3::Vec3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

inline Vec3::Vec3(const Vec2& v, f32 z)
{
	this->x = v.x;
	this->y = v.y;
	this->z = z;
}

inline Vec3::Vec3(f32 x, f32 y, f32 z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

inline Vec3 Vec3::operator +(const Vec3& v) const
{
	return Vec3(this->x + v.x, this->y + v.y, this->z + v.z);
}

inline Vec3& Vec3::operator +=(const Vec3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

inline Vec3 Vec3::operator -() const
{
	return Vec3(-this->x, -this->y, -this->z);
}

inline Vec3 Vec3::operator -(const Vec3& v) const
{
	return Vec3(this->x - v.x, this->y - v.y, this->z - v.z);
}

inline Vec3& Vec3::operator -=(const Vec3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

inline Vec3 Vec3::operator *(const Vec3& v) const
{
	return Vec3(this->x * v.x, this->y * v.y, this->z * v.z);
}

inline Vec3& Vec3::operator *=(const Vec3& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	return *this;
}

inline Vec3 Vec3::operator *(f32 k) const
{
	return Vec3(this->x * k, this->y * k, this->z * k);
}

inline Vec3& Vec3::operator *=(f32 k)
{
	this->x *= k;
	this->y *= k;
	this->z *= k;
	return *this;
}

inline Vec3 operator *(f32 k, const Vec3& v)
{
	return v * k;
}

inline Vec3 Vec3::operator /(f32 k) const
{
	return Vec3(this->x / k, this->y / k, this->z / k);
}

inline Vec3& Vec3::operator /=(f32 k)
{
	this->x /= k;
	this->y /= k;
	this->z /= k;
	return *this;
}

inline Vec3 operator /(f32 k, const Vec3& v)
{
	return Vec3(v.x / k, v.y / k, v.z / k);
}

inline f32 Vec3::dot(const Vec3& v) const
{
	return this->x * v.x + this->y * v.y + this->z *v.z;
}

inline f32 Vec3::norm() const
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

inline f32 Vec3::norm2() const
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

inline Vec3 Vec3::normalize() const
{
	f32 length = this->norm();
	if (length == 0.0f)
		return Vec3(0.0f, 0.0f, 0.0f);
	else
	{
		f32 factor = 1.0f / length;
		return Vec3(this->x * factor, this->y * factor, this->z * factor);
	}
}

inline Vec3 Vec3::cross(const Vec3& v) const
{
	return Vec3(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}

inline std::ostream& operator <<(std::ostream& out, const Vec3& v)
{
	return out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

} // math namespace

#endif // __VEC3_INLINE_HPP__

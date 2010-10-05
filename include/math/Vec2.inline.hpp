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

#ifndef __VEC2_INLINE_HPP__
#define __VEC2_INLINE_HPP__

#include <cmath>

namespace math {

inline Vec2::Vec2()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

inline Vec2::Vec2(f32 x)
{
	this->x = x;
	this->y = 0.0f;
}

inline Vec2::Vec2(f32 x, f32 y)
{
	this->x = x;
	this->y = y;
}

inline Vec2 Vec2::operator +(const Vec2& v) const
{
	return Vec2(this->x + v.x, this->y + v.y);
}

inline Vec2& Vec2::operator +=(const Vec2& v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

inline Vec2 Vec2::operator -() const
{
	return Vec2(-this->x, -this->y);
}

inline Vec2 Vec2::operator -(const Vec2& v) const
{
	return Vec2(this->x - v.x, this->y - v.y);
}

inline Vec2& Vec2::operator -=(const Vec2& v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

inline Vec2 Vec2::operator *(const Vec2& v) const
{
	return Vec2(this->x * v.x, this->y * v.y);
}

inline Vec2& Vec2::operator *=(const Vec2& v)
{
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

inline Vec2 Vec2::operator *(f32 k) const
{
	return Vec2(this->x * k, this->y * k);
}

inline Vec2& Vec2::operator *=(f32 k)
{
	this->x *= k;
	this->y *= k;
	return *this;
}

inline Vec2 operator *(f32 k, const Vec2& v)
{
	return Vec2(v.x * k, v.y * k);
}

inline Vec2 Vec2::operator /(f32 k) const
{
	return Vec2(this->x / k, this->y / k);
}

inline Vec2& Vec2::operator /=(f32 k)
{
	this->x /= k;
	this->y /= k;
	return *this;
}

inline Vec2 operator /(f32 k, const Vec2& v)
{
	return Vec2(v.x / k, v.y / k);
}

inline f32 Vec2::dot(const Vec2& v) const
{
	return this->x * v.x + this->y * v.y;
}

inline f32 Vec2::norm() const
{
	return sqrt(this->x * this->x + this->y * this->y);
}

inline f32 Vec2::norm2() const
{
	return this->x * this->x + this->y * this->y;
}

inline Vec2 Vec2::normalize() const
{
	f32 length = this->norm();
	if (length == 0.0f)
		return Vec2(0.0f, 0.0f);
	else
	{
		f32 factor = 1.0f / length;
		return Vec2(this->x * factor, this->y * factor);
	}
}

inline f32 Vec2::area(const Vec2& v) const
{
	// equivalent to ((*this, 0) x (v, 0)).z
	return this->x * v.y - this->y * v.x;
}

inline std::ostream& operator <<(std::ostream& out, const Vec2& v)
{
	return out << "(" << v.x << ", " << v.y << ")";
}

} // math namespace

#endif // __VEC2_INLINE_HPP__


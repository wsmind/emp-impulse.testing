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

#ifndef __VEC4_INLINE_HPP__
#define __VEC4_INLINE_HPP__

namespace math {

inline Vec4::Vec4()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}

inline Vec4::Vec4(const Vec3& v, f32 w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = w;
}

inline Vec4::Vec4(f32 x, f32 y, f32 z, f32 w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

inline std::ostream& operator <<(std::ostream& out, const Vec4& v)
{
	return out << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
}

} // math namespace

#endif // __VEC4_INLINE_HPP__

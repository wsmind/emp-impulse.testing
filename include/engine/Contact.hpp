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

#ifndef __CONTACT_HPP__
#define __CONTACT_HPP__

#include <common.hpp>
#include <math/Vec2.hpp>

namespace engine {

/**
* \struct Contact
* \author Elen Le Par
*
* \brief The Contact struct defines a contact when a collision occurs.
*
* A contact is defined by:
* \li the normalized normal of the collision.
* \li the penetration of the polygon into the other one.
*/
struct Contact
{
	math::Vec2 normal;
	float interpenetration;
};

} // engine namespace

#endif // __CONTACT_HPP__

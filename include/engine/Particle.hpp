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

#ifndef __PARTICLE_HPP__
#define __PARTICLE_HPP__

#include <common.hpp>
#include <math/Vec2.hpp>
#include <math/Vec4.hpp>

#include <SFML/Graphics.hpp>

namespace engine {

/**
 * \class Particle
 * \brief Describe a particle
 * \author Davy LEGGIERI
 *
 */
class Particle
{
	public:
		//! \brief x and y coordinate of the particle
		math::Vec2 position;
		//! \brief x and y coordinate speed of the particle (unit per sec)
		math::Vec2 speed;
		//! \brief rotation of the particle (counterclockwise and degre unit)
		f32 rotation;
		//! \brief orientation speed of the particle (degre per sec)
		f32 rotationSpeed;
		//! \brief color of the particle (x,y,z are RBG colour and w alpha)
		math::Vec4 color;
		//! \brief age of the particle (sec)
		f32 age;
		
		/**
		* \brief Construct a particle (position)
		* \param position x and y coordinate of the new particle
		*/
		Particle(math::Vec2 position);

		/**
		 * \brief Draw the particle in the windows
		 */
		void draw(sf::RenderWindow *window, sf::Sprite *sprite) const;
};

} // engine namespace

#endif // __PARTICLE_HPP__


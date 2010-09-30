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

#ifndef __PARTICLEBIN_HPP__
#define __PARTICLEBIN_HPP__

#include <common.hpp>
#include <engine/Particle.hpp>

namespace engine {
	
	/**
	 * \class ParticleBin
	 * \brief Pool-base particle creation
	 * \author Davy LEGGIERI
	 *
	 */
	class ParticleBin
	{
	public:		
		/**
		 * \brief Construct a particleBin (1000)
		 */
		ParticleBin();
		
		/**
		 * \brief Construct a particleBin (size)
		 * \param size the pool-size
		 */
		ParticleBin(u32 size);
		
		/**
		 * \brief Destruct a particleBin
		 */
		virtual ~ParticleBin();
		
		/**
		 * \brief Obtain a Particle from pool
		 */
		Particle* obtain();
		
		/**
		 * \brief Recycle a Particle by pushing in pool
		 */
		void collect(Particle* p);
		
	private:
		u32 count;
		u32 size;
		Particle** bin;
	};
	
} // engine namespace

#endif // __PARTICLEBIN_HPP__


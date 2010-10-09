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

#ifndef __PARTICLESYSTEMLISTENER_HPP__
#define __PARTICLESYSTEMLISTENER_HPP__

#include <common.hpp>
#include <engine/Particle.hpp>

IMPULSE_FORWARD_DECLARE1(engine, ParticleSystem)

namespace engine {

/**
 * \class ParticleSystemListener
 * \brief Describe some event we can listen 
 * \author Davy LEGGIERI
 *
 */
class ParticleSystemListener
{
	public:
		/**
		* \brief Destruct a ParticleSystemListener
		*/
		virtual ~ParticleSystemListener() {}
	
		/**
		* \brief Called when the last particle is spawned (getRemainingParticleCount() == 0)
		* \param particleSystem pointer to the particle system concerned by this event
		*/
		virtual void lastParticleSpawned (ParticleSystem *particleSystem){}
	
		/**
		* \brief Called when the last flying particle is died (getFlyingParticleCount() == 0)
		* \param particleSystem pointer to the particle system concerned by this event
		*/
		virtual void lastFlyingParticleDied (ParticleSystem *particleSystem){}
};
	
} // engine namespace

#endif // __PARTICLESYSTEMLISTENER_HPP__


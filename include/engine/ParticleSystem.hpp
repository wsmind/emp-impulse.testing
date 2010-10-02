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

#ifndef __PARTICLESYSTEM_HPP__
#define __PARTICLESYSTEM_HPP__

#include <common.hpp>
#include <math/Vec2.hpp>
#include <math/Vec4.hpp>
#include <engine/Particle.hpp>
#include <SFML/Graphics.hpp>

#include <list>
#include <boost/pool/object_pool.hpp>

using namespace math;

namespace engine {
	
	/**
	 * \class ParticleSystem
	 * \brief UI particle effects
	 * \author Davy LEGGIERI
	 *
	 */
	class ParticleSystem
	{
	public:		
		/**
		 * \brief Construct a particleSystem
		 */
		ParticleSystem();
		
		/**
		 * \brief Know if particleSystem is active (try producing particle)
		 */
		bool isActive() const;
		
		/**
		 * \brief Active/Inactive particleSystem
		 * \param active true to activate the particleSystem, false to inactivate it.
		 */
		void setActive(bool active);
		
		/**
		 * \brief sprite applyed to each particle emitted by the particleSystem
		 * \param particleSprite particle sprite
		 */
		void setParticleSprite(sf::Sprite particleSprite);
		
		/**
		 * \brief particle lifetime (count down from birth)
		 * \param lifeTime particle lifetime
		 */
		void setParticleLifeTime(f32 lifeTime);
		
		/**
		 * \brief particle acceleration, only affect the position
		 * \param acceleration particle acceleration (in coordinate unit/seconds)
		 */
		void setParticleAcceleration(Vec2 acceleration);
		
		/**
		 * \brief particle rotation acceleration
		 * \param rotAcceleration particle rotation acceleration (in counterclockwise degre/seconds)
		 */
		void setParticleRotationAcceleration(f32 rotAcceleration);
		
		/**
		 * \brief particle alpha decay
		 * \param alphaDecay alpha decay (in RGBA unit/seconds)
		 */
		void setParticleAlphaDecay(Vec4 alphaDecay);
		
		/**
		 * \brief particle count that can will be created by the particle system
		 * \param particleCount particle count
		 */
		void setCapacity(u32 particleCount);
		
		/**
		 * \brief Update the particleSystem
		 * \param dt delta time before last update call
		 * \param forces forces to apply on each particle
		 */
		void update(f32 dt, math::Vec2 forces);
		
		/**
		 * \brief Draw the particleSystem in the windows
		 */
		void draw(sf::RenderWindow& window) const;
		
	private:
		//! \brief particle pool to improve performance
		boost::object_pool<Particle> particlePool;
		//! \brief living particles emitted by the particleSystem (dead particle are removed from it and collected by the pool)
		std::list<Particle> particles;
		//! \brief true when the particle system is produting particle (active), false otherwise
		bool actived;
		
		//! \brief sprite applyed to each particle
		sf::Sprite particleSprite;
		//! \brief particle lifeTime (in seconds)
		f32 particleLifeTime;
		//! \brief particle acceleration, only affect the position (in coordinate unit/seconds)
		Vec2 particleAcceleration;
		//! \brief particle rotation acceleration (in counterclockwise degre/seconds)
		f32 ParticleRotationAcceleration;
		//! \brief particle alpha decay (in RGBA unit/seconds)
		Vec4 particleAlphaDecay;
		
		//! \brief particle count that can will be created by the particle system
		u32 capacity;
		//! \brief particle count remaining to created
		u32 remainingParticleCount;
		//! \brief position of the particle emitter
		Vec2 position;
		//! \brief rotation of the particle emitter
		f32 rotation;
		//! \brief spawning rate (in particle/second)
		f32 spawningRate;

		//! \brief particle initial alpha (at birth)
		Vec4 particleInitAlpha;
		//! \brief particle initial acceleration, only affect the position (in coordinate unit/seconds)
		Vec2 particleInitAcceleration;
		//! \brief particle initial rotation acceleration (in counterclockwise degre/seconds)
		f32 ParticleInitRotationAcceleration;
		//! \brief x and y coordinate initial speed of the particle (unit per sec)
		Vec2 particleInitSpeed;
		//! \brief initial orientation speed of the particle (degre per sec)
		f32 particleInitialRotationSpeed;
	};
	
} // engine namespace

#endif // __PARTICLESYSTEM_HPP__


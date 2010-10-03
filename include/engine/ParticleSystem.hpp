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
		 * \brief Construct a particleSystem, not active and with unlimied particle spawn
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
		 * \brief particle acceleration, only affect the position
		 * \param x x coordinate particle acceleration (in coordinate unit/seconds)
		 * \param y y coordinate particle acceleration (in coordinate unit/seconds)
		 */
		void setParticleAcceleration(f32 x, f32 y);
		
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
		 * \brief particle alpha decay
		 * \param r red color decay (unit/second)
		 * \param g green color decay (unit/second)
		 * \param b blue color decay (unit/second)
		 * \param a alpha decay (unit/second)
		 */
		void setParticleAlphaDecay(f32 r, f32 g, f32 b, f32 a);
		
		/**
		 * \brief particle count that can will be created by the particle system, this method restart the internal particle count
		 * \param particleCount particle count, -1 for unlimited particle spawn
		 */
		void setCapacity(i32 particleCount);
		
		/**
		 * \brief particle emitter position (new particle birth position)
		 * \param position particle emitter position (x and y coordinate)
		 */
		void setPosition(Vec2 position);
		
		/**
		 * \brief particle emitter position (new particle birth position)
		 * \param x x coordinate
		 * \param y y coordinate
		 */
		void setPosition(f32 x, f32 y);
		
		/**
		 * \brief fix the particle spawn rate
		 * \param rate particle spawn rate (in particle/second)
		 */
		void setSpawnRate(f32 rate);
		
		/**
		 * \brief fix the particle initial speed (at birth)
		 * \param particleSpeed particle initial speed(in coordinate/second)
		 */
		void setParticleInitSpeed(Vec2 particleSpeed);	
		
		/**
		 * \brief fix the particle initial speed (at birth)
		 * \param x x coordinate particle initial speed(in coordinate/second)
		 * \param y x coordinate particle initial speed(in coordinate/second)
		 */
		void setParticleInitSpeed(f32 x, f32 y);	
		
		/**
		 * \brief fix the particle initial rotation (at birth)
		 * \param rot x coordinate particle initial speed(in counterclockwise degre)
		 */
		void setParticleInitRotation(f32 rot);
		
		/**
		 * \brief fix the particle initial acceleration (at birth)
		 * \param x x coordinate particle initial acceleration(in coordinate/second)
		 * \param y y coordinate particle initial acceleration(in coordinate/second)
		 */
		void setParticleInitAcceleration(f32 x, f32 y);
		
		/**
		 * \brief fix the particle initial acceleration (at birth)
		 * \param particleAcceleration particle initial acceleration(in coordinate/second)
		 */
		void setParticleInitAcceleration(Vec2 particleAcceleration);
		
		/**
		 * \brief fix the particle initial roation speed (at birth)
		 * \param particleRotationSpeed particle initial rotation speed(in coordinate/second)
		 */
		void setParticleInitRotationSpeed(f32 particleRotationSpeed);
		
		/**
		 * \brief fix the particle initial rotation acceleration (at birth)
		 * \param rotAcceleration particle initial acceleration(in counterclockwise degre/second)
		 */
		void setParticleInitRotationAcceleration(f32 rotAcceleration);
		
		/**
		 * \brief get the particle count remaining to spawn
		 * \return particle count remaining to spawn, or -1 if unlimited particle spawn
		 */
		i32 getRemainingParticleCount();
		
		/**
		 * \brief Update the particleSystem
		 * \param dt delta time before last update call
		 * \param forces forces to apply on each particle
		 */
		void update(f32 dt, math::Vec2 forces);
		
		/**
		 * \brief Draw the particleSystem in the windows
		 */
		void draw(sf::RenderWindow& window);
		
	private:
		//! \brief particle pool to improve performance
		boost::object_pool<Particle> particlePool;
		//! \brief living particles emitted by the particleSystem (dead particle are removed from it and collected by the pool)
		std::list<Particle *> particles;
		//! \brief true when the particle system is produting particle (active), false otherwise
		bool actived;
		//! \brief time elasped after the last particle spawn (in seconds)
		f32 timeAfterLastSpawning;
		
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
		i32 capacity;
		//! \brief particle count remaining to spawn
		i32 remainingParticleCount;
		//! \brief position of the particle emitter
		Vec2 position;
		//! \brief spawning rate (in particle/second)
		f32 spawningRate;

		//! \brief x and y coordinate initial speed of the particle (unit per sec)
		Vec2 particleInitSpeed;
		//! \brief initial orientation of the particle (in counterclockwise degre)
		f32 particleInitRotation;
		//! \brief initial orientation speed of the particle (in counterclockwise degre/second)
		f32 particleInitRotationSpeed;		
		//! \brief particle initial alpha (at birth)
		Vec4 particleInitAlpha;
		
		/**
		 * \brief Generate new particles
		 * \param count particle count to generate
		 */
		void generateParticle(int count);

	};
	
} // engine namespace

#endif // __PARTICLESYSTEM_HPP__


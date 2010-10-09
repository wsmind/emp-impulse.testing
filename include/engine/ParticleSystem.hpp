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

#include <list>
#include <vector>
#include <boost/pool/object_pool.hpp>

IMPULSE_FORWARD_DECLARE1(sf, Image)
IMPULSE_FORWARD_DECLARE1(sf, Sprite)
IMPULSE_FORWARD_DECLARE1(sf, RenderWindow)

namespace engine {
	
/**
 * \class ParticleSystem
 * \brief A particle system is composed by particles created by an emitter and the emitter itself
 * \author Davy LEGGIERI
 *
 */
class ParticleSystem
{
	public:		
		/**
		 * \brief Construct a particleSystem, the emitter is not active and with unlimited particle spawn, persitent particle (never dead) and SpawnRate of 1 particle per second
		 */
		ParticleSystem();
		
		/**
		 * \brief Destructor
		 */
		virtual ~ParticleSystem();

		/**
		 * \brief Know if the particle system emitter is active (try producing particle)
		 */
		bool isEmitterActive() const;
		
		/**
		 * \brief Active/Inactive particleSystem
		 * \param active true to activate the particleSystem, false to inactivate it.
		 */
		void setEmitterActive(bool active);
		
		/**
		 * \brief image for each particle emitted by the particleSystem (override setParticleColor method effects)
		 * \param particleImage particle image
		 */
		void setParticlesImage(sf::Image *particleImage);

		/**
		 * \brief particle lifetime (count down from birth)
		 * \param lifeTime particle lifetime, or 0 for persistent particle (never dead)
		 */
		void setParticlesLifeTime(f32 lifeTime);
		
		/**
		 * \brief particle rotation friction
		 * \param rotFriction particle rotation friction (in counterclockwise degre/seconds squared)
		 */
		void setParticlesRotationFriction(f32 rotFriction);
		
		/**
		 * \brief particle color decay
		 * \param colorDecay color decay (in RGBA unit/seconds)
		 */
		void setParticlesColorDecay(math::Vec4 colorDecay);
		
		/**
		 * \brief particle count that can will be created by the particle system emitter (this method reset the internal particle count)
		 * \param particleCount particle count, 0 for unlimited particle spawn
		 */
		void setEmitterCapacity(u32 particleCount);
		
		/**
		 * \brief particle emitter position (new particle birth position)
		 * \param position particle emitter position (x and y coordinate)
		 */
		void setEmitterPosition(math::Vec2 position);

		/**
		 * \brief move the emitter and the whole particleSytem to a new position (emitter and all particles are moved)
		 * \param position new position of the particle system emitter
		 */
		void moveEmitterAndWholeSystem(math::Vec2 position);

		/**
		 * \brief translate the whole particleSytem (emitter and all particles are moved)
		 * \param vector translate vector
		 */
		void translateAll(math::Vec2 vector);

		/**
		 * \brief fix the particle spawn rate
		 * \param rate particle spawn rate (in particle/second)
		 */
		void setEmitterSpawnRate(f32 rate);
		
		/**
		 * \brief fix the particle initial speed (at birth)
		 * \param particlesSpeed particles initial speed(in coordinate/second)
		 */
		void setParticlesInitSpeed(math::Vec2 particlesSpeed);
		
		/**
		 * \brief fix the particle initial rotation (at birth)
		 * \param rot x coordinate particle initial speed(in counterclockwise degre)
		 */
		void setParticlesInitRotation(f32 rot);
		
		/**
		 * \brief fix the particle initial rotation speed (at birth)
		 * \param particlesRotationSpeed particles initial rotation speed(in coordinate/second)
		 */
		void setParticlesInitRotationSpeed(f32 particlesRotationSpeed);
		
		/**
		 * \brief get the not spawned yet particle count
		 * \return particle count remaining to spawn, or -1 if unlimited particle spawn
		 */
		u32 getEmitterRemainingParticleCount();
	
		/**
		 * \brief get the flying particle count
		 * \return particle count of flying particle
		 */
		u32 getFlyingParticleCount();
		
		/**
		 * \brief Update the particleSystem
		 * \param dt delta time before last update call
		 * \param forces forces to apply on each particle
		 */
		//FIXEME: And the rotation ? How the rotation will evolve ?
		void update(f32 dt, math::Vec2 forces);
		
		/**
		 * \brief Draw the particleSystem in the windows
		 */
		void draw(sf::RenderWindow *window);
		
	private:
		//! \brief particle pool to improve performance
		boost::object_pool<Particle> particlePool;
		//! \brief living particles emitted by the particleSystem (dead particle are removed from it and collected by the pool)
		std::list<Particle *> particles;
		//! \brief true when the particle system is produting particle (active), false otherwise
		bool actived;
		//! \brief time elapsped after the last particle spawn (in seconds)
		f32 timeAfterLastSpawning;
		
		//! \brief sprite applyed to each particle
		sf::Sprite *particleSprite;
		//! \brief sprite initial color
		math::Vec4 particleSpriteInitColor;
		//! \brief particle lifeTime (in seconds)
		f32 particleLifeTime;
		//! \brief particle rotation friction (in counterclockwise degre/seconds squared)
		f32 particleRotationFriction;
		//! \brief particle color decay (in RGBA unit/seconds)
		math::Vec4 particleColorDecay;
		
		//! \brief particle count that can will be created by the particle system
		u32 capacity;
		//! \brief particle count remaining to spawn
		u32 remainingParticleCount;
		//! \brief position of the particle emitter
		math::Vec2 position;
		//! \brief spawning rate (in second between two particle spawns)
		f32 timeBetweenTwoSpawns;

		//! \brief x and y coordinate initial speed of the particle (unit per sec)
		math::Vec2 particleInitSpeed;
		//! \brief initial orientation of the particle (in counterclockwise degre)
		f32 particleInitRotation;
		//! \brief initial orientation speed of the particle (in counterclockwise degre/second)
		f32 particleInitRotationSpeed;		
		
		/**
		 * \brief Generate new particles
		 * \param count particle count to generate
		 */
		void generateParticles(u32 count);
	
		/**
		 * \brief Emit the event lastParticleSpawned for each listener
		 */
		void fireLastParticleSpawned();
	
		/**
		 * \brief Emit the event lastFlyingParticleDied for each listener
		 */
		void fireLastFlyingParticleDied();
};
	
} // engine namespace

#endif // __PARTICLESYSTEM_HPP__


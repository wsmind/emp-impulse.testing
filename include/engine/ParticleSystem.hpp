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
#include <engine/ParticleSystemListener.hpp>
#include <SFML/Graphics.hpp>

#include <list>
#include <vector>
#include <boost/pool/object_pool.hpp>

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
		 * \brief Construct a particleSystem, the emitter is not active and with unlimited particle spawn
		 */
		ParticleSystem();
		
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
		 * \brief sprite for each particle emitted by the particleSystem (override setParticleColor method effects)
		 * \param particleSprite particle sprite
		 */
		void setParticlesSprite(sf::Sprite *particleSprite);

		/**
		 * \brief particle lifetime (count down from birth)
		 * \param lifeTime particle lifetime
		 */
		void setParticlesLifeTime(f32 lifeTime);
		
		/**
		 * \brief particle rotation friction
		 * \param rotFriction particle rotation friction (in counterclockwise degre/seconds squared)
		 */
		void setParticlesRotationFriction(f32 rotFriction);
		
		/**
		 * \brief particle color decay
		 * \param alphaDecay alpha decay (in RGBA unit/seconds)
		 */
		void setParticlesColorDecay(math::Vec4 alphaDecay);
		
		/**
		 * \brief particle count that can will be created by the particle system emitter (this method reset the internal particle count)
		 * \param particleCount particle count, -1 for unlimited particle spawn
		 */
		void setEmitterCapacity(i32 particleCount);
		
		/**
		 * \brief particle emitter position (new particle birth position)
		 * \param position particle emitter position (x and y coordinate)
		 */
		void setEmitterPosition(math::Vec2 position);

		/**
		 * \brief move the whole particleSytem to a new position (emitter and all particles are moved)
		 * \param position new position of the particle system emitter
		 */
		void moveAllToAPosition(math::Vec2 position);

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
		i32 getEmitterRemainingParticleCount();
	
		/**
		 * \brief get the flying particle count
		 * \return particle count of flying particle
		 */
		i32 getFlyingParticleCount();
	
		/**
		 * \brief register a listener to the system particle events
		 * \return listener listener called on events
		 */
		void registerListener(ParticleSystemListener *listener);
	
		/**
		 * \brief unregister a listener to the system particle events
		 * \return listener listener to remove 
		 */
		void unregisterListener(ParticleSystemListener *listener);
		
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
		//! \brief particle lifeTime (in seconds)
		f32 particleLifeTime;
		//! \brief particle rotation friction (in counterclockwise degre/seconds squared)
		f32 ParticleRotationFriction;
		//! \brief particle color decay (in RGBA unit/seconds)
		math::Vec4 particleColorDecay;
		
		//! \brief particle count that can will be created by the particle system
		i32 capacity;
		//! \brief particle count remaining to spawn
		i32 remainingParticleCount;
		//! \brief position of the particle emitter
		math::Vec2 position;
		//! \brief spawning rate (in particle/second)
		f32 spawningRate;

		//! \brief x and y coordinate initial speed of the particle (unit per sec)
		math::Vec2 particleInitSpeed;
		//! \brief initial orientation of the particle (in counterclockwise degre)
		f32 particleInitRotation;
		//! \brief initial orientation speed of the particle (in counterclockwise degre/second)
		f32 particleInitRotationSpeed;		
		//! \brief particle initial color (at birth)
		math::Vec4 particleInitColor;
	
		//! \brief particle systems events listeners
		std::vector<ParticleSystemListener *> listeners;
		
		/**
		 * \brief Generate new particles
		 * \param count particle count to generate
		 */
		void generateParticles(int count);
	
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


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

#include <engine/ParticleSystem.hpp>

#include <ctime>
#include <cmath>


namespace engine {
	
	ParticleSystem::ParticleSystem()
	{
		this->actived=false;
	}

	bool ParticleSystem::isActive() const
	{
		return this->actived;
	}
	
	void ParticleSystem::setActive(bool active)
	{
		this->actived=active;
	}
	
	void ParticleSystem::setParticleSprite(sf::Sprite sprite)
	{
		this->particleSprite=sprite;
	}
	
	void ParticleSystem::setParticleLifeTime(f32 lifeTime)
	{
		this->particleLifeTime=lifeTime;	
	}
	
	void ParticleSystem::setParticleAcceleration(Vec2 acceleration)
	{
		this->particleAcceleration=acceleration;	
	}
	
	void ParticleSystem::setParticleRotationAcceleration(f32 rotAcceleration)
	{
		this->ParticleRotationAcceleration=rotAcceleration;
	}
	
	void ParticleSystem::setParticleAlphaDecay(Vec4 alphaDecay)
	{
		this->particleAlphaDecay=alphaDecay;
	}
	
	void ParticleSystem::setCapacity(u32 particleCount)
	{
		this->capacity=particleCount;
	}
	
	void ParticleSystem::update(f32 dt, math::Vec2 forces)
	//1.Remove dead particles
	//2.Update preexistent particles position, alpha, rotation
	//3.Add generated particles
	{
		std::list<Particle>::iterator it;
		it=particles.begin();
		
		//For each particle
		while(it != particles.end())
		{
			//update the age
			(*it).age+=dt; 
			//1.Remove dead particles
			if ( (*it).age > this->particleLifeTime )
			{
				particles.erase(it);	
				continue;
			}
			
			//2.Update preexistent particles position, alpha, rotation
			(*it).position+= dt * (*it).speed;
			(*it).position+= dt * this->particleAcceleration;
			(*it).position+= dt * forces;
			
			(*it).rotation+= dt * (*it).rotationSpeed;
			(*it).rotation+= dt * this->ParticleRotationAcceleration;
			
			(*it).alpha.x-= dt * this->particleAlphaDecay.x;
			(*it).alpha.y-= dt * this->particleAlphaDecay.y;
			(*it).alpha.z-= dt * this->particleAlphaDecay.z;
			(*it).alpha.w-= dt * this->particleAlphaDecay.w;
			
			//3.Add generated particles
			
			//Next particle
			++it;
		}

	}
	
	void ParticleSystem::draw(sf::RenderWindow& window) const
	{
		std::list<Particle>::iterator it;
		for (it=particles.begin(); it != particles.end(); ++it) 
		{
			(*it).draw(window, this->particleSprite);
		}
	}
	
} // engine namespace


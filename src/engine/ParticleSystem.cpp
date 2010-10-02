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
	
	void ParticleSystem::setPosition(Vec2 position)
	{
		this->position=position;
	}
	
	void ParticleSystem::setPosition(f32 x, f32 y)
	{
		this->position.x=x;
		this->position.y=y;
	}
	
	void ParticleSystem::setSpawnRate(f32 rate)
	{
		this->spawningRate=rate;	
	}
	
	void ParticleSystem::update(f32 dt, math::Vec2 forces)
	//1.Update particle age
	//2.Remove dead particles
	//3.Update preexistent particles speed, position, alpha, rotation, etc
	//4.Add generated particles
	{
		std::list<Particle *>::iterator it;
		it=particles.begin();
		
		//For each particle
		while(it != particles.end())
		{
			//1.update particle age
			(**it).age+=dt;
			
			//2.Remove dead particles
			if ( (**it).age > this->particleLifeTime )
			{
				Particle* p=(*it);
				it=particles.erase(it);
				this->particlePool.destroy(p);
				continue;
			}
			
			//3.Update preexistent particles speed, position, alpha, rotation, etc
			(**it).speed+= dt * (this->particleAcceleration + forces);
			
			(**it).position+= dt * (**it).speed;
			
			(**it).rotationSpeed+= dt * this->ParticleRotationAcceleration;
			
			(**it).rotation+= dt * (**it).rotationSpeed;
			
			(**it).alpha.x+= dt * this->particleAlphaDecay.x;
			(**it).alpha.y+= dt * this->particleAlphaDecay.y;
			(**it).alpha.z+= dt * this->particleAlphaDecay.z;
			(**it).alpha.w+= dt * this->particleAlphaDecay.w;
			
			//Next particle
			++it;
		}
		
		//4.Add generated particles
		this->timeAfterLastSpawning+=dt;
		
		int particleToSpawnCount=0;
		while ( this->timeAfterLastSpawning >= this->spawningRate)
		{
			this->timeAfterLastSpawning-=this->spawningRate;
			++particleToSpawnCount;
		}
		
		for(int i=0;i<particleToSpawnCount;++i)
		{
			Particle* p=this->particlePool.construct();
			particles.push_front(p);
			(*p).position=this->position;
		}

	}
	
	void ParticleSystem::draw(sf::RenderWindow& window)
	{
		std::list<Particle *>::iterator it;
		for (it=particles.begin(); it != particles.end(); ++it) 
		{
			(**it).draw(window, this->particleSprite);
		}
	}
	
} // engine namespace


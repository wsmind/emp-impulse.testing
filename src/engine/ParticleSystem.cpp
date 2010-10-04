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

#define UNLIMITED_PARTICLE -1

namespace engine {
	
ParticleSystem::ParticleSystem()
{
	this->actived=false;
	this->capacity=UNLIMITED_PARTICLE;
	this->remainingParticleCount=UNLIMITED_PARTICLE;
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
	
void ParticleSystem::setParticleAcceleration(math::Vec2 acceleration)
{
	this->particleAcceleration=acceleration;	
}
	
void ParticleSystem::setParticleAcceleration(f32 x, f32 y)
{
	this->particleAcceleration.x=x;	
	this->particleAcceleration.y=y;	
}
	
void ParticleSystem::setParticleRotationAcceleration(f32 rotAcceleration)
{
	this->ParticleRotationAcceleration=rotAcceleration;
}
	
void ParticleSystem::setParticleAlphaDecay(math::Vec4 alphaDecay)
{
	this->particleAlphaDecay=alphaDecay;
}
	
void ParticleSystem::setParticleAlphaDecay(f32 r, f32 g, f32 b, f32 a)
{
	this->particleAlphaDecay.x=r;
	this->particleAlphaDecay.y=g;
	this->particleAlphaDecay.z=b;
	this->particleAlphaDecay.w=a;
}
	
void ParticleSystem::setCapacity(i32 particleCount)
{
	this->capacity=particleCount;
		
	//unlimited particle spawn
	if (particleCount == UNLIMITED_PARTICLE)
	{
		this->remainingParticleCount=UNLIMITED_PARTICLE;
	//limited particle spawn
	}else {
		this->remainingParticleCount=particleCount;
	}
}
	
i32 ParticleSystem::getRemainingParticleCount()
{
	return this->remainingParticleCount;
}
	
i32 ParticleSystem::getFlyingParticleCount()
{
	return this->particles.size();
}
	
void ParticleSystem::setPosition(math::Vec2 position)
{
	this->position=position;
}
	
void ParticleSystem::setPosition(f32 x, f32 y)
{
	this->position.x=x;
	this->position.y=y;
}
	
void ParticleSystem::moveAllToAPosition(math::Vec2 position)
{
	math::Vec2 deplacement;
	deplacement=(position - this->position);
	deplacement.x = position.x - this->position.x;
	deplacement.y = position.y - this->position.y;
	
	//Change emitter position
	this->position=position;
	
	//Move each particle
	std::list<Particle *>::iterator it;
	for (it=particles.begin(); it != particles.end(); ++it) 
	{
		(**it).position+=deplacement;
	}
}

void ParticleSystem::moveAllToAPosition(f32 x, f32 y)
{
	math::Vec2 position(x,y);
	moveAllToAPosition(position);
}
	
void ParticleSystem::setSpawnRate(f32 rate)
{
	this->spawningRate=rate;	
}
	
void ParticleSystem::setParticleInitSpeed(math::Vec2 particleSpeed)
{
	this->particleInitSpeed=particleSpeed;	
}
	
void ParticleSystem::setParticleInitSpeed(f32 x, f32 y)
{
	this->particleInitSpeed.x=x;
	this->particleInitSpeed.y=y;	
}
	
void ParticleSystem::setParticleInitRotation(f32 rot)
{
	this->particleInitRotation=rot;
}
	
void ParticleSystem::setParticleInitRotationSpeed(f32 particleRotationSpeed)
{
	this->particleInitRotationSpeed=particleRotationSpeed;	
}
	
void ParticleSystem::registerListener(ParticleSystemListener *l)
{
	// check for previous existence
	if (std::find(this->listeners.begin(), this->listeners.end(), l) != this->listeners.end())
		return;
	
	// add the new spawner
	this->listeners.push_back(l);
}
	
void ParticleSystem::unregisterListener(ParticleSystemListener *l)
{
	// find the listener in the collection
	std::vector<ParticleSystemListener *>::iterator i;
	i = std::find(this->listeners.begin(), this->listeners.end(), l);
	
	// delete the found listener
	if (i != this->listeners.end())
	{
		this->listeners.erase(i);
	}	
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
			
			//Last Flying Particle Died
			//FIXME: It is the better moment ? Or move it after step 4 ?!
			if (it==particles.begin()) {
				fireLastFlyingParticleDied();
			}
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
		
	if (remainingParticleCount != 0)
	{
		int particleToSpawnCount=0;
		while ( this->timeAfterLastSpawning >= this->spawningRate)
		{
			this->timeAfterLastSpawning-=this->spawningRate;
			++particleToSpawnCount;
		}
		
		if (remainingParticleCount == UNLIMITED_PARTICLE )
		{
			generateParticle(particleToSpawnCount);
		}
		else if (particleToSpawnCount < (this->remainingParticleCount) ) 
		{
			generateParticle(particleToSpawnCount);
			this->remainingParticleCount -= particleToSpawnCount;
		}
		else
		{
			generateParticle(this->remainingParticleCount);
			this->remainingParticleCount=0;
			//Warn listener
			this->fireLastParticleSpawned();
		}
	}
}
	
void ParticleSystem::draw(sf::RenderWindow *window)
{
	std::list<Particle *>::iterator it;
	for (it=particles.begin(); it != particles.end(); ++it) 
	{
		(**it).draw(window, &this->particleSprite);
	}
}
	
void ParticleSystem::generateParticle(int count)
{
	for(int i=0;i<count;++i)
	{
		Particle* p=this->particlePool.construct(this->position);
			
		//Initialise the particle
		(*p).speed=this->particleInitSpeed;
		(*p).rotation=this->particleInitRotation;
		(*p).rotationSpeed=this->particleInitRotationSpeed;
		(*p).alpha=this->particleInitAlpha;
			
		//Add to list
		particles.push_front(p);
	}
}
	
void ParticleSystem::fireLastParticleSpawned()
{
	//Call listeners : lastParticleSpawned
	for (std::vector<ParticleSystemListener *>::iterator it = this->listeners.begin(); it != this->listeners.end(); ++it)
	{
		(*it)->lastParticleSpawned(this);
	}	
}
	
void ParticleSystem::fireLastFlyingParticleDied()
{
	//Call listeners : lastFlyingParticleDied
	for (std::vector<ParticleSystemListener *>::iterator it = this->listeners.begin(); it != this->listeners.end(); ++it)
	{
		(*it)->lastFlyingParticleDied(this);
	}		
}
	
} // engine namespace


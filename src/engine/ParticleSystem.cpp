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

bool ParticleSystem::isEmitterActive() const
{
	return this->actived;
}
	
void ParticleSystem::setEmitterActive(bool active)
{
	this->actived=active;
}
	
void ParticleSystem::setParticlesSprite(sf::Sprite *sprite)
{
	this->particleSprite=sprite;
}
	
void ParticleSystem::setParticlesLifeTime(f32 lifeTime)
{
	this->particleLifeTime=lifeTime;	
}
	
void ParticleSystem::setParticlesRotationFriction(f32 rotFriction)
{
	this->ParticleRotationFriction=rotFriction;
}
	
void ParticleSystem::setParticlesColorDecay(math::Vec4 colorDecay)
{
	this->particleColorDecay=colorDecay;
}
	
void ParticleSystem::setEmitterCapacity(i32 particleCount)
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
	
i32 ParticleSystem::getEmitterRemainingParticleCount()
{
	return this->remainingParticleCount;
}
	
i32 ParticleSystem::getFlyingParticleCount()
{
	return this->particles.size();
}

void ParticleSystem::setEmitterPosition(math::Vec2 position)
{
	this->position=position;
}

void ParticleSystem::moveAllToAPosition(math::Vec2 position)
{
	math::Vec2 move;
	move=(position - this->position);
	move.x = position.x - this->position.x;
	move.y = position.y - this->position.y;
	
	//Change emitter position
	this->position=position;
	
	//Move each particle
	std::list<Particle *>::iterator it;
	for (it=particles.begin(); it != particles.end(); ++it) 
	{
		(**it).position+=move;
	}
}

void ParticleSystem::translateAll(math::Vec2 vector)
{
	//Change emitter position
	this->position+=vector;

	//Move each particle
	std::list<Particle *>::iterator it;
	for (it=particles.begin(); it != particles.end(); ++it)
	{
		(**it).position+=vector;
	}
}
	
void ParticleSystem::setEmitterSpawnRate(f32 rate)
{
	this->spawningRate=rate;	
}
	
void ParticleSystem::setParticlesInitSpeed(math::Vec2 particlesSpeed)
{
	this->particleInitSpeed=particlesSpeed;
}
	
void ParticleSystem::setParticlesInitRotation(f32 rot)
{
	this->particleInitRotation=rot;
}
	
void ParticleSystem::setParticlesInitRotationSpeed(f32 particleRotationSpeed)
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
//1.Update particles age
//2.Remove dead particles
//3.Update pre-existent particles speed, position, color, rotation, etc
//4.Add generated particles
{
	std::list<Particle *>::iterator it;
	it=particles.begin();
	
	//For each particle
	while(it != particles.end())
	{
		//1.update particles age
		(**it).age+=dt;
			
		//2.Remove dead particles
		if ( (**it).age > this->particleLifeTime )
		{
			Particle* p=(*it);
			it=particles.erase(it);
			this->particlePool.destroy(p);
			
			//Last Flying Particle Died
			//FIXME: It is the good moment ? Or move it after step 4 ?!
			if (it==particles.begin()) {
				fireLastFlyingParticleDied();
			}
			continue;
		}
			
		//3.Update pre-existent particles speed, position, color, rotation, etc
		(**it).speed+= dt * forces;
		(**it).position+= dt * (**it).speed;
			
		(**it).rotationSpeed+= dt * this->ParticleRotationFriction;
		(**it).rotation+= dt * (**it).rotationSpeed;
			
		(**it).color.x+= dt * this->particleColorDecay.x;
		(**it).color.y+= dt * this->particleColorDecay.y;
		(**it).color.z+= dt * this->particleColorDecay.z;
		(**it).color.w+= dt * this->particleColorDecay.w;
			
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
			generateParticles(particleToSpawnCount);
		}
		else if (particleToSpawnCount < (this->remainingParticleCount) ) 
		{
			generateParticles(particleToSpawnCount);
			this->remainingParticleCount -= particleToSpawnCount;
		}
		else
		{
			generateParticles(this->remainingParticleCount);
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
		(**it).draw(window, this->particleSprite);
	}
}
	
void ParticleSystem::generateParticles(int count)
{
	for(int i=0;i<count;++i)
	{
		Particle* p=this->particlePool.construct(this->position);
			
		//Initialize the particle
		(*p).speed=this->particleInitSpeed;
		(*p).rotation=this->particleInitRotation;
		(*p).rotationSpeed=this->particleInitRotationSpeed;
		(*p).color=this->particleInitColor;
			
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


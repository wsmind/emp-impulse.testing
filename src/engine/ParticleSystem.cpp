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
#include <SFML/Graphics.hpp>

#include <ctime>
#include <cmath>

#define UNLIMITED_PARTICLE -1
#define UNLIMITED_PARTICLE_LIFE -1.0f

namespace engine {
	
ParticleSystem::ParticleSystem()
{
	this->actived=false;
	this->capacity=UNLIMITED_PARTICLE;
	this->remainingParticleCount=UNLIMITED_PARTICLE;
	this->timeAfterLastSpawning=0;
	this->timeBetweenTwoSpawns=1;

	this->particleInitRotation=0;
	this->particleInitRotationSpeed=0;
	this->particleInitSpeed=0;
	this->particleColorDecay=math::Vec4(0.f,0.f,0.f,0.f);

	this->position=math::Vec2();
	this->ParticleRotationFriction=0;
	this->particleLifeTime=UNLIMITED_PARTICLE_LIFE;

	this->particleSprite = new sf::Sprite();
	this->particleSpriteInitColor=math::Vec4(0.f,0.f,0.f,0.f);
}

ParticleSystem::~ParticleSystem()
{
	delete this->particleSprite;
}

bool ParticleSystem::isEmitterActive() const
{
	return this->actived;
}
	
void ParticleSystem::setEmitterActive(bool active)
{
	this->actived=active;
}
	
void ParticleSystem::setParticlesImage(sf::Image *particleImage)
{
	this->particleSprite->SetImage(*particleImage);

	sf::Color color=this->particleSprite->GetColor();
	this->particleSpriteInitColor.x=color.r;
	this->particleSpriteInitColor.y=color.g;
	this->particleSpriteInitColor.z=color.b;
	this->particleSpriteInitColor.w=color.a;
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
	this->timeBetweenTwoSpawns=1/rate;
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
	bool someParticleDied = false;
	std::list<Particle *>::iterator it;
	it=particles.begin();
	
	//For each particle
	while(it != particles.end())
	{
		Particle *particle = *it;

		//1.update particles age
		particle->age+=dt;
			
		//2.Remove dead particles
		if ( this->particleLifeTime != UNLIMITED_PARTICLE_LIFE )
		{
			if ( (particle->age) > (this->particleLifeTime) )
			{
				it=particles.erase(it);
				this->particlePool.destroy(particle);
				someParticleDied=true;
				continue;
			}
		}
			
		//3.Update pre-existent particles speed, position, color, rotation, etc
		particle->speed+= dt * forces;
		particle->position+= dt * particle->speed;
			
		particle->rotationSpeed+= dt * this->ParticleRotationFriction;
		particle->rotation+= dt * particle->rotationSpeed;
			
		particle->color.x+= dt * this->particleColorDecay.x;
		particle->color.y+= dt * this->particleColorDecay.y;
		particle->color.z+= dt * this->particleColorDecay.z;
		particle->color.w+= dt * this->particleColorDecay.w;
			
		//Next particle
		++it;
	}
		
	//4.Add generated particles
	this->timeAfterLastSpawning+=dt;
		
	if (remainingParticleCount != 0)
	{
		int particleToSpawnCount=0;
		while ( this->timeAfterLastSpawning >= this->timeBetweenTwoSpawns)
		{
			this->timeAfterLastSpawning-=this->timeBetweenTwoSpawns;
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

	//No more Flying Particle
	if ( someParticleDied && (particles.size() == 0) ) {
		fireLastFlyingParticleDied();
	}
}
	
void ParticleSystem::draw(sf::RenderWindow *window)
{
	std::list<Particle *>::iterator it;
	for (it=particles.begin(); it != particles.end(); ++it) 
	{
		(*it)->draw(window, this->particleSprite);
	}
}
	
void ParticleSystem::generateParticles(int count)
{
	for(int i=0;i<count;++i)
	{
		Particle* p=this->particlePool.construct(this->position);
			
		//Initialize the particle
		p->speed=this->particleInitSpeed;
		p->rotation=this->particleInitRotation;
		p->rotationSpeed=this->particleInitRotationSpeed;
		p->color=particleSpriteInitColor;
			
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


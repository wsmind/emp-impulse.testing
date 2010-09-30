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

#include <engine/Particle.hpp>

#include <ctime>
#include <cmath>

namespace engine {
	Particle::Particle()
	{
		this->position.x=0.f;
		this->position.y=0.f;
		
		this->speed.x=0.f;
		this->speed.y=0.f;
		
		this->rotation=0.f;
		this->rotationSpeed=0.f;
		
		this->age=0.f;
		
		this->alpha.x=0.f;
		this->alpha.y=0.f;
		this->alpha.z=0.f;
		this->alpha.w=0.f;
	}
	
	Particle::Particle(f32 x, f32 y)
	{
		this->position.x=x;
		this->position.y=y;
		
		this->speed.x=0.f;
		this->speed.y=0.f;
		
		this->rotation=0.f;
		this->rotationSpeed=0.f;
		
		this->age=0.f;
		
		this->alpha.x=0.f;
		this->alpha.y=0.f;
		this->alpha.z=0.f;
		this->alpha.w=0.f;
	}
	
	void Particle::draw(sf::RenderWindow& window, sf::Sprite& sprite) const
	{
		sprite.SetPosition(this->position.x,this->position.y);
		sprite.SetRotation(this->rotation);
		window.Draw(sprite);
	}

	std::ostream& operator <<(std::ostream& out, const Particle& p)
	{
		return out;
	}
} // engine namespace


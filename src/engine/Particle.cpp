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
#include <SFML/Graphics.hpp>

namespace engine {

Particle::Particle(math::Vec2 position):position(position),speed(),color(0.f,0.f,0.f,1.f),rotation(0.f),rotationSpeed(0.f),age(0.f)
{
}
	
void Particle::draw(sf::RenderWindow *window, sf::Sprite *sprite) const
{
	sprite->SetPosition(this->position.x,this->position.y);
	sprite->SetRotation(this->rotation);
	sprite->SetColor(sf::Color(color.x, color.y, color.z, color.w));
	window->Draw(*sprite);
}

} // engine namespace


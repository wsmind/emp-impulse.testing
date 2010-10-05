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

#include <scene/Scene.hpp>

#include <scene/InputState.hpp>
#include <SFML/Graphics.hpp>

namespace scene {

Scene::Scene()
{
	// window size temporarily hard-coded
	this->window = new sf::RenderWindow(sf::VideoMode(1024, 768), "Impulse");
}

Scene::~Scene()
{
	delete this->window;
}

bool Scene::pollEvents()
{
	// process pending events
	sf::Event event;
	while (this->window->GetEvent(event))
	{
		if (event.Type == sf::Event::Closed)
			return true;
	}
	
	// update input state (temporary hard-wired input mapping)
	const sf::Input &input = this->window->GetInput();
	this->inputState->left = input.IsKeyDown(sf::Key::Left);
	this->inputState->right = input.IsKeyDown(sf::Key::Right);
	this->inputState->jump = input.IsKeyDown(sf::Key::Up);
	this->inputState->action = input.IsKeyDown(sf::Key::Space);
	
	return false;
}

const InputState *Scene::getInputState() const
{
	return this->inputState;
}

void Scene::render()
{
	// clear the screen
	this->window->Clear();
	
	// swap back and front buffers
	this->window->Display();
}

} // scene namespace


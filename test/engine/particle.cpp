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

#include <SFML/Graphics.hpp>
#include <engine/ParticleSystem.hpp>
#include <engine/ParticleSystemListener.hpp>
#include <sstream>

#include <math/Vec2.hpp>

class psListener: public engine::ParticleSystemListener
{

	public:
		psListener(){};

		void lastParticleSpawned (engine::ParticleSystem *particleSystem)
		{
			std::cout << "Last Particle Spawned." << std::endl;
		}

		void lastFlyingParticleDied (engine::ParticleSystem *particleSystem)
		{
			std::cout << "Last Flying Particle Died." << std::endl;
		}
};

int main()
{
    // Create the main rendering window
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML Graphics");
	
	// Load the sprite image from a file
	sf::Image particleImage;
	if (!particleImage.LoadFromFile("particle.png"))
	{
		std::cout << "Error loading the particle." << std::endl;
	}
	
	//Create a particle system
	engine::ParticleSystem particleSystem;
	particleSystem.setEmitterCapacity(1000);
	particleSystem.setParticlesImage(&particleImage);
	particleSystem.setEmitterPosition(math::Vec2(100,100));
	particleSystem.setEmitterSpawnRate(3.f);
	particleSystem.setParticlesLifeTime(12);
	particleSystem.setParticlesInitSpeed(math::Vec2(30.f,-10.f));
	particleSystem.setParticlesColorDecay(math::Vec4(0.f,0.f,0.f,-20.f));
	particleSystem.setEmitterActive(true);
	
	psListener psl;
	particleSystem.registerListener(&psl);

	math::Vec2 totalForces(0.f,9.8f);
	
	sf::String TextFps;
	TextFps.SetStyle(sf::String::Bold | sf::String::Italic | sf::String::Underlined);
	TextFps.SetStyle(sf::String::Regular);
	TextFps.SetColor(sf::Color(128, 0, 0));
	TextFps.Move(10.f, 0.f);
	TextFps.SetText("");

	float fps=0.f;
	float deltaFpsDisplay=0.f;

	// Start game loop
	while (window.IsOpened())
	{
		float elapsedTime = window.GetFrameTime();
		
		// Process FPS count
		fps = 1 / elapsedTime;
		deltaFpsDisplay+=elapsedTime;

		// Change FPS text ~every second
		if (deltaFpsDisplay >= 1.f)
		{
			fps/=deltaFpsDisplay;
			std::ostringstream oss;
			oss << fps << " FPS";
			TextFps.SetText(oss.str());

			deltaFpsDisplay=0;
			fps=0;
		}

		// Process events
		sf::Event event;
		while (window.GetEvent(event))
		{
			// Close window : exit
			if (event.Type == sf::Event::Closed)
			{
				window.Close();
			}
		}
		
		// Update particle system engine
		particleSystem.update(elapsedTime,totalForces);
		
		// Clear the screen (fill it with white color)
		window.Clear(sf::Color(255, 255, 255));
		
		// Draw particles
		particleSystem.draw(&window);
		// Draw FPS text
		window.Draw(TextFps);
		
		// Display window contents on screen
		window.Display();
	}
	
	return EXIT_SUCCESS;
}

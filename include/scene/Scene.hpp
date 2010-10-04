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

#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <common.hpp>

IMPULSE_FORWARD_DECLARE1(scene, InputState);
IMPULSE_FORWARD_DECLARE1(sf, RenderWindow);

namespace scene {

/**
 * \class Scene
 * \author Remi Papillie
 *
 * \brief Root of the scene namespace package
 *
 * The scene hides most of the tedious technical things from the engine to allow
 * gameplay classes to focus on game-related things. For instance, the scene
 * hides resource management, window creation and input handling. It also
 * alleviates the need for drawing each object separately.
 *
 * Thus, the interface exposed by the Scene class and other classes from the
 * same package relates directly to gameplay needs.
 */
class Scene
{
	public:
		/**
		 * \brief Constructor
		 *
		 * Creates the window.
		 */
		Scene();
		
		/**
		 * \brief Destructor
		 *
		 * Force the window destruction, if it was not closed before
		 */
		~Scene();
		
		/**
		 * \brief Checks for events received by the game window
		 * \return true if the window was closed through the window manager interface
		 *
		 * After reading events, this methods updates the current input state.
		 */
		bool pollEvents();
		
		/**
		 * \brief Retrieve current mapped input state
		 * 
		 * The input state is updated every time pollEvents() is called.
		 */
		const InputState *getInputState() const;
		
		/**
		 * \brief Redraw window contents
		 *
		 * Takes everything which can be rendered (sprites, sounds, ...) and
		 * put it on the screen/speakers.
		 */
		void render();
	
	private:
		/// SFML window
		sf::RenderWindow *window;
		
		/// current input state
		InputState *inputState;
};

} // scene namespace

#endif // __SCENE_HPP__


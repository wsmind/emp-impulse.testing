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

#ifndef __INPUTSTATE_HPP__
#define __INPUTSTATE_HPP__

#include <common.hpp>

namespace scene {

/**
 * \class InputState
 * \author Remi Papillie
 *
 * \brief Game-domain input representation
 *
 * Objects of this class are managed by the Scene class, which maps user input
 * (keyboard, mouse) to game commands (e.g jump, walk right).
 *
 * Currently, this class only exposes raw game input, but it could evolve to
 * handle input state changes (i.e key pressed, released, etc.)
 */
class InputState
{
	public:
		bool left;
		bool right;
		bool jump;
		bool action;
};

} // scene namespace

#endif // __INPUTSTATE_HPP__


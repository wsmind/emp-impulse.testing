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

#ifndef __COLLISIONSHAPE_HPP__
#define __COLLISIONSHAPE_HPP__

#include <common.hpp>
#include <vector>
#include <math/Vec2.hpp>
#include <math/Mat33.hpp>
#include <engine/Contact.hpp>

namespace engine {

class CollisionShape
{
	public:
		CollisionShape(std::vector<math::Vec2> points);
		~CollisionShape();
		
		void setPosition(math::Vec2 newPosition);
		void setRotation(float newRotation);
		void setScale(math::Vec2 newScale);
		
		math::Vec2 getPosition() const;
		f32 getRotation() const;
		math::Vec2 getScale() const;
		
		bool detectCollision(CollisionShape *polygon, Contact *contact);
		//bool isInside(math::Vec2 point, math::Vec2 *normal, float *distance);
		
	private:
		void rebuildTransform();
		void projectPolygon(math::Vec2 normal, math::Vec2 point, CollisionShape *polygon, f32 *max, f32 *min);
		
		std::vector<math::Vec2> points;
		
		math::Vec2 position;
		float rotation;
		math::Vec2 scale;
		
		math::Mat33 transform;
};


} // engine namespace


#endif // __COLLISIONSHAPE_HPP__

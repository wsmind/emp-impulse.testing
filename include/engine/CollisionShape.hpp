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

IMPULSE_FORWARD_DECLARE1(engine, Contact)

namespace engine {

/**
* \class CollisionShape
* \author Elen Le Par
*
* \brief The CollisionShape class defines a polygon convex.
*
* The polygon is defined by the list of his vertices in clockwise order.
*
* A polygon can detect the collision with another polygon and compute the data
* of the collision.
*
* The detection collision algorithm used is explained here:
*  http://www.codeproject.com/KB/GDI-plus/PolygonCollision.aspx
*/
class IMPULSE_ENGINE_EXPORT CollisionShape
{
	public:
		/**
		* \brief Constructs a CollisionShape.
		* \param points list of vertices.
		*/
		CollisionShape(std::vector<math::Vec2> points);
		
		/**
		* \brief Sets a new position.
		* \param newPosition new position.
		*/
		void setPosition(math::Vec2 newPosition);
		
		/**
		* \brief Sets a new rotation.
		* \param newRotation new rotation in degree.
		*/
		void setRotation(float newRotation);
		
		/**
		* \brief Sets a new scale.
		* \param newScale new scale.
		*/
		void setScale(math::Vec2 newScale);
		
		/**
		* \brief Gets the current position.
		* \return current position.
		*/
		math::Vec2 getPosition() const;
		
		/**
		* \brief Gets the current rotation.
		* \return current rotation.
		*/
		f32 getRotation() const;
		
		/**
		* \brief Gets the current scale.
		* \return current scale.
		*/
		math::Vec2 getScale() const;
		
		/**
		* \brief Test a collision against another shape.
		* \param polygon second polygon.
		* \param contact contact data of the collision.
		* \return true if there is collision.
		*
		* The result normal is oriented from this to polygon.
		* The contact parameter is not obligatory.
		*/
		bool detectCollision(CollisionShape *polygon, Contact *contact = NULL);
		
	private:
		/**
		* \brief Computes the transformation matrix.
		*/
		void rebuildTransform();
		
		/**
		* \brief Projects each point of this on a normal.
		* \param direction direction on which this will be projected.
		* \param point point of the line on which the polygon is being projected.
		* \param[out] max max of the projection result.
		* \param[out] min min of the projection result.
		*/
		void projectPolygon(math::Vec2 direction, math::Vec2 point, f32 *min, f32 *max);
		
		/**
		* \brief Points list.
		*/
		std::vector<math::Vec2> points;
		
		/**
		* \brief Position of the polygon.
		*/
		math::Vec2 position;
		/**
		* \brief Rotation of the polygon in degree.
		*/
		float rotation;
		/**
		* \brief Scale of the polygon.
		*/
		math::Vec2 scale;
		
		/**
		* \brief Transformation matrix.
		*/
		math::Mat33 transform;
};


} // engine namespace


#endif // __COLLISIONSHAPE_HPP__

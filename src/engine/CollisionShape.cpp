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

#include <engine/CollisionShape.hpp>
#include <cmath>
#include <iostream>

using namespace math;

namespace engine {

CollisionShape::CollisionShape(std::vector<Vec2> points)
{
	this->points = points;
	
	this->position = Vec2(0.0f, 0.0f);
	this->rotation = 0.0f;
	this->scale = Vec2(1.0f, 1.0f);
	
	this->rebuildTransform();
}

CollisionShape::~CollisionShape()
{
}

void CollisionShape::setPosition(Vec2 newPosition)
{
	this->position = newPosition;
	this->rebuildTransform();
}

void CollisionShape::setRotation(float newRotation)
{
	this->rotation = newRotation;
	this->rebuildTransform();
}

void CollisionShape::setScale(Vec2 newScale)
{
	this->scale = newScale;
	this->rebuildTransform();
}

math::Vec2 CollisionShape::getPosition() const
{
	return this->position;
}

f32 CollisionShape::getRotation() const
{
	return this->rotation;
}

math::Vec2 CollisionShape::getScale() const
{
	return this->scale;
}

u32 CollisionShape::detectCollision(CollisionShape *polygon, Contact *contact)
{
	Vec2 maxNormal;
	Vec2 maxPoint;
	float maxDistance = -1.0f;
	int intersectionCount = 0;
	
	Vec2 normal;
	float distance;
	Vec2 point;
	
	// for each point of polygon
	Mat33 polygonLocalToThisLocal = this->transform.inverse() * polygon->transform;
	Mat33 normalMatrixThis = this->transform;
	normalMatrixThis.v[2] = 0.0f;
	normalMatrixThis.v[5] = 0.0f;
	for ( unsigned int i = 0 ; i < polygon->points.size(); i++)
	{
		point = polygonLocalToThisLocal * polygon->points[i];
		if (this->isInside(point, &normal, &distance))
		{
			intersectionCount++;
			if (distance > maxDistance)
			{
				maxNormal = normalMatrixThis * normal;
				float norm = maxNormal.norm();
				maxPoint = this->transform * point;
				maxDistance = distance * norm;
				maxNormal = maxNormal / norm;
			}
		}
	}
	
	// for each point of this
	Mat33 thisLocalToPolygonLocal = polygon->transform.inverse() * this->transform;
	Mat33 normalMatrixPolygon = polygon->transform;
	normalMatrixPolygon.v[2] = 0.0f;
	normalMatrixPolygon.v[5] = 0.0f;
	for ( unsigned int i = 0 ; i < this->points.size(); i++)
	{
		point = thisLocalToPolygonLocal * this->points[i];
		if(polygon->isInside(point, &normal, &distance))
		{
			intersectionCount++;
			if (distance > maxDistance)
			{
				maxNormal = normalMatrixPolygon * -normal;
				float norm = maxNormal.norm();
				maxPoint = polygon->transform * point;
				maxDistance = distance * norm;
				maxNormal = maxNormal / norm;
			}
		}
	}
	
	if (intersectionCount > 0)
	{
		contact->contactPoint = maxPoint;
		contact->normal = maxNormal;
		contact->interpenetration = maxDistance;
		std::cout << "Point: " << maxPoint << std::endl;
		std::cout << "Normal: " << maxNormal << std::endl;
	}
	
	return intersectionCount;
}

bool CollisionShape::isInside(Vec2 point, Vec2 *normal, float *distance)
{
	*normal = Vec2(0.0f, 0.0f);
	*distance = INFINITY;
	
	for(unsigned int i = 0; i < this->points.size(); i++)
	{
		Vec2 start = this->points[i];
		Vec2 end = this->points[(i + 1) % this->points.size()];
		
		Vec2 edge = end - start;
		Vec2 relPoint = point - start;
		
		if (edge.area(relPoint) < 0.0f)
			return false;
		
		// Compute the normal
		Vec2 n = Vec2(edge.y, -edge.x).normalize();
		//std::cout << "n: " << n << std::endl;
		
		// compute distance between the point and the edge
		float d = fabs(relPoint.dot(n));
		//std::cout << "d: " << d << std::endl;
		if (d < *distance)
		{
			*distance = d;
			*normal = n;
		}
	}
	return true;
}

void CollisionShape::rebuildTransform()
{
	Mat33 translation;
	translation.v[2] = this->position.x;
	translation.v[5] = this->position.y;
	
	Mat33 rotation;
	float rcos = cosf(this->rotation * M_PI / 180.0f);
	float rsin = sinf(this->rotation * M_PI / 180.0f);
	rotation.v[0] = rcos;
	rotation.v[1] = rsin;
	rotation.v[3] = -rsin;
	rotation.v[4] = rcos;
	
	Mat33 scale;
	scale.v[0] = this->scale.x;
	scale.v[4] = this->scale.y;
	
	this->transform = translation * rotation * scale;
}

} //engine namespace

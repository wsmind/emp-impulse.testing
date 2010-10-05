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

bool CollisionShape::detectCollision(CollisionShape *polygon, Contact *contact)
{
	/*Vec2 maxNormal;
	Vec2 maxPoint;
	float maxDistance = -1.0f;
	int intersectionCount = 0;
	
	Vec2 normal;
	float distance;
	Vec2 point;*/
	
	/*Mat33 polygonLocalToThisLocal = this->transform.inverse() * polygon->transform;
	Mat33 normalMatrixThis = this->transform;
	normalMatrixThis.v[2] = 0.0f;
	normalMatrixThis.v[5] = 0.0f;*/
	
	
	f32 maxDistanceThis;
	f32 minDistanceThis;
	f32 maxDistancePolygon;
	f32 minDistancePolygon;
	
	f32 overlap;
	f32 minOverlap = INFINITY;
	
	// for each edge of this
	for ( u32 i = 0; i < this->points.size(); i++)
	{
		std::cout << "New edge !" << std::endl;
		
		// Compute the edge
		Vec2 start = this->points[i];
		Vec2 end = this->points[(i + 1) % this->points.size()];
		Vec2 edge = end - start;
		
		// Compute the normal line
		Vec2 normal = Vec2(edge.y, -edge.x).normalize();
		
		projectPolygon(normal, start, this, &maxDistanceThis, &minDistanceThis);
		projectPolygon(normal, start, polygon, &maxDistancePolygon, &minDistancePolygon);
		std::cout << "MaxThis: " << maxDistanceThis << std::endl;
		std::cout << "MinThis: " << minDistanceThis << std::endl;
		std::cout << "MaxPolygon: " << maxDistancePolygon << std::endl;
		std::cout << "MinPolygon: " << minDistancePolygon << std::endl;
		
		// Test if there is collision
		if ((minDistanceThis > maxDistancePolygon) || (maxDistanceThis < minDistancePolygon))
			return false;
		
		// Compute the overlap
		if (maxDistancePolygon > minDistanceThis)
			overlap = maxDistancePolygon - minDistanceThis;
		else
			overlap = maxDistanceThis - minDistancePolygon;
		
		// Find the right edge
		if (overlap < minOverlap)
		{
			minOverlap = overlap;
			contact->normal = normal;
			contact->interpenetration = minOverlap;
		}
		
	}
	
	// for each edge of polygon
	for ( u32 i = 0; i < polygon->points.size(); i++)
	{
		std::cout << "New edge !" << std::endl;
		
		// Compute the edge
		Vec2 start = polygon->points[i];
		Vec2 end = polygon->points[(i + 1) % polygon->points.size()];
		Vec2 edge = end - start;
		
		// Compute the normal line
		Vec2 normal = Vec2(edge.y, -edge.x).normalize();
		
		projectPolygon(normal, start, this, &maxDistanceThis, &minDistanceThis);
		projectPolygon(normal, start, polygon, &maxDistancePolygon, &minDistancePolygon);
		std::cout << "MaxThis: " << maxDistanceThis << std::endl;
		std::cout << "MinThis: " << minDistanceThis << std::endl;
		std::cout << "MaxPolygon: " << maxDistancePolygon << std::endl;
		std::cout << "MinPolygon: " << minDistancePolygon << std::endl;
		
		// Test if there is collision
		if ((minDistanceThis > maxDistancePolygon) || (maxDistanceThis < minDistancePolygon))
			return false;
		
		// Compute the overlap
		if (maxDistancePolygon > minDistanceThis)
			overlap = maxDistancePolygon - minDistanceThis;
		else
			overlap = maxDistanceThis - minDistancePolygon;
		
		// Find the right edge
		if (overlap < minOverlap)
		{
			minOverlap = overlap;
			contact->normal = normal;
			contact->interpenetration = minOverlap;
		}
	}
	
	
	// for each point of this
	/*Mat33 thisLocalToPolygonLocal = polygon->transform.inverse() * this->transform;
	Mat33 normalMatrixPolygon = polygon->transform;
	normalMatrixPolygon.v[2] = 0.0f;
	normalMatrixPolygon.v[5] = 0.0f;*/
	/*for ( unsigned int i = 0 ; i < this->points.size(); i++)
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
	}*/
	
	
	return true;
}

/*bool CollisionShape::isInside(Vec2 point, Vec2 *normal, float *distance)
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
}*/

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

void CollisionShape::projectPolygon(math::Vec2 normal, math::Vec2 point, CollisionShape *polygon, f32 *max, f32 *min)
{	
	// Initialize max and min
	*max = -INFINITY;
	*min = INFINITY;
	
	// Compute projection for each point of polygon
	for ( u32 i = 0; i < polygon->points.size(); i++)
	{
		Vec2 relVector = polygon->points[i] - point;
		f32 distance = relVector.dot(normal);
		
		if (distance > *max)
			*max = distance;
		
		if (distance < *min)
			*min = distance;
	}

}

} //engine namespace

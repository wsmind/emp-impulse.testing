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

#include <engine/ParticleBin.hpp>

#include <ctime>
#include <cmath>

#define DEFAULT_SIZE 500u
#define MAX_SIZE_BEFORE_INCREASE 10000u //Maximal size tolered for an increase size process
#define INCREASE_COEF 2u

namespace engine {
	ParticleBin::ParticleBin()
	{
		this->count=0;
		this->size=DEFAULT_SIZE;
		this->bin = new Particle*[DEFAULT_SIZE];
	}
	
	ParticleBin::ParticleBin(u32 size)
	{
		this->count=0;
		this->size=size;
		this->bin = new Particle*[this->size];
	}

	ParticleBin::~ParticleBin()
	{
		//Deleting Particle in the bin
		for (u32 i=0; i<(this->count); i++) {
			delete this->bin[i];
		}
		
		//Deleting the bin itself
		delete [] this->bin;
	}
	
	Particle* ParticleBin::obtain()
	{
		//No recycled particle, creating one
		if (this->count == 0)
		{
			return new Particle();
		//Retrieve a recycle particle	
		}else{
			this->count--;
			
			return this->bin[count];
		}

	}
	
	void ParticleBin::collect(Particle* p)
	{
		if ( (this->count == this->size) && (this->size < MAX_SIZE_BEFORE_INCREASE)) {
			//Bigger bin needed
			this->size *= INCREASE_COEF;
			Particle** newBin = new Particle*[this->size];
			
			for (u32 i=0; i<(this->count); i++) {
				newBin[i]=this->bin[i];
			}
			
			delete [] this->bin;
			this->bin = newBin;
		}else{
			this->bin[count]=p;
			this->count++;
		}
	}
	

	
} // engine namespace


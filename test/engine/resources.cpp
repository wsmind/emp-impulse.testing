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

#include <engine/ResourceManager.hpp>
#include <peel.hpp>

using namespace engine;

int main()
{
	//images
	ResourceManager *rm = new ResourceManager;
	
	// normal use
	sf::Image *image = rm->loadImage("water.png");
	sf::Image *image2 = rm->loadImage("water.png");
	CHECK(image == image2);
	
	sf::Image *image3 = rm->loadImage("wave.png");
	CHECK(image != image3);
	
	rm->releaseImage("water.png");
	rm->releaseImage("water.png");
	rm->releaseImage("wave.png");
	
	// wrong file
	sf::Image *image4 = rm->loadImage("doesnotexist.png"); // will print a warning
	CHECK(image4 == NULL);
	rm->releaseImage("doesnotexist.png");
	
	// double release
	rm->releaseImage("neverloaded.png"); // will print another warning
	
	// summary of non-released resources
	rm->loadImage("water.png");
	rm->loadImage("water.png");
	rm->loadImage("wave.png");
	
	std::cout << "Resources still in use at the end:" << std::endl;
	rm->printLoadedResources();
	
	delete rm;
	
	// animationDatas
	ResourceManager *rm2 = new ResourceManager;
	
	// normal use
	AnimationData *animationData = rm2->loadAnimationData("resources/bounce.data");
	AnimationData *animationData2 = rm2->loadAnimationData("resources/bounce.data");
	CHECK(animationData == animationData2);
	
	AnimationData *animationData3 = rm2->loadAnimationData("resources/bounce2.data");
	CHECK(animationData != animationData3);
	
	rm2->releaseAnimationData("resources/bounce.data");
	rm2->releaseAnimationData("resources/bounce.data");
	rm2->releaseAnimationData("resources/bounce2.data");
	
	// wrong file
	AnimationData *animationData4 = rm2->loadAnimationData("doesnotexist.data");// will print a warning
	CHECK(animationData4 == NULL);
	rm->releaseAnimationData("doesnotexist.data");
	
	// double release
	rm->releaseAnimationData("neverloaded.data"); // will print another warning
	
	// summary of non-released resources
	rm2->loadAnimationData("resources/bounce.data");
	rm2->loadAnimationData("resources/bounce.data");
	rm2->loadAnimationData("resources/bounce2.data");
	
	std::cout << "Resources still in use at the end:" << std::endl;
	rm->printLoadedResources();

	delete rm2;
	
	return 0;
}


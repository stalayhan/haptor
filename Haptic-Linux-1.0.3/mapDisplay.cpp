/*
 * mapDisplay.cpp
 *
 *  Created on: 19 Kas 2015
 *      Author: DMK
 */

#include "mapDisplay.h"

mapDisplay::mapDisplay(IrrlichtDevice *device) {
	this->device = device;
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	mapMesh = smgr->getMesh("objects/insideMap.obj");

	if (!mapMesh)
	   device->drop();

	mapNode = smgr->addAnimatedMeshSceneNode( mapMesh );

	if (mapNode){
	  mapNode->setMaterialFlag(EMF_LIGHTING, true);
	  mapNode->setMaterialTexture( 0, driver->getTexture("objects/textures/insideMap.png"));
	}

	// give map initial position
	mapNode->setPosition(vector3df(0,0,0));
	mapNode->setScale(vector3df(23,0,23));
	mapNode ->setName("map");
	// add map markers
	addMarkerButtonsInside();
	addMarkerButtonsOutside();
	isInside = true;
	for (unsigned int i = 0; i < outsideButtons.size(); ++i)
		outsideButtons[i].setVisible(false);

}

void mapDisplay::addMarkerButtonsInside(){
	// Z23
	insideButtons.push_back(markerButton(vector3df(100,5,-62), device, 6));
	// Z20 - Circuit Lab
	insideButtons.push_back(markerButton(vector3df(100,5,-20), device, 5));
	// Z16 - Women WC
	//insideButtons.push_back(markerButton(vector3df(85,5,10), device, 10));
	// Exit 1
	//insideButtons.push_back(markerButton(vector3df(120,5,5), device, 11));
	// Z12 - Micro Lab
	insideButtons.push_back(markerButton(vector3df(100,5,33), device, 4));
	// Z10
	insideButtons.push_back(markerButton(vector3df(105,5,57), device, 3));
	// Z05
	insideButtons.push_back(markerButton(vector3df(100,5,80), device, 3));
	// Z04
	insideButtons.push_back(markerButton(vector3df(55,5,80), device, 2));
	// Exit Back
	insideButtons.push_back(markerButton(vector3df(15,5,95), device, 1));
	// Z02
	insideButtons.push_back(markerButton(vector3df(0,5,80), device, 1));

	// Z01 - Robotic Lab .... Z06 - talayhan
	insideButtons.push_back(markerButton(vector3df(-50,7,80), device, 0));
	// Z06
	insideButtons.push_back(markerButton(vector3df(-55,5,58), device, 10));
	// Z11
	insideButtons.push_back(markerButton(vector3df(-45,5,33), device, 10));
	// Z19 - Computer Lab
	insideButtons.push_back(markerButton(vector3df(-47,5,-20), device, 9));
	// Z21 - Cafeteria
	insideButtons.push_back(markerButton(vector3df(-45,5,-60), device, 8));
	// Main Exit
	insideButtons.push_back(markerButton(vector3df(15,5,-95), device, 7));
}

void mapDisplay::addMarkerButtonsOutside(){
	// Computer Engineering
	outsideButtons.push_back(markerButton(vector3df(110,5,110), device, 1));
	// Library
	outsideButtons.push_back(markerButton(vector3df(30,5,15), device, 12));
	// Molecular Biology
	outsideButtons.push_back(markerButton(vector3df(-25,5,-20), device, 14));
	// Chemical Engineering
	outsideButtons.push_back(markerButton(vector3df(-10,5,15), device, 14));
	// Station
	outsideButtons.push_back(markerButton(vector3df(52,5,-160), device, 19));
}

vector<markerButton>& mapDisplay::getMarkerButtons(){
	if(isInside)
		return insideButtons;
	else
		return outsideButtons;
}
vector<markerButton>& mapDisplay::getMarkerButtonsOtherMap(){
	if(!isInside)
		return insideButtons;
	else
		return outsideButtons;
}

void mapDisplay::changeToOutside(int clickedMarkerIndex){
	mapNode->setMaterialTexture( 0, driver->getTexture("objects/textures/outsideMapOrg.png"));

	if(clickedMarkerIndex != -1){
		for (unsigned int i = 0; i < insideButtons.size(); ++i)
			insideButtons[i].setVisible(false);
		for (unsigned int i = 0; i < outsideButtons.size(); ++i)
			if(outsideButtons[i].isSelected == true)
				outsideButtons[i].setVisible(true);
	}
	else{
		for (unsigned int i = 0; i < outsideButtons.size(); ++i)
			outsideButtons[i].setVisible(true);

		for (unsigned int i = 0; i < insideButtons.size(); ++i)
			insideButtons[i].setVisible(false);
	}

	isInside = false;

}
void mapDisplay::changeToInside(int clickedMarkerIndex){
	mapNode->setMaterialTexture( 0, driver->getTexture("objects/textures/insideMap.png"));

	if(clickedMarkerIndex != -1){
		for (unsigned int i = 0; i < outsideButtons.size(); ++i)
			outsideButtons[i].setVisible(false);

		for (unsigned int i = 0; i < insideButtons.size(); ++i)
			if(insideButtons[i].isSelected == true)
				insideButtons[i].setVisible(true);
	}
	else{
		for (unsigned int i = 0; i < outsideButtons.size(); ++i)
			outsideButtons[i].setVisible(false);

		for (unsigned int i = 0; i < insideButtons.size(); ++i)
			insideButtons[i].setVisible(true);
	}
	isInside = true;
}

mapDisplay::~mapDisplay() {
	// TODO Auto-generated destructor stub
}



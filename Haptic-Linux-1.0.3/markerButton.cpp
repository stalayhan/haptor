/*
 * markerButton.cpp
 *
 *  Created on: 26 Kas 2015
 *      Author: DMK
 */

#include "markerButton.h"
#include <iostream>
using namespace std;

markerButton::markerButton(vector3df position, IrrlichtDevice *device, int nodeId) {
	id = nodeId;
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	markerMesh = smgr->getMesh("objects/markerButton.obj");
	isSelected = false;

	if (!markerMesh)
	   device->drop();

	markerNode = smgr->addAnimatedMeshSceneNode(markerMesh);
	selector = smgr->createTriangleSelector(markerMesh, markerNode);
	markerNode->setTriangleSelector(selector);


	if (markerNode)
	  {
		  markerNode->setMaterialFlag(EMF_LIGHTING, true);
		  markerNode->setMaterialTexture( 0, driver->getTexture("objects/textures/markerButton.png"));
	  }

	// give marker its initial position and scale
	markerNode->setPosition(position);
	markerNode->setScale(vector3df(6,0,6));
	// To enable click
	sph = device->getSceneManager()->addSphereSceneNode(4,10,0,-1, position);
}

ISceneNode* markerButton::getMarkerNode(){
	return markerNode;
}

ITriangleSelector* markerButton::getSelector(){
	return selector;
}

void markerButton::setVisible(bool isVisible){
	markerNode->setVisible(isVisible);
	sph->setVisible(isVisible);
}

ISceneNode* markerButton::getSph(){
	return sph;
}

void markerButton::scaleSmaller(){
	markerNode->setScale(vector3df(5,0,5));
}

void markerButton::resetScale(){
	markerNode->setScale(vector3df(6,0,6));
}

markerButton::~markerButton() {
	// TODO Auto-generated destructor stub
}
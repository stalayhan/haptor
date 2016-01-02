/*
 * user.cpp
 *
 *  Created on: 12 Kas 2015
 *      Author: DMK
 */

#include "userDisplay.h"

userDisplay::userDisplay(vector3df position, IrrlichtDevice *device, bool isInside) {

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	userMesh = smgr->getMesh("objects/userModel.obj");
	this->isInside = isInside;

	if (!userMesh)
	   device->drop();

	userNode = smgr->addAnimatedMeshSceneNode( userMesh );

	if (userNode)
	  {
		  userNode->setMaterialFlag(EMF_LIGHTING, true);
		  userNode->setMaterialTexture( 0, driver->getTexture("objects/textures/user.png"));
	  }

	// give user initial coordinate and position
	this->position = position;
	this->scale = vector3df(15,0,15);
	this->rotation = vector3df(0,45,0);

	userNode->setPosition(position);
	userNode->setScale(scale);
	userNode->setRotation(rotation);

	if(!isInside)
		setVisible(false);
}
void userDisplay::setPosition(vector3df position){
	this->position = position;
	userNode->setPosition(position);
}

void userDisplay::rotateUser(int degree){
	rotation.Y = degree;
	userNode->setRotation(rotation);
}

void userDisplay::setVisible(bool isVisible){
	userNode->setVisible(isVisible);
}

userDisplay::~userDisplay() {
	// TODO Auto-generated destructor stub
}

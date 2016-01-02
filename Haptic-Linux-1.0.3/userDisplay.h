/*
 * user.h
 *
 *  Created on: 12 Kas 2015
 *      Author: DMK
 */

#ifndef USERDISPLAY_H_
#define USERDISPLAY_H_

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class userDisplay {
public:
	userDisplay(vector3df position, IrrlichtDevice *device, bool isInside);
	void setPosition(vector3df position);
	void rotateUser(int degree);
	void setVisible(bool isVisible);
	virtual ~userDisplay();
	ISceneNode* userNode;
	// VARIABLES
	bool isInside;
private:
	vector3df position;
	vector3df scale;
	vector3df rotation;
	ISceneManager* smgr;
	IVideoDriver* driver;
	IAnimatedMesh* userMesh;
};

#endif /* USERDISPLAY_H_ */


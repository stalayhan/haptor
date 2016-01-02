/*
 * popUp.h
 *
 *  Created on: 23 Ara 2015
 *      Author: Lenovo
 */

#ifndef POPUP_H_
#define POPUP_H_

#include <dimension2d.h>
#include <EDriverTypes.h>
#include <IGUIEnvironment.h>
#include <IrrlichtDevice.h>
#include <IReferenceCounted.h>
#include <ISceneManager.h>
#include <IVideoDriver.h>
#include <irrlicht.h>
#include <irrTypes.h>
#include <SColor.h>
#include <vector3d.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace std;
using namespace gui;

class popUp {
public:
	popUp();
	void closePopUp();
	void showPopUp(IrrlichtDevice *device);
	virtual ~popUp();
private:
	void customizeWindow();
	IGUIWindow * window;
	IGUIEnvironment* guienv;
	IGUIFont* font;
};

#endif /* POPUP_H_ */


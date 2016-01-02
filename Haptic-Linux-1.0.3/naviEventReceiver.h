/*
 * hapticEventReceiver.h
 *
 *  Created on: 2 Ara 2015
 *      Author: DMK
 */

#ifndef NAVIEVENTRECEIVER_H_
#define NAVIEVENTRECEIVER_H_
#ifdef _MSC_VER
// We'll define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif
#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>
#include "mapDisplay.h"
#include <vector>
#include "userDisplay.h"
#include "popUp.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace std;

class naviEventReceiver : public IEventReceiver {
public:
	naviEventReceiver(IrrlichtDevice * device, mapDisplay* map, userDisplay* user);
	void objectSelectHandler();
	int getClickedMarkerId();
	virtual bool OnEvent(const SEvent& event);
	virtual ~naviEventReceiver();
	// Variables
	bool isClickedInside;
	bool clickable;
	bool roadIsCalculated;
private:
    //SEvent::SJoystickEvent JoystickState;
	IrrlichtDevice *device;
	ISceneManager* smgr;
	ISceneCollisionManager *colmgr;
	mapDisplay* map;
	userDisplay* user;
	int clickedMarkerIndex;
	int finalId;
	bool clickDown;
	popUp popsy;
};

#endif /* NAVIEVENTRECEIVER_H_ */


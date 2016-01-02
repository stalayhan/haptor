/*
 * mapDisplay.h
 *
 *  Created on: 19 Kas 2015
 *      Author: DMK
 */

#ifndef MAPDISPLAY_H_
#define MAPDISPLAY_H_

#include <irrlicht.h>
#include <vector>
#include "markerButton.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace std;

class mapDisplay {
public:
	mapDisplay(IrrlichtDevice *device);
	vector<markerButton>& getMarkerButtons();
	vector<markerButton>& getMarkerButtonsOtherMap();
	void changeToInside(int clickedMarkerIndex);
	void changeToOutside(int clickedMarkerIndex);
	virtual ~mapDisplay();
	// VARIABLES
	bool isInside;
private:
	IrrlichtDevice *device;
	ISceneNode* mapNode;
	ISceneManager* smgr;
	IVideoDriver* driver;
	IAnimatedMesh* mapMesh;
	vector<markerButton> insideButtons;
	vector<markerButton> outsideButtons;
	void addMarkerButtonsInside();
	void addMarkerButtonsOutside();

};

#endif /* MAPDISPLAY_H_ */

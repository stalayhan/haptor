/*
 * markerButton.h
 *
 *  Created on: 26 Kas 2015
 *      Author: DMK
 */

#ifndef MARKERBUTTON_H_
#define MARKERBUTTON_H_

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class markerButton {
public:
	markerButton(vector3df position, IrrlichtDevice *device, int nodeId);
	void setVisible(bool isVisible);
	ISceneNode* getMarkerNode();
	ITriangleSelector* getSelector();
	ISceneNode* getSph();
	void scaleSmaller();
	void resetScale();
	virtual ~markerButton();
	// VARIABLES
	bool isSelected;
	int id;
private:
	ISceneManager* smgr;
	IVideoDriver* driver;
	IAnimatedMesh* markerMesh;
	ITriangleSelector* selector;
	IAnimatedMeshSceneNode * markerNode;
	ISceneNode *sph;
};

#endif /* MARKERBUTTON_H_ */


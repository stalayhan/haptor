/*
 * hapticEventReceiver.cpp
 *
 *  Created on: 2 Ara 2015
 *      Author: DMK
 */

#include "naviEventReceiver.h"


#define BUTTON_YES 1
#define BUTTON_NO 2
#define BUTTON_SETINSIDE 15

naviEventReceiver::naviEventReceiver(IrrlichtDevice * device, mapDisplay* map, userDisplay* user) {
	this->device = device;
	this->map = map;
	this->user = user;
	this->guienv = guienv;
	smgr = device->getSceneManager();
	colmgr = smgr->getSceneCollisionManager();
	clickedMarkerIndex = -1;
	finalId = -1;
	clickable = true;
	clickDown = false;
	isClickedInside = false;
	roadIsCalculated = false;
}

bool naviEventReceiver::OnEvent(const SEvent& event){
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch(event.MouseInput.Event)
		{
		case EMIE_LMOUSE_PRESSED_DOWN:
			if(clickable)
				objectSelectHandler();
			break;
		case EMIE_LMOUSE_LEFT_UP:
			// mark the selected marker
			if(clickedMarkerIndex != -1 && clickable){
				// reset size for click effect
				map->getMarkerButtons()[clickedMarkerIndex].resetScale();
				for(int i = 0; i < map->getMarkerButtons().size(); ++i)
					if(i != clickedMarkerIndex)
						map->getMarkerButtons()[i].setVisible(false);
					else
						map->getMarkerButtons()[i].isSelected = true;
				clickable = false;
				popsy.showPopUp(device);
				if(map->isInside)
					isClickedInside = true;
				else
					isClickedInside = false;
			}
			clickDown = false;
			break;
		case EMIE_MOUSE_WHEEL:
			if(!clickDown){
				// scroll in
				if(event.MouseInput.Wheel > 0){
					map->changeToInside(clickedMarkerIndex);
					user->setScale(vector3df(15, 0, 15));
					// when you show inside, if user is at outside don't show it
					if(user->isInside)
						user->setVisible(true);
					else
						user->setVisible(false);
				}
				// scroll out
				else if(event.MouseInput.Wheel < 0){
					map->changeToOutside(clickedMarkerIndex);
					user->setScale(vector3df(8, 0, 8));
					// when you show outside, if user is at inside make it stable in Comp. Eng.
					if(user->isInside)
						user->setPosition(vector3df(87,10,107));
					user->setVisible(true);
				}
			}
			break;
		default:
			// if middle button pressed, reset selected markers
			if(event.MouseInput.isMiddlePressed() && !clickDown){
				clickedMarkerIndex = -1;
				clickable = true;
				if(map->isInside)
					map->changeToInside(clickedMarkerIndex);
				else
					map->changeToOutside(clickedMarkerIndex);
				for(unsigned int i=0; i<map->getMarkerButtons().size(); i++){
					map->getMarkerButtons()[i].isSelected=false;
				}
				for(unsigned int i=0; i<map->getMarkerButtonsOtherMap().size(); i++){
					map->getMarkerButtonsOtherMap()[i].isSelected=false;
				}
				roadIsCalculated = false;
				finalId = -1;
			}
			break;
		}
	}

	 if (event.EventType == EET_GUI_EVENT)
	{
		if(event.GUIEvent.EventType == EGET_ELEMENT_CLOSED)
		{
			clickedMarkerIndex = -1;
			clickable = true;
			if(map->isInside)
				map->changeToInside(clickedMarkerIndex);
			else
				map->changeToOutside(clickedMarkerIndex);
			for(unsigned int i=0; i<map->getMarkerButtons().size(); i++){
				map->getMarkerButtons()[i].isSelected=false;
			}
			for(unsigned int i=0; i<map->getMarkerButtonsOtherMap().size(); i++){
				map->getMarkerButtonsOtherMap()[i].isSelected=false;
			}
		}
		if(event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
		{

			if (event.GUIEvent.Caller->getID() == BUTTON_SETINSIDE){
				user->isInside = !user->isInside;
				//setButton
			
				cout << "Alooo" << endl;
			}

			if(event.GUIEvent.Caller->getID() == BUTTON_YES){
				finalId = map->getMarkerButtons()[clickedMarkerIndex].id;
				popsy.closePopUp();
				roadIsCalculated = false;
			}
			if(event.GUIEvent.Caller->getID() == BUTTON_NO){
				clickedMarkerIndex = -1;
				clickable = true;
				if(map->isInside)
					map->changeToInside(clickedMarkerIndex);
				else
					map->changeToOutside(clickedMarkerIndex);
				for(unsigned int i=0; i<map->getMarkerButtons().size(); i++){
					map->getMarkerButtons()[i].isSelected=false;
				}
				for(unsigned int i=0; i<map->getMarkerButtonsOtherMap().size(); i++){
					map->getMarkerButtonsOtherMap()[i].isSelected=false;
				}
				popsy.closePopUp();
				roadIsCalculated = false;
				finalId = -1;
			}
		}
	}
	return false;
}

void naviEventReceiver::objectSelectHandler(){
	ISceneNode* select = smgr->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(device->getCursorControl()->getPosition());

	// debug print lines
	//if(select)
	//	cout<<select->getPosition().X << " " << select->getPosition().Y << " " << select->getPosition().Z<<endl;

	// check markers to find which one's clicked
	for(unsigned int i=0; i<map->getMarkerButtons().size(); i++){
		if (map->getMarkerButtons()[i].getSph() == select) {
			clickedMarkerIndex = i;
			// set size for click effect
			map->getMarkerButtons()[i].scaleSmaller();
			clickDown = true;
		}
	}
}

int naviEventReceiver::getClickedMarkerId(){
	return finalId;
}

naviEventReceiver::~naviEventReceiver() {
	// TODO Auto-generated destructor stub
}


/*
 * popUp.cpp
 *
 *  Created on: 23 Ara 2015
 *      Author: Lenovo
 */

#include "popUp.h"

#include <IGUISkin.h>
#include <IGUIWindow.h>
#include <rect.h>

#define BUTTON_YES 1
#define BUTTON_NO 2

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace std;
using namespace gui;

popUp::popUp() {

}

void popUp::customizeWindow(){

	for (s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
	{
		video::SColor col = guienv->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
		switch(i){
		case 0:
			col.setAlpha(255);
			col.set(255, 0, 0, 0);
			break;
		case 1:
			col.setAlpha(255);
			col.set(255, 0, 0, 0);
			break;
		case 3:
			col.setAlpha(255);
			col.set(255, 0, 0, 0);
			break;
		case 5:
			col.setAlpha(255);
			col.set(255, 0, 0, 0);
			break;
		// caption
		case 6:
			col.setAlpha(255);
			col.set(255, 255, 255, 255);
			break;
		// inside text
		case 8:
			col.setAlpha(255);
			col.set(255, 255, 255, 255);
			break;
		case 12:
			col.setAlpha(255);
			col.set(255, 0, 0, 0);
			break;
		// caption when active
		case 13:
			col.setAlpha(255);
			col.set(255, 255, 255, 255);
			break;
		// close button
		case 18:
			col.setAlpha(255);
			col.set(255, 255, 255, 255);
			break;
		default:
			col.setAlpha(255);
			col.set(255, 50, 50, 50);
		}
		guienv->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
	}
}

void popUp::showPopUp(IrrlichtDevice *device){
	guienv = device->getGUIEnvironment();
	font = guienv->getFont("fonts/dmkFont.xml");
	if (font)
		guienv->getSkin()->setFont(font);
		guienv->getSkin()->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);

	window = guienv->addWindow(
							rect<s32>(100, 100, 500, 300),
							false, // modal?
							L"ARE YOU SURE?");

	guienv->addStaticText(L"\n\n           Are you sure to set here as destination?\n        (Hint: You can reset later with middle click.)",
							rect<s32>(0,20,400,200),
							true, // border?
							false, // wordwrap?
							window, 0, true);

	guienv->addButton(rect<s32>(70,130,160,170),window,1,L"YES");
	guienv->addButton(rect<s32>(240,130,330,170),window,2,L"NO");

	customizeWindow();
}

void popUp::closePopUp(){
	window->remove();
}

popUp::~popUp() {
	// TODO Auto-generated destructor stub
}

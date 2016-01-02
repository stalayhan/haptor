//============================================================================
// Name        : hapticSandwich.cpp
// Author      : DMK
// Version     :
// Copyright   : ^_^
// Description :
//============================================================================

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

#include "payloadStruct.h"
#include "SerialClass.h"
#include <string>
#include <thread>

#include "mapDisplay.h"
#include "naviEventReceiver.h"
#include "path.h"
#include "userDisplay.h"
#include "nodes.h"

#define COMP_ENG_LAT 8047
#define COMP_ENG_LONG 56064
#define COMP_ENG_X 107
#define COMP_ENG_Y 92
#define LIBRARY_LAT 6548
#define LIBRARY_LONG 58839
#define LIBRARY_X 10
#define LIBRARY_Y 17

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;
using namespace video;

// Global variables
float userMotion = 0;
int userRotation = 0;
double ratioX = 0;
double ratioY = 0;

// Getter functions for other modules
vector3df setUserPositionInside(int square);
vector3df setUserPositionOutside(int latitude, int longitude);
int setUserRotation(int degree, bool isInside);
// coordinate conversion functions
void getRatioOutside();
vector3df convertCoordinates(int latitude, int longitude);//Takes last 5 num

//Payload Parse
void structToStr(char *dest_str, const struct payload *st_mockup);
void strToStruct(struct payload *st_mockup, char *str);

int calculateChecksum(const char *str);


struct payload st_payload;
// Incoming variables
int degree = 220;
int latitude = 6547;
int longitude = 58839;

float f_latitude;
float f_longitude;
int square = 2;//Haritadaki kordinat
//extern bool isUserInside = false;

int sourceId = 1;//Haritadaki node

void SerialThread(){
	int a;
	printf("Welcome to the serial test app!\n\n");
	std::string com = "\\\\.\\COM";
	std::string com_in;
	std::string fullCom;

	Serial* SP;   // adjust as needed
	//Serial* SP = new Serial("COM7");    // adjust as needed

	std::string p_degree;
	std::string p_lang;
	std::string p_lt;


	do{
		cout << "Plesea enter com port" << endl;
		cin >> com_in;
		fullCom = com + com_in;
		SP = new Serial(&fullCom[0]);
	} while (!(SP->IsConnected()));

	if (SP->IsConnected())
		printf("We're connected");

	char incomingData[256] = "";			// don't forget to pre-allocate memory
	//printf("%s\n",incomingData);
	int dataLength = 255;
	int readResult = 0;
	bool status = true;

	//###################################
	while (SP->IsConnected())
	{
		if (status){
			readResult = SP->ReadData(incomingData, dataLength);
			// printf("Bytes read: (0 means no data available) %i\n",readResult);

			//printf("%d", st_payload.st_direction.degree);
			incomingData[readResult] = 0;
			if (readResult > 0){
				st_payload.st_direction.northDegree=0;
				strToStruct(&st_payload, incomingData);
				printf("%d--%lu, %lu\n", st_payload.st_direction.northDegree, st_payload.st_gps_coord.x_coord, st_payload.st_gps_coord.y_coord);
				if (st_payload.st_direction.northDegree!=0)
					degree = st_payload.st_direction.northDegree;

				if (st_payload.st_gps_coord.x_coord != 0 && st_payload.st_gps_coord.y_coord != 0){
					f_longitude = st_payload.st_gps_coord.y_coord;
					f_longitude / 1000000;
					f_latitude = st_payload.st_gps_coord.x_coord;
					f_latitude / 1000000;
					latitude = st_payload.st_gps_coord.x_coord%100000;
					longitude = st_payload.st_gps_coord.y_coord % 100000;

				
				}
				
			}
			

			status = false;

		}
		else{
			structToStr(incomingData, &st_payload);
			SP->WriteData(incomingData, 255);
			status = true;
		}
	}
	//####################################
}

int main()
{
	IrrlichtDevice *device =
					createDevice( video::EDT_OPENGL, dimension2d<u32>(1024,768), 16,
					false, false, false, 0);
	device->setResizable(true);
	if (!device)
		return 1;

	std::thread serial(SerialThread);
	device->setWindowCaption(L"Haptic Navigator");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	IGUIButton *setButton = guienv->addButton(rect<s32>(1024-100, 0, 1024,0+30), 0, 15, L"Set Inside", L" ");//###########


	userDisplay user = userDisplay(vector3df(-35,10,52), device, false);
	mapDisplay map = mapDisplay(device);

	// build scene with initial camera position and light
	smgr->addCameraSceneNode(0, vector3df(0,182,0), vector3df(0,0,0));
	smgr->setAmbientLight(SColorf(255,255,255,0));

	// ADD MOUSE EVENT
	naviEventReceiver receiver = naviEventReceiver(device, &map, &user);
	device->setEventReceiver(&receiver);

	// find ratio between real map and screen to convert coordinates
	getRatioOutside();

	initializeDirectionMatrixIndoor();
	initializeDirectionMatrixOutdoor();
	//initializeAdjacencyLists(user.isInside, 2, 10);

	


	//latitude = st_payload.st_gps_coord.x_coord;
	//longitude = st_payload.st_gps_coord.y_coord;


	//###############################SOCKET##########################
	



	user.isInside = true;//#####################

	// update display
	while (device->run())
	{
		if (!receiver.roadIsCalculated){
			if (receiver.getClickedMarkerId() != -1){
				initializeAdjacencyLists(receiver.isClickedInside, sourceId, receiver.getClickedMarkerId());
				receiver.roadIsCalculated = true;
			}
		}


		if (user.isInside)
			setButton->setText(L"isInside=1");
		else
			setButton->setText(L"isInside=0");

		if(map.isInside && user.isInside){
			user.setPosition(setUserPositionInside(square));
			user.rotateUser(setUserRotation(degree, map.isInside));
		}
		else if(!map.isInside && !user.isInside){
			user.setPosition(setUserPositionOutside(latitude, longitude));
			user.rotateUser(setUserRotation(degree, map.isInside));
		}
		else if(!map.isInside && user.isInside){
			user.rotateUser(setUserRotation(degree, map.isInside));
		}

		driver->beginScene(true, true, SColor(255,39,39,39));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}

	device->drop();

	return 0;
}

vector3df setUserPositionInside(int square){

	switch (square) {
	case 1:
		return vector3df(-37, 10, 55);
	case 2:
		return vector3df(-30, 10, 30);
	case 3:
		return vector3df(-30, 10, -15);
	case 4:
		return vector3df(-30, 10, -55);
	case 5:
		return vector3df(8, 10, -70);
	case 6:
		return vector3df(45, 10, -55);
	case 7:
		return vector3df(45, 10, -15);
	case 8:
		return vector3df(45, 10, 8);
	case 9:
		return vector3df(45, 10, 30);
	case 10:
		return vector3df(52, 10, 55);
	case 11:
		return vector3df(30, 10, 60);
	case 12:
		return vector3df(-15, 10, 60);
	default:
		return vector3df(500, 500, 500);
	}
}



vector3df setUserPositionOutside(int latitude, int longitude){

	return convertCoordinates(latitude, longitude);
}

int setUserRotation(int degree, bool isInside){

	if(isInside)
		return 360-(degree -13);
	else
		return 360-degree;
}

void getRatioOutside(){
	double subLat = 0, subLong = 0, subX = 0, subY = 0;

	// find the ratio between real x,y and screen x,y
	subLat = COMP_ENG_LAT - LIBRARY_LAT;
	subY = COMP_ENG_Y - LIBRARY_Y;
	ratioY = subLat / subY;

	subLong = COMP_ENG_LONG - LIBRARY_LONG;
	subX = COMP_ENG_X - LIBRARY_X;
	ratioX = subLong / subX;
}

vector3df convertCoordinates(int latitude, int longitude){
	double subLat = 0, subLong = 0, subX = 0, subY = 0;

	subLat = COMP_ENG_LAT - latitude;
	subY = subLat / ratioY;
	latitude = COMP_ENG_Y - subY;

	subLong = COMP_ENG_LONG - longitude;
	subX = subLong / ratioX;
	longitude = COMP_ENG_X - subX;

	return vector3df(latitude, 10, longitude);

}

void structToStr(char *dest_str, const struct payload *st_mockup){
	//Struct taki verilerin mock_up string ine kaydedilmesi
	sprintf(dest_str, "%d, %d, %d, %d, %d, %lu, %lu, %d, %d, %d", st_mockup->st_router.channel, st_mockup->st_router.rssi,
		st_mockup->st_router.bssid, st_mockup->st_direction.northDegree, st_mockup->st_direction.turnDegree,
		st_mockup->st_gps_coord.x_coord, st_mockup->st_gps_coord.y_coord, st_mockup->type, st_mockup->flag,
		st_mockup->checksum);
}

/*
* example: "1, 2, 3" = ('1' + ',' + '2' + ',' + '3')%10
*/
int calculateChecksum(const char *str){
	int checkSum = 0, i = 0;
	do{
		checkSum += (int)str[i];
	} while (str[i] != '\0');

	return checkSum;
}

/*
*
*/
void strToStruct(struct payload *st_mockup, char *str)
{
	/*std::string channel;
	std::string rssi;  // keep positive, check sender code, if doesn't send positive, multipyly -1
	std::string bssid; // map to the router so don't have to keep 17 char (size of mac address) each router
	std::string northDegree;  // the angle relative to the north 0-360 - 16bit
	std::string turnDegree;
	std::string x_coord;
	std::string y_coord;
	std::string type;  // packet type e.g. indoor_pos_resp_t, indoor_pos_req_t
	std::string flag;  // for feature development
	std::string checksum;

	channel = strtok(str, ", ");
	rssi = strtok(NULL, ", ");
	bssid = strtok(NULL, ", ");
	northDegree = strtok(NULL, ", ");
	turnDegree = strtok(NULL, ", ");
	x_coord = strtok(NULL, ", ");
	y_coord = strtok(NULL, ", ");
	type = strtok(NULL, ", ");
	flag = strtok(NULL, ", ");
	checksum = strtok(NULL, ", ");

	st_mockup->st_router.channel = atoi(&channel[0]);
	st_mockup->st_router.rssi = atoi(&rssi[0]);
	st_mockup->st_router.bssid = atoi(&bssid[0]);
	st_mockup->st_direction.northDegree = atoi(&northDegree[0]);
	st_mockup->st_direction.turnDegree = atoi(&turnDegree[0]);
	st_mockup->st_gps_coord.x_coord = atoi(&x_coord[0]);
	st_mockup->st_gps_coord.y_coord = atoi(&y_coord[0]);
	st_mockup->type = atoi(&type[0]);
	st_mockup->flag = atoi(&flag[0]);
	st_mockup->checksum = atoi(&checksum[0]);*/



	sscanf(str,"%d, %d, %d, %d, %d, %lu, %lu, %d, %d, %d",
	&(st_mockup->st_router.channel),
	&(st_mockup->st_router.rssi),
	&(st_mockup->st_router.bssid),
	&(st_mockup->st_direction.northDegree),
	&(st_mockup->st_direction.turnDegree),
	&(st_mockup->st_gps_coord.x_coord),
	&(st_mockup->st_gps_coord.y_coord),
	&(st_mockup->type),
	&(st_mockup->flag),
	&(st_mockup->checksum)
	);
	//return (calculateChecksum(str) == st_mockup->checksum) ? 0 : 1;
}

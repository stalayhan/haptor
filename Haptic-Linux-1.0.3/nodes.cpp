/*Bazý noktalar hiç bir node a denk gelmiyor. Kullanýcý bu nodelarýn
dýþýna çýkarsa biz bir önceki nodedaymýs gibi devam ediyoruz.*/
#include "nodes.h"

int findNodeOutside(float x, float y){

	if (checkIfnode0(x, y))
		return 0;
	else if (checkIfnode1(x, y))
		return 1;
	else if (checkIfnode2(x, y))
		return 2;
	else if (checkIfnode3(x, y))
		return 3;
	else if (checkIfnode4(x, y))
		return 4;
	else if (checkIfnode5(x, y))
		return 5;
	else if (checkIfnode6(x, y))
		return 6;
	else if (checkIfnode7(x, y))
		return 7;
	else if (checkIfnode8(x, y))
		return 8;
	else if (checkIfnode9(x, y))
		return 9;
	else if (checkIfnode10(x, y))
		return 10;
	else if (checkIfnode11(x, y))
		return 11;
	else if (checkIfnode12(x, y))
		return 12;
	else if (checkIfnode13(x, y))
		return 13;
	else if (checkIfnode14(x, y))
		return 14;
	else if (checkIfnode15(x, y))
		return 15;
	else if (checkIfnode16(x, y))
		return 16;
	else if (checkIfnode17(x, y))
		return 17;
	else if (checkIfnode18(x, y))
		return 18;
	else if (checkIfnode19(x, y))
		return 19;
	else
		return -1;
}

bool checkIfnode0(double x, double y){
	return((x >= 40.808132 && x <= 40.808431) &&
		(y >= 29.356449 && y <= 29.356695));
}

bool checkIfnode1(double x, double y){
	return((x >= 40.807738 && x <= 40.808131) &&
		(y >= 29.356309 && y <= 29.356614));
}

bool checkIfnode2(double x, double y){
	return((x >= 40.807645 && x <= 40.807775) &&
		(y >= 29.356288 && y <= 29.356518));
}

bool checkIfnode3(double x, double y){
	return((x >= 40.807666 && x <= 40.807863) &&
		(y >= 29.355707 && y <= 29.356517));
}

bool checkIfnode4(double x, double y){
	return((x >= 40.807781 && x <= 40.807899) &&
		(y >= 29.355508 && y <= 29.355743));
}

bool checkIfnode5(double x, double y){
	return((x >= 40.807852 && x <= 40.808398) &&
		(y >= 29.355510 && y <= 29.355910));
}

bool checkIfnode6(double x, double y){
	return((x >= 40.808399 && x <= 40.808528) &&
		(y >= 29.355698 && y <= 29.355911));
}

bool checkIfnode7(double x, double y){
	return((x >= 40.808168 && x <= 40.808489) &&
		(y >= 29.356450 && y <= 29.356969));
}

bool checkIfnode8(double x, double y){
	return((x >= 40.807434 && x <= 40.807665) &&
		(y >= 29.356214 && y <= 29.356469));
}

bool checkIfnode9(double x, double y){
	return((x >= 40.807314 && x <= 40.807433) &&
		(y >= 29.356173 && y <= 29.356430));
}

bool checkIfnode10(double x, double y){
	return((x >= 40.806772 && x <= 40.807314) &&
		(y >= 29.356402 && y <= 29.359336));
}

bool checkIfnode11(double x, double y){
	return((x >= 40.806772 && x <= 40.806911) &&
		(y >= 29.359289 && y <= 29.359637));
}
//////////////////////////////////////////////////////////
bool checkIfnode12(double x, double y){
	return((x >= 40.806038 && x <= 40.806771) &&
		(y >= 29.359114 && y <= 29.359597));
}
bool checkIfnode13(double x, double y){
	return((x >= 40.805725 && x <= 40.806037) &&
		(y >= 29.359034 && y <= 29.359398));
}
bool checkIfnode14(double x, double y){
	return((x >= 40.805490 && x <= 40.805725) &&
		(y >= 29.358980 && y <= 29.359229));
}

bool checkIfnode15(double x, double y){
	return((x >= 40.807653 && x <= 40.808132) &&
		(y >= 29.356615 && y <= 29.359756));
}

bool checkIfnode16(double x, double y){
	return((x >= 40.807605 && x <= 40.807825) &&
		(y >= 29.359756 && y <= 29.359892));
}
bool checkIfnode17(double x, double y){
	return((x >= 40.806900 && x <= 40.807605) &&
		(y >= 29.359408 && y <= 29.359836));
}
bool checkIfnode18(double x, double y){
	return((x >= 40.806969 && x <= 40.807785) &&
		(y >= 29.359836 && y <= 29.363454));
}
bool checkIfnode19(double x, double y){
	return((x >= 40.806877 && x <= 40.807121) &&
		(y >= 29.363454 && y <= 29.363952));
}
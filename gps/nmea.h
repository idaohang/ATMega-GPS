#ifndef NMEA_H
#define NMEA_H
	#include "buffer.h"
	#include "hd44780.h"
	#include<stdio.h>
	#define F_CPU 7372800UL
	#include <util/delay.h>

	extern short lat_deg;
	extern double lat_min;
	
	
	extern short lon_deg;
	extern double lon_min;
	

	extern float lat_decimal;
	extern float lon_decimal;

	extern char lon_[2];
	extern char lat_[2];
	extern char utcTime[11];
	extern short fixMode;
	extern short satsUsed;
	extern float MSL_Altitude;
	extern float course;
	extern float speed;

	extern short hour;
	extern short min;
	extern char time_of_day[3];
	/*void init_NMEA_Engine();*/
	extern void parseNMEA();
	void processGGA();
	void processGLL();
	void processVTG();
	void skipNextParameter();
	//extern char readFromBuffer();
	void readNextParameter(char* store);
	extern void utcToLocalTime();
	void cookLattitudeCoordinates();
	void cookLongitudeCoordinates();
#endif






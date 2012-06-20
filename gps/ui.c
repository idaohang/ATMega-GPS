/*
 * ui.c
 *
 * Created: 6/13/2012 1:14:48 PM
 *  Author: Harindra
 */ 
#include "hd44780.h"
#include "ui.h"
#include "nmea_fsm.h"
#include<avr/pgmspace.h>

char strLat[] ="Lat:";
char strLon[]="Lon:";
char strSats[] ="Sats:";
char strSpeed[]="Spd:";
char strFix[] ="Fix:";
char c=(char)223;
char strCourse[] ="Hed:";
char strAltitude[] ="A:";

void lcdUI1(){// Degree Minutes Seconds view
	write_HD44780_Command(CLEAR_DISPLAY);
	write_HD44780_DataAtRowCol(1,1,strLat);//start printing value at 5th column
	write_HD44780_DataAtRowCol(2,1,strLon);//value should be at 5th column
	write_HD44780_DataAtRowCol(3,1,strSpeed);
	write_HD44780_DataAtRowCol(3,12,strFix);
	//write_HD44780_DataAtRowCol(4,1,strCourse);
}

void displayHeadingAt(short col,short row){
	char buff[10];
	sprintf(buff,"%s%4.1f%c",strCourse,course,c);
	write_HD44780_DataAtRowCol(row,col,buff);
}

void displayAltitudeAt(short col, short row){
	char buff[10];
	sprintf(buff,"%s%4.1fm",strAltitude,MSL_Altitude);
	write_HD44780_DataAtRowCol(row,col,buff);
}

void displayLocalTimeAtColRow(short col,short row){
		utcToLocalTime();
		char buff[6];
		buff[5]='\0';
		
		if(hour<10 && min<10){
			sprintf(buff,"0%d:0%d%s",hour,min,time_of_day);
		}else if(hour<10){
			sprintf(buff,"0%d:%d%s",hour,min,time_of_day);
		}else if(min<10){
			sprintf(buff,"%d:0%d%s",hour,min,time_of_day);
		}else{
			sprintf(buff,"%d:%d%s",hour,min,time_of_day);
		}							
		write_HD44780_DataAtRowCol(row,col,buff);		
}

void displayDecimalLattitude(){
	char buff[12];	
	sprintf(buff,"%9.7f%c%s",lat_decimal,c,lat_);	
	write_HD44780_DataAtRowCol(1,5,buff);
}

void displayDecimalLongitude(){
	char buff[12];	
	sprintf(buff,"%9.7f%c%s",lon_decimal,c,lon_);	
	write_HD44780_DataAtRowCol(2,5,buff);
}

void displayFixMode(short col,short row){
	char buff[2];
		
	if(!strcmp(fixMode,"A"))sprintf(buff,"Y");
	else sprintf(buff,"N");
				
	write_HD44780_DataAtRowCol(row,col,buff);
}

void displaySatsUsed(short col,short row){
	char buff[7];
	sprintf(buff,"Sats:%d",satsUsed);
	write_HD44780_DataAtRowCol(row,col,buff);
}

void displayLattitudeDegressMinutes(){
	char buff[17];	
	sprintf(buff,"%2d%c%6.4f'%s",lat_deg,c,lat_min,lat_);	
	write_HD44780_DataAtRowCol(1,5,buff);
}

void displayLongitudeDegressMinutes(){
	char buff[17];	
	
	sprintf(buff,"%2d%c%6.4f'%s",lon_deg,c,lon_min,lon_);
	write_HD44780_DataAtRowCol(2,5,buff);
}

void displayVerticalSpeedAtColRow(short col,short row){
	char buff[15];
	sprintf(buff,"%.2f",speed);
	write_HD44780_DataAtRowCol(row,col,buff);
}	
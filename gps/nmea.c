#include "nmea.h"
#include<stdlib.h>
#include<string.h>
#include "buffer.h"

#include<math.h>

char tempBuffer[15];//Temporarily hold parameters
char longitude[11];
char lattitude[10];

short lon_deg=0;
double lon_min=0;

short lat_deg=0;
double lat_min=0;

float lat_decimal=0;
float lon_decimal=0;

char lon_[2]; // N, S
char lat_[2];// E,W
char utcTime[11];
short fixMode=0; //false- no fix, true-valid fix
short satsUsed=0;
float MSL_Altitude;
float course=0;
float speed=0;

//time related variables
short hour;
short min;
char time_of_day[3];

void makeNullTerminating(char* str,int length){
	str[length-1]='\0';
}

void clearBuffer(char* buffer,short length){
	for(int i=9;i<length-1;i++){//do not clear the last position. it holds nul
		buffer[i]='0';
	}
}

void cookLattitudeCoordinates(){
	double tempLat=atof(lattitude);
	lat_deg=floor(tempLat/100.00);
	lat_min=tempLat-(lat_deg*100);

	lat_decimal=(lat_deg+ (tempLat-(lat_deg*100))/60.0);
}

void cookLongitudeCoordinates(){
	double tempLon=atof(longitude);
	lon_deg=floor(tempLon/100.00);
	lon_min=tempLon-(lon_deg*100);
		
	lon_decimal=(lon_deg+(tempLon-(lon_deg*100))/60.0);
}



void readNextParameter(char* store){
	char temp;
	char temp2;
	//int timeout=15;
	while((temp=readFromBuffer())!=','){
		if(temp=='\r'){//check if it is the end of the line 
			temp2=temp;
			if(temp=='\n' && temp2=='\r')break;	//end of sentence,exit the reader 	 
			}
		if(temp!=NULL){
		 *store=temp;//if temp=@, it means that buffer is empty. wait for data.
		 store++;
		}
	}			
}
void parseNMEA(){
	
	char szSentenceType[6];//MSG ID is exactly 5 characters long
	while(readFromBuffer()!='$');//Seek $ then exit loop and execute code below

		//Read sentence type identifier
		readNextParameter(szSentenceType);
		makeNullTerminating(szSentenceType,6);// Make sentenceType a null terminating one
				
		if(strcmp(szSentenceType,"GPGGA")==0){
			processGGA();
			//}
		//}else if(strcmp(szSentenceType,"GPGLL")==0){
			//processGLL();
		}else if(strcmp(szSentenceType,"GPVTG")==0){
			processVTG();
		}
}

int timeadd(int a,int hours,int minutes){
	int i=0,j=0;//i hours,j minutes
	i=a/100;
	j=a-(i*100);
	
	j+=minutes;
	if(j>=60){
		i=i+(j/60);
		j=(j%60);
	}
	i+=hours;
	if(i>=24)i-=24;
	
	return (i*100+j);
}
void utcToLocalTime(){
	char temp[5];
		
	memcpy(temp,utcTime,4);
	makeNullTerminating(temp,5);
	int ut=atoi(temp);
	//5 Hours and 30mins ahead of UTC
	int ut1=timeadd(ut,5,30);
	hour=(ut1/100);
	min=(ut1%100);
		
	if(ut1<1200){ memcpy(time_of_day,"AM",2);}
	else{ memcpy(time_of_day,"PM",2);}
		
	if(hour==0){hour=12;}
	else if(hour>12)hour-=12;
}
void processGGA(){
	char temp[3];

	makeNullTerminating(temp,3);
	makeNullTerminating(utcTime,11);
	readNextParameter(utcTime);
	
	makeNullTerminating(lattitude,10);
	readNextParameter(lattitude);
	cookLattitudeCoordinates();
	
	makeNullTerminating(lat_,2);
	readNextParameter(lat_);//N,S indicator
		
	makeNullTerminating(longitude,11);
	readNextParameter(longitude);
	cookLongitudeCoordinates();

	makeNullTerminating(lon_,2);
	readNextParameter(lon_);// E,W indicator
	
	clearBuffer(temp,3);
	readNextParameter(temp);
	fixMode=atoi(temp);	//Position validity	

	clearBuffer(temp,3);
	readNextParameter(temp);
	satsUsed=atoi(temp);

	readNextParameter(tempBuffer); //skip HDOP

	clearBuffer(tempBuffer,15);
	makeNullTerminating(tempBuffer,15);
	readNextParameter(tempBuffer);
	MSL_Altitude=atof(tempBuffer);

	////discard all the others for now

}


void processGLL(){


}
void processVTG(){
	
	makeNullTerminating(tempBuffer,15);
	clearBuffer(tempBuffer,15);
	readNextParameter(tempBuffer);//course
	course=atof(tempBuffer);
	
	skipNextParameter();//reference
	skipNextParameter();//course
	skipNextParameter();//reference
	skipNextParameter();//speed knots
	skipNextParameter();//unit knots
	clearBuffer(tempBuffer,15);
	readNextParameter(tempBuffer);//speed km/hr
	speed=atof(tempBuffer);
}
void skipNextParameter(){	
	//int timeout=15;
	while((readFromBuffer())!=','){
		//if(timeout<0)break;//timeout
		//timeout--;
	}
}
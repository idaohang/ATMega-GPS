/*
 * button.h
 *
 * Created: 6/15/2012 5:43:48 PM
 *  Author: Harindra
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#include<stdio.h>


extern short flag;
extern volatile short buttonChanged;
extern void initButtonHandler();

#endif /* BUTTON_H_ */
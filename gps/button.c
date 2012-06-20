/*
 * button.c
 *
 * Created: 6/15/2012 6:12:37 PM
 *  Author: Harindra
 */ 
#include "button.h"
#include <avr/io.h>
#include "hd44780.h"
#include <avr/interrupt.h>

short flag=1;
volatile short buttonChanged=0;

			
 void initButtonHandler(){
	
	DDRC|=(1<<DDC7);//PIN 7 of PORT C is input
	PORTC|=(1<<PC7);//Enable pull-up of PIN 7 of PORT C
	
	TCCR1B|=/*(0<<CS12)|(0<<CS10)|*/(1 << WGM12)|(1<<CS11);// clock, ctc mode
	OCR1A=64000;
	TIMSK|=(1<<OCIE1A);//enable interrupt for output compare	
}


ISR(TIMER1_COMPA_vect){
	if(!(PINC & (1<<PC7) )){
		
		while(!(PINC & (1<<PC7) ));//wait for the button to be released
		if(flag<2){
			buttonChanged=1;
			flag++;
		}else{
			flag=1;
			buttonChanged=1;
		}
	}			
		
		
}
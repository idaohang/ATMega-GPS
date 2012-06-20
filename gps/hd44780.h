#ifndef HD44780_H_
#define HD44780_H_

#include<avr/io.h>
#ifndef F_CPU
#define F_CPU 7372800UL
#endif
#include<util/delay.h>

#define CLEAR_DISPLAY 0b00000001
#define RETURN_HOME   0b00000010
#define DISPLAY_ON    0b00001100

#define DISPLAY_OFF   0b00001000
#define DIS_ON_CUR_ON_BLNK_OFF     0b00001110
#define DIS_ON_CUR_OFF_BLNK_OFF    0b00001100
#define DIS_ON_CUR_ON_BLNK_ON      0b00001111
#define DIS_ON_CUR_ON_BLNK_OFF     0b00001110
#define DIS_FUNC_SET               0b00111000 //8bit data, 2 lines, 5x10 dots

#define SET_E_PIN (PORTA |=(1<<PA2))
#define CLR_E_PIN (PORTA &=~(1<<PA2))
#define SET_RW_PIN (PORTA |=(1<<PA1))
#define CLR_RW_PIN (PORTA &=~(1<<PA1))
#define SET_RS_PIN (PORTA |=(1<<PA0))
#define CLR_RS_PIN (PORTA &=~(1<<PA0))
#define LCD_PORT PORTB

	extern void init_HD44780();
	extern void write_HD44780_Command(unsigned char cmd);
	extern void write_HD44780_DataAt(unsigned char address, char* data);
	extern void write_HD44780_DataAtRowCol(unsigned char y,unsigned char x,char* data);
	extern void write_HD44780_Data(char* data);
	extern void set_HD44780_DDRAM_Address(unsigned char address);
	extern void clearDisplay(short row,short fromCol,short toCol);
	//short LCDBusy();

#endif

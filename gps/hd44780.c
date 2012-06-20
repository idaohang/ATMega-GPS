#include "hd44780.h"

void init_HD44780(){
	DDRB=0xFF;//All pins output of LCD_PORT
	DDRA=(1<<DDB0)|(1<<DDB1)|(1<<DDB2);
	
	_delay_ms(1);
	write_HD44780_Command(CLEAR_DISPLAY);
	_delay_ms(1);
	write_HD44780_Command(DIS_ON_CUR_ON_BLNK_ON);
	_delay_ms(1);
	write_HD44780_Command(DIS_FUNC_SET);
}

void write_HD44780_Command(unsigned char cmd){
	LCD_PORT=0x0;
	LCD_PORT|=cmd;
	CLR_RW_PIN;
	CLR_RS_PIN;
	CLR_E_PIN;	
	SET_E_PIN;
	_delay_us(1);// wait
	CLR_E_PIN;
	_delay_ms(1);
}

void write_HD44780_DataAt(unsigned char address,char* data){
	set_HD44780_DDRAM_Address(address);
	write_HD44780_Data(data);
}

void write_HD44780_DataAtRowCol(unsigned char y,unsigned char x,char* data){
	unsigned char address=0;
	switch(y){
		//case 1: //case 1 is not really required. address is already zero
			//address=0x00;
			//break;
		case 2:
			address=0x40;
			break;
		case 3:
			address=0x10;
			break;
		case 4:
			address=0x50;
			break;	
	}

	address+=x-1;
	
	write_HD44780_DataAt(address,data);
}

void write_HD44780_Data(char* data){
	SET_RS_PIN;
	CLR_RW_PIN;
	CLR_E_PIN;
	while(*data){
		_delay_ms(1);
		LCD_PORT=0x0;
		LCD_PORT=*data;
		SET_E_PIN;
		_delay_us(1);
		CLR_E_PIN;
		_delay_us(200);
		data++;
	}
}

void set_HD44780_DDRAM_Address(unsigned char address){
	CLR_RS_PIN;//select IR
	CLR_RW_PIN;//Going to write
	LCD_PORT=0x0;
	LCD_PORT|=(1<<7); //|=0b10000000
	//Now set address
	LCD_PORT|=address;
	CLR_E_PIN;
	_delay_us(2);
	SET_E_PIN;
	_delay_us(2);
	CLR_E_PIN;
	_delay_ms(1);

}

void clearDisplay(short row,short fromCol,short toCol){
	char c[]=" ";
	for(int j=fromCol;j<=toCol;j++){
		write_HD44780_DataAtRowCol(row,j,c);
		
	}
}
/*short LCDBusy(){
	SET_RW_PIN;
	CLR_RS_PIN;
	SET_E_PIN;
	_delay_us(10);
	if(LCD_PORT & 0x80) {// PIN 7 high
		CLR_E_PIN;
		CLR_RW_PIN;
		return 1;
	}else{
		CLR_E_PIN;
		CLR_RW_PIN;
		return 0;
	}
}*/


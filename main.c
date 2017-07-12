/*
 * LCDMain.c
 *
 *  Created on: Jul 12, 2017
 *      Author: leenovoz510
 */

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#define LCD_RS_Pin 5
#define LCD_RW_pin 6
#define LCD_Enable_Pin 7

void send_command(char command);
void send_data(char data);
void clear_screan();
void Print_On_Screen(char *str);
void Go_to(char x ,char y);
void LCD_init();


int	main(void){

    DDRA  |= 0xff;
    DDRB  |= 0xFF;	/* Init Data PIN as Output 4,5,6,7 */
    _delay_ms(10);
    LCD_init();
    _delay_ms(10);
    clear_screan();

    DDRC = 0; PORTC |= 0xff;
    DDRD = 0; PORTD |= 0xff;

    int key[4]= {11} , i=0 ;
	while(1){

		key[i] = Keybad();
				if(key[i] != 11){
							PORTA ^= (1<<0);
							Go_to(2, 1);
							Print_On_Screen("Enter Password");
							Go_to(i+1, 2);
							Print_On_Screen("*");
							_delay_ms(30);
							i++;
					}
				if(i == 4){
					if(key[0] == 1 && key[1] == 9 && key[2] == 9 &&key[3] == 6 ){
						PORTA ^= (1<<1);
						PORTA &= ~(1<<2);
						Go_to(1, 2);
						Print_On_Screen("Correct Password");
						i = 0;
						key[i] = 11;
					}else{
						i = 0;
						key[i] = 11;
						PORTA ^= (1<<2);
						PORTA &= ~(1<<1);
						Go_to(1, 2);
						Print_On_Screen("worng Password");
					}
				}


	}
}

int Keybad(){
	int x = 11;
	if(PINC == 0b11111110){
		x = 1;
	}else if(PINC == 0b11111101){
		x = 2;
	}
	else if(PINC == 0b11111011){
		x = 3;
	}
	else if(PINC == 0b11110111){
		x = 4;
	}
	else if(PINC == 0b11101111){
		x = 5;
	}
	else if(PINC == 0b11011111){
		x = 6;
	}
	else if(PINC == 0b10111111){
		x = 7;
	}
	else if(PINC == 0b01111111){
		x = 8;
	}
	else if(PIND == 0b11111110){
		x = 9;
	}
	else if(PIND == 0b11111101){
		x = 0;
	}
return x;
}
void send_command(char command){
	PORTB = command;
	PORTA &= ~(1<<LCD_RS_Pin);
	PORTA &= ~(1<<LCD_RW_pin);

	PORTA |= (1<<LCD_Enable_Pin);
	_delay_ms(10);
	PORTA &= ~(1<<LCD_Enable_Pin);
}
void send_data(char data){
	PORTB = data;

	PORTA |= (1<<LCD_RS_Pin);
	PORTA &= ~(1<<LCD_RW_pin);

	PORTA |= (1<<LCD_Enable_Pin);
	_delay_ms(10);
	PORTA &= ~(1<<LCD_Enable_Pin);

}
void clear_screan(){
	send_command(0x01);
	_delay_ms(10);
}
void Print_On_Screen(char *str){
	int i=0;
	while(str[i] != 0){
		send_data(str[i]);
		i++;
	}
}
void Go_to(char x ,char y){
	char firstAddress[] = {0x80,0xC0,0x94,0xD4};
	send_command(firstAddress[y-1] + x-1);
		_delay_ms(10);
}
void LCD_init(){
	send_command(0x38);  // 8-bit mode
	send_command(0x0C);
	send_command(0x06);
	send_command(0x80);
		_delay_ms(10);
}

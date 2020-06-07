
/*
 * LINK:  https://drive.google.com/open?id=1JuKrMBCEp6ZJquMKzs7LvTvemHu8DpAN
 * */

/*
Author: Robert Wyatt
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#include "io.h"
#include"keypad.h"
#include "scheduler.h"
#include "bit.h"
#endif

enum let_key_states{let_key_start, let_key_base}let_key_state;
enum visual_states{visual_base, visual_start}visual_state;

unsigned char saveX;
unsigned char savePoint;
unsigned char array[37] = {'C','S',1 + '0', 2 + '0', '0', 'B', 32,'i','s',32, 'L','e','g','e','n','d',46,46,46,32,'w','a','i','t',32, 'f','o','r',32, 'i','t',32 ,'D','A','R','Y',33};
	int Visual(){
		switch(visual_state){
			case visual_start:
				visual_state = visual_base;
			break;
			case visual_base:
				visual_state = visual_base;
			break;
		}
		switch(visual_state){
                        case visual_start:
                        break;
                        case visual_base:

			if(savePoint == 39 - 12){
				savePoint = 0;
			}
			LCD_Cursor(0x01);
			if(savePoint < 38 -12)	
			for(unsigned char i = savePoint; i < 12 + savePoint; i ++){
				 LCD_WriteData(array[i]);
			}
			savePoint++;
			return visual_base;
                        break;
                }
	}

	int LetterKey(){
		switch(let_key_state){
			case let_key_start:
			let_key_state = let_key_base;
			break;
			case let_key_base:
			let_key_state = let_key_base;
			break;
		}
		switch(let_key_state){
			case let_key_base:
				saveX = GetKeypadKey();
				switch(saveX){
					
					case '\0': break;
					case '0':LCD_Cursor(0x01); LCD_WriteData(0 + '0');
						  break;

					case '1': LCD_Cursor(0x01);LCD_WriteData(1 + '0');
						  break;

					case '2': LCD_Cursor(0x01);LCD_WriteData(2 + '0');
						  break;

			                case '3': LCD_Cursor(0x01);LCD_WriteData(3 + '0');
						  break;

				     	case '4': LCD_Cursor(0x01);LCD_WriteData(4 + '0');
						  break;

                                        case '5': LCD_Cursor(0x01);LCD_WriteData(5 + '0');
						  break;

                                        case '6': LCD_Cursor(0x01);LCD_WriteData(6 + '0');
						  break;

                                        case '7': LCD_Cursor(0x01);LCD_WriteData(7 + '0');
						  break;

                                        case '8': LCD_Cursor(0x01);LCD_WriteData(8 + '0');
						  break;

                                        case '9': LCD_Cursor(0x01);
                                                  LCD_WriteData(9 + '0');
						  break;

                                        case '*': LCD_Cursor(0x01);
						  LCD_WriteData(42);
						  break;

					case '#': LCD_Cursor(0x01);
                                                  LCD_WriteData(35);
						  break;

						
				}
				return let_key_base;
				break;
			default:	
				break;
		}

	}



int main(void) {

	DDRA = 0xF0;PORTA = 0x0F;

       DDRC = 0xFF;PORTC = 0x00;

       DDRB = 0xFF;PORTB = 0x00;

       DDRD = 0xFF;PORTD = 0x00;

	const char start = -1;
	
	const unsigned long GCD = 50;
	savePoint = 0;

static task task1;
task *tasks[] = {&task1};
const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
task1.state = start;
task1.period = 500;
task1.elapsedTime = task1.period;
task1.TickFct = &Visual;
	
	LCD_init();
	TimerSet(50);
	TimerOn();

    while (1) {

	for (unsigned char i = 0; i < numTasks; i++){
		if(tasks[i]->elapsedTime == tasks[i]->period){		
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;	
		}
		tasks[i]->elapsedTime += GCD;
	}

	while(!TimerFlag){}

	TimerFlag = 0;

    }

    return 1;

}

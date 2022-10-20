/*
 * OLED.c
 *
 * Created: 06.10.2022 15:48:39
 *  Author: titouani
 */ 

#include <stdio.h>
#include <util/delay.h>
#include <string.h>
//#include <avr/pgmspace.h>
#include "SRAM.h"
#include "OLED.h"
#include "fonts.h"
#include "JOYSTICK.h"


volatile oled_pos current_pos;


void OLED_init()
{
	current_pos.page = 0x00;
	current_pos.column = 0x00;
	
	
	oled_write_c(0xae); // display off
	oled_write_c(0xa1); //segment remap
	oled_write_c(0xda); //common pads hardware: alternative
	oled_write_c(0x12);
	oled_write_c(0xc8); //common output scan direction:com63~com0
	oled_write_c(0xa8); //multiplex ration mode:63
	oled_write_c(0x3f);
	oled_write_c(0xd5); //display divide ratio/osc. freq. mode
	oled_write_c(0x80);
	oled_write_c(0x81); //contrast control
	oled_write_c(0x50);
	oled_write_c(0xd9); //set pre-charge period
	oled_write_c(0x21);
	oled_write_c(0x20); //Set Memory Addressing Mode
	oled_write_c(0x02);
	oled_write_c(0xdb); //VCOM deselect level mode
	oled_write_c(0x30);
	oled_write_c(0xad); //master configuration
	oled_write_c(0x00);
	oled_write_c(0xa4); //out follows RAM content
	oled_write_c(0xa6); //set normal display
	oled_write_c(0xaf); // display on
	
}

void oled_write_c(uint8_t command) {
	xmem_write(command, 0x0000);
}


void oled_write_d(uint8_t data) {
	OLED_set_page(current_pos.page);
	xmem_write(data, 0x0200);
}

void OLED_clear_page(){
	OLED_set_column(0x00);
	for (int column = 0; column < 128; column++) {
		oled_write_d(0x00);
	}
	OLED_set_column(0x00);
}


void OLED_reset() {
	OLED_set_page(0x00);
	
	for (int page = 0; page < 8; page++) {
		OLED_clear_page(page);
		OLED_go_to_page();
	}
	OLED_set_page(0x00);
	OLED_set_column(0x00);
}
	
void OLED_home(){
	
	OLED_reset();
	OLED_set_page(0x00);
	OLED_set_column(0x28);
	OLED_print_string("Menu");
	OLED_go_to_page();
	OLED_go_to_page();
	OLED_print_string("Play");
	OLED_go_to_page();
	OLED_print_string("Score");

	/*
	OLED_set_page(0x00);
	OLED_set_column(0x28);
	OLED_print_string("Jeu");
	*/
}

void OLED_score(){
	char* score_player1 = "99";
	char* score_player2 = "99";
	OLED_reset();
	OLED_set_page(0x00);
	OLED_set_column(0x28);
	OLED_print_string("Score");
	OLED_go_to_page();
	OLED_go_to_page();
	OLED_print_string("Player 1 :  ");
	OLED_print_string(score_player1);
	OLED_go_to_page();
	OLED_go_to_page();
	OLED_print_string("Player 2 :  ");
	OLED_print_string(score_player2);
}

void OLED_play(){
	
}


void OLED_scenario(){ // changer position - current page
	OLED_home();
	int position = 0;
	joystick_dir previous_position = NEUTRAL;
	joystick_dir direction =  NEUTRAL;
	
	
	while(1){
		direction = get_joystick_dir();
		if (previous_position == NEUTRAL){
			switch(direction){
				case(NEUTRAL):
					position=position;
					break;
				case(RIGHT):
					position=position;
					break;
				case(LEFT):
					position=position;
					break;
				case(DOWN):
					if(position < 3){
						position++;
					}
					break;
				case(UP):
					if(position > 0){
						position--;
					}
					break;
			}
			printf("\r\n position : %d", position);
		}
		previous_position=direction;
		if (joystick_button()){
			if (position == 3)
			{
				OLED_score();
			}
			else if (position == 2){
				OLED_play();
			}
			else{
				OLED_home();
			}
		}
		
	}
	
	
	
}


void OLED_go_to_page() {
	uint8_t next_page = current_pos.page + 0x01;
	OLED_set_page(next_page);
	OLED_set_column(0x00);	
}
	


void OLED_set_page(uint8_t page) {
	uint8_t mask = 0xB0;
	uint8_t command = mask | page;
	current_pos.page = page;
	oled_write_c(command);
}

void OLED_set_column(uint8_t column) {
	current_pos.column = column;
	uint8_t mask_lsb = 0x0F;
	uint8_t command = mask_lsb & column;
	oled_write_c(command);
	uint8_t mask_msb = 0xF0;
	command = mask_msb & column;
	for(int i=0;i<4;i++){
		command = command >> 1;
	}
	command = 0x10 | command;
	oled_write_c(command);
}

void OLED_print_char(unsigned char c){ // typo for calling func -> 'A' and not "A"
	int to_print = (int)c - 32;
	
	for (int i = 0; i < 8; i++){
		oled_write_d(pgm_read_byte(&font8[to_print][i]));
	}
	
}

void OLED_print_string(char* string) {
	int string_length = strlen(string);
	for (int i = 0; i < string_length; i++) {
		OLED_print_char(string[i]); 
	}
	
}
	
void OLED_print(char* c){}
	
void OLED_set_brightness(int level){}
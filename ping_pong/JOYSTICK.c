/*
 * JOYSTICK.c
 *
 * Created: 22.09.2022 15:00:01
 *  Author: titouani
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "JOYSTICK.h"
#include "ADC.h"

volatile joystick_pos mean_pos;

joystick_pos joystick_calibrate(){
	
	mean_pos.x = ADC_Read(0);
	mean_pos.y = ADC_Read(1);
	
	return mean_pos;
}

joystick_pos get_joystick_pos(){
	joystick_pos pos;
	joystick_dir dir;
	
	dir = get_joystick_dir();
	
	switch (dir)
	{
	case UP:
		pos.y = (int)(((ADC_Read(0) - mean_pos.y) * 100) / (223 - mean_pos.y));
		pos.x = (int)(((ADC_Read(1) - mean_pos.x) * 100) / mean_pos.x);
		break;
	case RIGHT:
		pos.x = (int)(((ADC_Read(1) - mean_pos.x) * 100) / (223 - mean_pos.x));
		pos.y = (int)(((ADC_Read(0) - mean_pos.y) * 100) / mean_pos.y);
		break;
	case LEFT:
		pos.x = (int)(((ADC_Read(1) - mean_pos.x) * 100) / abs(3 - mean_pos.x));
		pos.y = (int)(((ADC_Read(0) - mean_pos.y) * 100) / mean_pos.y);
		break;
	case DOWN:
		pos.y = (int)(((ADC_Read(0) - mean_pos.y) * 100) / abs(3 - mean_pos.y));
		pos.x = (int)(((ADC_Read(1) - mean_pos.x) * 100) / mean_pos.x);
		break;
	case NEUTRAL:
		pos.x = 0;
		pos.y = 0;
	}
	

	
	return pos;
}

joystick_dir get_joystick_dir() {
	joystick_dir dir;
	joystick_pos pos;
	pos.x = ADC_Read(1);
	pos.y = ADC_Read(0);
	dir = NEUTRAL;
	
	
	if (abs(mean_pos.x - pos.x) < 5 & abs(mean_pos.y - pos.y) < 5) 
	{
		return NEUTRAL;
	} else {
		if (abs(pos.x - mean_pos.x) > abs(pos.y - mean_pos.y)) {
			if (pos.x > mean_pos.x) {
				return RIGHT;
			} else {
				return LEFT;
			}
		} else {
			if (pos.y > mean_pos.y) {
				return UP;
			} else {
				return DOWN;
			} 
		}
	}
	
	return dir;
	
}

int joystick_button() {
	int x = 0;
	if ((PIND & 0b00100000) != 0b00100000) {
		x = 1;
		printf("Joystick button \r\n");
	}
	return x;
}
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
#include "CAN.h"

volatile joystick_pos mean_pos;

joystick_pos joystick_calibrate(){
	mean_pos.x = ADC_Read(1);
	mean_pos.y = ADC_Read(0);
	
	return mean_pos;
}

joystick_pos get_joystick_pos(){
	joystick_pos pos;
	joystick_dir dir;
	
	dir = get_joystick_dir();
	
	switch (dir)
	{
	case UP:
		pos.y = (int)abs(((ADC_Read(0) - mean_pos.y) * 100) / (255 - mean_pos.y));
		pos.x = (int)abs(((ADC_Read(1) - mean_pos.x) * 100) / mean_pos.x);
		pos.dir = UP;
		break;
	case RIGHT:
		pos.x = (int)abs(((ADC_Read(1) - mean_pos.x) * 100) / (255 - mean_pos.x));
		pos.y = (int)abs(((ADC_Read(0) - mean_pos.y) * 100) / mean_pos.y);
		pos.dir = RIGHT;
		break;
	case LEFT:
		pos.x = (int)abs(((ADC_Read(1) - mean_pos.x) * 100) / abs(3 - mean_pos.x));
		pos.y = (int)abs(((ADC_Read(0) - mean_pos.y) * 100) / mean_pos.y);
		pos.dir = LEFT;
		break;
	case DOWN:
		pos.y = (int)abs(((ADC_Read(0) - mean_pos.y) * 100) / abs(3 - mean_pos.y));
		pos.x = (int)abs(((ADC_Read(1) - mean_pos.x) * 100) / mean_pos.x);
		pos.dir = DOWN;
		break;
	case NEUTRAL:
		pos.x = 0;
		pos.y = 0;
		pos.dir = NEUTRAL;
	}

	return pos;
}

joystick_dir get_joystick_dir() {
	joystick_dir dir;
	joystick_pos pos;
	
	pos.x = ADC_Read(1);
	pos.y = ADC_Read(0);
	
	dir = NEUTRAL;
	
	
	if (abs(mean_pos.x - pos.x) < 15 & abs(mean_pos.y - pos.y) < 15) {
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
		
	}
	return x;
}


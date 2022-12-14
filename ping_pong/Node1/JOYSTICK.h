/*
 * JOYSTICK.h
 *
 * Created: 22.09.2022 15:00:14
 *  Author: titouani
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_
#include "CAN.h"


typedef enum {UP, DOWN, LEFT, RIGHT, NEUTRAL} joystick_dir;

typedef struct  
{
	uint8_t x;
	uint8_t y;
	joystick_dir dir;
	int button;
} joystick_pos;

joystick_pos joystick_calibrate();

joystick_dir get_joystick_dir();
joystick_pos get_joystick_pos();
int joystick_button();

#endif /* JOYSTICK_H_ */
/*
 * JOYSTICK.h
 *
 * Created: 22.09.2022 15:00:14
 *  Author: titouani
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

typedef struct  
{
	int x;
	int y;
} joystick_pos;

joystick_pos joystick_calibrate();

typedef enum {UP, DOWN, LEFT, RIGHT, NEUTRAL} joystick_dir;
joystick_dir get_joystick_dir();
joystick_pos get_joystick_pos();
int joystick_button();

#endif /* JOYSTICK_H_ */
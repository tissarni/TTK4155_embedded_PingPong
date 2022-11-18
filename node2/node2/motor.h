/*
 * motor.h
 *
 * Created: 18.11.2022 10:38:54
 *  Author: floriaca
 */ 

#include <stdio.h>

#ifndef MOTOR_H_
#define MOTOR_H_
#define encoder_mask (0xff << 1)


void motor_init();
uint16_t encoder_read();
void delay(int num);
void set_positon(int joy_value, int dir);


#endif /* MOTOR_H_ */
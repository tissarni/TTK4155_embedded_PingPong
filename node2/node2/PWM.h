/*
 * PWN.h
 *
 * Created: 17.11.2022 10:43:11
 *  Author: floriaca
 */ 


#ifndef PWM_H_
#define PWM_H_

void pwm_init(void);
void pwm_set_duty(int input, int dir);

#endif /* PWM_H_ */
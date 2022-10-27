/*
 * CAN.h
 *
 * Created: 27.10.2022 14:22:15
 *  Author: titouani
 */ 


#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>

typedef struct
{
	int id;
	int length;
	char data[8];
} can_message;

void can_init();
void can_send(can_message* message);
can_message can_receive();

#endif /* CAN_H_ */
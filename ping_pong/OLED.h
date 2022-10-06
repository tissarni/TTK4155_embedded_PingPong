/*
 * OLED.h
 *
 * Created: 06.10.2022 15:48:56
 *  Author: titouani
 */ 


#ifndef OLED_H_
#define OLED_H_

void OLED_init();
void oled_write_c(uint8_t command);
void oled_write_d(uint8_t data);



#endif /* OLED_H_ */
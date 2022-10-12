/*
 * OLED.h
 *
 * Created: 06.10.2022 15:48:56
 *  Author: titouani
 */ 


#ifndef OLED_H_
#define OLED_H_

typedef struct
{
	uint8_t page;
	uint8_t column;
} oled_pos;

void OLED_init();
void oled_write_c(uint8_t command);
void oled_write_d(uint8_t data);
void OLED_reset();
void OLED_home();
void OLED_go_to_page();
void OLED_clear_page(int page);
void OLED_set_page(uint8_t page);
void OLED_pos(int row, int column);
void OLED_write_data(volatile c);
void OLED_print(char* c);
void OLED_set_brightness(int level);



#endif /* OLED_H_ */
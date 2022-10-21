/*
 * MENU.c
 *
 * Created: 13.10.2022 14:26:11
 *  Author: titouani
 */ 

#include "MENU.h"

menu main_menu, play, score;

/*void MENU_init() {
	
	main_menu.name = "MAIN MENU";
	main_menu.parent = NULL;
	
	play.name = "Play";
	play.parent = &main_menu;
	
	score.name = "Score";
	score.parent = &main_menu;
	
	MENU_run(*main_menu);
}

void MENU_run(menu *current_menu){
	switch (current_menu.name)	{
		case "MAIN MENU":
			OLED_reset();
			
			OLED_set_page(0x00);
			OLED_set_column(0x00);
			
			OLED_print_char('A');
			OLED_go_to_page();
			OLED_print_string("VIVE LA FRANCE !");
			break;
		case "Play":
			OLED_reset();
		
			OLED_set_page(0x00);
			OLED_set_column(0x00);
		
			OLED_print_char('A');
			OLED_go_to_page();
			OLED_print_string("VIVE LA NORWAY !");
			break;
		case "Play":
			OLED_reset();
			
			OLED_set_page(0x00);
			OLED_set_column(0x00);
			
			OLED_print_char('A');
			OLED_go_to_page();
			OLED_print_string("VIVE LA TURQUIE !");
			break;
	}
}*/
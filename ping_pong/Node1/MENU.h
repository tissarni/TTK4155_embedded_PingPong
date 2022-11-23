/*
 * MENU.h
 *
 * Created: 13.10.2022 14:26:25
 *  Author: titouani
 */ 


#ifndef MENU_H_
#define MENU_H_

typedef struct
{
	char *name;
	struct menu *parent;
		
} menu;

void MENU_run(menu *current_menu);

#endif /* MENU_H_ */
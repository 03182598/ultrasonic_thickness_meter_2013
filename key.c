/*
 * key.c
 *
 *  Created on: 24.04.2009
 *      Author: Izon
 */

#include <avr/io.h>

#include "key.h"
//#include "core.h"
#include "constant.h"
#include "dev_cfg.h"
#include "display.h"
#include "measuring.h"
#include "main.h"

unsigned char tmp;
unsigned int key_new = 0;
unsigned int key_old = 0;


/////////////

void rkey (void)  /// сброс клавиатуры
{

PORTE |= _BV(KEY_RES); //1	
PORTE &= ~_BV(KEY_RES);//0

}

/////////////
unsigned char key_find (void)
{ unsigned char codk;



	if(((PINL & 0x04) == 0x04))
	
	
	
									////Проверить признак готовности клавиатуры 
	{
	
//	ctm(); // Счетчик 5минут для выключения
	
	codk = (KEY_PORT & 0X78);
	rkey();
	
	switch (codk)
	{
	case 64: return 1;
	case 32: return 2;
	case 0: return 3;
	
	case 80: return 4;
	case 48: return 5;
	case 16: return 6;
	
	case 72: return 7;
	case 40: return 8;
	case 8: return 9;
	
	case 88: return 10;
	case 56: return 11;
	case 24: return 12;
	}
	
	
	}
	
return 0;
}





unsigned char red_key(void) //// проверка нажатия клавиши выключения прибора для выходов из меню
{
unsigned char i=0;
if (!(PINF & (1<<ONKEY)))
	
	{ i=key_off; 
		//ctm();
		} // Счетчик 5минут для выключения}// BEEP(1); }
	
	else
	
	{ i=0; }
	
	return i;
}



/*
 * display.c
 *
 *  Created on: 03.04.2009
 *      Author: Izon
 */
#define F_CPU 3533200UL
#include <avr/io.h>
#include "key.h"
#include "main.h"
#include "display.h"
//#include "charset.h" !!!!!!!!!!!!
#include "constant.h"
//#include "core.h"
#include "dev_cfg.h"
#include "measuring.h"
#include <util/delay.h>
#include <avr/eeprom.h>
#include "MEM.h"

volatile unsigned char display_io =0;

unsigned char num_buffer[5] = {0, 0, 10, 10, 10};
unsigned char xnum_buffer[5] = {0, 0, 10, 10, 10};

unsigned char SHOW_NUM[5] = { 0, 0, 0, 0, 0};

unsigned char hi_num_buffer[4] = { 0, 10, 10, 10};
unsigned char snum_buffer[5] = {0, 0, 0, 0, 0};
unsigned char cnum_buffer[4] = {0, 10, 10, 10};
unsigned char new_buffer = 1;
unsigned char new_hi_buffer = 1;
unsigned char video_ram[50][4];

//---------------------------------------------------------------------------------------


unsigned char ask_disp(void)////// Передать состояние есть ли обмен с дисплеем
{
unsigned char i=0;

i = display_io; // Признак передачи данных в дисплей
return i;
}


unsigned char BRIVAL(void) ////Вычислить яркость дисплея
{
unsigned char ibv=0, x=0;

ibv = eeprom_read_byte(BRIGHT);  ////считать градацию

switch (ibv)
	{
	case 0:x=0x01; break;
	
		case 1:x=0x01; break;
	
	//case 2:x=0x10; break;
	
		case 2:x=0x30; break;
	
	//case 4:x=0x50; break;
	
		case 3:x=0x6C; break;
	
	//case 6:x=0x75; break;
	
	//case 7:x=0x88; break;
	
		case 4:x=0x9F; break;
	
	//case 9:x=0xA8; break;
	
		case 5:x=0xFF; break;
	}
	
	
	send_command(0xC1);send_data(0xFF);//// Отрегулировать яркость  x  !!!!!!!!!!!!!!
	return x;
}


void brset(void)
{
unsigned char io=0,ix=0;
	io = eeprom_read_byte(BRIGHT);  ////считать градацию
	ix=io;
//! cls();
	///show_mpos(6,20,0);/// усилен
	draw_dline();
	draw_memoline (9,7,48);
	put_int_to_cnum_buffer(io);
	show_cnum_buffer();
//! BEEP(2);

		while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
			{
			}
			_delay_ms (dkeyl); //!620
			key_find();
			_delay_ms (32);

			while (!(key_find()==keyenter)) /// ждать кнопки ввод
			{
				//if (key_find()==keyzero)
				//{
				//cls();
				//BEEP(1);
				//return 0;
				//}
				
				if (key_find()==keyup)   /// двигать курсор вверх вниз
				{   _delay_ms (step_speedZ);
					key_find();
					io ++;
					if (io==6) {io = 5;}
					 put_int_to_cnum_buffer(io);
					 show_cnum_buffer();
					 BEEP(3);
					 eeprom_write_byte (BRIGHT,io);
					 BRIVAL();
				}
				if (key_find()==keydown)
				{   _delay_ms (step_speedZ);
					key_find();	
					io --;
					if (io==0) { io =1;}
					 put_int_to_cnum_buffer(io);
					 show_cnum_buffer();
					BEEP(4);
					eeprom_write_byte (BRIGHT,io); 
					BRIVAL(); 
				}
				
			if (key_find()==keynastr) /// Выход по кнопке по которой вошли --- ждет когда ее отпустят тогда выход.
				{
				io=keynastr;
				while (io==keynastr)
				{
				_delay_ms(35);
				io=key_find();
				//BEEP(1);
				};	
		//! cls();
					// put_int_to_cnum_buffer(ix);  /// Вернуть первоночальную яркость
						//show_cnum_buffer();
					 eeprom_write_byte (BRIGHT,ix);
					 BRIVAL();
		 _delay_ms(dkeyl); //! 200
				BEEP(1);
				goto b_out;
				}
			}
	b_out:;
rkey();
	BEEP(1);
}

void ZPset(void) /// Управление звуком
{ 
signed char io=0,ix=0;

io = eeprom_read_byte(BEEP_MODE);  ////считать сост звука
ix=io;
cls();
///show_mpos(6,20,0);/// усилен
draw_dline();
//draw_memoline (10,7,48);
//put_int_to_cnum_buffer(io);
//show_cnum_buffer();
ZP_draw_zwuk(io);
BEEP(2);

while (!(key_find()==0)) /// ждать пока отпустят все кнопки
{
}
_delay_ms (620);
key_find();
_delay_ms (32);

while (!(key_find()==keyenter)) /// ждать кнопки ввод
{
	//if (key_find()==keyzero)
	//{
	//cls();
	//BEEP(1);
	//return 0;
	//}
	
	if (key_find()==keyup)   /// двигать курсор вверх вниз
	{   _delay_ms (step_speedZ);
		key_find();
		io ++;
		if (io==2) { io = 0;}
		// put_int_to_cnum_buffer(io);
		// show_cnum_buffer();
		ZP_draw_zwuk(io);
		BEEP(4);
		// eeprom_write_byte (BEEP_MODE,io);
	}
	if (key_find()==keydown)
	{   _delay_ms (step_speedZ);
		key_find();
		io --;
		if (io<0) { io =1;}
		// put_int_to_cnum_buffer(io);
		// show_cnum_buffer();
		ZP_draw_zwuk(io);
		BEEP(3);
		//eeprom_write_byte (BEEP_MODE,io);
		
	}
	
	if (key_find()==keynastr) /// Выход по кнопке по которой вошли --- ждет когда ее отпустят тогда выход.
	{
		io=keynastr;
		//BEEP(1);
		while (io==keynastr)
		{
			_delay_ms(35);
			io=key_find();
			//BEEP(1);
		};	cls();
		// put_int_to_cnum_buffer(ix);  /// Вернуть первоночальное сост звука
		//	show_cnum_buffer();
		
		//ZP_draw_zwuk(io);
		eeprom_write_byte (BEEP_MODE,ix);
		_delay_ms(200);
		goto b_out;
	}
	
	
	
}

eeprom_write_byte (BEEP_MODE,io);

b_out:;
rkey();
BEEP(1);
}

void ZP_draw_zwuk(unsigned char num) /// Рисовать меню звука
{
//cls();
switch (num)
	{
	case 1: show_wpos(44,6,0); show_wpos(45,6,14);  draw_dline(); menu_wcursor(1,0);  break;
	case 0: show_wpos(44,6,0); show_wpos(45,6,14);  draw_dline(); menu_wcursor(2,0);  break;
	}
	draw_memoline (10,7,48);
}

void digitbuf(unsigned long num)  /// поместить число в буфер для отображения наработки 5 симв
{

unsigned long temp = num; 

	SHOW_NUM[4] = temp / 10000;
	temp = temp % 10000;
	SHOW_NUM[3] = temp / 1000;
	temp = temp % 1000;
	SHOW_NUM[2] = temp / 100;
	temp = temp % 100;
	SHOW_NUM[1] = temp / 10;
	temp = temp % 10;
	SHOW_NUM[0] = temp;
	
	if(num < 10000)
	{
		SHOW_NUM[4] = 10;
		if(num < 1000)
		{
			SHOW_NUM[3] = 10;
			if(num < 100)
				{
					SHOW_NUM[2] = 10;
					if(num < 10)
					{
					SHOW_NUM[1] = 10;
					}
				}
		}		
	}
}

void put_int_to_num_buffer(unsigned int num, unsigned char doten)
{  
signed char ix;
ix=0;
if (num >= 10000)   ////  Выбор разрядов в 4 знакоместа
	  { 
	 num = num/10;
	 ix=1;
	  }
	 
	unsigned int temp = num;  
		
	//num_buffer[4] = temp / 10000;
	//temp = temp % 10000;
	num_buffer[3] = temp / 1000;
	temp = temp % 1000;
	num_buffer[2] = temp / 100;
	temp = temp % 100;
	num_buffer[1] = temp / 10;
	temp = temp % 10;
	num_buffer[0] = temp;
	if(num < 10000)
	{
		num_buffer[4] = 10;
		if(num < 1000)
		{
			num_buffer[3] = 10;
			if(num < 100)
				num_buffer[2] = 0;
		}
	}
	
	new_buffer = 1;
		
		
if (doten == 0) /// если 0 то рисовать точки
	{
		if(ix==0)
		{
			show_dot(0);
		}
		else
	
		if(ix==1)
		{
			show_dot(1);
		}
	}
	
	
}
/////////////////

//---------------------------------------------------------------------------------------
void put_int_to_bnum_buffer(unsigned int num, unsigned char pos) /// буфер для боковых надписей pos - нижн или верх строка
{  
signed char ixx;
ixx=0;
if (num >= 10000)   ////  Выбор разрядов в 4 знакоместа
	  { 
	 num = num/10;
	 ixx=1;
	  }
	 
	unsigned int temp = num;  
		
	//num_buffer[4] = temp / 10000;
	//temp = temp % 10000;
	xnum_buffer[3] = temp / 1000;
	temp = temp % 1000;
	xnum_buffer[2] = temp / 100;
	temp = temp % 100;
	xnum_buffer[1] = temp / 10;
	temp = temp % 10;
	xnum_buffer[0] = temp;
	if(num < 10000)
	{
		xnum_buffer[4] = 10;
		if(num < 1000)
		{
			xnum_buffer[3] = 10;
			if(num < 100)
				xnum_buffer[2] = 0;
		}
	}
	if(ixx==0)
	{
//	show_sdot(0,pos);
	}
	else
	
	if(ixx==1)
	{
//	show_sdot(1,pos);
	}
	
}
/////////////////////////////////////////////////////////////////////////////////////////

void show_bnum_buffer(unsigned char pos, unsigned int mnoj) // mnoj - значение буффера для определения положения зяпятой если 0xFFFA  то все стереть. 
{	
	
	
	unsigned int i, j, ypos = 0,xp = 0;

						if (mnoj == 0XFFFA) /// Стереть строчку

							{
							
							switch(pos)
							{
							case 0: ypos = 28; break; /// нижняя строчка
							case 1: ypos = 14; break; /// верхняя строчка
							}
	
	
								for(i = 0; i < 5; i++)
							
									{	
									
									switch(i)
									{
										case 0: xp = 23; break;
										case 1: xp = 24; break;
										case 2: xp = 25; break;
										case 3: xp = 26; break;
										case 4: xp = 27; break;
									}
	
									place_in_ram(xp, ypos+1, 1, 14);     //// X Y len len 
									send_command(0x5C);//Write RAM Command (5Ch)
									
										for(j = 0; j < 14; j++)//Y
									
										{
											send_8pixels(0);	
										}
									}
	
								}
	else {  ///// Рисование строки


	if (mnoj >= 10000) {mnoj = 1;} else {mnoj = 0;}


	switch (pos)
	{
	case 0: ypos = 28; break; /// нижняя строчка
	case 1: ypos = 14; break; /// верхняя строчка
	}
	
	
	
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	place_in_ram(23, ypos, 5, 15);     //// X Y len len //////////////////// Очистка поля 
	send_command(0x5C);//Write RAM Command (5Ch)
	
		for(j = 0; j < 15; j++)//Y
				{//
					send_8pixels(0);
					send_8pixels(0);
					send_8pixels(0);
					send_8pixels(0);
					send_8pixels(0);
				}*/
		for(i = 0; i < 4; i++)
		{
	
		if (mnoj == 1) //// отображает в формате *** * свыше 9999 
		{
		draw_smdot(0,ypos-1);
		switch(i)
		{
			case 0: xp = 23; break;
			case 1: xp = 25; break;
			case 2: xp = 26; break;
			case 3: xp = 27; break;
			///24+i*1
		}
		}
		
		else
		
		{
		draw_smdot(1,ypos-1);
		switch(i) //// отображает в формате ** **  до 9999
		{
				
			case 0: xp = 23; break;
			case 1: xp = 24; break;
			case 2: xp = 26; break;
			case 3: xp = 27; break;
			///24+i*1
			
		}
		}
		
			place_in_ram(xp, ypos, 1, 15);     //// X Y len len 
			send_command(0x5C);//Write RAM Command (5Ch)
			if(xnum_buffer[i] != 10)
				for(j = 0; j < 15; j++)//Y
			
				{
	
					send_8pixels(pgm_read_byte_near(small_num_set[xnum_buffer[i]][j]));
					
				}
				
			else
			{
				for(j = 0; j < 15; j++)//Y !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				{//
					send_8pixels(0);
				}
			}
	
		}
}
}
/////////////////////////////////////////////////////////////////////////////////////////

void put_int_to_cnum_buffer(unsigned int num) //// буфер служебный скорость усиление
{  

	unsigned int temp = num;
	cnum_buffer[3] = temp / 1000;
	temp = temp % 1000;
	cnum_buffer[2] = temp / 100;
	temp = temp % 100;
	cnum_buffer[1] = temp / 10;
	temp = temp % 10;
	cnum_buffer[0] = temp;
		if(num < 1000)
	{
		cnum_buffer[3] = 10;
		if(num < 100)
		{
			cnum_buffer[2] = 10;
			if(num < 10)
				cnum_buffer[1] = 10;
		}
	}
	new_buffer = 1;	
}

void show_cnum_buffer(void)/////////
{
	unsigned int i, j;


		for(i = 0; i < 4; i++)
		{
			place_in_ram(4+i*4, 0, 3, 42);     //// X Y len len 
			send_command(0x5C);//Write RAM Command (5Ch)
			if(cnum_buffer[i] != 10)
				for(j = 0; j < 42; j++)//Y
				{
					send_8pixels(pgm_read_byte_near(number_set[cnum_buffer[i]][j]));
					send_8pixels(pgm_read_byte_near(number_set[cnum_buffer[i]][j]+1));
					send_8pixels(pgm_read_byte_near(number_set[cnum_buffer[i]][j]+2));
				}
			else
			{
				for(j = 0; j < 42; j++)//Y
				{
					send_8pixels(0);
					send_8pixels(0);
					send_8pixels(0);
				}
			}
		}
//	}
}
//////////////////////////////////////////////

void put_int_to_snum_buffer(unsigned int num)
{  

	unsigned int temp = num;
	snum_buffer[4] = temp / 10000;
	temp = temp % 10000;
	snum_buffer[3] = temp / 1000;
	temp = temp % 1000;
	snum_buffer[2] = temp / 100;
	temp = temp % 100;
	snum_buffer[1] = temp / 10;
	temp = temp % 10;
	snum_buffer[0] = temp;
	
	if(num < 10000)
	{
		snum_buffer[4] = 10;
		if(num < 1000)
		{
			snum_buffer[3] = 0;
			if(num < 100)
			{
				snum_buffer[2] = 0;
				if(num < 10)
					snum_buffer[1] = 0;
			}
		}
	}
	
}

///----------------------------------------Show KONTAKT----------

void show_acont(unsigned char num)

{

				unsigned char i;
		if (num == 0)		
				{
					PORTH &= ~_BV(acontpin); // 0 вывод ак конт
				   
				place_in_ram(0, 15, 3, 13);
				send_command(0x5C);//Write RAM Command (5Ch)
				

				for(i = 0; i < 13; i++)//Y_len
					{	
					
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
					}

				}
				
				else
				
				{
				
					PORTH |= _BV(acontpin); // 1 вывод ак конт
					
				place_in_ram(0, 15, 3, 13);
				send_command(0x5C);//Write RAM Command (5Ch)
				

				for(i = 0; i < 13; i++)//Y_len
					{	
					
						send_8pixels(pgm_read_byte_near(acont_set[0][i]));
						send_8pixels(pgm_read_byte_near(acont_set[0][i]+1));
						send_8pixels(pgm_read_byte_near(acont_set[0][i]+2));
					}
				}	
				
}

//---------------------------------------------------------------------------------------
void show_mmdiv(void) // показать "мм" в режиме ИЗМЕРЕНИЕ
{
	unsigned char i;
	//! clr_mmsdiv();
	place_in_ram(0, 30, 3, 13);
	send_command(0x5C);//Write RAM Command (5Ch)
	for(i = 0; i < 13; i++)//Y_len
		{	
			send_8pixels(pgm_read_byte_near(MMdiv_set[0][i]));
			send_8pixels(pgm_read_byte_near(MMdiv_set[0][i]+1));
			send_8pixels(pgm_read_byte_near(MMdiv_set[0][i]+2));
		}
}

void show_msdiv(void)
{
	unsigned char i;
	clr_mmsdiv();
	place_in_ram(0, 30, 3, 13);
	send_command(0x5C);//Write RAM Command (5Ch)
	for(i = 0; i < 13; i++)//Y_len
		{	
		
			send_8pixels(pgm_read_byte_near(MSdiv_set[0][i]));
			send_8pixels(pgm_read_byte_near(MSdiv_set[0][i]+1));
			send_8pixels(pgm_read_byte_near(MSdiv_set[0][i]+2));
		}
}

void clr_mmsdiv(void)
{
	unsigned char i;
	
	place_in_ram(0, 30, 3, 13);
	send_command(0x5C);//Write RAM Command (5Ch)
	for(i = 0; i < 13; i++)//Y_len
		{	
		
			send_8pixels(0);
			send_8pixels(0);
			send_8pixels(0);
		}

}
////////////////////////////////////////////////////////

void show_batEXT(void)//// Внешнее питание 
{
	unsigned char i;
//! clr_bat();
	place_in_ram(0, 0, 3, 13);
	send_command(0x5C);//Write RAM Command (5Ch)
	for(i = 0; i < 13; i++)//Y_len
		{	
		
			send_8pixels(pgm_read_byte_near(batEXT_set[0][i]));
			send_8pixels(pgm_read_byte_near(batEXT_set[0][i]+1));
			send_8pixels(pgm_read_byte_near(batEXT_set[0][i]+2));
		}

}
////////////////////////

void show_bat100(void)//Батарейка 100%  
{
	unsigned char i;
	
	//! clr_bat();
	place_in_ram(0, 0, 3, 13);
	send_command(0x5C);//Write RAM Command (5Ch)
	for(i = 0; i < 13; i++)//Y_len
		{	
			send_8pixels(pgm_read_byte_near(bat100_set[0][i]));
			send_8pixels(pgm_read_byte_near(bat100_set[0][i]+1));
			send_8pixels(pgm_read_byte_near(bat100_set[0][i]+2));
		}

}
/////////////////////////////////////////////////////////
void show_bat75(void)//
{
	unsigned char i;
	
//! clr_bat();
	place_in_ram(0, 0, 3, 13);
	send_command(0x5C);//Write RAM Command (5Ch)
	

	for(i = 0; i < 13; i++)//Y_len
		{	
		
			send_8pixels(pgm_read_byte_near(bat75_set[0][i]));
			send_8pixels(pgm_read_byte_near(bat75_set[0][i]+1));
			send_8pixels(pgm_read_byte_near(bat75_set[0][i]+2));
		}

}

void show_bat50(void)//
{
	unsigned char i;
	
//! clr_bat();
	place_in_ram(0, 0, 3, 13);
	send_command(0x5C);//Write RAM Command (5Ch)
	

	for(i = 0; i < 13; i++)//Y_len
		{	
		
			send_8pixels(pgm_read_byte_near(bat50_set[0][i]));
			send_8pixels(pgm_read_byte_near(bat50_set[0][i]+1));
			send_8pixels(pgm_read_byte_near(bat50_set[0][i]+2));
		}

}

void show_bat25(void)//
{
	unsigned char i;
	
//! clr_bat();
	place_in_ram(0, 0, 3, 13);
	send_command(0x5C);//Write RAM Command (5Ch)
	

	for(i = 0; i < 13; i++)//Y_len
		{	
		
			send_8pixels(pgm_read_byte_near(bat25_set[0][i]));
			send_8pixels(pgm_read_byte_near(bat25_set[0][i]+1));
			send_8pixels(pgm_read_byte_near(bat25_set[0][i]+2));
		}

}

void show_bat0(void)//  Батарейка 0% полный разряд
{
	unsigned char i;
	
//! clr_bat();
	place_in_ram(0, 0, 3, 13);
	send_command(0x5C);//Write RAM Command (5Ch)
	

	for(i = 0; i < 13; i++)//Y_len
		{	
		
			send_8pixels(pgm_read_byte_near(bat0_set[0][i]));
			send_8pixels(pgm_read_byte_near(bat0_set[0][i]+1));
			send_8pixels(pgm_read_byte_near(bat0_set[0][i]+2));
		}

}
///////////////////////

void clr_bat(void)//////Очистить поле батарейки
{
	unsigned char i;
	
	place_in_ram(0, 0, 3, 13);
	send_command(0x5C);//Write RAM Command (5Ch)
	

	for(i = 0; i < 13; i++)//Y_len
		{	
		
			send_8pixels(0);
			send_8pixels(0);
			send_8pixels(0);
		}

}
///////////////////
void draw_dline(void)  //// Рисование длинной линии отделяющей нижнюю строку
{

	unsigned char i;
	
	place_in_ram(0, 45, 36, 1);
	send_command(0x5C);//Write RAM Command (5Ch)
	

	for(i = 0; i < 6; i++)//Y_len
		{
		
			send_8pixels(0xff);
			send_8pixels(0xff);
			send_8pixels(0xff);
			send_8pixels(0xff);
			send_8pixels(0xff);
			send_8pixels(0xff);
		}
}

void draw_hline(void)   /// Рисовать линии вертикальные  разбивки нижней строки
{
	unsigned char i;
	
	place_in_ram(25, 46, 1, 18);
	send_command(0x5C);//Write RAM Command (5Ch)

	for(i = 0; i < 18; i++)//Y_len
		{
		send_8pixels(0x08);
		}
		
	place_in_ram(15, 46, 1, 18);
	send_command(0x5C);//Write RAM Command (5Ch)

	for(i = 0; i < 18; i++)//Y_len
		{
		send_8pixels(0x08);
		}
place_in_ram(11, 46, 1, 18);
	send_command(0x5C);//Write RAM Command (5Ch)

	for(i = 0; i < 18; i++)//Y_len
		{
		send_8pixels(0x08);
		}
place_in_ram(3, 46, 1, 18);
	send_command(0x5C);//Write RAM Command (5Ch)

	for(i = 0; i < 18; i++)//Y_len
		{
		send_8pixels(0x08);
		}	
}


//---------------------------------------------------------------------------------------
void display_driver(void)
{
//	if ((new_buffer == 1) && (get_flag(FLAG_FRAME_SHOW)))
	{
//		show_all();
//		new_buffer = 0;
	}
}

//---------------------------------------------------------------------------------------
/*void show_all(void)
{
	if(get_flag(FLAG_CH_NUM))
		show_num_buffer();
}

*/
//---------------------------------------------------------------------------------------
void show_dot(unsigned char num)
{
			print_dot(DOT_PICT_INVIS);
		    show_video(11, 33, 1, 9);////55
			print_dot(DOT_PICT_INVIS);///INVIS
		    show_video(7, 33, 1, 9);

	switch(num)
	{
	case DIM_MKM:
		
	
			
		//else
	//	{
			//print_dot(DOT_PICT_INVIS);
		   // show_video(20, 55, 1, 9);
			print_dot(DOT_PICT_VIS);
			show_video(7, 33, 1, 9);
			

	//	}
		break;
		
	case DIM_MM:
	
		//print_dot(DOT_PICT_INVIS);///INVIS
		//show_video(16, 55, 1, 9);
		print_dot(DOT_PICT_VIS);
		show_video(11, 33, 1, 9);
		

		
		
	}
}

////---------------------------------------------------------------------------------------
void show_inv_dot(unsigned char num)
{
			print_ndot(DOT_PICT_INVIS);
		    show_video(11, 33, 1, 9);////55
			print_ndot(DOT_PICT_INVIS);///INVIS
		    show_video(7, 33, 1, 9);

	switch(num)
	{
	case DIM_MKM:
		
	
			
		//else
	//	{
			//print_dot(DOT_PICT_INVIS);
		   // show_video(20, 55, 1, 9);
			print_ndot(DOT_PICT_VIS);
			show_video(7, 33, 1, 9);
			

	//	}
		break;
		
	case DIM_MM:
	
		//print_dot(DOT_PICT_INVIS);///INVIS
		//show_video(16, 55, 1, 9);
		print_ndot(DOT_PICT_VIS);
		show_video(11, 33, 1, 9);
		

		
		
	}
}
//---------------------------------------------------------------------------------------
void show_inv_num_buffer(unsigned char clr)
{
	unsigned int i, j;

	if (clr == 0)
{

		for(i = 0; i < 4; i++)
		{
			place_in_ram(4+i*4, 0, 4, 42);     //// X Y len len 
			send_command(0x5C);//Write RAM Command (5Ch)
			if( num_buffer[i] != 10)
				for(j = 0; j < 42; j++)//Y
				{
					send_8pixels(~(pgm_read_byte_near(number_set[num_buffer[i]][j])));
					send_8pixels(~(pgm_read_byte_near(number_set[num_buffer[i]][j]+1)));
					send_8pixels(~(pgm_read_byte_near(number_set[num_buffer[i]][j]+2)));
					
					send_8pixels(~(0));
				}
			else
			{
				for(j = 0; j < 42; j++)//Y
				{
					send_8pixels(~(0));
					send_8pixels(~(0));
					send_8pixels(~(0));
					send_8pixels(~(0));
				}
			}
		}
	}
	
	else   //// очистка поля диспеля
	{
	
	for(i = 0; i < 4; i++)
		{
			place_in_ram(4+i*4, 0, 4, 42);     //// X Y len len 
			send_command(0x5C);//Write RAM Command (5Ch)
			
				for(j = 0; j < 42; j++)//Y
				{
					send_8pixels(0);
					send_8pixels(0);
					send_8pixels(0);
					send_8pixels(0);
					//send_8pixels(0);
				}
	
	
	}
	}
	
}
//---------------------------------------------------------------------------------------
void show_num_buffer(void)
{
	unsigned int i, j;


		for(i = 0; i < 4; i++)
		{
			place_in_ram(4+i*4, 0, 3, 42);     //// X Y len len 
			send_command(0x5C);//Write RAM Command (5Ch)
			if(num_buffer[i] != 10)
				for(j = 0; j < 42; j++)//Y
				{
					send_8pixels(pgm_read_byte_near(number_set[num_buffer[i]][j]));
					send_8pixels(pgm_read_byte_near(number_set[num_buffer[i]][j]+1));
					send_8pixels(pgm_read_byte_near(number_set[num_buffer[i]][j]+2));
					
					
				}
			else
			{
				for(j = 0; j < 42; j++)//Y
				{
					send_8pixels(0);
					send_8pixels(0);
					send_8pixels(0);
					
				}
			}
		}
//	}
}
//////////////////////////////////////////////

void draw_dachnum (unsigned char num, unsigned char pos)  //// Вывести в нижнюю строку тип датчика сокращенный


{
unsigned char s0=0,s1=0,s2=0,s3=0,s4=0,s5=0,s6=0,s7=0,s8=0,j, xp=0, yp=0;


switch (num) 
	{		/// Тип Датчика 		
	case 1: s0=1; s1=0; s2=45; s3=6; s4=48; s5=2; s6=29; s7=10; s8=10; break; 	//10-6/2Т
	case 2: s0=5; s1=45; s2=1; s3=0; s4=48; s5=2; s6=29; s7=10; s8=10; break;	//5-10/2Т
	case 3: s0=2; s1=47; s2=5; s3=45; s4=1; s5=2; s6=48; s7=2; s8=29;  break;  //2.5-12/2Т
	
	case 4: s0=2; s1=47; s2=5; s3=29; s4=45; s5=1; s6=2; s7=48; s8=2;  break; //2.5Т-12/2
	case 5: s0=5; s1=29; s2=45; s3=1; s4=2; s5=48; s6=2; s7=10; s8=10;  break; //5Т-12/2
	case 6: s0=2; s1=47; s2=5; s3=45; s4=1; s5=2; s6=48; s7=2; s8=11;  break; //2.5-12/2А
	
	case 7: s0=1; s1=47; s2=2; s3=45; s4=2; s5=0; s6=48; s7=2; s8=11;  break; //1.2-20/2А
	case 8: s0=1; s1=47; s2=2; s3=5; s4=45; s5=21; s6=2; s7=0; s8=10;  break; //1.25-К20
	case 9: s0=1; s1=47; s2=2; s3=5; s4=45; s5=26; s6=2; s7=0; s8=10;	 break;  //1.25-П20
				
	
	}
switch (pos)
	{
	case 0: xp=16; yp=48; break;//// самая нижняя строчка
	case 1: xp=13; yp=0; break; /// первая 
	case 2: xp=13; yp=16; break;
	case 3: xp=13; yp=32; break;
	case 4: xp=13; yp=48; break; /// четвертая
	}

	
	place_in_ram(xp, yp, 9, 15);
	send_command(0x5C);//Write RAM Command (5Ch)
	

	for(j = 0; j < 15; j++)//Y_len
		{
	
		send_8pixels(pgm_read_byte_near(small_num_set[s8][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s7][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s6][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s5][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s4][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s3][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s2][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s1][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s0][j]));
		
}
}


void draw_nastrn (unsigned char num)   //// вывести в нижнюю строку настройку 3 символа Н-1....Н-9 ПЭТ


{
unsigned char s0=0,s1=0,s2=0,j, xp=0, yp=0;


switch (num) 
	{		/// Номер настройки 		
	case 1: s0=24; s1=45; s2=1;  break; 	
	case 2: s0=24; s1=45; s2=2;  break;
	case 3: s0=24; s1=45; s2=3;    break; 
	
	case 4: s0=24; s1=45; s2=4;   break;
	case 5: s0=24; s1=45; s2=5;  break;
	case 6: s0=24; s1=45; s2=6;  break; 
	
	case 7: s0=24; s1=45; s2=7;  break;
	case 8: s0=24; s1=45; s2=8;  break; 
	case 9: s0=24; s1=45; s2=9;   break; 
	
	case 10: s0=26; s1=40; s2=29;   break;	/// ПЭТ		
	
	}

	xp=12; yp=48;//// самая нижняя строчка

	place_in_ram(xp, yp, 3, 15);
	send_command(0x5C);//Write RAM Command (5Ch)

	for(j = 0; j < 15; j++)//Y_len
		{
		
		send_8pixels(pgm_read_byte_near(small_num_set[s2][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s1][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s0][j]));	
}

}

void draw_samp(unsigned char amp)  /// Вывести усиление в нижнюю строку
{
unsigned char s1=0,s2=0,j, xp=0, yp=0;
xp=0; yp=48;//// самая нижняя строчка
s1=	amp/10;
while (!(amp < 10))
{
amp = amp - 10;
}
s2 = amp;

	place_in_ram(xp, yp, 3, 15);
	send_command(0x5C);//Write RAM Command (5Ch)
	

	for(j = 0; j < 15; j++)//Y_len
		{
		
		send_8pixels(pgm_read_byte_near(small_num_set[s2][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s1][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[52][j]));	
		}
}

void draw_smem(unsigned char file, unsigned int frees, unsigned char typefile)  /// Вывести состояние памяти в нижнюю строчку -----------------------------------------
{
unsigned char s0=0,s1=0,s2=0, j,i, xp=0, yp=0;
xp=8; yp=48;//// самая нижняя строчка

file = file+1; //// Отображать номера файлов с 1 а не с 0 как было раньше 

if (file == 100)
	{
				put_int_to_snum_buffer (frees);
										
										place_in_ram(xp-1, yp, 4, 15);
										send_command(0x5C);//Write RAM Command (5Ch)
										

										for(j = 0; j < 15; j++)//Y_len
												{
												send_8pixels(pgm_read_byte_near(small_num_set[53][j]));
												send_8pixels(pgm_read_byte_near(small_num_set[0][j]));
												send_8pixels(pgm_read_byte_near(small_num_set[0][j]));
												send_8pixels(pgm_read_byte_near(small_num_set[1][j]));

												}




										for(i = 0; i < 3; i++)
										{
											place_in_ram(4+i*1, yp, 1, 15);     //// X Y len len 
											send_command(0x5C);//Write RAM Command (5Ch)
											if(snum_buffer[i] != 10)
											
											
												for(j = 0; j < 15; j++)//Y
											
												{	
													
													
													send_8pixels(pgm_read_byte_near(small_num_set[snum_buffer[i]][j]));
												}
												
											else
											{
												for(j = 0; j < 15; j++)//Y
												{//
													send_8pixels(0);
												}
											}
									
										}
										
	}			

else
//xp=8; yp=48;//// самая нижняя строчка

{

s0 = file/10;   /// отобразить выбранный файл памяти 0-99

while (!(file < 10))
{
file = file - 10;
}
s1 = file;
s2 = 53;
put_int_to_snum_buffer (frees);


	if(!(typefile<=3))  //// длинна файла меньще 10000 ячеек   то формат отображения 00*0000

	{

		place_in_ram(xp, yp, 3, 15);
		send_command(0x5C);//Write RAM Command (5Ch)
		

		for(j = 0; j < 15; j++)//Y_len
				{
				
				send_8pixels(pgm_read_byte_near(small_num_set[s2][j]));
				send_8pixels(pgm_read_byte_near(small_num_set[s1][j]));
				send_8pixels(pgm_read_byte_near(small_num_set[s0][j]));

				}




		for(i = 0; i < 4; i++)
		{
			place_in_ram(4+i*1, yp, 1, 15);     //// X Y len len 
			send_command(0x5C);//Write RAM Command (5Ch)
			if(snum_buffer[i] != 10)
			
			
				for(j = 0; j < 15; j++)//Y
			
				{	
					
					
					send_8pixels(pgm_read_byte_near(small_num_set[snum_buffer[i]][j]));
				}
				
			else
			{
				for(j = 0; j < 15; j++)//Y
				{//
					send_8pixels(0);
				}
			}
	
		}

	}
	
	else  ///////  Файла больше 10000 ячеек 30000 , 15000 тыщь  то формат 0*00000
	
	{
	
		
		place_in_ram((xp+1), yp, 2, 15);
		send_command(0x5C);//Write RAM Command (5Ch)
		

		for(j = 0; j < 15; j++)//Y_len
				{
				
				send_8pixels(pgm_read_byte_near(small_num_set[s2][j]));
				send_8pixels(pgm_read_byte_near(small_num_set[s1][j]));
				//send_8pixels(pgm_read_byte_near(small_num_set[s0][j]));

				}




		for(i = 0; i < 5; i++)
		{
			place_in_ram(4+i*1, yp, 1, 15);     //// X Y len len 
			send_command(0x5C);//Write RAM Command (5Ch)
			if(snum_buffer[i] != 10)
			
			
				for(j = 0; j < 15; j++)//Y
			
				{	
					
					
					send_8pixels(pgm_read_byte_near(small_num_set[snum_buffer[i]][j]));
				}
				
			else
			{
				for(j = 0; j < 15; j++)//Y
				{//
					send_8pixels(0);
				}
			}
	
		}

	}



}
}

//===================================================================================================================================


//---------------------------------------------------------------------------------------
void show_snum_buffer(void)
{
	unsigned int i, j;

		for(i = 0; i < 4; i++)
		{
			place_in_ram(28+i*1, 48, 1, 15);     //// X Y len len 
			send_command(0x5C);//Write RAM Command (5Ch)
			if(snum_buffer[i] != 10)
				for(j = 0; j < 15; j++)//Y
			
				{
	
					send_8pixels(pgm_read_byte_near(small_num_set[snum_buffer[i]][j]));
					
				}
				
			else
			{
				for(j = 0; j < 15; j++)//Y
				{//
					send_8pixels(0);
				}
			}
	
		}

}



void show_msmin(unsigned char num)
{

place_in_ram(26, 50, 2, 15);
	send_command(0x5C);//Write RAM Command (5Ch)
unsigned char j;	

	for(j = 0; j < 15; j++)//Y_len
		{
		
		
		
		send_8pixels(pgm_read_byte_near(small_num_set[49][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[50][j]));
}

}

//---------------------------------------------------------------------------------------
void print_number(unsigned char num)
{
	unsigned char i;

	if(num != 10)
		for(i = 0; i < 50; i++)
		{
			video_ram[i][0] = pgm_read_byte_near(number_set[num][i]);
			video_ram[i][1] = pgm_read_byte_near(number_set[num][i]+1);
			video_ram[i][2] = pgm_read_byte_near(number_set[num][i]+2);
		}
	else
		clear_ram(50);
}

//---------------------------------------------------------------------------------------
void print_dot(unsigned char num)
{
	unsigned char i;

	for(i = 0; i < 9; i++)
	{
		video_ram[i][0] = pgm_read_byte_near(dot_set[num][i]);
	}
}
//-------------------------------------------------
void print_ndot(unsigned char num)
{
	unsigned char i;

	for(i = 0; i < 9; i++)
	{
		video_ram[i][0] = (~(pgm_read_byte_near(dot_set[num][i])));
	}
}

//---------------------------------------------------------------------------------------
void clear_ram(unsigned char num)
{
	unsigned char i;

	for(i = 0; i < num; i +=5)
	{
		video_ram[i][0] = video_ram[i][1] = video_ram[i][2] = video_ram[i][3] = 0x00;
		video_ram[i+1][0] = video_ram[i+1][1] = video_ram[i+1][2] = video_ram[i+1][3] = 0x00;
		video_ram[i+2][0] = video_ram[i+2][1] = video_ram[i+2][2] = video_ram[i+2][3] = 0x00;
		video_ram[i+3][0] = video_ram[i+3][1] = video_ram[i+3][2] = video_ram[i+3][3] = 0x00;
		video_ram[i+4][0] = video_ram[i+4][1] = video_ram[i+4][2] = video_ram[i+4][3] = 0x00;
	}
}

//---------------------------------------------------------------------------------------
void show_video(unsigned char x_pos, unsigned char  y_pos, unsigned char  x_len, unsigned char  y_len)
{
	unsigned char i, j;

	send_command(0x15);send_data(0x1C+(x_pos << 1));send_data(0x1C+((x_pos+x_len)<<1)-1);//Set Column Address (15h) столбцы x
	send_command(0x75);send_data(y_pos);send_data(y_pos + y_len-1);//Set Row Address (75h) строки y
	send_command(0x5C);//Write RAM Command (5Ch)
	for(i = 0; i < y_len; i++)//Y
		for(j = 0; j < x_len; j++)//X
			send_8pixels(video_ram[i][j]);
	/*for(i = 0; i < x_len*y_len; i ++)
		send_8pixels(0x0F);*/
}

//---------------------------------------------------------------------------------------
void place_in_ram(unsigned char x0, unsigned char  y0, unsigned char  x1, unsigned char  y1)
{
//	send_command(0x15);send_data(0x1C+(x_pos << 1));send_data(0x1C+((x_pos+x_len)<<1)-1);//Set Column Address (15h) столбцы x
//	send_command(0x75);send_data(y_pos);send_data(y_pos + y_len-1);//Set Row Address (75h) строки y
	send_command(0x15);  // счетчик тетрад
		send_data(x0);
		send_data(x1); //Set Column Address (15h) столбцы x
		
	send_command(0x75);
		send_data(y0);
		send_data(y1); //Set Row Address (75h) строки y

}

//---------------------------------------------------------------------------------------
void oled_on(void)
{
	unsigned char i;
	PORTJ &= 0x1F;//RST = 0
	display_delay(600);//задержка 10 мс
	PORTJ |= 0x20;//RST = 1

	send_command(0xFD);  //Command Lock
		send_data(0x12); 
	send_command(0xAE);	 //Set Display ON/OFF (AFh/AEh)
	
//	send_command(0xB3);  //Set Front Clock Divider / Oscillator Frequency (B3h)
//		send_data(0x91); // 0x91   не трогать!

	send_command(0xCA);  //Set Multiplex Ratio (CAh)  !!!!!!!!! тоже неплохо
		send_data(0x3F); //0x3F 0x40

	send_command(0xA2);  //Set Display Offset (A2h)
		send_data(0x00);
	send_command(0xA1);  //Set Display Start Line (A1h)
		send_data(0x00
		);

	send_command(0xA0);  //Set Re-map & Dual COM Line Mode (A0h) оно !!!!!!!!!!
		send_data(0x06); // 0x00 2b (0x02) - адрес слева на право A5 - черезстрочная развертка
		send_data(0x11); // 0x11   B4 - ставть обязательно, без него неравномерная подстветка
		
	send_command(0xB5);  //Set GPIO
		send_data(0x00);
	send_command(0xAB);  //Set Function selection (ABh)
		send_data(0x01); // A[0]=1b, Enable internal VDD regulator [reset] 
		
	send_command(0xB4);  //Enable External VSL
		send_data(0xA0);
		send_data(0xFD);
	//BRIVAL(); ///
//	send_command(0xC1);  //Set Contrast Current (C1h) 9F
//		send_data(0xFF); // 256 steps for ISEG current [reset = 7Fh] 
//	send_command(0xC7);  //Master Contrast Current Control (C7h)
//	send_data(0x0F);  //!0x0F
	
	send_command(0x00);  //Enable GrayScale table
//	send_command(0xB8);
//		for (i=0;i<180;i=i+12){send_data(i);} //15 data bytes define Gray Scale
//	send_command(0xB9);  //Select Default Linear Gray Scale Table (B9h)

	
//	send_command(0xB1);  //Set Phase Length (B1h)
//		send_data(0xB1);
	
//	send_command(0xD1);  //Enhance Driving Scheme Capability
//		send_data(0xA2); //0x82
//		send_data(0x20);

	send_command(0xBB);  //Set Pre-charge voltage (BB)1F
		send_data(0x05); // 0x1F
		
	send_command(0xA9);
//	send_command(0xB6);  //Set Second Pre-charge Period
//		send_data(0x08); // 1000b 8 dclks [reset] 

	send_command(0xBE);  //Set V_COMH (BE) 07
		send_data(0x07);
	send_command(0xA6);  //Display Mode Normal - весь дисплей черный
//	send_command(0xA5);  //Entire Display ON - весь дисплей светлый
	//send_command(0xA7);  //A7h = Inverse Display
	cls();
	send_command(0xAF);  //Set Display ON/OFF (AFh/AEh)
}

//---------------------------------------------------------------------------------------
void cls(void)//clear screen;
{
	unsigned int i;

	send_command(0x15);send_data(0x1C);send_data(0x5B);//Set Column Address (15h) столбцы x
	send_command(0x75);send_data(0x00);send_data(0x3F);//Set Row Address (75h) строки y
	send_command(0x5C);//Write RAM Command (5Ch)
	for(i = 0; i < 2048; i++)
	send_8pixels(0x00);
}

//---------------------------------------------------------------------------------------
void send_command(unsigned char com)
{
	display_io =1; // Признак передачи данных в дисплей
	PORTJ &= 0x3F;//SDC = 0
	PORTG |= 0x04;//WR = 1
	PORTA = com;
	PORTG &= 0xFB;//WR = 0
	display_io =0; // Признак передачи данных в дисплей
}

//---------------------------------------------------------------------------------------
void send_data(unsigned char data)
{
	display_io =1; // Признак передачи данных в дисплей
	PORTJ |= 0x40;//SDC = 1;
	PORTG |= 0x04;//WR = 1
	PORTA = data;
	PORTG &= 0xFB;//WR = 0
	display_io =0; // Признак передачи данных в дисплей
}

//---------------------------------------------------------------------------------------
void send_8pixels(unsigned char data)
{
	display_io =1; // Признак передачи данных в дисплей
	unsigned char tmp = 0;

	switch((data >> 2) & 0x03)
	{
	case 0x00: tmp = 0x00; break;
	case 0x01: tmp = 0x0F;	break;
	case 0x02: tmp = 0xF0;	break;
	case 0x03: tmp = 0xFF;	break;
	}
	PORTJ |= 0x40;//SDC = 1;
	PORTG |= 0x04;//WR = 1
	PORTA = tmp;
	PORTG &= 0xFB;//WR = 0
	switch(data & 0x03)
	{
	case 0x00: tmp = 0x00; break;
	case 0x01: tmp = 0x0F;	break;
	case 0x02: tmp = 0xF0;	break;
	case 0x03: tmp = 0xFF;	break;
	}
	PORTG |= 0x04;//WR = 1
	PORTA = tmp;
	PORTG &= 0xFB;//WR = 0
	switch((data >> 6) & 0x03)
	{
	case 0x00: tmp = 0x00; break;
	case 0x01: tmp = 0x0F;	break;
	case 0x02: tmp = 0xF0;	break;
	case 0x03: tmp = 0xFF;	break;
	}
	PORTG |= 0x04;//WR = 1
	PORTA = tmp;
	PORTG &= 0xFB;//WR = 0
	switch((data >> 4) & 0x03)
	{
	case 0x00: tmp = 0x00; break;
	case 0x01: tmp = 0x0F;	break;
	case 0x02: tmp = 0xF0;	break;
	case 0x03: tmp = 0xFF;	break;
	}
	PORTG |= 0x04;//WR = 1
	PORTA = tmp;
	PORTG &= 0xFB;//WR = 0
	
	display_io =0; // Признак передачи данных в дисплей
}

//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
void display_delay(unsigned int num)
{
	volatile unsigned int i;
	for(i = 0; i < num; i++);
}

////////////////////MEMO/////////////////

void show_hicons(unsigned char num)
{

				unsigned char i;
		if (num == 0)		
				{
				place_in_ram(20, 0, 12, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				

				for(i = 0; i < 16; i++)//Y_len
					{	
					
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
					}

				}
				
				else
				
				{
				
				
				place_in_ram(20, 0, 12, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				num = num-1;

				for(i = 0; i < 16; i++)//Y_len
					{	
					
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+1));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+2));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+3));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+4));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+5));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+6));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+7));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+8));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+9));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+10));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+11));

						
						
					}
				}	
				

}



void show_mpos(unsigned char num, unsigned char xmm, unsigned char ymm)
{

				unsigned char i;
		if (num == 0)		
				{
				place_in_ram(xmm, ymm, 12, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				

				for(i = 0; i < 16; i++)//Y_len
					{	
					
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
				
					
					}

				}
				
				else
				
				{
				
				
				place_in_ram(xmm, ymm, 12, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				num = num-1;

				for(i = 0; i < 16; i++)//Y_len
					{	
					
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+1));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+2));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+3));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+4));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+5));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+6));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+7));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+8));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+9));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+10));
						send_8pixels(pgm_read_byte_near(memo_hicon[num][i]+11));

						
						
					}
				}	
				

}

void show_wpos(unsigned char num, unsigned char xmm, unsigned char ymm)
// рисует строчку меню на экране
{
	unsigned char i;
		if (num == 0)		
				{
				place_in_ram(xmm, ymm, 19, 12);
				send_command(0x5C);//Write RAM Command (5Ch)
				for(i = 0; i < 12; i++)//Y_len
					{	
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
					}
				}		
				else		
				{

				place_in_ram(xmm, ymm, 19, 12);
				send_command(0x5C);//Write RAM Command (5Ch)
				num = num-1;

				for(i = 0; i < 12; i++)//Y_len
					{	
					
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+1));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+2));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+3));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+4));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+5));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+6));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+7));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+8));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+9));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+10));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+11));	
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+12));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+13));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+14));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+15));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+16));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+17));
						send_8pixels(pgm_read_byte_near(memo_wicon[num][i]+18));
					}
				}	
				
}

void show_twpos(unsigned char num, unsigned char xmm, unsigned char ymm) //// Рисовать надпись в 25 байт шириной 200точек
{
unsigned char i=0;
				place_in_ram(xmm, ymm, 25, 12);
				send_command(0x5C);//Write RAM Command (5Ch)
				num = num-1;

				for(i = 0; i < 12; i++)//Y_len
					{	
					
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+1));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+2));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+3));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+4));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+5));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+6));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+7));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+8));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+9));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+10));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+11));
						
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+12));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+13));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+14));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+15));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+16));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+17));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+18));
						
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+19));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+20));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+21));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+22));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+23));
						send_8pixels(pgm_read_byte_near(memo_ticon[num][i]+24));
						
						
					}
					

}

////////////////////////////////////////////////////////////////////////////////////////////////

void show_wposx(unsigned char num, unsigned char xmm, unsigned char ymm)

	
{

				unsigned char i;
		if (num == 0)		
				{
				place_in_ram(xmm, ymm, 21, 12);
				send_command(0x5C);//Write RAM Command (5Ch)
				

				for(i = 0; i < 12; i++)//Y_len
					{	
					
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						
						send_8pixels(0);
						send_8pixels(0);
						
				
					
					}

				}
				
				else
				
				{
				
				
				place_in_ram(xmm, ymm, 21, 12);
				send_command(0x5C);//Write RAM Command (5Ch)
				num = num-1;

				for(i = 0; i < 12; i++)//Y_len
					{	
					
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+1));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+2));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+3));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+4));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+5));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+6));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+7));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+8));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+9));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+10));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+11));
						
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+12));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+13));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+14));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+15));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+16));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+17));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+18));
						
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+19));
						send_8pixels(pgm_read_byte_near(memo_wiconx[num][i]+20));

						
						
					}
				}	
				

}

////////////////////////////////////////////////////////////////////////////////////////////////




void show_upos(unsigned char num, unsigned char xmm, unsigned char ymm)

{

				unsigned char i;
		if (num == 0)		
				{
				place_in_ram(xmm, ymm, 9, 12);
				send_command(0x5C);//Write RAM Command (5Ch)
				

				for(i = 0; i < 12; i++)//Y_len
					{	
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);			
					}

				}
				
				else
				
				{
				place_in_ram(xmm, ymm, 9, 12);
				send_command(0x5C);//Write RAM Command (5Ch)
				num = num-1;

				for(i = 0; i < 12; i++)//Y_len
					{	
					
						send_8pixels(pgm_read_byte_near(memo_wmc[num][i]));
						send_8pixels(pgm_read_byte_near(memo_wmc[num][i]+1));
						send_8pixels(pgm_read_byte_near(memo_wmc[num][i]+2));
						send_8pixels(pgm_read_byte_near(memo_wmc[num][i]+3));
						send_8pixels(pgm_read_byte_near(memo_wmc[num][i]+4));
						send_8pixels(pgm_read_byte_near(memo_wmc[num][i]+5));
						send_8pixels(pgm_read_byte_near(memo_wmc[num][i]+6));
						send_8pixels(pgm_read_byte_near(memo_wmc[num][i]+7));
						send_8pixels(pgm_read_byte_near(memo_wmc[num][i]+8));						
					}
				}	
				

}

void show_rpos(unsigned char num, unsigned char xmm, unsigned char ymm)

	
{

				unsigned char i;
		if (num == 0)		
				{
				place_in_ram(xmm, ymm, 11, 12);
				send_command(0x5C);//Write RAM Command (5Ch)
				

				for(i = 0; i < 12; i++)//Y_len
					{	
					
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);
						send_8pixels(0);

					}

				}
				
				else
				
				{
				
				
				place_in_ram(xmm, ymm, 11, 12);
				send_command(0x5C);//Write RAM Command (5Ch)
				num = num-1;

				for(i = 0; i < 12; i++)//Y_len
					{	
					
						send_8pixels(pgm_read_byte_near(memo_ricon[num][i]));
						send_8pixels(pgm_read_byte_near(memo_ricon[num][i]+1));
						send_8pixels(pgm_read_byte_near(memo_ricon[num][i]+2));
						send_8pixels(pgm_read_byte_near(memo_ricon[num][i]+3));
						send_8pixels(pgm_read_byte_near(memo_ricon[num][i]+4));
						send_8pixels(pgm_read_byte_near(memo_ricon[num][i]+5));
						send_8pixels(pgm_read_byte_near(memo_ricon[num][i]+6));
						send_8pixels(pgm_read_byte_near(memo_ricon[num][i]+7));
						send_8pixels(pgm_read_byte_near(memo_ricon[num][i]+8));
						send_8pixels(pgm_read_byte_near(memo_ricon[num][i]+9));
						send_8pixels(pgm_read_byte_near(memo_ricon[num][i]+10));
					
					}
				}	
				

}



void menu_cursor(unsigned char pos)
{
unsigned char xmm =0,ymm =0, st =0;
switch(pos)
	{
	case 1: xmm = 18; 	ymm=0;	break;  /// для меню режимов
	case 2: xmm = 18;	ymm=20;	break;
	case 3: xmm = 18;	ymm=40;	break;
	case 4: xmm = 4;	ymm=0;	break;
	case 5: xmm = 4;	ymm=20;	break;
	case 6: xmm = 4;	ymm=40;	break;
	
	case 7: xmm = 11;	ymm=16; st=1;	break;  /// для меню датчиков
	case 8: xmm = 11;	ymm=32; st=1; 	break;
	case 9: xmm = 11;	ymm=48; st=1;	break;
	
	case 10: xmm = 11;	ymm=16; st=1;	break;  /// для меню датчиков
	case 11: xmm = 11;	ymm=32; st=1; 	break;
	case 12: xmm = 11;	ymm=48; st=1;	break;
	
	case 13: xmm = 11;	ymm=16; st=1;	break;  /// для меню датчиков
	case 14: xmm = 11;	ymm=32; st=1; 	break;
	}
			unsigned char i;
			
				if (st==0)
				{
	/*			place_in_ram(18, 0, 1, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				for(i = 0; i < 16; i++)//Y_len
					{	
						send_8pixels(0);
					}
				place_in_ram(18, 20, 1, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				for(i = 0; i < 16; i++)//Y_len
					{	
						send_8pixels(0);
					}
				place_in_ram(18, 40, 1, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				for(i = 0; i < 16; i++)//Y_len
					{	
						send_8pixels(0);
					}
				place_in_ram(4, 0, 1, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				for(i = 0; i < 16; i++)//Y_len
					{	
						send_8pixels(0);
					}
				
				place_in_ram(4, 20, 1, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				for(i = 0; i < 16; i++)//Y_len
					{	
						send_8pixels(0);
					}
				place_in_ram(4, 40, 1, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				for(i = 0; i < 16; i++)//Y_len
					{	
						send_8pixels(0);
					}*/
				}
				else
				{
				place_in_ram(7, 16, 1, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				for(i = 0; i < 16; i++)//Y_len
					{	
						send_8pixels(0);
					}
				place_in_ram(7, 16, 1, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				for(i = 0; i < 16; i++)//Y_len
					{	
						send_8pixels(0);
					}
					place_in_ram(7, 48, 1, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				for(i = 0; i < 16; i++)//Y_len
					{	
						send_8pixels(0);
					}
				
				}
				
				
				place_in_ram(xmm, ymm, 1, 16);
				send_command(0x5C);//Write RAM Command (5Ch)
				

				for(i = 0; i < 16; i++)//Y_len
					{	
					
						send_8pixels(pgm_read_byte_near(menu_cursors[0][i]));
					}

}


void menu_wcursor(unsigned char pos,unsigned char mode)
{

unsigned char xmm =4,ymm =0, st =0,i;
switch(pos)
	{
	case 1: 
			ymm = 14;
			place_in_ram(xmm, ymm, 1, 12); 
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			place_in_ram((xmm + 22), ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
				
			place_in_ram(xmm, ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			place_in_ram((xmm + 22), ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}

			ymm = 28;
			place_in_ram(xmm, ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			place_in_ram((xmm + 22), ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			
			place_in_ram(xmm, ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			place_in_ram((xmm + 22), ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			
			ymm = 0;
	break;
	case 2: 
			ymm = 0;
			place_in_ram(xmm, ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			place_in_ram((xmm + 22), ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			
			place_in_ram(xmm, ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			place_in_ram((xmm + 22), ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}

			ymm = 28;
			place_in_ram(xmm, ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			place_in_ram((xmm + 22), ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			
			place_in_ram(xmm, ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			place_in_ram((xmm + 22), ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}

			ymm = 14;
	break; 
	case 3: 
			ymm = 0;
			place_in_ram(xmm, ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			place_in_ram((xmm + 22), ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			
			place_in_ram(xmm, ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			place_in_ram((xmm + 22), ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}

			ymm = 14;
			place_in_ram(xmm, ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			place_in_ram((xmm + 22), ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			
			place_in_ram(xmm, ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}
			place_in_ram((xmm + 22), ymm, 1, 12);
			send_command(0x5C);
			for(i = 0; i < 12; i++)	{send_8pixels(0);}

			ymm = 28;
	break;
	}


				place_in_ram(xmm, ymm, 1, 12);
				send_command(0x5C);//Write RAM Command (5Ch)

				for(i = 0; i < 12; i++)//Y_len
					{	
					
						send_8pixels(pgm_read_byte_near(menu_wcurs[0][i]+1));
					}
					
					
				place_in_ram((xmm + 22), ymm, 1, 12); 
				send_command(0x5C);//Write RAM Command (5Ch)
				
					for(i = 0; i < 12; i++)//Y_len
					{	
					
						send_8pixels(pgm_read_byte_near(menu_wcurs[0][i]));
					}
}



void show_dmenu(unsigned char dachik)  /// рисует меню датчиков  с прокруткой
{
cls();
	show_mpos(6,20,0); 
	
	switch (dachik)
	{
	case 1: draw_dachnum (1,2); draw_dachnum (2,3); draw_dachnum (3,4); break;
	case 2: draw_dachnum (1,2); draw_dachnum (2,3); draw_dachnum (3,4); break;
	case 3: draw_dachnum (1,2); draw_dachnum (2,3); draw_dachnum (3,4); break;
	case 4: draw_dachnum (4,2); draw_dachnum (5,3); draw_dachnum (6,4); break;
	case 5: draw_dachnum (4,2); draw_dachnum (5,3); draw_dachnum (6,4); break;
	case 6: draw_dachnum (4,2); draw_dachnum (5,3); draw_dachnum (6,4); break;
	case 7: draw_dachnum (7,2); draw_dachnum (8,3); break;
	case 8: draw_dachnum (7,2); draw_dachnum (8,3); break;
	}
	menu_cursor(dachik + 6);
}






void zapret()  /// сообщение запрет

{

BEEP(2);  /// запрет менять настройки первых 3 настроек
cls();
show_wpos(43,6,14);/// Файл заполнен !
_delay_ms (400);
BEEP(2);
_delay_ms (400);
BEEP(2);
_delay_ms (400);
BEEP(2);
cls();

}

void show_wmenu(unsigned char num)////// Нарисовать меню режимов измерения 
{
//! cls();
							// экраны меню с 1 по 5
	switch (num)
	{
	case 1: show_wpos(1,6,0); show_wpos(2,6,14); show_wpos(3,6,28); draw_dline(); menu_wcursor(1,0); draw_rezsel(1); break;
	case 2: show_wpos(1,6,0); show_wpos(2,6,14); show_wpos(3,6,28); draw_dline(); menu_wcursor(2,0); draw_rezsel(2); break;
	case 3: show_wpos(1,6,0); show_wpos(2,6,14); show_wpos(3,6,28); draw_dline(); menu_wcursor(3,0); draw_rezsel(3); break;
	case 4: show_wpos(0,6,28);show_wpos(4,6,0); show_wpos(5,6,14);	draw_dline(); menu_wcursor(1,0); draw_rezsel(4); break;
	case 5: show_wpos(0,6,28);show_wpos(4,6,0); show_wpos(5,6,14);	draw_dline(); menu_wcursor(2,0); draw_rezsel(5); break;
	}

}

void show_wnmenu(unsigned char num)////// Нарисовать меню Настроек и усиления  --  последний пунк СИСТЕМА
{
//! cls(); - из-за этого мигает меню

	switch (num)
	{
	case 1: show_wpos(7,6,0); show_wpos(8,6,14); show_wpos(9,6,28); draw_dline(); menu_wcursor(1,0); draw_nastrsel(1); break;
	case 2: show_wpos(7,6,0); show_wpos(8,6,14); show_wpos(9,6,28); draw_dline(); menu_wcursor(2,0); draw_nastrsel(2); break;
	case 3: show_wpos(7,6,0); show_wpos(8,6,14); show_wpos(9,6,28); draw_dline(); menu_wcursor(3,0); draw_nastrsel(3); break;
	
	case 4: show_wpos(10,6,0); show_wpos(11,6,14); show_wpos(12,6,28); draw_dline(); menu_wcursor(1,0); draw_nastrsel(4); break;
	case 5: show_wpos(10,6,0); show_wpos(11,6,14); show_wpos(12,6,28); draw_dline(); menu_wcursor(2,0); draw_nastrsel(5); break;
	case 6: show_wpos(10,6,0); show_wpos(11,6,14); show_wpos(12,6,28); draw_dline(); menu_wcursor(3,0); draw_nastrsel(6); break;
	
	case 7: show_wpos(13,6,0); show_wpos(14,6,14); show_wpos(15,6,28); draw_dline(); menu_wcursor(1,0); draw_nastrsel(7); break;
	case 8: show_wpos(13,6,0); show_wpos(14,6,14); show_wpos(15,6,28); draw_dline(); menu_wcursor(2,0); draw_nastrsel(8); break;
	case 9: show_wpos(13,6,0); show_wpos(14,6,14); show_wpos(15,6,28); draw_dline(); menu_wcursor(3,0); draw_nastrsel(9); break;
	


	case 10: show_wpos(16,6,0); show_wpos(6,6,14); show_wpos(38,6,28);  draw_dline(); menu_wcursor(1,0); draw_nastrsel(10); break;
	case 11: show_wpos(16,6,0); show_wpos(6,6,14); show_wpos(38,6,28);  draw_dline(); menu_wcursor(2,0); draw_nastrsel(11); break;
	case 12: show_wpos(16,6,0); show_wpos(6,6,14); show_wpos(38,6,28);  draw_dline(); menu_wcursor(3,0); draw_nastrsel(12); break;
	
	case 13: show_wpos(0,6,28);  show_wpos(40,6,0); show_wpos(42,6,14);  draw_dline(); menu_wcursor(1,0); draw_nastrsel(13); break; //// Яркость
	case 14: show_wpos(0,6,28);  show_wpos(40,6,0); show_wpos(42,6,14);  draw_dline(); menu_wcursor(2,0); draw_nastrsel(14); break; //// ЗВУК
	}

}


void show_MEMmenu(unsigned char num,unsigned char mf,unsigned int mp, unsigned char tf)////// Нарисовать меню ПАМЯТЬ//////////////////////////////////////////////
{
//! cls();

	switch (num)
	{
	case 1: show_wpos(28,6,0); show_wpos(29,6,14); show_wpos(30,6,28); draw_dline(); menu_wcursor(1,0); break;
	case 2: show_wpos(28,6,0); show_wpos(29,6,14); show_wpos(30,6,28); draw_dline(); menu_wcursor(2,0); break;
	case 3: show_wpos(28,6,0); show_wpos(29,6,14); show_wpos(30,6,28); draw_dline(); menu_wcursor(3,0); break;
	case 4: show_wpos(0,6,28); show_wpos(31,6,0); show_wpos(32,6,14);  draw_dline(); menu_wcursor(1,0); break;
	case 5: show_wpos(0,6,28); show_wpos(31,6,0); show_wpos(32,6,14);  draw_dline(); menu_wcursor(2,0); break;
	//case 6: show_wpos(31,6,0); show_wpos(32,6,14); show_wpos(33,6,28); draw_dline(); menu_wcursor(3,0); draw_smem(mf,mp,tf);  break;

	}
}


unsigned char show_FORMmenu(unsigned char num) ///// Нарисовать меню ФОРМАТИРОВАНЕ
{
unsigned char i=0;
//! cls();

	switch (num)
	{
	case 1: show_upos(1,11,0); show_upos(2,11,14); show_upos(3,11,28); draw_dline(); menu_wcursor(1,0);/* show_wpos(35,6,48);*/ i=1; break;
	case 2: show_upos(1,11,0); show_upos(2,11,14); show_upos(3,11,28); draw_dline(); menu_wcursor(2,0); /*show_wpos(35,6,48); */i=2; break;
	case 3: show_upos(1,11,0); show_upos(2,11,14); show_upos(3,11,28); draw_dline(); menu_wcursor(3,0); /*show_wpos(35,6,48); */i=5; break;
	
	case 4: show_upos(4,11,0); show_upos(5,11,14); show_upos(6,11,28); draw_dline(); menu_wcursor(1,0); /*show_wpos(35,6,48); */i=10; break;
	case 5: show_upos(4,11,0); show_upos(5,11,14); show_upos(6,11,28); draw_dline(); menu_wcursor(2,0); /*show_wpos(35,6,48); */i=20; break;
	case 6: show_upos(4,11,0); show_upos(5,11,14); show_upos(6,11,28); draw_dline(); menu_wcursor(3,0);/* show_wpos(35,6,48); */i=50; break;
	
	case 7: show_upos(0,11,14); show_upos(0,11,28); show_upos(7,11,0); draw_dline(); menu_wcursor(1,0); /*show_wpos(35,6,48);*/ i=100; break;

	}
return i;
}



void show_SELmenu(unsigned char num) /// Меню выбора файла
{

unsigned char mf=0,tf=0;
unsigned int mp=0;
	wfilename(num); /// Запись номера файла
	
	draw_dline();

	
	put_int_to_cnum_buffer(num+1); //// Вывести номер файла на дисплей  отображать с 1 файла
	show_cnum_buffer();
	
	tf=filetype();
	mf=filename(); /// узнать номер текущего файла
	mp=rfd(mf,tf); /// прочитать файл  и узнать количество ячеек свободных
	
	
	draw_smem(mf,mp,tf);  //// Отразить состояние памяти прибора	

}


void show_cmenu(unsigned char num) //// Меню калибровок
{
switch (num)
	{
	case 1: show_wpos(41,6,0); show_wpos(27,6,14); show_wpos(26,6,28);  draw_dline(); menu_wcursor(1,0); break;
	case 2: show_wpos(41,6,0); show_wpos(27,6,14); show_wpos(26,6,28);  draw_dline(); menu_wcursor(2,0); break;
	case 3: show_wpos(41,6,0); show_wpos(27,6,14); show_wpos(26,6,28);  draw_dline(); menu_wcursor(3,0); break;
	}
	draw_memoline (11,7,48);
}




void show_pepmenu(unsigned char num)////// Нарисовать меню Датчиков с прокруткой
{
//! cls();

	switch (num)
	{
	case 1: show_wpos(17,6,0); show_wpos(18,6,14); show_wpos(19,6,28); draw_dline(); menu_wcursor(1,0); draw_pepsel(1); break;
	case 2: show_wpos(17,6,0); show_wpos(18,6,14); show_wpos(19,6,28); draw_dline(); menu_wcursor(2,0); draw_pepsel(2); break;
	case 3: show_wpos(17,6,0); show_wpos(18,6,14); show_wpos(19,6,28); draw_dline(); menu_wcursor(3,0); draw_pepsel(3); break;
	
	case 4: show_wpos(20,6,0); show_wpos(21,6,14); show_wpos(22,6,28); draw_dline(); menu_wcursor(1,0); draw_pepsel(4); break;
	case 5: show_wpos(20,6,0); show_wpos(21,6,14); show_wpos(22,6,28); draw_dline(); menu_wcursor(2,0); draw_pepsel(5); break;
	case 6: show_wpos(20,6,0); show_wpos(21,6,14); show_wpos(22,6,28); draw_dline(); menu_wcursor(3,0); draw_pepsel(6); break;
	
	case 7: show_wpos(23,6,0); show_wpos(24,6,14); show_wpos(25,6,28); draw_dline(); menu_wcursor(1,0); draw_pepsel(7); break;
	case 8: show_wpos(23,6,0); show_wpos(24,6,14); show_wpos(25,6,28); draw_dline(); menu_wcursor(2,0); draw_pepsel(8); break;
	case 9: show_wpos(23,6,0); show_wpos(24,6,14); show_wpos(25,6,28); draw_dline(); menu_wcursor(3,0); draw_pepsel(9); break;
	
	}
	//cls();
}

void draw_caldatch (unsigned char num)  /// Вывести в нижнем поле тип датчика для режима калибровки 0
{
unsigned char y = 48,x=3,ampp=0;
	
	
switch (num)
	{
	case 1: show_wpos(17,0,y);	ampp=30;  break;
	case 2: show_wpos(18,0,y);	ampp=30;  break;
	case 3: show_wpos(19,0,y);	ampp=25;  break;
	
	case 4: show_wpos(20,0,y);	ampp=25;  break;
	case 5: show_wpos(21,0,y);	ampp=25;  break;
	case 6: show_wpos(22,0,y);	ampp=25;  break;
	
	case 7: show_wpos(23,0,y);	ampp=25; x=5;  break;  ///  
	case 8: show_wpos(24,0,y);	ampp=25; x=6;  break;
	case 9: show_wpos(25,0,y);	ampp=25; x=6;  break;
	
	}
		show_rpos(1,21,0);  /// Установите 
		show_rpos(2,21,14); /// ПЭП на ОБР. 
		show_rpos(x,21,28);  /// x=3 3.00ММ ; x=5 5.00MM ; x=6 20.0MM 
		
		show_rpos(4,21,y);  /// Калибр. 0 
	
	//cfgr_load(ampp,num); //// Загрузка Усиления и настроек аналоговой платы. ampp - усиление предустановленно для калибровки 0. num номер датчика 
}



void draw_batl(unsigned char vb)
{

switch (vb)
	{
	case 0: show_bat0();  break;
	case 1: show_bat25(); break;
	case 2: show_bat50(); break;
	case 3: show_bat75(); break;
	case 4: show_bat100(); break;
	case 5: show_batEXT(); break;
	
	}

}


void draw_pepsel(unsigned char num)     //// Вывод надписи ВЫБОР ТИПА ПЭП n ИЗ 9
{

unsigned char s0=13,s1=38,s2=12,s3=25 ,s4=27,s5=10,s6=29,s7=19,s8=26,s9=11,s10=10,s11=26,s12=40,s13=26,s14=10,  s15=0, s16=10,s17=19,s18=18,s19=10, s20=9,j, xp=0, yp=0;

s15=num;


xp=11; yp=48; /// четвертая
	place_in_ram(xp, yp, 21, 15);
	send_command(0x5C);//Write RAM Command (5Ch)
	for(j = 0; j < 15; j++)//Y_len
		{
		send_8pixels(pgm_read_byte_near(small_num_set[s20][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s19][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s18][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s17][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s16][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s15][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s14][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s13][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s12][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s11][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s10][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s9][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s8][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s7][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s6][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s5][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s4][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s3][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s2][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s1][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s0][j]));		
		}
}

void draw_nastrsel(unsigned char num)     //// Вывод надписи ВЫБОР НАСТРОЙКИ n ИЗ 11
{
unsigned char s0=13,s1=38,s2=12,s3=25,s4=27,s5=10, s6=24,s7=11,s8=28,s9=29,s10=27,s11=25,s12=20,s13=21,s14=19, s15=10,s16=0, s17=0,s18=10,s19=19, s20=18,s21=10,s22=1,s23=4,j, xp=0, yp=0;

switch(num)
{
case 1: s16=10 ; s17=1 ; break;
case 2: s16=10 ; s17=2 ; break;
case 3: s16=10 ; s17=3 ; break;
case 4: s16=10 ; s17=4 ; break;
case 5: s16=10 ; s17=5 ; break;
case 6: s16=10 ; s17=6 ; break;
case 7: s16=10 ; s17=7 ; break;
case 8: s16=10 ; s17=8 ; break;
case 9: s16=10 ; s17=9 ; break;
case 10: s16=1 ; s17=0 ; break;
case 11: s16=1 ; s17=1 ; break;
case 12: s16=1 ; s17=2 ; break;
case 13: s16=1 ; s17=3 ; break;
case 14: s16=1 ; s17=4 ; break;
}
xp=8; yp=48; /// четвертая
	place_in_ram(xp, yp, 24, 15);
	send_command(0x5C);//Write RAM Command (5Ch)
	
	for(j = 0; j < 15; j++)//Y_len
		{
		send_8pixels(pgm_read_byte_near(small_num_set[s23][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s22][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s21][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s20][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s19][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s18][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s17][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s16][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s15][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s14][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s13][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s12][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s11][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s10][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s9][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s8][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s7][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s6][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s5][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s4][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s3][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s2][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s1][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s0][j]));		
		}
}

void draw_rezsel(unsigned char num)     //// Вывод надписи ВЫБОР РЕЖИМА  n ИЗ 5
{
unsigned char s0=13,s1=38,s2=12,s3=25 ,s4=27,s5=10,s6=27,s7=16,s8=17,s9=19,s10=23,s11=11,s12=10, s13=19,s14=18,s15=23,s16=16,s17=27,s18=16,s19=24,s20=19,s21=20,s22=10, s23,s24=10,s25=19,s26=18,s27=10,s28=5, j, xp=0, yp=0;

s23=num;
xp=3; yp=48; /// четвертая
	place_in_ram(xp, yp, 29, 15);
	send_command(0x5C);//Write RAM Command (5Ch)
	
	for(j = 0; j < 15; j++)//Y_len
		{
		send_8pixels(pgm_read_byte_near(small_num_set[s28][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s27][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s26][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s25][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s24][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s23][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s22][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s21][j]));		
		send_8pixels(pgm_read_byte_near(small_num_set[s20][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s19][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s18][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s17][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s16][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s15][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s14][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s13][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s12][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s11][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s10][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s9][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s8][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s7][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s6][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s5][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s4][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s3][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s2][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s1][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s0][j]));		
		}

}

void draw_memoline (unsigned char num, unsigned char xp, unsigned char yp)//// Рисование линии подсказки ВВЕДИТЕ ЗНАЧЕНИЕ   СКОРОСТИ . УСИЛЕНИЯ, ТОЛЩИНЫ
{


unsigned char s0=13,s1=13,s2=16,s3=15,s4=19,s5=29,s6=16,s7=10,s8=18,s9=24,s10=11,s11=34,s12=16, s13=24,s14=19,s15=16,s16=10,s17=28,s18=21,s19=25,s20=27,s21=25,s22=28, s23=29 ,s24=19,  j;
unsigned long ic=0;
ic=timerab();
ic = ic/60;



switch (num)
{
	case 1: s17=28; s18=21; s19=25; s20=27; s21=25; s22=28; s23=29; s24=19;  break;
	case 2: s17=30; s18=28; s19=19; s20=22; s21=16; s22=24; s23=19; s24=42;  break;
	case 3: s17=29; s18=25; s19=22; s20=36; s21=19; s22=24; s23=38; s24=10;  break;
	case 4: s0=19,s1=18,s2=23,s3=16,s4=27,s5=39,s6=29,s7=16,  s8=10,s9=29,s10=25,s11=22,s12=36, s13=19,s14=24,s15=30, s16=10,  s17=25,s18=12,s19=27,s20=11,s21=18,s22=33, s23=11 ,s24=10;  break;
	
	
	
	case 5: s0=30,s1=18,s2=10,s3=29,s4=25,s5=22,s6=36,s7=19, s8=24 ,s9=25,s10=23,s11=16,   s12=27, s13=10,s14=30,s15=29, s16=45,  s17=1,s18=1,s19=1,s20=10,s21=10,s22=10, s23=10 ,s24=10;  break;   //// Ут-111
	case 6: s0=10,s1=10,s2=13,s3=16,s4=27,s5=28,s6=19,s7=42,     s8=10,s9=24    ,s10= verHA  ,s11= verHb  ,s12=47, s13=54,     s14=verSa,s15=verSb,   s16=10,s17=10,s18=10,s19=10,s20=10,s21=10,s22=10, s23=10 ,s24=10;  break; ///Версия Н01.S01
	
	case 7: s0=10,s1=18,s2=11,s3=13,s4=47,s5=10, s6=60, s7=10, s8= eeprom_read_byte(ZNUM3); s9= eeprom_read_byte(ZNUM2); s10= eeprom_read_byte(ZNUM1); s11= eeprom_read_byte(ZNUM0); s12=10,  s13=10,s14=10,s15=10, s16=10,  s17=10,s18=10,s19=10,s20=10,s21=10,s22=10, s23=10 ,s24=10;  break;
	case 8: digitbuf(ic); s0=10,s1=24,s2=11,s3=27,s4=11,s5=12,s6=25,s7=29,s8=21,s9=11,s10=10, s11=SHOW_NUM[4]; s12=SHOW_NUM[3]; s13=SHOW_NUM[2]; s14=SHOW_NUM[1]; s15=SHOW_NUM[0];s16=10;s17=34,s18=11,s19=28,s20=10,s21=10;s22=10; s23=10; s24=10;   break; /// Наработка 
	
	case 9: s17=42; s18=27; s19=21; s20=25; s21=28; s22=29; s23=19; s24=10;  break; 

	case 10: s0=23,s1=16,s2=24,s3=41,s4=10,s5=18,s6=13,s7=30,s8=21,s9=10,s10=10,s11=10,s12=10, s13=10,s14=10,s15=10,s16=10,s17=10,s18=10,s19=10,s20=10,s21=10,s22=10, s23=10 ,s24=10;break;  /// МЕНЮ ЗВУК
	
	case 11: s0=13,s1=38,s2=12,s3=25,s4=27,s5=10,s6=13,s7=19,s8=15,s9=11,s10=10,s11=21,s12=11, s13=22,s14=19,s15=12,s16=27,s17=25,s18=13,s19=21,s20=19,s21=10,s22=10, s23=10 ,s24=10;break;  /// ВЫБОР ВИДА КАЛИБРОВКИ
	
	case 12: s0=23,s1=16,s2=24,s3=41,s4=10,s5=26,s6=11,s7=23,s8=42,s9=29,s10=39,s11=10,s12=10, s13=10,s14=10,s15=10,s16=10,s17=10,s18=10,s19=10,s20=10,s21=10,s22=10, s23=10 ,s24=10;break;  /// МЕНЮ ПАМЯТЬ
	
	
	
	case 13: s0=13,s1=38,s2=32,s3=25,s4=15,s5=10,s6=21,s7=22,s8=10,s9=61,s10=10,s11=10,s12=10, s13=10,s14=10,s15=10,s16=10,s17=10,s18=10,s19=10,s20=10,s21=10,s22=10, s23=10 ,s24=10;break;  /// ВЫХОД _ КЛ -
}	/// Измерьте толщину образца



//xp=7; yp=48; /// четвертая



	place_in_ram(xp, yp, 25, 15);
	send_command(0x5C);//Write RAM Command (5Ch)
	
	for(j = 0; j < 15; j++)//Y_len
		{
		send_8pixels(pgm_read_byte_near(small_num_set[s24][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s23][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s22][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s21][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s20][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s19][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s18][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s17][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s16][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s15][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s14][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s13][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s12][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s11][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s10][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s9][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s8][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s7][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s6][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s5][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s4][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s3][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s2][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s1][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s0][j]));		
		}
}
void show_intro(void) ///  Отобразить меню СИСТЕМА         / Вывести Заставку на 3 секунды///

{
unsigned char io=0;
		rkey();
//!cls();
		BEEP(2);

		draw_memoline(8,0,42); // наработка
		draw_memoline(7,0,28); /// Серийный номер 44
		draw_memoline(6,1,14);  /// Версия Hxx.Sxx 28
		draw_memoline(5,0,0);  /// УТ-111 14


		while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
			{
			}
			_delay_ms (step_speedZ); //! 620
			key_find();
			_delay_ms (step_speedZ); //! 320


while (!(key_find()==keyenter))
{

	if (key_find()==keynastr) /// Выход по кнопке по которой вошли --- ждет когда ее отпустят тогда выход.
	{
	io=keynastr;
	
	while (io==keynastr)
	{
	_delay_ms(35);
	io=key_find();
	//BEEP(1);
	};
	_delay_ms(200);
	
	
	goto mp_out;
	}
}

		//_delay_ms(3000); 
		mp_out:;
		cls();
		BEEP(1);
}
void Draw_symbol(unsigned char* mass,unsigned char xm,unsigned char ym,unsigned char as,unsigned char bs,unsigned char color)
{
	unsigned char  screen_byte;
	unsigned long 	i=0, gg;
	xm=28+(xm<<1);
	ym<<=4;
//	as=1; // *2 = размер знакоместа горизонтальный в тетрадах *4 = бит
//	bs=12; // размер знакоместа вертикальный
	place_in_ram(xm, ym, xm+as, ym+bs);
	send_command(0x5C);		//Write RAM Command (5Ch)
	gg=as*4*bs;
	for(i = 0; i < gg; i++)//Y_len за раз выводим 2 пикселя
	{
		screen_byte=pgm_read_byte_near(&mass[i]);
		if (screen_byte&0x0F > color)screen_byte-=color; else screen_byte&=0xF0;	// вычитаем цвет
		if (screen_byte>>4 > 0) screen_byte-=color<<4;else screen_byte&=0x0F;     // вычитаем цвет
		PORTJ |= 0x40;				//SDC = 1;
		PORTG |= 0x04;				//WR = 1
		PORTA = screen_byte;	//j
		PORTG &= 0xFB;			//WR = 0
	}
}

void StrWriteLCD(char *str)
{
	unsigned int i=0;
	
	place_in_ram(0, 0, 32, 64);
	send_command(0x5C);//Write RAM Command (5Ch)
	
	while(str[i]!='/')
	{
		//Draw_symbol(str[i]);
		++i;
	}
}

void Show_Logo(void)///// Показать заставку луча                        ================================================================
{	
unsigned char i=0;
unsigned char j=0,xm,ym,as,bs,flag=0;;
cls();
//Draw_symbol(letter2,90,0,1,16,0);
//Draw_symbol(letter3,28,0,1,16,0);
  Draw_symbol(char_t,0,0,1,16,0);
 Draw_symbol(char_e,1,0,1,16,0);
 Draw_symbol(char_k,2,0,1,16,0);
 Draw_symbol(char_c,3,0,1,16,0);
  Draw_symbol(char_t,4,0,1,16,0);

Draw_symbol(fullchar,5,0,1,16,0x0F);
  
 Draw_symbol(char_t,6,0,1,16,0);
Draw_symbol(char_e,7,0,1,16,0);
 Draw_symbol(char_c,8,0,1,16,0);
  Draw_symbol(char_t,9,0,1,16,0);
  
Draw_symbol(fullchar,10,0,1,16,0x0F);

Draw_symbol(char_0,11,0,1,16,0);
Draw_symbol(char_1,12,0,1,16,0);
Draw_symbol(char_2,13,0,1,16,0);

Draw_symbol(fullchar,14,0,1,16,0x0F);

Draw_symbol(char_tn,15,0,1,16,0);
Draw_symbol(char_en,16,0,1,16,0);
Draw_symbol(char_cn,17,0,1,16,0);
Draw_symbol(char_tn,18,0,1,16,0);

Draw_symbol(fullchar,19,0,1,16,0x0F);

Draw_symbol(char_tn,20,0,1,16,0);
Draw_symbol(char_en,21,0,1,16,0);
Draw_symbol(char_kn,22,0,1,16,0);
Draw_symbol(char_cn,23,0,1,16,0);
Draw_symbol(char_tn,24,0,1,16,0);

//Draw_symbol(letter2,30,0,1,12,6);
//  Draw_symbol(letter2,28, 0,1,16,0);
//  Draw_symbol(letter2,28,16,1,16,0);
  Draw_symbol(fullchar,8,2,1,16,0);
  Draw_symbol(fullchar,9,2,1,16,7);//28+(9)*2
  
for(i=4;i<5;i++)
{
  Draw_symbol(gamma1,i*2,3,1,16,0); //28+i*2
  Draw_symbol(gamma2,i*2+1,3,1,16,0); 
}
  
				//StrWriteLCD("fff/");
				

					
_delay_ms(1000); //!1500

while (!(key_find()==keyenter))
{
/*
	Draw_symbol(fullchar,8,2,1,16,5);
	Draw_symbol(fullchar,9,2,1,16,5);//28+(9)*2
	_delay_ms(250);
	Draw_symbol(fullchar,8,2,1,16,10);
	Draw_symbol(fullchar,9,2,1,16,10);//28+(9)*2
	_delay_ms(250); 
		Draw_symbol(fullchar,8,2,1,16,0);
		Draw_symbol(fullchar,9,2,1,16,0);//28+(9)*2
	_delay_ms(250);
	
	Draw_symbol(fullchar,8,2,1,16,10);
	Draw_symbol(fullchar,9,2,1,16,10);//28+(9)*2
_delay_ms(250);
	Draw_symbol(fullchar,8,2,1,16,5);
	Draw_symbol(fullchar,9,2,1,16,5);//28+(9)*2
	_delay_ms(250);*/
	Draw_symbol(fullchar,8,2,1,16,0);
	Draw_symbol(fullchar,9,2,1,16,0);//28+(9)*2
	_delay_ms(250);
		Draw_symbol(fullchar,8,2,1,16,0x0F);
		Draw_symbol(fullchar,9,2,1,16,0x0F);//28+(9)*2
		_delay_ms(250);
	
	}; /// ждать кнопки ввод !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


send_command(0xA7);  //A7h = Inverse Display
//cls();

}

/////////////////////////////////////////
void draw_spsim (unsigned char type) /// Вывести символы D= ВП= НП= БУ=
{
unsigned char s0=0,s1=0,s2=0,j=0,ypos=0;
	switch (type)
	{
	case 1: s0=10; s1=55; s2=46 ; ypos=14; break; /// D=
	case 2: s0=13; s1=26; s2=46 ; ypos=14; break; /// ВП=
	case 3: s0=24; s1=26; s2=46 ; ypos=28; break; //  НП=
	case 4: s0=12; s1=30; s2=46 ; ypos=14; break; //  БУ=
	case 5: s0=58; s1=59; s2=46 ; ypos=14; break; /// Min=
	case 6: s0=13; s1=26; s2=10 ; ypos=21; break; /// ВП  В реж память отображение !!!!!1
	case 7: s0=24; s1=26; s2=10 ; ypos=21; break; /// НП  В реж память 
	}
	
	place_in_ram(29, ypos, 3, 15);
	send_command(0x5C);//Write RAM Command (5Ch)
	
	for(j = 0; j < 15; j++)//Y_len
		{
		send_8pixels(pgm_read_byte_near(small_num_set[s2][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s1][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[s0][j]));
		}
}
  
void draw_bminus(unsigned char yes, unsigned char lr) //// Нарисовать большой минус  1 нарисовать 0 стререть // lr 0 4 симаола 1- 3 символа
{
unsigned char j=0, xpos=0;
switch(lr)
	{
	case 0: xpos =19; break; 
	case 1: xpos =16; break;
	}
	place_in_ram(xpos, 15, 1, 12);
	send_command(0x5C);//Write RAM Command (5Ch)
if (yes >= 1)
	{

		for(j = 0; j < 12; j++)//Y_len
			{
			send_8pixels(pgm_read_byte_near(small_num_set[57][j]));
			}
	}
	else
	{
		for(j = 0; j < 12; j++)//Y_len
			{
			send_8pixels(0);
			}
		
	}
}
void draw_sminus(unsigned char pos) //// Нарисовать маленький минус блока параметров
{
unsigned char j,ypos=0;
	switch (pos)
	{
	case 0: ypos = 28; break; /// нижняя строчка
	case 1: ypos = 14; break; /// верхняя строчка
	}
	
	place_in_ram(27, ypos, 1, 15);
	send_command(0x5C);//Write RAM Command (5Ch)
	

	for(j = 0; j < 15; j++)//Y_len
		{
		send_8pixels(pgm_read_byte_near(small_num_set[45][j]));
		}
}

void draw_smm(unsigned char pos) /// вывести мм параметров
{
unsigned char j,ypos=0;
	switch (pos)
	{
	case 0: ypos = 28; break; /// нижняя строчка
	case 1: ypos = 14; break; /// верхняя строчка
	}

place_in_ram(21, ypos, 2, 15);
	send_command(0x5C);//Write RAM Command (5Ch)
	

	for(j = 0; j < 15; j++)//Y_len
		{
		send_8pixels(pgm_read_byte_near(small_num_set[56][j]));
		send_8pixels(pgm_read_byte_near(small_num_set[56][j]));
		}
}

void draw_smdot(unsigned char pos, unsigned char ypos)/// отобразить точку в блоке параметров режимов
{
	switch (pos)
	{
		case 0: pos = 24; break;
		case 1: pos = 25; break;
	}

	place_in_ram(pos, 14+ypos, 1, 2);
	send_command(0x5C);//Write RAM Command (5Ch)
	

		send_8pixels(0x0C);
		send_8pixels(0x0C);

}

void draw_razb_p(unsigned int hilev,unsigned int lolev) /// отобразить пределы в разбраковке
{
if (!(lolev <= (RAZBRL_low - 1)))
	{
	put_int_to_bnum_buffer(lolev,0); //// Нижн пред
	show_bnum_buffer(0,lolev);  // позиция . множитель
	draw_smm(0);
	}
	draw_spsim(3); /// Надписи ВП НП рисовать всегда
	
if (!(hilev <= (RAZBRH_low - 1)))

	{
	put_int_to_bnum_buffer(hilev,1); //// Верх пред
	show_bnum_buffer(1,hilev);
	draw_smm(1);
	//draw_spsim(2);
	}
	draw_spsim(2);	/// Надписи ВП НП рисовать всегда
}
void draw_CLASSMODE(unsigned char SM)  /////////////  Нарисоватиь параметры ячейки файла при сохранении 
{
	switch (SM)
	{
	case CMIZMER: show_hicons(1); break;
	case CMSCANR: show_hicons(3); break;
	case CMNONIU: show_hicons(5); break; 
	case CMDIFFP: show_hicons(4); break;
	case CMDIFFM: show_hicons(4); draw_bminus(1,0); break;
	case CMRAZBL: show_hicons(2); draw_spsim(7); break;
	case CMRAZBH: show_hicons(2); draw_spsim(6); break;
	case CMRAZBR: show_hicons(2); break;
	}
}

///////////////////////

void draw_non_d(signed int levd) /// отобразить доб коэфф в нониусе - дельта
{

unsigned char i=0;


	if ((levd - 500) >= 0) /// работа с отрицательными числами  -5 00   0   +5 00 мм
		{
			levd = levd-500;
			i = 1;
		}
		else
		{
			levd = 500-levd;
			i = 0;
		}
			
	
	put_int_to_bnum_buffer(levd,1); //// Верх пред
	show_bnum_buffer(1,levd);
	draw_smm(1);
	draw_spsim(1);
		
	if (i == 0)  /// если меньше нуля вывести знак минус
		{
			draw_sminus(1);
		}
	}

///////////////////////////////////////

void draw_diff_u(unsigned int val)
{
	put_int_to_bnum_buffer(val,1); //// Уровень дифф режима
	show_bnum_buffer(1,val);
	draw_smm(1);
	draw_spsim(4);
}

//////////////////////////////////////

void draw_scan_min(unsigned int val)
{
	put_int_to_bnum_buffer(val,1); //// мин уровень в режиме сканирования
	show_bnum_buffer(1,val);
	draw_smm(1);
	draw_spsim(5);
}

/////////////////////////////////=================================================================

void draw_wdataerase(void) ////  Надпись на экране   Данные будут удалены   продолжить ?  Да кл 0  НЕТ enter
{
cls();
BEEP(2);
show_wposx(1,5,6); //// Данные будут удалены
show_wpos(39,3,22); //// Продолжить ?
show_twpos(2,3,38); 
//show_wpos(36,6,38); //// Да кл 0  Нет кл enter
}

void DDS_CLK()  /// Clock
{
PORTC |= _BV(SCLK);
PORTC &= ~_BV(SCLK);
}

void DDS_SD(unsigned char tbb)  //// передача байта LSB первыйм MSB последним
{
unsigned char i,StoredData;
StoredData = tbb;


for (i=0;i<8;i++) 
 { 
 
 if (StoredData & 1) 
 
  { 
  PORTC |= _BV(SDAT); 
  } 
  
 else  
  { 
  PORTC &= ~_BV(SDAT);
  }

 DDS_CLK();
 StoredData>>=1; 
 } 
}
//////////////////////////////Загрузка В ЦАП
void DAC_CLK(void)  /// Clock
{
PORTF |= _BV(SCLDAC);
PORTF &= ~_BV(SCLDAC);
}

void DAC_SD(unsigned char tbb)  //// передача байта MSB первыйм LSB последним
{

unsigned char i,StoredData;



StoredData = tbb;

for (i=0;i<8;i++) 
 { 
 
 if (StoredData & 0x80) 
 
  { 
  PORTF |= _BV(SDLDAC); 
  } 
  
 else  
  { 
  PORTF &= ~_BV(SDLDAC);
  }
 DAC_CLK();
StoredData<<=1; 
 } 
}

void SIG_UP(unsigned char im)  /// Сигн разбраковки порога
{
//send_command(0xA6);
BEEP(im);
_delay_ms(300);
BEEP(im); 
//send_command(0xA5);
}


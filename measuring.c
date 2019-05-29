/*
 * measuring.c
 *
 *  Created on: 14.04.2009
 *  
 */
 



 
#include <avr/eeprom.h>
#include <avr/interrupt.h>
//#define F_CPU 3533200UL
#define F_CPU 8000000UL
#include <util/delay.h>

#include "MEM.h"
#include "key.h"
//#include "core.h"
#include "measuring.h"
//#include "constant.h"
#include "dev_cfg.h"
#include "display.h"
#include "main.h"
#include "Config.h"
//#include "bigfont.h"
extern ee_sound_choice;

void cfgr_load(unsigned char amp, unsigned char datch)//// Загрузка конфигурации датчиков и усиления
{
unsigned char num=0;
unsigned int ampx=0;

switch (datch)
	{
		/// Тип Датчика 		
	case 0: num = 0x84;break; 	//10-8/2Т    
	case 1: num = 0x84;break;	//5-10/2Т   
	case 2: num = 0x84;break;  //2.5-12/2Т   
	case 3: num = 0x24;break; //2.5Т-12/2
	case 4: num = 0x24;break; //5Т-12/2
	case 5: num = 0x44;break; //2.5-12/2А
	case 6: num = 0x44;break; //1.2-20/2А   
	case 7: num = 0x10;break; //1.25-К20   
	case 8: num = 0x10;break;  //1.25-П20	
	}	

DDS_SD(num);

////////////////////////// Загрузка в ЦАП/

ampx = ((amp-10)*19)+62;  /// Пересчитать усиление 10-40 




PORTF &= ~_BV(SYCDAC);
DAC_SD(ampx >>=4);
DAC_SD(ampx <<=4);
PORTF |= _BV(SYCDAC);


}


unsigned short ADC_convert(void) 
{ 
unsigned short int MVAL, HB, LB; 


//ADCSRA |= 0X80; //ENABLE ADC 
ADCSRA|= 0x40; //starting the conversion 

while(ADCSRA & 0x40); // wait for the end of the conversion 
asm ("nop");
asm ("nop");
LB = ADCL;
HB = ADCH;
MVAL =(HB<<8)  + LB;  /// Объединить Два байта в WORD
return MVAL;
} 




unsigned short int ReadX (void)     //// Чтение регистров счетчиков ПЛИС

{
unsigned short int MVAL;
unsigned char Hbyte;
unsigned char Lbyte;
unsigned static char akpr;

	
	
	
			if(!((PING & 0x01) == 0x01))//END = 1 акустический контакт  /////  Проверка на наличие правильных данных в регистрах
			
     
 
				{
					MVAL = 0xFFFF;     //// Если нет контакта
					akpr =0x00; /// Признак в ноль
				//	
					return MVAL;
				}

	akpr ++;
	
	if (akpr>=3)
	{
	akpr =0x50;
	
	PORTD = 0xFF; // Подтяжка       Да контак есть

	PORTB &= ~_BV(RDD);  //// Младший Разряд читаем
	asm ("nop");

	Lbyte = DATAX;

	PORTB |= _BV(RDD);   //// Старший разряд читаем
	asm ("nop");

	Hbyte = DATAX;
	PORTB &= ~_BV(RDD);
	
	
	PORTB |= _BV(RDD);   //// Сброс в 0
	asm ("nop");



	MVAL =(Hbyte<<8)  + Lbyte;  /// Объединить Два байта в WORD


	return MVAL;
	}
	
			else
			
			{
			
			
			
			MVAL = 0xFFFE;     //// Если нет контакта				
			return MVAL;
			}
			

}





//////////////////////////

void HI_volts(void)      //// Высокое напряжение
{
int i;

	for (i = 1; i <= 10; i++)
{
PORTB |= _BV(GENER);
	PORTE |= _BV(Hi_volt);
	_delay_us (4);
	PORTE &= ~_BV(Hi_volt);
	_delay_us (300);
	
}
_delay_us (400);
}
//////////////////////// 
 
void ZG(void) /// Импульс запуска ЗГ

{
PORTE |= _BV(ZG_IN);
asm ("nop");
asm ("nop");

asm ("nop"); // было 2
asm ("nop"); // было 2

PORTE &= ~_BV(ZG_IN);
} 
 
//////////////////////


void delayx(unsigned char val)
{
	switch(val)
			{
				case 0:	HI_volts(); ZG(); asm("nop"); break; /// 2uS
				case 1:	HI_volts();	ZG(); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");    
//				 asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
				 break; /// 4uS
				case 2:	HI_volts(); ZG(); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop");
				asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop");
				 break;/// 6us
				
				case 3:	HI_volts(); ZG(); asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
						asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");  
asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");						
						 break;/// 6.8us
						 
				
				
				case 8: HI_volts(); ZG();asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
											asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
											asm("nop");
asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
asm("nop");											
											 break;
				
				
				case 9: HI_volts(); ZG();  asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
											asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
											asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
											asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop"); 
											asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop");
asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");											
											
											 break; /// 20Us
			
			}
			
}


///////////////////////
/* 
void BEEP(unsigned char num)
{
unsigned char i=0;

i=eeprom_read_byte(BEEP_MODE);

if (i==0x01)
	{

		switch (num)
					
			{
			case 0: break;
			
			
			case 1: 
			{
			PORTE &= ~_BV(BEEPM0); 	//0
			PORTE &= ~_BV(BEEPM1);  //0
			
			PORTE |= _BV(BEEPX); //1	
			PORTE &= ~_BV(BEEPX);//0
			break;
			}
			case 2: 
			{
			PORTE |= _BV(BEEPM0); 	
			PORTE &= ~_BV(BEEPM1);
			
			PORTE |= _BV(BEEPX); //1	
			PORTE &= ~_BV(BEEPX);//0
			break;
			}
			
			case 3: 
			{
			PORTE |= _BV(BEEPM1); 	
			PORTE &= ~_BV(BEEPM0);
			
			PORTE |= _BV(BEEPX); //1	
			PORTE &= ~_BV(BEEPX);//0
			break;
			}
			
			case 4: 
			{
			PORTE |= _BV(BEEPM0); 
			PORTE |= _BV(BEEPM1);	
			
			PORTE |= _BV(BEEPX); //1	
			PORTE &= ~_BV(BEEPX);//0
			break;
			}
			
			
			
			default: 
			{
			
			PORTE &= ~_BV(BEEPM0); 	//0
			PORTE &= ~_BV(BEEPM1);  //0
			}
			
			
			}
	}
	
	
	
	//PORTE |= _BV(BEEPX); //1	
	//PORTE &= ~_BV(BEEPX);//0
}
*/




void loadamp(unsigned char amp) /// Загрузка усиления
{
unsigned int ampx;
ampx = ((amp-10)*19)+62;  /// Пересчитать усиление 10-40 
PORTF &= ~_BV(SYCDAC);
DAC_SD(ampx >>=4);
DAC_SD(ampx <<=4);
PORTF |= _BV(SYCDAC);
}



///////////////////////////////// Стандартное измерение 32 цикла - результат  сумма 32 одиночных измерений

unsigned long GET_MESINT (unsigned char numd, unsigned char clr)///Измерение импульсов толщины - тип датчика --  сброс счетчиков и регистров хранение 1. 0 - работа
{
static unsigned long AXRESULT;
//unsigned long AXT;

unsigned char i=0,u=0;

signed long XRES, mni;
signed short int ECBX;
unsigned char strob_width[9]={210,210,210,210,210,210,210,210,210};

XRES = 0;
ECBX = 0;


	if (clr == 1)
	{
		AXRESULT = 0; /// очистка счетика хранения
		ECBX = 0;
		mni = 0;
		return mni;
	}

	if (clr == 0)
	{
		switch (numd) /// режим нормальных измерений
		{		/// Тип Датчика
			case 0: u = 1; break; //1  // П112-10.0-6\2-Т003
			case 1: u = 2; break; //2  // П112-5.0-10\2-Т003
			case 2: u = 2; break; //2  // П112-2.5-12\2-Т003
			case 3: u = 0; break; //0  // П112-2.5Т-12\2-Б
			case 4: u = 0; break; //0  // П112-5.0Т-12\2-Б
			case 5: u = 1; break; //1  // П112-2.5-12\2А
			case 6: u = 1; break; //1  // П111-1.25-20\2А  ----
			case 7: u = 2; break; //2  // П111-1.25К20///////////////// 2
			case 8: u = 3; break; //3  // П111-1.25П20   ----
		}
	}


	if (clr == 2)   //// строб калибровки датчиков  стробы сдвигаются у 3 последних датчиков
	{
		switch (numd)
		{		/// Тип Датчика
			case 0: u = 1; break; //П112-10.0-6\2-Т003
			case 1: u = 2; break; //П112-5.0-10\2-Т003
			case 2: u = 2; break; //П112-2.5-12\2-Т003
			case 3: u = 0; break; //П112-2.5Т-12\2-Б
			case 4: u = 0; break; //П112-5.0Т-12\2-Б
			case 5: u = 1; break; //П112-2.5-12\2А
			//////////////////////////////////////////////////
			case 6: u = 1; break; //П111-1.25-20\2А  ----
			case 7: u = 2; break; //П111-1.25К20//////////////////////////////// 2
			case 8: u = 3; break; //П111-1.25П20   ----
		}
	}
	
	if (clr == 3)
	{
		
		switch (numd) /// режим Измерений НАСТРОЙКИ 10 толстый ПЭТ Лед
		{		/// Тип Датчика
			case 0: u = 1; break;  //П112-10.0-6\2-Т003
			case 1: u = 2; break; //П112-5.0-10\2-Т003
			case 2: u = 2; break; //П112-2.5-12\2-Т003
			case 3: u = 0; break; //П112-2.5Т-12\2-Б
			case 4: u = 0; break; //П112-5.0Т-12\2-Б
			case 5: u = 1; break; //П112-2.5-12\2А
			case 6: u = 9; break; //П111-1.25-20\2А  ----
			case 7: u = 2; break; //П111-1.25К20 /////////////////////// 2
			case 8: u = 9; break; //П111-1.25П20   ----
		}
		
		
	}


			PORTB |= _BV(RES); ///  Сброс счетчиков плис
			asm ("nop");
			PORTB &= ~_BV(RES);
			
		for (i=0; i<32; i++)
		{
			//_delay_ms (20);				/////  Задержка между измерениями --------------- 20
			delayx(u);	//_delay_us (u);	//// мертвая зона перед стробом
	//		_delay_us (u);					//// мертвая зона перед стробом
			PORTC |= _BV(STROB);			/// Строб включить
			_delay_us (210);				/// Ширина Строба
			PORTC &= ~_BV(STROB);			/// Строб выключ
			///PORTB &= ~_BV(GENER);		/// Отключить Генератор 100Мгц
			
			ECBX=ReadX(); 
			
			if (ECBX == 0xFFFE)				/// Начало измерений
			{
				show_acont(1);
				//mni = corrector(AXRESULT, numd);
				//BEEP(2);
				mni = AXRESULT;
				return mni;
			};
			if (ECBX == 0xFFFF)   /// Пропал сигнал  измерения недействительные
			{
				show_acont(0);
				//mni = corrector(AXRESULT, numd);
				mni = AXRESULT;
				return 0; //mni
			}
			else
			{
				PORTB |= _BV(RES);		///  Сброс счетчиков плис
				PORTB &= ~_BV(RES);
				XRES = XRES + ECBX;     //// Считать результат и сложить
			}; // if()
		}; // for()
	show_acont(1);
	//ctm(); /// сброс счетчика выключения
	AXRESULT = XRES;
	mni = XRES;
	//mni = corrector(XRES, numd);
	
	
	
	return mni;	
}
/////////////////////// Быстрое измерение для режима сканирование  4 цикла  результат сумма 4  * на 8  чтобы приравнять к 32 измепрениям ////////////////

unsigned long FAST_GET_MESINT (unsigned char numd, unsigned char clr)///Измерение импульсов толщины - тип датчика --  сброс счетчиков и регистров хранение 1. 0 - работа

{
static unsigned long AXRESULTa;
//unsigned long AXT;

unsigned int i=0,u=0;

signed long XRESa, mni;
signed short int ECBXa;

XRESa = 0;
ECBXa = 0;


	if (clr == 1)
	{	
		AXRESULTa = 0; /// очистка счетика хранения
		ECBXa = 0;
		mni = 0;
		return mni;
	}


switch (numd) 
	{		/// Тип Датчика 	
			case 0: u = 1; break;  //П112-10.0-6\2-Т003
			case 1: u = 2; break; //П112-5.0-10\2-Т003
			case 2: u = 2; break; //П112-2.5-12\2-Т003
			case 3: u = 0; break; //П112-2.5Т-12\2-Б
			case 4: u = 0; break; //П112-5.0Т-12\2-Б
			case 5: u = 1; break; //П112-2.5-12\2А 
  
			case 6: u = 1; break; //П111-1.25-20\2А  ----
			case 7: u = 2; break; //П111-1.25К20///////////////// 2
			case 8: u = 3; break; //П111-1.25П20   ---- 
	

//	default: u= 2;
}

PORTB |= _BV(RES); ///  Сброс счетчиков плис
asm ("nop");
PORTB &= ~_BV(RES);
 

		for (i = 1; i <= 8; i++)

		{
			//_delay_ms (20);/////  Задержка между измерениями ---------------
				//HI_volts();
				//ZG();
			delayx(u); //_delay_us (u); //// мертвая зона перед стробом
			
			
				
				
			
			
			

			PORTC |= _BV(STROB);  /// Строб включить

			_delay_us (210); /// Ширина Строба

					
			PORTC &= ~_BV(STROB);  /// Строб выключ
			///PORTB &= ~_BV(GENER);  /// Отключить Генератор 100Мгц
			ECBXa=ReadX(); 
			
			
			///////////////////////////////////////////////////////////////////////////////
				if (ECBXa == 0xFFFE)  /// Начало измерений
					
					{
					show_acont(1);
					
					//mni = corrector(AXRESULT, numd);
					mni = AXRESULTa;
					return mni;
					}
				
			////////////////////////////////////////////////////////////////////////////////
			
			
				if (ECBXa == 0xFFFF)   /// Пропал сигнал  измерения недействительные
				{
				show_acont(0);
				
				//mni = corrector(AXRESULTa, numd);
				
				return mni;
 
				}
				else
				{

			PORTB |= _BV(RES); ///  Сброс счетчиков плис
			PORTB &= ~_BV(RES);
		
			XRESa = XRESa + ECBXa;     //// Считать результат и сложить
			
				}
		  		
		}
show_acont(1);


//ctm(); /// сброс счетчика выключения


XRESa = XRESa * 4; /// догнать до 32 измерений
AXRESULTa = XRESa;

mni = corrector(XRESa, numd);

return mni;	
}

/*

/////////////////////////////////////////// Режимы работы прибора и МЕНЮ ///////////

unsigned char mmenu(unsigned char status, unsigned char nastr)

{
unsigned char ir=0,iv=0;

cls();
show_wmenu(status);
BEEP(2);
ir = status;

while (!(key_find()==keyenter))  /// ждать кнопки ввод
{

	if (key_find()==keydown)   /// двигать курсор вверх вниз  //// с циклической прокруткой.
	{   _delay_ms (dkeyl);
		key_find();
		status ++;
		if (status==6) { status =1;}
		BEEP(4);
		show_wmenu(status);
		//menu_wcursor(status,0);
	}
	
	if (key_find()==keyup)
	{   _delay_ms (dkeyl);
		key_find();	
		status --;
		if (status==0) { status =5;cls();}
		BEEP(3);
		show_wmenu(status);
		//menu_wcursor(status,0);
	}
	

if (key_find()==keyrezim) /// Выход по кнопке по которой вошли --- ждет когда ее отпустят тогда выход.
	{
	iv=keyrezim;
	
	while (iv==keyrezim)
	{
	_delay_ms(35);
	iv=key_find();
	//BEEP(1);
	};
	_delay_ms(500);
	status = ir;
	BEEP(1);
	goto m_out;
	}
}
//! cls();	
		if (!(status == ir))
			{
			eeprom_write_byte ((MODE1-1)+nastr,status); /// записать в память настройки режим работы
			}
m_out:;
cls();	
rkey();	
BEEP(2);	
return status; 

}

*/

/*

unsigned char rmenu(unsigned char nastr)///// меню настроек прибора (гаечный ключ) /// /// /// /// /// /// /// 
{
unsigned char ir=0,iv=0;
BEEP(2);
ir = nastr;
r_agn:;
show_wnmenu(nastr);
rkey();
while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
	{
	}
	_delay_ms (dkeyl); //! 620
	key_find();
	_delay_ms (32);
	

while (!(key_find()==keyenter)) /// ждать кнопки ввод
{


	if (key_find()==keydown)   /// двигать курсор вверх вниз/// с циклической прокруткой.
	{   _delay_ms (dkeyl);
		key_find();
		nastr ++;
		if (nastr==15) { nastr =1;}
		BEEP(4);
		show_wnmenu(nastr);
	}
	
	if (key_find()==keyup)
	{   _delay_ms (dkeyl);
		key_find();	
		nastr --;
		if (nastr==0) { nastr =14;}
		BEEP(3);
		show_wnmenu(nastr);
	}

if (key_find()==keynastr) /// Выход по кнопке по которой вошли --- ждет когда ее отпустят тогда выход.
	{
	iv=keynastr;
	
	while (iv==keynastr)
	{
	_delay_ms(35);
	iv=key_find();
	//BEEP(1);
	};
	_delay_ms(500);//
	nastr=ir;
	BEEP(1);
	goto r_out;
	}
	

	if (key_find()==keymem) ///// Скрытая функция записи серийного номера. разрешает запись по  нажатию кнопки память в режиме выбора настроек
	{
	
	SNUMWR(0xE0);
	 /// Разрешить запись серийного номера
	
	}



}

SNUMWR(0x00);

cls();
		
		if (nastr == 14)//// Звук
		
		{
		ZPset(); /// Управление звуком
		cls();
		goto r_agn;
		return ir;
		}
		
		
		if (nastr == 13)//// Регулировка яркости
		
		{
		
		brset();
		cls();
		goto r_agn;
		return ir;
		
		}
		
		
		if(nastr == 11) /// Вызов Усиления
		
		{
		
		
		ampset(ir);
		
		cls();
		
		goto r_agn;
		return ir;
		}
		
		
		if(nastr == 12)//// Вызов меню Система
		
		{
		show_intro(); //// отобразить меню система!!!
		goto r_agn;
		return ir;
		}
		
			//if (!(nastr == ir))
			//{
			eeprom_write_byte (NASTR,nastr); /// записать в память режим работы
			//}
r_out:;
cls();
rkey();
BEEP(2);
return nastr;
}*/



/*unsigned char regulmenu(unsigned char num)  /// меню регулировок 
{
unsigned char io=1,iod=1;

cls();
show_mpos(17,20,0);///регулировки



show_mpos(18,20,20);/// усилен
show_mpos(19,20,40);/// скорость узк

show_mpos(20,5,20);/// память
show_mpos(21,5,40);/// сброс

switch (io)
{
case 1: iod=2; break;
case 2: iod=3; break;
case 3: iod=5; break;
case 4: iod=6; break;
}
menu_cursor(iod);


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
	
	if (key_find()==keydown)   /// двигать курсор вверх вниз
	{   _delay_ms (320);
		key_find();
		io ++;
		if (io==5) { io = 4;}
		BEEP(4);
		
		switch (io)
		{
		case 1: iod=2; break;
		case 2: iod=3; break;
		case 3: iod=5; break;
		case 4: iod=6; break;
		}
		
		menu_cursor(iod);
	}
	
	if (key_find()==keyup)
	{   _delay_ms (320);
		key_find();	
		io --;
		if (io==0) { io =1;}
		BEEP(3);
		
		switch (io)
		{
		case 1: iod=2; break;
		case 2: iod=3; break;
		case 3: iod=5; break;
		case 4: iod=6; break;
		}
		
		menu_cursor(iod);
	}
}
	if (io == 4)
	{
	eeprom_write_word(STAT,0xFFFF);  //// произвести сброс до заводских установок
	cls();
	_delay_ms (600);
	BEEP(2);
	_delay_ms (600);
	BEEP(2);
	_delay_ms (600);
	BEEP(2);
	initmem();
	}
return io;  /// возврат выборанной функции
}

/*/

/*


unsigned char kalibmenu(unsigned char nastr)//////////////////////////////////////////////////////////
{
unsigned char ir=0,ik=0, id=0;
cls();
switch (nastr)
		{
		case 0: 	id= eeprom_read_byte(DATCH1);	break;	
		case 1:		id= eeprom_read_byte(DATCH2);	break;	
		case 2: 	id= eeprom_read_byte(DATCH3);	break;	
		case 3: 	id= eeprom_read_byte(DATCH4);	break;	
		case 4: 	id= eeprom_read_byte(DATCH5);	break;	
		case 5: 	id= eeprom_read_byte(DATCH6);	break;	
		case 6: 	id= eeprom_read_byte(DATCH7);	break;
		case 7: 	id= eeprom_read_byte(DATCH8);	break;	
		case 8: 	id= eeprom_read_byte(DATCH9);	break;
		case 9: 	id= eeprom_read_byte(DATCH10);	break;
		}


ir = nastr;
ik=1;
BEEP(2);
agnm:;
show_cmenu(ik);

rkey();


while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);


rkey();

while (!(key_find()==keyenter)) /// ждать кнопки ввод
{
	if (key_find()==keydown)   /// двигать курсор вверх вниз
	{   _delay_ms (320);
		key_find();
		ik ++;
		if (ik==4) { ik =1;}
		BEEP(4);
	//! cls();
	//!	show_cmenu(ik);
		menu_wcursor(ik,0);
	}
	
	if (key_find()==keyup)
	{   _delay_ms (320);
		key_find();	
		ik --;
		if (ik==0) { ik =3;}
		BEEP(3);
	//! cls();
	//!	show_cmenu(ik);
		menu_wcursor(ik,0);
	}
	

if (key_find()==keyzero) /// Выход по кнопке по которой вошли --- ждет когда ее отпустят тогда выход.
	{
	ik=keyzero;
	
	while (ik==keyzero)
	{
	_delay_ms(35);
	ik=key_find();
	//BEEP(1);
	};
	_delay_ms(500);
	BEEP(1);
	goto cm_out;
	}	
}

if (ik == 3) {calibhig(nastr,id); ik=3; goto agnm;} //// Калибр по толщине
if (ik == 2) {velset(nastr); ik=2; goto agnm;} /// установка скорости
//if (ik == 1) {calibzero(id); ik=1; goto agnm;} //// Калибр 0

			//if (!(nastr == ir))
			//{
			//eeprom_write_byte (NASTR,nastr); /// записать в память режим работы
			//}
cm_out:;
cls();
rkey();
return nastr;
}*/

/*

void calibhig (unsigned char nastr, unsigned char dach) //// Калибровка по толщине - Вычисление скорости при заданной толщине и измеренному числу импульсов
//// V = (толщ(mm) * 100 * 64000) /N имп *32 
{
unsigned char num;
unsigned int vel=0, io=0;
unsigned long mvs=0, im=0, VA=0,VB=0, SA=0, SB=0; 
signed long it;
unsigned int calib=0;

switch (nastr)  //// прочитаьть из памяти настройки скоростоть
{
case 0: vel = eeprom_read_word (VEL1);	calib = eeprom_read_dword(CALB1); break;		/// СКОРОСТИ ДЛЯ НАСТРОЕК1
case 1: vel = eeprom_read_word (VEL2);	calib = eeprom_read_dword(CALB2); break;		/// СКОРОСТИ ДЛЯ НАСТРОЕК1
case 2: vel = eeprom_read_word (VEL3);	calib = eeprom_read_dword(CALB3); break;		/// СКОРОСТИ ДЛЯ НАСТРОЕК1
case 3: vel = eeprom_read_word (VEL4);	calib = eeprom_read_dword(CALB4); break;		/// СКОРОСТИ ДЛЯ НАСТРОЕК1
case 4: vel = eeprom_read_word (VEL5);	calib = eeprom_read_dword(CALB5); break;		/// СКОРОСТИ ДЛЯ НАСТРОЕК1
case 5: vel = eeprom_read_word (VEL6);	calib = eeprom_read_dword(CALB6); break;		/// СКОРОСТИ ДЛЯ НАСТРОЕК1
case 6: vel = eeprom_read_word (VEL7);	calib = eeprom_read_dword(CALB7); break;		/// СКОРОСТИ ДЛЯ НАСТРОЕК1
case 7: vel = eeprom_read_word (VEL8);	calib = eeprom_read_dword(CALB8); break;		/// СКОРОСТИ ДЛЯ НАСТРОЕК1
case 8: vel = eeprom_read_word (VEL9);	calib = eeprom_read_dword(CALB9); break;		/// СКОРОСТИ ДЛЯ НАСТРОЕК1
case 9: vel = eeprom_read_word (VEL10);	calib = eeprom_read_dword(CALB10); break;	/// СКОРОСТИ ДЛЯ НАСТРОЕК1
}

///calib = eeprom_read_word(CALIBD); /// считать калибровку 0 ПЭП после изменения
num=nastr;




//if (num ==0)
//{
//zapret(); ///запрет первых 3 установок изменений в настройках

//}
//else
//{

io = 100;

cls();
show_mmdiv();
draw_dline();
draw_memoline (4,7,48); /// Строка подсказка Введите занч тощ
BEEP(2);

put_int_to_num_buffer(0,0);
		 show_num_buffer();

/////////////////////////////////////////////////////////////////// Измерение числа импульсов

while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
			{
			}
			_delay_ms (620);
			key_find();
			_delay_ms (32);

//mvs =  calculmes(calib,vel,dach,nastr);			
//mvs =  GET_MESINT(dach,0);
_delay_ms(50);

while (!(key_find()==keyenter)) /// ждать кнопки ввод
{

//ctm(); //// сброс таймера отключения

PORTB &= ~_BV(RES);				/// Вывести из сброса ПЛИС

//mvs =  calculmes(calib,vel,dach,nastr);
mvs =  GET_MESINT(dach,0);

PORTB |= _BV(RES);

	//mvs =  GET_MESINT(dach,0);
	//mvs = 0;
	
it = (mvs - calib);

if  (it <= 0 )   
	{
	mvs=0;
	}
	else 
	{
	mvs = (mvs-calib);
	}
	 
im =  ((vel * ((mvs)/2))/1000)/32;
//im=mvs;
im = corrector (im,dach); /// корректировка показаний прибора
if (im <= 0) {im =0;}  ///толщина мм

/// mvs хранит число импульсов 
 
VA = im; //// Толщина измеренная 
SA = vel; //// Скорость заданная
 
///tval=  (calculmes(calib,vel,dach,nastr));
	put_int_to_num_buffer(im,0); //// Вывести толщину на дисплей

          
	show_num_buffer();
	
	

	

/ *mvs =  GET_MESINT(dach);

tx = mvs;

put_int_to_num_buffer((tx)); //// Вывести толщину на дисплей   .. Скорость константа
show_num_buffer();* /

_delay_ms(30);//100

if (key_find()==keyzero) /// Выход по кнопке по которой вошли --- ждет когда ее отпустят тогда выход.
	{
	io=keyzero;
	BEEP(1);
	while (io==keyzero)
	{
	_delay_ms(35);
	io=key_find();
	//BEEP(1);
	};
	_delay_ms(500);
	
	goto calh_out;
	}
	
_delay_ms(35);

}

cls();
show_mmdiv();
draw_dline();
put_int_to_num_buffer(0,0);
		 show_num_buffer();
draw_memoline (3,7,48); /// Строка подсказка Введите занч тощ


	if (im<=0){im=MinHiS;}
	if (im>MaxHiS){im=MaxHiS;}

io = im;  /// Значение ТОЛЩИНЫ В mm 
put_int_to_num_buffer(io,0);
		 show_num_buffer();
show_mmdiv();



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
	//return value;
	//}
	_delay_us(3);
	
	while (key_find()==keyup)   /// двигать курсор вверх вниз
	{ 	
		_delay_ms (step_speed0);
		key_find();
		
	
											if (io >= 10000)	{io = io+ (10*autoplusm(0));}  /// если больше 10 тыщ мкм прибавлять по 10
											else {io = io + autoplusm(0);} /// до 10000 прибавлять по 1
		
		//io=io+autoplusm(0);
		
		if (io>=(MaxHiS+1)) { io = MaxHiS;}
		  put_int_to_num_buffer(io,0);
		  show_num_buffer();

		rkey();	
		
	}
	
	
	while (key_find()==keydown)
	{   
		_delay_ms (step_speed0);
		//_delay_ms (step_speed0);
		key_find();	
			
											if (io >= 10000)	{io = io - (10*autoplusm(0));} /// вычитать по 10
											else {io= io - autoplusm(0);} //// Вычитать по 1
		
		//io=io-autoplusm(0);
	
		if (io<=(MinHiS-1)) { io = MinHiS;}
		put_int_to_num_buffer(io,0);  
		show_num_buffer();
		
		rkey();

	}
	
	
	if (key_find()==keyzero) /// Выход по кнопке по которой вошли --- ждет когда ее отпустят тогда выход.
	{
	io=keyzero;
	BEEP(1);
	while (io==keyzero)
	{
	_delay_ms(35);
	io=key_find();
	//BEEP(1);
	};
	_delay_ms(500);
	
	goto calh_out;
	}

}





VB = io;   //// Толщина ВВЕДЕННАЯ   


im = io;

io = ((im)*64000)/(mvs);
cls();
show_msdiv();
draw_dline();



SB=	(VB*SA)/VA; ///// Вычислить скорость из пропорции

io =SB;

if (io >= HISPEED ) {io = HISPEED;}
if (io <= LowSPEED ) {io = LowSPEED;}

put_int_to_cnum_buffer(io);  
		show_cnum_buffer();
		
_delay_ms(3500);		





///////////////////////////////////////////////////////////////////

if (num==1)     //// сохранить скорость в памяти
	{
	eeprom_write_word (VEL1,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==2)
	{
	eeprom_write_word (VEL2,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==3)
	{
	eeprom_write_word (VEL3,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==4)
	{
	eeprom_write_word (VEL4,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==5)
	{
	eeprom_write_word (VEL5,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==6)
	{
	eeprom_write_word (VEL6,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==7)
	{
	eeprom_write_word (VEL7,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==8)
	{
	eeprom_write_word (VEL8,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==9)
	{
	eeprom_write_word (VEL9,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==10)
	{
	eeprom_write_word (VEL10,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
calh_out:;
cls();
rkey();
//}
}
*/


/*
////////////////////////////////////////////////////////////////////////////
void velset (unsigned char num)//// установки скорости в настройке
{
unsigned int io=0, value=0;



		switch (num)  //// прочитаьть из памяти настройки скоростоть
		{
		case 1: value = eeprom_read_word (VEL1); break;  /// СКОРОСТИ ДЛЯ НАСТРОЕК1
		case 2: value = eeprom_read_word (VEL2); break; /// СКОРОСТИ ДЛЯ НАСТРОЕК1
		case 3: value = eeprom_read_word (VEL3); break; /// СКОРОСТИ ДЛЯ НАСТРОЕК1
		case 4: value = eeprom_read_word (VEL4); break; /// СКОРОСТИ ДЛЯ НАСТРОЕК1
		case 5: value = eeprom_read_word (VEL5); break; /// СКОРОСТИ ДЛЯ НАСТРОЕК1
		case 6: value = eeprom_read_word (VEL6); break; /// СКОРОСТИ ДЛЯ НАСТРОЕК1
		case 7: value = eeprom_read_word (VEL7); break;/// СКОРОСТИ ДЛЯ НАСТРОЕК1
		case 8: value = eeprom_read_word (VEL8); break; /// СКОРОСТИ ДЛЯ НАСТРОЕК1
		case 9: value = eeprom_read_word (VEL9); break; /// СКОРОСТИ ДЛЯ НАСТРОЕК1
		case 10: value = eeprom_read_word (VEL10); break; /// СКОРОСТИ ДЛЯ НАСТРОЕК1
		}
		io = value;

cls();
show_mpos(7,20,0);/// скорость узк
draw_dline();
draw_memoline (1,7,48);


 put_int_to_cnum_buffer(io);
		 show_cnum_buffer();
show_msdiv();
BEEP(2);

		while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
			{
			}
			_delay_ms (620);
			key_find();
			_delay_ms (32);

while (!(key_find()==keyenter)) /// ждать кнопки ввод
{



	//ctm(); //// сброс таймера отключения

	//if (key_find()==keyzero)
	//{
	//cls();
	//BEEP(1);
	//return value;
	//}
	
	while (key_find()==keyup)   /// двигать курсор вверх вниз
	{  _delay_ms (step_speed0);
		// 
		
		key_find();
		
		io = io +autoplusm(0);
		
		if (io>=HISPEED+1) { io = HISPEED;}
		  put_int_to_cnum_buffer(io);
		  show_cnum_buffer();

		rkey();	
		_delay_ms (27);
		rkey();
		
	}
	
	while (key_find()==keydown)
	{   _delay_ms (step_speed0);
		key_find();	
		io = io - autoplusm(0);;
		if (io<=LowSPEED-1) { io =LowSPEED;}
		put_int_to_cnum_buffer(io);  
		show_cnum_buffer();
		
		rkey();
		_delay_ms (27);
		rkey();

	}
	
	if (key_find()==keyzero) /// Выход по кнопке по которой вошли --- ждет когда ее отпустят тогда выход.
	{
	io=keyzero;
	BEEP(1);
	while (io==keyzero)
	{
	_delay_ms(35);
	io=key_find();
	//BEEP(1);
	};
	_delay_ms(500);
	
	goto vel_out;
	}
}

if (num==1)     //// сохранить скорость в памяти
	{
	eeprom_write_word (VEL1,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==2)
	{
	eeprom_write_word (VEL2,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==3)
	{
	eeprom_write_word (VEL3,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==4)
	{
	eeprom_write_word (VEL4,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==5)
	{
	eeprom_write_word (VEL5,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==6)
	{
	eeprom_write_word (VEL6,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==7)
	{
	eeprom_write_word (VEL7,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==8)
	{
	eeprom_write_word (VEL8,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==9)
	{
	eeprom_write_word (VEL9,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
if (num==10)
	{
	eeprom_write_word (VEL10,io);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	}
	
	vel_out:;
cls();
rkey();
}
//////////////////////////////////////////////////////////////////////////////*/
//////////////////////////////////////////////////////////////////////////////
void calibzero (unsigned char nastr, unsigned char dach) ///  Калибровка 0 ПЭП ====================================================
{
	signed long mvs, iv;
	signed int itimer;
	unsigned char amplif=20,io=0;
	unsigned int calib;
	volatile unsigned char *iv_show[4];					// строка для отображения числа

	cls();

	switch (nastr)    ///// Узнать усиление в настройке

	{
		case 1:  amplif= eeprom_read_byte(AMP1); calib = eeprom_read_dword(CALB1);	break;
		case 2:  amplif= eeprom_read_byte(AMP2); calib = eeprom_read_dword(CALB2);	break;
		case 3:  amplif= eeprom_read_byte(AMP3); calib = eeprom_read_dword(CALB3);	break;
		case 4:  amplif= eeprom_read_byte(AMP4); calib = eeprom_read_dword(CALB4);	break;
		case 5:  amplif= eeprom_read_byte(AMP5); calib = eeprom_read_dword(CALB5);	break;
		case 6:  amplif= eeprom_read_byte(AMP6); calib = eeprom_read_dword(CALB6);	break;
		case 7:  amplif= eeprom_read_byte(AMP7); calib = eeprom_read_dword(CALB7);	break;
		case 8:  amplif= eeprom_read_byte(AMP8); calib = eeprom_read_dword(CALB8);	break;
		case 9:  amplif= eeprom_read_byte(AMP9); calib = eeprom_read_dword(CALB9);	break;
		case 10: amplif= eeprom_read_byte(AMP10);calib = eeprom_read_dword(CALB10);	break;
	}

	cfgr_load(amplif,dach); //// Загрузка Усиления и настроек аналоговой платы.


//	show_mmdiv();
//	draw_dline();
	mvs =  GET_MESINT(dach,2);
//	_delay_ms(50);
//	rkey();
	itimer=0;


	while ((PINH & (1<<acontpin)) && !keypressed_short)////((!(key_find()==keyenter)) && ( PINH & (1<<acontpin))) /// ждать кнопки ввод и акустического контакта
	{

		

		PORTB &= ~_BV(RES); /// Вывести из сброса ПЛИС

		mvs =  GET_MESINT(dach,2);  /// замер в режиме калибровка

		PORTB |= _BV(RES); ///  Сброс счетчиков плиc - Пониженное потребление


		if ((mvs-calib)<=0)
		{ iv =  0; } ///меньше нуля
		
		else
		{ iv =  ((CALVL * ((mvs-calib)/2))/1000)/32; } /// больше нуля

                num2str_right((unsigned int)iv,iv_show);
                if(iv<range_switching_threshold)dot_pos=1; else dot_pos=2;
                Draw_big_font (4,dot_pos,iv_show,measure_pos,measure_raw, big_font_16, 16, front_color);


	} ////////////////////////////// enter

	if (dach <=6)
	{

		if ((mvs-calobr3mm) >= 0)
		{
			mvs = mvs - calobr3mm; /// Вычесть число импульсов из образца. 3мм
		}
		else
		{
			mvs = 0;
		}
	}
	
	if (dach==7)
	{
		
		if ((mvs-calobr5mm) >= 0)
		{
			mvs = mvs - calobr5mm; /// Вычесть число импульсов из образца.5мм для датчика П112-1.25
		}
		else
		{
			mvs = 0;
		}
		
	}
	
	if (dach>=8)
	{
		if ((mvs-calobr20mm) >= 0)
		{
			mvs = mvs - calobr20mm; /// Вычесть число импульсов из образца.20мм для датчиков П111
		}
		else
		{
			mvs = 0;
		}
	}
	
	eeprom_write_word (CALIBD,mvs);


	switch (nastr)  //// Сохраниит калибровку в блоке
	{
		case 1: eeprom_write_word (CALB1,mvs);		break;
		case 2: eeprom_write_word (CALB2,mvs);		break;
		case 3: eeprom_write_word (CALB3,mvs);		break;
		case 4: eeprom_write_word (CALB4,mvs);		break;
		case 5: eeprom_write_word (CALB5,mvs);		break;
		case 6: eeprom_write_word (CALB6,mvs);		break;
		case 7: eeprom_write_word (CALB7,mvs);		break;
		case 8: eeprom_write_word (CALB8,mvs);		break;
		case 9: eeprom_write_word (CALB9,mvs);		break;
		case 10: eeprom_write_word (CALB10,mvs);	break;

		
	}


	//put_int_to_num_buffer(calculmes(mvs,CALVL,dach,0XFE),0); //// Вывести толщину на дисплей   .. Скорость константа
	//show_num_buffer();

	cls();
};

void ampset(unsigned char num)//// установки усиления в настройке
{
unsigned char io=0,bo=0,value=0;


if (num == 0)
{
zapret();///запрет первых 3 установок изменений в настройках
}
else

{
switch (num)  //// прочитаьть из памяти настройки устление
{
case 1: value = eeprom_read_byte (AMP1); break;  ///  
case 2: value = eeprom_read_byte (AMP2); break; /// 
case 3: value = eeprom_read_byte (AMP3); break; /// 1
case 4: value = eeprom_read_byte (AMP4); break; /// 1
case 5: value = eeprom_read_byte (AMP5); break; /// 1
case 6: value = eeprom_read_byte (AMP6); break; /// 
case 7: value = eeprom_read_byte (AMP7); break;/// 1
case 8: value = eeprom_read_byte (AMP8); break; /// 
case 9: value = eeprom_read_byte (AMP9); break; /// 1
case 10: value = eeprom_read_byte (AMP10); break; /// 
}
io = value;
cls();
show_mpos(6,20,0);/// усилен
draw_dline();
draw_memoline (2,7,48);

 put_int_to_cnum_buffer(io);
		 show_cnum_buffer();
BEEP(2);


			bo=keynastr;  /// :Ждать пока отпустят кнопку
			
			while (bo==keynastr)
			{
			_delay_ms(35);
			bo=key_find();	
			};
			rkey();


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
	{   _delay_ms (step_speeda);
		key_find();
		io ++;
		if (io==41) { io = 40;}
		 put_int_to_cnum_buffer(io);
		 show_cnum_buffer();
		  
		BEEP(4);
			
		
	}
	
	if (key_find()==keydown)
	{   _delay_ms (step_speeda);
		key_find();	
		io --;
		if (io==9) { io =10;}
		 put_int_to_cnum_buffer(io);
		 show_cnum_buffer();
		  
		BEEP(3);

		
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
	_delay_ms(500);
	
	goto amp_out;
	}
	
}

if (num == 1)
		{
			eeprom_write_byte (AMP1,io);  /// УСИЛЕНИЕ ДЛЯ НАСТРОЕК
		}
if (num == 2)
		{
			eeprom_write_byte (AMP2,io);  /// УСИЛЕНИЕ ДЛЯ НАСТРОЕК
		}
if (num == 3)
		{
			eeprom_write_byte (AMP3,io);  /// УСИЛЕНИЕ ДЛЯ НАСТРОЕК
		}
if (num == 4)
		{
			eeprom_write_byte (AMP4,io);  /// УСИЛЕНИЕ ДЛЯ НАСТРОЕК
		}
if (num == 5)
		{
			eeprom_write_byte (AMP5,io);  /// УСИЛЕНИЕ ДЛЯ НАСТРОЕК
		}
if (num == 6)
		{
			eeprom_write_byte (AMP6,io);  /// УСИЛЕНИЕ ДЛЯ НАСТРОЕК
		}		
		
if (num == 7)
		{
			eeprom_write_byte (AMP7,io);  /// УСИЛЕНИЕ ДЛЯ НАСТРОЕК
		}		
if (num == 8)
		{
			eeprom_write_byte (AMP8,io);  /// УСИЛЕНИЕ ДЛЯ НАСТРОЕК
		}		
if (num == 9)
		{
			eeprom_write_byte (AMP9,io);  /// УСИЛЕНИЕ ДЛЯ НАСТРОЕК
		}		
if (num == 10)
		{
			eeprom_write_byte (AMP10,io);  /// УСИЛЕНИЕ ДЛЯ НАСТРОЕК
		}	

amp_out:;	
cls();
BEEP(1);
rkey();
}
}

unsigned char pepmenu (unsigned char nastr) ///  МЕНЮ ВЫБОРА ДАТЧИКА ............................................

{
unsigned char io=0, ir=0;
cls();
io = eeprom_read_byte ((DATCH1-1)+nastr);  /// прочитать тип датчика из настроек 
ir = io;

show_pepmenu(io); 

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
	//return nastr;
	//}
	
	if (key_find()==keydown)   /// двигать курсор вверх вниз /// с циклической прокруткой.
	{   _delay_ms (dkeyl);
		key_find();
		io ++;
		if (io==(maxPEP+1)) { io = 1;}
		BEEP(4);
		show_pepmenu(io);
	}
	
	if (key_find()==keyup)
	{   _delay_ms (dkeyl);
		key_find();	
		io --;
		if (io==0) { io =maxPEP;}
		BEEP(3);
		show_pepmenu(io);	
	}
	

if (key_find()==keypep) /// Выход по кнопке по которой вошли --- ждет когда ее отпустят тогда выход.
	{
	io=keypep;
	
	while (io==keypep)
	{
	_delay_ms(35);
	io=key_find();
	//BEEP(1);
	};
	_delay_ms(500);
	BEEP(1);
	goto p_out;
	}

}

if (!(io == ir)) 
			{
			
			//if (io>5) {io++;}
			
			
			eeprom_write_byte ( ((DATCH1-1)+nastr),io); /// записать в память Выбранной настройки тип датчика ++++++++++++++++++++++++++++
			cls();
			show_twpos(1,3,14);
			///show_wpos(37,6,14); //// Требуется калибровка
			_delay_ms(2500);
			BEEP(2);
			//calibzero(io); //// Вызвать калибровку датчика 
			read_caibrext();//// прочитать калибровку
			}
			
p_out:;
cls();
rkey();
BEEP(2);
return nastr;
}

/////////////////////////////////////////


unsigned long calculmes (unsigned int calib, unsigned int velos, unsigned char dach, unsigned char nastr)  //// измерение и пересчет с учетом калибровок и скорости
//unsigned long calculmes (unsigned int calib, unsigned int velos, unsigned char dach)  //// измерение и пересчет с учетом калибровок и скорости
{
unsigned long mvs=0, im;
signed long it;
	
	if (nastr==0xFE)  /// при калибровке последних датчиков
	
	{
	mvs =  GET_MESINT(dach,2);
	}
	
	
	if (nastr <=8 )   //// Режим обычных измерений настр Н1-Н9
	{
	mvs =  GET_MESINT(dach,0);
	}
	//mvs = 0;
	
	if (nastr ==9 )   //// Режим сдвинутого строба датчиков 7 и 9  Работает в Режимен настройки Н10
	{
	mvs =  GET_MESINT(dach,3);
	}
	
	
	mvs = (mvs-calib);

it = (mvs - calib);

if  (it <= 0 )   
	{
	mvs=0;
	}
	else 
	{
	mvs = (mvs-calib);
	}

	 
im =  ((velos * ((mvs)/2))/1000)/32; /// пересчет импульсов в толщину

im = corrector (im,dach); /// корректировка показаний прибора

if (im <= 0) {im =0;}

return im;


}

///////////////////////////


unsigned long FAST_calculmes (unsigned int calib, unsigned int velos, unsigned char dach)  //// быстрое сканирование измерение и пересчет с учетом калибровок и скорости
{
unsigned long mvs, im;
signed long it;
	mvs =  FAST_GET_MESINT(dach,0);
	//mvs = 0;
	
it = (mvs - calib);

if  (it <= 0 )   
	{
	mvs=0;
	}
	else 
	{
	mvs = (mvs-calib);
	}
	 
im =  ((velos * ((mvs)/2))/1000)/32; /// пересчет импульсов в толщину

im = corrector (im,dach); /// корректировка показаний прибора

if (im <= 0) {im =0;}

return im;
}











//////////////////////////////////////////  РЕЖИМЫ РАБОТЫ ///////////

unsigned int IZMERENIE (unsigned char status, unsigned short velos, unsigned char datchnum, unsigned char nastr, unsigned char amp, unsigned char vb, unsigned int calib,unsigned char mf,unsigned int mp, unsigned char typefile)  ///// Режим измерение
//unsigned int IZMERENIE (unsigned char status, unsigned short velos, unsigned char datchnum, unsigned char amp, unsigned char vb, unsigned int calib,unsigned char mf,unsigned int mp, unsigned char typefile)  ///// Режим измерение
{

unsigned int val=0;/// толщина 
if (status == 0x01) 
{

//WR_CLASSM(CMIZMER);/// для памяти состояние

PORTB &= ~_BV(RES); /// Вывести из сброса ПЛИС

// show_hicons(1);
//show_mmdiv();
	
// draw_dline();
// draw_hline();


///calculmes(calib,velos,datchnum,nastr)*/

	val=  calculmes(calib,velos,datchnum,nastr); /// это тут!!!!!!!!!!!!!!!!!!!!!!
	
	//num2str_right((unsigned int)val,str_show);
	//Draw_big_font (4,0,str_show,measure_pos,measure_raw, fnt1, 16, front_color);



//	put_int_to_num_buffer(val,0); //// Вывести толщину на дисплей
         
//	show_num_buffer();

//put_int_to_snum_buffer(velos); /// скорость узк
	//show_snum_buffer();
//	show_msmin(0);


//draw_nastrn(nastr);


//draw_dachnum(datchnum,0);


//draw_samp(amp); /// Вывести усиление
//draw_smem(mf,mp,typefile);  //// Отразить состояние памяти прибора
//draw_smem (100,235,100);
//draw_batl(vb);

	
	PORTB |= _BV(RES); ///  Сброс счетчиков плиc - Пониженное потребление	

//if (!( PINH & (1<<acontpin))) {_delay_ms(50);} //50

}
return val; /// Вернуть толщину отображенную на дисплее
}


//////////////////////////////

unsigned int RAZBRAKOVKA (unsigned char status, unsigned short velos, unsigned char datchnum, unsigned char nastr, unsigned char amp, unsigned char vb, unsigned int calib, unsigned int RAZBH, unsigned int RAZBHL,unsigned char mf,unsigned int mp, unsigned char typefile)  ///// Режим разбраковка
{

static unsigned char exp =0, expb =0;
unsigned char state=0, var=0;
unsigned int value=0;

if (status == 5)
{
		if (exp == 1) {var = 1;}
		if (expb== 1) {var = 1;}

PORTB &= ~_BV(RES); /// Вывести из сброса ПЛИС
//show_hicons(2);
//show_mmdiv();
//draw_dline();
//draw_hline();
	  
	value =  calculmes(calib,velos,datchnum,nastr); 
	
	//WR_CLASSM(CMRAZBR);/// для памяти состояние
	
	  
	//show_num_buffer();
	
	
	
	if (!(RAZBH <= (RAZBRH_low - 1))) /// если порог не выключен
		{
			if (value >= RAZBH) { SIG_UP(3); state =1; exp =1; WR_CLASSM(CMRAZBH);} else {exp =0;}    // 
			 /// проверка верхнего порога если порог достигнут - сигнализация верх порога
		}
		
	
	if (!(RAZBHL <= (RAZBRL_low - 1))) /// если порог нижний не выключен
		{
			if (value <= RAZBHL) { SIG_UP(4); state =1; expb =1; WR_CLASSM(CMRAZBL);} else {expb =0;} // 
			 /// проверка нижнего порога если порог достигнут - сигнализация нижн порога
		}
	
	

	if (state == 1) 
		{	put_int_to_num_buffer(value,1);   /// отобразить инверсно /// отобразитиь значение без затятых

			show_inv_num_buffer(0); 

	
			
		if (value >= 10000)
			{show_inv_dot(1);}
			else
			{show_inv_dot(0);}
			
			PORTH |= _BV(razbr_alrm); ///  1 на вывод разбраковки реле

		
		} 
	
			else
			{
			
				if ( (var ==1) && (state == 0))
			
					{ 
						show_inv_num_buffer(1); /// очистка поля
						exp =0;
						expb =0;
						goto exitf;
					}
					
			
			put_int_to_num_buffer(value,0); 
			show_num_buffer();
			
	
			PORTH &= ~_BV(razbr_alrm);///  0 на вывод разбраковки реле

			
			} /// отобразить не инверсно
				

/*
put_int_to_snum_buffer(velos); /// скорость узк
	show_snum_buffer();
	show_msmin(0);


draw_razb_p(RAZBH,RAZBHL); /// вывод параметров разбраковки

draw_nastrn(nastr);

draw_dachnum(datchnum,0);

draw_samp(amp);
draw_smem(mf,mp,typefile);  //// Отразить состояние памяти прибора
draw_batl(vb);
*/
	PORTB |= _BV(RES); ///  Сброс счетчиков плиc - Пониженное потребление
if (!( PINH & (1<<acontpin))) {_delay_ms(1500);}

exitf:;

}
return value; /// Вернуть толщину отображенную на дисплее
}

//////////////////////////

unsigned int SKANIROV (unsigned char status, unsigned short velos, unsigned char datchnum, unsigned char nastr, unsigned char amp, unsigned char vb, unsigned int calib,unsigned char moders,unsigned char mf,unsigned int mp,unsigned char typefile)  ///// Режим сканирование
{

unsigned int bval; /// вывод мин числа на дисплей
static unsigned char cdrv; /// счетчик рисования линий и батареии с мм
static unsigned int minlev; /// минимальное значение в режиме сканирования
unsigned long ax=0;

//WR_CLASSM(CMSCANR);/// для памяти состояние

PORTB &= ~_BV(RES); /// Вывести из сброса ПЛИС
if (status == 2)
{
	if (moders==1) {minlev = SCANMAX; cdrv =0;  goto exf;} ///  сброс мин числа и выход

/*
if (cdrv == 0)
	{

	show_hicons(3);
	show_mmdiv();	
	draw_dline();
	draw_hline();
	draw_batl(vb);
	
	}
	cdrv++;*/
	

///calculmes(calib,velos,datchnum,nast)*/
ax = FAST_calculmes(calib,velos,datchnum);

	ax = ax/10;  /// округление
	ax = ax *10;
	 
	 if (minlev == 0) {minlev = SCANMAX;} /// первоначальная запись
	 
	 
	if (!(ax==0))
		{
			if (ax <= minlev) {minlev = ax;} /// запись минимального значения
		}
	
	
	
	
	
	if (!(minlev==SCANMAX))
	{
		//draw_scan_min(minlev);
	}
		else
	{
		//draw_scan_min(0); //// ноль при отсутсвии измерений
	}
		
///if ( PINH & (1<<acontpin)) 


			if (moders==2) ///// Нормальный режим работы - отображать измеряемую толщину
				{
			//	put_int_to_num_buffer(ax,0); //// Вывести измеряемую толщину на дисплей         
			//	show_num_buffer();
				}
				
				
			if (moders==3) ///// Отображение толщины минимальной - измеренной конец цикла сканирования
				{
				bval = minlev;
				if (bval == SCANMAX) {bval=0;}
			//	put_int_to_num_buffer(bval,0); //// Вывести минимальную  толщину на дисплей         
			//	show_num_buffer();
				}


	PORTB |= _BV(RES); ///  Сброс счетчиков плиc - Пониженное потребление

//put_int_to_snum_buffer(velos); /// скорость узк
//	show_snum_buffer();
//	show_msmin(0);


//draw_nastrn(nastr);


//draw_dachnum(datchnum,0);


//draw_samp(amp);
//draw_smem(mf,mp,typefile);  //// Отразить состояние памяти прибора



exf:;

}
return bval; /// Вернуть толщину отображенную на дисплее
}

/////////////////////////

unsigned int DIFFERNC (unsigned char status, unsigned short velos, unsigned char datchnum, unsigned char nastr, unsigned char amp, unsigned char vb, unsigned int calib, unsigned int DIFFU, unsigned char DIFFP,unsigned char mf,unsigned int mp, unsigned char typefile)  ///// Режим диффер
{

signed long ax=0;
unsigned char i=0;

if (status == 4)
{

PORTB &= ~_BV(RES); /// Вывести из сброса ПЛИС
show_hicons(4);
show_mmdiv();
draw_dline();
draw_hline();

	ax = calculmes(calib,velos,datchnum,nastr);
	
		if (!(ax == 0)) /// проверка на наличие измерение
		{
			if ((ax - DIFFU) >= 0) /// работа с отрицательными числами  -5 00   0   +5 00 мм
														{
															
															ax = ax-DIFFU;
															i=0;  /// знак плюс
															WR_CLASSM(CMDIFFP);/// для памяти состояние
														}
														else
														{
															ax = DIFFU-ax;
															i=1; // знак минус
															WR_CLASSM(CMDIFFM);/// для памяти состояние
														}

		}
	
	
	
	put_int_to_num_buffer(ax,0); //// Вывести толщину на дисплей
    show_num_buffer();
	
	draw_bminus(i,0); /// отобразить большой минус


	put_int_to_snum_buffer(velos); /// скорость узк
	show_snum_buffer();
	show_msmin(0);




draw_diff_u(DIFFU);// отобразить дифф уровень

draw_nastrn(nastr);
draw_dachnum(datchnum,0);
draw_samp(amp);
draw_smem(mf,mp,typefile);  //// Отразить состояние памяти прибора

draw_batl(vb);
	PORTB |= _BV(RES); ///  Сброс счетчиков плиc - Пониженное потребление

if (!( PINH & (1<<acontpin))) {_delay_ms(1500);}

}
return ax; /// Вернуть толщину отображенную на дисплее
}

/////////////////////////

unsigned int NONIUS (unsigned char status, unsigned short velos, unsigned char datchnum, unsigned char nastr, unsigned char amp, unsigned char vb, unsigned int calib, unsigned int NONIUSU, unsigned char NONIUSP,unsigned char mf,unsigned int mp,unsigned char typefile)  ///// Режим нониус
{
 
signed long ax=0;
signed int levd=0;

if (status == 3)
{

WR_CLASSM(CMNONIU);/// для памяти состояние

PORTB &= ~_BV(RES); /// Вывести из сброса ПЛИС
show_hicons(5);
show_mmdiv();
draw_dline();

draw_hline();
	
	levd = NONIUSU; /// значение нониуса -5мм = 0   +5мм = 1000 

	ax = calculmes(calib,velos,datchnum,nastr);
	
	if (!(ax == 0)) /// проверка на наличие измерение
		{
	
	
											
												if ((levd - 500) >= 0) /// работа с отрицательными числами  -5 00   0   +5 00 мм
														{
															levd = levd-500;
															ax = ax+levd;
														}
														else
														{
															levd = 500-levd;
															ax = ax-levd;
														}
		if (ax <= 0)	{ax = 0;}
		}
	
	
  
	put_int_to_num_buffer(ax,0); //// Вывести толщину на дисплей
	show_num_buffer();


put_int_to_snum_buffer(velos); /// скорость узк
	show_snum_buffer();
	show_msmin(0);


	
draw_non_d(NONIUSU);//// отобразить дельту

draw_nastrn(nastr);
draw_dachnum(datchnum,0);
draw_samp(amp);
draw_smem(mf,mp,typefile);  //// Отразить состояние памяти прибора
draw_batl(vb);
	PORTB |= _BV(RES); ///  Сброс счетчиков плиc - Пониженное потребление
if (!( PINH & (1<<acontpin))) {_delay_ms(1500);}

}
return ax; /// Вернуть толщину отображенную на дисплее
}




/////////////////////////////////////  RS-232 ////////////////////////////////////////////////////////////////

void USART_Init( unsigned int ubrr)  /// Инициализация 
{
/* Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/* Enable receiver and transmitter */
//UCSR0A = (1<<U2X0);

UCSR0B = (1<<RXEN0)|(1<<TXEN0);//(1<<RXCIE0)|
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<USBS0)|(3<<UCSZ00);

//SetBit(SREG,7);				// разрешаем все прерывания
}


void USART_SEND_Byte(unsigned char sb) //// Передача байта
{
while ( !( UCSR0A & (1<<UDRE0)) );
/* Put data into buffer, sends the data */
UDR0 = sb; 
}


unsigned char USART_Receive( void )
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) );
/* Get and return received data from buffer */
return UDR0;
}


///////////////////////////////////// Автоизменение скорости нарастания параметра при прокрутке

volatile unsigned char autoplusm(unsigned char st)
{

volatile static unsigned char cont=0, fastcont=0;
unsigned char iop=0;

	

	if (st==1) // состояние сброс 
	{
	
	cont =0; /// сброс счетчика
	fastcont=0;
	TIMSK1 = 0x00; /// таймер 1 выключить 
	return 0;
	}
	
	cont++; /// увеличить счетчик
	
	
if (st==0) /// если состояние счет
	{
	
	TIMSK1 = 0x01; //// Включить таймер 
	TCNT1=0x00; /// обнулить счетчик таймера1
	
	
	
	if (cont >= 50)
	{ 	cont = 50; 
		fastcont++; /// Самая быстрая прокрутка
			if (fastcont>= 70)
				{
				_delay_ms (step_speed0);
				fastcont=70;
				TCNT1=0x00;
				return 10;
				}
		
	TCNT1=0x00;
		
		return 2;
	} /// ускоренная прокрутка
	
	else 
	
	{


			if (cont<= 4)//// Замедленная на 5 шагов вначале прокрутка
			{
			TCCR1B = 0x00;
			TCNT1=0x00;
			_delay_ms(650);
					rkey();
					if (cont >= 2) // первое нажатие кнопки
						{
								_delay_ms(60); /// Если кнопку отпустили
								if (0==key_find())
								{
									rkey();
									TCCR1B = 0x02;
									return 0;
								}
						}
			//BEEP(1);
			TCCR1B = 0x02;
				rkey();
			return 1;
			
		}
	
	TCNT1=0x00;
	_delay_ms(step_apx);
	TCNT1=0x00;
	TCNT1=0x00;
	_delay_ms(step_apx);
	TCNT1=0x00;
	rkey();
	
	return 1; 
	} /// увеличит на 1
	
	}

return 0;

}














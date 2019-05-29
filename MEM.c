// Memory EEPROM mc  EEPROM i2c

#include <util/delay.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>


//#include "core.h"
//#include "eeprom.h"
#include "display.h"
#include "measuring.h"
#include "key.h"
#include "dev_cfg.h"
#include "MEM.h"
#include "main.h"
#include "Config.h"

unsigned char SEND_NUM[5] = { 0, 0, 0, 0, 0};
volatile unsigned char SEND_NUMX[8] = {32,32, 32,32, 32, 32, 32, 32};//0000

void initmem(void)  /// инициализация начальных установок в памяти прибора в случае пустой EEPROM мк.
{
	unsigned int i;
	

	
	////////////////////////////////////////////// запись в I2C EEPROM
	//i2c_init();
	
	//wfilename(0); /// записать номер файла.
	
	////////////////////////////////////////////// запись в EEPROM MCU
	eeprom_write_word (VELMEM,6045); //5940
	eeprom_write_byte (NUMDATC,2);
	eeprom_write_byte (MODES,0x00); //0x01
	eeprom_write_word (MEMCFG,10);
	eeprom_write_word (MEMPNT,0);		// номер страницы по умолчанию
	eeprom_write_word (STAT,0);
	                               //// КОНФИГУРАЦИЯ НАСТРОЕК 
	eeprom_write_byte (NASTR,0);	//1
	eeprom_write_word (CALIBD,3177); //24440
	eeprom_write_byte (MINUTES_OFF,0);	 ///  минут, автовыключение 0=никогда
	
	eeprom_write_word (VEL1,5930);  /// СКОРОСТИ ДЛЯ НАСТРОЕК
	eeprom_write_word (VEL2,5930);
	eeprom_write_word (VEL3,5930);
	eeprom_write_word (VEL4,5930);
	eeprom_write_word (VEL5,5930);
	eeprom_write_word (VEL6,5930);
	eeprom_write_word (VEL7,5930);
	eeprom_write_word (VEL8,5930);
	eeprom_write_word (VEL9,5930);
	eeprom_write_word (VEL10,2300);
										/// Запись калибровок для настроек
// 	eeprom_write_word (CALB1,24440); //24440 1339
// 	eeprom_write_word (CALB2,24440);
// 	eeprom_write_word (CALB3,24440);
// 	eeprom_write_word (CALB4,24440);
// 	eeprom_write_word (CALB5,24440);
// 	eeprom_write_word (CALB6,24440);
// 	eeprom_write_word (CALB7,24440);
// 	eeprom_write_word (CALB8,24440);
// 	eeprom_write_word (CALB9,24440);
// 	eeprom_write_word (CALB10,24440);

	eeprom_write_word (CALB1,calobr3mm); //24440 1339
	eeprom_write_word (CALB2,calobr3mm);
	eeprom_write_word (CALB3,calobr3mm);
	eeprom_write_word (CALB4,calobr3mm);
	eeprom_write_word (CALB5,calobr3mm);
	eeprom_write_word (CALB6,calobr3mm);
	eeprom_write_word (CALB7,calobr3mm);
	eeprom_write_word (CALB8,calobr5mm);
	eeprom_write_word (CALB9,calobr20mm);
	eeprom_write_word (CALB10,calobr20mm);


#ifdef   maket_build
	eeprom_write_byte (BEEP_MODE,0x01); /// Звук включен 0x01
#else
	eeprom_write_byte (BEEP_MODE,0x00); /// Звук выключен
#endif	
//	eeprom_write_byte (BEEP_MODE,0x00); /// Звук включен 0x01
	
	
	eeprom_write_byte (AMP1,25);  /// УСИЛЕНИЕ ДЛЯ НАСТРОЕК
	eeprom_write_byte (AMP2,25);
	eeprom_write_byte (AMP3,25);
	eeprom_write_byte (AMP4,25);
	eeprom_write_byte (AMP5,25);
	eeprom_write_byte (AMP6,25);
	eeprom_write_byte (AMP7,25);
	eeprom_write_byte (AMP8,25);
	eeprom_write_byte (AMP9,25);
	eeprom_write_byte (AMP10,25);
	
	eeprom_write_byte (DATCH1,2);  /// Датчик в настройках
	eeprom_write_byte (DATCH2,2);
	eeprom_write_byte (DATCH3,2);
	eeprom_write_byte (DATCH4,2);
	eeprom_write_byte (DATCH5,2);
	eeprom_write_byte (DATCH6,2);
	eeprom_write_byte (DATCH7,2);
	eeprom_write_byte (DATCH8,2);
	eeprom_write_byte (DATCH9,2);
	eeprom_write_byte (DATCH10,7);
	
	eeprom_write_byte (MODE1,0);  /// Режим работы в настройках
	eeprom_write_byte (MODE2,0);
	eeprom_write_byte (MODE3,0);
	eeprom_write_byte (MODE4,0);
	eeprom_write_byte (MODE5,0);
	eeprom_write_byte (MODE6,0);
	eeprom_write_byte (MODE7,0);
	eeprom_write_byte (MODE8,0);
	eeprom_write_byte (MODE9,0);
	eeprom_write_byte (MODE10,0);
	
	
	eeprom_write_word (RAZB_H1,1023);  /// Пороги разбраковки в настройках 
	eeprom_write_word (RAZB_L1,340);
	
	eeprom_write_word (RAZB_H2,1500);
	eeprom_write_word (RAZB_L2,1000);
	
	eeprom_write_word (RAZB_H3,1200);
	eeprom_write_word (RAZB_L3,100);
	
	eeprom_write_word (RAZB_H4,600);
	eeprom_write_word (RAZB_L4,256);
	
	eeprom_write_word (RAZB_H5,670);
	eeprom_write_word (RAZB_L5,50);
	
	eeprom_write_word (RAZB_H6,540);
	eeprom_write_word (RAZB_L6,100);
	
	eeprom_write_word (RAZB_H7,90);
	eeprom_write_word (RAZB_L7,70);
	
	eeprom_write_word (RAZB_H8,2020);
	eeprom_write_word (RAZB_L8,100);
	
	eeprom_write_word (RAZB_H9,470);
	eeprom_write_word (RAZB_L9,40);
	
	eeprom_write_word (RAZB_H10,350);
	eeprom_write_word (RAZB_L10,40);
	
	
	eeprom_write_word (DIFFU1,500);  /// Уровнень в режиме "Отклонение" в настройках
	eeprom_write_word (DIFFU2,900);
	eeprom_write_word (DIFFU3,100);
	eeprom_write_word (DIFFU4,20);
	eeprom_write_word (DIFFU5,20);
	eeprom_write_word (DIFFU6,30);
	eeprom_write_word (DIFFU7,505);
	eeprom_write_word (DIFFU8,700);
	eeprom_write_word (DIFFU9,30);
	eeprom_write_word (DIFFU10,40);
	
	
	eeprom_write_word (NONIUSU1,nonius_half_range); /// Уровни в режиме нониус в настройках
	eeprom_write_word (NONIUSU2,nonius_half_range);
	eeprom_write_word (NONIUSU3,nonius_half_range);
	eeprom_write_word (NONIUSU4,nonius_half_range);
	eeprom_write_word (NONIUSU5,nonius_half_range);
	eeprom_write_word (NONIUSU6,nonius_half_range);
	eeprom_write_word (NONIUSU7,nonius_half_range);
	eeprom_write_word (NONIUSU8,nonius_half_range);
	eeprom_write_word (NONIUSU9,nonius_half_range);
	eeprom_write_word (NONIUSU10,nonius_half_range);
	
	//for (i=0;i<10;i++)eeprom_write_word(NONIUSP1 + i*2,nonius_half_range);
	
	eeprom_write_byte (BRIGHT,0); /// яркость дисплея 1 - 5 текущ 4
	
	//eeprom_write_dword (TNAR,0); ///Запись наработки в память
	CLRTR();						//Запись наработки в память
//	zav_num=0x31313131;
	eeprom_write_byte (ZNUM0,zav_num>>24);
	eeprom_write_byte (ZNUM1,zav_num>>16);
	eeprom_write_byte (ZNUM2,zav_num>>8);
	eeprom_write_byte (ZNUM3,zav_num);
	
	
//////////////////////////////////////////////// journal ////////////////////////////////////////////

	eeprom_write_byte(journal_addr,0);								// размер журнала в байтах (journal_size_off=4 байта)
	eeprom_write_byte(journal_addr+1,0);
	eeprom_write_byte(journal_addr+2,0);
	eeprom_write_byte(journal_addr+3,0);

	eeprom_write_word(journal_addr+journal_size_off,entry_size);	// размер записи в байтах (entry_size_off= 2 байта)
	eeprom_write_word(journal_addr+journal_size_off+entry_size_off,ee_page_numb);	// номер страницы для записи ee_page_numb (page_size_off=2 байта)

	for(i=0;i<page_numb_max;i++)
		eeprom_write_dword(get_page_size(i),0);						// очищение таблицы страниц (количества записей на каждой странице)

/////////////////////////////////////////////////////////////////////////////////////////////////////	 

};

unsigned long corrector (unsigned long vals,unsigned char dach)//// Таблицы коррекции датчиков  возвращает и принимает число импульсов * 32.!!!

{
unsigned long ix=0;

switch (dach) //без -1
	{
	
	case 0: ix = cord1(vals); break; //П112-10.0-8\2-Т003	3мм кал обр
	case 1: ix = cord2(vals); break; //П112-5.0-10\2-Т003	3мм кал обр
	case 2: ix = cord3(vals); break; //П112-2.5-12\2-Т003	3мм кал обр
	
	case 3: ix = cord4(vals); break; //П112-2.5Т-12\2-Б   //П112-5.0Т-12\2-Б  одна таблица для 2 датчиков 4 и 5	3мм кал обр
	case 4: ix = cord4(vals); break; //П112-5.0Т-12\2-Б	
	case 5: ix = cord6(vals); break; //П112-2.5-12\2А		3мм кал обр
	
	case 6: ix = cord7(vals); break; //П111-1.25-20\2А 	5мм кал обр !!!!
	
	case 7: ix = vals; break; //П111-1.25К20 //// таблиц не требуется 20мм кал обр !!!
	case 8: ix = vals; break; //П111-1.25П20 //// таблиц не требуется 20мм кал обр !!!
	
	
	/*case 1: ix = cord1(vals); break; //П112-10.0-8\2-Т003
	case 2: ix = cord2(vals); break; //П112-5.0-10\2-Т003
	case 3: ix = cord3(vals); break; //П112-2.5-12\2-Т003
	case 4: ix = cord4(vals); break; //П112-2.5Т-12\2-Б
	case 5: ix = cord5(vals); break; //П112-5.0Т-12\2-Б
	case 6: ix = cord6(vals); break; //П111-1.25К20
	case 7: ix = cord7(vals); break; //П111-1.25П20
	case 8: ix = cord8(vals); break; //П111-1.25-20\2А*/
	}

return ix;

}
////-------------------------------------------------------------------------------------------------------------------------------------
unsigned long cord1 (unsigned long val) //// Таблица коррекции датчика 1   10-8\2T

{
	/// нижнее значение    ---   /// верхнее значение   порога в диапазоне
if ((val >= 30) && (val <=64))  // поправка в ММ для диапазона толщин в мм 1МЗР - 0.01мм 9999- 99.99мм   10000 - 100.0 мм
{
val = val-17;/// Сама поправка 1
goto ex1;
}


if ((val >= 64) && (val <=76))  // 
{
val = val-16;/// Сама поправка 2
goto ex1;
}


if ((val >= 76) && (val <=86))  // 
{
val = val-14;/// Сама поправка 2
goto ex1;
}

if ((val >= 86) && (val <=95))  // 
{
val = val-14;/// Сама поправка 3
goto ex1;
}

if ((val >= 95) && (val <=120))  // 
{
val = val-14;/// Сама поправка 4
goto ex1;
}


if ((val >= 120) && (val <=150))  // 
{
val = val-9;/// Сама поправка 5
goto ex1;
}




if ((val >= 150) && (val <=176))  // 
{
val = val-10;/// Сама поправка 5
goto ex1;
}



if ((val >= 176) && (val <=230))  // 
{
val = val-10;/// Сама поправка 5
goto ex1;
}



if ((val >= 230) && (val <=275))  // 
{
val = val-9;/// Сама поправка 5
goto ex1;
}



if ((val >= 275) && (val <=290))  // 
{
val = val-8;/// Сама поправка 5
goto ex1;
}



if ((val >= 290) && (val <=310))  // калибровка 3 ММ 0
{
val = val;/// Сама поправка 6
goto ex1;
}




if ((val >= 310) && (val <=350))  // 
{
val = val-1;/// Сама поправка 7
goto ex1;
}

if ((val >= 350) && (val <=450))  // 
{
val = val-1;/// Сама поправка 8
goto ex1;
}



if ((val >= 450) && (val <=490))  // 
{
val = val+4;/// Сама поправка 9
goto ex1;
}




if ((val >= 490) && (val <=550))  // 
{
val = val+5;/// Сама поправка 9
goto ex1;
}

if ((val >= 550) && (val <=650))  // 
{
val = val+10;/// Сама поправка 10
goto ex1;
}

if ((val >= 650) && (val <=710))  // 
{
val = val+13;/// Сама поправка 11
goto ex1;
}



if ((val >= 710) && (val <=750))  // 
{
val = val+14;/// Сама поправка 12
goto ex1;
}



if ((val >= 750) && (val <=830))  // 
{
val = val+13;/// Сама поправка 12
goto ex1;
}



if ((val >= 830) && (val <=875))  // 
{
val = val+12;/// Сама поправка 12
goto ex1;
}



if ((val >= 875) && (val <=950))  // 
{
val = val+20;/// Сама поправка 13
goto ex1;
}


if ((val >= 950) && (val <=1050))  // 
{
val = val+19;/// Сама поправка 14
goto ex1;
}

if ((val >= 1050) && (val <=1110))  // 
{
val = val+21;/// Сама поправка 15
goto ex1;
}


if ((val >= 1110) && (val <=1350))  // 
{
val = val+20;/// Сама поправка 15
goto ex1;
}





if ((val >= 1350) && (val <=1830))  // 
{
val = val+21;/// Сама поправка 16
goto ex1;
}




if ((val >= 1830) && (val <=1850))  // 
{
val = val+26;/// Сама поправка 17
goto ex1;
}




if ((val >= 1850) && (val <=1875))  // 
{
val = val+26;/// Сама поправка 18
goto ex1;
}


if ((val >= 1875) && (val <=1930))  // 
{
val = val+25;/// Сама поправка 18
goto ex1;
}


if ((val >= 1930) && (val <=1970))  // 
{
val = val+24;/// Сама поправка 18
goto ex1;
}

if ((val >= 1970) && (val <=2100))  // 
{
val = val+23;/// Сама поправка 18
goto ex1;
}

if ((val >= 2100) && (val <=2200))  // 
{
val = val+22;/// Сама поправка 18
goto ex1;
}



if ((val >= 2200) && (val <=2300))  // 
{
val = val+24;/// Сама поправка 19
goto ex1;
}

if ((val >= 2300) && (val <=2400))  // 
{
val = val+23;/// Сама поправка 19
goto ex1;
}

if ((val >= 2400) && (val <=2475))  // 
{
val = val+22;/// Сама поправка 19
goto ex1;
}

if ((val >= 2475) && (val <=2600))  // 
{
val = val+21;/// Сама поправка 19
goto ex1;
}



if ((val >= 2600) && (val <=2700))  // 
{
val = val+20;/// Сама поправка 20
goto ex1;
}

if ((val >= 2700) && (val <=2800))  // 
{
val = val+10;/// Сама поправка 20
goto ex1;
}


if ((val >= 2800) && (val <=2900))  // 
{
val = val;/// Сама поправка 20
goto ex1;
}

if ((val >= 2900) && (val <=3000))  // 
{
val = val-10;/// Сама поправка 20
goto ex1;
}


if ((val >= 3000) && (val <=3250))  // 
{
val = val-22;/// Сама поправка 20
goto ex1;
}


if ((val >= 3250) && (val <=3750))  // 
{
val = val-25;/// Сама поправка 21
goto ex1;
}

if ((val >= 3750) && (val <=4250))  // 
{
val = val-28;/// Сама поправка 22
goto ex1;
}

if ((val >= 4250) && (val <=4750))  // 
{
val = val-36;/// Сама поправка 23
goto ex1;
}

if ((val >= 4750) && (val <=6250))  // 
{
val = val-38;/// Сама поправка 24
goto ex1;
}

if ((val >= 6250) && (val <=8250))  // 
{
val = val-40;/// Сама поправка 25
goto ex1;
}

if ((val >= 8250) && (val <=9500))  // 
{
val = val-42;/// Сама поправка 26
goto ex1;
}

if ((val >= 9500) && (val <=15000))  // 
{
val = val-54;/// Сама поправка 27
goto ex1;
}

if ((val >= 15000) && (val <=25000))  // 
{
val = val-60;/// Сама поправка 28
goto ex1;
}

if ((val >= 25000) && (val <=35000))  // 
{
val = val-70;/// Сама поправка 29
goto ex1;
}

if ((val >= 35000) && (val <=45000))  // 
{
val = val-80;/// Сама поправка 30
goto ex1;
}

ex1:;
return val;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned long cord2 (unsigned long val) //// Таблица коррекции датчика 2 П112-5.0-10\2-Т003

{
	/// нижнее значение    ---   /// верхнее значение   порога в диапазоне
if ((val >= 30) && (val <=76))  // поправка в ММ для диапазона толщин в мм 1МЗР - 0.01мм 9999- 99.99мм   10000 - 100.0 мм
{
val = val-7;/// Сама поправка 1 -10
goto ex1;
}

if ((val >= 76) && (val <=86))  // 
{
val = val-6;/// Сама поправка 2 -10
goto ex1;
}

if ((val >= 86) && (val <=95))  // 
{
val = val-5;/// Сама поправка 3 -13
goto ex1;
}

if ((val >= 95) && (val <=130))  //
{
	val = val-4;/// Сама поправка 4
	goto ex1;
}

if ((val > 130) && (val <=150))  // 
{
val = val-3;/// Сама поправка 4
goto ex1;
}

if ((val > 150) && (val <=170))  //
{
	val = val-2;/// Сама поправка 4
	goto ex1;
}
if ((val > 170) && (val <=200))  // 
{
val = val-1;/// Сама поправка 5
goto ex1;
}

if ((val > 200) && (val <=270))  //
{
	//val = val-9;/// Сама поправка 5
	goto ex1;
}
if ((val >= 270) && (val <=310))  // калибровка 3 ММ 0
{
//val = val;/// Сама поправка 6
goto ex1;
}

if ((val >= 310) && (val <=350))  // 
{
val = val-5;/// Сама поправка 7 -7
goto ex1;
}

if ((val >= 350) && (val <=450))  // -6
{
val = val-4;/// Сама поправка 8
goto ex1;
}

if ((val >= 450) && (val <=550))  // 
{
val = val-3;/// Сама поправка 9 -5
goto ex1;
}

if ((val >= 550) && (val <=650))  // 
{
val = val-1;/// Сама поправка 10  -3
goto ex1;
}

if ((val >= 650) && (val <=750))  // 
{
val = val;/// Сама поправка 11  +1
goto ex1;
}

if ((val >= 750) && (val <=850))  // 
{
val = val+3;/// Сама поправка 12  +5
goto ex1;
}

if ((val >= 850) && (val <=950))  // 
{
val = val+5;/// Сама поправка 13 +7
goto ex1;
}

if ((val >= 950) && (val <=1050))  // 
{
val = val+8;/// Сама поправка 14 +11
goto ex1;
}

if ((val >= 1050) && (val <=1350))  // 
{


val = val+19;/// Сама поправка 15
goto ex1;
}

if ((val >= 1350) && (val <=1650))  // 
{
val = val+20;/// Сама поправка 16
goto ex1;
}

if ((val >= 1650) && (val <=1900))  // 
{
val = val+20;/// Сама поправка 17
goto ex1;
}

if ((val >= 1900) && (val <=2250))  // 
{
val = val+25;/// Сама поправка 18
goto ex1;
}

if ((val >= 2250) && (val <=2750))  // 
{
val = val+28;/// Сама поправка 19
goto ex1;
}

if ((val >= 2750) && (val <=3250))  // 
{
val = val+29+5;/// Сама поправка 20
goto ex1;
}

if ((val >= 3250) && (val <=3750))  // 
{
val = val+33+10;/// Сама поправка 21
goto ex1;
}

if ((val >= 3750) && (val <=4250))  // 
{
val = val+34+15;/// Сама поправка 22
goto ex1;
}

if ((val >= 4250) && (val <=4750))  // 
{
val = val+34+20;/// Сама поправка 23
goto ex1;
}

if ((val >= 4750) && (val <=6250))  // 
{
val = val+34+25;/// Сама поправка 24
goto ex1;
}

if ((val >= 6250) && (val <=8250))  // 
{
val = val+34+30;/// Сама поправка 25 +34
goto ex1;
}

if ((val >= 8250) && (val <=9500))  // 
{
val = val+34+50;/// Сама поправка 26 +36
goto ex1;
}

if ((val >= 9500) && (val <=15000))  // 
{
val = val+34+50;/// Сама поправка 27 +34
goto ex1;
}

if ((val >= 15000) && (val <=25000))  // 
{
val = val+40+50;/// Сама поправка 28
goto ex1;
}

if ((val >= 25000) && (val <=35000))  // 
{
val = val+20;/// Сама поправка 29
goto ex1;
}

if ((val >= 35000) && (val <=45000))  // 
{
//val = val;/// Сама поправка 30
goto ex1;
}

ex1:;
return val;
}




unsigned long cord3 (unsigned long val) //// Таблица коррекции датчика 3 2.5-12\2Т

{
	/// нижнее значение    ---   /// верхнее значение   порога в диапазоне
if ((val >= 30) && (val <=76))  // поправка в ММ для диапазона толщин в мм 1МЗР - 0.01мм 9999- 99.99мм   10000 - 100.0 мм
{
val = val;/// Сама поправка 1
goto ex1;
}

if ((val >= 76) && (val <=86))  // 
{
val = val;/// Сама поправка 2
goto ex1;
}

if ((val >= 86) && (val <=95))  // 
{
val = val;/// Сама поправка 3
goto ex1;
}

if ((val >= 95) && (val <=150))  // 
{
val = val-4;/// Сама поправка 4
goto ex1;
}

if ((val >= 150) && (val <=270))  // 
{
val = val-15;/// Сама поправка 5
goto ex1;
}

if ((val >= 270) && (val <=310))  // калибровка 3 ММ 0
{
val = val;/// Сама поправка 6
goto ex1;
}

if ((val >= 310) && (val <=350))  // 
{
val = val+1;/// Сама поправка 7
goto ex1;
}

if ((val >= 350) && (val <=450))  // 
{
val = val+2;/// Сама поправка 8
goto ex1;
}

if ((val >= 450) && (val <=550))  // 
{
val = val+4;/// Сама поправка 9
goto ex1;
}

if ((val >= 550) && (val <=650))  // 
{
val = val+8;/// Сама поправка 10
goto ex1;
}

if ((val >= 650) && (val <=750))  // 
{
val = val+12;/// Сама поправка 11
goto ex1;
}

if ((val >= 750) && (val <=850))  // 
{
val = val+12;/// Сама поправка 12
goto ex1;
}

if ((val >= 850) && (val <=950))  // 
{
val = val+15;/// Сама поправка 13
goto ex1;
}

if ((val >= 950) && (val <=1050))  // 
{
val = val+16;/// Сама поправка 14
goto ex1;
}

if ((val >= 1050) && (val <=1350))  // 
{
val = val+18;/// Сама поправка 15
goto ex1;
}

if ((val >= 1350) && (val <=1650))  // 
{
val = val+25;/// Сама поправка 16
goto ex1;
}

if ((val >= 1650) && (val <=1900))  // 
{
val = val+28;/// Сама поправка 17
goto ex1;
}

if ((val >= 1900) && (val <=2250))  // 
{
val = val+30;/// Сама поправка 18
goto ex1;
}

if ((val >= 2250) && (val <=2750))  // 
{
val = val+34;/// Сама поправка 19
goto ex1;
}

if ((val >= 2750) && (val <=3250))  // 
{
val = val+40;/// Сама поправка 20
goto ex1;
}

if ((val >= 3250) && (val <=3750))  // 
{
val = val+42;/// Сама поправка 21
goto ex1;
}

if ((val >= 3750) && (val <=4250))  // 
{
val = val+42;/// Сама поправка 22
goto ex1;
}

if ((val >= 4250) && (val <=4750))  // 
{
val = val+44;/// Сама поправка 23
goto ex1;
}

if ((val >= 4750) && (val <=6250))  // 
{
val = val+46;/// Сама поправка 24
goto ex1;
}

if ((val >= 6250) && (val <=8250))  // 
{
val = val+44;/// Сама поправка 25
goto ex1;
}

if ((val >= 8250) && (val <=9500))  // 
{
val = val+40;/// Сама поправка 26
goto ex1;
}

if ((val >= 9500) && (val <=15000))  // 
{
val = val+35;/// Сама поправка 27
goto ex1;
}

if ((val >= 15000) && (val <=25000))  // 
{
val = val+30;/// Сама поправка 28
goto ex1;
}

if ((val >= 25000) && (val <=35000))  // 
{
val = val;/// Сама поправка 29
goto ex1;
}

if ((val >= 35000) && (val <=45000))  // 
{
val = val;/// Сама поправка 30
goto ex1;
}

ex1:;
return val;
}



unsigned long cord4 (unsigned long val) //// Таблица коррекции датчика 4 П112-2.5Т-12/2-Б
 {
	/// нижнее значение    ---   /// верхнее значение   порога в диапазоне
if ((val >= 30) && (val <=76))  // поправка в ММ для диапазона толщин в мм 1МЗР - 0.01мм 9999- 99.99мм   10000 - 100.0 мм
{
val = val;/// Сама поправка 1
goto ex1;
}

if ((val >= 76) && (val <=86))  // 
{
val = val;/// Сама поправка 2
goto ex1;
}

if ((val >= 86) && (val <=95))  // 
{
val = val-2;/// Сама поправка 3
goto ex1;
}

	if ((val >= 95) && (val <=120))  // 
	{
	val = val-2;/// Сама поправка 4
	goto ex1;
	}

	if ((val >= 120) && (val <=140))  // 
	{
	val = val-3;/// Сама поправка 4
	goto ex1;
	}

	if ((val >= 140) && (val <=170))  // 
	{
	val = val-4;/// Сама поправка 4
	goto ex1;
	}
	
	if ((val >= 170) && (val <=185))  // 
	{
	val = val-5;/// Сама поправка 4
	goto ex1;
	}


if ((val >= 185) && (val <=270))  // 
{
val = val-6;/// Сама поправка 5
goto ex1;
}

if ((val >= 270) && (val <=310))  // калибровка 3 ММ 0
{
val = val;/// Сама поправка 6
goto ex1;
}

if ((val >= 310) && (val <=350))  // 
{
//val = val-6;/// Сама поправка 7
goto ex1;
}

if ((val >= 350) && (val <=450))  // 
{
//val = val-7;/// Сама поправка 8
goto ex1;
}

if ((val >= 450) && (val <=550))  // 
{
//val = val-7;/// Сама поправка 9
goto ex1;
}

if ((val >= 550) && (val <=650))  // 
{
//val = val-8;/// Сама поправка 10
goto ex1;
}

if ((val >= 650) && (val <=750))  // 
{
//val = val-7;/// Сама поправка 11
goto ex1;
}

if ((val >= 750) && (val <=850))  // 
{
//val = val-5;/// Сама поправка 12
goto ex1;
}

if ((val >= 850) && (val <=950))  // 
{
//val = val-2;/// Сама поправка 13
goto ex1;
}

if ((val >= 950) && (val <=1050))  // 
{
//val = val-2;/// Сама поправка 14
goto ex1;
}

if ((val >= 1050) && (val <=1350))  // 
{
//val = val;/// Сама поправка 15
goto ex1;
}

if ((val >= 1350) && (val <=1650))  // 
{
//val = val+2;/// Сама поправка 16
goto ex1;
}

if ((val >= 1650) && (val <=1900))  // 
{
//val = val+4;/// Сама поправка 17
goto ex1;
}

if ((val >= 1900) && (val <=2250))  // 
{
//val = val+6;/// Сама поправка 18
goto ex1;
}

if ((val >= 2250) && (val <=2750))  // 
{
//val = val+8;/// Сама поправка 19
goto ex1;
}

if ((val >= 2750) && (val <=3250))  // 
{
//val = val+12;/// Сама поправка 20
goto ex1;
}

if ((val >= 3250) && (val <=3750))  // 
{
//val = val+16;/// Сама поправка 21
goto ex1;
}

if ((val >= 3750) && (val <=4250))  // 
{
//val = val+20;/// Сама поправка 22
goto ex1;
}

if ((val >= 4250) && (val <=4750))  // 
{
//val = val+30;/// Сама поправка 23
goto ex1;
}

if ((val >= 4750) && (val <=6250))  // 
{
//val = val+16;/// Сама поправка 24
goto ex1;
}

if ((val >= 6250) && (val <=8250))  // 
{
//val = val+18;/// Сама поправка 25
goto ex1;
}

if ((val >= 8250) && (val <=9500))  // 
{
//val = val+20;/// Сама поправка 26
goto ex1;
}

if ((val >= 9500) && (val <=15000))  // 
{
//val = val+20;/// Сама поправка 27
goto ex1;
}

if ((val >= 15000) && (val <=25000))  // 
{
//val = val+20;/// Сама поправка 28
goto ex1;
}

if ((val >= 25000) && (val <=35000))  // 
{
//val = val+20;/// Сама поправка 29
goto ex1;
}

if ((val >= 35000) && (val <=42000))  // 
{
//val = val+20;/// Сама поправка 29
goto ex1;
}

if ((val >= 42000) && (val <=55000))  // 
{
//val = val;/// Сама поправка 30
goto ex1;
}

ex1:;

return val;
}

unsigned long cord5 (unsigned long val) //// Таблица коррекции датчика 5 П112-5.0Т-12/2-Б исполльзуется табл 4 

{
return val;
}

unsigned long cord6 (unsigned long val) //// Таблица коррекции датчика 6 П112-2.5-12/2А
{
	/// нижнее значение    ---   /// верхнее значение   порога в диапазоне
				// поправка в ММ для диапазона толщин в мм 1МЗР - 0.01мм 9999- 99.99мм   10000 - 100.0 мм


if ((val >= 270) && (val <=310))  // калибровка 3 ММ 0
{
val = val;/// Сама поправка 6
goto ex1;
}

if ((val >= 310) && (val <=350))  // 
{
val = val+3;/// Сама поправка 7
goto ex1;
}

if ((val >= 350) && (val <=450))  // 
{
val = val+5;/// Сама поправка 8
goto ex1;
}

if ((val >= 450) && (val <=550))  // 
{
val = val+15;/// Сама поправка 9
goto ex1;
}

if ((val >= 550) && (val <=650))  // 
{
val = val+23;/// Сама поправка 10
goto ex1;
}

if ((val >= 650) && (val <=750))  // 
{
val = val+30;/// Сама поправка 11
goto ex1;
}

if ((val >= 750) && (val <=850))  // 
{
val = val+30;/// Сама поправка 12
goto ex1;
}

if ((val >= 850) && (val <=950))  // 
{
val = val+36;/// Сама поправка 13
goto ex1;
}

if ((val >= 950) && (val <=1050))  // 
{
val = val+40;/// Сама поправка 14
goto ex1;
}

if ((val >= 1050) && (val <=1350))  // 
{
val = val+50;/// Сама поправка 15
goto ex1;
}

if ((val >= 1350) && (val <=1650))  // 
{
val = val+53;/// Сама поправка 16
goto ex1;
}

if ((val >= 1650) && (val <=1900))  // 
{
val = val+60;/// Сама поправка 17
goto ex1;
}

if ((val >= 1900) && (val <=2250))  // 
{
val = val+62;/// Сама поправка 18
goto ex1;
}

if ((val >= 2250) && (val <=2750))  // 
{
val = val+64;/// Сама поправка 19
goto ex1;
}

if ((val >= 2750) && (val <=3250))  // 
{
val = val+68;/// Сама поправка 20
goto ex1;
}

if ((val >= 3250) && (val <=3750))  // 
{
val = val+70;/// Сама поправка 21
goto ex1;
}

if ((val >= 3750) && (val <=4250))  // 
{
val = val+75;/// Сама поправка 22
goto ex1;
}

if ((val >= 4250) && (val <=4750))  // 
{
val = val+80;/// Сама поправка 23
goto ex1;
}

if ((val >= 4750) && (val <=6250))  // 
{
val = val+70;/// Сама поправка 24
goto ex1;
}

if ((val >= 6250) && (val <=8250))  // 
{
val = val+60;/// Сама поправка 25
goto ex1;
}

if ((val >= 8250) && (val <=9500))  // 
{
val = val+50;/// Сама поправка 26
goto ex1;
}

if ((val >= 9500) && (val <=15000))  // 
{
val = val+40;/// Сама поправка 27
goto ex1;
}

if ((val >= 15000) && (val <=25000))  // 
{
val = val+40;/// Сама поправка 28
goto ex1;
}

if ((val >= 25000) && (val <=35000))  // 
{
val = val+40;/// Сама поправка 29
goto ex1;
}


ex1:;
return val;
}

unsigned long cord7 (unsigned long val) //// Таблица коррекции датчика 7 П112-1.25-20\2А  к обр 5мм!!!
{
	/// нижнее значение    ---   /// верхнее значение   порога в диапазоне
								// поправка в ММ для диапазона толщин в мм 1МЗР - 0.01мм 9999- 99.99мм   10000 - 100.0 мм

if ((val >= 290) && (val <=350))  // 
{
val = val-5;/// Сама поправка 1
goto ex1;
}

if ((val >= 350) && (val <=480))  // 
{
val = val-4;/// Сама поправка 2
goto ex1;
}

if ((val >= 480) && (val <=510))  //  5.мм калибр обр 0!!!
{
val = val;/// Сама поправка 3
goto ex1;
}

if ((val >= 510) && (val <=560))  // 
{
val = val+4;/// Сама поправка 4
goto ex1;
}

if ((val >= 560) && (val <=650))  // 
{
val = val+6;/// Сама поправка 5
goto ex1;
}

if ((val >= 650) && (val <=750))  // 
{
val = val+8;/// Сама поправка 6
goto ex1;
}

if ((val >= 750) && (val <=850))  // 
{
val = val+16;/// Сама поправка 7
goto ex1;
}

if ((val >= 850) && (val <=950))  // 
{
val = val+22;/// Сама поправка 8
goto ex1;
}

if ((val >= 950) && (val <=1050))  // 
{
val = val+23;/// Сама поправка 9
goto ex1;
}

if ((val >= 1050) && (val <=1350))  // 
{
val = val+28;/// Сама поправка 10
goto ex1;
}

if ((val >= 1350) && (val <=1650))  // 
{
val = val+36;/// Сама поправка 11
goto ex1;
}

if ((val >= 1650) && (val <=1900))  // 
{
val = val+45;/// Сама поправка 12
goto ex1;
}

if ((val >= 1900) && (val <=2250))  // 
{
val = val+48;/// Сама поправка 13
goto ex1;
}

if ((val >= 2250) && (val <=2750))  // 
{
val = val+55;/// Сама поправка 14
goto ex1;
}

if ((val >= 2750) && (val <=3250))  // 
{
val = val+70;/// Сама поправка 15
goto ex1;
}

if ((val >= 3250) && (val <=3750))  // 
{
val = val+70;/// Сама поправка 16
goto ex1;
}

if ((val >= 3750) && (val <=4250))  // 
{
val = val+72;/// Сама поправка 17
goto ex1;
}

if ((val >= 4250) && (val <=4750))  // 
{
val = val+80;/// Сама поправка 18
goto ex1;
}

if ((val >= 4750) && (val <=6250))  // 
{
val = val+65;/// Сама поправка 19
goto ex1;
}

if ((val >= 6250) && (val <=8250))  // 
{
val = val+58;/// Сама поправка 20
goto ex1;
}

if ((val >= 8250) && (val <=9500))  // 
{
val = val+48;/// Сама поправка 21
goto ex1;
}

if ((val >= 9500) && (val <=15000))  // 
{
val = val+46;/// Сама поправка 22
goto ex1;
}

if ((val >= 15000) && (val <=25000))  // 
{
val = val+40;/// Сама поправка 23
goto ex1;
}

if ((val >= 25000) && (val <=35000))  // 
{
val = val;/// Сама поправка 24
goto ex1;
}

if ((val >= 35000) && (val <=45000))  // 
{
val = val;/// Сама поправка 25
goto ex1;
}

ex1:;
return val;
}


unsigned long cord8 (unsigned long val) //// Таблица коррекции датчика 8

{
return val;
}


unsigned long cord9 (unsigned long val) //// Таблица коррекции датчика 9

{
return val;
}


////////////////////////////////////Работа с ПАМЯТЬЮ //////////////////////////////////////////////////////
/*

void MEMORY_MEN(unsigned char mode) //// Режим память основное меню ---- 
{
unsigned char io=1,bo=0,mf=0,tf=0;
unsigned int mp=0;

agn:;

tf=filetype();  /// Прочитать тип файлов
mf=filename(); /// узнать номер текущего файла
mp=rfd(mf,tf); /// прочитать файл   mf- номер файла tf- тип файла.


cls();
//show_mpos(8,20,0);///Память


show_MEMmenu(io,mf,mp,tf);
draw_memoline (12,7,48); // строчка внизу экрана "Меню память"
draw_smem(mf,mp,tf);	// количество ячеек

BEEP(2);


			bo=keymem;  /// :Ждать пока отпустят кнопку
			
			while (bo==keymem)
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
 
	
	if (key_find()==keydown)   /// двигать курсор вверх вниз/// с циклической прокруткой.
	{   _delay_ms (600); //!820
		key_find();
		io ++;
		if (io==6) { io = 1;}
		BEEP(4);
		show_MEMmenu(io,mf,mp,tf);
	}
	
	if (key_find()==keyup)
	{   _delay_ms (600); //!820
		key_find();	
		io --;
		if (io==0) { io =5;}
		BEEP(3);
		show_MEMmenu(io,mf,mp,tf);	
	}
	
	
	if (key_find()==keymem) /// Выход по кнопке по которой вошли --- ждет когда ее отпустят тогда выход.
	{
	io=keymem;
	
	while (io==keymem)
	{
	_delay_ms(35);
	io=key_find();
	//BEEP(1);
	};
	_delay_ms(dkeyl); //!500
	BEEP(1);
	goto pm_out;
	}
	
}
	if (io==1) {SFM(); io=1; goto agn;} /// Выбор файла
	if (io==5) {MF(); io=5; goto agn;} /// меню форматирование
	if (io==2) {RFILE();io=2; goto agn;} /// Просмотр файла
	if (io==3) {FCLR(); io=3; goto agn;} /// Очистить файл --- пререместить указатель курсора в файле ДАННЫЕ НЕ СТИРАЮТСЯ !!! 
	if (io==4) {CLRMEMALL(); io=4; goto agn;} /// Очистить всю память.
	
pm_out:;
cls();
rkey();
}
/////////////////////////////////////////////////////////////////////////////////
*/
/*

unsigned char filename(void)  /// прочитать номер файла
{
unsigned char i=0;
i = readWEE(fname);
return i; 
}

void wfilename(unsigned char i)  ///Записать ном файла
{
writeWEE(i,fname);
}



unsigned int rfd(unsigned char mp,unsigned char tf) //// Вычислить число свободных ячеек в указанном файле
{
unsigned int posf=0, maxlen=0, point=0;

posf = pointstart + mp; /// найти ячейку еепром указатель курсора файла.

maxlen = v1m30/tf; /// Найти максимальную длинну файла

point = readWEE(posf); /// читать ячейку позиции файла.

return (maxlen-point);  /// Вычесть из макс длинны - позицию файла
}




unsigned int rfd_use(unsigned char mp,unsigned char tf) //// Вычислить число занятых ячеек в файле
{
unsigned int posf=0, maxlen=0, point=0;

posf = pointstart + mp; /// найти ячейку еепром указатель курсора файла.

maxlen = v1m30/tf; /// Найти максимальную длинну файла

point = readWEE(posf); /// читать ячейку позиции файла.

return point;  /// Вычесть из макс длинны - позицию файла
}

*/
////////////////////////////////////

/*
unsigned char filetype(void)  /// прочитать ТИП файлов
{
unsigned char i=0;
i = readWEE(tfile);
return i; 
}


void wfiletype(unsigned char i)  ///Записать Тип файлов 
{
writeWEE(i,tfile);
}
*/

///////////////////////////////////// Записать серийный номер прибора ////////////////////////////////////
void WR_SNUM(unsigned char a,unsigned char b,unsigned char c,unsigned char d)
{
//_delay_ms(15);
eeprom_write_byte (ZNUM0,d);
eeprom_write_byte (ZNUM1,c);
eeprom_write_byte (ZNUM2,b);
eeprom_write_byte (ZNUM3,a);
//_delay_ms(25);
}
///////////////////////////////////////////////// ФОРМАТИРОВАНИЕ //////////////////////////////////////////

void MF(void) /// Меню форматирования
{

cls();
unsigned char io=1,i=0,ib=0;

BEEP(2);
i=show_FORMmenu(io);
while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);

while (!(key_find()==keyenter)) /// ждать кнопки ввод
{
 
	
	if (key_find()==keydown)   /// двигать курсор вверх вниз /// с циклической прокруткой.
	{   _delay_ms (620);
		key_find();
		io ++;
		if (io==8) { io = 1;}
		BEEP(4);
		i=show_FORMmenu(io);
	}
	
	if (key_find()==keyup)
	{   _delay_ms (620);
		key_find();	
		io --;
		if (io==0) { io =7;}
		BEEP(3);
		i=show_FORMmenu(io);	
	}
	
	
	
	if (key_find()==keymem) /// Выход по кнопке по которой вошли --- ждет когда ее отпустят тогда выход.
	{
	ib=keymem;
	
	while (ib==keymem)
	{
	_delay_ms(35);
	ib=key_find();
	//BEEP(1);
	};
	_delay_ms(500);
	//BEEP(1);
	goto exfm;
	}
	
	

	
}


FORMAT(i);  //// Само форматирование

exfm:; /// Отмена форматирования
}




void FORMAT(unsigned char tf) 
{


draw_wdataerase(); //// Табличка Данные будут удалены продолжить ДА кл 0  НЕТ КЛ enter


while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);

while (!(key_find()==keyzero)) /// ждать кнопки 0  для начала стирания
{

	if (key_find()==keyenter)   /// если ввод то отмена стирания и выход
	{ 

	//BEEP(1);
	goto exf;
	
	}

}


BEEP(2);
cls();
show_wpos(34,6,14); //// ЖДИТЕ 
clraEE(); /// очистка памяти

wfiletype(tf); /// Тип файлов 
wfilename(0);//// Указатель файла на 0 файл
BEEP(2);

exf:;
cls();
}
/////////////////////////////////////////// ВЫБОР ФАЙЛА /////////////////////////////////////////////////

void SFM(void) /// меню выбора файла
{

signed char io=0;

unsigned char nfile=0,tf=0;


nfile=filename(); /// Прочесть номер файла
tf=filetype(); /// Прочесть тип файла
cls();
BEEP(2);

io = nfile;
//ic = nfile;
show_SELmenu(io);

while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);

while (!(key_find()==keyenter)) /// ждать кнопки ввод
{
 
	
	while (key_find()==keyup)   /// двигать курсор вверх вниз
	{   _delay_ms (620);
		key_find();
		io ++;
		if (io>=(tf)) { io = tf-1;}
		BEEP(4);
		show_SELmenu(io);
		
		rkey();
	}
	
	while (key_find()==keydown)
	{   _delay_ms (620);
		key_find();	
		io --;
		if (io<=0) { io =0;}
		BEEP(3);
		show_SELmenu(io);

		rkey();
	}
	
	
	if (key_find()==keymem) /// Выход по кнопке по которой вошли --- ждет когда ее отпустят тогда выход.
	{
	io=keymem;
	
	while (io==keymem)
	{
	_delay_ms(35);
	io=key_find();
	//BEEP(1);
	};
	
	_delay_ms(500);
	
	wfilename(nfile); /// Запись номера файла  который был изночально
	BEEP(1);
	goto sf_out;
	}
	
}
sf_out:;
rkey();
}


/*
/////////////////////////////////////////// ПРОСМОТР ФАЙЛА //////////////////////////////////////////////
void RFILE(void)
{
cls();
unsigned char nfile=0,tf=0, STSM=0;
unsigned long maxlen=0,free=0,filestart=0,fileend=0,io=0,posf=0,ax=0;
signed long point=0;

nfile=filename(); /// Прочесть номер файла
tf=filetype(); /// Прочесть тип файла

posf = pointstart + nfile; /// найти ячейку еепром указатель курсора файла.

maxlen = (v1m30/tf); /// Найти максимальную длинну файла

point = readWEE(posf); /// читать ячейку позиции файла.

point = point-1;

if (point <= 0) {point = 0;}

free= maxlen-point; /// Свободное место

filestart= (nfile * maxlen) + memstart; ///Найти начало файла (в ячейках) абсолютных  для обращения к памяти
//filestart = filestart+1;///
fileend = filestart+point;  /// Найти конец файла (в ячейках)


//// -------------------------
io=filestart; /// В начальную позицию файла для просмотра
ax=readWEE(io);



STSM = ax>>16;
ax = ax & 0x0000FFFF;

draw_memoline(13,7,48); ///нижняя строчка Выход кл enter
draw_dline();// линия 
show_mmdiv();// номер ячейки

vf_disp(ax,nfile,(io-filestart+1),tf);
draw_CLASSMODE(STSM);


BEEP(2);

Eexf5:;

while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);

while (!(key_find()==keyenter)) /// ждать кнопки ввод
{
 
	
	while (key_find()==keyup)   /// Листать файл вверх вниз  между файлстарт и файленд
	{   _delay_ms (readfilest);
		key_find();
		io ++;
		if (io>=(fileend+1)) { io = fileend;} 
		
		//if ((io-filestart)==0xFFFF) {io=fileend+1;}
		
		//if (io-filestart)
		BEEP(4);
		

		
		ax=readWEE(io);
		STSM = ax>>16;
		ax = ax & 0x0000FFFF;
		vf_disp(ax,nfile,(io-filestart+1),tf);	 /// отобразить ячейку на экране
		draw_CLASSMODE(STSM);
		
		rkey();
	}
	
	while (key_find()==keydown)
	{   _delay_ms (readfilest);
		key_find();	
		io --;
		if (io<=(filestart-1)) { io =filestart;}
		
		BEEP(3);
		

		
		ax=readWEE(io);
		STSM = ax>>16;
		ax = ax & 0x0000FFFF;
		vf_disp(ax,nfile,(io-filestart+1),tf);	 /// отобразить ячейку на экране
		draw_CLASSMODE(STSM);
		
		rkey();
	}
	
	
	
	
	
	while (key_find()==keynastr) ///переместится в начало файла
	{
		_delay_ms (readfilest);
		key_find();	
		io = filestart;
		//if (io<=(filestart-1)) { io =filestart;}
		BEEP(3);
		

		
		ax=readWEE(io);
		STSM = ax>>16;
		ax = ax & 0x0000FFFF;
		vf_disp(ax,nfile,(io-filestart+1),tf);	 /// отобразить ячейку на экране
		draw_CLASSMODE(STSM);
		
		rkey();
	
	}
	
		while (key_find()==keyrezim) ///переместится в Конец файла
	{
		_delay_ms (readfilest);
		key_find();	
		io = fileend;
		
		//if ((io-filestart)==0xFFFF) {io=fileend+1;}
		//if (io<=(filestart-1)) { io =filestart;}
		BEEP(3);
		

		
		ax=readWEE(io);
		STSM = ax>>16;
		ax = ax & 0x0000FFFF;
		vf_disp(ax,nfile,(io-filestart+1),tf);	 /// отобразить ячейку на экране
		draw_CLASSMODE(STSM);
		
		rkey();
	
	}
	
	
		while (key_find()==keymem) ///Стереть последнюю запись    ////////   стирает с конца по порядку ячейки
	{
		_delay_ms (readfilestE);
		key_find();	
		
			rkey();
			_delay_ms(10);
			
	if (key_find()==keymem) /// Да нажата кнопка память  можно стирать
				
		{		
		
			_delay_ms(10);
		
								draw_wdataerase(); //// Табличка Данные будут удалены продолжить ДА кл 0  НЕТ КЛ enter
			_delay_ms(10);

								while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
									{
									}
									_delay_ms (620);
									key_find();
									_delay_ms (32);

								while (!(key_find()==keyzero)) /// ждать кнопки 0  для начала стирания
								{

									if (key_find()==keyenter)   /// если ввод то отмена стирания и выход
									{ 

									BEEP(1);
							
													
													ax=readWEE(io);
													STSM = ax>>16;
													ax = ax & 0x0000FFFF;
													cls();
													vf_disp(ax,nfile,(io-filestart+1),tf);	 /// отобразить ячейку на экране
													draw_memoline(13,7,48); ///нижняя строчка Выход кл enter
													draw_dline();// линия
													draw_CLASSMODE(STSM);
													
													rkey();
									
									goto Eexf5;
									
									}

								}
		
		
		
		if (!(point<=0)) //// проверить , можно ли стирать ячейку. не последняя ли она в файле.
		{
		writeWEE(point,posf); /// Записать в указатель файла увеличенное на еденицу 
		}
		
		
			if (point <= 0) 
				
				{
				writeWEE(0x00,posf); /// Записать в указатель файла 0
				writeWEE(0x00,filestart); /// Записать в ячейку 0
				}
		
		point = readWEE(posf); /// читать ячейку позиции файла.
		
		point = point-1;
		if (point < 0) {point = 0;}
		
		free= maxlen-point; /// Свободное место

		filestart= (nfile * maxlen) + memstart; ///Найти начало файла (в ячейках) абсолютных  для обращения к памяти
		//filestart = filestart+1;///
		fileend = filestart+point;
			/// Найти конец файла (в ячейках)
		
		
		io = fileend;
		//if (io<=(filestart-1)) { io =filestart;}
		//BEEP(3);
		

		
		ax=readWEE(io);
		STSM = ax>>16;
		ax = ax & 0x0000FFFF;
		cls();
		vf_disp(ax,nfile,(io-filestart+1),tf);	 /// отобразить ячейку на экране
		draw_memoline(13,7,48); ///нижняя строчка Выход кл enter
		draw_dline();// линия
		show_mmdiv();// номер ячейки
		draw_CLASSMODE(STSM); 
		
		BEEP(1); ////// 
						rkey();
	/*					_delay_ms(50);
		
						while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
						{
						}
						_delay_ms (820);
						key_find();
						_delay_ms (32);*/
					
		
/*
		
//!  cls();
		}
		
		rkey();
	
	}

}
///-------------------------
}

/////////////////////////////////////////////// ОТОБРАЗИТЬ ЯЧЕЙКУ //////////////////////////////////////
*/

/*
void vf_disp(unsigned int val, unsigned char mf,unsigned int mp,unsigned char tf)  /// отобразить на дисплее ячейку файла. mp в этом режиме указатель текущей ячейки
{


//! cls(); - из-за этого мигают большие цифры

//!draw_memoline(13,7,48); ///нижняя строчка Выход кл ент
//!show_mmdiv();	
//!draw_dline();


put_int_to_num_buffer(val,0); //// Вывести толщину на дисплей  
show_num_buffer();
draw_smem(mf,mp,tf);  //// Отразить состояние памяти прибора

}

/////////////////////////////////////////// ЗАПИСАТЬ В ФАЙЛ ЗАМЕР ///////////////////////////////////////

unsigned char WR_FILE (unsigned long val)
{

if (val==0x00) {BEEP(4); return 4;}//// ноль сохранять нельзя

unsigned char nfile=0,tf=0;
unsigned long maxlen=0,free=0,filestart=0,fileend=0,posf=0,point=0;

nfile=filename(); /// Прочесть номер файла
tf=filetype(); /// Прочесть тип файла

posf = pointstart + nfile; /// найти ячейку еепром указатель курсора файла.

maxlen = v1m30/tf; /// Найти максимальную длинну файла

point = readWEE(posf); /// читать ячейку позиции файла.

free= maxlen-point; /// Свободное место

	if (free==0) {return 5;} /// Выход кончилась свободная память 
	
filestart= (nfile * maxlen) + memstart; ///Найти начало файла (в ячейках) абсолютных  для обращения к памяти

//filestart = filestart-1;

fileend = filestart+point;  /// Найти конец файла (в ячейках)


free= READ_CLASSM(); /// Записать в ячейку толщину, и состояние при котором она измерена

free = (free << 16) + val;

writeWEE(free,(fileend)); /// Записать в ячейку измеренное число
_delay_ms(10);
writeWEE((point+1),posf); /// Записать в указатель файла увеличенное на еденицу 


BEEP(1);
return 1; /// запись успешна - ОК

}
////////////////////////////////////// Очистка файла //// //////////////////////////////////////////
void FCLR(void)  /// Записывает в указатель курсора файла позицию 0  ДАННЫЕ НЕ СТИРАЮТСЯ !!!!!
{
unsigned char nfile=0;
unsigned int posf=0, filestart=0, tf=0, maxlen=0;

cls();
BEEP(2);


draw_wdataerase(); //// Табличка Данные будут удалены продолжить ДА кл 0  НЕТ КЛ enter

while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);

while (!(key_find()==keyzero)) /// ждать кнопки 0  для начала стирания
{

	if (key_find()==keyenter)   /// если enter то отмена стирания и выход
	{ 

	//BEEP(1);
	goto exf;
	
	}

}

nfile=filename(); /// Прочесть номер файла
tf=filetype(); /// Прочесть тип файла

posf = pointstart + nfile; /// найти ячейку еепром указатель курсора файла.

maxlen = v1m30/tf; /// Найти максимальную длинну файла
	
filestart= (nfile * maxlen) + memstart; ///Найти начало файла (в ячейках) абсолютных  для обращения к памяти

///point = readWEE(posf); /// читать ячейку позиции файла.

//writeWEE(0,posf); /// Записать в указатель файла 0 - начальная позиция
writeWEE(0x00,posf); /// Записать в указатель файла 0
writeWEE(0x00,filestart); /// Записать в ячейку 0  - 0

exf:; /// Выход
cls();

}
///////////////////////////////////////////ОЧИСТКА ВСЕЙ ПАМЯТИ /////////////////////////////////////////////

void CLRMEMALL(void) /// Очистить память  -- форматирование по умолчанию выбранной файловой организации
{
unsigned char i=0;

cls();
BEEP(2);


draw_wdataerase(); //// Табличка Данные будут удалены продолжить ДА кл 0  НЕТ КЛ enter

while (!(key_find()==0)) /// ждать пока отпустят все кнопки 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);

while (!(key_find()==keyzero)) /// ждать кнопки 0  для начала стирания
{

	if (key_find()==keyenter)   /// если enter то отмена стирания и выход
	{ 

	//BEEP(1);
	goto exf;
	
	}

}

i=filetype();

FORMAT(i); /// Заново стереть и отформатировать память 

exf:; /// Выход без форматирования

cls();


}
*/


//////////////////////////////////// Работа с ЕЕПРОМ i2c /////////////////////////////////////////////////

unsigned char readEE(unsigned int ADR) /// прочитать байт из памяти 750uS
{
unsigned char br=0;

	i2c_start();		// старт
	i2c_tx(eeWR);		// Физадрес + режим записи
	i2c_tx(ADR>>8);		// Старщий байт адреса
	i2c_tx(ADR);		// младш байт адреса
	i2c_stop();			// стоп

	//_delay_us(3); 

	i2c_start();		// Старт
	i2c_tx(eeRD);		// Физадрес + режим чтения
	br=i2c_rx(0);		// Прочитать байт
//	br=i2c_rx(1);		// Прочитать байт
	i2c_stop();			// Стоп
	_delay_us(1); 
	
	return br;
}
// 
// unsigned long readWEE(unsigned int ADR) /// прочитать слово //// Адресация в СЛОВАХ  byte/2 = word adr 3
// {
// unsigned long wr=0;
// unsigned char ba=0, bb=0, bc=0;
// 
// 	ADR = ADR*3;
// 
// 	i2c_start();		// старт
// 	i2c_tx(eeWR);		// передача адреса  1 физадрес чт зп
// 	i2c_tx(ADR>>8);		// Старщий байт адреса
// 	i2c_tx(ADR);		// младш байт адреса
// 	i2c_stop();			// стоп
// 
// 	//_delay_us(3); //
// 
// 	i2c_start();		// Старт
// 	i2c_tx(eeRD);		// Физадрес режим чтения
// 	ba=i2c_rx(1);		// Прочитать байт
// 	bb=i2c_rx(1);
// 	bc=i2c_rx(0);
// 	i2c_stop();			// Стоп
// 
// 	wr = ba; 
// 	wr= (wr<<8)+bb;
// 	wr= (wr<<8)+bc;
// 
// return wr;
// };

unsigned long readWEE(unsigned int ADR) /// прочитать слово //// Адресация в СЛОВАХ  byte/2 = word adr 3
{
	unsigned long wr=0;
	unsigned char ba=0, bb=0, bc=0;

	ADR = ADR*3;

	i2c_start(); // старт
	i2c_tx(eeWR); // передача адреса  1 физадрес чт зп
	i2c_tx(ADR>>8); /// Старщий байт адреса
	i2c_tx(ADR);  /// младш байт адреса
	i2c_stop();  /// стоп

	_delay_us(3); //

	i2c_start(); /// Старт
	i2c_tx(eeRD); /// Физадрес режим чтения
	ba=i2c_rx(1); /// Прочитать байт
	bb=i2c_rx(1);
	bc=i2c_rx(0);
	i2c_stop(); // Стоп

	wr = ba;
	wr= (wr<<8)+bb;

	wr= (wr<<8)+bc;


	return wr;
}

void writeEE(unsigned int ADR, unsigned int val) //// Запись байта
{
i2c_start(); 
i2c_tx(eeWR);		// адрес микросхемы + признак записи

i2c_tx(ADR>>8);		// адрес в памяти для записи
i2c_tx(ADR);

//_delay_ms(5);		// Задержка для записи еепором

//i2c_tx(val>>8);	// запись байта
i2c_tx(val);		// запись байта
i2c_stop();
//_delay_ms(1);		// Задержка для записи еепором

};
//! Send a byte sequence on the I2C bus
void i2c_EXT_Send(unsigned int ADR, unsigned char length, unsigned char *data)
{
i2c_start();
i2c_tx(eeWR);		// адрес микросхемы + признак записи

i2c_tx(ADR>>8);		// адрес в памяти для записи
i2c_tx(ADR);

	// send the data
	while (length--)
	i2c_tx(*data++);

i2c_stop();

//	I2C_SDL_LO;					// clear data line and
//	I2C_STOP;					// send STOP transition
}

void writeWEE(unsigned int ADR,unsigned long val)///// Записать слово /// Адресация в СЛОВАХ  byte/2 = word adr  3
{

	ADR = ADR*3;
	i2c_start();
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);

	i2c_tx(val>>16); /// запись байта

	i2c_stop();
	_delay_ms(9);/// Задержка для записи еепором

	////////////////////////////

	ADR = ADR+1;

	i2c_start();
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);

	i2c_tx(val>>8); /// запись байта

	i2c_stop();
	_delay_ms(9);/// Задержка для записи еепором



	ADR = ADR+1;

	i2c_start();
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);

	i2c_tx(val); /// запись байта

	i2c_stop();
	_delay_ms(9);/// Задержка для записи еепором
}

void writeWEE_old(unsigned int ADR, unsigned long val)///// Записать слово /// Адресация в СЛОВАХ  byte/2 = word adr  3
{

ADR = ADR*3;

i2c_start(); 
i2c_tx(eeWR);

USART_SEND_Byte(eeWR);

i2c_tx(ADR>>8);

USART_SEND_Byte(ADR>>8);

i2c_tx(ADR);

USART_SEND_Byte(ADR);
USART_SEND_Byte('=');

i2c_tx(val>>16); /// запись байта 

USART_SEND_Byte(val>>16);

i2c_tx(val>>8); /// запись байта

USART_SEND_Byte(val>>8);

i2c_tx(val); /// запись байта

USART_SEND_Byte(val);
USART_SEND_Byte('|');

i2c_stop();
_delay_ms(9);/// Задержка для записи еепором
}

/*
void writeWEE(unsigned char * str_save, unsigned int ADR, unsigned char delete,unsigned char dtps,unsigned char mdch)///// Записать слово /// Адресация в СЛОВАХ  byte/2 = word adr  3
{
	unsigned char MD=0;

	ADR = ADR*entry_size;

	i2c_start();
	i2c_tx(eeWR);				// адрес микросхемы + признак записи
	i2c_tx(ADR>>8);				// адрес в памяти для записи
	i2c_tx(ADR);

	i2c_tx(str_save[0]); /// запись байта 

	i2c_stop();
	//_delay_ms(9);/// Задержка для записи еепором

	////////////////////////////

	ADR = ADR+1;

	i2c_start(); 
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);

	i2c_tx(str_save[1]); /// запись байта

	i2c_stop();
	//_delay_ms(9);/// Задержка для записи еепором

	////////////////////////////

	ADR = ADR+1;

	i2c_start(); 
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);

	i2c_tx(str_save[2]); /// запись байта

	i2c_stop();
	//_delay_ms(9);/// Задержка для записи еепором
	////////////////////////////

	ADR = ADR+1;

	i2c_start();
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);

	i2c_tx(str_save[3]); /// запись байта

	i2c_stop();	

	////////////////////////////

	ADR = ADR+1;

	i2c_start();
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);
	
	MD=mdch;										// младшие разряды = номер режима
	if(dtps>>1) SetBit(MD,6); else ResetBit(MD,6);		// положение десятичной точки 0-десятые; 1-сотые;
	if(delete) SetBit(MD,7); else ResetBit(MD,7);	// запись удалена
	
	i2c_tx(MD); /// запись байта

	i2c_stop();
}
*/



void clraEE(void) /// Очистить всю память
{

unsigned long ADR=0;
unsigned char i=0;


while (!(ADR>=0xFFFF))
	{
		i2c_start(); 
		i2c_tx(eeWR);
	
		i2c_tx(ADR>>8);
		i2c_tx(ADR);
		
	
				for(i = 0; i < 128; i++)
				{
				
				i2c_tx(0); /// запись байта 0
				ADR++;
				
				}

		i2c_stop();
	
		_delay_ms(10);/// Задержка для записи еепором
	
	}
	
_delay_ms(10);

}

unsigned char i2c_error_soft;                         //ошибки  программной шины

//Инициализация программной шины I2C
void i2c_init(void)
{
  I2C_DDR&=~(1<<SDA_LN);                              //изначально линии SDA
  I2C_DDR&=~(1<<SCL_LN); 
														//и SCL в высокоимпедансном состоянии
  I2C_PORT|= _BV(1<<SDA_LN);                             //и на них поддерживается за счет внешних резисторов
  I2C_PORT|= _BV(1<<SCL_LN);                             //высокий уровень
  i2c_error_soft=0;                                   //изначально ошибок нет :-)
}

//Формирует условие "СТАРТ"
void i2c_start(void)
{
  if(i2c_error_soft)
  {
	//BEEP(3);
	return;
  }
  scl_set(1);
  sda_set(0);
  scl_set(0);
}

//Формирует условие "СТОП"
void i2c_stop(void)
{
  sda_set(0);
  scl_set(1);
  sda_set(1);
  if(i2c_error_soft)
  {
	//BEEP(3);
    i2c_init();
  }
}

//Посылка байта
void i2c_tx(unsigned char byte)
{
  if(i2c_error_soft)
  {
	  //BEEP(3);
	  return;
  }
  for(unsigned char i=0;i<8;i++)
    {
      if(byte&0x80)
        sda_set(1);
      else
        sda_set(0);
      scl_set(1);
      scl_set(0);
      byte<<=1;
    }
  sda_io(IN_LN);
  scl_set(1);
  i2c_error_soft=in_sda(); //!!!!!!!!!!!!!!!!!!!!!!!!!
  scl_set(0);
  sda_io(OUT_LN);
}


//Прием байта, если last_byte=0, то принимаем последний байт и подтверждение от мастера не нужно
unsigned char i2c_rx(unsigned char last_byte)
{
  unsigned char data=0;
  unsigned char mask=0x80;
  if(i2c_error_soft)
  {
	  //BEEP(3);
	  return 0;
  }
  sda_io(IN_LN);
  for(unsigned char i=0;i<8;i++)
    {
      scl_set(1);
      if(in_sda())
        data=data+mask;
      mask>>=1;
      scl_set(0);
    }
  sda_io(OUT_LN);
  if(last_byte)
    sda_set(0);
  else
    sda_set(1);
  scl_set(1);
  scl_set(0);
  return data;
}

//Возвращает уровень линии SDA
unsigned char in_sda(void)
{
  if(I2C_PIN&(1<<SDA_LN))
    return 1;
  else
    return 0;
}

//Устанавливает линию SDA на вход или выход
void sda_io(unsigned char io_c)
{
  if(io_c==IN_LN)
    I2C_DDR&=~(1<<SDA_LN);
  else
    I2C_DDR|=(1<<SDA_LN);
	
  _delay_us(idel);
}

//Устанавливает уровень на линии SCL
void scl_set(unsigned char set_c)
{
  if(set_c)
    {
      I2C_DDR&=~(1<<SCL_LN);
      I2C_PORT&=~(1<<SCL_LN);
    }
  else
    {
      I2C_DDR|=(1<<SCL_LN);
      I2C_PORT&=~(1<<SCL_LN);
    }
	
  _delay_us(idel);
}

//Устанавливает уровень на линии SDA
void sda_set(unsigned char set_c)
{
  if(set_c)
    {
      I2C_DDR&=~(1<<SDA_LN);
      I2C_PORT&=~(1<<SDA_LN);
    }
  else
    {
      I2C_DDR|=(1<<SDA_LN);
      I2C_PORT&=~(1<<SDA_LN);
    }

  _delay_us(idel);
}

///////////////////////////////////////////////// Служебные программы обмена данными ////////////////////////

void RWN(void) //// Запись номера прибора через RS232
{
unsigned char a[5],x=0;
//cls();
//show_wpos(34,6,14); //// ЖДИТЕ 
for (x = 0; x < 5; x++) /// Получить 5 байт 
	{
		while (!(UCSR0A & (1<<RXC0)));
		
		a[x]=(UDR0-0x30);
	}
	
	if ((a[0]==0xF5) && (a[1]<=9) && (a[2]<=9) && (a[3]<=9) && (a[4]<=9)) /// Если признаки верные
	{
	WR_SNUM(a[1],a[2],a[3],a[4]);  //// Записать серийный номер
	BEEP(4);
	SEND_ST(W_OK); /// Выполнено
	SNUMWR(0x00);
	
	CLRTR(); /// Обнуление нар
	wrnar(0x00); //// ОБНУЛЕНИЕ НАРАБОТКИ !!!!!!!!!!!!!!!!!!!1
	
	goto exf;
	}
	
	
	if ((a[1]>9) && (a[2]>9) && (a[3]>9) && (a[4]>9) ) { SEND_ST(M03err);}/// -- Неправильный формат данных (вместо цифр ascii другие символы)
	
	



	
exf:;
//cls();
}
/*
///////////////////////////  Передача структуры памяти и числа занятых ячеек в файлах ///////////////////////
void SENDUFORG(void)
{
unsigned int tf=0,mp=0,i=0;


//tf=filetype();
tf=1;
LBS(tf);


				if (SEND_NUM[2]<10)  //// Передача числа файлов
				{
				USART_SEND_Byte(SEND_NUM[2]+0x30); 
				}
				
				if (SEND_NUM[1]<10)
				{
				USART_SEND_Byte(SEND_NUM[1]+0x30);
				}
				USART_SEND_Byte(SEND_NUM[0]+0x30);
				SCRCL();


	
	for (i = 0; i <= (tf-1); i++)    //// прокрутить все файлы которые есть /// увеличить счетчик файлов
	{
	
	//mp=rfd_use(i,tf); /// узнать число занятых в файле ячеек
	mp=20000; 
	LBS(mp); // передать в буффер передачи
	
	
	
					//// Передача строчки -  файл -- ячеек занято
				
				if (SEND_NUM[4]<10)
				{
				USART_SEND_Byte(SEND_NUM[4]+0x30);
				}
				
				if (SEND_NUM[3]<10)
				{
				USART_SEND_Byte(SEND_NUM[3]+0x30);
				}
				
				if (SEND_NUM[2]<10)
				{
				USART_SEND_Byte(SEND_NUM[2]+0x30); 
				}
				
				if (SEND_NUM[1]<10)
				{
				USART_SEND_Byte(SEND_NUM[1]+0x30);
				}
				USART_SEND_Byte(SEND_NUM[0]+0x30);
				SCRCL(); /// Перевод каретки
	
	
	}

SEND_ST(END_S);  ///Конец передачи 


}*/
/*
//////////////////////// Передача файла через UART /////////////////////////////////////////////
void SENDUFILE(void)
{
unsigned char a[3],x=0,fnum=0, tf=0, STSM=0;
unsigned int  maxlen=0, filestart=0, fileend=0, io=0, sendcont=0, sr=0, blockq=0; /// blq=0;
unsigned long val=0, is=0;
//cls();
//show_wpos(34,6,14); //// ЖДИТЕ 
tf=filetype();

 




for (x = 0; x < 3; x++) /// Получить 5 байт 
	{
		while (!(UCSR0A & (1<<RXC0)));
		
		a[x]=(UDR0-0x30);
	}
	
	fnum =(a[1]*10)+a[2]; /// номер файла
	
	if ((a[0]==0xF5) && (a[1]<=9) && (a[2]<=9) && (fnum<=tf)) /// Если признак верный то продолжаем 
	{

			maxlen = (v1m30/tf); /// Найти максимальную длинну файла

	//blockq = maxlen/blockSIZE; // число блоков в файле для передачи

			filestart= (fnum * maxlen) + memstart; ///Найти начало файла (в ячейках) абсолютных  для обращения к памяти
	
			fileend = filestart+maxlen;  /// Найти конец файла 

			io=filestart; /// В начальную позицию файла для просмотра
			
			sendcont=0;
			
			for (io = filestart; io < fileend; io++)  //// Передача файла
			{
				
				TIMSK3=0x00;
				TCNT3=0;
				
				
				
				
				
				val=readWEE(io); /// прочитать ячейку из памяти
				
				
				
				
				

				STSM = val>>16;  //// Вычислить состояние при которм было измерение 
				val = val & 0x0000FFFF;

				if (STSM==0) {STSM = CMCLR;}
				
				USART_SEND_Byte(STSM);
				
			
			
				LBS(val); // передать в буффер передачи
			
				if (SEND_NUM[4]<10)
				{
				USART_SEND_Byte(SEND_NUM[4]+0x30);
				}
				
				if (SEND_NUM[3]<10)
				{
				USART_SEND_Byte(SEND_NUM[3]+0x30);
				}
				
				if (SEND_NUM[2]<10)
				{
				USART_SEND_Byte(SEND_NUM[2]+0x30); 
				}
				
				if (SEND_NUM[1]<10)
				{
				USART_SEND_Byte(SEND_NUM[1]+0x30);
				}
				USART_SEND_Byte(SEND_NUM[0]+0x30);
				SCRCL(); /// Перевод каретки
				
				sendcont++; /// Увеличить счетчик
				if (sendcont==blockSIZE)
				
					{	
									//is=TOTRS(0);
									
						
									LBS(blockq+10); /// счетчик блоков  10.....59 фактичесий 0-49
									
									USART_SEND_Byte('B');
									
									USART_SEND_Byte(SEND_NUM[1]+0x30);
							
									USART_SEND_Byte(SEND_NUM[0]+0x30);
									
									blockq++;
					
					
							SCRCL(); /// Перевод каретки
						
				sei();											////Включить вложенное прерывание !!!!!!!!!!!
						is=TOTRS(2); // Включить контроль тайм аут
						
						
						while (!(UCSR0A & (1<<RXC0)))
						
							{
							
										if (TOTRS(1)>0x01)
											{
												is=0;
												SEND_ST(BTOT); /// таймаут
												is=TOTRS(0);
												goto exf;
											}
							
							}
				cli();                                        ////Выключить вложенное прерывание !!!!!!!!!!!
						
						sr=UDR0;
						is=TOTRS(0);
						
							if (sr=='z') /// Блок принят  продолжаем передачу 
								{
								sendcont=0; 
								
								}
								else
								{
								SEND_ST(FF0err); //// нет управляющего байта ОК  сбой передачи отмена
								blockq=0;
								goto exf;
								}
					}
				
				
			}
			SEND_ST(END_S);  /// Передача Конец
	
	}
	else
	{
		if ((a[1]>9) && (a[2]>9)) { SEND_ST(M03err); goto exf; }/// -- Неправильный формат данных (вместо цифр ascii другие символы)
		
		if (tf < fnum) {SEND_ST(M01err);} //// -- Нет такого файла
	
	}


exf:;

//cls();
is=TOTRS(0);

}*/
//////////////////////// Передача состояния в UART /////  M00, M01, M02, M03, END, Ser_Num /////////////////
void SEND_ST(unsigned char num)
{
unsigned char a[4],i=0;


	switch (num)
		{
		case 0: a[2]='M'; a[1]='0'; a[0]='0';i=0; break;
		case 1:	a[2]='M'; a[1]='0'; a[0]='1';i=0; break;
		case 2:	a[2]='M'; a[1]='0'; a[0]='2';i=0; break;
		case 3:	a[2]='M'; a[1]='0'; a[0]='3';i=0; break;
		case 4:	a[2]='E'; a[1]='N'; a[0]='D';i=0; break;
		
		case 5:	a[3]=(eeprom_read_byte(ZNUM3)+0x30); a[2]=(eeprom_read_byte(ZNUM2)+0x30); a[1]=(eeprom_read_byte(ZNUM1)+0x30); a[0]=(eeprom_read_byte(ZNUM0)+0x30);i=1; break;
		case 6: a[2]='W'; a[1]='O'; a[0]='K';i=0; break;
		case 7: a[2]='F'; a[1]='F'; a[0]='0';i=0; break;
		case 8: a[2]='B'; a[1]='V'; a[0]='L';i=0; break;
		case 9: a[2]='F'; a[1]='F'; a[0]='T';i=0; break;
		}


	if (i>=1)								//// Передача 
	{
	USART_SEND_Byte(a[3]);
	}
		USART_SEND_Byte(a[2]);
		USART_SEND_Byte(a[1]);
		USART_SEND_Byte(a[0]);

	SCRCL(); /// Перевод каретки
}
///////////////////////////////////////////////// Передать толщину текущюю //////////

void SendUT(void)
{
	//LBS(Read_Disp());
	LBS(main_value);
 // передать в буффер передачи
			
				if (SEND_NUM[4]<10)
				{
				USART_SEND_Byte(SEND_NUM[4]+0x30);
				}
				
				if (SEND_NUM[3]<10)
				{
				USART_SEND_Byte(SEND_NUM[3]+0x30);
				}
				
				if (SEND_NUM[2]<10)
				{
				USART_SEND_Byte(SEND_NUM[2]+0x30); 
				}
				
				if (SEND_NUM[1]<10)
				{
				USART_SEND_Byte(SEND_NUM[1]+0x30);
				}
				USART_SEND_Byte(SEND_NUM[0]+0x30);
				SCRCL(); /// Перевод каретки
}

/////////////////////////////////////  Передать напряжение ///////////////////////////////////
void SEND_VOLT(unsigned int val)
{

				LBS(val); // передать в буффер передачи
				
				if (SEND_NUM[2]<10)
				{
				USART_SEND_Byte(SEND_NUM[2]+0x30); 
				}
				
				if (SEND_NUM[1]<10)
				{
				USART_SEND_Byte(SEND_NUM[1]+0x30);
				}
				USART_SEND_Byte(SEND_NUM[0]+0x30);
				SCRCL(); /// Перевод каретки
}

//////////////////////// Чтение  Запись и Передача НАРАБОТКИ ///////////////////////////////////////////////
 
void wrnar(unsigned long nar)
{
eeprom_write_dword (TNAR,nar); ///Запись наработки в память
}

unsigned long TNARAB(void)
{
unsigned long i=0;
i= eeprom_read_dword(TNAR); //// Считать наработку
return i;
}

void Send_NARU(void) /////  Передача текущей наработки часы:минуты в ком порт
{
unsigned long  i=0;
unsigned long tmp_save=0;

//i=timerab(); /// получить текущюю наработку
	tmp_save=eeprom_read_word(TNAR); //// Считать наработку
	num2str_3_zeros(tmp_save,SEND_NUMX);

//i=timerab();
//LBSX(i); // передать в буффер передачи
			
		
			
				if (SEND_NUMX[7]<10)
				{
				USART_SEND_Byte(SEND_NUMX[7]+0x30);
				}
			
				if (SEND_NUMX[6]<10)
				{
				USART_SEND_Byte(SEND_NUMX[6]+0x30);
				}
				if (SEND_NUMX[5]<10)
				{
				USART_SEND_Byte(SEND_NUMX[5]+0x30);
				}
			
				if (SEND_NUMX[4]<10)
				{
				USART_SEND_Byte(SEND_NUMX[4]+0x30);
				}
				
				if (SEND_NUMX[3]<10)
				{
				USART_SEND_Byte(SEND_NUMX[3]+0x30);
				}
				
				if (SEND_NUMX[2]<10)
				{
				USART_SEND_Byte(SEND_NUMX[2]+0x30); 
				}
				
				if (SEND_NUMX[1]<10)
				{
				USART_SEND_Byte(SEND_NUMX[1]+0x30);
				}
				USART_SEND_Byte(SEND_NUMX[0]+0x30);
				SCRCL(); /// Перевод каретки
};



//////////////////////////////////// Перевод каретки UART////////////////////////////////////////////////////
void SCRCL(void)
{
USART_SEND_Byte(CR);
USART_SEND_Byte(LF);
}




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

void initmem(void)  /// ������������� ��������� ��������� � ������ ������� � ������ ������ EEPROM ��.
{
	unsigned int i;
	

	
	////////////////////////////////////////////// ������ � I2C EEPROM
	//i2c_init();
	
	//wfilename(0); /// �������� ����� �����.
	
	////////////////////////////////////////////// ������ � EEPROM MCU
	eeprom_write_word (VELMEM,6045); //5940
	eeprom_write_byte (NUMDATC,2);
	eeprom_write_byte (MODES,0x00); //0x01
	eeprom_write_word (MEMCFG,10);
	eeprom_write_word (MEMPNT,0);		// ����� �������� �� ���������
	eeprom_write_word (STAT,0);
	                               //// ������������ �������� 
	eeprom_write_byte (NASTR,0);	//1
	eeprom_write_word (CALIBD,3177); //24440
	eeprom_write_byte (MINUTES_OFF,0);	 ///  �����, �������������� 0=�������
	
	eeprom_write_word (VEL1,5930);  /// �������� ��� ��������
	eeprom_write_word (VEL2,5930);
	eeprom_write_word (VEL3,5930);
	eeprom_write_word (VEL4,5930);
	eeprom_write_word (VEL5,5930);
	eeprom_write_word (VEL6,5930);
	eeprom_write_word (VEL7,5930);
	eeprom_write_word (VEL8,5930);
	eeprom_write_word (VEL9,5930);
	eeprom_write_word (VEL10,2300);
										/// ������ ���������� ��� ��������
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
	eeprom_write_byte (BEEP_MODE,0x01); /// ���� ������� 0x01
#else
	eeprom_write_byte (BEEP_MODE,0x00); /// ���� ��������
#endif	
//	eeprom_write_byte (BEEP_MODE,0x00); /// ���� ������� 0x01
	
	
	eeprom_write_byte (AMP1,25);  /// �������� ��� ��������
	eeprom_write_byte (AMP2,25);
	eeprom_write_byte (AMP3,25);
	eeprom_write_byte (AMP4,25);
	eeprom_write_byte (AMP5,25);
	eeprom_write_byte (AMP6,25);
	eeprom_write_byte (AMP7,25);
	eeprom_write_byte (AMP8,25);
	eeprom_write_byte (AMP9,25);
	eeprom_write_byte (AMP10,25);
	
	eeprom_write_byte (DATCH1,2);  /// ������ � ����������
	eeprom_write_byte (DATCH2,2);
	eeprom_write_byte (DATCH3,2);
	eeprom_write_byte (DATCH4,2);
	eeprom_write_byte (DATCH5,2);
	eeprom_write_byte (DATCH6,2);
	eeprom_write_byte (DATCH7,2);
	eeprom_write_byte (DATCH8,2);
	eeprom_write_byte (DATCH9,2);
	eeprom_write_byte (DATCH10,7);
	
	eeprom_write_byte (MODE1,0);  /// ����� ������ � ����������
	eeprom_write_byte (MODE2,0);
	eeprom_write_byte (MODE3,0);
	eeprom_write_byte (MODE4,0);
	eeprom_write_byte (MODE5,0);
	eeprom_write_byte (MODE6,0);
	eeprom_write_byte (MODE7,0);
	eeprom_write_byte (MODE8,0);
	eeprom_write_byte (MODE9,0);
	eeprom_write_byte (MODE10,0);
	
	
	eeprom_write_word (RAZB_H1,1023);  /// ������ ����������� � ���������� 
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
	
	
	eeprom_write_word (DIFFU1,500);  /// �������� � ������ "����������" � ����������
	eeprom_write_word (DIFFU2,900);
	eeprom_write_word (DIFFU3,100);
	eeprom_write_word (DIFFU4,20);
	eeprom_write_word (DIFFU5,20);
	eeprom_write_word (DIFFU6,30);
	eeprom_write_word (DIFFU7,505);
	eeprom_write_word (DIFFU8,700);
	eeprom_write_word (DIFFU9,30);
	eeprom_write_word (DIFFU10,40);
	
	
	eeprom_write_word (NONIUSU1,nonius_half_range); /// ������ � ������ ������ � ����������
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
	
	eeprom_write_byte (BRIGHT,0); /// ������� ������� 1 - 5 ����� 4
	
	//eeprom_write_dword (TNAR,0); ///������ ��������� � ������
	CLRTR();						//������ ��������� � ������
//	zav_num=0x31313131;
	eeprom_write_byte (ZNUM0,zav_num>>24);
	eeprom_write_byte (ZNUM1,zav_num>>16);
	eeprom_write_byte (ZNUM2,zav_num>>8);
	eeprom_write_byte (ZNUM3,zav_num);
	
	
//////////////////////////////////////////////// journal ////////////////////////////////////////////

	eeprom_write_byte(journal_addr,0);								// ������ ������� � ������ (journal_size_off=4 �����)
	eeprom_write_byte(journal_addr+1,0);
	eeprom_write_byte(journal_addr+2,0);
	eeprom_write_byte(journal_addr+3,0);

	eeprom_write_word(journal_addr+journal_size_off,entry_size);	// ������ ������ � ������ (entry_size_off= 2 �����)
	eeprom_write_word(journal_addr+journal_size_off+entry_size_off,ee_page_numb);	// ����� �������� ��� ������ ee_page_numb (page_size_off=2 �����)

	for(i=0;i<page_numb_max;i++)
		eeprom_write_dword(get_page_size(i),0);						// �������� ������� ������� (���������� ������� �� ������ ��������)

/////////////////////////////////////////////////////////////////////////////////////////////////////	 

};

unsigned long corrector (unsigned long vals,unsigned char dach)//// ������� ��������� ��������  ���������� � ��������� ����� ��������� * 32.!!!

{
unsigned long ix=0;

switch (dach) //��� -1
	{
	
	case 0: ix = cord1(vals); break; //�112-10.0-8\2-�003	3�� ��� ���
	case 1: ix = cord2(vals); break; //�112-5.0-10\2-�003	3�� ��� ���
	case 2: ix = cord3(vals); break; //�112-2.5-12\2-�003	3�� ��� ���
	
	case 3: ix = cord4(vals); break; //�112-2.5�-12\2-�   //�112-5.0�-12\2-�  ���� ������� ��� 2 �������� 4 � 5	3�� ��� ���
	case 4: ix = cord4(vals); break; //�112-5.0�-12\2-�	
	case 5: ix = cord6(vals); break; //�112-2.5-12\2�		3�� ��� ���
	
	case 6: ix = cord7(vals); break; //�111-1.25-20\2� 	5�� ��� ��� !!!!
	
	case 7: ix = vals; break; //�111-1.25�20 //// ������ �� ��������� 20�� ��� ��� !!!
	case 8: ix = vals; break; //�111-1.25�20 //// ������ �� ��������� 20�� ��� ��� !!!
	
	
	/*case 1: ix = cord1(vals); break; //�112-10.0-8\2-�003
	case 2: ix = cord2(vals); break; //�112-5.0-10\2-�003
	case 3: ix = cord3(vals); break; //�112-2.5-12\2-�003
	case 4: ix = cord4(vals); break; //�112-2.5�-12\2-�
	case 5: ix = cord5(vals); break; //�112-5.0�-12\2-�
	case 6: ix = cord6(vals); break; //�111-1.25�20
	case 7: ix = cord7(vals); break; //�111-1.25�20
	case 8: ix = cord8(vals); break; //�111-1.25-20\2�*/
	}

return ix;

}
////-------------------------------------------------------------------------------------------------------------------------------------
unsigned long cord1 (unsigned long val) //// ������� ��������� ������� 1   10-8\2T

{
	/// ������ ��������    ---   /// ������� ��������   ������ � ���������
if ((val >= 30) && (val <=64))  // �������� � �� ��� ��������� ������ � �� 1��� - 0.01�� 9999- 99.99��   10000 - 100.0 ��
{
val = val-17;/// ���� �������� 1
goto ex1;
}


if ((val >= 64) && (val <=76))  // 
{
val = val-16;/// ���� �������� 2
goto ex1;
}


if ((val >= 76) && (val <=86))  // 
{
val = val-14;/// ���� �������� 2
goto ex1;
}

if ((val >= 86) && (val <=95))  // 
{
val = val-14;/// ���� �������� 3
goto ex1;
}

if ((val >= 95) && (val <=120))  // 
{
val = val-14;/// ���� �������� 4
goto ex1;
}


if ((val >= 120) && (val <=150))  // 
{
val = val-9;/// ���� �������� 5
goto ex1;
}




if ((val >= 150) && (val <=176))  // 
{
val = val-10;/// ���� �������� 5
goto ex1;
}



if ((val >= 176) && (val <=230))  // 
{
val = val-10;/// ���� �������� 5
goto ex1;
}



if ((val >= 230) && (val <=275))  // 
{
val = val-9;/// ���� �������� 5
goto ex1;
}



if ((val >= 275) && (val <=290))  // 
{
val = val-8;/// ���� �������� 5
goto ex1;
}



if ((val >= 290) && (val <=310))  // ���������� 3 �� 0
{
val = val;/// ���� �������� 6
goto ex1;
}




if ((val >= 310) && (val <=350))  // 
{
val = val-1;/// ���� �������� 7
goto ex1;
}

if ((val >= 350) && (val <=450))  // 
{
val = val-1;/// ���� �������� 8
goto ex1;
}



if ((val >= 450) && (val <=490))  // 
{
val = val+4;/// ���� �������� 9
goto ex1;
}




if ((val >= 490) && (val <=550))  // 
{
val = val+5;/// ���� �������� 9
goto ex1;
}

if ((val >= 550) && (val <=650))  // 
{
val = val+10;/// ���� �������� 10
goto ex1;
}

if ((val >= 650) && (val <=710))  // 
{
val = val+13;/// ���� �������� 11
goto ex1;
}



if ((val >= 710) && (val <=750))  // 
{
val = val+14;/// ���� �������� 12
goto ex1;
}



if ((val >= 750) && (val <=830))  // 
{
val = val+13;/// ���� �������� 12
goto ex1;
}



if ((val >= 830) && (val <=875))  // 
{
val = val+12;/// ���� �������� 12
goto ex1;
}



if ((val >= 875) && (val <=950))  // 
{
val = val+20;/// ���� �������� 13
goto ex1;
}


if ((val >= 950) && (val <=1050))  // 
{
val = val+19;/// ���� �������� 14
goto ex1;
}

if ((val >= 1050) && (val <=1110))  // 
{
val = val+21;/// ���� �������� 15
goto ex1;
}


if ((val >= 1110) && (val <=1350))  // 
{
val = val+20;/// ���� �������� 15
goto ex1;
}





if ((val >= 1350) && (val <=1830))  // 
{
val = val+21;/// ���� �������� 16
goto ex1;
}




if ((val >= 1830) && (val <=1850))  // 
{
val = val+26;/// ���� �������� 17
goto ex1;
}




if ((val >= 1850) && (val <=1875))  // 
{
val = val+26;/// ���� �������� 18
goto ex1;
}


if ((val >= 1875) && (val <=1930))  // 
{
val = val+25;/// ���� �������� 18
goto ex1;
}


if ((val >= 1930) && (val <=1970))  // 
{
val = val+24;/// ���� �������� 18
goto ex1;
}

if ((val >= 1970) && (val <=2100))  // 
{
val = val+23;/// ���� �������� 18
goto ex1;
}

if ((val >= 2100) && (val <=2200))  // 
{
val = val+22;/// ���� �������� 18
goto ex1;
}



if ((val >= 2200) && (val <=2300))  // 
{
val = val+24;/// ���� �������� 19
goto ex1;
}

if ((val >= 2300) && (val <=2400))  // 
{
val = val+23;/// ���� �������� 19
goto ex1;
}

if ((val >= 2400) && (val <=2475))  // 
{
val = val+22;/// ���� �������� 19
goto ex1;
}

if ((val >= 2475) && (val <=2600))  // 
{
val = val+21;/// ���� �������� 19
goto ex1;
}



if ((val >= 2600) && (val <=2700))  // 
{
val = val+20;/// ���� �������� 20
goto ex1;
}

if ((val >= 2700) && (val <=2800))  // 
{
val = val+10;/// ���� �������� 20
goto ex1;
}


if ((val >= 2800) && (val <=2900))  // 
{
val = val;/// ���� �������� 20
goto ex1;
}

if ((val >= 2900) && (val <=3000))  // 
{
val = val-10;/// ���� �������� 20
goto ex1;
}


if ((val >= 3000) && (val <=3250))  // 
{
val = val-22;/// ���� �������� 20
goto ex1;
}


if ((val >= 3250) && (val <=3750))  // 
{
val = val-25;/// ���� �������� 21
goto ex1;
}

if ((val >= 3750) && (val <=4250))  // 
{
val = val-28;/// ���� �������� 22
goto ex1;
}

if ((val >= 4250) && (val <=4750))  // 
{
val = val-36;/// ���� �������� 23
goto ex1;
}

if ((val >= 4750) && (val <=6250))  // 
{
val = val-38;/// ���� �������� 24
goto ex1;
}

if ((val >= 6250) && (val <=8250))  // 
{
val = val-40;/// ���� �������� 25
goto ex1;
}

if ((val >= 8250) && (val <=9500))  // 
{
val = val-42;/// ���� �������� 26
goto ex1;
}

if ((val >= 9500) && (val <=15000))  // 
{
val = val-54;/// ���� �������� 27
goto ex1;
}

if ((val >= 15000) && (val <=25000))  // 
{
val = val-60;/// ���� �������� 28
goto ex1;
}

if ((val >= 25000) && (val <=35000))  // 
{
val = val-70;/// ���� �������� 29
goto ex1;
}

if ((val >= 35000) && (val <=45000))  // 
{
val = val-80;/// ���� �������� 30
goto ex1;
}

ex1:;
return val;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned long cord2 (unsigned long val) //// ������� ��������� ������� 2 �112-5.0-10\2-�003

{
	/// ������ ��������    ---   /// ������� ��������   ������ � ���������
if ((val >= 30) && (val <=76))  // �������� � �� ��� ��������� ������ � �� 1��� - 0.01�� 9999- 99.99��   10000 - 100.0 ��
{
val = val-7;/// ���� �������� 1 -10
goto ex1;
}

if ((val >= 76) && (val <=86))  // 
{
val = val-6;/// ���� �������� 2 -10
goto ex1;
}

if ((val >= 86) && (val <=95))  // 
{
val = val-5;/// ���� �������� 3 -13
goto ex1;
}

if ((val >= 95) && (val <=130))  //
{
	val = val-4;/// ���� �������� 4
	goto ex1;
}

if ((val > 130) && (val <=150))  // 
{
val = val-3;/// ���� �������� 4
goto ex1;
}

if ((val > 150) && (val <=170))  //
{
	val = val-2;/// ���� �������� 4
	goto ex1;
}
if ((val > 170) && (val <=200))  // 
{
val = val-1;/// ���� �������� 5
goto ex1;
}

if ((val > 200) && (val <=270))  //
{
	//val = val-9;/// ���� �������� 5
	goto ex1;
}
if ((val >= 270) && (val <=310))  // ���������� 3 �� 0
{
//val = val;/// ���� �������� 6
goto ex1;
}

if ((val >= 310) && (val <=350))  // 
{
val = val-5;/// ���� �������� 7 -7
goto ex1;
}

if ((val >= 350) && (val <=450))  // -6
{
val = val-4;/// ���� �������� 8
goto ex1;
}

if ((val >= 450) && (val <=550))  // 
{
val = val-3;/// ���� �������� 9 -5
goto ex1;
}

if ((val >= 550) && (val <=650))  // 
{
val = val-1;/// ���� �������� 10  -3
goto ex1;
}

if ((val >= 650) && (val <=750))  // 
{
val = val;/// ���� �������� 11  +1
goto ex1;
}

if ((val >= 750) && (val <=850))  // 
{
val = val+3;/// ���� �������� 12  +5
goto ex1;
}

if ((val >= 850) && (val <=950))  // 
{
val = val+5;/// ���� �������� 13 +7
goto ex1;
}

if ((val >= 950) && (val <=1050))  // 
{
val = val+8;/// ���� �������� 14 +11
goto ex1;
}

if ((val >= 1050) && (val <=1350))  // 
{


val = val+19;/// ���� �������� 15
goto ex1;
}

if ((val >= 1350) && (val <=1650))  // 
{
val = val+20;/// ���� �������� 16
goto ex1;
}

if ((val >= 1650) && (val <=1900))  // 
{
val = val+20;/// ���� �������� 17
goto ex1;
}

if ((val >= 1900) && (val <=2250))  // 
{
val = val+25;/// ���� �������� 18
goto ex1;
}

if ((val >= 2250) && (val <=2750))  // 
{
val = val+28;/// ���� �������� 19
goto ex1;
}

if ((val >= 2750) && (val <=3250))  // 
{
val = val+29+5;/// ���� �������� 20
goto ex1;
}

if ((val >= 3250) && (val <=3750))  // 
{
val = val+33+10;/// ���� �������� 21
goto ex1;
}

if ((val >= 3750) && (val <=4250))  // 
{
val = val+34+15;/// ���� �������� 22
goto ex1;
}

if ((val >= 4250) && (val <=4750))  // 
{
val = val+34+20;/// ���� �������� 23
goto ex1;
}

if ((val >= 4750) && (val <=6250))  // 
{
val = val+34+25;/// ���� �������� 24
goto ex1;
}

if ((val >= 6250) && (val <=8250))  // 
{
val = val+34+30;/// ���� �������� 25 +34
goto ex1;
}

if ((val >= 8250) && (val <=9500))  // 
{
val = val+34+50;/// ���� �������� 26 +36
goto ex1;
}

if ((val >= 9500) && (val <=15000))  // 
{
val = val+34+50;/// ���� �������� 27 +34
goto ex1;
}

if ((val >= 15000) && (val <=25000))  // 
{
val = val+40+50;/// ���� �������� 28
goto ex1;
}

if ((val >= 25000) && (val <=35000))  // 
{
val = val+20;/// ���� �������� 29
goto ex1;
}

if ((val >= 35000) && (val <=45000))  // 
{
//val = val;/// ���� �������� 30
goto ex1;
}

ex1:;
return val;
}




unsigned long cord3 (unsigned long val) //// ������� ��������� ������� 3 2.5-12\2�

{
	/// ������ ��������    ---   /// ������� ��������   ������ � ���������
if ((val >= 30) && (val <=76))  // �������� � �� ��� ��������� ������ � �� 1��� - 0.01�� 9999- 99.99��   10000 - 100.0 ��
{
val = val;/// ���� �������� 1
goto ex1;
}

if ((val >= 76) && (val <=86))  // 
{
val = val;/// ���� �������� 2
goto ex1;
}

if ((val >= 86) && (val <=95))  // 
{
val = val;/// ���� �������� 3
goto ex1;
}

if ((val >= 95) && (val <=150))  // 
{
val = val-4;/// ���� �������� 4
goto ex1;
}

if ((val >= 150) && (val <=270))  // 
{
val = val-15;/// ���� �������� 5
goto ex1;
}

if ((val >= 270) && (val <=310))  // ���������� 3 �� 0
{
val = val;/// ���� �������� 6
goto ex1;
}

if ((val >= 310) && (val <=350))  // 
{
val = val+1;/// ���� �������� 7
goto ex1;
}

if ((val >= 350) && (val <=450))  // 
{
val = val+2;/// ���� �������� 8
goto ex1;
}

if ((val >= 450) && (val <=550))  // 
{
val = val+4;/// ���� �������� 9
goto ex1;
}

if ((val >= 550) && (val <=650))  // 
{
val = val+8;/// ���� �������� 10
goto ex1;
}

if ((val >= 650) && (val <=750))  // 
{
val = val+12;/// ���� �������� 11
goto ex1;
}

if ((val >= 750) && (val <=850))  // 
{
val = val+12;/// ���� �������� 12
goto ex1;
}

if ((val >= 850) && (val <=950))  // 
{
val = val+15;/// ���� �������� 13
goto ex1;
}

if ((val >= 950) && (val <=1050))  // 
{
val = val+16;/// ���� �������� 14
goto ex1;
}

if ((val >= 1050) && (val <=1350))  // 
{
val = val+18;/// ���� �������� 15
goto ex1;
}

if ((val >= 1350) && (val <=1650))  // 
{
val = val+25;/// ���� �������� 16
goto ex1;
}

if ((val >= 1650) && (val <=1900))  // 
{
val = val+28;/// ���� �������� 17
goto ex1;
}

if ((val >= 1900) && (val <=2250))  // 
{
val = val+30;/// ���� �������� 18
goto ex1;
}

if ((val >= 2250) && (val <=2750))  // 
{
val = val+34;/// ���� �������� 19
goto ex1;
}

if ((val >= 2750) && (val <=3250))  // 
{
val = val+40;/// ���� �������� 20
goto ex1;
}

if ((val >= 3250) && (val <=3750))  // 
{
val = val+42;/// ���� �������� 21
goto ex1;
}

if ((val >= 3750) && (val <=4250))  // 
{
val = val+42;/// ���� �������� 22
goto ex1;
}

if ((val >= 4250) && (val <=4750))  // 
{
val = val+44;/// ���� �������� 23
goto ex1;
}

if ((val >= 4750) && (val <=6250))  // 
{
val = val+46;/// ���� �������� 24
goto ex1;
}

if ((val >= 6250) && (val <=8250))  // 
{
val = val+44;/// ���� �������� 25
goto ex1;
}

if ((val >= 8250) && (val <=9500))  // 
{
val = val+40;/// ���� �������� 26
goto ex1;
}

if ((val >= 9500) && (val <=15000))  // 
{
val = val+35;/// ���� �������� 27
goto ex1;
}

if ((val >= 15000) && (val <=25000))  // 
{
val = val+30;/// ���� �������� 28
goto ex1;
}

if ((val >= 25000) && (val <=35000))  // 
{
val = val;/// ���� �������� 29
goto ex1;
}

if ((val >= 35000) && (val <=45000))  // 
{
val = val;/// ���� �������� 30
goto ex1;
}

ex1:;
return val;
}



unsigned long cord4 (unsigned long val) //// ������� ��������� ������� 4 �112-2.5�-12/2-�
 {
	/// ������ ��������    ---   /// ������� ��������   ������ � ���������
if ((val >= 30) && (val <=76))  // �������� � �� ��� ��������� ������ � �� 1��� - 0.01�� 9999- 99.99��   10000 - 100.0 ��
{
val = val;/// ���� �������� 1
goto ex1;
}

if ((val >= 76) && (val <=86))  // 
{
val = val;/// ���� �������� 2
goto ex1;
}

if ((val >= 86) && (val <=95))  // 
{
val = val-2;/// ���� �������� 3
goto ex1;
}

	if ((val >= 95) && (val <=120))  // 
	{
	val = val-2;/// ���� �������� 4
	goto ex1;
	}

	if ((val >= 120) && (val <=140))  // 
	{
	val = val-3;/// ���� �������� 4
	goto ex1;
	}

	if ((val >= 140) && (val <=170))  // 
	{
	val = val-4;/// ���� �������� 4
	goto ex1;
	}
	
	if ((val >= 170) && (val <=185))  // 
	{
	val = val-5;/// ���� �������� 4
	goto ex1;
	}


if ((val >= 185) && (val <=270))  // 
{
val = val-6;/// ���� �������� 5
goto ex1;
}

if ((val >= 270) && (val <=310))  // ���������� 3 �� 0
{
val = val;/// ���� �������� 6
goto ex1;
}

if ((val >= 310) && (val <=350))  // 
{
//val = val-6;/// ���� �������� 7
goto ex1;
}

if ((val >= 350) && (val <=450))  // 
{
//val = val-7;/// ���� �������� 8
goto ex1;
}

if ((val >= 450) && (val <=550))  // 
{
//val = val-7;/// ���� �������� 9
goto ex1;
}

if ((val >= 550) && (val <=650))  // 
{
//val = val-8;/// ���� �������� 10
goto ex1;
}

if ((val >= 650) && (val <=750))  // 
{
//val = val-7;/// ���� �������� 11
goto ex1;
}

if ((val >= 750) && (val <=850))  // 
{
//val = val-5;/// ���� �������� 12
goto ex1;
}

if ((val >= 850) && (val <=950))  // 
{
//val = val-2;/// ���� �������� 13
goto ex1;
}

if ((val >= 950) && (val <=1050))  // 
{
//val = val-2;/// ���� �������� 14
goto ex1;
}

if ((val >= 1050) && (val <=1350))  // 
{
//val = val;/// ���� �������� 15
goto ex1;
}

if ((val >= 1350) && (val <=1650))  // 
{
//val = val+2;/// ���� �������� 16
goto ex1;
}

if ((val >= 1650) && (val <=1900))  // 
{
//val = val+4;/// ���� �������� 17
goto ex1;
}

if ((val >= 1900) && (val <=2250))  // 
{
//val = val+6;/// ���� �������� 18
goto ex1;
}

if ((val >= 2250) && (val <=2750))  // 
{
//val = val+8;/// ���� �������� 19
goto ex1;
}

if ((val >= 2750) && (val <=3250))  // 
{
//val = val+12;/// ���� �������� 20
goto ex1;
}

if ((val >= 3250) && (val <=3750))  // 
{
//val = val+16;/// ���� �������� 21
goto ex1;
}

if ((val >= 3750) && (val <=4250))  // 
{
//val = val+20;/// ���� �������� 22
goto ex1;
}

if ((val >= 4250) && (val <=4750))  // 
{
//val = val+30;/// ���� �������� 23
goto ex1;
}

if ((val >= 4750) && (val <=6250))  // 
{
//val = val+16;/// ���� �������� 24
goto ex1;
}

if ((val >= 6250) && (val <=8250))  // 
{
//val = val+18;/// ���� �������� 25
goto ex1;
}

if ((val >= 8250) && (val <=9500))  // 
{
//val = val+20;/// ���� �������� 26
goto ex1;
}

if ((val >= 9500) && (val <=15000))  // 
{
//val = val+20;/// ���� �������� 27
goto ex1;
}

if ((val >= 15000) && (val <=25000))  // 
{
//val = val+20;/// ���� �������� 28
goto ex1;
}

if ((val >= 25000) && (val <=35000))  // 
{
//val = val+20;/// ���� �������� 29
goto ex1;
}

if ((val >= 35000) && (val <=42000))  // 
{
//val = val+20;/// ���� �������� 29
goto ex1;
}

if ((val >= 42000) && (val <=55000))  // 
{
//val = val;/// ���� �������� 30
goto ex1;
}

ex1:;

return val;
}

unsigned long cord5 (unsigned long val) //// ������� ��������� ������� 5 �112-5.0�-12/2-� ������������� ���� 4 

{
return val;
}

unsigned long cord6 (unsigned long val) //// ������� ��������� ������� 6 �112-2.5-12/2�
{
	/// ������ ��������    ---   /// ������� ��������   ������ � ���������
				// �������� � �� ��� ��������� ������ � �� 1��� - 0.01�� 9999- 99.99��   10000 - 100.0 ��


if ((val >= 270) && (val <=310))  // ���������� 3 �� 0
{
val = val;/// ���� �������� 6
goto ex1;
}

if ((val >= 310) && (val <=350))  // 
{
val = val+3;/// ���� �������� 7
goto ex1;
}

if ((val >= 350) && (val <=450))  // 
{
val = val+5;/// ���� �������� 8
goto ex1;
}

if ((val >= 450) && (val <=550))  // 
{
val = val+15;/// ���� �������� 9
goto ex1;
}

if ((val >= 550) && (val <=650))  // 
{
val = val+23;/// ���� �������� 10
goto ex1;
}

if ((val >= 650) && (val <=750))  // 
{
val = val+30;/// ���� �������� 11
goto ex1;
}

if ((val >= 750) && (val <=850))  // 
{
val = val+30;/// ���� �������� 12
goto ex1;
}

if ((val >= 850) && (val <=950))  // 
{
val = val+36;/// ���� �������� 13
goto ex1;
}

if ((val >= 950) && (val <=1050))  // 
{
val = val+40;/// ���� �������� 14
goto ex1;
}

if ((val >= 1050) && (val <=1350))  // 
{
val = val+50;/// ���� �������� 15
goto ex1;
}

if ((val >= 1350) && (val <=1650))  // 
{
val = val+53;/// ���� �������� 16
goto ex1;
}

if ((val >= 1650) && (val <=1900))  // 
{
val = val+60;/// ���� �������� 17
goto ex1;
}

if ((val >= 1900) && (val <=2250))  // 
{
val = val+62;/// ���� �������� 18
goto ex1;
}

if ((val >= 2250) && (val <=2750))  // 
{
val = val+64;/// ���� �������� 19
goto ex1;
}

if ((val >= 2750) && (val <=3250))  // 
{
val = val+68;/// ���� �������� 20
goto ex1;
}

if ((val >= 3250) && (val <=3750))  // 
{
val = val+70;/// ���� �������� 21
goto ex1;
}

if ((val >= 3750) && (val <=4250))  // 
{
val = val+75;/// ���� �������� 22
goto ex1;
}

if ((val >= 4250) && (val <=4750))  // 
{
val = val+80;/// ���� �������� 23
goto ex1;
}

if ((val >= 4750) && (val <=6250))  // 
{
val = val+70;/// ���� �������� 24
goto ex1;
}

if ((val >= 6250) && (val <=8250))  // 
{
val = val+60;/// ���� �������� 25
goto ex1;
}

if ((val >= 8250) && (val <=9500))  // 
{
val = val+50;/// ���� �������� 26
goto ex1;
}

if ((val >= 9500) && (val <=15000))  // 
{
val = val+40;/// ���� �������� 27
goto ex1;
}

if ((val >= 15000) && (val <=25000))  // 
{
val = val+40;/// ���� �������� 28
goto ex1;
}

if ((val >= 25000) && (val <=35000))  // 
{
val = val+40;/// ���� �������� 29
goto ex1;
}


ex1:;
return val;
}

unsigned long cord7 (unsigned long val) //// ������� ��������� ������� 7 �112-1.25-20\2�  � ��� 5��!!!
{
	/// ������ ��������    ---   /// ������� ��������   ������ � ���������
								// �������� � �� ��� ��������� ������ � �� 1��� - 0.01�� 9999- 99.99��   10000 - 100.0 ��

if ((val >= 290) && (val <=350))  // 
{
val = val-5;/// ���� �������� 1
goto ex1;
}

if ((val >= 350) && (val <=480))  // 
{
val = val-4;/// ���� �������� 2
goto ex1;
}

if ((val >= 480) && (val <=510))  //  5.�� ������ ��� 0!!!
{
val = val;/// ���� �������� 3
goto ex1;
}

if ((val >= 510) && (val <=560))  // 
{
val = val+4;/// ���� �������� 4
goto ex1;
}

if ((val >= 560) && (val <=650))  // 
{
val = val+6;/// ���� �������� 5
goto ex1;
}

if ((val >= 650) && (val <=750))  // 
{
val = val+8;/// ���� �������� 6
goto ex1;
}

if ((val >= 750) && (val <=850))  // 
{
val = val+16;/// ���� �������� 7
goto ex1;
}

if ((val >= 850) && (val <=950))  // 
{
val = val+22;/// ���� �������� 8
goto ex1;
}

if ((val >= 950) && (val <=1050))  // 
{
val = val+23;/// ���� �������� 9
goto ex1;
}

if ((val >= 1050) && (val <=1350))  // 
{
val = val+28;/// ���� �������� 10
goto ex1;
}

if ((val >= 1350) && (val <=1650))  // 
{
val = val+36;/// ���� �������� 11
goto ex1;
}

if ((val >= 1650) && (val <=1900))  // 
{
val = val+45;/// ���� �������� 12
goto ex1;
}

if ((val >= 1900) && (val <=2250))  // 
{
val = val+48;/// ���� �������� 13
goto ex1;
}

if ((val >= 2250) && (val <=2750))  // 
{
val = val+55;/// ���� �������� 14
goto ex1;
}

if ((val >= 2750) && (val <=3250))  // 
{
val = val+70;/// ���� �������� 15
goto ex1;
}

if ((val >= 3250) && (val <=3750))  // 
{
val = val+70;/// ���� �������� 16
goto ex1;
}

if ((val >= 3750) && (val <=4250))  // 
{
val = val+72;/// ���� �������� 17
goto ex1;
}

if ((val >= 4250) && (val <=4750))  // 
{
val = val+80;/// ���� �������� 18
goto ex1;
}

if ((val >= 4750) && (val <=6250))  // 
{
val = val+65;/// ���� �������� 19
goto ex1;
}

if ((val >= 6250) && (val <=8250))  // 
{
val = val+58;/// ���� �������� 20
goto ex1;
}

if ((val >= 8250) && (val <=9500))  // 
{
val = val+48;/// ���� �������� 21
goto ex1;
}

if ((val >= 9500) && (val <=15000))  // 
{
val = val+46;/// ���� �������� 22
goto ex1;
}

if ((val >= 15000) && (val <=25000))  // 
{
val = val+40;/// ���� �������� 23
goto ex1;
}

if ((val >= 25000) && (val <=35000))  // 
{
val = val;/// ���� �������� 24
goto ex1;
}

if ((val >= 35000) && (val <=45000))  // 
{
val = val;/// ���� �������� 25
goto ex1;
}

ex1:;
return val;
}


unsigned long cord8 (unsigned long val) //// ������� ��������� ������� 8

{
return val;
}


unsigned long cord9 (unsigned long val) //// ������� ��������� ������� 9

{
return val;
}


////////////////////////////////////������ � ������� //////////////////////////////////////////////////////
/*

void MEMORY_MEN(unsigned char mode) //// ����� ������ �������� ���� ---- 
{
unsigned char io=1,bo=0,mf=0,tf=0;
unsigned int mp=0;

agn:;

tf=filetype();  /// ��������� ��� ������
mf=filename(); /// ������ ����� �������� �����
mp=rfd(mf,tf); /// ��������� ����   mf- ����� ����� tf- ��� �����.


cls();
//show_mpos(8,20,0);///������


show_MEMmenu(io,mf,mp,tf);
draw_memoline (12,7,48); // ������� ����� ������ "���� ������"
draw_smem(mf,mp,tf);	// ���������� �����

BEEP(2);


			bo=keymem;  /// :����� ���� �������� ������
			
			while (bo==keymem)
			{
			_delay_ms(35);
			bo=key_find();	
			};
			rkey();


while (!(key_find()==0)) /// ����� ���� �������� ��� ������ 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);

while (!(key_find()==keyenter)) /// ����� ������ ����
{
 
	
	if (key_find()==keydown)   /// ������� ������ ����� ����/// � ����������� ����������.
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
	
	
	if (key_find()==keymem) /// ����� �� ������ �� ������� ����� --- ���� ����� �� �������� ����� �����.
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
	if (io==1) {SFM(); io=1; goto agn;} /// ����� �����
	if (io==5) {MF(); io=5; goto agn;} /// ���� ��������������
	if (io==2) {RFILE();io=2; goto agn;} /// �������� �����
	if (io==3) {FCLR(); io=3; goto agn;} /// �������� ���� --- ������������ ��������� ������� � ����� ������ �� ��������� !!! 
	if (io==4) {CLRMEMALL(); io=4; goto agn;} /// �������� ��� ������.
	
pm_out:;
cls();
rkey();
}
/////////////////////////////////////////////////////////////////////////////////
*/
/*

unsigned char filename(void)  /// ��������� ����� �����
{
unsigned char i=0;
i = readWEE(fname);
return i; 
}

void wfilename(unsigned char i)  ///�������� ��� �����
{
writeWEE(i,fname);
}



unsigned int rfd(unsigned char mp,unsigned char tf) //// ��������� ����� ��������� ����� � ��������� �����
{
unsigned int posf=0, maxlen=0, point=0;

posf = pointstart + mp; /// ����� ������ ������ ��������� ������� �����.

maxlen = v1m30/tf; /// ����� ������������ ������ �����

point = readWEE(posf); /// ������ ������ ������� �����.

return (maxlen-point);  /// ������� �� ���� ������ - ������� �����
}




unsigned int rfd_use(unsigned char mp,unsigned char tf) //// ��������� ����� ������� ����� � �����
{
unsigned int posf=0, maxlen=0, point=0;

posf = pointstart + mp; /// ����� ������ ������ ��������� ������� �����.

maxlen = v1m30/tf; /// ����� ������������ ������ �����

point = readWEE(posf); /// ������ ������ ������� �����.

return point;  /// ������� �� ���� ������ - ������� �����
}

*/
////////////////////////////////////

/*
unsigned char filetype(void)  /// ��������� ��� ������
{
unsigned char i=0;
i = readWEE(tfile);
return i; 
}


void wfiletype(unsigned char i)  ///�������� ��� ������ 
{
writeWEE(i,tfile);
}
*/

///////////////////////////////////// �������� �������� ����� ������� ////////////////////////////////////
void WR_SNUM(unsigned char a,unsigned char b,unsigned char c,unsigned char d)
{
//_delay_ms(15);
eeprom_write_byte (ZNUM0,d);
eeprom_write_byte (ZNUM1,c);
eeprom_write_byte (ZNUM2,b);
eeprom_write_byte (ZNUM3,a);
//_delay_ms(25);
}
///////////////////////////////////////////////// �������������� //////////////////////////////////////////

void MF(void) /// ���� ��������������
{

cls();
unsigned char io=1,i=0,ib=0;

BEEP(2);
i=show_FORMmenu(io);
while (!(key_find()==0)) /// ����� ���� �������� ��� ������ 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);

while (!(key_find()==keyenter)) /// ����� ������ ����
{
 
	
	if (key_find()==keydown)   /// ������� ������ ����� ���� /// � ����������� ����������.
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
	
	
	
	if (key_find()==keymem) /// ����� �� ������ �� ������� ����� --- ���� ����� �� �������� ����� �����.
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


FORMAT(i);  //// ���� ��������������

exfm:; /// ������ ��������������
}




void FORMAT(unsigned char tf) 
{


draw_wdataerase(); //// �������� ������ ����� ������� ���������� �� �� 0  ��� �� enter


while (!(key_find()==0)) /// ����� ���� �������� ��� ������ 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);

while (!(key_find()==keyzero)) /// ����� ������ 0  ��� ������ ��������
{

	if (key_find()==keyenter)   /// ���� ���� �� ������ �������� � �����
	{ 

	//BEEP(1);
	goto exf;
	
	}

}


BEEP(2);
cls();
show_wpos(34,6,14); //// ����� 
clraEE(); /// ������� ������

wfiletype(tf); /// ��� ������ 
wfilename(0);//// ��������� ����� �� 0 ����
BEEP(2);

exf:;
cls();
}
/////////////////////////////////////////// ����� ����� /////////////////////////////////////////////////

void SFM(void) /// ���� ������ �����
{

signed char io=0;

unsigned char nfile=0,tf=0;


nfile=filename(); /// �������� ����� �����
tf=filetype(); /// �������� ��� �����
cls();
BEEP(2);

io = nfile;
//ic = nfile;
show_SELmenu(io);

while (!(key_find()==0)) /// ����� ���� �������� ��� ������ 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);

while (!(key_find()==keyenter)) /// ����� ������ ����
{
 
	
	while (key_find()==keyup)   /// ������� ������ ����� ����
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
	
	
	if (key_find()==keymem) /// ����� �� ������ �� ������� ����� --- ���� ����� �� �������� ����� �����.
	{
	io=keymem;
	
	while (io==keymem)
	{
	_delay_ms(35);
	io=key_find();
	//BEEP(1);
	};
	
	_delay_ms(500);
	
	wfilename(nfile); /// ������ ������ �����  ������� ��� ����������
	BEEP(1);
	goto sf_out;
	}
	
}
sf_out:;
rkey();
}


/*
/////////////////////////////////////////// �������� ����� //////////////////////////////////////////////
void RFILE(void)
{
cls();
unsigned char nfile=0,tf=0, STSM=0;
unsigned long maxlen=0,free=0,filestart=0,fileend=0,io=0,posf=0,ax=0;
signed long point=0;

nfile=filename(); /// �������� ����� �����
tf=filetype(); /// �������� ��� �����

posf = pointstart + nfile; /// ����� ������ ������ ��������� ������� �����.

maxlen = (v1m30/tf); /// ����� ������������ ������ �����

point = readWEE(posf); /// ������ ������ ������� �����.

point = point-1;

if (point <= 0) {point = 0;}

free= maxlen-point; /// ��������� �����

filestart= (nfile * maxlen) + memstart; ///����� ������ ����� (� �������) ����������  ��� ��������� � ������
//filestart = filestart+1;///
fileend = filestart+point;  /// ����� ����� ����� (� �������)


//// -------------------------
io=filestart; /// � ��������� ������� ����� ��� ���������
ax=readWEE(io);



STSM = ax>>16;
ax = ax & 0x0000FFFF;

draw_memoline(13,7,48); ///������ ������� ����� �� enter
draw_dline();// ����� 
show_mmdiv();// ����� ������

vf_disp(ax,nfile,(io-filestart+1),tf);
draw_CLASSMODE(STSM);


BEEP(2);

Eexf5:;

while (!(key_find()==0)) /// ����� ���� �������� ��� ������ 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);

while (!(key_find()==keyenter)) /// ����� ������ ����
{
 
	
	while (key_find()==keyup)   /// ������� ���� ����� ����  ����� ��������� � �������
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
		vf_disp(ax,nfile,(io-filestart+1),tf);	 /// ���������� ������ �� ������
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
		vf_disp(ax,nfile,(io-filestart+1),tf);	 /// ���������� ������ �� ������
		draw_CLASSMODE(STSM);
		
		rkey();
	}
	
	
	
	
	
	while (key_find()==keynastr) ///������������ � ������ �����
	{
		_delay_ms (readfilest);
		key_find();	
		io = filestart;
		//if (io<=(filestart-1)) { io =filestart;}
		BEEP(3);
		

		
		ax=readWEE(io);
		STSM = ax>>16;
		ax = ax & 0x0000FFFF;
		vf_disp(ax,nfile,(io-filestart+1),tf);	 /// ���������� ������ �� ������
		draw_CLASSMODE(STSM);
		
		rkey();
	
	}
	
		while (key_find()==keyrezim) ///������������ � ����� �����
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
		vf_disp(ax,nfile,(io-filestart+1),tf);	 /// ���������� ������ �� ������
		draw_CLASSMODE(STSM);
		
		rkey();
	
	}
	
	
		while (key_find()==keymem) ///������� ��������� ������    ////////   ������� � ����� �� ������� ������
	{
		_delay_ms (readfilestE);
		key_find();	
		
			rkey();
			_delay_ms(10);
			
	if (key_find()==keymem) /// �� ������ ������ ������  ����� �������
				
		{		
		
			_delay_ms(10);
		
								draw_wdataerase(); //// �������� ������ ����� ������� ���������� �� �� 0  ��� �� enter
			_delay_ms(10);

								while (!(key_find()==0)) /// ����� ���� �������� ��� ������ 
									{
									}
									_delay_ms (620);
									key_find();
									_delay_ms (32);

								while (!(key_find()==keyzero)) /// ����� ������ 0  ��� ������ ��������
								{

									if (key_find()==keyenter)   /// ���� ���� �� ������ �������� � �����
									{ 

									BEEP(1);
							
													
													ax=readWEE(io);
													STSM = ax>>16;
													ax = ax & 0x0000FFFF;
													cls();
													vf_disp(ax,nfile,(io-filestart+1),tf);	 /// ���������� ������ �� ������
													draw_memoline(13,7,48); ///������ ������� ����� �� enter
													draw_dline();// �����
													draw_CLASSMODE(STSM);
													
													rkey();
									
									goto Eexf5;
									
									}

								}
		
		
		
		if (!(point<=0)) //// ��������� , ����� �� ������� ������. �� ��������� �� ��� � �����.
		{
		writeWEE(point,posf); /// �������� � ��������� ����� ����������� �� ������� 
		}
		
		
			if (point <= 0) 
				
				{
				writeWEE(0x00,posf); /// �������� � ��������� ����� 0
				writeWEE(0x00,filestart); /// �������� � ������ 0
				}
		
		point = readWEE(posf); /// ������ ������ ������� �����.
		
		point = point-1;
		if (point < 0) {point = 0;}
		
		free= maxlen-point; /// ��������� �����

		filestart= (nfile * maxlen) + memstart; ///����� ������ ����� (� �������) ����������  ��� ��������� � ������
		//filestart = filestart+1;///
		fileend = filestart+point;
			/// ����� ����� ����� (� �������)
		
		
		io = fileend;
		//if (io<=(filestart-1)) { io =filestart;}
		//BEEP(3);
		

		
		ax=readWEE(io);
		STSM = ax>>16;
		ax = ax & 0x0000FFFF;
		cls();
		vf_disp(ax,nfile,(io-filestart+1),tf);	 /// ���������� ������ �� ������
		draw_memoline(13,7,48); ///������ ������� ����� �� enter
		draw_dline();// �����
		show_mmdiv();// ����� ������
		draw_CLASSMODE(STSM); 
		
		BEEP(1); ////// 
						rkey();
	/*					_delay_ms(50);
		
						while (!(key_find()==0)) /// ����� ���� �������� ��� ������ 
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

/////////////////////////////////////////////// ���������� ������ //////////////////////////////////////
*/

/*
void vf_disp(unsigned int val, unsigned char mf,unsigned int mp,unsigned char tf)  /// ���������� �� ������� ������ �����. mp � ���� ������ ��������� ������� ������
{


//! cls(); - ��-�� ����� ������ ������� �����

//!draw_memoline(13,7,48); ///������ ������� ����� �� ���
//!show_mmdiv();	
//!draw_dline();


put_int_to_num_buffer(val,0); //// ������� ������� �� �������  
show_num_buffer();
draw_smem(mf,mp,tf);  //// �������� ��������� ������ �������

}

/////////////////////////////////////////// �������� � ���� ����� ///////////////////////////////////////

unsigned char WR_FILE (unsigned long val)
{

if (val==0x00) {BEEP(4); return 4;}//// ���� ��������� ������

unsigned char nfile=0,tf=0;
unsigned long maxlen=0,free=0,filestart=0,fileend=0,posf=0,point=0;

nfile=filename(); /// �������� ����� �����
tf=filetype(); /// �������� ��� �����

posf = pointstart + nfile; /// ����� ������ ������ ��������� ������� �����.

maxlen = v1m30/tf; /// ����� ������������ ������ �����

point = readWEE(posf); /// ������ ������ ������� �����.

free= maxlen-point; /// ��������� �����

	if (free==0) {return 5;} /// ����� ��������� ��������� ������ 
	
filestart= (nfile * maxlen) + memstart; ///����� ������ ����� (� �������) ����������  ��� ��������� � ������

//filestart = filestart-1;

fileend = filestart+point;  /// ����� ����� ����� (� �������)


free= READ_CLASSM(); /// �������� � ������ �������, � ��������� ��� ������� ��� ��������

free = (free << 16) + val;

writeWEE(free,(fileend)); /// �������� � ������ ���������� �����
_delay_ms(10);
writeWEE((point+1),posf); /// �������� � ��������� ����� ����������� �� ������� 


BEEP(1);
return 1; /// ������ ������� - ��

}
////////////////////////////////////// ������� ����� //// //////////////////////////////////////////
void FCLR(void)  /// ���������� � ��������� ������� ����� ������� 0  ������ �� ��������� !!!!!
{
unsigned char nfile=0;
unsigned int posf=0, filestart=0, tf=0, maxlen=0;

cls();
BEEP(2);


draw_wdataerase(); //// �������� ������ ����� ������� ���������� �� �� 0  ��� �� enter

while (!(key_find()==0)) /// ����� ���� �������� ��� ������ 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);

while (!(key_find()==keyzero)) /// ����� ������ 0  ��� ������ ��������
{

	if (key_find()==keyenter)   /// ���� enter �� ������ �������� � �����
	{ 

	//BEEP(1);
	goto exf;
	
	}

}

nfile=filename(); /// �������� ����� �����
tf=filetype(); /// �������� ��� �����

posf = pointstart + nfile; /// ����� ������ ������ ��������� ������� �����.

maxlen = v1m30/tf; /// ����� ������������ ������ �����
	
filestart= (nfile * maxlen) + memstart; ///����� ������ ����� (� �������) ����������  ��� ��������� � ������

///point = readWEE(posf); /// ������ ������ ������� �����.

//writeWEE(0,posf); /// �������� � ��������� ����� 0 - ��������� �������
writeWEE(0x00,posf); /// �������� � ��������� ����� 0
writeWEE(0x00,filestart); /// �������� � ������ 0  - 0

exf:; /// �����
cls();

}
///////////////////////////////////////////������� ���� ������ /////////////////////////////////////////////

void CLRMEMALL(void) /// �������� ������  -- �������������� �� ��������� ��������� �������� �����������
{
unsigned char i=0;

cls();
BEEP(2);


draw_wdataerase(); //// �������� ������ ����� ������� ���������� �� �� 0  ��� �� enter

while (!(key_find()==0)) /// ����� ���� �������� ��� ������ 
	{
	}
	_delay_ms (620);
	key_find();
	_delay_ms (32);

while (!(key_find()==keyzero)) /// ����� ������ 0  ��� ������ ��������
{

	if (key_find()==keyenter)   /// ���� enter �� ������ �������� � �����
	{ 

	//BEEP(1);
	goto exf;
	
	}

}

i=filetype();

FORMAT(i); /// ������ ������� � ��������������� ������ 

exf:; /// ����� ��� ��������������

cls();


}
*/


//////////////////////////////////// ������ � ������ i2c /////////////////////////////////////////////////

unsigned char readEE(unsigned int ADR) /// ��������� ���� �� ������ 750uS
{
unsigned char br=0;

	i2c_start();		// �����
	i2c_tx(eeWR);		// �������� + ����� ������
	i2c_tx(ADR>>8);		// ������� ���� ������
	i2c_tx(ADR);		// ����� ���� ������
	i2c_stop();			// ����

	//_delay_us(3); 

	i2c_start();		// �����
	i2c_tx(eeRD);		// �������� + ����� ������
	br=i2c_rx(0);		// ��������� ����
//	br=i2c_rx(1);		// ��������� ����
	i2c_stop();			// ����
	_delay_us(1); 
	
	return br;
}
// 
// unsigned long readWEE(unsigned int ADR) /// ��������� ����� //// ��������� � ������  byte/2 = word adr 3
// {
// unsigned long wr=0;
// unsigned char ba=0, bb=0, bc=0;
// 
// 	ADR = ADR*3;
// 
// 	i2c_start();		// �����
// 	i2c_tx(eeWR);		// �������� ������  1 �������� �� ��
// 	i2c_tx(ADR>>8);		// ������� ���� ������
// 	i2c_tx(ADR);		// ����� ���� ������
// 	i2c_stop();			// ����
// 
// 	//_delay_us(3); //
// 
// 	i2c_start();		// �����
// 	i2c_tx(eeRD);		// �������� ����� ������
// 	ba=i2c_rx(1);		// ��������� ����
// 	bb=i2c_rx(1);
// 	bc=i2c_rx(0);
// 	i2c_stop();			// ����
// 
// 	wr = ba; 
// 	wr= (wr<<8)+bb;
// 	wr= (wr<<8)+bc;
// 
// return wr;
// };

unsigned long readWEE(unsigned int ADR) /// ��������� ����� //// ��������� � ������  byte/2 = word adr 3
{
	unsigned long wr=0;
	unsigned char ba=0, bb=0, bc=0;

	ADR = ADR*3;

	i2c_start(); // �����
	i2c_tx(eeWR); // �������� ������  1 �������� �� ��
	i2c_tx(ADR>>8); /// ������� ���� ������
	i2c_tx(ADR);  /// ����� ���� ������
	i2c_stop();  /// ����

	_delay_us(3); //

	i2c_start(); /// �����
	i2c_tx(eeRD); /// �������� ����� ������
	ba=i2c_rx(1); /// ��������� ����
	bb=i2c_rx(1);
	bc=i2c_rx(0);
	i2c_stop(); // ����

	wr = ba;
	wr= (wr<<8)+bb;

	wr= (wr<<8)+bc;


	return wr;
}

void writeEE(unsigned int ADR, unsigned int val) //// ������ �����
{
i2c_start(); 
i2c_tx(eeWR);		// ����� ���������� + ������� ������

i2c_tx(ADR>>8);		// ����� � ������ ��� ������
i2c_tx(ADR);

//_delay_ms(5);		// �������� ��� ������ �������

//i2c_tx(val>>8);	// ������ �����
i2c_tx(val);		// ������ �����
i2c_stop();
//_delay_ms(1);		// �������� ��� ������ �������

};
//! Send a byte sequence on the I2C bus
void i2c_EXT_Send(unsigned int ADR, unsigned char length, unsigned char *data)
{
i2c_start();
i2c_tx(eeWR);		// ����� ���������� + ������� ������

i2c_tx(ADR>>8);		// ����� � ������ ��� ������
i2c_tx(ADR);

	// send the data
	while (length--)
	i2c_tx(*data++);

i2c_stop();

//	I2C_SDL_LO;					// clear data line and
//	I2C_STOP;					// send STOP transition
}

void writeWEE(unsigned int ADR,unsigned long val)///// �������� ����� /// ��������� � ������  byte/2 = word adr  3
{

	ADR = ADR*3;
	i2c_start();
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);

	i2c_tx(val>>16); /// ������ �����

	i2c_stop();
	_delay_ms(9);/// �������� ��� ������ �������

	////////////////////////////

	ADR = ADR+1;

	i2c_start();
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);

	i2c_tx(val>>8); /// ������ �����

	i2c_stop();
	_delay_ms(9);/// �������� ��� ������ �������



	ADR = ADR+1;

	i2c_start();
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);

	i2c_tx(val); /// ������ �����

	i2c_stop();
	_delay_ms(9);/// �������� ��� ������ �������
}

void writeWEE_old(unsigned int ADR, unsigned long val)///// �������� ����� /// ��������� � ������  byte/2 = word adr  3
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

i2c_tx(val>>16); /// ������ ����� 

USART_SEND_Byte(val>>16);

i2c_tx(val>>8); /// ������ �����

USART_SEND_Byte(val>>8);

i2c_tx(val); /// ������ �����

USART_SEND_Byte(val);
USART_SEND_Byte('|');

i2c_stop();
_delay_ms(9);/// �������� ��� ������ �������
}

/*
void writeWEE(unsigned char * str_save, unsigned int ADR, unsigned char delete,unsigned char dtps,unsigned char mdch)///// �������� ����� /// ��������� � ������  byte/2 = word adr  3
{
	unsigned char MD=0;

	ADR = ADR*entry_size;

	i2c_start();
	i2c_tx(eeWR);				// ����� ���������� + ������� ������
	i2c_tx(ADR>>8);				// ����� � ������ ��� ������
	i2c_tx(ADR);

	i2c_tx(str_save[0]); /// ������ ����� 

	i2c_stop();
	//_delay_ms(9);/// �������� ��� ������ �������

	////////////////////////////

	ADR = ADR+1;

	i2c_start(); 
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);

	i2c_tx(str_save[1]); /// ������ �����

	i2c_stop();
	//_delay_ms(9);/// �������� ��� ������ �������

	////////////////////////////

	ADR = ADR+1;

	i2c_start(); 
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);

	i2c_tx(str_save[2]); /// ������ �����

	i2c_stop();
	//_delay_ms(9);/// �������� ��� ������ �������
	////////////////////////////

	ADR = ADR+1;

	i2c_start();
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);

	i2c_tx(str_save[3]); /// ������ �����

	i2c_stop();	

	////////////////////////////

	ADR = ADR+1;

	i2c_start();
	i2c_tx(eeWR);
	i2c_tx(ADR>>8);
	i2c_tx(ADR);
	
	MD=mdch;										// ������� ������� = ����� ������
	if(dtps>>1) SetBit(MD,6); else ResetBit(MD,6);		// ��������� ���������� ����� 0-�������; 1-�����;
	if(delete) SetBit(MD,7); else ResetBit(MD,7);	// ������ �������
	
	i2c_tx(MD); /// ������ �����

	i2c_stop();
}
*/



void clraEE(void) /// �������� ��� ������
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
				
				i2c_tx(0); /// ������ ����� 0
				ADR++;
				
				}

		i2c_stop();
	
		_delay_ms(10);/// �������� ��� ������ �������
	
	}
	
_delay_ms(10);

}

unsigned char i2c_error_soft;                         //������  ����������� ����

//������������� ����������� ���� I2C
void i2c_init(void)
{
  I2C_DDR&=~(1<<SDA_LN);                              //���������� ����� SDA
  I2C_DDR&=~(1<<SCL_LN); 
														//� SCL � ����������������� ���������
  I2C_PORT|= _BV(1<<SDA_LN);                             //� �� ��� �������������� �� ���� ������� ����������
  I2C_PORT|= _BV(1<<SCL_LN);                             //������� �������
  i2c_error_soft=0;                                   //���������� ������ ��� :-)
}

//��������� ������� "�����"
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

//��������� ������� "����"
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

//������� �����
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


//����� �����, ���� last_byte=0, �� ��������� ��������� ���� � ������������� �� ������� �� �����
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

//���������� ������� ����� SDA
unsigned char in_sda(void)
{
  if(I2C_PIN&(1<<SDA_LN))
    return 1;
  else
    return 0;
}

//������������� ����� SDA �� ���� ��� �����
void sda_io(unsigned char io_c)
{
  if(io_c==IN_LN)
    I2C_DDR&=~(1<<SDA_LN);
  else
    I2C_DDR|=(1<<SDA_LN);
	
  _delay_us(idel);
}

//������������� ������� �� ����� SCL
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

//������������� ������� �� ����� SDA
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

///////////////////////////////////////////////// ��������� ��������� ������ ������� ////////////////////////

void RWN(void) //// ������ ������ ������� ����� RS232
{
unsigned char a[5],x=0;
//cls();
//show_wpos(34,6,14); //// ����� 
for (x = 0; x < 5; x++) /// �������� 5 ���� 
	{
		while (!(UCSR0A & (1<<RXC0)));
		
		a[x]=(UDR0-0x30);
	}
	
	if ((a[0]==0xF5) && (a[1]<=9) && (a[2]<=9) && (a[3]<=9) && (a[4]<=9)) /// ���� �������� ������
	{
	WR_SNUM(a[1],a[2],a[3],a[4]);  //// �������� �������� �����
	BEEP(4);
	SEND_ST(W_OK); /// ���������
	SNUMWR(0x00);
	
	CLRTR(); /// ��������� ���
	wrnar(0x00); //// ��������� ��������� !!!!!!!!!!!!!!!!!!!1
	
	goto exf;
	}
	
	
	if ((a[1]>9) && (a[2]>9) && (a[3]>9) && (a[4]>9) ) { SEND_ST(M03err);}/// -- ������������ ������ ������ (������ ���� ascii ������ �������)
	
	



	
exf:;
//cls();
}
/*
///////////////////////////  �������� ��������� ������ � ����� ������� ����� � ������ ///////////////////////
void SENDUFORG(void)
{
unsigned int tf=0,mp=0,i=0;


//tf=filetype();
tf=1;
LBS(tf);


				if (SEND_NUM[2]<10)  //// �������� ����� ������
				{
				USART_SEND_Byte(SEND_NUM[2]+0x30); 
				}
				
				if (SEND_NUM[1]<10)
				{
				USART_SEND_Byte(SEND_NUM[1]+0x30);
				}
				USART_SEND_Byte(SEND_NUM[0]+0x30);
				SCRCL();


	
	for (i = 0; i <= (tf-1); i++)    //// ���������� ��� ����� ������� ���� /// ��������� ������� ������
	{
	
	//mp=rfd_use(i,tf); /// ������ ����� ������� � ����� �����
	mp=20000; 
	LBS(mp); // �������� � ������ ��������
	
	
	
					//// �������� ������� -  ���� -- ����� ������
				
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
				SCRCL(); /// ������� �������
	
	
	}

SEND_ST(END_S);  ///����� �������� 


}*/
/*
//////////////////////// �������� ����� ����� UART /////////////////////////////////////////////
void SENDUFILE(void)
{
unsigned char a[3],x=0,fnum=0, tf=0, STSM=0;
unsigned int  maxlen=0, filestart=0, fileend=0, io=0, sendcont=0, sr=0, blockq=0; /// blq=0;
unsigned long val=0, is=0;
//cls();
//show_wpos(34,6,14); //// ����� 
tf=filetype();

 




for (x = 0; x < 3; x++) /// �������� 5 ���� 
	{
		while (!(UCSR0A & (1<<RXC0)));
		
		a[x]=(UDR0-0x30);
	}
	
	fnum =(a[1]*10)+a[2]; /// ����� �����
	
	if ((a[0]==0xF5) && (a[1]<=9) && (a[2]<=9) && (fnum<=tf)) /// ���� ������� ������ �� ���������� 
	{

			maxlen = (v1m30/tf); /// ����� ������������ ������ �����

	//blockq = maxlen/blockSIZE; // ����� ������ � ����� ��� ��������

			filestart= (fnum * maxlen) + memstart; ///����� ������ ����� (� �������) ����������  ��� ��������� � ������
	
			fileend = filestart+maxlen;  /// ����� ����� ����� 

			io=filestart; /// � ��������� ������� ����� ��� ���������
			
			sendcont=0;
			
			for (io = filestart; io < fileend; io++)  //// �������� �����
			{
				
				TIMSK3=0x00;
				TCNT3=0;
				
				
				
				
				
				val=readWEE(io); /// ��������� ������ �� ������
				
				
				
				
				

				STSM = val>>16;  //// ��������� ��������� ��� ������ ���� ��������� 
				val = val & 0x0000FFFF;

				if (STSM==0) {STSM = CMCLR;}
				
				USART_SEND_Byte(STSM);
				
			
			
				LBS(val); // �������� � ������ ��������
			
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
				SCRCL(); /// ������� �������
				
				sendcont++; /// ��������� �������
				if (sendcont==blockSIZE)
				
					{	
									//is=TOTRS(0);
									
						
									LBS(blockq+10); /// ������� ������  10.....59 ���������� 0-49
									
									USART_SEND_Byte('B');
									
									USART_SEND_Byte(SEND_NUM[1]+0x30);
							
									USART_SEND_Byte(SEND_NUM[0]+0x30);
									
									blockq++;
					
					
							SCRCL(); /// ������� �������
						
				sei();											////�������� ��������� ���������� !!!!!!!!!!!
						is=TOTRS(2); // �������� �������� ���� ���
						
						
						while (!(UCSR0A & (1<<RXC0)))
						
							{
							
										if (TOTRS(1)>0x01)
											{
												is=0;
												SEND_ST(BTOT); /// �������
												is=TOTRS(0);
												goto exf;
											}
							
							}
				cli();                                        ////��������� ��������� ���������� !!!!!!!!!!!
						
						sr=UDR0;
						is=TOTRS(0);
						
							if (sr=='z') /// ���� ������  ���������� �������� 
								{
								sendcont=0; 
								
								}
								else
								{
								SEND_ST(FF0err); //// ��� ������������ ����� ��  ���� �������� ������
								blockq=0;
								goto exf;
								}
					}
				
				
			}
			SEND_ST(END_S);  /// �������� �����
	
	}
	else
	{
		if ((a[1]>9) && (a[2]>9)) { SEND_ST(M03err); goto exf; }/// -- ������������ ������ ������ (������ ���� ascii ������ �������)
		
		if (tf < fnum) {SEND_ST(M01err);} //// -- ��� ������ �����
	
	}


exf:;

//cls();
is=TOTRS(0);

}*/
//////////////////////// �������� ��������� � UART /////  M00, M01, M02, M03, END, Ser_Num /////////////////
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


	if (i>=1)								//// �������� 
	{
	USART_SEND_Byte(a[3]);
	}
		USART_SEND_Byte(a[2]);
		USART_SEND_Byte(a[1]);
		USART_SEND_Byte(a[0]);

	SCRCL(); /// ������� �������
}
///////////////////////////////////////////////// �������� ������� ������� //////////

void SendUT(void)
{
	//LBS(Read_Disp());
	LBS(main_value);
 // �������� � ������ ��������
			
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
				SCRCL(); /// ������� �������
}

/////////////////////////////////////  �������� ���������� ///////////////////////////////////
void SEND_VOLT(unsigned int val)
{

				LBS(val); // �������� � ������ ��������
				
				if (SEND_NUM[2]<10)
				{
				USART_SEND_Byte(SEND_NUM[2]+0x30); 
				}
				
				if (SEND_NUM[1]<10)
				{
				USART_SEND_Byte(SEND_NUM[1]+0x30);
				}
				USART_SEND_Byte(SEND_NUM[0]+0x30);
				SCRCL(); /// ������� �������
}

//////////////////////// ������  ������ � �������� ��������� ///////////////////////////////////////////////
 
void wrnar(unsigned long nar)
{
eeprom_write_dword (TNAR,nar); ///������ ��������� � ������
}

unsigned long TNARAB(void)
{
unsigned long i=0;
i= eeprom_read_dword(TNAR); //// ������� ���������
return i;
}

void Send_NARU(void) /////  �������� ������� ��������� ����:������ � ��� ����
{
unsigned long  i=0;
unsigned long tmp_save=0;

//i=timerab(); /// �������� ������� ���������
	tmp_save=eeprom_read_word(TNAR); //// ������� ���������
	num2str_3_zeros(tmp_save,SEND_NUMX);

//i=timerab();
//LBSX(i); // �������� � ������ ��������
			
		
			
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
				SCRCL(); /// ������� �������
};



//////////////////////////////////// ������� ������� UART////////////////////////////////////////////////////
void SCRCL(void)
{
USART_SEND_Byte(CR);
USART_SEND_Byte(LF);
}




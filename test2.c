/*
 * test2.c
 *
 * Created: 23.08.2013 10:31:49
 *  Author: Programmer1
 */ 


#include <avr/io.h>
#include <avr/pgmspace.h>								// ������� ��� ���������� �������� � ������ ��������
#include <avr/eeprom.h>									// ������� ��� ������ � �������
#include <avr/interrupt.h>								// ������� ��� ��������� ����������
#include <util/delay.h>

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"

#include "MEM.h"
#include "config.h"
//#include "menu_txt.h"
//#include "measuring.h"
#include "bigfont.h"
#include "picture.h"
#include "font.h"
#include "logo.h"

//________________________ ���������� ���������� ____________________________
//volatile unsigned char* fnt1=&big_font_16;

volatile unsigned char ch;								// ��� ������� ������
volatile unsigned char keypressed_short=false;			// ���� ��������� ������� ������
volatile unsigned char keypressed_long=false;			// ���� ������� ������� ������
volatile unsigned char key_released=false;				// ���� ���������� ������
volatile unsigned char butt_new=0;						// ����� �������� ����� ����������
volatile unsigned char butt_old=0;						// ���������� �������� ����� ����������
volatile unsigned char pwr_old=0;						// ���������� �������� ������ power
volatile unsigned int  pwr_new=0;						// ����� �������� ������ power
volatile unsigned int  key_time_pwr=0;					// ������� ��������� ������� ������� (0 ����� ��� ������� ���������)
volatile unsigned long key_time=5;						// ������� �������� ��������� �������

volatile unsigned int  key_inc=1;						// ��������� ���������� �������� ��� ��������
//volatile unsigned long	 key_time_pwr=0;			// ������� �������� ��������� �������
volatile unsigned char test_flag=false;					// ����
volatile unsigned char screen_refresh=false;			// ���� ���������� ����
volatile unsigned char batt_refresh=true;				// ���� ���������� �������
volatile unsigned char batt_percent=1;					// ������� ������� ������� (� ������� ��������)
volatile unsigned char batt_max=0;						// �������� ������� ������� (� ������� ��������)
volatile unsigned char batt_min=0xFF;					// ������� ������� ������� (� ������� ��������)
volatile unsigned char posss=3;
//volatile unsigned char big_dot_pos=1;					// ������� ����� � ������� ������ (�������� ��������)
volatile unsigned char dot_pos=1;						// ������� ����� � ������� ������ (����� ��������)

volatile unsigned char entry_refresh=false;				// ���� ���������� ������ �� �������� �������

//volatile unsigned char no_sound_flag=true;			// ���� ����������� no_sound
volatile unsigned char chpush=0;

//volatile unsigned char time[6]={0x00,0x00,0x00,0x00,0x00,0x00};	// ����: H:M:S:DD:MM:YY
//volatile unsigned int temperature=0;					// �������� ����������� 16 bit
//volatile unsigned char MD_sample=0;						// ����� ������ ��� ������� ����������� ��������� sample

volatile unsigned char i2c_error_soft;                  // ������  ����������� ����

unsigned long readwordeeprom=0;
volatile unsigned char menu_level_choice=1;						// ��������� ������� ����

unsigned int  ee_page_numb=page_numb_min;				// ����� �������� ������� ��� �����������
unsigned long ee_page_size=0;							// ���������� ������� �� �������� ��� �����������
unsigned long numb_deleted_entry=0;						// ���������� ��������� ������� �� ��������
unsigned int  page_choice=0; 
unsigned long entry_choice=0;							// ����� ��� ��������� �������, �� 0 �� ee_page_size
unsigned char clear_journal=0;							// dlg_12 �������� ������?
unsigned char clear_entry=0;							// dlg_13 ������� ������?

unsigned char ee_mode_choice=0;							// ����� �������� ������� = ����� ������ T1
unsigned char service_choice=1;							// ����� �������������� �������
unsigned char dialogues_choice=1;						// ����� ������� 
unsigned char messages_choice=1;						// ����� ��������� 
unsigned char show_main_value=true;						// ���������� �������� ��������
unsigned char ee_pep_numb=0;							// ����� ���������� ������� ��� (��� �����������)

unsigned char settings_choice=0;						// ��������� ������� ���� ���������
unsigned char ee_brightness_choice=0;					// ��������� ��������� ������� ������
unsigned char ee_sound_choice=1;						// ��������� ��������� ����� 
unsigned char ee_gain_choice=25;						// ��������� ��������� ��������
unsigned char ee_gain_min=10;							// ����������� �������� ��������
unsigned char ee_gain_max=40;							// ������������ �������� ��������
unsigned char ee_minutes_off=ee_minutes_off_min;		// ����� �� ��������������
unsigned char time2off=0;
unsigned char reset_choice=0;							// ����� �������� �� ���������
unsigned char back_color=back_color_const;

unsigned char calibration_choice=0;						// ��������� ������� ���� ����������

unsigned long ee_thickness_choice=lowlim;				// ��������� ������� ����������
unsigned int  ee_thickness_min=lowlim;					// ����������� �������� ������� 
unsigned long ee_thickness_max=uplim;					// ������������ �������� �������
 
unsigned int  ee_velocity_choice=5234;					// ������� �������� ��������
unsigned int  ee_velocity_min=100;						// ������� ��������
unsigned int  ee_velocity_max=9999;						// �������� ��������

unsigned int  ee_grade_min=lowlim;						// ������� ��� �������� �����������
unsigned long ee_grade_max=uplim;						// �������� ��� �������� �����������
  signed long ee_grade_lowlim_choice=lowlim;			// ��������� ������ ������ ��� �����������
unsigned long ee_grade_uplim_choice=uplim;				// ��������� ������� ������ ��� �����������

  signed int  ee_nonius_min=0;							// ����������� �������� ��������: 0-500 �������������
  signed int  ee_nonius_choice=nonius_half_range;		// ������� �������� �������� (�������� ������������) ��������!!!
  signed int  ee_nonius_max=1000;						// ������������ �������� ��������

unsigned int  ee_base_level_min=0;						// ����������� �������� �������� ������ 0
unsigned long ee_base_level_choice=lowlim;				// ��������� ������� �������
unsigned long ee_base_level_max=uplim;					// ������������ �������� �������� ������

volatile unsigned char *str_show[8];					// ������ ��� ����������� �����
volatile unsigned char *str_show4[4];					// ������ ��� ����������� �����
//volatile unsigned char *str_clear[4]={" "," "," "," ",};// ������ ��� ����������� �����
//volatile unsigned char jrn_buf[journal_buf];			// ����� �������� ��� �������
#define scroll_page_mode_pos 10
volatile  char msg_line_clear[scr_col] = {"                               "};
volatile  char msg_line_entry[scr_col] = {"[000] 000                      "};
volatile  char msg_line_value[scr_col] = {"000.0 ��                       "};
volatile  char msg_line[scr_col*scr_raw]={"                                                                                                                            "};
//volatile unsigned char msg_line[scr_col*scr_raw]={"[001] 000                      [002] 000                      [003] 000                      [004] 000                      "};			//[�31]
 char mode_name[modes_numb+3]={"�����   "};			// �������� ������� ��� ����������� � scroll_page(); * - ����� ��� ������ �� �������
 char mode_name_eng[8]={"ISRDN   "};		// �������� ������� ��� �������� � PC



unsigned long zav_num=0x30303030;

unsigned int calobr_num[pep_numb]={calobr3mm,calobr3mm,calobr3mm,calobr3mm,calobr3mm,calobr3mm,calobr5mm,calobr20mm,calobr20mm};
unsigned int vel_calib [pep_numb]={vel3mm,   vel3mm,   vel3mm,   vel3mm,   vel3mm,   vel3mm,   vel5mm,   vel20mm,   vel20mm};
	
volatile unsigned int main_value=0;						// �������� �������� ��� ����������� long
volatile unsigned char USB_connect=false;				// USB ����������, ��� 

unsigned char read_byte=0;

// typedef struct eext_data_format
// {
// 	unsigned long data;
// 	unsigned char status, H,M,S,DD,MM,YY,T1,T0;
// }; 
//eext_data_format eext_pages_addr [1000];				// ������ ���������� �� ������ �������

// static volatile unsigned long ccc =0;					// ��������
// static volatile unsigned long ccc1=1;					// ��������
// static volatile unsigned long ccc2=2;					// ��������

static unsigned long ulIdleCycleCount = 0UL;

/* ���������� �������� � ���������� ����������*/
volatile xSemaphoreHandle xMutex;

//xSemaphoreHandle xDisplay;							// ������� ��� ������ �� �����
///////////////////////////////////////////////////////////////

	volatile unsigned long TRAB=0, tmpt=0;///  ���������1
	volatile unsigned char TKOFF=0, CLASSMODE=0;
	
	volatile unsigned int RAZBH,RAZBL, DIFFU, NONIUSU, extdisp; /// ������ �����������, ������� ���� ���, ������� ������ ������.1
	volatile unsigned int calibr=3177;//1336;
	volatile unsigned char DIFFP,NONIUSP;				/// ������ ���� ������, ���������� ������.1
	extern nastr=0;				// ������� ����� ���������, ����������� � eeprom 
    volatile unsigned char voltp=0;
	volatile unsigned char amplif =25;	//0
	volatile unsigned short vel =6048;	//0
	volatile unsigned char datch =2;	//0
	volatile unsigned char mode =0;	//0
	volatile unsigned int  voltsb=0;
	volatile unsigned char RXBI=0;						// �����1
	volatile unsigned char TOFFVAL=0;					// ������� 5����� ��� ����������1
	volatile static unsigned int icctx=0,ictrab=0;		// ������ �������������� � ��������� ��������� �������� ������
	volatile static unsigned char brt =0,tmpbat=0,ccx=0;
	//volatile char buf[32]; // �����
	//volatile int bufsize = 0; // ����� ������
	//volatile char ready = 0; // �������� �� ������?
	volatile unsigned char RXIUART=0, timeoutRS=0;
////////////////////////////////////////////////////////////////
static unsigned long CV=0;
//static unsigned int adcont;
volatile  signed int io=0,lp=0;
unsigned int inct =0, ioa=0;
unsigned char memst=0;
unsigned long timek;
signed int  levd=0;
unsigned char ii=0;
unsigned char ik=0, kkk=0, i=0;		/// ������� ����;
unsigned char ixc=0, ssc=0;			/// ��������� ������ ������������
unsigned int mti=0,mri=0,mdi=0,mni=0,msi=0,memory=0;
unsigned char mf=5,tf=0,iv=0, id=0; /// ����� �����
unsigned int mp=300;				/// ���������� ��������� ����� � �����
unsigned long im=0, VA=0,VB=0, SA=0, SB=0;
signed long it,mvs=0;

///////////////////////////////////////////////////////////////
unsigned int get_page_size(unsigned int);					 // ���������� ����� �� ���������� (contents) ������� ��� �������� � ������� cscl
unsigned int get_addr(unsigned int);
void send_journal(void);

//________________________ ������ cnt - ������� �������� ������ ________________________
void BEEP(unsigned char cnt)
{
	if (ee_sound_choice<1)
	{
		PORTE &= ~_BV(BEEPM0); 				// 0
		PORTE &= ~_BV(BEEPM1);				// 0
		PORTE |= _BV(BEEPX);				// 1
		PORTE &= ~_BV(BEEPX);				// 0
	};
};
void butt_scan(void)
{
                        chpush=key_find();

                        if(chpush >0 && butt_old ==0){key_time=0;keypressed_short=true;}
                        else
                        if ((chpush >0 && butt_old >0))
                        {
	                        key_time++;
	                        if (key_time>key_repeat){keypressed_long=true;}
                        }
                        else
                        if(chpush==0 && butt_old >0)
                        {
	                        key_time=0;
	                        key_released=true;              // ?????? ????????!
	                        //keypressed_short=false;
	                        //keypressed_long=false;
                        }
                        butt_old=chpush;
}
///----------------------------------------Show KONTAKT----------
void show_acont(unsigned char num)
{

//	unsigned char i;
	if(num == 0)
	{
		PORTH &= ~_BV(acontpin); // 0 ����� �� ����
		
//		place_in_ram(0, 15, 3, 13);
//		send_command(0x5C);//Write RAM Command (5Ch)
		show_acoustic(clear_color);

	}
	else
	{
		
		PORTH |= _BV(acontpin); // 1 ����� �� ����
		
//		place_in_ram(0, 15, 3, 13);
//		send_command(0x5C);//Write RAM Command (5Ch)
		

		show_acoustic(front_color);                    
        time2off=0;					// ���������� ������� ��������������
		
		////BEEP(2);
	}
	
};

void DDS_CLK()  /// Clock
{
	PORTC |= _BV(SCLK);
	PORTC &= ~_BV(SCLK);
};
void DDS_SD(unsigned char tbb)  //// �������� ����� LSB ������� MSB ���������
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
};
//////////////////////////////�������� � ���
void DAC_CLK(void)  /// Clock
{
	PORTF |= _BV(SCLDAC);
	PORTF &= ~_BV(SCLDAC);
};

void DAC_SD(unsigned char tbb)  //// �������� ����� MSB ������� LSB ���������
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
};

void RPM(void)/// ������ ���������� �� ������
{

	PORTH &= ~_BV(razbr_alrm);///  0 �� ����� ����������� ����
	
	nastr=eeprom_read_byte(NASTR);
	//nastr=settings_choice;
	switch (nastr)
	{
		case 0: vel = eeprom_read_word(VEL1); amplif= eeprom_read_byte(AMP1);	datch= eeprom_read_byte(DATCH1);	mode= eeprom_read_byte(MODE1);	calibr = eeprom_read_dword(CALB1);	break;
		case 1: vel = eeprom_read_word(VEL2); amplif= eeprom_read_byte(AMP2);	datch= eeprom_read_byte(DATCH2);	mode= eeprom_read_byte(MODE2);	calibr = eeprom_read_dword(CALB2);	break;
		case 2: vel = eeprom_read_word(VEL3); amplif= eeprom_read_byte(AMP3);	datch= eeprom_read_byte(DATCH3);	mode= eeprom_read_byte(MODE3);	calibr = eeprom_read_dword(CALB3);	break;
		case 3: vel = eeprom_read_word(VEL4); amplif= eeprom_read_byte(AMP4);	datch= eeprom_read_byte(DATCH4);	mode= eeprom_read_byte(MODE4);	calibr = eeprom_read_dword(CALB4);	break;
		case 4: vel = eeprom_read_word(VEL5); amplif= eeprom_read_byte(AMP5);	datch= eeprom_read_byte(DATCH5);	mode= eeprom_read_byte(MODE5);	calibr = eeprom_read_dword(CALB5);	break;
		case 5: vel = eeprom_read_word(VEL6); amplif= eeprom_read_byte(AMP6);	datch= eeprom_read_byte(DATCH6);	mode= eeprom_read_byte(MODE6);	calibr = eeprom_read_dword(CALB6);	break;
		case 6: vel = eeprom_read_word(VEL7); amplif= eeprom_read_byte(AMP7);	datch= eeprom_read_byte(DATCH7);	mode= eeprom_read_byte(MODE7);	calibr = eeprom_read_dword(CALB7);	break;
		case 7: vel = eeprom_read_word(VEL8); amplif= eeprom_read_byte(AMP8);	datch= eeprom_read_byte(DATCH8);	mode= eeprom_read_byte(MODE8);	calibr = eeprom_read_dword(CALB8);	break;
		case 8: vel = eeprom_read_word(VEL9); amplif= eeprom_read_byte(AMP9);	datch= eeprom_read_byte(DATCH9);	mode= eeprom_read_byte(MODE9);	calibr = eeprom_read_dword(CALB9);	break;
		case 9: vel = eeprom_read_word(VEL10);amplif= eeprom_read_byte(AMP10);	datch= eeprom_read_byte(DATCH10);	mode= eeprom_read_byte(MODE10);	calibr = eeprom_read_dword(CALB10);	break;
		//calibr = eeprom_read_dword(CALIBD);
	};
	
	ee_velocity_choice=vel;
	ee_gain_choice=amplif;
	settings_choice=nastr;
	ee_pep_numb=datch;	
	ee_mode_choice=mode;
	ee_sound_choice=eeprom_read_byte (BEEP_MODE);
	ee_brightness_choice=eeprom_read_byte (BRIGHT);
	ee_minutes_off= eeprom_read_byte (MINUTES_OFF);				//  �����, ��������������
	ee_nonius_choice=eeprom_read_word(NONIUSU1 + nastr*2);
	ee_base_level_choice=eeprom_read_word(DIFFU1 + nastr*2);
	ee_grade_uplim_choice=eeprom_read_word(RAZB_H1 + nastr*2);
	ee_grade_lowlim_choice=eeprom_read_word(RAZB_L1 + nastr*2);
	ee_page_numb=eeprom_read_word(MEMPNT);						// ������ ����� ������� �������� �������
	ee_page_size=eeprom_read_dword(get_page_size(ee_page_numb));
};

//////////
void RPR(void)//// ��������� ��� �������
{

	PORTH &= ~_BV(razbr_alrm);///  0 �� ����� ����������� ����
	GET_MESINT(0,1);
	switch (mode) ///�������� ���������� ��� ������� ������
	{
		case 0: GET_MESINT(0,1);	break;
		case 1: FAST_GET_MESINT(0,1);	SKANIROV (mode,	vel,datch,nastr,amplif,voltp,calibr,1,0,0,0); break;
		case 2: GET_MESINT(0,1);	NONIUSU = eeprom_read_word(((nastr *2))+(NONIUSU1)) ; NONIUSP = eeprom_read_byte((nastr)+(NONIUSP1)) ; break; /// ����� ������
		case 3: GET_MESINT(0,1);	DIFFU = eeprom_read_word(((nastr *2))+(DIFFU1));  DIFFP = eeprom_read_byte((nastr)+(DIFFP1)) ; break; /// ����� ����
		case 4: GET_MESINT(0,1);	RAZBH = eeprom_read_word(((nastr *4))+(RAZB_H1)) ; RAZBL = eeprom_read_word(((nastr *4))+(RAZB_L1)); break; /// ����� ����������� ����  ���� �������
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////
//___________________________ ����� ������� � OLED ������� _________________________
void send_command(unsigned char com)
{
	PORTJ &= 0x3F;						// SDC = 0
	PORTG |= 0x04;						// WR = 1
	PORTA = com;						// ���������� ���� �� ���� ������
	PORTG &= 0xFB;						// WR = 0 ������� �����
};
//___________________________ ����� ������ � OLED ������� __________________________
void send_data(unsigned char data)
{
	PORTJ |= 0x40;						// SDC = 1;
	PORTG |= 0x04;						// WR = 1
	PORTA = data;						// ���������� ���� �� ���� ������
	PORTG &= 0xFB;						// WR = 0
};
//____________________________ ������� ����� ������� _________________________________
void cls(void)
{
	unsigned int i;
//taskENTER_CRITICAL();
	place_in_ram(28,0,28+63,63);						// �������� ������� 4 ������� ����� RAM. 4*64=256 �����* 64 ������ /2=8192 �����
	send_command(0x5C);									// Write RAM Command (5Ch)
	for(i = 0; i < 8192; i++)
	{
		if(i%4==0) PORTJ |= 0x40;					// SDC = 1; ����� ��� ������������ �� ��������� ������ RAM �������� 4 �����
		PORTG |= 0x04;								// WR = 1
		PORTA = 0x00;								// ���������� ���� �� ���� ������ 0x00
		PORTG &= 0xFB;								// WR = 0
	}
	//screen_refresh=true;					// ��������� �����
//taskEXIT_CRITICAL();
};
//________________________ ������������� OLED ������� �������_______________________
void OLED_on(void)
{	// ����� OLED ������� 256 x 64 ����� 4 ��� ����� (�����). ���������� ������� - SSD1322
	
	unsigned char data=0;
	
	PORTJ &= 0x1F;						// RST = 0
	PORTJ |= 0x20;//RST = 1

	send_command(0xFD);					// Command Lock
	send_data(0x12);
	send_command(0xAE);					// Set Display ON/OFF (AFh/AEh)
	
	//	send_command(0xB3);				// Set Front Clock Divider / Oscillator Frequency (B3h)
	//	send_data(0x91);				// 0x91   �� �������!

	send_command(0xCA);					// Set Multiplex Ratio (CAh)  !!!!!!!!! ���� �������
	send_data(0x3F);					// 0x3F 0x40

	send_command(0xA2);					// Set Display Offset (A2h)
	send_data(0x00);
	send_command(0xA1);					// Set Display Start Line (A1h)
	send_data(0x00);
										// ��� ���������� ������ A[4]=1; A[1]=0; � ������ �������: A[4]=0; A[1]=1;
#ifdef   maket_build //rotate_screen
	SetBit(data,1);						// Enable Column Address Re-map (���������� ��������� ����� �����-�������)
#else
	SetBit(data,4);						// (�������� ������ ����)
#endif

	SetBit(data,2);						// Enable Nibble Re-map (������ ������� ������ ������)
	//SetBit(data,5);					// Enable COM Split Odd Even
	
	send_command(0xA0);					// Set Re-map & Dual COM Line Mode (A0h) ��� !!!!!!!!!!
	send_data(data);					// 0x06    2b (0x02) - ����� ����� �� ����� A5 - ������������� ���������
	send_data(0x11);					// 0x11   B4 - ������ �����������, ��� ���� ������������� ����������
	
	send_command(0xB5);					// Set GPIO
	send_data(0x00);
	send_command(0xAB);					// Set Function selection (ABh)
	send_data(0x01);					// A[0]=1b, Enable internal VDD regulator [reset]
	
	send_command(0xB4);					// Enable External VSL
	send_data(0xA0);
	send_data(0xFD);
	//BRIVAL(); ///
	send_command(0xC1);					// Set Contrast Current (C1h) 9F
	send_data(0x00);					// 256 steps for ISEG current [reset = 7Fh] 0xff
	send_command(0xC7);					// Master Contrast Current Control (C7h)
	send_data(0x0F);					// !0x0F
	
	send_command(0x00);					// Enable GrayScale table
	//	send_command(0xB8);
	//		for (i=0;i<180;i=i+12){send_data(i);} //15 data bytes define Gray Scale
	//	send_command(0xB9);				// Select Default Linear Gray Scale Table (B9h)

	
	//	send_command(0xB1);				// Set Phase Length (B1h)
	//		send_data(0xB1);
	
	//	send_command(0xD1);				// Enhance Driving Scheme Capability
	//		send_data(0xA2);			// 0x82
	//		send_data(0x20);

	send_command(0xBB);					// Set Pre-charge voltage (BB)1F
	send_data(0x05);					// 0x1F
	
	send_command(0xA9);
	//	send_command(0xB6);				// Set Second Pre-charge Period
	//		send_data(0x08);			// 1000b 8 dclks [reset]

	send_command(0xBE);					// Set V_COMH (BE) 07
	send_data(0x07);
	send_command(0xA6);					// Display Mode Normal - ���� ������� ������
	//	send_command(0xA5);				// Entire Display ON - ���� ������� �������
	//send_command(0xA7);				// A7h = Inverse Display
	//cls();
	send_command(0xAF);					// Set Display ON/OFF (AFh/AEh)
	
	//cfgr_load(25,2);

	if(ee_brightness_choice>0)
	{send_command(0xA7);				// A7h = Inverse Display OLED
	}else
	{send_command(0xA6);				// Normal Display OLED
	}

};
//////////////
void CLRTR(void) /// ��������� ���������
{
	//TRAB=0x00;
		eeprom_write_dword(TNAR,0); // �������� ���������
};

///////////
unsigned char SNUMWR(unsigned char i)  //// ���������� ������ ��� ������
{
	static unsigned char m=0;
	
	if (i==2) {return m;}
	m=i;
	return m;
};

//________________ ������ � ������ OLED ������ ������� ������ �� �����__________________
void place_in_ram(unsigned char x0, unsigned char  y0, unsigned char  x1, unsigned char  y1)
{
	send_command(0x15);									// ������� ������
	send_data(x0);
	send_data(x1);										//Set Column Address (15h) ������� x

	send_command(0x75);
	send_data(y0);
	send_data(y1);										//Set Row Address (75h) ������ y
};

//______________________ ������ �������� �� ���� ����� 256 x 64 x 4bpp_____________________
void Draw_picture(const unsigned char* mass)
{  
	unsigned int 	i=0;

	place_in_ram(28,0,28+63,63);						// �������� ������� 4 ������� ����� RAM. 4*64=256 ����� * 64 ������ /2=8192 �����
	send_command(0x5C);									// Write RAM Command (5Ch)
	for(i = 0; i < 8192; i++)							// �� ���� ������� 2 �������: � ������� � ������� �������, 4 ���� �� ���� �����
	{
		if(i%4==0) PORTJ |= 0x40;						// SDC = 1; ����� ��� ������������ �� ��������� ������ RAM �������� 4 �����
		PORTG |= 0x04;									// WR = 1
		PORTA =  pgm_read_byte_far(&mass[i]);			// ���������� ���� �� ���� ������
		PORTG &= 0xFB;									// WR = 0
	}
}

//_________________________ ������ ���������� 16 x 32 x 4bpp______________________________

void Draw_picture_32(const unsigned char* mass)
{
	unsigned int 	i=0;

	place_in_ram(28,0,28+4-1,32-1);						// �������� ������� 4 ������� ����� RAM. 4*4=16 ����� * 32 ������ /2=256 ����
	send_command(0x5C);									// Write RAM Command (5Ch)
	for(i = 0; i < 256; i++)							// �� ���� ������� 2 �������: � ������� � ������� �������, 4 ���� �� ���� �����
	{
		if(i%4==0) PORTJ |= 0x40;						// SDC = 1; ����� ��� ������������ �� ��������� ������ RAM �������� 4 �����
		PORTG |= 0x04;									// WR = 1
		PORTA = pgm_read_byte_far(&mass[i]);			// ���������� ���� �� ���� ������
		PORTG &= 0xFB;									// WR = 0
	}
};
//_________ ������ ����.������� �� ������ �������� as �� bs; ����� ������� ���� �� ������� xm,ym; ������ �� color(0x00-0x0F)______________

void Draw_symbol(const unsigned char* mass,unsigned char xm,unsigned char ym,unsigned char as,unsigned char bs,unsigned char color)
{  // ������� �� ������ ������� � ������� ��������� 32 � 4������

	unsigned char  screen_byte;
	unsigned int 	i=0, gg;

	place_in_ram(28+xm*(as>>2), ym*16, 28+xm*(as>>2)+(as/4)-1 , ym*16+bs-1);		
	
	send_command(0x5C);										// Write RAM Command (5Ch)
	gg=as*bs/2;												// ����� ����������� ���� �� �����
	for(i = 0; i < gg; i++)									// �� ��� ������� 2 �������: � ������� � ������� �������, 4 ���� �� �����
	{
		//if(as==16) screen_byte=pgm_read_byte_far(&mass[i]);//far mass
		//else 
		screen_byte=pgm_read_byte_near(&mass[i]);//near
		if(color<16)
		{
			if ((screen_byte & 0x0F) > color)screen_byte-=color; else screen_byte&=0xF0;	// �������� ����
			if (screen_byte>>4 > 0) screen_byte-=color<<4;else screen_byte&=0x0F;			// �������� ����
		}else
		{
			screen_byte=0xff-screen_byte;		
		}
		if(i%4==0) PORTJ |= 0x40;							// SDC = 1; ����� ��� ������������ �� ��������� ������ RAM �������� 4 �����
		PORTG |= 0x04;										// WR = 1
		PORTA = screen_byte;								// ���������� ���� �� ���� ������
		PORTG &= 0xFB;										// WR = 0
	}
}
//___________ ������ �������� � ������ � ������� xm,ym, ���������� ���� nm, ������ ���� hm �����, ���� ���� cm, ����� fnt_________________
void Draw_small_num (unsigned char nm,unsigned char shift, char* str,unsigned char xm,unsigned char ym, const unsigned char* fnt, unsigned char hm, unsigned char color)//unsigned
{
	unsigned int i;
	unsigned char chr;
	
	for(i = 0; i < nm; i++)
	{
		chr=str[i]-32;
		if(shift<nm && i==shift)
		{
			Draw_symbol(&fnt[(chr+146)*64],xm+i,ym,hm,hm*2,color);
		}else
			Draw_symbol(&fnt[chr*64],xm+i,ym,hm,hm*2,color);		// ���� ������� ��� ������ 16x32  chr*128 !!!!!!!!!!!!!
	}
}
//___________ ������ ������ � ������� xm,ym, ���������� ���� nm, ������ ���� hm �����, ���� ���� cm, ����� fnt_________________
void Draw_string_left (unsigned char nm, char* str,unsigned char xm,unsigned char ym, const unsigned char* fnt, unsigned char hm, unsigned char color)//const unsigned
{
	unsigned int i;
	unsigned char chr;
	
	for(i = 0; i < nm; i++)
	{//pgm_read_byte_far(&mass[i]);
		//chr=(unsigned char)str[i];
		chr=pgm_read_byte(&str[i]);							//pgm_read_byte_far
		if(chr<128) chr=chr-32;								// str[]-32 - �������� ������ �������� ��� ���������� ����
		else {
			if(chr>175)	chr=chr-96;							// ��� ������� ����
			else
			chr=chr-96-17;
		}
		Draw_symbol ( &fnt[chr*64]   ,xm+i,ym,  hm,hm*2,color );		// ���� ������� ��� ������ 16x32  chr*128 !!!!!!!!!!!!!
	}
}
//___________ ������ ������ �������� � ������ � ������� xm,ym, ���������� ���� nm, ������ ���� hm �����, ���� ���� cm, ����� fnt_________________
void Draw_string (unsigned char nm,unsigned char shift,  char* str,unsigned char xm,unsigned char ym, const unsigned char* fnt, unsigned char hm, unsigned char color)//const unsigned
{
	unsigned int i,im=0;
	unsigned char chr,isdot=false;
//	unsigned char sh=1;
	for(i = nm; i >0 ; i--)												// ������ ������ �������� � ������
	{
		chr=(unsigned char)str[i-1];
		if (chr==46) {isdot=true;}
		else	
		{
		  if(isdot){chr=chr+114;isdot=false;shift=0;}
		  else
			if(chr<128) chr=chr-32;										// str[]-32 - �������� ������ �������� ��� ���������� ����
			else {
					if(chr>175)	chr=chr-96;	else chr=chr-96-17;			// ��� ������� ����
				 }
		  Draw_symbol(&fnt[chr*64] ,xm+nm-im-shift-1,ym,  hm,hm*2,color);		// ���� ������� ��� ������ 16x32  chr*256 !!!!!!!!!!!!!
		  im+=1;
		}
	}
}
//______ ������ ������� ����� �������� � ������ � ������� xm,ym, ���������� ���� nm, ������ ���� hm �����, ���� ���� cm, ����� fnt_________________
void Draw_big_num (unsigned char nm,unsigned char shift, const unsigned char* str,unsigned char xm,unsigned char ym, const unsigned char* fnt, unsigned char hm, unsigned char color)
{
	unsigned int i;//,im=0;
	unsigned char chr;
	
	for(i=0; i<nm ; i++)										 		// ������ ������ �������� � ������
	{
		chr=(unsigned char)str[i];

		if(shift<nm && i==shift)
		{
			Draw_symbol(big_font_rus+(chr-48+66)*256,xm+i,ym,hm,hm*2,color);
		}
		else
		if(chr<128)														// ��� ���������� ��������
		{
			chr=chr-32;
			Draw_symbol(big_font_16+chr*256,xm+i,ym,hm,hm*2,color);
		}else															// ��� ������� ��������� � ���� � ������
		{
			if(chr>175) chr=chr-192; else chr=chr-192-17;
			Draw_symbol(big_font_rus+chr*256,xm+i,ym,hm,hm*2,color);//shift
		};

	}
}

//______ ������ ������� ����� �������� � ������ � ������� xm,ym, ���������� ���� nm, ������ ���� hm �����, ���� ���� cm, ����� fnt_________________
void Draw_big_font (unsigned char nm,unsigned char shift, const unsigned char* str,unsigned char xm,unsigned char ym, const unsigned char* fnt, unsigned char hm, unsigned char color)
{
	unsigned int i;//im=0;
	unsigned char chr,isdot=false;
/*	
	if(shift<nm)
		if(main_value<10000){ shift=1;}
		else 
		{shift=2;
			//main_value/=10;
		}*/
		
	for(i=0; i<nm ; i++)												
	{
		chr=(unsigned char)str[i];
		
		if(shift<nm && i==shift)
		{
			
			Draw_symbol(big_font_rus+(chr-48+66)*256,xm+i,ym,hm,hm*2,color);
		}
		else
		if(chr<128)														// ��� ���������� ��������
		{	
			chr=chr-32;
			Draw_symbol(big_font_16+chr*256,xm+i,ym,hm,hm*2,color);			
		}else															// ��� ������� ��������� � ���� � ������
		{ 
			if(chr>175) chr=chr-192; else chr=chr-192-17;
			Draw_symbol(big_font_rus+chr*256,xm+i,ym,hm,hm*2,color);//shift
		};			
		
		
	}
};
void Draw_symbol_align(const unsigned char* mass,unsigned char xm,unsigned char ym,unsigned char as,unsigned char bs,unsigned char align,unsigned char color)
{  // ������� �� ������ ������� � ������� ��������� 32 � 4������

	unsigned char  screen_byte;
	unsigned int 	i=0, gg;

	place_in_ram(28+xm*(as>>2)+align, ym*16, 28+xm*(as>>2)+(as/4)-1 +align, ym*16+bs-1);
	
	send_command(0x5C);										// Write RAM Command (5Ch)
	gg=as*bs/2;												// ����� ����������� ���� �� �����
	for(i = 0; i < gg; i++)									// �� ��� ������� 2 �������: � ������� � ������� �������, 4 ���� �� �����
	{
		//if(as==16) screen_byte=pgm_read_byte_far(&mass[i]);//far mass
		//else
		screen_byte=pgm_read_byte_near(&mass[i]);//near
		if(color<16)
		{
			if ((screen_byte & 0x0F) > color)screen_byte-=color; else screen_byte&=0xF0;	// �������� ����
			if (screen_byte>>4 > 0) screen_byte-=color<<4;else screen_byte&=0x0F;			// �������� ����
		}else
		{
			screen_byte=0xff-screen_byte;
		}
		if(i%4==0) PORTJ |= 0x40;							// SDC = 1; ����� ��� ������������ �� ��������� ������ RAM �������� 4 �����
		PORTG |= 0x04;										// WR = 1
		PORTA = screen_byte;								// ���������� ���� �� ���� ������
		PORTG &= 0xFB;										// WR = 0
	}
}
//______ ������ ������� ����� �������� � ������ � ������� xm,ym, ���������� ���� nm, ������ ���� hm �����, ���� ���� cm, ����� fnt_________________
void Draw_big_font_align (unsigned char nm,unsigned char shift, const unsigned char* str,unsigned char xm,unsigned char ym, const unsigned char* fnt, unsigned char hm, unsigned char align,unsigned char color)
{
	unsigned int i;//im=0;
	unsigned char chr,isdot=false;
/*	
	if(shift<nm)
		if(main_value<10000){ shift=1;}
		else 
		{shift=2;
			//main_value/=10;
		}*/
		
	for(i=0; i<nm ; i++)												
	{
		chr=(unsigned char)str[i];
		
		if(shift<nm && i==shift)
		{
			
			Draw_symbol_align(big_font_rus+(chr-48+66)*256,xm+i,ym,hm,hm*2,align,color);
		}
		else
		if(chr<128)														// ��� ���������� ��������
		{	
			chr=chr-32;
			Draw_symbol_align(big_font_16+chr*256,xm+i,ym,hm,hm*2,align,color);			
		}else															// ��� ������� ��������� � ���� � ������
		{ 
			if(chr>175) chr=chr-192; else chr=chr-192-17;
			Draw_symbol_align(big_font_rus+chr*256,xm+i,ym,hm,hm*2,align,color);//shift
		};			
	}
};

//_______________________________________ �������� ������� ��� �� ������� ________________________
void delay_in_cycle(unsigned int cnt)
{
	unsigned long i=0,j=0;
	
	//for(i=0;i<cnt;i++ )						// cnt - � �������� (��� OSC=4M) && !keypressed_short
	while(i<cnt && !keypressed_short)
	{
		for(j=0;j<0xFFFF; j++){asm("NOP");};	// 16536
		i++;
		//vReadButtons();
		butt_scan();
	}
	keypressed_short=false;
}
//__________________ ���������� ��������� 4 Show logo________________
void show_msg_4(unsigned char color)
{
	Draw_string (msg_4_width,nodot, msg_4_line0 , msg_4_pos, 0, font_8_dark, fnt_width_8, color);
	Draw_string (msg_4_width,nodot, msg_4_line1 , msg_4_pos, 1, font_8_dark, fnt_width_8, color);
	Draw_string (msg_4_width,nodot, msg_4_line2 , msg_4_pos, 2, font_8_dark, fnt_width_8, color);
	Draw_string (msg_4_width,nodot, msg_4_line3 , msg_4_pos, 3, font_8_dark, fnt_width_8, color);
};
void bright_up()
{
	unsigned char i;

	for(i=0;i<0xff;i++)
	{
		send_command(0xC1);					// Set Contrast Current (C1h) 9F
		send_data(i);						// 256 steps for ISEG current [reset = 7Fh]
		_delay_ms(bright_speed);
	}
};
void bright_down()
{
	unsigned char i;

	for(i=0xff;i>0;i--)
	{
		send_command(0xC1);					// Set Contrast Current (C1h) 9F
		send_data(i);						// 256 steps for ISEG current [reset = 7Fh]
		_delay_ms(bright_speed);
	}	
};
//_______________________________________ �������� �������� ���� ___________________
void Show_Logo(void)
{
	cls();
	show_msg_4(back_color);
	Draw_symbol(&font_8_dark[172*64],18,3, fnt_width_8,fnt_width_8*2,back_color);	// ������ "copyright"
	Draw_symbol(&font_8_dark[2*64] ,23,3,  fnt_width_8,fnt_width_8*2,back_color);	// ������ "�������"
	Draw_symbol(&font_8_dark[2*64] ,27,3,  fnt_width_8,fnt_width_8*2,back_color);	// ������ "�������"
	//Draw_symbol(logo_64_64,0,0,64,64,0);
	//Draw_symbol (pep_radius,27,3,8,16,front_color );
	bright_up();
};
//________________ �������������� ����� � ������ ��� ������� ����� __________________
unsigned char num2str_left(unsigned long v, unsigned char *str)
{ unsigned char c,ind=0;
	unsigned char was_dig=false;
	//unsigned char str[4];
	

	while(v>9999){v-=10000;}				// ������� ������� ������� �������� �����
	c=0;
	while(v>=1000){c++;v-=1000;}
	if((!was_dig)&&(c==0)) str[0]=' ';		// ���� ������ �� ���� - ������
	else{
		was_dig=true;
		str[ind]=number_offset+c;			// ������
		ind++;
	}
	c=0;
	while(v>=100){c++;v-=100;}
	if((!was_dig)&&(c==0)) str[1]=' ';		// ���� ����� �� ���� - ������
	else{
		was_dig=true;
		str[ind]=number_offset+c;			// �����
		ind++;
	}
	c=0;
	while(v>=10){c++;v-=10;}
	if((!was_dig)&&(c==0)) str[2]=' ';		// ���� �������� �� ���� - ������
	else{
		was_dig=true;
		str[ind]=number_offset+c;			// �������
		ind++;
	}
	str[3]=' ';
	str[ind]=number_offset+v;				// �������
	ind++;
	return ind;
};
//________________ �������������� ����� � ������ ��� ������� ����� __________________
unsigned char num2str_right(unsigned long v, unsigned char *str)
{ unsigned char c,ind=0;
	unsigned char was_dig=false;
	//unsigned char str[4];
	
	
	//if(v>=10000)v/=10;						// ���� ������ 100��, �� 1 ���� ����� �����
	while(v>=10000)v/=10;

	while(v>9999){v-=10000;}				// ������� ������� ������� �������� �����
	c=0;
	while(v>=1000){c++;v-=1000;}
	if((!was_dig)&&(c==0)) str[0]=' ';		// ���� ������ �� ���� - ������
	else{
		was_dig=true;
		str[0]=number_offset+c;				// ������
		ind++;
	}
	c=0;
	while(v>=100){c++;v-=100;}
	if((!was_dig)&&(c==0)) str[1]='0';		// ���� ����� �� ���� - ������ 32
	else{
		was_dig=true;
		str[1]=number_offset+c;				// �����
		ind++;
	}
	c=0;
	while(v>=10){c++;v-=10;}
	if((!was_dig)&&(c==0)) str[2]='0';		// ���� �������� �� ���� - ������ 32
	else{
		was_dig=true;
		str[2]=number_offset+c;				// �������
		ind++;
	}
	str[3]=number_offset+v;					// �������
	ind++;
	/*
	if(main_value>high_resolution)
	{
		big_dot_pos=1;				
	}else big_dot_pos=2;	
*/
	return ind;
};
//________________�������������� ����� � ������ ��� ������� �����, ��� long __________________
unsigned char num2str_left_long(unsigned long v, unsigned char *str)
{ unsigned char c,ind=0,ii;
	unsigned char was_dig=false;
	
	for(ii=0;ii<8;ii++)str[ii]=32;
	c=0;
	while(v>=10000000){c++;v-=10000000;}
	if((!was_dig)&&(c==0)) str[ind]=' ';               // ???? ?????? ?? ???? - ??????
	else{
		was_dig=true;
		str[ind]=number_offset+c;                       // ??????
		ind++;
	}
	c=0;
	while(v>=1000000){c++;v-=1000000;}
	if((!was_dig)&&(c==0)) str[ind]=' ';               // ???? ?????? ?? ???? - ??????
	else{
		was_dig=true;
		str[ind]=number_offset+c;                       // ??????
		ind++;
	}
	c=0;
	while(v>=100000){c++;v-=100000;}
	if((!was_dig)&&(c==0)) str[ind]=' ';               // ???? ?????? ?? ???? - ??????
	else{
		was_dig=true;
		str[ind]=number_offset+c;                       // ??????
		ind++;
	}
	c=0;
	while(v>=10000){c++;v-=10000;}
	if((!was_dig)&&(c==0)) str[ind]=' ';               // ???? ?????? ?? ???? - ??????
	else{
		was_dig=true;
		str[ind]=number_offset+c;                       // ??????
		ind++;
	}
	c=0;
	while(v>=1000){c++;v-=1000;}
	if((!was_dig)&&(c==0)) str[ind]=' ';               // ???? ?????? ?? ???? - ??????
	else{
		was_dig=true;
		str[ind]=number_offset+c;                       // ??????
		ind++;
	}
	c=0;
	while(v>=100){c++;v-=100;}
	if((!was_dig)&&(c==0)) str[ind]=' ';               // ???? ????? ?? ???? - ??????
	else{
		was_dig=true;
		str[ind]=number_offset+c;                       // ?????
		ind++;
	}
	c=0;
	while(v>=10){c++;v-=10;}
	if((!was_dig)&&(c==0)) str[ind]=' ';               // ???? ???????? ?? ???? - ??????
	else{
		was_dig=true;
		str[ind]=number_offset+c;                       // ???????
		ind++;
	}
	//str[ind-1]=' ';
	str[ind]=number_offset+v;                               // ???????
	ind++;
	return ind;
};
//________________ �������������� ����� � ������ c �������� ������ __________________
void num2str_zeros(unsigned int v, unsigned char *str,unsigned char num_off)
{ unsigned char c;
	unsigned char was_dig=false;
	//unsigned char str[4];
	

	while(v>9999){v-=10000;}				// ������� ������� ������� �������� �����
	c=0;
	while(v>=1000){c++;v-=1000;}
	if((!was_dig)&&(c==0)) str[0]='0';		// ���� ������ �� ���� - ����
	else{
		was_dig=true;
		str[0]=number_offset+c;				// ������
	}
	c=0;
	while(v>=100){c++;v-=100;}
	if((!was_dig)&&(c==0)) str[1]='0';		// ���� ����� �� ���� - ����
	else{
		was_dig=true;
		str[1]=number_offset+c;				// �����
	}
	c=0;
	while(v>=10){c++;v-=10;}
	if((!was_dig)&&(c==0)) str[2]='0';		// ���� �������� �� ���� - ����
	else{
		was_dig=true;
		str[2]=number_offset+c+num_off;		// �������
	}
	str[3]=number_offset+v;					// �������
};
//________________ �������������� ����� � ������ c �������� ������ __________________
unsigned char num2str_3_zeros(unsigned int v, unsigned char *str)
{ unsigned char c;
	unsigned char was_dig=false;
	//unsigned char str[4];
	
	c=0;
	while(v>=100){c++;v-=100;}
	if((!was_dig)&&(c==0)) str[0]='0';		// ���� ����� �� ���� - ����
	else{
		was_dig=true;
		str[0]=number_offset+c;				// �����
	}
	c=0;
	while(v>=10){c++;v-=10;}
	if((!was_dig)&&(c==0)) str[1]='0';		// ���� �������� �� ���� - ����
	else{
		was_dig=true;
		str[1]=number_offset+c;				// �������
	}
	str[2]=number_offset+v;					// �������
	return c;
};
// __________________________ ���������� ��������� �������__________
void show_battery(unsigned char percent,unsigned char color)
{
	if(batt_refresh)
	{
		Draw_symbol(batt_16_H+(percent<<6),15,0,16,8,color); //*64 - ������ ������� � ������, ������ �������� 0-4
		batt_refresh=false;
	
/*		if(TestBit(PORTK,0))Draw_symbol(USB_conn,13,0,16,8,color);
		else Draw_symbol(USB_conn,13,0,16,8,clear_color);
	*/
	
	}
};

// __________________�������� ������� ������ � ���������
void battery_status(void)
{
	unsigned int voltsb=0,CV;

	if (PINK & (1<<EXTPOWER))					//// �������� ���� �� ������� �������
	{
		batt_percent=4;
		//batt_max=4;
		batt_min=0xFF;
	}else
	{
		CV =  ADC_convert();					//// ������ ��������� � ��������� ��������

		voltsb = (CV*59.37)/100;
		if ((voltsb >= 270) && (voltsb <=307 )) // ������ ��������� 2� - 3.51�  200-350
		{
			batt_percent=0;
			//eeprom_write_word (0x1000,CV);
		}else
		if ((voltsb > 307) && (voltsb <=345 )) // ������ ��������� 350-365
		{
			batt_percent=1;
			//eeprom_write_word (0x1200,CV);
		}
		if ((voltsb > 345) && (voltsb <=382 )) // ������ ��������� 365-380
		{
			batt_percent=2;
			//eeprom_write_word (0x1300,CV);
		}else
		if ((voltsb > 382) && (voltsb <=420 )) // ������ ��������� 380-395
		{
			batt_percent=3;
			//eeprom_write_word (0x1400,CV);
		}else
		if ((voltsb > 420) && (voltsb <=1530 )) // ������ ��������� 395-1530
		{
			batt_percent=4;
			//eeprom_write_word (0x1500,CV);
			batt_min=0xFF;
			
		}//else	batt_percent=1;
	};
	if(batt_min>batt_percent) batt_min=batt_percent;
	else batt_percent=batt_min;
	
	//batt_refresh=true;
};

void pwr_off()		// ���������� ������� ���.11
{
	BEEP(3);
	bright_down();
	cls();
	PORTA = 0X00;
	PORTB = 0X00;
	PORTC = 0X00;
	PORTD = 0X00;
	PORTE = 0X00;
	PORTJ = 0X00;
	PORTF = 0x00;
	DDRF = 0X00;
	for(;;); // ������ ��������
};
//////////////////////////////////////////////////

/*_______________������ #1___________________*/
void vReadButtons( void *pvParameters )
{
        unsigned char temp_choice=1;
 unsigned long key_read_cnt=0;                                  // ������� �������� ��������� ������� 
        unsigned long work_time=0;
        unsigned long time_cnt=0;                                       // ������� �������

//        unsigned char i=0;
//		unsigned char pwr=0;
        unsigned char call_butt=0;
        portTickType xLastExecutionTime;
        unsigned char *str_show_temp[4];
        str_show_temp[0]=" ";
        str_show_temp[1]=" ";
        str_show_temp[2]=" ";
        str_show_temp[3]=" ";


        //xLastExecutionTime = xTaskGetTickCount();

        /* ������ ��������� �� ���� ������������ ����� */
        for(;;)
        {
        
 		//if(UCSR0A & (1<<RXC0)) CONFR();		// ������ ���� UART

	 
        #ifdef   maket_build
		 

                        if (!(PINF & (1<<ONKEY)) && key_time_pwr>0)
                        {
                                BEEP(3);
                                key_time_pwr++;
                                if(key_time_pwr>key_pwr_limit)
                                {
                                        pwr_off();
                                };
                        }else // ?????? ????????
                        {
                                key_time_pwr=1;
//                              if(menu_level_choice>1)menu_level_choice--;
                        };
        #endif
        
        ///////////////////////////////////////// ���� �������: �������������� � ���������
        time_cnt++;
        if(time_cnt>0x2A00)             // 1 ��� � ��� ��� 8� = 0x2A00
        {
				time_cnt=0;
				work_time=eeprom_read_dword(TNAR);
				work_time+=1;
				eeprom_write_dword(TNAR,work_time); 
				
				if(ee_minutes_off>0)
				{
					time2off++;
					if(time2off>ee_minutes_off) pwr_off();	
				}
        }
        /////////////////////////////////////////
        
        key_read_cnt++;
        if(key_read_cnt>key_read_delay)                                 // 128??
        {
                key_read_cnt=0;
                ////BEEP(2);
                //screen_refresh=true;                                          // ���������� ������!!!!!!!!!!!!!!!!!!!!
                chpush=key_find();

                if(chpush >0 && butt_old==0)
                {
                        key_time=0; 
                        keypressed_short=true;
						key_released=false;
                        BEEP(2);
                }
                else
                if(chpush >0 && butt_old >0)
                {
                       key_time++;
                       if(key_time>key_repeat)  
                       {
                                keypressed_long=true; 
                                keypressed_short=true;
                        }
//                         if(key_time%64==0)										// ��� ������� �������� �� ������
//                         {
//                                 if(key_inc<100)key_inc*=10;
//                                 //else key_inc=1;
//                         }
                }
                else
                if(chpush==0 && butt_old >0)
                {
                        key_time=0;
                        key_inc=1;
                        key_released=true;	                                    // ������ ��������!
                        keypressed_short=false;
                        keypressed_long=false;
                }
                butt_old=chpush;
                batt_refresh=true;


//*****************************************************************
//_________________________________________________________________
//_________________________________________________________________
                if(keypressed_short)                                            // �������� ������� �� ������!
                {
                        time2off=0;                                             // ����� ������� ��������������
                        
                        //screen_refresh=true;                                  
                        //keypressed_short=false;
                        ////BEEP(2);
                        //menu_level_choice=2;
                        //call_butt=butt_old;
                        
                        if(butt_old==keyrezim)                                  // �����
                        {
                                //cls();
                                keypressed_short=false;
                                
                                service_choice=1;                               // ���.1 ������	        
                                
                                if(menu_level_choice==1)                        // ������
                                {
                                        cls();
                                        screen_refresh=true;                    // 
                                        temp_choice=ee_mode_choice;             // ��������� ����� �����
                                        //xSemaphoreGive( xMutex );
                                        menu_level_choice=2;                    // =2
                                }
                                else
                                if(menu_level_choice==2)
                                {
                                        cls();
                                        service_choice=1;                                       // ???.1 ?????? 
                                        if(call_butt==butt_old)
                                        {
                                                ee_mode_choice= eeprom_read_byte(MODE1+nastr);//temp_choice;// ��������������� ����� ����� ��� ���������
                                                screen_refresh=true;            // ????????? ?????
                                                menu_level_choice=1;            // ??????? ? ???????? ???????
                                        }
                                        //call_butt=butt_old;

                                }else
                                if(menu_level_choice==3)
                                {
                                        cls();
                                        //service_choice=1;                     // ?????
                                        menu_level_choice=2;            // ??????? ??????? ??? ??????????
                                };
                                call_butt=butt_old;
                        }
                        else
                        if(butt_old==keynastr)								// ���������
                        {
                                
							keypressed_short=false;
                            service_choice=2;                                       // ???.7 ?????????
							/////////////////////////////////////   
							if(keypressed_long)                                     // ������ ������� = ��������
							{
									//BEEP(2);
									//cls();
									keypressed_long=false;
									keypressed_short=false;
									screen_refresh=true;            // ????????? ?????
									dialogues_choice=dlg_settings_gain;                     // Dlg_8 ????????
									           
									menu_level_choice=3;            // ?????? ? ???????
							}               //if(keypressed_long)
							else    /////////////////////////////                      
                                
                                if(menu_level_choice==1)                        // ??????
                                {
                                        cls();
                                        screen_refresh=true;                    // ????????? ?????
                                        temp_choice=settings_choice;    // ????????? ????? ?????
                                        menu_level_choice=2;                    // ??????
                                }
                                else
                                if(menu_level_choice==2)
                                {
                                        cls();
                                        service_choice=2;                                       // ???.7 ?????????
                                        if(call_butt==butt_old)
                                        {
                                                settings_choice=temp_choice;// ??????????????? ????? ????? ??? ?????????
                                                screen_refresh=true;            // ????????? ?????
                                                menu_level_choice=1;            // ??????? ? ???????? ???????   
                                        }
                                        //call_butt=butt_old;
                                }else
                                if(menu_level_choice==3)
                                {
                                        cls();
                                        service_choice=2;                                       // ???.7 ?????????
                                        menu_level_choice=2;                    // ??????? ??????? ??? ?????????? ? ?????????
                                };
                                call_butt=butt_old;
                        }
                        else
                        if(butt_old==keyzero)                                   // ?????? ??????
                        {
                                cls();
                                keypressed_short=false;
                                service_choice=3;                                       // ???.8 ??????????
//                              screen_refresh=true;                            
                                if(menu_level_choice==1)                        // ??????
                                {
                                        //cls();
                                        
                                        screen_refresh=true;                    // ????????? ?????
                                        temp_choice=ee_pep_numb;                // ????????? ????? ?????
                                        menu_level_choice=2;                    // ??????
                                }
                                else
                                if(menu_level_choice==2)
                                {
                                        //cls();
                                        
                                        if(call_butt==butt_old)
                                        {
                                                ee_pep_numb=temp_choice;        // ??????????????? ????? ????? ??? ?????????
                                                screen_refresh=true;            // ????????? ?????      
                                                menu_level_choice=1;            
                                        }
                                        //call_butt=butt_old;
                                }else
                                if(menu_level_choice==3)
                                {
                                        cls();
                                        service_choice=3;                               // ???.8 ??????????
                                        menu_level_choice=2;                    // ??????? ??????? ? ????????? ??? ??????????
                                };
                                call_butt=butt_old;

                        }
                        else
                        if(butt_old==keypep)                                    // ???.9 ???
                        {
                                cls();
                                keypressed_short=false;
                                service_choice=4;                                       // ???.9 ???
                                screen_refresh=true;    
                                if(menu_level_choice==1)                        // ??????
                                {
                                        
                                        //cls();
                                        temp_choice=ee_pep_numb;                // ????????? ????? ?????
                                        menu_level_choice=2;                    // ??????       
                                        //call_butt=butt_old;                           
                                }
                                else
                                if(menu_level_choice==2)
                                {
                                        //cls();
                                        if(call_butt==butt_old)
                                        {
                                                ee_pep_numb=temp_choice;        // ??????????????? ????? ????? ??? ?????????
                                                screen_refresh=true;            // ????????? ?????
                                                menu_level_choice=1;            // ??????? ? ???????? ???????
                                                
                                        } 
                                        
                                        //temp_choice=ee_pep_numb;				// ????????? ????? ?????
                                        //call_butt=butt_old;
                                        
                                }else
                                if(menu_level_choice==3)
                                {
                                        cls();
                                        service_choice=4;                               // ???.9 ???
                                        menu_level_choice=2;                    // ??????? ??????? ??? ??????????
                                };
                                call_butt=butt_old;
                        }
                        else
                        if(butt_old==keymem)                                    // ???.10 ??????
                        {
	                          //  cls();
                                keypressed_short=false;
                              // screen_refresh=true;							//___________________________
                        
//                                else
                                if(menu_level_choice==1)                        // ??????? ???????? ???????- ?????? ?????????? ????????
                                {
                                        //menu_level_choice=2;
                                        //service_choice=5;                     // ???.10 ??????
                                        //ee_page_numb++;                       // ????? ????????
                                        //screen_refresh=true;                  // ????????? ?????
                                        entry_refresh=true;                                     
										
                                if(keypressed_long)                             // ?????? ??????? ?? ??????!
                                {
	                                //BEEP(2);
	                                keypressed_long=false;
	                                //screen_refresh=true;                    // ????????? ?????
	                                temp_choice=page_choice;                // ????????? ????? ?????
	                                service_choice=5;                               // ???.10 ??????
	                                menu_level_choice=2;                    // ??????? ? ?????????????? ??????? ?????? scroll_journal
 	num2str_left(menu_level_choice,str_show4);
 	Draw_string (4,nodot,str_show4, 6,2, font_8_dark, 8, front_color);


                                }       //if(keypressed_long)
										
										
                                }else
                                if(menu_level_choice==2)                        // ??????? ?????????????? ??????? scroll_journal
                                {
                                      // cls();
                                      // service_choice=5;                      // ???.7 ?????????
									   
//                                        if(call_butt==butt_old)
//                                        {
// 	                                       screen_refresh=true;            
// 	                                       menu_level_choice=1;            
//                                        }
//                                         //if(service_choice!=5)					// ?????? ?? ?????? ?????????????? ???????=??????

										if(service_choice!=5)  
                                        {
											//cls();
											screen_refresh=true;
                                            temp_choice=page_choice;				// ????????? ????? ?????
                                            service_choice=5;						// ???.10 ??????
                                        }
                                        else
                                        {                                           // ???? ?????? ??? ?????? ?? ?????? "??????"= ??????? ? ????????
                                            // cls();
                                            ee_page_numb=eeprom_read_word(MEMPNT);  // ?????? ????? ??????? ???????? ???????
                                            ee_page_size=eeprom_read_dword(get_page_size(ee_page_numb));
                                            //ee_page_size=eeprom_read_dword(get_addr(ee_page_numb));                       // ?????????? ??????? ?? i-? ????????
                                            screen_refresh=true;					// ????????? ?????
                                            menu_level_choice=1;					// ??????? ? ???????? ???????                                           
                                        }
                                }else
                                if(menu_level_choice==3)							// ????????? ? scroll_page
                                {
                                        cls();
										ee_page_numb=eeprom_read_word(MEMPNT);      // ?????? ????? ??????? ???????? ???????
										ee_page_size=eeprom_read_dword(get_page_size(ee_page_numb));
 										screen_refresh=true;
                                        service_choice=5;                           // ???.10 ??????
                                        menu_level_choice=2;						// ??????? ? ?????????????? ??????? ?????? scroll_journal
                                };
								//call_butt=butt_old;
                        }
                }; //if(keypressed_short)
        } //if(key_read_cnt>key_read_delay)
//_________________________________________________________________     
//_________________________________________________________________     
        //vTaskDelay(40 / portTICK_RATE_MS);//100 80 40
        taskYIELD();
        //vTaskDelayUntil(xLastExecutionTime, 10 / portTICK_RATE_MS);   //50
        } 
        vTaskDelete(NULL);
};

/*_______________ ������ #1 ___________________*/
/*
void vDisplay( void *pvParameters )
{
	portTickType xLastExecutionTime;
	
	xLastExecutionTime = xTaskGetTickCount();

	for(;;)
	{
		if(show_main_value)
		{
			main_value=IZMERENIE(0x01,vel,datch,nastr,amplif,voltp,calibr,mf,mp,tf);
			num2str_right((unsigned int)main_value,str_show);
			Draw_big_font (4,big_dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
		}
		show_main_value=false;
		
		//taskYIELD();
		vTaskDelayUntil(xLastExecutionTime, 100 / portTICK_RATE_MS);
	} 
	vTaskDelete(NULL);
};*/
void show_progress_bar(unsigned long prs,  unsigned long prb_max, unsigned long prs_max, unsigned char pos)
{
//	unsigned char slb_length=1; //2
	unsigned int i=0;
	unsigned long slb_off=0;
		
	slb_off=(prb_max*prs)/prs_max;							// ������������ � ������ ������
// 	if(prs_max>prb_max)slb_length=1;
// 	else slb_length=(prb_max)/prs_max;					//+1 ��� ����� ������� �� ���������� �� �����

	for(i=0;i<slb_off;i++)
	{
		Draw_symbol(progress_mask,(32-prb_max)/2+i,pos,8,16,front_color);
	}
	for(i=slb_off;i<prb_max;i++)
	{
		Draw_symbol(progress_mask,(32-prb_max)/2+i,pos,8,16,12);
	}

}
//__________________________ ���������� No sound __________________
void show_no_sound(unsigned char flag)
{
	if(flag)
	{Draw_symbol(no_sound_16,14,0,16,16,back_color);}
	else
	{Draw_symbol(no_sound_16,14,0,16,16,clear_color);}
};
//__________________________ ���������� ������������ ������� __________________
void show_acoustic(unsigned char color)
{
	Draw_symbol(acustic,0,1,16,32,color);
};
//__________________ ���������� ��������� 5 (������� Enter � �������)________________
void show_msg_5(unsigned char color)
{
	unsigned char setting_num=0;
		
	Draw_string (msg_5_width,nodot, msg_5_line0 , msg_5_pos, 0, font_8_dark, fnt_width_8, color);
	Draw_string (msg_5_width,nodot, msg_5_line1 , msg_5_pos, 1, font_8_dark, fnt_width_8, color);
	Draw_string (msg_5_width,nodot, msg_5_line2 , msg_5_pos, 2, font_8_dark, fnt_width_8, color);
	Draw_string (msg_5_width,nodot, msg_5_line3 , msg_5_pos, 3, font_8_dark, fnt_width_8, color);
	
	if(settings_choice>10)setting_num=10; else setting_num=settings_choice;
	Draw_string_left(menu_settings_width,setting_list[10+setting_num], 12, 0, font_8_dark, fnt_width_8, front_color);
	Draw_string_left(menu_modes_width,mode_list[5+ee_mode_choice], 12, 1, font_8_dark, fnt_width_8, front_color);
	num2str_left(ee_gain_choice,str_show);
	Draw_string (2,nodot, str_show , 12, 2, font_8_dark, fnt_width_8, front_color);
	
	screen_refresh=true;
};
//__________________ ���������� ��������� 14 ________________
void show_msg_14(unsigned char color)							// �������
{
	unsigned long tmp_save=0;
	 unsigned char * str_show4[4]={"    "};
	Draw_string (msg_14_width,nodot, msg_14_line0 , msg_14_pos, 0, font_8_dark, fnt_width_8, color);
	Draw_string (msg_14_width,nodot, msg_14_line1 , msg_14_pos, 1, font_8_dark, fnt_width_8, color);
	Draw_string (msg_14_width,nodot, msg_14_line2 , msg_14_pos, 2, font_8_dark, fnt_width_8, color);
	Draw_string (msg_14_width,nodot, msg_14_line3 , msg_14_pos, 3, font_8_dark, fnt_width_8, color);

	tmp_save=eeprom_read_dword(TNAR)/60;						// ������� ��������� � ���������� � �����
	num2str_3_zeros(tmp_save,str_show4);//num2str_left
	Draw_string (3,nodot, str_show4 , 16, 3, font_8_dark, fnt_width_8, color);

//	tmp_save=eeprom_read_dword(ZNUM0);							// ������� ����� �������
//	num2str_right(tmp_save,str_show4);

// 	str_show4[0]=eeprom_read_byte(ZNUM0);
// 	str_show4[1]=eeprom_read_byte(ZNUM1);
// 	str_show4[2]=eeprom_read_byte(ZNUM2);
// 	str_show4[3]=eeprom_read_byte(ZNUM3);	
// 	Draw_string (4,nodot,str_show4, 16+6, 2, font_8_dark, fnt_width_8, color);	

	str_show4[0]=eeprom_read_byte(ZNUM0);
	Draw_string (1,nodot,str_show4, 16+6, 2, font_8_dark, fnt_width_8, color);
	str_show4[0]=eeprom_read_byte(ZNUM1);
	Draw_string (1,nodot,str_show4, 16+7, 2, font_8_dark, fnt_width_8, color);
	str_show4[0]=eeprom_read_byte(ZNUM2);
	Draw_string (1,nodot,str_show4, 16+8, 2, font_8_dark, fnt_width_8, color);
	str_show4[0]=eeprom_read_byte(ZNUM3);
	Draw_string (1,nodot,str_show4, 16+9, 2, font_8_dark, fnt_width_8, color);

		
// 	Draw_string (1,nodot,  , 16+6, 2, font_8_dark, fnt_width_8, color);
// 	Draw_string (1,nodot, &eeprom_read_byte(ZNUM1) , 16+7, 2, font_8_dark, fnt_width_8, color);
// 	Draw_string (1,nodot, &eeprom_read_byte(ZNUM2) , 16+8, 2, font_8_dark, fnt_width_8, color);
// 	Draw_string (1,nodot, &eeprom_read_byte(ZNUM3) , 16+9, 2, font_8_dark, fnt_width_8, color);

};
//__________________ ���������� ��������� 15 (��� �� ������� �������)________________
void show_msg_15(unsigned char color)
{
if(screen_refresh)
{
		
	Draw_string (msg_15_width,nodot, msg_15_line0 , msg_15_pos, 0, font_8_dark, fnt_width_8, color);
	Draw_string (msg_15_width,nodot, msg_15_line1 , msg_15_pos, 1, font_8_dark, fnt_width_8, color);
	Draw_string (msg_15_width,nodot, msg_15_line2 , msg_15_pos, 2, font_8_dark, fnt_width_8, color);
	Draw_string (msg_15_width,nodot, msg_15_line3 , msg_15_pos, 3, font_8_dark, fnt_width_8, color);
	
	if(ee_pep_numb<(pep_numb-3))	
	{Draw_string_left (2, thickness_standard[0] , 23, 2, font_8_dark, fnt_width_8, color);} // 3 ��
	else
	if(ee_pep_numb==pep_numb-3)	{Draw_string_left  (2, thickness_standard[1] , 23, 2, font_8_dark, fnt_width_8, color);} //5 ��
	else
	if((ee_pep_numb==pep_numb-1)|| (ee_pep_numb==pep_numb-2))	Draw_string_left  (2, thickness_standard[2] , 23, 2, font_8_dark, fnt_width_8, color); // 20 ��
	
	show_acoustic(clear_color);
	
	
	switch (nastr)				// ��������� ��������� ��� ���������� 0
	{
		 case 0:  amplif= eeprom_read_byte(AMP1); calibr = eeprom_read_dword(CALB1);     break;
		 case 1:  amplif= eeprom_read_byte(AMP2); calibr = eeprom_read_dword(CALB2);     break;
		 case 2:  amplif= eeprom_read_byte(AMP3); calibr = eeprom_read_dword(CALB3);     break;
		 case 3:  amplif= eeprom_read_byte(AMP4); calibr = eeprom_read_dword(CALB4);     break;
		 case 4:  amplif= eeprom_read_byte(AMP5); calibr = eeprom_read_dword(CALB5);     break;
		 case 5:  amplif= eeprom_read_byte(AMP6); calibr = eeprom_read_dword(CALB6);     break;
		 case 6:  amplif= eeprom_read_byte(AMP7); calibr = eeprom_read_dword(CALB7);     break;
		 case 7:  amplif= eeprom_read_byte(AMP8); calibr = eeprom_read_dword(CALB8);     break;
		 case 8:  amplif= eeprom_read_byte(AMP9); calibr = eeprom_read_dword(CALB9);     break;
		 case 9: amplif= eeprom_read_byte(AMP10); calibr = eeprom_read_dword(CALB10);	break;
	}
	cfgr_load(amplif,datch);
}
screen_refresh=false;
}; 
//__________________ ���������� ��������� 16 ________________
void show_msg_16(unsigned char color)
{
	
/*
	 unsigned char* msg_16_line0[32] = {"                                "};
	 unsigned char* msg_16_line1[32] = {"    ���������� ���� ���������,  "};
	 unsigned char* msg_16_line2[32] = {"    ����� ��������� ���������   "};
	 unsigned char* msg_16_line3[32] = {"                                "};
	
	Draw_string (32,nodot, msg_16_line0 , 0, 0, font_8_dark, fnt_width_8, color);
	Draw_string (32,nodot, msg_16_line1 , 0, 1, font_8_dark, fnt_width_8, color);
	Draw_string (32,nodot, msg_16_line2 , 0, 2, font_8_dark, fnt_width_8, color);
	Draw_string (32,nodot, msg_16_line3 , 0, 3, font_8_dark, fnt_width_8, color);
*/
	Draw_string (msg_16_width,nodot, msg_16_line0 , msg_16_pos, 0, font_8_dark, fnt_width_8, color);
	Draw_string (msg_16_width,nodot, msg_16_line1 , msg_16_pos, 1, font_8_dark, fnt_width_8, color);
	Draw_string (msg_16_width,nodot, msg_16_line2 , msg_16_pos, 2, font_8_dark, fnt_width_8, color);
	Draw_string (msg_16_width,nodot, msg_16_line3 , msg_16_pos, 3, font_8_dark, fnt_width_8, color);


};
//__________________ ���������� ��������� 17 ���������� V________________
void show_msg_17(unsigned char color)
{
	Draw_string (msg_17_width,nodot, msg_17_line0 , msg_17_pos, 0, font_8_dark, fnt_width_8, color);
	Draw_string (msg_17_width,nodot, msg_17_line1 , msg_17_pos, 1, font_8_dark, fnt_width_8, color);
	Draw_string (msg_17_width,nodot, msg_17_line2 , msg_17_pos, 2, font_8_dark, fnt_width_8, color);
	Draw_string (msg_17_width,nodot, msg_17_line3 , msg_17_pos, 3, font_8_dark, fnt_width_8, color);
};
//__________________ ���������� ��������� 18 ���������� H________________
void show_msg_18(unsigned char color)
{
	Draw_string (msg_18_width,nodot, msg_18_line0 , msg_18_pos, 0, font_8_dark, fnt_width_8, color);
	Draw_string (msg_18_width,nodot, msg_18_line1 , msg_18_pos, 1, font_8_dark, fnt_width_8, color);
	Draw_string (msg_18_width,nodot, msg_18_line2 , msg_18_pos, 2, font_8_dark, fnt_width_8, color);
	Draw_string (msg_18_width,nodot, msg_18_line3 , msg_18_pos, 3, font_8_dark, fnt_width_8, color);
};
//__________________ ���������� ��������� 19 ���������� H________________
void show_msg_19(unsigned char color)
{
	Draw_string (msg_19_width,nodot, msg_19_line0 , msg_19_pos, 0, font_8_dark, fnt_width_8, color);
	Draw_string (msg_19_width,nodot, msg_19_line1 , msg_19_pos, 1, font_8_dark, fnt_width_8, color);
	Draw_string (msg_19_width,nodot, msg_19_line2 , msg_19_pos, 2, font_8_dark, fnt_width_8, color);
	Draw_string (msg_19_width,nodot, msg_19_line3 , msg_19_pos, 3, font_8_dark, fnt_width_8, color);
	show_acoustic(clear_color);
};
// __________________ ���������� ��������� 20 ________________
// void show_msg_20(unsigned char color)
// {
// 	Draw_string (msg_20_width,nodot, msg_20_line0 , msg_20_pos, 0, font_8_dark, fnt_width_8, color);
// 	Draw_string (msg_20_width,nodot, msg_20_line1 , msg_20_pos, 1, font_8_dark, fnt_width_8, color);
// 	Draw_string (msg_20_width,nodot, msg_20_line2 , msg_20_pos, 2, font_8_dark, fnt_width_8, color);
// 	Draw_string (msg_20_width,nodot, msg_20_line3 , msg_20_pos, 3, font_8_dark, fnt_width_8, color);
// };
//__________________ ���������� ��������� 21 �������� ��������� ________________
void show_msg_21(unsigned char color)
{
//	unsigned char *str_sh[4];
	//taskENTER_CRITICAL ();
// 	cls();
//  	Draw_string (23,nodot, "�������� [   ] ���������,", 3, 0, font_8_dark, fnt_width_8, color);

//  	Draw_string (msg_21_width,nodot, msg_21_line1 , msg_21_pos, 1, font_8_dark, fnt_width_8, color);
//  	Draw_string (msg_21_width,nodot, msg_21_line2 , msg_21_pos, 2, font_8_dark, fnt_width_8, color);
//  	Draw_string (msg_21_width,nodot, msg_21_line3 , msg_21_pos, 3, font_8_dark, fnt_width_8, color);
//  	num2str_3_zeros(ee_page_numb,str_sh);
//  	Draw_string (3,nodot, str_sh , 13, 0, font_8_dark, fnt_width_8, color);


	Draw_string (msg_21_width,nodot, msg_21_line0, msg_21_pos, 0, font_8_dark, fnt_width_8, color);
	Draw_string (msg_21_width,nodot, msg_21_line1, msg_21_pos, 1, font_8_dark, fnt_width_8, color);
	Draw_string (msg_21_width,nodot, msg_21_line2, msg_21_pos, 2, font_8_dark, fnt_width_8, color);
	Draw_string (msg_21_width,nodot, msg_21_line3, msg_21_pos, 3, font_8_dark, fnt_width_8, color);
	num2str_3_zeros(ee_page_numb,str_show);
	Draw_string (3,nodot, str_show , 13, 0, font_8_dark, fnt_width_8, color);
	//taskEXIT_CRITICAL ();
};
//__________________ ���������� ��������� 22 ���������� �� ���������________________
void show_msg_22(unsigned char color)
{
	Draw_string (msg_22_width,nodot, msg_22_line0 , msg_22_pos, 0, font_8_dark, fnt_width_8, color);
	Draw_string (msg_22_width,nodot, msg_22_line1 , msg_22_pos, 1, font_8_dark, fnt_width_8, color);
	Draw_string (msg_22_width,nodot, msg_22_line2 , msg_22_pos, 2, font_8_dark, fnt_width_8, color);
	Draw_string (msg_22_width,nodot, msg_22_line3 , msg_22_pos, 3, font_8_dark, fnt_width_8, color);

// 	Draw_string (msg_22_width,nodot, "                                " , msg_22_pos, 0, font_8_dark, fnt_width_8, color);
// 	Draw_string (msg_22_width,nodot, " ���������� ���� �� ���������,  " , msg_22_pos, 1, font_8_dark, fnt_width_8, color);
// 	Draw_string (msg_22_width,nodot, "     �������� �� ���������      " , msg_22_pos, 2, font_8_dark, fnt_width_8, color);
// 	Draw_string (msg_22_width,nodot, "                                " , msg_22_pos, 3, font_8_dark, fnt_width_8, color);

};

//_________ ������ scrollbar ______________
void show_scrollbar(unsigned long prs,  unsigned long slb_max, unsigned long prs_max, unsigned char pos,unsigned char color)
{  // prs - ������������ ��������; slb_max - ������ scrollbar � ��������; prs_max - ������������ �������� ��������; pos- ��������� ������ � ����������� (0..31)

//	const unsigned char free_line[]  __attribute__ ((progmem))={0x00,0x0F,0x00,0x00,};
//	const unsigned char point_line[] __attribute__ ((progmem))={0x0F,0xFF,0xFF,0x00,};

	const unsigned char free_line[] ={0x00,0x0F,0x00,0x00,};
	const unsigned char point_line[] ={0x0F,0xFF,0xFF,0x00,};

	unsigned char screen_byte;
	unsigned char slb_length=1; //2
	unsigned int i=0,j;
	unsigned long slb_off=0;
	
	slb_off=(slb_max*prs)/prs_max;							// ������������ � ������ ������
	if(prs_max>slb_max)slb_length=1;
	else slb_length=(slb_max)/prs_max+1;					//+1 ��� ����� ������� �� ���������� �� �����
	
//	num2str_left(slb_off,str_show);							// ��� �������
//	Draw_string (4,nodot,str_show, 0,0, font_8_dark, 8, front_color);

	if(slb_max==32)place_in_ram(28+pos*(8>>2), 16, 28+pos*(8>>2)+(8/4)-1, 2*16+slb_max-1);
	else
	if(slb_max==48)place_in_ram(28+pos*(8>>2), 16, 28+pos*(8>>2)+(8/4)-1, 2*16+slb_max-1);
	else
	if(slb_max==64)place_in_ram(28+pos*(8>>2), 0,  28+pos*(8>>2)+(8/4)-1, 0*16+slb_max-1);
	
	send_command(0x5C);										// Write RAM Command (5Ch)
	for(i = 0; i < slb_max*4; i++)							// �� ��� ������� 2 �������: � ������� � ������� �������, 4 ���� �� �����
	{
		j=i>>2;												// �������� ������ �� ������� ����� (-2)
		if ((j >= slb_off) && (j < slb_off+slb_length))
		{	
			//if (j > slb_max-2)							// ������� �� �������
			screen_byte=point_line[i&0x03];
		} else screen_byte=free_line[i&0x03];
		if ((screen_byte & 0x0F) > color)screen_byte-=color; else screen_byte&=0xF0;	// �������� ����
		if (screen_byte>>4 > 0) screen_byte-=color<<4;else screen_byte&=0x0F;			// �������� ����
		
		if(i%4==0) PORTJ |= 0x40;							// SDC = 1; ����� ��� ������������ �� ��������� ������ RAM �������� 4 �����
		PORTG |= 0x04;										// WR = 1
		PORTA = screen_byte;								// ���������� ���� �� ���� ������
		PORTG &= 0xFB;										// WR = 0
	}
};
//__________________ ���������� ���� ������ _______________________
void scroll_menu_modes (unsigned char mlv)
{	// ������� = 16-length/2
	
	if(screen_refresh){cls();screen_refresh=false;}
	if(mlv==0)				// ����� ���������
	{
		Draw_string (menu_modes_width, nodot, menu_modes_line4 , menu_modes_pos, 0, font_8_dark, fnt_width_8, back_color);//0
		Draw_big_font_align(menu_modes_width, nobigdot, menu_modes_line0 , menu_modes_big_pos, 1, big_font_16, fnt_width_16,-1, front_color);
		Draw_string (menu_modes_width, nodot, menu_modes_line1 , menu_modes_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==1)				// ����� ������
	{
		Draw_string (menu_modes_width,nodot, menu_modes_line0 , menu_modes_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font(menu_modes_width, nobigdot, menu_modes_line1 , menu_modes_big_pos, 1, big_font_16, fnt_width_16, front_color);
		Draw_string (menu_modes_width,nodot, menu_modes_line2 , menu_modes_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==2)				// ����� ����������������
	{
		Draw_string (menu_modes_width,nodot, menu_modes_line1 , menu_modes_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font(menu_modes_width, nobigdot, menu_modes_line2 , menu_modes_big_pos, 1, big_font_16, fnt_width_16, front_color);
		Draw_string (menu_modes_width,nodot, menu_modes_line3 , menu_modes_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==3)				// ����� �����������
	{
		Draw_string (menu_modes_width,nodot, menu_modes_line2 , menu_modes_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font(menu_modes_width, nobigdot, menu_modes_line3 , menu_modes_big_pos, 1, big_font_16, fnt_width_16, front_color);
		Draw_string (menu_modes_width,nodot, menu_modes_line4 , menu_modes_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==4)				// ����� ������������
	{
		Draw_string (menu_modes_width,nodot, menu_modes_line3 , menu_modes_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font(menu_modes_width, nobigdot, menu_modes_line4 , menu_modes_big_pos, 1, big_font_16, fnt_width_16, front_color);
		Draw_string (menu_modes_width,nodot, menu_modes_line0 , menu_modes_pos, 3, font_8_dark, fnt_width_8, back_color);
	};
	show_scrollbar(mlv,64,modes_numb,scrol_pos, back_color);
};

//__________________ ���������� ���� ��������� _______________________
void scroll_menu_settings(unsigned char mlv)
{	// ������� = 16-length/2
	//Draw_big_font_align(menu_modes_width,nobigdot,menu_modes_line1,0,0, big_font_16, 16,-1, front_color);
	if(screen_refresh){cls();screen_refresh=false;}
	if(mlv==0)							// ��������� 1
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line15 ,menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width, nobigdot, menu_settings_line0 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,align_settings, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line1 , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==1)							// ��������� 2
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line0 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width, nobigdot, menu_settings_line1 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,align_settings, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line2 , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==2)							// ��������� 3
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line1 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width, nobigdot, menu_settings_line2 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,align_settings, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line3 , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==3)							// ��������� 4
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line2 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width, nobigdot, menu_settings_line3 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,align_settings, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line4 , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==4)							// ��������� 5
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line3 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width, nobigdot, menu_settings_line4 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,align_settings, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line5 , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==5)							// ��������� 6
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line4 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width, nobigdot, menu_settings_line5 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,align_settings, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line6 , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==6)							// ��������� 7
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line5 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width, nobigdot, menu_settings_line6 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,align_settings, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line7 , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==7)							// ��������� 8
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line6 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width, nobigdot, menu_settings_line7 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,align_settings, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line8 , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==8)							// ��������� 9
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line7 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width, nobigdot, menu_settings_line8 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,align_settings, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line9 , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==9)							// ���������� H>25 ��
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line8 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width, nobigdot, menu_settings_line9 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,align_settings, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line10, menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==10)							// ��������������
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line9  , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width, nobigdot, menu_settings_line10 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,align_settings, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line11 , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==11)							// �������
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line10 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width-1, nobigdot, menu_settings_line11 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,4, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line12 , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==12)							// �����
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line11 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width-1, nobigdot, menu_settings_line12 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,3, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line13 , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==13)							// ����
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line12 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width-1, nobigdot, menu_settings_line13 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,6, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line14 , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==14)							// ��������
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line13 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width, nobigdot, menu_settings_line14 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,3, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line15  , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==15)							// ����� ��������
	{
		Draw_string (menu_settings_width,nodot, menu_settings_line14 , menu_settings_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font_align(menu_settings_width, nobigdot, menu_settings_line15 , menu_settings_big_pos, 1, big_font_16, fnt_width_16,align_settings, front_color);
		Draw_string (menu_settings_width,nodot, menu_settings_line0  , menu_settings_pos, 3, font_8_dark, fnt_width_8, back_color);
	};
	show_scrollbar(mlv,64,settings_numb,scrol_pos, back_color);
};
//__________________ ���������� ���� ���������� _______________________
void scroll_menu_calibration(unsigned char mlv)
{
	if(screen_refresh){cls();screen_refresh=false;}
	if(mlv==0)							// ���������� �� 0
	{
		Draw_string (menu_calibration_width,nodot, menu_calibration_line2 , menu_calibration_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font(menu_calibration_width, nobigdot, menu_calibration_line0 , menu_calibration_big_pos, 1, big_font_16, fnt_width_16, front_color);
		Draw_string (menu_calibration_width,nodot, menu_calibration_line1 , menu_calibration_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==1)							// ���������� �� H
	{
		Draw_string (menu_calibration_width,nodot, menu_calibration_line0 , menu_calibration_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font(menu_calibration_width, nobigdot, menu_calibration_line1 , menu_calibration_big_pos, 1, big_font_16, fnt_width_16, front_color);
		Draw_string (menu_calibration_width,nodot, menu_calibration_line2 , menu_calibration_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==2)							// ���������� �� V
	{
		Draw_string (menu_calibration_width,nodot, menu_calibration_line1 , menu_calibration_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_big_font(menu_calibration_width, nobigdot, menu_calibration_line2 , menu_calibration_big_pos, 1, big_font_16, fnt_width_16, front_color);
		Draw_string (menu_calibration_width,nodot, menu_calibration_line0 , menu_calibration_pos, 3, font_8_dark, fnt_width_8, back_color);
	};
	show_scrollbar(mlv,64,calibration_numb,scrol_pos, back_color);
};
//__________________ ���������� ���� ��� _______________________
void scroll_menu_pep(unsigned char mlv)
{	// ������� = 16-length/2
	
	if(screen_refresh){cls();screen_refresh=false;}

	if(mlv==8)							// ��� 0
	{
		Draw_string (menu_pep_width,nodot, menu_pep_line7 , menu_pep_pos, 0, font_8_dark, fnt_width_8, back_color);		
		Draw_string (menu_pep_width,nodot, menu_pep_line8 , menu_pep_pos, 1, font_8_dark, fnt_width_8, front_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line0 , menu_pep_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line1 , menu_pep_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==0)							// ��� 1
	{
		Draw_string (menu_pep_width,nodot, menu_pep_line8 , menu_pep_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line0 , menu_pep_pos, 1, font_8_dark, fnt_width_8, front_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line1 , menu_pep_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line2 , menu_pep_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==1)							// ��� 2
	{
		Draw_string (menu_pep_width,nodot, menu_pep_line0 , menu_pep_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line1 , menu_pep_pos, 1, font_8_dark, fnt_width_8, front_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line2 , menu_pep_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line3 , menu_pep_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==2)							// ��� 3
	{
		Draw_string (menu_pep_width,nodot, menu_pep_line1 , menu_pep_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line2 , menu_pep_pos, 1, font_8_dark, fnt_width_8, front_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line3 , menu_pep_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line4 , menu_pep_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==3)							// ��� 4
	{
		Draw_string (menu_pep_width,nodot, menu_pep_line2 , menu_pep_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line3 , menu_pep_pos, 1, font_8_dark, fnt_width_8, front_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line4 , menu_pep_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line5 , menu_pep_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==4)							// ��� 5
	{
		Draw_string (menu_pep_width,nodot, menu_pep_line3 , menu_pep_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line4 , menu_pep_pos, 1, font_8_dark, fnt_width_8, front_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line5 , menu_pep_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line6 , menu_pep_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==5)							// ��� 6
	{
		Draw_string (menu_pep_width,nodot, menu_pep_line4 , menu_pep_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line5 , menu_pep_pos, 1, font_8_dark, fnt_width_8, front_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line6 , menu_pep_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line7 , menu_pep_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==6)							// ��� 7
	{
		Draw_string (menu_pep_width,nodot, menu_pep_line5 , menu_pep_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line6 , menu_pep_pos, 1, font_8_dark, fnt_width_8, front_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line7 , menu_pep_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line8 , menu_pep_pos, 3, font_8_dark, fnt_width_8, back_color);
	}else
	if(mlv==7)							// ��� 8
	{
		Draw_string (menu_pep_width,nodot, menu_pep_line6 , menu_pep_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line7 , menu_pep_pos, 1, font_8_dark, fnt_width_8, front_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line8 , menu_pep_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (menu_pep_width,nodot, menu_pep_line0 , menu_pep_pos, 3, font_8_dark, fnt_width_8, back_color);
	};
	show_scrollbar(mlv,64,pep_numb,scrol_pos, back_color);
}

unsigned int get_page_size(unsigned int cscl)					// ���������� ����� �� ���������� (contents) ������� ��� �������� � ������� cscl
{
	return journal_addr+8+cscl*4;
}

unsigned int get_addr(unsigned int pscl)						// ���������� ����� �������� � ������� pscl
{
	unsigned int i;
	unsigned long offset=0;
	
	for(i=0;i<pscl;i++) offset=offset+entry_size*eeprom_read_dword(get_page_size(i));
	
	return journal_addr+8+(page_numb_max)*4+offset+4;
}
unsigned int get_page_real_size(unsigned int pscl)						// ���������� ����� �������� � ������� pscl
{
	unsigned int i;
	unsigned long offset=0;
	
	for(i=0;i<pscl;i++) offset=offset+entry_size*eeprom_read_dword(get_page_size(i));
	
	return journal_addr+8+(page_numb_max)*4+offset;
}
//__________________ ���������� ���� ���������� _______________________
void scroll_journal(unsigned int journal_focus, unsigned int journal_size, unsigned char color)
{	
	unsigned char str_show_temp[3]={"999"};
	unsigned int i;
	//unsigned int point;
//	unsigned int accum=0;
	
		if(screen_refresh)
		{
			cls();
			screen_refresh=false;
		};
		
		show_scrollbar(journal_focus+1,64, journal_size+1, scrol_pos, back_color);		
		
		for (i=0;i<4;i++)
		{
			if(i==focus_raw)color=front_color; else color=back_color;
			

			if((journal_focus+i)==journal_size)
			{
				Draw_string(scr_col,nodot,msg_23_line0,0,i, font_8_dark, fnt_width_8, color);		// ����� �������� 
			}else
			if((journal_focus+i)==journal_size-1)
			{
				Draw_string(15,nodot,msg_23_line1,0,i, font_8_dark, fnt_width_8, color);			// �������� ������
// 				Draw_string(1,nodot, "[",15, i, font_8_dark, fnt_width_8, color);
// 				Draw_string(1,nodot, "/",19, i, font_8_dark, fnt_width_8, color);
// 				Draw_string(1,nodot, "]",24, i, font_8_dark, fnt_width_8, color);
// 				num2str_3_zeros(accum,str_show_temp);												// ������� ������� ������
// 				Draw_string(3,nodot,str_show_temp,16,i, font_8_dark, fnt_width_8, color);
// 				num2str_right(page_size_max,str_show_temp);											// ������ 0
// 				Draw_string (4,nodot,str_show_temp,20,i, font_8_dark, fnt_width_8, color);
			}else
			{
				if((journal_focus+i) < (journal_size))//-1
				{
					Draw_string (31-10,nodot,"                               ",9,i, font_8_dark, fnt_width_8, color);
					num2str_3_zeros(journal_focus+i,str_show_temp);									// ������� ����� ��������
					Draw_string(3,nodot,str_show_temp,1,i, font_8_dark, fnt_width_8, color);
					Draw_string(1,nodot, "[",0, i, font_8_dark, fnt_width_8, color);
					Draw_string(1,nodot, "]",4, i, font_8_dark, fnt_width_8, color);
					num2str_right(eeprom_read_dword(get_page_size(journal_focus+i)),str_show_temp);																// ������ 0
					Draw_string (4,nodot,str_show_temp,5,i, font_8_dark, fnt_width_8, color);		
				}else 	Draw_string (scr_col,nodot,"                               ",0,i, font_8_dark, fnt_width_8, color);
			}

		}// for()
	//show_scrollbar(journal_focus,64, journal_size, scrol_pos, back_color);
};
void scroll_page(unsigned int page_focus, unsigned int page_size, unsigned int page_numb, unsigned char color)	// ��������� �������� �������
{
	unsigned int i;
	unsigned char str_show_temp[4]={"9999"};
	unsigned char dot_pos=1;
	unsigned char status_byte;
	
	if(screen_refresh)
	{
		cls();
		screen_refresh=false;
		//scroll_page(page_choice,ee_page_size,0,back_color);
	};
	for (i=0;i<4;i++) 
	{
		if(i==0)color=front_color; else color=back_color;//focus_raw
 		status_byte = eeprom_read_byte(get_addr(page_numb)+(page_focus+i)*entry_size);
		if(!TestBit(status_byte,6))
		{
 			num2str_right(eeprom_read_word(get_addr(page_numb)+(page_focus+i)*entry_size+1),str_show_temp);								// ������ 0
			if(TestBit(status_byte,4))dot_pos=2; else dot_pos=1;
			Draw_small_num(4,dot_pos,str_show_temp,1,i, font_8_dark, fnt_width_8, color);
			if(TestBit(status_byte,7))
						Draw_string (1,nodot, "-",0, i, font_8_dark, fnt_width_8, color); 				// ����
			else		Draw_string (1,nodot, " ",0, i, font_8_dark, fnt_width_8, color);
	
			Draw_string (2,nodot,"��",scroll_page_mode_pos-3,i, font_8_dark, fnt_width_8, color);
			Draw_string (1,nodot, &mode_name[status_byte&0x07],scroll_page_mode_pos, i, font_8_dark, fnt_width_8, color);
		 }else
		 Draw_string (31,nodot,"                               ",0,i, font_8_dark, fnt_width_8, color);
	}
	show_scrollbar(page_focus,64, page_size, scrol_pos, back_color);	
};
/*_______________������ #6________________*/
void vService_functions( void *pvParameters )
{
	unsigned char ee_pep_numb_temp;
//	signed char itinc=0;
	
	for(;;)
	{
//		

		if(menu_level_choice==2)						// ��������� �������
		{	
//			xSemaphoreTake( xMutex, portMAX_DELAY );
			////BEEP(2);
			if(service_choice==1)						// ���.1 �����
			{
			if( xMutex != NULL )
			{
			if( xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE )
			{				
				scroll_menu_modes(ee_mode_choice);
				if(keypressed_short)					// �������� ������� �� ������!
				{  
					keypressed_short=false;
					//cls();
					////BEEP(2);
					if(butt_old==keydown)
					{
	//					//BEEP(2);
	//					keypressed_short=false;
						if(ee_mode_choice < mode_numb-1)ee_mode_choice++; 
						else ee_mode_choice=0; 
						//scroll_menu_modes(ee_mode_choice-1); 
						}
					else
					if(butt_old==keyup)
					{
	//					//BEEP(2);
	//					keypressed_short=false;
						if(ee_mode_choice > 0) ee_mode_choice--; 
						else ee_mode_choice=mode_numb-1; 
						//scroll_menu_modes(ee_mode_choice-1);
						}
					else
					if(butt_old==keyenter)				// ������ � ��������� �����
					{	
	//					//BEEP(2);
	//					keypressed_short=false; 
						cls();
						//xSemaphoreGive( xMutex );
						//nastr=eeprom_read_byte(NASTR);
						eeprom_write_byte(MODE1+nastr,ee_mode_choice);
						//load_defaults();
						//RPM();
						/*
						///////////////////////////////////////////
						switch (settings_choice)//settings_choice
						{
							case 1: eeprom_write_byte(MODE1,ee_mode_choice);	break;
							case 2: eeprom_write_byte(MODE2,ee_mode_choice);	break;
							case 3: eeprom_write_byte(MODE3,ee_mode_choice);	break;
							case 4: eeprom_write_byte(MODE4,ee_mode_choice);	break;
							case 5: eeprom_write_byte(MODE5,ee_mode_choice);	break;
							case 6: eeprom_write_byte(MODE6,ee_mode_choice);	break;
							case 7: eeprom_write_byte(MODE7,ee_mode_choice);	break;
							case 8: eeprom_write_byte(MODE8,ee_mode_choice);	break;
							case 9: eeprom_write_byte(MODE9,ee_mode_choice);	break;
							case 10:eeprom_write_byte(MODE10,ee_mode_choice);	break;
						};
						///////////////////////////////////////////		
						*/				
						screen_refresh=true;			// ����� �������� ����!
						menu_level_choice=1;			// �������� �������
					}
					else
					if(butt_old==keyrezim)				//
					{ cls();
					//	screen_refresh=true;			// ����� �������� ����!
					//	menu_level_choice=1;			// �������� �������
						
					}
				}//if(keypressed_short)
			xSemaphoreGive(xMutex);
			}//if(xSemaphoreTake)
			}//if( xMutex != NULL )
			}else
			if(service_choice==2)						// ���.7 ���������
			{
			if(xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE)
			{
				scroll_menu_settings(settings_choice);
				if(keypressed_short)					// �������� ������� �� ������!
				{
					keypressed_short=false;
					////BEEP(2); 
					if(butt_old==keydown)
					{
						////BEEP(2);
						keypressed_short=false;
						if(settings_choice < settings_numb-1)settings_choice++; 
						else settings_choice=0; 
					}
					else
					if(butt_old==keyup)
					{
						////BEEP(2);
						keypressed_short=false;
						if(settings_choice > 0) settings_choice--; 
						else settings_choice=settings_numb-1;
					}
					else
					if(butt_old==keyenter)				// ������ � ��������� �����
					{
						screen_refresh=true;			// ����� �������� ����!
						cls();
							
						if(settings_choice==10)			// ���� ����������
						{
							dialogues_choice=5;			// Dlg_5 Auto Power
							screen_refresh=true;		// ����� �������� �����							
							menu_level_choice=3;		// ������ � �������
						}else
						if(settings_choice==11)			// �������
						{
							show_msg_14(front_color);
							 
							delay_in_cycle(delay_8sec);
							cls();								// !!!!!!!!!	
						}else
						if(settings_choice==12)			// �����
						{
							dialogues_choice=6;			// Dlg_6 �����
							screen_refresh=true;		// ����� �������� �����					
							menu_level_choice=3;		// ������ � �������
						}else
						if(settings_choice==13)			// ����
						{
							dialogues_choice=7;			// Dlg_7 ����
							screen_refresh=true;		// ����� �������� �����
							menu_level_choice=3;		// ������ � �������
						}else
						if(settings_choice==14)			// ��������
						{
							dialogues_choice=8;			// Dlg_8 ��������
							screen_refresh=true;		// ����� �������� �����							
							menu_level_choice=3;		// ������ � �������
						}else
						if(settings_choice==15)			// ����� ���� �������� �� ���������
						{
							dialogues_choice=9;			// Dlg_9 ����� �������� �� ���������
							screen_refresh=true;		// ����� �������� �����
							menu_level_choice=3;		// ������ � �������
						}else							// ��������� 1 -9 �������� � ������� � ����� ������
						{	
							nastr=settings_choice;		// 
							eeprom_write_byte(NASTR,nastr);
							//nastr=eeprom_read_byte(NASTR);
							//load_defaults();
							RPM();
							menu_level_choice=1;		// ������ � �������� �������
						};

						////BEEP(2);
					}; //if(butt_old==keyenter)
				}//if(keypressed_short)
			xSemaphoreGive(xMutex);
			}//xMutex
			}//if(service_choice==2)
			else
			if(service_choice==3)						// ���.8 ����������
			{
			if( xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE )
			{

				scroll_menu_calibration(calibration_choice);
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)					// �������� ������� �� ������!
				{
					//cls();
					
					keypressed_short=false;
					if(butt_old==keydown)
					{
						//keypressed_short=false;
						if(calibration_choice < calibration_numb-1) calibration_choice++;
						else calibration_choice=0;
					}else
					if(butt_old==keyup)
					{
						//keypressed_short=false;
						if(calibration_choice > 0) calibration_choice--;
						else calibration_choice=calibration_numb-1;
					
					}else
					if(butt_old==keyenter)
					{
						keypressed_short=false;
						//cls();						//!!!!!!!!!!!!!!!!!!
						////BEEP(2);
						screen_refresh=true;			// ����� �������� �����
						if(calibration_choice==0)		// ���������� ����
						{
							dialogues_choice=dlg_calibration_zero;
						}else
						if(calibration_choice==1)
						{
							dialogues_choice=dlg_calibration_velocity;
						}else
						if(calibration_choice==2)
						{
							dialogues_choice=dlg_calibration_H;
						};
						
						//menu_level_choice=3;			// ������ � �������
						menu_level_choice+=1;
					}
				} // if(keypressed_short)

			xSemaphoreGive(xMutex);
			}//xMutex

			}// if(service_choice==3)
			else
			if(service_choice==4)						// ���.9 ���
			{
			if( xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE )
			{
				scroll_menu_pep(ee_pep_numb);
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)					// �������� ������� �� ������!
				{
				//cls();
					ee_pep_numb_temp=ee_pep_numb;
					keypressed_short=false;
					////BEEP(2);
					if(butt_old==keydown)
					{
					//	keypressed_short=false;
						if(ee_pep_numb < pep_numb-1) ee_pep_numb++;
						else ee_pep_numb=0;
					}else
					if(butt_old==keyup)
					{
					//	keypressed_short=false;
						if(ee_pep_numb > 0) ee_pep_numb--;
						else ee_pep_numb=pep_numb-1;
						
					}else
					if(butt_old==keyenter)
					{
						//keypressed_short=false;
						////BEEP(2);
						
						eeprom_write_byte(DATCH1+(nastr),ee_pep_numb);
						eeprom_write_byte(NUMDATC,ee_pep_numb);
						datch=ee_pep_numb;
						RPM();
						//_delay_ms(1);
						RPR();
						//_delay_ms(1);
						cfgr_load(ee_gain_choice,datch);	// �������� �������� � �������� ���������� �����.	
										
						//load_defaults();
						screen_refresh=true;
						
						dialogues_choice=dlg_calibration_zero;
						cls();							// !!!!!!!!!!!!!!!!!!						
						menu_level_choice=3;			// ������ � �������						
						
					}else ee_pep_numb=ee_pep_numb_temp;
				} // if(keypressed_short)
			xSemaphoreGive(xMutex);
			}//xMutex

			}//if(service_choice==4)
			else
			if(service_choice==5)						// ���.10 ������
			{
				//BEEP(2);BEEP(2);BEEP(2);
			if( xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE )
			{
				scroll_journal(page_choice-1,ee_page_numb+journal_commands,back_color);			// ������� ������ � ������� �� page_choice -1
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)															// �������� ������� �� ������!
				{
					
					////BEEP(2);
					keypressed_short=false;
					if(butt_old==keydown)
					{
						//keypressed_short=false;
						if(page_choice < ee_page_numb+journal_commands){page_choice+=1;}
						
						else page_choice=0;
						//scroll_journal(page_choice,+1);
						
					}else
					if(butt_old==keyup)
					{
						//keypressed_short=false;
						
						if(page_choice > 0){ page_choice-=1;}
						else page_choice=ee_page_numb+journal_commands;
						
						//scroll_journal(page_choice,-1);
						
						
					}else
					if(butt_old==keyenter)
					{
						//keypressed_short=false;
						cls();							//!!!!!!!!!!!!!!!!!!
						////BEEP(2);
						screen_refresh=true;
						//itinc=0;
						
						if(page_choice==(ee_page_numb+1))//ee_page_numb-1 "�������� ������"+1
						{	
							//service_choice=5;
							dialogues_choice=dlg_journal_clear;
							//screen_refresh=true;
							//service_choice=5;
							menu_level_choice+=1;	// ������ � �������
						}
						else 
						if(page_choice==(ee_page_numb+2))//ee_page_numb "����� ��������"+2
						{
								if(ee_page_numb<page_numb_max)ee_page_numb++;
								else 
								{
									ee_page_numb=page_numb_min;	// ������ ��������!!!
								} 
								page_choice=ee_page_numb;						// �������� ���������� �������� ��� �������, ��� ������
								eeprom_write_word(MEMPNT,ee_page_numb);			// ��������� ����� ������� �������� �������
								eeprom_write_word(journal_addr+2,ee_page_numb); // ��������� ���������� �������	
								show_msg_21(front_color);
								delay_in_cycle(delay_3sec);
								cls();							// !!!!!!!!!
								
							
								service_choice=5;
								//menu_level_choice=2;
						}else                                // �������� �������
						{
							ee_page_size=eeprom_read_dword(get_page_size(page_choice));			// ���������� ������� �� i-� ��������
							if(ee_page_size>0)		// ����� ������ ��� �������� �������
							{
								//service_choice=5;
								dialogues_choice=dlg_page_view;
								screen_refresh=true;
    							//menu_level_choice=3;
								menu_level_choice+=1;	// ������  �������
							}
						}
						//menu_level_choice=3;				// ������� ?????????????
					}
				} // if(keypressed_short)
			
			xSemaphoreGive(xMutex);
			}//xMutex
 
			};//if(service_choice==5)			
		
		};
		
		taskYIELD();
		
	}// for
	vTaskDelete(NULL);
}

/*_______________������ #8________________*/
void vConnect( void *pvParameters )
{
	unsigned char dev_name[6]="��-111";
	unsigned char firmware_ver[6]="H02S05";	
	unsigned char k=0,chr;
	unsigned long tmp_save=0;
    unsigned char str_show4[4];

//	unsigned char __attribute__((__progmem__)) * ptr = 0;
		
	for(;;)
	{
//		screen_refresh=true;
		
 		if(TestBit(UCSR0A,RXC0))    //UCSR0A && (1<<RXC0)
 		{
	 		BEEP(2);
			RXBI=USART_Receive();
			taskENTER_CRITICAL();
			if(RXBI=='i')			// ���������
			{
				for (k=0;k<6;k++)
				{
					USART_SEND_Byte(dev_name[k]);
				}
			}else
			if(RXBI=='s')
			{
				send_settings();
			}else
			if(RXBI=='v')			// ������ ��������
			{
				for (k=0;k<6;k++)
				{
					USART_SEND_Byte(firmware_ver[k]);
				}
			}else
			if(RXBI=='w')			// ���������
			{
				tmp_save=eeprom_read_dword(TNAR)/60;						// ������� ��������� � ���������� � �����
				//tmp_save=360;
				num2str_3_zeros(tmp_save,str_show4);
		
				USART_SEND_Byte(str_show4[0]);
				USART_SEND_Byte(str_show4[1]);
				USART_SEND_Byte(str_show4[2]);
				//USART_SEND_Byte(str_show4[3]);
			}else
			if(RXBI=='n')
			{
//				tmp_save=eeprom_read_dword(ZNUM0);							// ������� ����� �������
//	num2str_right(tmp_save,str_show4);
// 	eeprom_write_byte (ZNUM0,zav_num>>24);
// 	eeprom_write_byte (ZNUM1,zav_num>>16); 
//	eeprom_write_byte (ZNUM2,zav_num>>8);
//	eeprom_write_byte (ZNUM3,zav_num);
// 
				chr=eeprom_read_byte(ZNUM0);
				USART_SEND_Byte(chr);
				chr=eeprom_read_byte(ZNUM1);
				USART_SEND_Byte(chr);
				chr=eeprom_read_byte(ZNUM2);
				USART_SEND_Byte(chr);
				chr=eeprom_read_byte(ZNUM3);
				USART_SEND_Byte(chr);
			}else
			if(RXBI=='a')			// �������� �������� �����
			{
				RXBI=USART_Receive();
				eeprom_write_byte (ZNUM0,RXBI);
				BEEP(2);
				RXBI=USART_Receive();
				eeprom_write_byte (ZNUM1,RXBI);
				BEEP(2);
				RXBI=USART_Receive();
				eeprom_write_byte (ZNUM2,RXBI);
				BEEP(2);
				RXBI=USART_Receive();
				eeprom_write_byte (ZNUM3,RXBI);
				BEEP(2);
			}else
			if(RXBI=='k')			// ��������� �������
			{
				send_contents();
			}else
			if(RXBI=='j')			// ���������� �������
			{
				send_journal();
			}else
// 			if(RXBI=='p')
// 			{
// 				ptr=0;
// 				for(k=0;k<3;k++)
// 				{
// 						SPMCSR = (1<<SIGRD) | (1<<SPMEN);
// 						USART_SEND_Byte(pgm_read_byte(ptr));
// 						ptr+=2;
// 				}
// 			}else
			{
				USART_SEND_Byte(RXBI);		// ����������� �������, ���������� �����
			}
			taskEXIT_CRITICAL();
 		}
 		taskYIELD();
	}// for
	vTaskDelete(NULL);
}
/*_______________������ #7________________*/
void vMain_functions( void *pvParameters )
{
	unsigned int temp_main_value=long_max; //long
	portTickType xLastExecutionTime; //delay_acustic_lost;
	signed int nonius_temp;
	unsigned char color=back_color;
	unsigned char dot_pos=1;
	unsigned long acont_cnt=0;	// ������� �������� ���������� ��
	unsigned char acont_inc=1;
	unsigned char status_byte=0;
	unsigned long psize;
	xLastExecutionTime = xTaskGetTickCount();
	
	for(;;)
	{

		if(menu_level_choice==1)					// �������� �������
		{
			//____________________________________________________________________________//
			if(ee_mode_choice==0)					// ���.2 ���������
			{	
			////////////////////////////////////////////////////////////////////////////////////////////
			if(xMutex != NULL)
			{
				if( xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE )
				{
				if(screen_refresh)
				{
//writeWEE(0,11);
					cls();
					RPM();
					
					show_no_sound(ee_sound_choice);
				
					Draw_string (2,nodot,"��",(measure_pos+4)*2,2, font_8_dark, 8, back_color);
					
					//pgm_read_byte_far(&str[i]);pep_list[9+ee_mode_choice]
					
					Draw_string_left(menu_pep_width, pep_list[9+ee_pep_numb] , 0,0, font_8_dark, 8, back_color);// pgm_read_byte(&pep_list[9+ee_pep_numb])
					
					//strcpy_P(str_show, (PGM_P)pgm_read_word(&(string_table[i])));
					
					//Draw_string (menu_pep_width,nodot, pep_list0, pep_pos-1,0, font_8_dark, 8, back_color);//menu_pep_line0
					Draw_string (2,nodot,"V=",  velocity_pos-2,velocity_raw, font_8_dark, 8, back_color);
				//	ee_velocity_choice=eeprom_read_word(VEL1+(nastr)*2); 
				//	vel=ee_velocity_choice;
				
					num2str_left(ee_velocity_choice,str_show);//0x270F
					Draw_string (4,nodot,str_show,  velocity_pos,velocity_raw, font_8_dark, 8, back_color);
					Draw_string (3,nodot,"�/�",  velocity_pos+4,velocity_raw, font_8_dark, 8, back_color);

					//num2str_zeros(ee_page_numb,str_show,number_offset);
					num2str_3_zeros(ee_page_numb,str_show);	
					Draw_string (3,nodot,str_show,journal_pos+3,journal_raw, font_8_dark, 8, back_color);		//14
					Draw_string (1,nodot,"[",journal_pos+2,journal_raw, font_8_dark, 8, back_color);
					Draw_string (1,nodot,"]",journal_pos+6,journal_raw, font_8_dark, 8, back_color);
					num2str_right(ee_page_size,str_show);
					Draw_string (4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, back_color);	//14

						num2str_right(main_value,str_show);
						if(main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
						Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
/*
					batt_refresh=true;
					battery_status();							// ���������� ��������� �������
					show_battery(batt_min,back_color);
					//batt_refresh=false;*/

// 							read_byte=readWEE(0);
// 							num2str_left(read_byte,str_show);
// 							Draw_string (4,nodot,str_show, 4,1, font_8_dark, 8, back_color);

				screen_refresh=false;
				}
				////////////////////////////////////////////////////////////////////////////////////  */
				/////////_________________________���������___________________________________
//					show_main_value=true;
//					num2str_right(main_value,str_show);
//					Draw_big_font (4,1,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
//taskENTER_CRITICAL();

					main_value=IZMERENIE(0x01,vel,datch,nastr,amplif,voltp,calibr,mf,mp,tf);
			
					//if(!(PINH & (1<<acontpin))) //BEEP(2);
					//num2str_right(calibr,str_show);
					//Draw_string (4,nodot,str_show,journal_pos+3,2, font_8_dark, 8, back_color);		//14
					if(PINH & (1<<acontpin))					// ��������� �������� �� ������ ����� ���������� ��
					{
						num2str_right(main_value,str_show);
						if(main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
						Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
					};
//taskEXIT_CRITICAL();				
					//xSemaphoreTake(xDisplay, portMAX_DELAY);					
					//show_msg_20(back_color);
					batt_refresh=true;
					battery_status();							// ���������� ��������� �������
					show_battery(batt_percent,back_color);
					if(entry_refresh)							// ���������� ���������� ������ �� �������� �������
					{
																// ��������� � ������
 						status_byte|=ee_mode_choice&0x07;
 						if(dot_pos==2)SetBit(status_byte,4); else SetBit(status_byte,5);		// ��������� �����
//						SetBit(status_byte,7);					// ����		
					  	eeprom_write_byte(get_addr(ee_page_numb)+ee_page_size*entry_size,status_byte);
 						eeprom_write_word(get_addr(ee_page_numb)+ee_page_size*entry_size+1,main_value);
						psize=eeprom_read_dword(get_addr(ee_page_numb));
						psize+=1;
						eeprom_write_dword(get_addr(ee_page_numb),psize);						// ����������� ������� ������� �� ��������
						if(ee_page_size<page_size_max)ee_page_size++; else ee_page_size=0;		// ��������� ������
						eeprom_write_dword(get_page_size(ee_page_numb),ee_page_size);			// ���������� ������� �� i-� ��������

						num2str_right(ee_page_size,str_show);
						Draw_string(4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, front_color);	//14
						delay_in_cycle(delay_05sec);	//delay_1sec
						Draw_string(4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, back_color);	//14

						entry_refresh=false;
					}
				/////////___________________________________________________________
				
				if(keypressed_short)						// �������� ������� �� ������!
				{
					////BEEP(2);
					if(butt_old==keyup || butt_old==keydown || butt_old==keyenter)
					{
						keypressed_short=false;						
						show_msg_5(back_color);
						delay_in_cycle(delay_3sec);
						//vTaskDelay(1000 / portTICK_RATE_MS);
						cls();								// !!!!!!!!!
						screen_refresh=true;				// ��������� �����
					}
				};//if(keypressed_short)
				
// 				if(butt_old==keyrezim)				
// 				{ cls();}

				xSemaphoreGive(xMutex);
				}//xMutex
				}//if( xMutex != NULL )
			}else         //____________________________________________________________________________//
			if(ee_mode_choice==1)							// ���.3 ������������
			{
			if( xMutex != NULL )
			{

				if( xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE )
				{

				/////////////////////////////////////////////////////////////////////////////////////
				if(screen_refresh)
				{
/*
					battery_status();							// ���������� ��������� �������
					show_battery(batt_percent,back_color);
					//batt_refresh=false;*/
					cls();
					RPM();
					Draw_string (2,nodot,"MM",(measure_pos+4)*2,2, font_8_dark, 8, back_color);
		
					show_no_sound(ee_sound_choice);
	//				Draw_string (menu_pep_width,nodot,menu_pep_line0,  pep_pos-1,0, font_8_dark, 8, back_color);
					Draw_string_left(menu_pep_width, pep_list[9+ee_pep_numb] , 0,0, font_8_dark, 8, back_color);// pgm_read_byte(&pep_list[9+ee_pep_numb])

					Draw_string (2,nodot,"V=", velocity_pos-2,velocity_raw, font_8_dark, 8, back_color);
					num2str_left(ee_velocity_choice,str_show);
					Draw_string (4,nodot,str_show, velocity_pos,velocity_raw, font_8_dark, 8,back_color);
					Draw_string (3,nodot,"�/�", velocity_pos+4,velocity_raw, font_8_dark, 8, back_color);
				
					Draw_string (4,nodot,"���=", measure_pos+18,2, font_8_dark, 8, back_color);
						num2str_right(main_value,str_show);													// ��� ����� ���������� 0
						if(main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
						Draw_small_num(4,dot_pos,str_show,  measure_pos+22,2, font_8_dark, 8, front_color);
						//if(main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
						Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
					
					num2str_3_zeros(ee_page_numb,str_show);
					Draw_string (3,nodot,str_show,journal_pos+3,journal_raw, font_8_dark, 8, back_color);		//14
					Draw_string (1,nodot,"[",journal_pos+2,journal_raw, font_8_dark, 8, back_color);
					Draw_string (1,nodot,"]",journal_pos+6,journal_raw, font_8_dark, 8, back_color);
					num2str_right(ee_page_size,str_show);
					Draw_string (4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, back_color);	//14*/
				screen_refresh=false;
				} //if(screen_refresh)
				////////////////////////////////////////////////////////////////////////////////////
				/////////____________________________________________________________
				
				main_value=IZMERENIE(0x01,vel,datch,nastr,amplif,voltp,calibr,mf,mp,tf); //mode

				
				if(PINH & (1<<acontpin))					// ���� ��! ���������� ������� ��������	
				{
					acont_inc=1;
					if(main_value < temp_main_value) temp_main_value=main_value;	// ���������� �������

					num2str_right(main_value,str_show);
					if(main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
					Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);

					num2str_right(temp_main_value,str_show);
					if(temp_main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
					Draw_small_num(4,dot_pos,str_show,  measure_pos+22,2, font_8_dark, 8, front_color);
				}else 
				{
					acont_cnt+=acont_inc;
					//BEEP(2);
				
				
					if(acont_cnt>acont_delay)					// �� ������ �� acont_delay 
					{
						main_value=temp_main_value;				// ������� ������� � ������� ��������
						temp_main_value=int_max;//long_max;
					
						num2str_right(main_value,str_show);
						if(main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
						if(main_value<temp_main_value)			// ��� �� ������� �� ���������� 0xFFFFFFFF;
						{
							Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
							BEEP(2);
						}
 						num2str_right(0,str_show);
 						dot_pos=1;
 						Draw_small_num(4,dot_pos,str_show,  measure_pos+22,2, font_8_dark, 8, front_color);
						acont_cnt=0;
						acont_inc=0;
					}
				}

  
// 				if(!(PINH & (1<<acontpin)))
// 				{
// 					main_value=temp_main_value;
// 					if((xTaskGetTickCount()-delay_acustic_lost)>0xff){delay_acustic_lost=xTaskGetTickCount();temp_main_value=long_max;};
// 				}

					batt_refresh=true;
					battery_status();							// ���������� ��������� �������
					show_battery(batt_percent,back_color);

					if(entry_refresh)							// ���������� ���������� ������ �� �������� �������
					{
 						status_byte|=ee_mode_choice&0x07;
 						if(dot_pos==2)SetBit(status_byte,4); else SetBit(status_byte,5);		// ��������� �����
 						//						SetBit(status_byte,7);					// ����
 						eeprom_write_byte(get_addr(ee_page_numb)+ee_page_size*entry_size,status_byte);
 						eeprom_write_word(get_addr(ee_page_numb)+ee_page_size*entry_size+1,main_value);

 						if(ee_page_size<page_size_max)ee_page_size++; else ee_page_size=0;		// ��������� ������
 						eeprom_write_dword(get_page_size(ee_page_numb),ee_page_size);			// ���������� ������� �� i-� ��������


						num2str_right(ee_page_size,str_show);
						Draw_string(4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, front_color);	//14
						delay_in_cycle(delay_05sec);	//delay_1sec
						Draw_string(4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, back_color);	//14
						entry_refresh=false;
					}

				   /////////___________________________________________________________
				
				if(keypressed_short)							// �������� ������� �� ������!
				{
					if(butt_old==keyup || butt_old==keydown || butt_old==keyenter)
					{
						keypressed_short=false;
						show_msg_5(back_color);
						delay_in_cycle(delay_3sec);
						cls();									// !!!!!!!!!
						screen_refresh=true;					// ��������� �����
					}
				};
				xSemaphoreGive(xMutex);
			}//xMutex
			}//if( xMutex != NULL )	
			}else         //____________________________________________________________________________//
			if(ee_mode_choice==2)								// ���.6 �����������
			{
			if( xMutex != NULL )
			{

				if( xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE )
				{
	
				/////////////////////////////////////////////////////////////////////////////////////
				if(screen_refresh)
				{
/*
						batt_refresh=true;
						battery_status();						// ���������� ��������� �������
						show_battery(batt_percent,back_color);
						//batt_refresh=false;*/
						cls();
						RPM();
						Draw_string (2,nodot,"MM",(measure_pos+4)*2,2, font_8_dark, 8, back_color);
		
						show_no_sound(ee_sound_choice);
				
//						Draw_string (menu_pep_width,nodot,menu_pep_line0,  pep_pos-1,0, font_8_dark, 8, back_color);
						Draw_string_left(menu_pep_width, pep_list[9+ee_pep_numb] , 0,0, font_8_dark, 8, back_color);// pgm_read_byte(&pep_list[9+ee_pep_numb])

						Draw_string (2,nodot,"V=",  velocity_pos-2,velocity_raw, font_8_dark, 8, back_color);
						num2str_left(ee_velocity_choice,str_show);//0x270F
						Draw_string (4,nodot,str_show,  velocity_pos,velocity_raw, font_8_dark, 8, back_color);
						Draw_string (3,nodot,"�/�",  velocity_pos+4,velocity_raw, font_8_dark, 8, back_color);

						Draw_string (4,nodot," ��=",  measure_pos+18,2, font_8_dark, 8, back_color);
						Draw_string (4,nodot," ��=",  measure_pos+18,1, font_8_dark, 8, back_color);
						
						num2str_right(ee_grade_lowlim_choice,str_show);
						if(ee_grade_lowlim_choice<range_switching_threshold)dot_pos=1; else dot_pos=2;
						Draw_small_num(4,dot_pos,str_show,  measure_pos+22,2, font_8_dark, 8, front_color);
						//Draw_string (4,2,str_show,  measure_pos+24,1, font_8_dark, 8, front_color);
						
						num2str_right(ee_grade_uplim_choice,str_show);
						if(ee_grade_uplim_choice<range_switching_threshold)dot_pos=1; else dot_pos=2;
						//Draw_string (4,2,str_show,  measure_pos+24,2, font_8_dark, 8, front_color);
						Draw_small_num(4,dot_pos,str_show,  measure_pos+22,1, font_8_dark, 8, front_color);
						
						num2str_3_zeros(ee_page_numb,str_show);
						Draw_string (3,nodot,str_show,journal_pos+3,journal_raw, font_8_dark, 8, back_color);		//14
						Draw_string (1,nodot,"[",journal_pos+2,journal_raw, font_8_dark, 8, back_color);
						Draw_string (1,nodot,"]",journal_pos+6,journal_raw, font_8_dark, 8, back_color);
						num2str_right(ee_page_size,str_show);
						Draw_string (4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, back_color);	//14*/
					screen_refresh=false;
				} //if(screen_refresh)

				/////////____________________________________________________________

				//				num2str_right((unsigned int)main_value,str_show);
				//				Draw_big_font (4,big_dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
				
				//main_value=RAZBRAKOVKA (mode,vel,datch,nastr,amplif,voltp,calibr,RAZBH,RAZBL,mf,mp,tf);
				//main_value=RAZBRAKOVKA (0x01,ee_velocity_choice,ee_pep_numb,settings_choice,ee_gain_choice,voltp,calibr,ee_grade_uplim_choice,ee_grade_lowlim_choice,mf,mp,tf);
				main_value=IZMERENIE(0x01,vel,datch,nastr,amplif,voltp,calibr,mf,mp,tf);
				
				/*
				PORTB &= ~_BV(RES); /// ������� �� ������ ����
				//main_value =  calculmes(calibr,ee_velocity_choice,ee_pep_numb); 
				
				main_value =  calculmes(calibr,vel,datch); 
				
				PORTB |= _BV(RES); ///  ����� ��������� ���c - ���������� �����������
				*/
				
				//if(!(PINH & (1<<acontpin))) //BEEP(2);
				//num2str_right(calibr,str_show);
				//Draw_string (4,nodot,str_show,journal_pos+3,2, font_8_dark, 8, back_color);		//14

				num2str_right(main_value,str_show);
				if(main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
				
				if(main_value>0)
				{
					if (main_value<ee_grade_lowlim_choice || main_value>ee_grade_uplim_choice)
					{
						//Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, inverse_color);//front_color
						color=inverse_color;
						BEEP(3);
					}else color=front_color;
				}else color=front_color;
				
				Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, color);//front_color
				

				/*		
					num2str_left(ee_grade_uplim_choice,str_show);
					Draw_string (4,1,str_show,  measure_pos+25,1, font_8_dark, 8, front_color);
						
					num2str_left(ee_grade_lowlim_choice,str_show);
					Draw_string (4,1,str_show,  measure_pos+25,2, font_8_dark, 8, front_color);
				*/
					batt_refresh=true;
					battery_status();							// ���������� ��������� �������
					show_battery(batt_percent,back_color);

					if(entry_refresh)							// ���������� ���������� ������ �� �������� �������
					{
 						status_byte|=ee_mode_choice&0x07;
 						if(dot_pos==2)SetBit(status_byte,4); else SetBit(status_byte,5);		// ��������� �����
 						//						SetBit(status_byte,7);					// ����
 						eeprom_write_byte(get_addr(ee_page_numb)+ee_page_size*entry_size,status_byte);
 						eeprom_write_word(get_addr(ee_page_numb)+ee_page_size*entry_size+1,main_value);

 						if(ee_page_size<page_size_max)ee_page_size++; else ee_page_size=0;		// ��������� ������
 						eeprom_write_dword(get_page_size(ee_page_numb),ee_page_size);			// ���������� ������� �� i-� ��������


						num2str_right(ee_page_size,str_show);
						Draw_string(4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, front_color);	//14
						delay_in_cycle(delay_05sec);	//delay_1sec
						Draw_string(4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, back_color);	//14
						entry_refresh=false;
					}

	//			battery_status();							// ���������� ��������� �������
	//			show_battery(batt_percent,back_color);
				
				/////////___________________________________________________________
				
					////////////////////////////////////////////////////////////////////////////////////
					if(keypressed_short)						// �������� ������� �� ������!
					{
						keypressed_short=false;
						////BEEP(2);
						if(butt_old==keyup || butt_old==keydown)
						{
							show_msg_5(back_color);
							delay_in_cycle(delay_3sec);
							cls();								// !!!!!!!!!
							screen_refresh=true;					// ��������� �����
						}else
						if(butt_old==keyenter)
						{
							cls();							//!!!!!!!!!!!!!!!!!!
							dialogues_choice=3;				// dlg_3 ������� ������ ������
							screen_refresh=true;					// ��������� �����
							menu_level_choice=3;
						}
					}; // if(keypressed_short)
			
			xSemaphoreGive(xMutex);
			}//xMutex
			}//if( xMutex != NULL )		
			}else         //____________________________________________________________________________//
			if(ee_mode_choice==3)					// ���.5 ����������
			{
			if( xMutex != NULL )
			{

				if( xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE )
				{

				/////////////////////////////////////////////////////////////////////////////////////
				if(screen_refresh)
				{
	/*				batt_refresh=true;
					battery_status();							// ���������� ��������� �������
					show_battery(batt_percent,back_color);
					//batt_refresh=false;*/
				
					cls();
					RPM();
// 					num2str_right(31,str_show);
// 					Draw_big_font (4,nodot,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);

					Draw_string (2,nodot,"MM",(measure_pos+4)*2,2, font_8_dark, 8, back_color);
					show_no_sound(ee_sound_choice);
					show_acoustic(clear_color);
	//				Draw_string (menu_pep_width,nodot,menu_pep_line0,  pep_pos-1,0, font_8_dark, 8, back_color);
					Draw_string_left(menu_pep_width, pep_list[9+ee_pep_numb] , 0,0, font_8_dark, 8, back_color);	// pgm_read_byte(&pep_list[9+ee_pep_numb])

					Draw_string (2,nodot,"V=",  velocity_pos-2,velocity_raw, font_8_dark, 8, back_color);
					num2str_left(ee_velocity_choice,str_show);//0x270F
					Draw_string (4,nodot,str_show,  velocity_pos,velocity_raw, font_8_dark, 8, back_color);
					Draw_string (3,nodot,"�/�",  velocity_pos+4,velocity_raw, font_8_dark, 8, back_color);
		

						num2str_right(ee_base_level_choice,str_show);
						if(ee_base_level_choice<range_switching_threshold)dot_pos=1; else dot_pos=2;
						Draw_small_num(4,dot_pos,str_show,  measure_pos+22,2, font_8_dark, 8, front_color);
					Draw_string (4,nodot," ��=",  measure_pos+18,2, font_8_dark, 8, back_color);
					//Draw_string (4,nodot,"��",  measure_pos+24,2, font_8_dark, 8, back_color);				

						main_value=0;						// ������� ������� 0
// 						if(main_value<ee_base_level_choice)
// 						{	main_value=ee_base_level_choice-main_value;
// 							Draw_big_font (1,nobigdot,"-",measure_pos-1,measure_raw, big_font_16, 16, front_color);
// 						}
// 						else
// 						{
// 							main_value=main_value-ee_base_level_choice;
// 							Draw_big_font (1,nobigdot," ",measure_pos-1,measure_raw, big_font_16, 16, front_color);
// 						}
						
						num2str_right(main_value,str_show);
						if(main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
						Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);




					num2str_3_zeros(ee_page_numb,str_show);
					Draw_string (3,nodot,str_show,journal_pos+3,journal_raw, font_8_dark, 8, back_color);			//14
					Draw_string (1,nodot,"[",journal_pos+2,journal_raw, font_8_dark, 8, back_color);
					Draw_string (1,nodot,"]",journal_pos+6,journal_raw, font_8_dark, 8, back_color);
					num2str_right(ee_page_size,str_show);
					Draw_string (4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, back_color);			//14*/
				screen_refresh=false;
			} //if(screen_refresh)

				/////////____________________________________________________________
					main_value=IZMERENIE(0x01,vel,datch,nastr,amplif,voltp,calibr,mf,mp,tf);

					if(PINH & (1<<acontpin))					// ��������� �������� �� ������ ����� ���������� ��
					{
						if(main_value<ee_base_level_choice)
						{	main_value=ee_base_level_choice-main_value;
							Draw_big_font (1,nobigdot,"-",measure_pos-1,measure_raw, big_font_16, 16, front_color);
							SetBit(status_byte,7);
						}
						else
						{
							main_value=main_value-ee_base_level_choice;
							Draw_big_font (1,nobigdot," ",measure_pos-1,measure_raw, big_font_16, 16, front_color);
							ResetBit(status_byte,7);
						}
				
						num2str_right(main_value,str_show);
						if(main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
						Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);	
					};
					
					batt_refresh=true;
					battery_status();							// ���������� ��������� �������
					show_battery(batt_percent,back_color);

					if(entry_refresh)							// ���������� ���������� ������ �� �������� �������
					{
 						status_byte|=ee_mode_choice&0x07;
 						if(dot_pos==2)SetBit(status_byte,4); else SetBit(status_byte,5);		// ��������� �����
 						//						SetBit(status_byte,7);					// ����
 						eeprom_write_byte(get_addr(ee_page_numb)+ee_page_size*entry_size,status_byte);
 						eeprom_write_word(get_addr(ee_page_numb)+ee_page_size*entry_size+1,main_value);

 						if(ee_page_size<page_size_max)ee_page_size++; else ee_page_size=0;		// ��������� ������
 						eeprom_write_dword(get_page_size(ee_page_numb),ee_page_size);			// ���������� ������� �� i-� ��������

						num2str_right(ee_page_size,str_show);
						Draw_string(4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, front_color);	//14
						delay_in_cycle(delay_05sec);	//delay_1sec
						Draw_string(4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, back_color);	//14

						entry_refresh=false;
					}
							
				/////////___________________________________________________________

					////////////////////////////////////////////////////////////////////////////////////
					if(keypressed_short)						// �������� ������� �� ������!
					{
						keypressed_short=false;
						////BEEP(2);
						if(butt_old==keyup || butt_old==keydown)
						{
							show_msg_5(back_color);
							delay_in_cycle(delay_3sec);
							cls();								// !!!!!!!!!
						}else
						if(butt_old==keyenter)
						{
							cls();								//!!!!!!!!!!!!!!!!!!
							dialogues_choice=2;					// dlg_2 ������� ������� �������
							//BEEP(2);
							screen_refresh=true;				// ��������� �����
							menu_level_choice=3;
						}
					}; // if(keypressed_short)
			xSemaphoreGive(xMutex);
			}//xMutex
			}//if( xMutex != NULL )
			}else         //____________________________________________________________________________//
			if(ee_mode_choice==4)					// ���.4 ������
			{
			if( xMutex != NULL )
			{
				if( xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE )
				{
				/////////////////////////////////////////////////////////////////////////////////////
				if(screen_refresh)
				{
/*					batt_refresh=true;
					battery_status();							// ���������� ��������� �������
					show_battery(batt_percent,back_color);
					//batt_refresh=false;*/
					cls();
					RPM();
					show_no_sound(ee_sound_choice);
	//				Draw_string (menu_pep_width,nodot, menu_pep_line0, pep_pos-1,0, font_8_dark, 8, back_color);
					Draw_string_left(menu_pep_width, pep_list[9+ee_pep_numb] , 0,0, font_8_dark, 8, back_color);// pgm_read_byte(&pep_list[9+ee_pep_numb])

					
					Draw_string (2,nodot,"V=",  velocity_pos-2,velocity_raw, font_8_dark, 8, back_color);
					num2str_left(ee_velocity_choice,str_show);
					Draw_string (4,nodot,str_show,  velocity_pos,velocity_raw, font_8_dark, 8, back_color);
					Draw_string (3,nodot,"�/�",  velocity_pos+4,velocity_raw, font_8_dark, 8, back_color);
					
					Draw_string (2,nodot,"$=",  measure_pos+19,2, font_8_dark, 8, back_color);
					Draw_string (2,nodot,"MM",measure_pos+14,2, font_8_dark, 8, back_color);
					//////////////
					nonius_temp=ee_nonius_choice-nonius_half_range;
					
					
//  				itoa(nonius_temp,str_show,10);
//  				Draw_string (4,nodot,str_show,velocity_pos+10,velocity_raw, font_8_dark, 8, back_color);
					
					
					if(nonius_temp<0)
					{
						nonius_temp=abs(nonius_temp);
						//Draw_big_font (1,nobigdot,"-",measure_pos-1,measure_raw, big_font_16, 16, front_color);
						Draw_string(1,nodot,"-",measure_pos+21,2, font_8_dark, 8, back_color);
					}else
					Draw_string(1,nodot,"+",measure_pos+21,2, font_8_dark, 8, back_color);

						num2str_right(nonius_temp,str_show);
						if(nonius_temp<range_switching_threshold)dot_pos=1; else dot_pos=2;
						//Draw_small_num(4,dot_pos,str_show,  measure_pos+24,2, font_8_dark, 8, back_color);
					
					//////////////


					//////////////	
					num2str_right(main_value,str_show);
					if(main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
					Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
					
				//	num2str_left(ee_nonius_choice,str_show);
				//	Draw_string (4,nodot,str_show,  measure_pos+20,2, font_8_dark, 8, back_color);
					//Draw_string (4,nodot,"��",  measure_pos+24,2, font_8_dark, 8, back_color);

					num2str_3_zeros(ee_page_numb,str_show);
					Draw_string (3,nodot,str_show,journal_pos+3,journal_raw, font_8_dark, 8, back_color);		//14
					Draw_string (1,nodot,"[",journal_pos+2,journal_raw, font_8_dark, 8, back_color);
					Draw_string (1,nodot,"]",journal_pos+6,journal_raw, font_8_dark, 8, back_color);
					num2str_right(ee_page_size,str_show);
					Draw_string (4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, back_color);	//14*/
				screen_refresh=false;
				} //if(screen_refresh)

				/////////____________________________________________________________
				main_value=IZMERENIE(0x01,vel,datch,nastr,amplif,voltp,calibr,mf,mp,tf);
				
				//main_value = calculmes(calibr,vel,datch,nastr);
// 				if(main_value >abs(ee_nonius_choice-nonius_half_range))
// 				{
// 					main_value=main_value+ee_nonius_choice-nonius_half_range;
// 					if(main_value<0)main_value=0;
// 				}else main_value=0;  
				nonius_temp=ee_nonius_choice-nonius_half_range;
				if(nonius_temp<0)
				{
					if(main_value<abs(nonius_temp))				// �������� ������ �������, ���� �������� ���
					{
						main_value=0; 
						if( PINH & (1<<acontpin)) {color=front_color; BEEP(2);}
						else color=back_color;
					}
				}else                                           // ��� ���������, ���������� ������ �� ������
				{
					main_value=main_value+nonius_temp;
				}


				num2str_right(abs(nonius_temp),str_show);
				if(nonius_temp<range_switching_threshold)dot_pos=1; else dot_pos=2;
				Draw_small_num(4,dot_pos,str_show,  measure_pos+22,2, font_8_dark, 8, color);

				if(PINH & (1<<acontpin))					// ��������� �������� �� ������ ����� ���������� ��
				{
					num2str_right(main_value,str_show);
					if(main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
					Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
				}

				batt_refresh=true;
				battery_status();							// ���������� ��������� �������
				show_battery(batt_percent,back_color);

				if(entry_refresh)							// ���������� ���������� ������ �� �������� �������
				{
 						status_byte|=ee_mode_choice&0x07;
 						if(dot_pos==2)SetBit(status_byte,4); else SetBit(status_byte,5);		// ��������� �����
 						//						SetBit(status_byte,7);					// ����
 						eeprom_write_byte(get_addr(ee_page_numb)+ee_page_size*entry_size,status_byte);
 						eeprom_write_word(get_addr(ee_page_numb)+ee_page_size*entry_size+1,main_value);

 						if(ee_page_size<page_size_max)ee_page_size++; else ee_page_size=0;		// ��������� ������
 						eeprom_write_dword(get_page_size(ee_page_numb),ee_page_size);			// ���������� ������� �� i-� ��������

					num2str_right(ee_page_size,str_show);
					Draw_string(4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, front_color);	//14
					delay_in_cycle(delay_05sec);	//delay_1sec
					Draw_string(4,nodot,str_show, journal_pos+7,journal_raw, font_8_dark, 8, back_color);	//14
					entry_refresh=false;
				}
				/////////___________________________________________________________
					////////////////////////////////////////////////////////////////////////////////////
					if(keypressed_short)						// �������� ������� �� ������!
					{

						//BEEP(2);
						if(butt_old==keyup || butt_old==keydown)
						{
							keypressed_short=false;
							show_msg_5(back_color);
							delay_in_cycle(delay_3sec);
							cls();								// !!!!!!!!!
						}else
						if(butt_old==keyenter)
						{
							keypressed_short=false;
							cls();							//!!!!!!!!!!!!!!!!!!
							dialogues_choice=1;				// ������� ��������
							//BEEP(2);
							screen_refresh=true;					// ��������� �����
							menu_level_choice=3;
						}
					}; // if(keypressed_short)				
				xSemaphoreGive(xMutex);
			}//xMutex
			}//if( xMutex != NULL )
			}//if(ee_mode_choice==4)
			
		 }else //if(menu_level_choice==1)
		 {
		//	 vTaskDelay(func_delay / portTICK_RATE_MS);
		 }
		 taskYIELD(); 
		 //vTaskDelayUntil(xLastExecutionTime, 900 / portTICK_RATE_MS);
		 
	}//for(;;);
	vTaskDelete(NULL);
}

//______________________ ������ �������� ___________________

void show_dlg_1(unsigned char color)
{
	signed int nonius_temp;
	if(screen_refresh)
	{
		Draw_string (dlg_1_width,nodot, dlg_1_line0 , dlg_1_pos, 0, font_8_dark, fnt_width_8, color);
		Draw_string (dlg_1_width,nodot, dlg_1_line1 , dlg_1_pos, 1, font_8_dark, fnt_width_8, color);
		Draw_string (dlg_1_width,nodot, dlg_1_line2 , dlg_1_pos, 2, font_8_dark, fnt_width_8, color);
		Draw_string (dlg_1_width,nodot, dlg_1_line3 , dlg_1_pos, 3, font_8_dark, fnt_width_8, color);

		num2str_right(nonius_half_range,str_show);
		if(nonius_half_range<range_switching_threshold)dot_pos=1; else dot_pos=2;
		Draw_small_num(4,dot_pos,str_show,  measure_pos+21,2, font_8_dark, 8, back_color);
		Draw_string(1,nodot,"-",measure_pos+21,2, font_8_dark, 8, back_color);

		num2str_right(nonius_half_range,str_show);
		if(nonius_half_range<range_switching_threshold)dot_pos=1; else dot_pos=2;
		Draw_small_num(4,dot_pos,str_show,  measure_pos+21,1, font_8_dark, 8, back_color);
		Draw_string(1,nodot,"+",measure_pos+21,1, font_8_dark, 8, back_color);
	}
	screen_refresh=false;
	nonius_temp=ee_nonius_choice-nonius_half_range;
	if(nonius_temp<0)
	{
		nonius_temp=abs(nonius_temp);
		Draw_big_font (1,nobigdot,"-",measure_pos-1,measure_raw, big_font_16, 16, front_color);
	}else
		Draw_big_font (1,nobigdot,"+",measure_pos-1,measure_raw, big_font_16, 16, front_color);
	num2str_right(nonius_temp,str_show);
	//Draw_big_font (4,big_dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
	Draw_big_num(4,1,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
	show_scrollbar(ee_nonius_max-ee_nonius_choice,32,ee_nonius_max+1,scrol_pos,back_color);
}
// ______________________ ������ ������� ������� ___________________
void show_dlg_2(unsigned char color)
{
	if(screen_refresh)
	{
		Draw_string (dlg_2_width,nodot, dlg_2_line0 , dlg_2_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_2_width,nodot, dlg_2_line1 , dlg_2_pos, 1, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_2_width,nodot, dlg_2_line2 , dlg_2_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_2_width,nodot, dlg_2_line3 , dlg_2_pos, 3, font_8_dark, fnt_width_8, back_color);

		num2str_right(0,str_show);
		if(0<range_switching_threshold)dot_pos=1; else dot_pos=2;
		Draw_small_num(4,dot_pos,str_show,  measure_pos+21,2, font_8_dark, 8, back_color);
		num2str_right(uplim,str_show);
		if(uplim<range_switching_threshold)dot_pos=1; else dot_pos=2;
		Draw_small_num(4,dot_pos,str_show,  measure_pos+21,1, font_8_dark, 8, back_color);
		
	}screen_refresh=false;
	num2str_right(ee_base_level_choice,str_show);
	if(ee_base_level_choice<range_switching_threshold)dot_pos=1; else dot_pos=2;
	Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
	show_scrollbar(ee_base_level_max-ee_base_level_choice,32,ee_base_level_max-ee_base_level_min+1,scrol_pos,back_color);//-ee_base_level_min
}
void show_dlg_3(unsigned char color)		// ������ ������
{
	unsigned char dot_pos=1;
	if(screen_refresh)
	{
		Draw_string (dlg_3_width,nodot, dlg_3_line0 , dlg_3_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_3_width,nodot, dlg_3_line1 , dlg_3_pos, 1, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_3_width,nodot, dlg_3_line2 , dlg_3_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_3_width,nodot, dlg_3_line3 , dlg_3_pos, 3, font_8_dark, fnt_width_8, back_color);

		num2str_right(lowlim,str_show);
		if(lowlim<range_switching_threshold)dot_pos=1; else dot_pos=2;
		Draw_small_num(4,dot_pos,str_show,  measure_pos+21,2, font_8_dark, 8, back_color);
		num2str_right(uplim,str_show);
		if(uplim<range_switching_threshold)dot_pos=1; else dot_pos=2;
		Draw_small_num(4,dot_pos,str_show,  measure_pos+21,1, font_8_dark, 8, back_color);
	}screen_refresh=false;
	
	num2str_right(ee_grade_lowlim_choice,str_show);	
	if(ee_grade_lowlim_choice<range_switching_threshold)dot_pos=1; else dot_pos=2;
	Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
	show_scrollbar(ee_grade_max-ee_grade_lowlim_choice,32,ee_grade_max-ee_grade_min+1,scrol_pos,back_color);//-ee_grade_min
}

void show_dlg_4(unsigned char color)		// ������� ������
{
	unsigned char dot_pos=1;
	if(screen_refresh)
	{
		Draw_string (dlg_4_width,nodot, dlg_4_line0 , dlg_4_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_4_width,nodot, dlg_4_line1 , dlg_4_pos, 1, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_4_width,nodot, dlg_4_line2 , dlg_4_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_4_width,nodot, dlg_4_line3 , dlg_4_pos, 3, font_8_dark, fnt_width_8, back_color);

	num2str_right(ee_grade_lowlim_choice,str_show);
	if(ee_grade_lowlim_choice<range_switching_threshold)dot_pos=1; else dot_pos=2;
	Draw_small_num(4,dot_pos,str_show,  measure_pos+21,2, font_8_dark, 8, back_color);
	//Draw_string   (4,nodot,str_show, 27,1, font_8_dark, fnt_width_8, back_color);
	num2str_right(uplim,str_show);
	if(uplim<range_switching_threshold)dot_pos=1; else dot_pos=2;
	Draw_small_num(4,dot_pos,str_show,  measure_pos+21,1, font_8_dark, 8, back_color);

	}screen_refresh=false;

	num2str_right(ee_grade_uplim_choice,str_show);
	if(ee_grade_uplim_choice<range_switching_threshold)dot_pos=1; else dot_pos=2;
	Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
	show_scrollbar(ee_grade_max-ee_grade_uplim_choice,32,ee_grade_max-ee_grade_lowlim_choice+1,scrol_pos,back_color);//-ee_grade_lowlim_choice
};
void show_dlg_5(unsigned char color)	// ��������������
{
	if(screen_refresh)
	{
		Draw_string (dlg_5_width,nodot, dlg_5_line0 , dlg_5_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_5_width,nodot, dlg_5_line1 , dlg_5_pos, 1, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_5_width,nodot, dlg_5_line2 , dlg_5_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_5_width,nodot, dlg_5_line3 , dlg_5_pos, 3, font_8_dark, fnt_width_8, back_color);
	}screen_refresh=false;
	num2str_left(ee_minutes_off,str_show);//num2str_right
	Draw_big_font (2,nobigdot,str_show,measure_pos+2,measure_raw, big_font_16, 16, front_color);
	show_scrollbar(ee_minutes_off_max-ee_minutes_off,32,ee_minutes_off_max+1,scrol_pos,back_color);//-ee_minutes_off_min "+1"- ����� �� ����
};
void show_dlg_6(unsigned char color)	//�����
{
	if(screen_refresh)
	{
		Draw_string (dlg_6_width,nodot, dlg_6_line0 , dlg_6_pos, 0, font_8_dark, fnt_width_8, back_color);
//		Draw_string (dlg_6_width,nodot, dlg_6_line1 , dlg_6_pos, 1, font_8_dark, fnt_width_8, back_color);
//		Draw_string (dlg_6_width,nodot, dlg_6_line2 , dlg_6_pos, 2, font_8_dark, fnt_width_8, back_color);
//		Draw_string (dlg_6_width,nodot, dlg_6_line3 , dlg_6_pos, 3, font_8_dark, fnt_width_8, back_color);
	}screen_refresh=false;
	
	if(ee_brightness_choice==0)
	{
		Draw_big_font (dlg_6_big_width,nobigdot,dlg_6_line1, dlg_6_big_pos,1, big_font_16, 16, front_color);
		Draw_string (dlg_6_width,nodot, dlg_6_line2 , dlg_6_pos, 3, font_8_dark, fnt_width_8, back_color);
		//back_color=back_color_const;
		send_command(0xA6);					// Normal Display OLED
	}else
	{
		Draw_big_font (dlg_6_big_width,nobigdot,dlg_6_line2, dlg_6_big_pos,1, big_font_16, 16, front_color);
		Draw_string (dlg_6_width,nodot, dlg_6_line1 , dlg_6_pos, 3, font_8_dark, fnt_width_8, back_color);
		//back_color=front_color;
		send_command(0xA7);					// A7h = Inverse Display OLED
	}
	show_scrollbar(ee_brightness_choice ,48,2,scrol_pos,back_color);
};
void show_dlg_7(unsigned char color)		// ����
{
	if(screen_refresh)
	{
		Draw_string (dlg_7_width,nodot, dlg_7_line0 , dlg_7_pos, 0, font_8_dark, fnt_width_8, back_color);
		//		Draw_string (dlg_7_width,nodot, dlg_7_line1 , dlg_7_pos, 1, font_8_dark, fnt_width_8, back_color);
		//		Draw_string (dlg_7_width,nodot, dlg_7_line2 , dlg_7_pos, 2, font_8_dark, fnt_width_8, back_color);
		//		Draw_string (dlg_7_width,nodot, dlg_7_line3 , dlg_7_pos, 3, font_8_dark, fnt_width_8, back_color);
	}screen_refresh=false;
	show_no_sound(ee_sound_choice);
	if(ee_sound_choice==1)
	{
		Draw_big_font_align(dlg_7_big_width,nobigdot,dlg_7_line1, dlg_7_big_pos-1,1, big_font_16, 16,1, front_color);
//		Draw_big_font (dlg_7_big_width,nobigdot,dlg_7_line1, dlg_7_big_pos,1, big_font_16, 16, front_color);
		Draw_string   (dlg_7_big_width,nodot,dlg_7_line2, dlg_7_big_pos<<1,3, font_8_dark, fnt_width_8, back_color);
	}else
	{
		Draw_big_font (dlg_7_big_width,nobigdot,dlg_7_line2, dlg_7_big_pos-1,1, big_font_16, 16, front_color);
		Draw_string   (dlg_7_big_width,nodot,dlg_7_line1, dlg_7_big_pos<<1,3, font_8_dark, fnt_width_8, back_color);
	}
	show_scrollbar(ee_sound_choice ,48,2,scrol_pos,back_color);
};									
void show_dlg_8(unsigned char color)		// ��������
{
	if(screen_refresh)
	{
		Draw_string (dlg_8_width,nodot, dlg_8_line0, dlg_8_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_8_width,nodot, dlg_8_line1, dlg_8_pos, 1, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_8_width,nodot, dlg_8_line2, dlg_8_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_8_width,nodot, dlg_8_line3, dlg_8_pos, 3, font_8_dark, fnt_width_8, back_color);
	}screen_refresh=false;
	num2str_left(ee_gain_choice,str_show); //num2str_right
	Draw_big_font (2,nobigdot,str_show,measure_pos+1,measure_raw, big_font_16, 16, front_color);
	show_scrollbar(ee_gain_max-ee_gain_choice,32,ee_gain_max-ee_gain_min+1,scrol_pos,back_color);
};
void show_dlg_9(unsigned char color)		// �������� ���������
{
	if(screen_refresh) 
	{
		Draw_string (dlg_9_width,nodot, dlg_9_line0 , dlg_9_pos, 0, font_8_dark, fnt_width_8, back_color);
		//		Draw_string (dlg_9_width,nodot, dlg_9_line1 , dlg_9_pos, 1, font_8_dark, fnt_width_8, back_color);
		//		Draw_string (dlg_9_width,nodot, dlg_9_line2 , dlg_9_pos, 2, font_8_dark, fnt_width_8, back_color);
		//		Draw_string (dlg_9_width,nodot, dlg_9_line3 , dlg_9_pos, 3, font_8_dark, fnt_width_8, back_color);
	}screen_refresh=false;
	if(reset_choice==0)
	{
		Draw_big_font_align(dlg_9_big_width,nobigdot,dlg_9_line1, dlg_9_big_pos,1, big_font_16, 16,-2, front_color);
		//Draw_big_font (dlg_9_big_width,nobigdot,dlg_9_line1, dlg_9_big_pos,1, big_font_16, 16, front_color);
		Draw_string   (dlg_9_big_width,nodot,dlg_9_line2, dlg_9_big_pos<<1,3, font_8_dark, fnt_width_8, back_color);
	}else
	{
		Draw_big_font (dlg_9_big_width,nobigdot,dlg_9_line2, dlg_9_big_pos-1,1, big_font_16, 16, front_color);
		Draw_string   (dlg_9_big_width,nodot,dlg_9_line1, dlg_9_big_pos<<1,3, font_8_dark, fnt_width_8, back_color);
	}
	show_scrollbar(reset_choice ,48,2,scrol_pos,back_color);
};
void show_dlg_10(unsigned char color)		// �������� ���
{
	if(screen_refresh)
	{
		Draw_string (dlg_10_width,nodot, dlg_10_line0, dlg_10_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_10_width,nodot, dlg_10_line1, dlg_10_pos, 1, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_10_width,nodot, dlg_10_line2, dlg_10_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_10_width,nodot, dlg_10_line3, dlg_10_pos, 3, font_8_dark, fnt_width_8, back_color);
	}screen_refresh=false;
	num2str_right(ee_velocity_choice,str_show);
	Draw_big_font (4,nobigdot,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
	show_scrollbar(ee_velocity_max-ee_velocity_choice,32,ee_velocity_max-ee_velocity_min+1,scrol_pos,back_color);//-ee_velocity_min
};
void show_dlg_11(unsigned char color)		// ������� ���������
{
	if(screen_refresh)
	{
		Draw_string (dlg_11_width,nodot, dlg_11_line0, dlg_11_pos, 0, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_11_width,nodot, dlg_11_line1, dlg_11_pos, 1, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_11_width,nodot, dlg_11_line2, dlg_11_pos, 2, font_8_dark, fnt_width_8, back_color);
		Draw_string (dlg_11_width,nodot, dlg_11_line3, dlg_11_pos, 3, font_8_dark, fnt_width_8, back_color);
	}screen_refresh=false;
	num2str_right(ee_thickness_choice,str_show);
	if(ee_thickness_choice<range_switching_threshold)dot_pos=1; else dot_pos=2;
	Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
	show_scrollbar(ee_thickness_max-ee_thickness_choice,32,ee_thickness_max-ee_thickness_min+1,scrol_pos,back_color);//-ee_thickness_min
};
void show_dlg_12(unsigned char color)		// �������� ������?
{
	if(screen_refresh)
	{
		cls();
		Draw_string (dlg_12_width,nodot, dlg_12_line0 , dlg_12_pos, 0, font_8_dark, fnt_width_8, color);
		//		Draw_string (dlg_6_width,nodot, dlg_6_line1 , dlg_6_pos, 1, font_8_dark, fnt_width_8, back_color);
		//		Draw_string (dlg_6_width,nodot, dlg_6_line2 , dlg_6_pos, 2, font_8_dark, fnt_width_8, back_color);
		//		Draw_string (dlg_6_width,nodot, dlg_6_line3 , dlg_6_pos, 3, font_8_dark, fnt_width_8, back_color);
	}screen_refresh=false;
	
	if(clear_journal==0)
	{
		Draw_big_font (dlg_12_big_width,nobigdot,dlg_12_line1, dlg_12_big_pos-1,1, big_font_16, 16, front_color);
		Draw_string   (dlg_12_big_width+1,nodot, dlg_12_line2 , (dlg_12_big_pos<<1)-1, 3, font_8_dark, fnt_width_8, color);
	}else
	{
		Draw_big_font (dlg_12_big_width,nobigdot,dlg_12_line2, dlg_12_big_pos-1,1, big_font_16, 16, front_color);
		Draw_string   (dlg_12_big_width,nodot, dlg_12_line1 , dlg_12_big_pos<<1, 3, font_8_dark, fnt_width_8, color);
	}
	show_scrollbar(clear_journal ,48,2,scrol_pos,color);
};
void show_dlg_13(unsigned char color)		// ������� ������?
{
	unsigned char str_show_temp[4]={"9999"};
	unsigned char status_byte;	
	if(screen_refresh)
	{
		cls();
		Draw_string (dlg_13_width,nodot, dlg_13_line0 , dlg_13_pos, 0, font_8_dark, fnt_width_8, color);
		//		Draw_string (dlg_6_width,nodot, dlg_6_line1 , dlg_6_pos, 1, font_8_dark, fnt_width_8, back_color);
		//		Draw_string (dlg_6_width,nodot, dlg_6_line2 , dlg_6_pos, 2, font_8_dark, fnt_width_8, back_color);
		//		Draw_string (dlg_6_width,nodot, dlg_6_line3 , dlg_6_pos, 3, font_8_dark, fnt_width_8, back_color);

 		status_byte = eeprom_read_byte(get_addr(ee_page_numb)+(entry_choice+i)*entry_size);
 		if(!TestBit(status_byte,6))
 		{
	 		num2str_right(eeprom_read_word(get_addr(ee_page_numb)+(entry_choice+i)*entry_size+1),str_show_temp);								// ������ 0
	 		if(TestBit(status_byte,4))dot_pos=2; else dot_pos=1;
	 		Draw_small_num(4,dot_pos,str_show_temp,dlg_13_entry_pos,0, font_8_dark, fnt_width_8, color);
	 		if(TestBit(status_byte,7))
	 		Draw_string (1,nodot, "-",dlg_13_entry_pos-1, 0, font_8_dark, fnt_width_8, color); 				// ����
	 		else		Draw_string (1,nodot, " ",dlg_13_entry_pos-1, 0, font_8_dark, fnt_width_8, color);
	 		
	 		Draw_string (2,nodot,"��",dlg_13_entry_pos+4,0, font_8_dark, fnt_width_8, color);
		}
// 		num2str_right(3334,str_show_temp);					// ������� ��������� ������ 		
// 		if(3334<range_switching_threshold)dot_pos=1; else dot_pos=2;
// 		Draw_small_num(4,dot_pos,str_show_temp,dlg_13_entry_pos,0, font_8_dark, 8, color);
		
	}screen_refresh=false;
	
	if(clear_entry==0)
	{
		Draw_big_font (dlg_13_big_width,nobigdot,dlg_13_line1, dlg_13_big_pos-1,1, big_font_16, 16, front_color);
		Draw_string   (dlg_13_big_width+1,nodot, dlg_13_line2 ,(dlg_13_big_pos<<1)-1, 3, font_8_dark, fnt_width_8, color);
	}else
	{
		Draw_big_font (dlg_13_big_width,nobigdot,dlg_13_line2, dlg_13_big_pos-1,1, big_font_16, 16, front_color);
		Draw_string   (dlg_13_big_width,nodot, dlg_13_line1 , dlg_13_big_pos<<1, 3, font_8_dark, fnt_width_8, color);
	}
	show_scrollbar(clear_entry ,48,2,scrol_pos,color);
};

void show_dlg_14(unsigned char color)		// ���������� ����, ���������� ����������� ������� ��� ��
{
	if(screen_refresh)
	{
        cls();
        Draw_string (2,nodot,"MM",(measure_pos+4)*2,2, font_8_dark, 8, color);
        Draw_string_left(menu_pep_width, pep_list[9+ee_pep_numb] , 0,0, font_8_dark, 8, color);
        Draw_string (2,nodot,"V=", velocity_pos-2,velocity_raw, font_8_dark, 8, color);
        num2str_left(vel_calib[datch],str_show);
        Draw_string (4,nodot,str_show, velocity_pos,velocity_raw, font_8_dark, 8, color);
        Draw_string (3,nodot,"�/c", velocity_pos+4,velocity_raw, font_8_dark, 8, color);
	}screen_refresh=false;
};

/*_______________������ #8________________*/
void vDialogues( void *pvParameters )
{
unsigned int i;
unsigned int A1=1;
unsigned char stat_byte=0;
//unsigned char calibr_flag=false;
unsigned long psz;
unsigned char u=0;
unsigned int longpush_delay=0;

unsigned long psize;

	portTickType xLastExecutionTime;
	
	xLastExecutionTime = xTaskGetTickCount();

	for(;;)
	{
		
        if(keypressed_long )								// ��� ������� �������� �� ������
        {
			longpush_delay++;
			if(longpush_delay>100)
			{if(key_inc<100)key_inc*=10;
				longpush_delay=0;
			}
		}else {longpush_delay=0;key_inc=1;}

		
		
		if(menu_level_choice==3)							// �������
		{
			//delay_in_cycle(key_inc);
			if(dialogues_choice==dlg_nonius)				// ���.4 ������ dlg_1
			{
				show_dlg_1(back_color);
					////////////////////////////////////////////////////////////////////////////////////
					if(keypressed_short)					// �������� ������� �� ������!
					{
						keypressed_short=false;
						//BEEP(2);
						if(butt_old==keyup)
						{
							if(ee_nonius_choice < ee_nonius_max) ee_nonius_choice+=key_inc;
							else ee_nonius_choice=ee_nonius_min;
						}else
						if(butt_old==keydown)
						{
							if(ee_nonius_choice > ee_nonius_min) ee_nonius_choice-=key_inc;
							else ee_nonius_choice=ee_nonius_max;
							
						}else
						if(butt_old==keyenter)
						{
							cls();							//!!!!!!!!!!!!!!!!!!
							//BEEP(2);
							eeprom_write_word(NONIUSU1 + nastr*2,ee_nonius_choice);
							screen_refresh=true;
							menu_level_choice=1;			// ������� � ����� ������ �1
						}
					} // if(keypressed_short)
				
			}else
			if(dialogues_choice==dlg_deviation)				// ���.5 ���������� dlg_2
			{
				show_dlg_2(back_color);
				
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)						// �������� ������� �� ������!
				{
					keypressed_short=false;
					//BEEP(2);
					if(ee_base_level_choice<range_switching_threshold)A1=key_inc;
					else A1=10*key_inc;
					if(butt_old==keyup)
					{
						if(ee_base_level_choice < ee_base_level_max) ee_base_level_choice+=A1;
						else ee_base_level_choice=ee_base_level_min;
					}else
					if(butt_old==keydown)
					{
						if(ee_base_level_choice > (ee_base_level_min+A1)) ee_base_level_choice-=A1;
						else ee_base_level_choice=ee_base_level_max;
						
				}else
				if(butt_old==keyenter)
					{
						cls();								// !!!!!!!!!!!!!!!!!!!!!!!!!
						//BEEP(2);
						eeprom_write_word(DIFFU1 + nastr*2,ee_base_level_choice);
						screen_refresh=true;
						menu_level_choice=1;				// ������� � ����� ������ �1
					}
				} // if(keypressed_short)
			}else
			if(dialogues_choice==dlg_grade_lower)			// ���.6 ����������� dlg_3
			{
				show_dlg_3(back_color);
				
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)						// �������� ������� �� ������!
				{
					keypressed_short=false;
					
					//ee_grade_lowlim_choice=ee_grade_min;
					//BEEP(2);
					if(ee_grade_lowlim_choice<range_switching_threshold)A1=key_inc;
					else A1=10*key_inc;

					if(butt_old==keyup)
					{
						if(ee_grade_lowlim_choice < ee_grade_max) ee_grade_lowlim_choice+=A1;
						else ee_grade_lowlim_choice=ee_grade_min;
					}else
					if(butt_old==keydown)
					{
						if(ee_grade_lowlim_choice > ee_grade_min) ee_grade_lowlim_choice-=A1;
						else ee_grade_lowlim_choice=ee_grade_max;
						
					}else
					if(butt_old==keyenter)
					{
						cls();								//!!!!!!!!!!!!!!!!!!
						//BEEP(2);
						ee_grade_min=ee_grade_lowlim_choice;
						if(ee_grade_uplim_choice<ee_grade_lowlim_choice)ee_grade_uplim_choice=ee_grade_lowlim_choice;
						eeprom_write_word(RAZB_L1 + nastr*2,ee_grade_lowlim_choice);
						dialogues_choice=4;					// ��������� � dlg_4 ������� ������
						screen_refresh=true;
					}
				} // if(keypressed_short)
				
			}else
			if(dialogues_choice==dlg_grade_upper)			// ���.6 ����������� dlg_4
			{
				show_dlg_4(back_color);
				
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)						// �������� ������� �� ������!
				{
					keypressed_short=false;
					//BEEP(2);
					if(ee_grade_uplim_choice<range_switching_threshold)A1=key_inc;
					else A1=10*key_inc;
					
					if(butt_old==keyup)
					{
						
						if(ee_grade_uplim_choice < ee_grade_max) ee_grade_uplim_choice+=A1;
						else ee_grade_uplim_choice=ee_grade_min;
					}else
					if(butt_old==keydown)
					{
						if(ee_grade_uplim_choice > ee_grade_min) ee_grade_uplim_choice-=A1;
						else ee_grade_uplim_choice=ee_grade_max;
						
					}else
					if(butt_old==keyenter)
					{
						cls();								//!!!!!!!!!!!!!!!!!!
						//BEEP(2);
						//dialogues_choice=4;	
						eeprom_write_word(RAZB_H1 + nastr*2,ee_grade_uplim_choice);	
						ee_grade_min=lowlim;	
						screen_refresh=true;
						menu_level_choice=1;				// ������� � ����� ������ �1
					}
				} // if(keypressed_short)
				
			}else
			if(dialogues_choice==dlg_settings_autopower)	// ���.7 AutoPower dlg_5
			{
				show_dlg_5(back_color);
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)						// �������� ������� �� ������!
				{
					keypressed_short=false;
					//BEEP(2);
					if(butt_old==keyup) 
					{
						keypressed_short=false;
						if(ee_minutes_off < ee_minutes_off_max) ee_minutes_off++;
						else ee_minutes_off=ee_minutes_off_min;
					}else
					if(butt_old==keydown) 
					{
						keypressed_short=false;
						if(ee_minutes_off > ee_minutes_off_min) ee_minutes_off--;
						else ee_minutes_off=ee_minutes_off_max;		
					}else
					if(butt_old==keyenter)
					{
						keypressed_short=false;
						eeprom_write_byte (MINUTES_OFF,ee_minutes_off);	 ///  �����, ��������������
						cls();								// !!!!!!!!!!!!!!!!!!
//						//BEEP(2);
						screen_refresh=true;
						menu_level_choice=1;				// ������� � ����� ������  
						
					}
				} // if(keypressed_short)
			}else
			if(dialogues_choice==dlg_settings_screen)		// ���.7 ��������� �����. dlg_6
			{
				show_dlg_6(back_color);
				
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)						// �������� ������� �� ������!
				{
					keypressed_short=false;
					//BEEP(2);
					if(butt_old==keyup)
					{
						
						if(ee_brightness_choice < 1) ee_brightness_choice++;
						else ee_brightness_choice=0;
					}else
					if(butt_old==keydown)
					{
						if(ee_brightness_choice > 0) ee_brightness_choice--;
						else ee_brightness_choice=1;
						
					}else
					if(butt_old==keyenter)
					{
						cls();								//!!!!!!!!!!!!!!!!!!
						//BEEP(2);
						eeprom_write_byte (BRIGHT,ee_brightness_choice);	 ///  ������� 
						screen_refresh=true;
						menu_level_choice=1;				// ������� � ����� ������ T2 - ��������� �������
							
						//dialogues_choice=4;
					}
				} // if(keypressed_short)

			}else
			if(dialogues_choice==dlg_settings_sound)		// ���.7 ��������� ����. dlg_7
			{
				show_dlg_7(back_color);
				
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)						// �������� ������� �� ������!
				{
					keypressed_short=false;
					//BEEP(2);
					if(butt_old==keyup)
					{
						
						if(ee_sound_choice < 1) ee_sound_choice++;
						else ee_sound_choice=0;
					}else
					if(butt_old==keydown)
					{
						if(ee_sound_choice > 0) {ee_sound_choice--;BEEP(2);}
						else ee_sound_choice=1;
						
					}else
					if(butt_old==keyenter)
					{
						cls();								//!!!!!!!!!!!!!!!!!!
						//BEEP(2);
						eeprom_write_byte (BEEP_MODE,ee_sound_choice);
						screen_refresh=true;
						menu_level_choice=1;				// ������� � ����� ������ T2 - ��������� �������
						
						//dialogues_choice=4;
					}
				} // if(keypressed_short)

			}else
			if(dialogues_choice==dlg_settings_gain)			// ���.7 ��������� ��������. dlg_8
			{
				show_dlg_8(back_color);
				
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)						// �������� ������� �� ������!
				{
					keypressed_short=false;
					//BEEP(2);
					if(butt_old==keyup) 
					{
						if(ee_gain_choice < ee_gain_max) ee_gain_choice++;
						else ee_gain_choice=ee_gain_min;
					}else
					if(butt_old==keydown)
					{
						if(ee_gain_choice > ee_gain_min) ee_gain_choice--;
						else ee_gain_choice=ee_gain_max;
						
					}else
					if(butt_old==keyenter)
					{
						cls();								//!!!!!!!!!!!!!!!!!!
						//BEEP(2);
						
						screen_refresh=true;
						eeprom_write_byte(AMP1+(nastr)*2,ee_gain_choice);
						
						RPM();
						//_delay_ms(1);
						RPR();
						//_delay_ms(1);
						cfgr_load(ee_gain_choice,datch);		// �������� �������� � �������� ���������� �����.
						
	/*					
		eeprom_write_byte (AMP1,25);  /// �������� ��� ��������
		eeprom_write_byte (AMP2,25);
		eeprom_write_byte (AMP3,25);
		eeprom_write_byte (AMP4,25);
		eeprom_write_byte (AMP5,25);
		eeprom_write_byte (AMP6,25);
		eeprom_write_byte (AMP7,25);
		eeprom_write_byte (AMP8,25);
		eeprom_write_byte (AMP9,25);
		eeprom_write_byte (AMP10,25);*/
						            
						menu_level_choice=1;				// ������� � ����� ������ 
						//dialogues_choice=4;
					}
				} // if(keypressed_short)
				
			}else
			if(dialogues_choice==dlg_settings_reset)		// ���.9 ��������� �����. dlg_9
			{
				show_dlg_9(back_color);
				
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)						// �������� ������� �� ������!
				{
					keypressed_short=false;
					//BEEP(2);
					if(butt_old==keyup)
					{
						if(reset_choice < 1) reset_choice++;
						else reset_choice=0;
					}else
					if(butt_old==keydown)
					{
						if(reset_choice > 0) reset_choice--;
						else reset_choice=1;
						
					}else
					if(butt_old==keyenter)
					{
						cls();								//!!!!!!!!!!!!!!!!!!
						
						//BEEP(2);
						if(reset_choice)
						{
							Draw_string(32,dot, "          ����� ��������           ",0, 1, font_8_dark, fnt_width_8, front_color);
							
// 							for(i=0;i<256;i++)
// 							{
// 								
// 							
// 							show_progress_bar(i,22,255,3);
// 							_delay_ms(800);
// 							}
// 							
// 							Draw_symbol( progress_mask, 2+7,3,8,16,front_color);
// 							Draw_symbol( progress_mask, 3+7,3,8,16,front_color);
// 							Draw_symbol( progress_mask, 4+7,3,8,16,front_color);
// 							Draw_symbol( progress_mask, 5+7,3,8,16,front_color);
// 							Draw_symbol( progress_mask, 6+7,3,8,16,front_color);
// 							Draw_symbol( progress_mask, 7+7,3,8,16,front_color);
// 							Draw_symbol( progress_mask, 8+7,3,8,16,front_color);
// 							Draw_symbol( progress_mask, 9+7,3,8,16,front_color);
// 							Draw_symbol( progress_mask,10+7,3,8,16,front_color);
// 							Draw_symbol( progress_mask,11+7,3,8,16,6);
// 							Draw_symbol( progress_mask,12+7,3,8,16,12);
// 							Draw_symbol( progress_mask,13+7,3,8,16,12);

							show_progress_bar(10,22,100,3);
							eeprom_write_word(STAT,0xFFFF);
							initmem();
							show_progress_bar(100,22,100,3);							
							load_defaults();
							//show_progress_bar(100,22,100,3);							
							delay_in_cycle(delay_1sec);
							
						}
						screen_refresh=true;
						reset_choice=0;						// ������ ����� ������ "���"	
						menu_level_choice=1;				// ������� � ����� ������ T2 - ��������� �������
						
						//dialogues_choice=4;
					}
				} // if(keypressed_short)

			}else			
			if(dialogues_choice==dlg_calibration_zero)		// ���.8 ���������� ���� 10
			{
                 //___________________________________ ���������� 0 _______________________________________//

                  show_msg_15(front_color);		// ���������� ��� �� �������

//                    keypressed_short=false; 
//                    while // &&
//                    {
//                        butt_scan();
//                        IZMERENIE(0x01, vel,datch,nastr,amplif,voltp,calibr,mf,mp,tf);
//                    };
                    IZMERENIE(0x01, vel,datch,nastr,amplif,voltp,calibr,mf,mp,tf);	// ��� ����������� ��                    
					if((PINH & (1<<acontpin)) || keypressed_short)		// ���� ������ ������ ��� ���� ��
					{
						screen_refresh=true;
						keypressed_short=false;
						dialogues_choice=dlg_calibration_zero_input;	// ��������� � ����������� ����������� �������
					}
			}else
			if(dialogues_choice==dlg_calibration_velocity)	// ���.8 ���������� �������� ���. 11
			{
				show_dlg_10(back_color);
				//num2str_left(key_inc,str_show4);
				//Draw_string (4,nodot,str_show4, velocity_pos,velocity_raw, font_8_dark, 8, back_color);

				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)						// �������� ������� �� ������!
				{
					keypressed_short=false;
					//BEEP(2);
					if(butt_old==keyup)
					{
						
						if(ee_velocity_choice < ee_velocity_max) ee_velocity_choice+=key_inc;//key_inc;
						else ee_velocity_choice=ee_velocity_min;
// 						num2str_right(key_inc,str_show4);
// 						Draw_string (4,nodot,str_show4,0,3, font_8_dark, 8, back_color);
// 						num2str_right(A1,str_show4);
// 						Draw_string (4,nodot,str_show4,6,3, font_8_dark, 8, back_color); 
					}else
					if(butt_old==keydown)
					{
						if(ee_velocity_choice > ee_velocity_min) ee_velocity_choice-=key_inc;//key_inc;
						else ee_velocity_choice=ee_velocity_max;
// 						num2str_right(key_inc,str_show4);
// 						Draw_string (4,nodot,str_show4,0,3, font_8_dark, 8, back_color);
// 						num2str_right(A1,str_show4);
// 						Draw_string (4,nodot,str_show4,6,3, font_8_dark, 8, back_color);
						
					}else
					if(butt_old==keyenter)
					{
						nastr=eeprom_read_byte(NASTR);
						eeprom_write_word(VEL1+(nastr),ee_velocity_choice);
						vel=ee_velocity_choice;

						show_msg_17(front_color);
						delay_in_cycle(delay_2sec);
						//nastr=eeprom_read_byte(NASTR);		//nastr=settings_choice;
						//if(settings_choice<10)nastr=settings_choice; else nastr=eeprom_read_byte(NASTR);
						cls();								// !!!!!!!!!!!!!!!!!!
						screen_refresh=true;
						
						keypressed_short=false;					
						menu_level_choice=1;				// ������� � ����� ������ T1 - �������� �������								

						//dialogues_choice=4;
					}
				} // if(keypressed_short)

			}else
			if(dialogues_choice==dlg_calibration_H)			// ���.8 ���������� H. 12
			{
//____________________________________________________

				/////////////////////////////////////////////////////////////////////////////
				//cls();								//!!!!!!!!!!!!!!!!!!
				//BEEP(2);
				//menu_level_choice=2;				// ������� � ����� ������ T2 - ��������� �������
				//screen_refresh=true;

				show_msg_19(front_color);			// ����������, ����������, ��� �� ������� �������
//				delay_in_cycle(delay_2sec);

//				RPM();
				keypressed_short=false;
				//vel=eeprom_read_word(VELMEM);
				//vel=ee_velocity_choice;

				while(!(PINH & (1<<acontpin)) && !keypressed_short)
				{
					butt_scan();
					IZMERENIE(0x01,	vel,datch,nastr,amplif,voltp,calibr,mf,mp,tf);
				};


					
					cls();
					Draw_string (2,nodot,"MM",(measure_pos+4)*2,2, font_8_dark, 8, back_color);
					Draw_string_left(menu_pep_width, pep_list[9+ee_pep_numb] , 0,0, font_8_dark, 8, back_color);
					Draw_string (2,nodot,"V=", velocity_pos-2,velocity_raw, font_8_dark, 8, back_color);
					num2str_left(ee_velocity_choice,str_show);
					Draw_string (4,nodot,str_show, velocity_pos,velocity_raw, font_8_dark, 8, back_color);
					Draw_string (3,nodot,"�/c", velocity_pos+4,velocity_raw, font_8_dark, 8, back_color);

					keypressed_short=false;
					
				while(!keypressed_short)//(PINH & (1<<acontpin)) && 
				{
					butt_scan();
					main_value=IZMERENIE(0x01,vel,datch,nastr,amplif,voltp,calibr,mf,mp,tf);
					num2str_right(main_value,str_show);
					if(main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
					Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
				};//while()
				
				/////////////////////////////////////////////////////////////////////////////
 				keypressed_short=false;
 				
				if(main_value<ee_thickness_min)main_value=ee_thickness_min;
				else
				if(main_value>ee_thickness_max)main_value=ee_thickness_max;
				ee_thickness_choice=main_value;				// ������������ ���������� ��������
				
				show_msg_18(front_color);					// 
				//_delay_ms(4000);
				delay_in_cycle(delay_8sec);
				
				keypressed_short=false;
				
				dialogues_choice=dlg_thickness_input;

				//______________________________________					

			}else
			if(dialogues_choice==dlg_journal_clear)			// ���.10 �������� ������? 13
			{

				show_dlg_12(back_color);
			
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)						// �������� ������� �� ������!
				{
					keypressed_short=false;
					//BEEP(2);
					if(butt_old==keyup)
					{
					
						if(clear_journal < 1) clear_journal++;
						else clear_journal=0;
					}else
					if(butt_old==keydown)
					{
						if(clear_journal > 0) clear_journal--;
						else clear_journal=1;
					
					}else
					if(butt_old==keyenter)
					{
						if(clear_journal)					// ������� ������
						{
								cls();
								Draw_string(32,dot, "         �������� �������          ",0, 1, font_8_dark, fnt_width_8, front_color);

 							for(i=0;i<=page_size_max;i++)		// <=  ��� �� ��������� ������� ����������
							 {
 								eeprom_write_byte(get_addr(0)+i*entry_size,0x40);						// �������� ������� ������� (���������� ������� �� ������ ��������)
								show_progress_bar(i,22,page_size_max,3);
							 }
							for(i=0;i<page_numb_max;i++)
							eeprom_write_dword(get_page_size(i),0);						// �������� ������� ������� (���������� ������� �� ������ ��������)

							eeprom_write_word(journal_addr+2,page_numb_min);				// ���������� page_numb_min=1
							eeprom_write_word(MEMPNT,page_numb_min);					// ��������� ����� ������� �������� �������
							ee_page_numb=page_numb_min;
							ee_page_size=0;
						}
						
						clear_journal=0;					// �� ��������� - ���!
						
						cls();								//!!!!!!!!!!!!!!!!!!
						//BEEP(2);
						
						screen_refresh=true;		
						menu_level_choice=1;				// ������� � �������� �������	
					}
				} // if(keypressed_short)
	
			}else
			if(dialogues_choice==dlg_entry_clear)			// entry_clear 14
			{
				show_dlg_13(back_color);					// ������� ������?
				
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)						// �������� ������� �� ������!
				{
					keypressed_short=false;
					//BEEP(2);
					if(butt_old==keyup)
					{
						
						if(clear_entry < 1) clear_entry++;
						else clear_entry=0;
					}else
					if(butt_old==keydown)
					{
						if(clear_entry > 0) clear_entry--;
						else clear_entry=1;
						
					}else
					if(butt_old==keyenter)
					{
						if(clear_entry)						// ������� ������ (�������� ��� ���������)
						{
							stat_byte=eeprom_read_byte(get_addr(ee_page_numb)+entry_choice*entry_size);	
							//stat_byte|=0x40;				// ������� "��������� ������"
							SetBit(stat_byte,6);
							eeprom_write_byte(get_addr(ee_page_numb)+entry_choice*entry_size,stat_byte);
							psz=eeprom_read_dword(get_page_size(ee_page_numb));
							if(psz>0)
							{
								eeprom_write_dword(get_page_size(ee_page_numb),psz-1);	 //////// ��������� ������� ������� �� ��������!!!!!!!
								psize=eeprom_read_dword(get_addr(ee_page_numb));
								psize-=1;
								eeprom_write_dword(get_addr(ee_page_numb),psize);						// ����������� ������� ������� �� ��������
							}
						}
						clear_entry=0;						// �� ��������� - ���!
						cls();								//!!!!!!!!!!!!!!!!!!
						//BEEP(2);
						dialogues_choice=dlg_page_view;		// ������ � dlg_15 �������� ��������
						screen_refresh=true;
						if(psz==0)menu_level_choice=2;		// ���� ��� ���� ��������� ������, �� ������ � ������		
						else menu_level_choice=3;				
					}
				} // if(keypressed_short)				
			}else
			if(dialogues_choice==dlg_page_view)	// 15 �������� ��������
			{
				//ee_page_size=get_page_size(page_choice);
				//numb_deleted_entry=0;
// 				for(i=0;i<ee_page_size;i++)
// 				{
// 					status_byte = eeprom_read_byte(get_addr(page_numb)+(page_focus+i)*entry_size);
// 					if(TestBit(status_byte,6))numb_deleted_entry+=1;
// 				};
				//scroll_page(entry_choice,ee_page_size,ee_page_numb,back_color);
				scroll_page(entry_choice,ee_page_size,page_choice,back_color);
				////////////////////////////////////////////////////////////////////////////////////
				if(keypressed_short)						// �������� ������� �� ������!
				{
					
					keypressed_short=false;
					//BEEP(2);
					if(butt_old==keydown)
					{
						
						if(entry_choice < ee_page_size-1) entry_choice++;
						else entry_choice=0;
					//	scroll_page(entry_choice,ee_page_size,ee_page_numb,back_color);
					}else
					if(butt_old==keyup)
					{
						if(entry_choice > 0) entry_choice--;
						else entry_choice=ee_page_size-1;
					//	scroll_page(entry_choice,ee_page_size,ee_page_numb,back_color);
					}else
					if(butt_old==keyenter)
					{
					
						cls();								//!!!!!!!!!!!!!!!!!!
						//BEEP(2);
						entry_choice+=1;					// ��� ������ ���������� 2-� ������!!!!!!!!!!!!!!
						dialogues_choice=dlg_entry_clear;	// ������ � ������ �������� ������
						screen_refresh=true;
						menu_level_choice=3;				// ������� � ����� ������ �1 - ��������� �������
					}
				} // if(keypressed_short)				
			}else
			if(dialogues_choice==dlg_thickness_input)	// 16 ���� ������� � "���������� H"
			{
					show_dlg_11(back_color);
					if(keypressed_short)					// �������� ������� �� ������!
					{
						keypressed_short=false;
						//BEEP(2);
						if(ee_thickness_choice<range_switching_threshold)A1=key_inc;
						else A1=10*key_inc;

						if(butt_old==keyup)
						{
							if(ee_thickness_choice < ee_thickness_max) ee_thickness_choice+=A1;
							else ee_thickness_choice=ee_thickness_min;
						}else
						if(butt_old==keydown)
						{
							if(ee_thickness_choice > (ee_thickness_min+A1) )ee_thickness_choice-=A1;
							else ee_thickness_choice=ee_thickness_max;
						}else
						if(butt_old==keyenter)
						{
							
							VA = main_value;					//// ������� ����������
							//VA=mvs;
							SA = ee_velocity_choice;			//// �������� ��������
							VB = ee_thickness_choice;			//// ������� ���������
							//	im = io;

							//io = (im*64000)/(mvs);
							//if(VA==0)VA=1;
						
							SB=	(VB*SA)/VA;						// ��������� �������� �� ���������

							io =SB;
							//	io=it;
							if (io <= LowSPEED ) {io = LowSPEED;}
							else
							if (io >= HISPEED ) {io = HISPEED;}
						
						
							//show_msg_20(back_color);//_20	
							cls();							
							num2str_right(io,str_show);
							Draw_big_font (4,nobigdot,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
							Draw_string (12,nodot,"�������� ���",10, 0, font_8_dark, fnt_width_8, back_color);
							Draw_string (3,nodot,"�/�",20, 2, font_8_dark, fnt_width_8, back_color);
							Draw_string (29,nodot,"�������� �� ��������� �������",2, 3, font_8_dark, fnt_width_8, back_color);
							
							ee_velocity_choice=io;
							vel=ee_velocity_choice;
							eeprom_write_word(VEL1+(nastr)*2,io);
						//_delay_ms(4000);

							delay_in_cycle(delay_8sec);			// delay_4sec
							//cls();

						
							//	eeprom_write_word (VEL1+nastr*2,io);
						
							//load_defaults();
						
							//	main_value=0;						// ���������� ���������!
							//	ee_thickness_choice=0;				// ���������� ���������!
							keypressed_short=false;
							screen_refresh=true;				// ��������� �����
							menu_level_choice=1;				// ������� � ����� ������ T1
							
						}
						
					} // if(keypressed_short)
			}else
			if(dialogues_choice==dlg_calibration_zero_input)	// ���� � "���������� 0"
			{
					
					show_dlg_14(back_color);					// ����������� ����������� �������
					it=0;
					switch (datch)
					{
						case 0: u = 1; break; //�112-10.0-6\2-�003
						case 1: u = 2; break; //�112-5.0-10\2-�003
						case 2: u = 2; break; //�112-2.5-12\2-�003
						case 3: u = 0; break; //�112-2.5�-12\2-�
						case 4: u = 0; break; //�112-5.0�-12\2-�
						case 5: u = 1; break; //�112-2.5-12\2�
						case 6: u = 1; break; //�111-1.25-20\2�  ----
						case 7: u = 2; break; //�111-1.25�20//////////////////////////////// 2
						case 8: u = 3; break; //�111-1.25�20   ----
					};

					for (i=0;i<32;i++)                        // 32
					{
						PORTB |= _BV(RES);                    //  ����� ��������� ���c - ���������� �����������
						asm ("nop");
						PORTB &= ~_BV(RES);						// ������� �� ������ ����

						//_delay_ms (20);                     /////  ???????? ????? ??????????? --------------- 20
												
						delayx(u);      //0                   //_delay_us (u);        //// ??????? ???? ????? ???????
						PORTC |= _BV(STROB);                  /// ????? ????????
						_delay_us (210);                      /// ?????? ??????
						PORTC &= ~_BV(STROB);                 /// ????? ??????
												
						it+=ReadX();
					};//for()
											
					calibr=abs(it-calobr_num[datch])/2;
					main_value=IZMERENIE(0x01,vel_calib[datch],datch,nastr,amplif,voltp,calibr,mf,mp,tf);
					num2str_right(main_value,str_show);
					if(main_value<range_switching_threshold)dot_pos=1; else dot_pos=2;
					Draw_big_font (4,dot_pos,str_show,measure_pos,measure_raw, big_font_16, 16, front_color);
										
					if(keypressed_short)
					{
						BEEP(2);
						keypressed_short=false;										
						if(main_value>0 && butt_old!=keyzero)                   // ????????? ??????????
						{
							show_msg_16(front_color);
							
/*
	 cls();
	 Draw_string (32,nodot, "    ���������� ���� ���������,  " , 0, 1, font_8_dark, fnt_width_8, front_color);
	 Draw_string (32,nodot, "    ����� ��������� ���������   " , 0, 2, font_8_dark, fnt_width_8, front_color);
*/
							
							
							
							eeprom_write_word(CALB1+(nastr)*2,(unsigned int)calibr);
							eeprom_write_word (CALIBD,(unsigned int)calibr);
						}else show_msg_22(front_color);                                  // ??????? ??? ??????????

						delay_in_cycle(delay_4sec);
						RPM();
						cfgr_load(ee_gain_choice,datch);
						main_value=0;
						screen_refresh=true;
						menu_level_choice=1;                                    
					}//if(keypressed_short)
			}//if(dialogues_choice==dlg_calibration_zero_input)
			
			
		//vTaskDelay(func_delay / portTICK_RATE_MS);	
		//vTaskDelayUntil(xLastExecutionTime, 9 / portTICK_RATE_MS);
		//taskYIELD(); 
		//for(i=10;i<1000;i++){asm("nop");};						// �������� ��� �� �� ������ ������ �������� � ��������
			
		}//if(menu_level_choice==3)
		taskYIELD(); 
	}//for
	vTaskDelete(NULL);
};

void vApplicationIdleHook( void )
{
	/* ��� ������� ���� ������ �� ������, ����� ����������������� ��������. */
	ulIdleCycleCount++;
	////BEEP(2);
	//	num2str(ulIdleCycleCount,str_show);
	//	Draw_string (4,nodot, str_show , 0, 3, font_8_dark, fnt_width_8, front_color);
	taskYIELD();
};
//___________________________ �������� ���� �������� �� eeprom _______________
void load_defaults()
{
	nastr=eeprom_read_byte(NASTR);
	switch (nastr)
	{
		case 0: vel = eeprom_read_word(VEL1); amplif= eeprom_read_byte(AMP1);	datch= eeprom_read_byte(DATCH1);	mode= eeprom_read_byte(MODE1);	calibr = eeprom_read_dword(CALB1);	break;
		case 1: vel = eeprom_read_word(VEL2); amplif= eeprom_read_byte(AMP2);	datch= eeprom_read_byte(DATCH2);	mode= eeprom_read_byte(MODE2);	calibr = eeprom_read_dword(CALB2);	break;
		case 2: vel = eeprom_read_word(VEL3); amplif= eeprom_read_byte(AMP3);	datch= eeprom_read_byte(DATCH3);	mode= eeprom_read_byte(MODE3);	calibr = eeprom_read_dword(CALB3);	break;
		case 3: vel = eeprom_read_word(VEL4); amplif= eeprom_read_byte(AMP4);	datch= eeprom_read_byte(DATCH4);	mode= eeprom_read_byte(MODE4);	calibr = eeprom_read_dword(CALB4);	break;
		case 4: vel = eeprom_read_word(VEL5); amplif= eeprom_read_byte(AMP5);	datch= eeprom_read_byte(DATCH5);	mode= eeprom_read_byte(MODE5);	calibr = eeprom_read_dword(CALB5);	break;
		case 5: vel = eeprom_read_word(VEL6); amplif= eeprom_read_byte(AMP6);	datch= eeprom_read_byte(DATCH6);	mode= eeprom_read_byte(MODE6);	calibr = eeprom_read_dword(CALB6);	break;
		case 6: vel = eeprom_read_word(VEL7); amplif= eeprom_read_byte(AMP7);	datch= eeprom_read_byte(DATCH7);	mode= eeprom_read_byte(MODE7);	calibr = eeprom_read_dword(CALB7);	break;
		case 7: vel = eeprom_read_word(VEL8); amplif= eeprom_read_byte(AMP8);	datch= eeprom_read_byte(DATCH8);	mode= eeprom_read_byte(MODE8);	calibr = eeprom_read_dword(CALB8);	break;
		case 8: vel = eeprom_read_word(VEL9); amplif= eeprom_read_byte(AMP9);	datch= eeprom_read_byte(DATCH9);	mode= eeprom_read_byte(MODE9);	calibr = eeprom_read_dword(CALB9);	break;
		case 9: vel = eeprom_read_word(VEL10); amplif= eeprom_read_byte(AMP10); datch= eeprom_read_byte(DATCH10);	mode= eeprom_read_byte(MODE10);	calibr = eeprom_read_dword(CALB10);	break;
	};
	ee_velocity_choice=vel;
	ee_gain_choice=amplif;
	ee_pep_numb=datch;
	settings_choice=nastr;
	ee_mode_choice=mode;
	ee_sound_choice=eeprom_read_byte (BEEP_MODE);
	ee_brightness_choice=eeprom_read_byte (BRIGHT);	
	ee_nonius_choice=eeprom_read_word(NONIUSU1 + nastr*2);
	ee_base_level_choice=eeprom_read_word(DIFFU1 + nastr*2);
	ee_grade_uplim_choice=eeprom_read_word(RAZB_H1 + nastr*2);
	ee_grade_lowlim_choice=eeprom_read_word(RAZB_L1 + nastr*2);
};
//___________________ ����� �������� � eeprom �� ��������� ___________________
void reset_defaults()	
{
	
};
//___________________________ ������������� �� _______________________________
void init(void) 
{
	///////////////////////////////////// ����������� �����					
	DDRA |= 0xFF;					//8-bit ������ �� ������� �� �����
	PORTA &= 0x00;
	DDRB =0xF0;						// ������� ������� �� ����� � ����
	PORTB =0x10;
	DDRC =0x27;						// 
	PORTC =0x00;					// �� ���� �� ����
	PORTD = 0xFF;
	DDRE =0xFE;						// RX, TX, HI_VOLT, ���������� � ����
	PORTE =0x03;					// ������������� ��������� �� RX, TX
	DDRF = 0xF4;					// �������� ������
	PORTF = 0x1C;					// ����� ��� �� ����� 
	DDRG |= 0x04;					// WR �� ����� � ����
	PORTG &= 0xFB;					// WR = 0
	DDRH = 0x03;
	PORTH = 0x00;
	DDRJ =0x60;						// �� ����
	PORTJ = 0x7F;					// ������������� ���������
	DDRK =0x00;						// �� ����
	PORTK = 0xFF;					// ������������� ���������
	DDRL =0x00;						// ���� ���������� �� ����� ������� PJ2-PJ6?
	PORTL = 0x7F;
	
	////////////////////////////////////// ���
	ADMUX = 0x80;					// ��������� ��� ��� ��������� ���������� �� ������������
	ADCSRA = 0x87;					// 86
	
	////////////////////////////////////// ��������  ���������
	PORTB &= ~_BV(RDD);
	PORTB |= _BV(GENER);			// �������� ��������� 100���
	PORTB |= _BV(RES);				// ����� ��������� ����
//	PORTB &= ~_BV(RES);				// ������� �� ������ ���� ???????????????
	asm ("nop");
	PORTB &= ~_BV(RES);                                                                                                                      
	PORTB |= _BV(RES);
	DDRK &= ~_BV(EXTPOWER);			// ���� ��� ����������� �������� �������.
	PORTK &= ~_BV(EXTPOWER);
		
	/*  ////////////////////////////////// ��������� ����������
	TCCR0A = 0x00;					// ������ 0
	TCCR0B = 0x05;					// � �������� �� ��������� ������� ADMUX = 0xC0; TCCR0A = 0x05; ����� ���������� � get_mesure
	TCNT0 = 0x00;
	TIMSK0 = 0x00;*/
/*
	TCCR1A = 0x00;					// ������ 1 - Normal port operation
	TCCR1B = Prescaler;				// (prescaler)
	TCCR1C = 0x00;
	TIMSK1 = 0x01;					// Timer Interrupt Mask Enable - Overflow Interrupt Enable

	TCCR2A = 0x00;					// ������ 2
	TCCR2B = Prescaler;				// (prescaler)
	TIMSK2 = 0x01;					// Timer Interrupt Mask Enable - Overflow Interrupt Enable
/*
//	TCCR3A = 0x00;					// ������ 3
//	TCCR3B = 0x02;
//	TCCR3C = 0x00;
	//TIMSK3 = 0x01;
	//DDRB &= ~_BV(PB3);
	//DDRB &= ~_BV(PB2);
	//PCICR = 0x01;
	//PCIFR = 0x01;
	//PCMSK0 = 0x08;*/
	//SetBit(SREG,7);				// ��������� ��� ����������

};
void init_ext_eeprom()	// �������������� ������� 
{
	unsigned int journal_size=0;
	unsigned int i;
	
	
	journal_size=5;//readWEE(0);

for(i=0;i<15;i++) writeEE(i,i+1);	



	//if(journal_size<0xff)
	//{
		//writeEE(0,233);				// ������ ������ � ������
		//_delay_ms(2);
		//writeEE(4,88);
		//writeEE(2,ee_pep_numb);		// ����� �������� ��� ������
		//writeWEE(0,11);

	//	writeWEE(6,555);



		
// 		for(i=0;i<100;i++)	// � "1" !!!!!!!!!! journal_size
// 		{
// // 		//	writeWEE(i,i*4);
// // 			str_show4[0]="x";
// // 			str_show4[1]="x";
// // 			str_show4[2]="x";
// // 			str_show4[3]="x";
// 							
// 			//writeWEE(str_show4, i + 4, 1 ,dot_pos,ee_mode_choice);//page_numb_max*4
// 			//writeEE(i,0xBB);
// 			//writeWEE_old(0xCC,i*3+5);
// 			//writeWEE(i+5,unsigned long val)
// 			writeEE(i*2+5,i);
// 			//_delay_ms(3);
// 		}
// 	}
	
// 		for(i=0;i<100;i++)	// � "1" !!!!!!!!!! journal_size
// 		{
// 			//read_byte=readEE(i);	
// 			read_byte=readWEE(i);
// 			eeprom_write_byte(CALIBD+i,read_byte);
// 			
// 			num2str_left(read_byte,str_show);
//             //num2str_right(read_byte,str_show);
// 			//num2str_3_zeros(read_byte,str_show);
// 			//str_show[3]="+";
// 			if(i<4)Draw_string (4,nodot,str_show, 0,i%4, font_8_dark, 8, back_color);
// 			
// 			//Draw_string (4,nodot,str_show, i/4,i%4, font_8_dark, 8, back_color);
// 		}

//	for(;;);	///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
};
//////////////////////////////////////////////////////////////////////
void CONFR(void)  //// ����� ������� � ��
{
//	unsigned long ttt;
//	unsigned char *sss[1];
	unsigned char *str_show4[4];
	SNUMWR(0xE0);
	//sss[0]=RXBI;


	num2str_left(RXBI,str_show4);
	Draw_small_num(3,nodot,str_show4, 10,1, font_8_dark, fnt_width_8, front_color);


	//posss++;
	/////////////////////////////////////////////////////// RS 232  ����� ������� /////////////////////////////////////////////
	if (!(RXBI==0)) {TOFFVAL=0; TIMSK0 = 0x00;} // ����� �������� 5����� ��� ����������  ���������� ������� ���������� ������� ��� ������� �������
	
	
	if (RXBI=='S')  /// ������ ��������� ������
	{
		BEEP(4);
		RXBI=0;
		
		//UCSR0B = (0<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); /// ���� ���������� ������ ���� � ����� ������
		
		USART_SEND_Byte(0x05);/// �������� ������, �� ������ ����������
		
		
		if (0xE0==SNUMWR(2))
		{
			RWN(); /// ������ ������ �������
		}
		
		//UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); /// ����� ���������� ����� �� ������
	}
	if (RXBI=='T')  /// ������ ��������� �������
	{
		
		Send_NARU(); //!!!!!!!!!!!!!!!
		//USART_SEND_Byte(TRAB>>24);  /// �������� ������� ���������
		//USART_SEND_Byte(TRAB>>16);
		//USART_SEND_Byte(TRAB>>8);
		//USART_SEND_Byte(TRAB);
		//BEEP(4);
		RXBI=0;
	}
	
	if (RXBI=='J') //// ������ �������� �����������, ��������� ������ �� ������  ---  1 ��� ������, 2 ��00 -- ��� �� ����� ������, 3��00+1 -- ��� ��
	{
		//BEEP(4);
		RXBI=0;
		
		//UCSR0B = (0<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); /// ���� ���������� ������ ���� � ����� ������
		
		SENDUFORG(); //// �������� ������  !!!!!!!!!!!
		
		//UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); /// ����� ���������� ����� �� ������
	}
	
	if (RXBI=='L')
	{
		
		//BEEP(4);
		RXBI=0;
		//UCSR0B = (0<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); /// ���� ���������� ������ ���� � ����� ������
		/////SENDUFILE(); //// �������� ���� !!!!!!!!!!!!!!!!!!!
		//UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); /// ����� ���������� ����� �� ������
	}
	
	if (RXBI=='R')
	{
		
		RXBI=0;
		
		//UCSR0B = (0<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); /// ���� ���������� ������ ���� � ����� ������
		
		SEND_ST(GET_SN);/// �������� ����� �������
		
		//UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); /// ����� ���������� ����� �� ������
		
	}
	
	if (RXBI=='F')
	{
		RXBI=0;
		
		USART_SEND_Byte('i'); /// �������� ������ �� ������� ��� ����������
	}
	
	if (RXBI=='V') /// ������ ����������
	{
		RXBI=0;
		
		
		
		SEND_VOLT(voltsb);//// �������� ����������
	}
	
	
	if (RXBI=='P') /// ������ ����������
	{
		RXBI=0;
		
		//USART_SEND_Byte(voltp);
		
		SendUT();
	}
	
	
	if (RXBI=='x') /// ������ ���������� �����
	{
		RXBI=0;
		
		USART_SEND_Byte(voltp);
		
		//SendUT();
	}
	
	
	if (!(RXBI == 0))
	{
		RXBI = 0;
		
		//UCSR0B = (0<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); /// ���� ���������� ������ ���� � ����� ������
		
		SEND_ST(M00err);/// -- ��� ����� �������
		
		//UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); /// ����� ���������� ����� �� ������
	}
	
	RXIUART=0; /// �����
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
};
void send_settings(void)
{
	unsigned int k=0;

	for (k=0;k<320;k++)
	{
		USART_SEND_Byte(eeprom_read_byte(k));
	}
}
void send_contents(void)
{
	unsigned int k=0;
	
	for (k=0;k<3508;k++)//4008
	{
		USART_SEND_Byte(eeprom_read_byte(journal_addr+k));
	}
	
}
void send_journal(void)
{
	unsigned long i,size_frn,offset;
	unsigned char status_byte,chbt;
	unsigned char str_show_temp[4];

	
	//size_frn= page_numb_max*4+ee_page_numb*3 + 4;
	size_frn=80;
	
i=0;

	while(i<size_frn)
	{

		if(i>offset)
		{
		USART_SEND_Byte(CR);//������� ������ � ������� �������
		USART_SEND_Byte(LF);//����� ������
 			status_byte = eeprom_read_byte(journal_addr+i);
			 i++;
			if(TestBit(status_byte,7))
			USART_SEND_Byte('-'); 				// ���� "-" 0x2D
			else USART_SEND_Byte(' ');			// 0x20

	 		num2str_right(eeprom_read_word(journal_addr+i),str_show_temp);		
			i+=2;						

	 		
			USART_SEND_Byte(str_show_temp[0]);		// ������ ����� 
	 		if(TestBit(status_byte,4))
			{
				 //dot_pos=2; 
				 USART_SEND_Byte(str_show_temp[1]);
				 USART_SEND_Byte(str_show_temp[2]);		
				 USART_SEND_Byte('.');				//"." 0x2E
				 USART_SEND_Byte(str_show_temp[3]);		
			}else 
			{
				// dot_pos=1;
				 USART_SEND_Byte(str_show_temp[1]);	
				 USART_SEND_Byte('.');				//"."
				 USART_SEND_Byte(str_show_temp[2]);	
				 USART_SEND_Byte(str_show_temp[3]);
			}
			
			
	 		USART_SEND_Byte('�');//"�" 0x6D
			USART_SEND_Byte('�');	//0xAC	 		
	 		USART_SEND_Byte(' ');  //" "
	 		USART_SEND_Byte(mode_name[status_byte & 0x07]);//mode_name_engc
			//USART_SEND_Byte(status_byte & 0x07);
		}else
		{
			
			chbt=eeprom_read_byte(journal_addr+i);
			USART_SEND_Byte(chbt);
			i++;
		}
	}
	
}
//_________________________________________________________________________________
int main(void)
{ 
	portBASE_TYPE ret1,ret2,ret3,ret4,ret5,ret6;
//	unsigned int i;

	init();
	//_delay_ms(600);
	i2c_init();		// ������ � I2C EEPROM ������� 
	initmem();	// ��������� �� ������� �������� � ��������� ���� ��� �� �������� ��
	
	nastr=eeprom_read_byte(NASTR);
	settings_choice=nastr;
	RPM();
	RPR();
	cfgr_load(ee_gain_choice,datch);				// �������� �������� � �������� ���������� �����.	
	//load_defaults();								// ��������� ��������� � RAM
	USART_Init(MYUBRR);
	OLED_on();										// �������������� OLED �������
		
	init_ext_eeprom();								// ������������ ����� ������
/*	
	char i=0;
	unsigned char str[]={"1234"},chr;

	for(i=0;i<4;i++)
	{
		chr=str[i]-32;
		if(i==3)
		{
			Draw_symbol(&font_8_dark[(chr+146)*64],0+i,0,8,8*2,front_color);
		}else
			Draw_symbol(&font_8_dark[chr*64],0+i,0,8,8*2,front_color);		// ���� ������� ��� ������ 16x32  chr*128 !!!!!!!!!!!!!
	}

//		Draw_string(32,nodot,"������������ABCDEFGH�abcdefghij����",0,0,font_8_dark,fnt_width_8,front_color);
Draw_string(10,nodot,"0123456789",0,1,font_8_dark,fnt_width_8,front_color);
Draw_string(32,nodot,"������������������������������",0,2,font_8_dark,fnt_width_8,front_color);
Draw_string(26,nodot,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",0,3,font_8_dark,fnt_width_8,front_color);
//Draw_string(26,nodot,"abcdefghijklmnopqrstuvwxyz",0,2,font_8_dark,fnt_width_8,front_color);
for(;;);	*/
	
	Show_Logo();									// ���������� ������� "���", ��������� � ����� logo.h
	BEEP(2);
	delay_in_cycle(delay_4sec);						// delay_4sec
	//_delay_ms(900);	
	//cls();
	screen_refresh=true;
	
///////////////////////////// ���������  /////////////////////////////////
// for(i=0;i<3;i++) 
// {		
// 		read_byte=readEE(i);
// 		num2str_left(read_byte,str_show);
// 		Draw_string (4,nodot,str_show, 15,i, font_8_dark, 8, back_color);
// };
// 		//BEEP(2);
// 		read_byte=readWEE(3);
// 		num2str_left(read_byte,str_show);
// 		Draw_string (4,nodot,str_show, 0 ,1, font_8_dark, 8, back_color);
// 
// //i2c_EXT_Send(10, 30, localBuffer);
// 
// for(i=0;i<7;i++)
// {
// 	writeEE(i+1,i+10);
// };
// 
// for(i=0;i<7;i++)
// {
// 	read_byte=readEE(i);
// 	num2str_left(read_byte,str_show); 
// 	Draw_string (4,nodot,str_show, i*4,3, font_8_dark, 8, back_color);
// };
// for(;;)
// {
// 	
// 	if(UCSR0A & (1<<RXC0))
// 	{
// 		USART_SEND_Byte(UDR0);
// 		BEEP(2);
// 		send_journal();
// 	}
// 	//CONFR();
// }
//  	for(;;);
///////////////////////// ����� ���������  /////////////////////////////

	xMutex = xSemaphoreCreateMutex();				// ������� ���������� ��������

	ret1 = xTaskCreate( vReadButtons,(signed char *) "Butt",260,NULL,1,NULL );
	ret2 = xTaskCreate( vConnect,    (signed char *) "ConnFunc",250,NULL,1,NULL );
	ret4 = xTaskCreate( vMain_functions,(signed char *) "MainFunc",990,NULL,1,NULL );
	ret5 = xTaskCreate( vService_functions,(signed char *) "ServFunc",900,NULL,1,NULL );
	ret6 = xTaskCreate( vDialogues,(signed char *) "Dialogue",990,NULL,1,NULL );

    if(ret1 && ret2 && ret4 && ret5 && ret6) Draw_string(8,nodot, "tasks-OK" , 0, 0, font_8_dark, fnt_width_8, front_color);
    else Draw_string(11,nodot, "tasks-ERROR" , 0, 0, font_8_dark, fnt_width_8, front_color);
	
	vTaskStartScheduler();							// ��������� RTOS 
	for(;;){};
};

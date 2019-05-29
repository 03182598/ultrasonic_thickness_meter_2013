//#define F_CPU 3533200UL
#define F_CPU 8000000UL
//#define FOSC 4000000		// Clock Speed
#define FOSC 8000000		// Clock Speed
#define BAUD 19200
#define MYUBRR 12			//FOSC/16/BAUD-1  38400 12

#define pgm_read_byte_near(address_short) \
__LPM((uint16_t)(address_short))
//================================================//
#define WRITE_EEPROM   	while((EECR&0x2)!=0){} \
EECR |= 0x4; \
EECR |= 0x2; \
while((EECR&0x2)!=0){}
#define READ_EEPROM   	while((EECR&0x2)!=0){} \
EECR |= 0x1;
//=================== ���������� =================//
#define false 0x00
#define true 0xFF
#define SetBit(Port,BitNo) (Port) |= (1<<(BitNo))
#define ResetBit(Port,BitNo) (Port) &= ~(1<<(BitNo))
#define TestBit(Port,No) (((Port)&(1<<(No)))==0?false:true)

#define CS	3
#define SDA 4
#define SCL 5

///////////////////////////////////////////////////////////////////////////////////// �� devcfg.h
//������ �����������    verHa+verHb . verSa+verSb  ==  ������ H01.S01
#define verHA 0
#define verHb 2
#define verSa 0
#define verSb 5

/// ����������
#define keyup 7			//7
#define keydown 8		//8
#define keyenter 9
#define keyrezim 4
#define keynastr 5
#define keyzero 2
#define keypep 1 // 1?
#define keymem 6
#define key_off 1

#define btn1 1				// 
#define btn2 2				// 
#define btn3 3				// 
#define btn4 4				// 
#define btn5 5				// 
#define btn6 6				//
#define btn7 7				// 
#define btn8 8				//
#define btn9 9				//

#define LF 10				// ������� ������
#define CR 13				// ������� �������

#define M00err 0			// ������ 00 uart   -- ��� ����� �������
#define M01err 1			// ������ 01 uart	 -- ��� ������ �����
#define M02err 2			// ������ 02 uart	 -- �������� ��������� �������� ������� ��� ��������� ������ �� �������
#define M03err 3			// ������ 03 uart	 -- ������������ ������ ������ (������ ���� ascii ������ �������)
#define END_S  4			// ����� ��������	�������� �������  , ������ ������ ��� ����
#define GET_SN 5			// ��������� ����� �������
#define W_OK   6			// �������� ������� ���������
#define FF0err 7			// ������ �������� �����
#define BOKV   8			// ����� �����
#define BTOT   9			// ������� �����

//// ������� ����������� ��������
/*
!! 1 ������ �������� ����������� ����� ������. ����� ���� ����� �������� �� 1.5���  ��� ���������

S % * * * *  �������� � ������ ****- �������� ����� 4 ����� (����� ������� ���� ��������� ����� ����� � ���� ��������� � ���������� ������ ������)

T  - ������ ��������� ������� (���������� �����)

J - ������ �������� �����������  (���������� �����)   1 ������� ���������� ������ � �������, ��������� ������ (�� ��� �� ����� ����� ������) ���������
������� ����� ������������ � �����. ���� 0 ���� ����.  ��������� ������ � 00 �� 99

L % * * ��������� ���� ** ����� �����.  �������� ������ ���������� � 00000 ������ ����� � �� ���������. ���� ���� � ����� ���� c
����������� �� ����� ���� 400 �����. ����� �������� B** - ������� ����� ����� � ����� �����, ��� ����������� �������� ���������� z ���� ������ ������
���������� ������ �������� ����� FF0.  ������ ��� � ������ �� 300�����. � ����� 600����� ���� 1 � ����� ������� B**-z ������ END
����� �����

����� ����� B** ����� ����� �� 10 �� ���� 59  ��� ������� 1� ���� ����� 10 ��� 00����  11���� ��� 1����  59���� 49����

20000����� / 400 = 50������   00-49   = 10-59.    � ��������� �� ����� -10.

��� �������� ���� ���������� �������, ����� ���������� (��������� ������) ������� ������ ����� � ���������� ������� ������ ���������� ������
�� ������� J

P - ������� ������� �� ������� �������

����� ��������� ���� 400 ����� ������ 20000�� ����������� ������ � ���� ������. ���� � ����� � ������� ���� ���������.
������ ��������  X01234  X - ����� ��������

*/

#define LowSPEED 100					// ����������� �������� ���
#define HISPEED 9999					// ������������ �������� ���
#define CALVL 6043						// �������� � 3 �� �������.
#define stbokh  15000					// ��������� �������� ��������� ������� � ������� �����  ����� ��� ������� ������
#define stbokl  7500					// ����� ��� ������� ����������.
#define maxPEP 9						// ������������ ����� �������� � �������

#define high_resolution 100				// ����� ������� � �� ��� ����� ���������� ��������� ��������

#define step_speedX  12					// 40 // ��� ��������� �������� �������� 000
#define step_speed0  18					// 40 18// ��� ��������� �������� ��������
#define step_speeda  250				// ��� ���������  �������� ��������

#define key_read_delay 1				// ������� ���������� ���������� 0,001*4M/256=15�� 1000 2084  0
#define key_repeat 15					// �������� ������� ������ 15
#define Prescaler 0x01

#define step_speedZ  180				// 180 ��� ���������  �������� ��������

#define step_apx 50						// ��� ��������� �� ��������� �������� ���������
#define readfilest 370					// ��� ��������� ����� ����� � ��������� ������
#define readfilestE 500					// ��� �������� ��������



#define RAZBRH_low 31					// ������� ������� �����������
#define RAZBRH_hi 30000

#define RAZBRL_low 30
#define RAZBRL_hi 29990

#define NONIUSL 0						//  ������� ������	// -5.00��
#define NONIUSH 1000					// +5.00��

#define DIFFHI 30000					// ������� ������� ���� 300.0��
#define DIFFLO 30						// ������ ������� ���� 0.30��


#define SCANMAX 65000					// ���� ���� ������ ��� ������������


#define MaxHiS 30000					// ������������ ������� ��� ���������� �� �������
#define MinHiS 10						// ����������� ������� ��� ���������� �� �������

#define calobr3mm 3185					// ���� ������� 3�� ������� 1-6 3185
#define calobr5mm 5402					// 5467 5308		// ���� ������� 5 �� ������ 7
#define calobr20mm 21611				//21233		// ���� ������� ������� 8-9

#define vel3mm 6043						// �������� � �������� ������� 3 ��
#define vel5mm	5930					// �������� � �������� ������� 5 ��
#define vel20mm 5920					// �������� � �������� ������� 20��



#define STAT (unsigned int*)0x0000		// ��������� ��� ���������, ���� ������ ������

//#define SNUMS 0x0002					// �������� ����� ������� word
//#define NARAB 0x0004					// ��������� �� �����	dword

#define VELMEM  (unsigned int*) 0x0010		// �������� ���
#define NUMDATC (unsigned char*)0x1A		// ����� ������� ���
#define MODES   (unsigned char*)0x0020		// ��������� �������  �� ���� � ������� ������
#define MEMCFG  (unsigned int*) 0x02A		// ����������� ������ ������ ���������
#define MEMPNT  (unsigned int*) 0x030		// ��������� ������ �� �������
#define NASTR   (unsigned char*)0x035		// ����� ���������
#define CALIBD  (unsigned int*) 0x130		// ������� �������� ���������� 0
#define BRIGHT  (unsigned char*)0x38		// ������� �������� �������.
#define MINUTES_OFF (unsigned char*)0x132	// �������������� �����
#define VEL1  (unsigned int*)0X040 //C������� ���������1
#define VEL2  (unsigned int*)0X042 //C������� ���������2
#define VEL3  (unsigned int*)0X044 //C������� ���������3
#define VEL4  (unsigned int*)0X046 //C������� ���������4
#define VEL5  (unsigned int*)0X048 //C������� ���������5
#define VEL6  (unsigned int*)0X04A //C������� ���������6
#define VEL7  (unsigned int*)0X04C //C������� ���������7
#define VEL8  (unsigned int*)0X04E //C������� ���������8
#define VEL9  (unsigned int*)0X050 //C������� ���������9
#define VEL10 (unsigned int*)0X052 //C������� ���������10

#define AMP1  (unsigned char*)0X054 //�������� ���������1
#define AMP2  (unsigned char*)0X056 //�������� ���������2
#define AMP3  (unsigned char*)0X058 //�������� ���������3
#define AMP4  (unsigned char*)0X05A //�������� ���������4
#define AMP5  (unsigned char*)0X05C //�������� ���������5
#define AMP6  (unsigned char*)0X05E //�������� ���������6
#define AMP7  (unsigned char*)0X060 //�������� ���������7
#define AMP8  (unsigned char*)0X062 //�������� ���������8
#define AMP9  (unsigned char*)0X064 //�������� ���������9
#define AMP10 (unsigned char*)0X066 //�������� ���������10

#define DATCH1  (unsigned char*)0X070 //������ ���������1
#define DATCH2  (unsigned char*)0X071 //������ ���������2
#define DATCH3  (unsigned char*)0X072 //������ ���������3
#define DATCH4  (unsigned char*)0X073 //������ ���������4
#define DATCH5  (unsigned char*)0X074 //������ ���������5
#define DATCH6  (unsigned char*)0X075 //������ ���������6
#define DATCH7  (unsigned char*)0X076 //������ ���������7
#define DATCH8  (unsigned char*)0X077 //������ ���������8
#define DATCH9  (unsigned char*)0X078 //������ ���������9
#define DATCH10 (unsigned char*)0X079 //������ ���������10

#define MODE1  (unsigned char*)0x080 //����� ������ ���������1
#define MODE2  (unsigned char*)0x081 //����� ������ ���������2
#define MODE3  (unsigned char*)0x082 //����� ������ ���������3
#define MODE4  (unsigned char*)0x083 //����� ������ ���������4
#define MODE5  (unsigned char*)0x084 //����� ������ ���������5
#define MODE6  (unsigned char*)0x085 //����� ������ ���������6
#define MODE7  (unsigned char*)0x086 //����� ������ ���������7
#define MODE8  (unsigned char*)0x087 //����� ������ ���������8
#define MODE9  (unsigned char*)0x088 //����� ������ ���������9
#define MODE10 (unsigned char*)0x089 //����� ������ ���������10

#define CALB1  0x08A // ���������� � ����� 1
#define CALB2  0x08C // ���������� � ����� 2
#define CALB3  0x08E // ���������� � ����� 3
#define CALB4  0x090 // ���������� � ����� 4
#define CALB5  0x092 // ���������� � ����� 5
#define CALB6  0x094 // ���������� � ����� 6
#define CALB7  0x096 // ���������� � ����� 7
#define CALB8  0x098 // ���������� � ����� 8
#define CALB9  0x09A // ���������� � ����� 9
#define CALB10 0x09C // ���������� � ����� 10

#define BEEP_MODE 0x09E // ���������� �����

#define RAZB_H1  0x0A0 // ������ ���� ��� ��� ����������� � ���������1 word
#define RAZB_H2  0x0A2
#define RAZB_H3  0x0A4 
#define RAZB_H4  0x0A6
#define RAZB_H5  0x0A8 
#define RAZB_H6  0x0AA
#define RAZB_H7  0x0AC 
#define RAZB_H8  0x0AE
#define RAZB_H9  0x0B0 
#define RAZB_H10 0x0B2
#define RAZB_L1  0x0B4 
#define RAZB_L2  0x0B6
#define RAZB_L3  0x0B8 
#define RAZB_L4  0x0BA
#define RAZB_L5  0x0BC 
#define RAZB_L6  0x0BE
#define RAZB_L7  0x0C0 
#define RAZB_L8  0x0C2
#define RAZB_L9  0x0C4 
#define RAZB_L10 0x0C6

// ��������� ����� �������     ������ 3.2.1.0.  4 ����� ���� �� ������.

#define ZNUM0 0x110 // ������ ������ ������� 0
#define ZNUM1 0x111	// ������ ������ ������� 1
#define ZNUM2 0x112	// ������ ������ ������� 2
#define ZNUM3 0x113	// ������ ������ ������� 3
#define TNAR  0x120 // DWORD ���������   1�� ��� 1������   ���� ����� 71582.7882 ������ �����

#define DIFFU1 0x0D0 // ����� ���� ������ � ��������� 1 word
#define DIFFU2 0x0D2 // ����� ���� ������ � ��������� 2
#define DIFFU3 0x0D4 // ����� ���� ������ � ��������� 3
#define DIFFU4 0x0D6 // ����� ���� ������ � ��������� 4
#define DIFFU5 0x0D8 // ����� ���� ������ � ��������� 5
#define DIFFU6 0x0DA // ����� ���� ������ � ��������� 6
#define DIFFU7 0x0DC // ����� ���� ������ � ��������� 7
#define DIFFU8 0x0DE // ����� ���� ������ � ��������� 8
#define DIFFU9 0x0E0 // ����� ���� ������ � ��������� 9
#define DIFFU10 0x0E2 // ����� ���� ������ � ��������� 10

#define DIFFP1  (unsigned char*)0x0E4 // ���������� � ���� ������ � ��������� 1 byte
#define DIFFP2  (unsigned char*)0x0E5 // ���������� � ���� ������ � ��������� 2
#define DIFFP3  (unsigned char*)0x0E6 // ���������� � ���� ������ � ��������� 3
#define DIFFP4  (unsigned char*)0x0E7 // ���������� � ���� ������ � ��������� 4
#define DIFFP5  (unsigned char*)0x0E8 // ���������� � ���� ������ � ��������� 5
#define DIFFP6  (unsigned char*)0x0E9 // ���������� � ���� ������ � ��������� 6
#define DIFFP7  (unsigned char*)0x0EA // ���������� � ���� ������ � ��������� 7
#define DIFFP8  (unsigned char*)0x0EB // ���������� � ���� ������ � ��������� 8
#define DIFFP9  (unsigned char*)0x0EC // ���������� � ���� ������ � ��������� 9
#define DIFFP10 (unsigned char*)0x0ED // ���������� � ���� ������ � ��������� 10

#define NONIUSU1 0x0F0 /// �������� ������� ��� ������ ������ � ��������� 1 word
#define NONIUSU2 0x0F2 /// �������� ������� ��� ������ ������ � ��������� 2
#define NONIUSU3 0x0F4 /// �������� ������� ��� ������ ������ � ��������� 3
#define NONIUSU4 0x0F6 /// �������� ������� ��� ������ ������ � ��������� 4
#define NONIUSU5 0x0F8 /// �������� ������� ��� ������ ������ � ��������� 5
#define NONIUSU6 0x0FA /// �������� ������� ��� ������ ������ � ��������� 6
#define NONIUSU7 0x0FC /// �������� ������� ��� ������ ������ � ��������� 7
#define NONIUSU8 0x0FE /// �������� ������� ��� ������ ������ � ��������� 8
#define NONIUSU9 0x100 /// �������� ������� ��� ������ ������ � ��������� 9
#define NONIUSU10 0x102 /// �������� ������� ��� ������ ������ � ��������� 10

#define NONIUSP1 (unsigned char*)0x104 /// ���������� �������� ��� ������ ������ � ��������� 1 byte
#define NONIUSP2 (unsigned char*)0x105 /// ���������� �������� ��� ������ ������ � ��������� 2
#define NONIUSP3 (unsigned char*)0x106 /// ���������� �������� ��� ������ ������ � ��������� 3
#define NONIUSP4 (unsigned char*)0x107 /// ���������� �������� ��� ������ ������ � ��������� 4
#define NONIUSP5 (unsigned char*)0x108 /// ���������� �������� ��� ������ ������ � ��������� 5
#define NONIUSP6 (unsigned char*)0x109 /// ���������� �������� ��� ������ ������ � ��������� 6
#define NONIUSP7 (unsigned char*)0x10A /// ���������� �������� ��� ������ ������ � ��������� 7
#define NONIUSP8 (unsigned char*)0x10B /// ���������� �������� ��� ������ ������ � ��������� 8
#define NONIUSP9 (unsigned char*)0x10C /// ���������� �������� ��� ������ ������ � ��������� 9
#define NONIUSP10 (unsigned char*)0x10D /// ���������� �������� ��� ������ ������ � ��������� 10

#define i2cdel	asm volatile("nop"); asm volatile("nop"); asm volatile("nop");asm volatile("nop"); asm volatile("nop"); asm volatile("nop");

#define eeRD 0xA1			// ���������� �����  ��� ������ ������
#define eeWR 0xA0			// ���������� �����  ��� ������ ������

#define idel 1				// �������� i2c
#define SDA_LN PH1          // ����� SDA
#define SCL_LN PH2          // ����� SCL
#define I2C_PIN PINH		// ���� �����
#define I2C_DDR DDRH		// ���� �����������
#define I2C_PORT PORTH		// ���� ������

#define IN_LN 0				//����� �� ����
#define OUT_LN 1			//����� �� �����

#define ACK 1				//�������� ������������� ������ (�� ��������� ����)
#define NOT_ACK 0			//�� ������������ ����� (��������� ����)

#define I2C_T 0.00001		//������ �������� ������������� (1/I2C_T = ������� ����)
//��� ����������� ���������� ����

//! #define SDA PH1
//! #define SCL PH2

#define mSCL PJ1			// ����� ���� ������
#define mSDA PJ0			// ����� ������
#define EEPJ PORTJ
#define INPJ PINJ

#define SDLDAC PF5			// ����� ���
#define SCLDAC PF6
#define	SYCDAC PF7

#define BEEPX PE4
//.EQU BEEPX= 4				//porte 4 out

#define BEEPM0 PE5
//.EQU BEEPM0= 5			//porte 5 out
#define BEEPM1 PE6
//.EQU BEEPM1= 6			//porte 6 out

#define KEY_RES PE7
//.EQU KEY_RES= 7			//porte 7 out

#define KEY_OK PL2
//.EQU KEY_OK= 2			//portj 2 out

#define KEY_PORT PINL       // ���� ���������� PJ3-PJ6
#define ONKEY PF3			// ������� ������� ������� ���������.
#define EXTPOWER PK5		// ����� 0 - ���������� ������� ������� !!!

#define ZG_IN PE3
//.EQU ZG_IN = 3// porte 3  out
#define Hi_volt  PE2
//.EQU Hi_volt = 2// porte 2 out
#define SDAT  PC0
//.EQU SDAT =  0// portc 0  out
#define SCLK  PC1
//.EQU SCLK =  1// portc 1  out
#define STROB PC5
//.EQU STROB = 5// portc 5  out
#define CDIM  PC2
//.EQU CDIM = 2// portc 2 out

#define GENER  PB4
//.EQU GENER = 4// portb 4 out
#define RES PB6
//.EQU RES =	 6// portb 6 out
#define RDD PB7
//.EQU RDD = 	 7// portb 7 out

#define XDPX PB5
//.EQU XDPX =  5 // portb 5 in
#define DATA_OK PG1
//.EQU DATA_OK = 1 //portg 1 in
#define END_T PG0
//.EQU END_T = 0 //portg 0 in
#define DATAX PIND
//.EQU DATAX = pind// DATA port in

#define acontpin PH0
#define razbr_alrm PH3

#define ADCBATPIN PF0
#define DDSDAT PH4
#define DDSCLK PH5
#define DDSFQU PH6

/////////////////////////////////////////////////////////////////////////////////////
#define nonius_half_range 500			// �������� ��������� ������� 0-499 �������������, 500-1000 �������������
#define range_switching_threshold 10000 // ���� ����� 100�� �� 0,1 ����� 0,01
#define long_max 0xffffffff
#define int_max  0xffff
#define lowlim 60						// 0.6 ��
#define uplim 50000						// 500 ��
///////////////////////////////////////////////////////////////////////////////////////
#define clear_color 15
#define back_color_const  9
#define half_color 12
#define front_color 0
#define inverse_color 16
#define fnt_width_8 8					// ������ ������ � ������
#define fnt_width_16 16					// ������ ������ � ������
#define scrol_pos 31					// ��������� ������ ���������
#define limits_pos 27					// ��������� ������ �����

#define number_offset 48				// �������� ���� � ������� ascii 
#define number_dot_offset 179			// �������� ���� � ������� ascii 
#define dot 1							// ���� ����� � ������
#define nodot 0							// ��� ����� � ������
#define nobigdot 0xff					// ��� ����� � ������� ������

#define delay_8sec 72					// �������� � 8 ������ 
#define delay_5sec 60					// �������� � 4 ������� 
#define delay_4sec 36					// �������� � 4 ������� 
#define delay_3sec 26					// �������� � 3 ������� 
#define delay_2sec 18					// �������� � 2 ������� 9
#define delay_1sec 8					// �������� � 1 ������� 8
#define delay_05sec 4					// �������� � 0.5 ������� 4

#define key_pwr_limit 10				// �������� ��������� ������ ���������� 30
#define bright_speed 20					// �������� "�������" ������ ��� ���/����
//____________________ ��������� ����� ������ �� ������ [measurement] _________
#define measure_pos 6					// ������� ��������� ��������� main_value
#define measure_raw 1					// ������ ��������� ��������� 
#define pep_pos 0						// ������� ���� ��� � ������
#define pep_raw 0						// ������ �������� �������
#define velocity_pos 2					// ������� ��������
#define velocity_raw 3					// ������ ��������
#define velocity_lim_pos 27				// ������� ������ ��������� ��������
#define journal_pos 21					// �������: �������� ������� + ����� ��������� 0..31
#define journal_raw 3					// ������ �������


//_____________________________ ��������� ������� ���� ________________________
#define item2show 3						// ���������� ������� ���� ��� ����������� 
#define item2show_file 4				// ���������� ������� ���� ��� �����������
#define menu_modes_length 5				// ���������� ������� � ���� "������"
#define func_delay 30					// �������� ����� ������� 30
#define acont_delay 0x00FF			// �������� ���������� �� ��� ������������
#define dlg_nonius 1					// 
#define dlg_deviation 2					//
#define dlg_grade_lower 3				//
#define dlg_grade_upper 4				//
#define dlg_settings_autopower 5		//
#define dlg_settings_screen 6			//
#define dlg_settings_sound 7			//
#define dlg_settings_gain 8				//
#define dlg_settings_reset 9			//
#define dlg_calibration_zero 10			//
#define dlg_calibration_velocity 11		//
#define dlg_calibration_H 12			//
#define dlg_journal_clear 13			//
#define dlg_entry_clear 14				//
#define dlg_page_view 15				//
#define dlg_thickness_input 16			//
#define dlg_calibration_zero_input 17	//

#define page_numb_max 100				// ������������ ���������� ������� � �������
#define page_numb_min 0					// ����������� ���������� ������� � �������
#define page_size_max 1000				// ������������ ������ �������� (� �� �������) ���������� �������� ������
#define scr_raw 4						// ���������� ����� �� ������ "������"
#define scr_col 31						// ���������� �������� � ������ �� ������ "������"
#define focus_raw 1						// ����� ������ � �������: 0 1 2 3

#define journal_row_num 125
#define journal_col_num 16
#define journal_buf    journal_row_num*journal_col_num
#define entry_size 3					// ���������� ���� � ������
#define entry_offset   page_numb_max*4	// 4 ����� ��� �������� ��������
#define journal_addr 0x140
#define journal_commands 2				// ���������� ������ � ������ �������
#define contents journal_addr+0x04		// �������� ����������
#define pages_addr contents+page_numb_max*4	// �������� �������� 0 (������ �������)
//_____________________________________________________________________________
#define language_rus					// ����� ����� ����: language_rus, language_eng, language_trl.
#define mode_numb 5						// ����� ������� ���� ������

#define maket_build						// ��������� ������ � ������ �������, ���� ������� �� ��������� 
										//#define rotate_screen	// ��������� ������, ���� �� ���� - �������������
 
//____________________________ ���� ������� �� ���������� _____________________
#define menu_modes_width 12				// �� 12 ��������
#define menu_modes_big_pos 2			// ��� ������� ����
#define menu_modes_pos 10				// ������� � �������� �� ������ ����
#define modes_numb 5					// ���������� ������� ���� ������
#ifdef   language_eng
		#define menu_modes_line0 " MEASUREMENT"				
		#define menu_modes_line1 "  SCANNING  "
		#define menu_modes_line2 "    GRADE   "
		#define menu_modes_line3 "  DEVIATION " 
		#define menu_modes_line4 "   NONIUS   "
#endif
//____________________________ ���� ������� �� ������� ________________________
#ifdef   language_rus
		#define menu_modes_line0 "  ��������� "	
		#define menu_modes_line1 "������������"
		#define menu_modes_line2 " �����������"
		#define menu_modes_line3 " ���������� "
		#define menu_modes_line4 "   ������   "


#endif
//____________________________ ���� ������� �� �������������� _________________
#ifdef   language_trl
		#define menu_modes_line0 "  IZMERENIE "
		#define menu_modes_line1 "SKANIROVANIE"
		#define menu_modes_line2 " RAZBRAKOVKA"
		#define menu_modes_line3 " OTKLONENIE "
		#define menu_modes_line4 "   NONIUS   "

#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ ���� �������� �� ���������� _____________________
#define menu_settings_width 15								// �� 20 ��������
#define menu_settings_pos 9									// ������� � �������� �� ������ ����
#define menu_settings_big_pos 0								// ��� ������� ����
#define settings_numb 16									// ���������� ������� ���� ���������
#define align_settings 0									// ������������ � ���� �������
#ifdef   language_eng
		#define menu_settings_line0   "     SETTING 1      "
		#define menu_settings_line1   "     SETTING 2      "
		#define menu_settings_line2   "     SETTING 3      "
		#define menu_settings_line3   "     SETTING 4      "
		#define menu_settings_line4   "     SETTING 5      "
		#define menu_settings_line5   "     SETTING 6      "
		#define menu_settings_line6   "     SETTING 7      "
		#define menu_settings_line7   "     SETTING 8      "
		#define menu_settings_line8   "     SETTING 9      "
		#define menu_settings_line9   "POLYETHYLENE H>25 MM" //20
		#define menu_settings_line10  "   AUTO POWER OFF   "
		#define menu_settings_line11  "       SYSTEM       "
		#define menu_settings_line12  "       SCREEN       "
		#define menu_settings_line13  "        SOUND       "
		#define menu_settings_line14  "        GAIN        "
		#define menu_settings_line15  "   RESET SETTINGS   "
#endif
//____________________________ ���� �������� �� ������� ________________________
#ifdef   language_rus
		#define menu_settings_line0   "   ��������� 1 "
		#define menu_settings_line1   "   ��������� 2 "
		#define menu_settings_line2   "   ��������� 3 "
		#define menu_settings_line3   "   ��������� 4 "
		#define menu_settings_line4   "   ��������� 5 "
		#define menu_settings_line5   "   ��������� 6 "
		#define menu_settings_line6   "   ��������� 7 "
		#define menu_settings_line7   "   ��������� 8 "
		#define menu_settings_line8   "   ��������� 9 "
		#define menu_settings_line9   "����������>25��" //16
		#define menu_settings_line10  " ��������������" //��������������
		#define menu_settings_line11  "    �������    "
		#define menu_settings_line12  "     �����     "
		#define menu_settings_line13  "     ����      "
		#define menu_settings_line14  "    ��������   "
		#define menu_settings_line15  " ����� ��������"
		
#endif
//____________________________ ���� �������� �� �������������� _________
#ifdef   language_trl
		#define menu_settings_line0   "     NASTROIKA 1     "
		#define menu_settings_line1   "     NASTROIKA 2     "
		#define menu_settings_line2   "     NASTROIKA 3     "
		#define menu_settings_line3   "     NASTROIKA 4     "
		#define menu_settings_line4   "     NASTROIKA 5     "
		#define menu_settings_line5   "     NASTROIKA 6     "
		#define menu_settings_line6   "     NASTROIKA 7     "
		#define menu_settings_line7   "     NASTROIKA 8     "
		#define menu_settings_line8   "     NASTROIKA 9     "
		#define menu_settings_line9   " POLIETILEN H>25 MM  " //20
		#define menu_settings_line10  "   AUTOVIKLUCHENIE   "
		#define menu_settings_line11  "      SISTEMA        "
		#define menu_settings_line12  "       EKRAN         "
		#define menu_settings_line13  "        ZVUK         "
		#define menu_settings_line14  "      USILENIE       "
		#define menu_settings_line15  "   SBROS NASTROEK    "
#endif



//////////////////////////////////////////////////////////////////////////////////////
//____________________________ ���� ��� �� ���������� __________________
#define menu_pep_width 19								// �� 18 ��������
#define menu_pep_pos 6									// ������� � �������� �� ������ ����
#define menu_pep_big_pos 0
#define pep_numb 9										// ���������� ��������
#ifdef   language_eng
		#define menu_pep_line0   "P112-10.0-6/2-T-003"//18
		#define menu_pep_line1   "P112-5.0-10/2-T-003"
		#define menu_pep_line2   "P112-2.5-12/2-T-003"
		#define menu_pep_line3   " P112-2.5�-12/2-B  "
		#define menu_pep_line4   " P112-5.0�-12/2-B  "
		#define menu_pep_line5   "  P112-2.5-12/2-A  "
		#define menu_pep_line6   "  P112-1.25-20/2-A "
		#define menu_pep_line7   "   P111-1.25-K20   "
		#define menu_pep_line8   "   P111-1.25-P20   "
#endif
//____________________________ ���� ��� �� ������� _____________________
#ifdef   language_rus
		#define menu_pep_line0   "�112-10.0-6/2-�-003"//0
		#define menu_pep_line1   "�112-5.0-10/2-�-003"//1
		#define menu_pep_line2   "�112-2.5-12/2-�-003"//2
		#define menu_pep_line3   " �112-2.5�-12/2-�  "//3 �������������������
		#define menu_pep_line4   " �112-5.0�-12/2-�  "//4 �������������������
		#define menu_pep_line5   " �112-2.5-12/2-�   "//5
		#define menu_pep_line6   " �112-1.25-20/2-�  "//6
		#define menu_pep_line7   " �111-1.25-�20     "//7
		#define menu_pep_line8   " �111-1.25-�20     "//8
#endif
//____________________________ ���� ��� �� �������������� ______________
#ifdef   language_trl
		#define menu_pep_line0   "P112-10.0-6/2-T-003"//18
		#define menu_pep_line1   "P112-5.0-10/2-T-003"
		#define menu_pep_line2   "P112-2.5-12/2-T-003"
		#define menu_pep_line3   " P112-2.5�-12/2-B  "
		#define menu_pep_line4   " P112-5.0�-12/2-B  "
		#define menu_pep_line5   "  P112-2.5-12/2-A  "
		#define menu_pep_line6   "  P112-1.25-20/2-A "
		#define menu_pep_line7   "   P111-1.25-K20   "
		#define menu_pep_line8   "   P111-1.25-P20   "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ ���� ���������� �� ���������� ___________
#define menu_calibration_width 13							// �� 13 ��������
#define menu_calibration_pos 9								// ������� � �������� �� ������ ����
#define menu_calibration_big_pos 2							// ������� ��� ������� ����
#define calibration_numb 3									// ���������� ������� ���� ����������
#ifdef   language_eng
		#define menu_calibration_line0 "CALIBRATION 0"				
		#define menu_calibration_line1 "CALIBRATION V"
		#define menu_calibration_line2 "CALIBRATION H"		
#endif
//____________________________ ���� ���������� �� ������� ______________
#ifdef   language_rus
		#define menu_calibration_line0 "���������� 0 "				
		#define menu_calibration_line1 "���������� V "
		#define menu_calibration_line2 "���������� H "		
#endif
//____________________________ ���� ���������� �� �������������� _______
#ifdef   language_trl
		#define menu_calibration_line0 "KALIBROVKA 0 "
		#define menu_calibration_line1 "KALIBROVKA V "
		#define menu_calibration_line2 "KALIBROVKA H "		
#endif

/*
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 1 �� ����������______________________
#define msg_1_width 32							// �� 32 ��������
#define msg_1_pos 0								// ������� � �������� �� ������ ����
#ifdef   language_eng
		#define msg_1_line0 "                                "
		#define msg_1_line1 "            Hello,              "					//32
		#define msg_1_line2 "  which mode will be measured?  "
		#define msg_1_line3 "                                "
#endif
//____________________________ msg 1 �� ������� ________________________
#ifdef   language_rus
		#define msg_1_line0 "                                "
		#define msg_1_line1 "         ������������,          "					//32
		#define msg_1_line2 " � ����� ������ ����� ��������? "
		#define msg_1_line3 "                                "
#endif
//____________________________ msg 1 �� �������������� _________________
#ifdef   language_trl
		#define msg_1_line0 "                                "
		#define msg_1_line1 "         Zdravstvuite,          "					//32
		#define msg_1_line2 " V kakom rezime budem izmeryat? "
		#define msg_1_line3 "                                "
#endif*/
/*
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 2 �� ����������______________________
#define msg_2_width 32							// �� 32 ��������
#define msg_2_pos 0								// ������� � �������� �� ������ ����
#ifdef   language_eng
		#define msg_2_line0 "Welcome, the instrument is in the"
		#define msg_2_line1 "mode        MEASURING            "						//32
		#define msg_2_line2 "setting     POLYETHYLENE H>25 MM "
		#define msg_2_line3 "gain        25                   "
#endif
//____________________________ msg 2 �� ������� ________________________
#ifdef   language_rus
		#define msg_2_line0 "������������, ������ ���������   "
		#define msg_2_line1 "� ������    ���������            "					//32
		#define msg_2_line2 "���������   ���������� H>25��    "
		#define msg_2_line3 "��������    25                   "
#endif
//____________________________ msg 2 �� �������������� _________________
#ifdef   language_trl
		#define msg_2_line0 "Zdravstvuite, pribor nahoditsya  "
		#define msg_2_line1 "v rezime                         "						//32
		#define msg_2_line2 "nastroika                        "
		#define msg_2_line3 "usilenie                         "
#endif*/
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 5 �� ����������______________________
#define msg_5_width 32							// �� 32 ��������
#define msg_5_pos 0								// ������� � �������� �� ������ ����
#ifdef   language_eng
		#define msg_5_line0 "  SETTING                       "
		#define msg_5_line1 "     mode                       "
		#define msg_5_line2 "     gain                       "
		#define msg_5_line3 "                                "
#endif
//____________________________ msg 5 �� ������� ________________________
#ifdef   language_rus
		#define msg_5_line0 "���������                       "
		#define msg_5_line1 "    �����                       " //32
		#define msg_5_line2 " ��������                       "
		#define msg_5_line3 "                                "

#endif
//____________________________ msg 5 �� �������������� _________________
#ifdef   language_trl
		#define msg_5_line0 "NASTROIKA                       "
		#define msg_5_line1 "    rezim                       "
		#define msg_5_line2 " usilenie                       "
		#define msg_5_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 14 �� ����������______________________
#define msg_14_width 32							// �� 32 ��������
#define msg_14_pos 0							// ������� � �������� �� ������ ����
#ifdef   language_eng
		#define msg_14_line0 "   Ultrasonic thickness meter  "
		#define msg_14_line1 "     Version H02S05 UT-111     "
		#define msg_14_line2 "       Serial number           "
		#define msg_14_line3 "       Run time     hours      "
#endif
//____________________________ msg 14 �� ������� ________________________
#ifdef   language_rus
		#define msg_14_line0 "�������������� ���������� ��-111" //32
		#define msg_14_line1 "         ������ H02S05          "
		#define msg_14_line2 "      ��������� �����           "
		#define msg_14_line3 "      ���������     �����       "
#endif
//____________________________ msg 14 �� �������������� __________________
#ifdef   language_trl
		#define msg_14_line0 "Ultrazvykovoi tolshinomer UT-111"
		#define msg_14_line1 "         Versia H02S05          "
		#define msg_14_line2 "      Zavodskoi nomer           "
		#define msg_14_line3 "      Narabotka     chasov      "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 15 �� ����������______________________
#define msg_15_width 32							// �� 32 ��������
#define msg_15_pos 0							// ������� � �������� �� ������ ����
#ifdef   language_eng
		#define msg_15_line0 "     Please, put the ultrasonic "
		#define msg_15_line1 "      transducer on the sample  "
		#define msg_15_line2 "		    thickness of    mm    "//calibration test blocks
		#define msg_15_line3 "                                "
#endif
//____________________________ msg 15 �� ������� ________________________
#ifdef   language_rus
		#define msg_15_line0 "                                "
		#define msg_15_line1 "    ����������, ����������, ��� "
		#define msg_15_line2 "    �� ������� �������    ��    "
		#define msg_15_line3 "                                "
#endif
//____________________________ msg 15 �� �������������� _________________
#ifdef   language_trl
		#define msg_15_line0 "                                "
		#define msg_15_line1 "    Ustanovite, pozaluista, PEP "
		#define msg_15_line2 "    na obrazec tolshini   mm    "
		#define msg_15_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 16 �� ����������______________________
#define msg_16_width 32							// �� 32 ��������
#define msg_16_pos 0							// ������� � �������� �� ������ ����
#ifdef   language_eng
		#define msg_16_line0 "                                 "
		#define msg_16_line1 " Zero calibration is performed,  "
		#define msg_16_line2 "   it is possible to measure     "
		#define msg_16_line3 "                                 "
#endif
//____________________________ msg 16 �� ������� ________________________
#ifdef   language_rus
		#define msg_16_line0 "                                 "
		#define msg_16_line1 "    ���������� ���� ���������,   "
		#define msg_16_line2 "    ����� ��������� ���������    "
		#define msg_16_line3 "                                 "
#endif
//____________________________ msg 16 �� �������������� _________________
#ifdef   language_trl
		#define msg_16_line0 "                                 "
		#define msg_16_line1 "  Kalibrovka nulya vipolnena,    "
		#define msg_16_line2 "   mozno provodit izmereniya     "
		#define msg_16_line3 "                                 "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 17 �� ����������______________________
#define msg_17_width 32							// �� 32 ��������
#define msg_17_pos 0							// ������� � �������� �� ������ ����
#ifdef   language_eng
		#define msg_17_line0 "                                "
		#define msg_17_line1 "  Ultrasonic velocity is set,   "
		#define msg_17_line2 "   it is possible to measure    "
		#define msg_17_line3 "                                "
#endif
//____________________________ msg 17 �� ������� ________________________
#ifdef   language_rus
		#define msg_17_line0 "                                "
		#define msg_17_line1 "    �������� ��� �����������    "
		#define msg_17_line2 "    ����� ��������� ���������   "
		#define msg_17_line3 "                                "
#endif
//____________________________ msg 17 �� �������������� _________________
#ifdef   language_trl
		#define msg_17_line0 "                                "
		#define msg_17_line1 "    Skorost UZK ustanovlena     "
		#define msg_17_line2 "    mozno provodit izmereniya   "
		#define msg_17_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 18 �� ����������______________________
#define msg_18_width 32							// �� 32 ��������
#define msg_18_pos 0							// ������� � �������� �� ������ ����
#ifdef   language_eng
		#define msg_18_line0 "                                "
		#define msg_18_line1 "  Please, enter the thickness   "
		#define msg_18_line2 " of the sample and press Enter  "
		#define msg_18_line3 "                                "
#endif
//____________________________ msg 18 �� ������� ________________________
#ifdef   language_rus
		#define msg_18_line0 "                                "
		#define msg_18_line1 " �������, ����������, ��������  "
		#define msg_18_line2 " ������� ������� � ������� Enter"
		#define msg_18_line3 "                                "
#endif
//____________________________ msg 18 �� �������������� _________________
#ifdef   language_trl
		#define msg_18_line0 "                                "
		#define msg_18_line1 "Vvedite, pozaluista, znachehie  "
		#define msg_18_line2 "tolshini obrazca i nazmite Enter"
		#define msg_18_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 19 �� ����������______________________
#define msg_19_width 32							// �� 32 ��������
#define msg_19_pos 0							// ������� � �������� �� ������ ����
#ifdef   language_eng
#define msg_19_line0 "                                "
#define msg_19_line1 "     Please, put the ultrasonic "
#define msg_19_line2 "     transducer on the sample   "
#define msg_19_line3 "		                          "

#endif
//____________________________ msg 19 �� ������� ________________________
#ifdef   language_rus
#define msg_19_line0 "                                "
#define msg_19_line1 "     ����������, ����������,    "
#define msg_19_line2 "     ��� �� ������� �������     "
#define msg_19_line3 "                                "
#endif
//____________________________ msg 19 �� �������������� _________________
#ifdef   language_trl
#define msg_19_line0 "                                "
#define msg_19_line1 "     Ustanovite, pozaluista,    "
#define msg_19_line2 "     PEP na obrazec tolshini    "
#define msg_19_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 3 �� ����������_______________________
#define msg_3_width 32							// �� 32 ��������
#define msg_3_pos 0								// ������� � �������� �� ������ ����
#ifdef   language_eng
#define msg_3_line0 "                               "
#define msg_3_line1 "    Please, select the mode    "
#define msg_3_line2 "       and press Enter         "
#define msg_3_line3 "                               "
#endif
//____________________________ msg 3 �� ������� _________________________
#ifdef   language_rus
#define msg_3_line0 "                                " //32
#define msg_3_line1 "   ����������, �������� �����   "
#define msg_3_line2 "     � ������� ������ Enter     "
#define msg_3_line3 "                                "
#endif
//____________________________ msg 3 �� �������������� ___________________
#ifdef   language_trl
#define msg_3_line0 "                                "
#define msg_3_line1 "   Pozaluista, viberite rezim   "
#define msg_3_line2 "     i nazmite knopku Enter     "
#define msg_3_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 4 �� ����������________________________
#define msg_4_width 32							// �� 32 ��������
#define msg_4_pos 0								// ������� � �������� �� ������ ����
#ifdef   language_eng
#define msg_4_line0 "                      ULTRASONIC"
#define msg_4_line1 "          THICKNESS METER UT-111"
#define msg_4_line2 "                                "
#define msg_4_line3 "                   NPK LUCH 2013"
#endif
//____________________________ msg 4 �� ������� ___________________________
#ifdef   language_rus
#define msg_4_line0 "                  ��������������" //32
#define msg_4_line1 "               ���������� ��-111"
#define msg_4_line2 "                                "
#define msg_4_line3 "                    ��� ��� 2013"
#endif
//____________________________ msg 4 �� �������������� _____________________
#ifdef   language_trl
#define msg_4_line0 "                   ULTRAZVUKOVOI" //32
#define msg_4_line1 "              TOLSHINOMER UT-111"
#define msg_4_line2 "                                "
#define msg_4_line3 "                   NPK LUCH 2013"
#endif

/*
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 11 �� �������____________________________
#define msg_30_width 31							// �� 32 ��������
#define msg_30_pos 0								// ������� � �������� �� ������ ���� [001/999]
#define msg_30_numb 5
#ifdef   language_rus
		#define msg_30_line0 "�������� ������                "
		#define msg_30_line1 "����� ��������                 "
		#define msg_30_line2 "[001]  3                       "
		#define msg_30_line3 "[002] 33                       "
		#define msg_30_line4 "[003]999                       "
#endif

//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 6 �� �������_____________________________
#define msg_31_width 31							// �� 32 ��������
#define msg_31_pos 0								// ������� � �������� �� ������ ����
#ifdef   language_rus
		#define msg_31_line0 "1) 12.7��                      "
		#define msg_31_line1 "2)  2.3��                      "
		#define msg_31_line2 "3) 9.21��                      "
		#define msg_31_line3 "4)301.3��                      "
		#define msg_31_line4 "5)  5.1��                      "
#endif
*/



/*
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 9 �� ����������__________________________
#define msg_9_width 32							// �� 32 ��������
#define msg_9_pos 0								// ������� � �������� �� ������ ����
#ifdef   language_eng
		#define msg_9_line0 "       Saving settings!          "
		#define msg_9_line1 "            Goodbye,             "						//32
		#define msg_9_line2 "       with best wishes!         "
		#define msg_9_line3 "                                 "
#endif
//____________________________ msg 9 �� ������� _____________________________
#ifdef   language_rus
		#define msg_9_line0 "       ���������� ��������!      "
		#define msg_9_line1 "           �� ��������,          "					//32
		#define msg_9_line2 "        ����� ��� �������!       "
		#define msg_9_line3 "                                 "
#endif
//____________________________ msg 9 �� �������������� ______________________
#ifdef   language_trl
		#define msg_9_line0 "      Sohranenie nastroek!       "
		#define msg_9_line1 "          Do svidaniya,          "						//32
		#define msg_9_line2 "        vsego vam dobrogo!       "
		#define msg_9_line3 "                                 "
#endif*/
////////////////////////////////////////////////////////////////////////////
//____________________________ msg_20 �������� �������� �� ��������� ������� �� ���������� ________________
#define msg_20_width 32										// �� 32 �������
#define msg_20_pos 0										// ������� � �������� �� ������ ����
//#define reset_numb 2										// ���������� ������� ���� ����
#ifdef   language_eng
#define msg_20_line0 "        ULTRASONIC VELOCITY     "
#define msg_20_line1 "                                "
#define msg_20_line2 "                     m/s        "
#define msg_20_line3 "measured according to thickness "
#endif
//____________________________ msg_20 �� ������� ___________________
#ifdef   language_rus
#define msg_20_line0 "           �������� ���         "
#define msg_20_line1 "                                "
#define msg_20_line2 "                     �/�        "
#define msg_20_line3 " �������� �� ��������� �������  "
#endif
//____________________________ msg_20 �� �������������� ____________
#ifdef   language_trl
#define msg_20_line0 "           SKOROST UZK          "
#define msg_20_line1 "                                "
#define msg_20_line2 "                     m/s        "
#define msg_20_line3 " izmereno po izvestnoy tolshine "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define msg_21_width 32							// �� 32 ��������
#define msg_21_pos 0								// ������� � �������� �� ������ ����
//____________________________ msg 21 �� ����������________________________
#ifdef   language_eng
	#define msg_21_line0 "      Page  [   ] was addied,    " 
	#define msg_21_line1 "       All measurements are      "
	#define msg_21_line2 "         will saved in it        "
	#define msg_21_line3 "                                 "
#endif
//____________________________ msg 21 �� ������� ___________________________
#ifdef   language_rus
	#define msg_21_line0 "   �������� [   ] ���������,     " 
	#define msg_21_line1 "      ��� ��������� �����        "
	#define msg_21_line2 "       ���������� � ���          "
	#define msg_21_line3 "                                 "
#endif
//____________________________ msg 21 �� �������������� _____________________
#ifdef   language_trl
	#define msg_21_line0 "   Stranica [   ] dobavlena,     " 
	#define msg_21_line1 "      Vse izmeneniya budut       "
	#define msg_21_line2 "       sohranyatsya v nei        "
	#define msg_21_line3 "                                 "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define msg_22_width 32							// �� 32 ��������
#define msg_22_pos 0							// ������� � �������� �� ������ ����
//____________________________ msg 22 �� ����������______________________
#ifdef   language_eng
#define msg_22_line0 "                                "
#define msg_22_line1 " Zero calibration NOT performed,"
#define msg_22_line2 "   zero calibration defaults    "
#define msg_22_line3 "                                "
#endif
//____________________________ msg 22 �� ������� ________________________
#ifdef   language_rus
#define msg_22_line0 "                                "
#define msg_22_line1 " ���������� ���� �� ���������,  "
#define msg_22_line2 "     �������� �� ���������      "
#define msg_22_line3 "                                "
#endif
//____________________________ msg 22 �� �������������� _________________
#ifdef   language_trl
#define msg_22_line0 "                                "
#define msg_22_line1 "  Kalibrovka nulya NE vipolnena,"
#define msg_22_line2 "    Kalibrovka po umolchaniu    "
#define msg_22_line3 "                                "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define msg_23_width 32							// �� 32 ��������
#define msg_23_pos 0							// ������� � �������� �� ������ ����
//____________________________ msg 23 �� ����������______________________
#ifdef   language_eng
#define msg_23_line0 "New Page                        "
#define msg_23_line1 "Clear Journal  [   /    ]       "
#endif
//____________________________ msg 23 �� ������� ________________________
#ifdef   language_rus
#define msg_23_line0 "����� ��������                  "
#define msg_23_line1 "�������� ������[   /    ]       "
#endif
//____________________________ msg 23 �� �������������� _________________
#ifdef   language_trl
#define msg_23_line0 "Novaya Stranitsa                "
#define msg_23_line1 "Ochistit Jurnal[   /    ]       "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define dlg_1_width 32							// �� 32 ��������
#define dlg_1_pos 0								// ������� � �������� �� ������ ����
//____________________________ dlg_1 �� ����������____________________________
#ifdef   language_eng
#define dlg_1_line0 "           CORRECTION $         "
#define dlg_1_line1 "                          +5.00 "						//32
#define dlg_1_line2 "                   mm     -5.00 "
#define dlg_1_line3 "                                "
#endif
//____________________________ dlg 1 �� ������� ______________________________
#ifdef   language_rus
#define dlg_1_line0 "           �������� $           "
#define dlg_1_line1 "                          +5.00 "					//32
#define dlg_1_line2 "                   ��     -5.00 "
#define dlg_1_line3 "                                "
#endif
//____________________________ dlg 1 �� �������������� ________________________
#ifdef   language_trl
#define dlg_1_line0 "           POPRAVKA $           "
#define dlg_1_line1 "                          +5.00 "						//32
#define dlg_1_line2 "                   mm     -5.00 "
#define dlg_1_line3 "                                "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define dlg_2_width 32							// �� 32 ��������
#define dlg_2_pos 0								// ������� � �������� �� ������ ����
//____________________________ dlg_2 �� ����������____________________________
#ifdef   language_eng
#define dlg_2_line0 "           BASIC LEVEL          "
#define dlg_2_line1 "                           0.60 "						//32
#define dlg_2_line2 "                   mm     500.0 "
#define dlg_2_line3 "                                "
#endif
//____________________________ dlg 1 �� ������� ______________________________
#ifdef   language_rus
#define dlg_2_line0 "         ������� �������        "
#define dlg_2_line1 "                           0.60 "					//32
#define dlg_2_line2 "                   ��     500.0 "
#define dlg_2_line3 "                                "
#endif
//____________________________ dlg 1 �� �������������� ________________________
#ifdef   language_trl
#define dlg_2_line0 "         BAZOVII UROVEN         "
#define dlg_2_line1 "                           0.60 "						//32
#define dlg_2_line2 "                   mm     500.0 "
#define dlg_2_line3 "                                "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define dlg_3_width 32							// �� 32 ��������
#define dlg_3_pos 0								// ������� � �������� �� ������ ����
//____________________________ dlg_3 �� ����������_____________________________
#ifdef   language_eng
#define dlg_3_line0 "           LOWER LIMIT          "
#define dlg_3_line1 "                          500.0 "						//32
#define dlg_3_line2 "                   mm      0.60 "
#define dlg_3_line3 "                                "
#endif
//____________________________ dlg 3 �� ������� _______________________________
#ifdef   language_rus
#define dlg_3_line0 "         ������ ������          "
#define dlg_3_line1 "                          500.0 "					//32
#define dlg_3_line2 "                   ��      0.60 "
#define dlg_3_line3 "                                "
#endif
//____________________________ dlg 3 �� �������������� ________________________
#ifdef   language_trl
#define dlg_3_line0 "         NIZNII PREDEL          "
#define dlg_3_line1 "                          500.0 "						//32
#define dlg_3_line2 "                   mm      0.60 "
#define dlg_3_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
#define dlg_4_width 32							// �� 32 ��������
#define dlg_4_pos 0								// ������� � �������� �� ������ ����
//____________________________ dlg_4 �� ����������_____________________________
#ifdef   language_eng
#define dlg_4_line0 "           UPPER LIMIT          "
#define dlg_4_line1 "                          500.0 "						//32
#define dlg_4_line2 "                   mm      0.60 "
#define dlg_4_line3 "                                "
#endif
//____________________________ dlg 4 �� ������� _______________________________
#ifdef   language_rus
#define dlg_4_line0 "         ������� ������         "
#define dlg_4_line1 "                          500.0 "					//32
#define dlg_4_line2 "                   ��      0.60 "
#define dlg_4_line3 "                                "
#endif
//____________________________ dlg 4 �� �������������� ________________________
#ifdef   language_trl
#define dlg_4_line0 "         VERHNII PREDEL         "
#define dlg_4_line1 "                          500.0 "						//32
#define dlg_4_line2 "                   mm      0.60 "
#define dlg_4_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
#define dlg_5_width 31							// �� 32 ��������
#define dlg_5_pos 0								// ������� � �������� �� ������ ����
#define ee_minutes_off_min 0					// 0=�������
#define ee_minutes_off_max 15
//____________________________ dlg 5 �� ����������__________________________
#ifdef   language_eng
#define dlg_5_line0 "          AUTO POWER OFF         "
#define dlg_5_line1 "                             15  "						//32
#define dlg_5_line2 "                     min      0  "
#define dlg_5_line3 "        without the using        "
#endif
//____________________________ dlg 5 �� ������� ____________________________
#ifdef   language_rus
#define dlg_5_line0 "          ��������������         " // �������������� �������
#define dlg_5_line1 "                             15  "						//32
#define dlg_5_line2 "                     ���      0  "
#define dlg_5_line3 "        ��� ���������������      "
#endif
//____________________________ dlg 5 �� �������������� ______________________
#ifdef   language_trl
#define dlg_5_line0 "          AUTOVIKLUCHENIE        "
#define dlg_5_line1 "                             15  "						//32
#define dlg_5_line2 "                     min      0  "
#define dlg_5_line3 "         pri neispolzovanii      "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define dlg_6_width 12										// �� 32 ��������
#define dlg_6_big_width 12									// �� 32 ��������
#define dlg_6_pos 9											// ������� ��� ����� ���� � �������� �� ������ ����
#define dlg_6_big_pos 2										// ��� ������� ����
#define dlg_6_numb 2										// ���������� ������� �������
#define brightness_max 1
#define brightness_min 0
//____________________________ dlg_6 ������� �� ���������� ______________
#ifdef   language_eng
#define dlg_6_line0 "   SCREEN   "
#define dlg_6_line1 "   INDOORS  "
#define dlg_6_line2 "   OUTSIDE  "
#define dlg_6_line3 "            "
#endif
//____________________________ dlg_6 ������� �� ������� _________________
#ifdef   language_rus
#define dlg_6_line0 "   �����    "
#define dlg_6_line1 "� ��������� "
#define dlg_6_line2 " �� ������  "
#define dlg_6_line3 "            "
#endif
//____________________________ dlg_6 ������� �� �������������� __________
#ifdef   language_trl
#define dlg_6_line0 "   EKRAN    "
#define dlg_6_line1 "V POMESHENII"
#define dlg_6_line2 " NA SOLNCE  "
#define dlg_6_line3 "            "
#endif
//////////////////////////////////////////////////////////////////////////////////////
#define dlg_7_width 32										// �� 32 �������
#define dlg_7_pos 0											// ������� � �������� �� ������ ����
#define dlg_7_big_pos 7										// ������� ������� �������� � �������� �� ������ ����
#define dlg_7_big_width 4									//
#define sound_numb 2										// ���������� ������� ���� ����
//____________________________ dlg_7 sound �� ���������� ________________
#ifdef   language_eng
#define dlg_7_line0 "             SOUND                 "
#define dlg_7_line1 "OFF "
#define dlg_7_line2 " ON "
#define dlg_7_line3 "                                   "
#endif
//____________________________ dlg_7 sound �� ������� ___________________
#ifdef   language_rus
#define dlg_7_line0 "              ����                 "
#define dlg_7_line1 "����"
#define dlg_7_line2 " ���"
#define dlg_7_line3 "                                   "
#endif
//____________________________ dlg_7 sound �� �������������� ____________
#ifdef   language_trl
#define dlg_7_line0 "              ZVUK                 "
#define dlg_7_line1 "OFF "
#define dlg_7_line2 " ON "
#define dlg_7_line3 "                                   "
#endif
//////////////////////////////////////////////////////////////////////////////////////

#define dlg_8_width 32								// �� 32 �������
#define dlg_8_pos 0									// ������� � �������� �� ������ ����
//____________________________ dlg_8 sound �� ���������� ________________
#ifdef   language_eng
#define dlg_8_line0 "              GAIN             "
#define dlg_8_line1 "                             40"
#define dlg_8_line2 "                             10"
#define dlg_8_line3 "                               "
#endif
//____________________________ dlg_8 sound �� ������� ___________________
#ifdef   language_rus
#define dlg_8_line0 "            ��������           "
#define dlg_8_line1 "                             40"
#define dlg_8_line2 "                             10"
#define dlg_8_line3 "                               "
#endif
//____________________________ dlg_8 sound �� �������������� ____________
#ifdef   language_trl
#define dlg_8_line0 "            USILENIE           "
#define dlg_8_line1 "                             40"
#define dlg_8_line2 "                             10"
#define dlg_8_line3 "                               "
#endif
////////////////////////////////////////////////////////////////////////////
#define dlg_9_width 32										// �� 32 �������
#define dlg_9_pos 0											// ������� � �������� �� ������ ����
#define dlg_9_big_pos 8										// ������� ������� �������� � �������� �� ������ ����
#define dlg_9_big_width 4									//
//____________________________ dlg_9 sound �� ���������� ________________
#ifdef   language_eng
#define dlg_9_line0 "    RESET SETTINGS TO DEFAULTS?    "
#define dlg_9_line1 "NO  "
#define dlg_9_line2 "YES "
#define dlg_9_line3 "                                   "
#endif
//____________________________ dlg_9 sound �� ������� ___________________
#ifdef   language_rus
#define dlg_9_line0 "     �������� ��� ���������?       "
#define dlg_9_line1 "��� "
#define dlg_9_line2 " �� "
#define dlg_9_line3 "                                   "
#endif
//____________________________ dlg_9 sound �� �������������� ____________
#ifdef   language_trl
#define dlg_9_line0 "     SBROSIT VSE NASTROIKI?        "
#define dlg_9_line1 "NET "
#define dlg_9_line2 "DA  "
#define dlg_9_line3 "                                   "
#endif
////////////////////////////////////////////////////////////////////////////
//____________________________ dlg_10 �������� ��� �� ���������� ________________
#define dlg_10_width 32										// �� 32 �������
#define dlg_10_pos 0											// ������� � �������� �� ������ ����
#ifdef   language_eng
#define dlg_10_line0 "        ULTRASONIC VELOCITY       "
#define dlg_10_line1 "                           9999"
#define dlg_10_line2 "                    M/S     100"
#define dlg_10_line3 "                                  "
#endif
//____________________________ dlg_10 �������� ��� �� ������� ___________________
#ifdef   language_rus
#define dlg_10_line0 "          �������� ���          "
#define dlg_10_line1 "                           9999 "
#define dlg_10_line2 "                    �/�     100 "
#define dlg_10_line3 "                                "
#endif
//____________________________ dlg_10�������� ��� �� �������������� ____________
#ifdef   language_trl
#define dlg_10_line0 "         SKOROST UZK            "
#define dlg_10_line1 "                           9999 "
#define dlg_10_line2 "                    M/S     100 "
#define dlg_10_line3 "                                "
#endif

////////////////////////////////////////////////////////////////////////////
#define dlg_11_width 31										// �� 32 �������
#define dlg_11_pos 0										// ������� � �������� �� ������ ����
//____________________________ dlg_11 ������� ��������� �� ���������� ________________
#ifdef   language_eng
#define dlg_11_line0 "         KNOWN THICKNESS       "
#define dlg_11_line1 "                          500.0"
#define dlg_11_line2 "                    MM    0.60"
#define dlg_11_line3 "                               "
#endif
//____________________________ dlg_11 ������� ��������� �� ������� ___________________
#ifdef   language_rus
#define dlg_11_line0 "        ������� ���������      "
#define dlg_11_line1 "                          500.0"
#define dlg_11_line2 "                    ��     0.60"
#define dlg_11_line3 "                               "
#endif
//____________________________ dlg_11 ������� ��������� �� �������������� ____________
#ifdef   language_trl
#define dlg_11_line0 "        TOLSHINA IZVESTNAYA    "
#define dlg_11_line1 "                          500.0"
#define dlg_11_line2 "                    MM     0.60"
#define dlg_11_line3 "                               "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define dlg_12_width 31									// �� 32 ��������
#define dlg_12_pos 0									// ������� � �������� �� ������ ����
#define dlg_12_big_pos 8	
#define dlg_12_big_width 3				
//____________________________ dlg 12 �� ����������__________________________
#ifdef   language_eng
#define dlg_12_line0 "         CLEAR THE LOG?          "
#define dlg_12_line1 " NO "						
#define dlg_12_line2 "YES "
#define dlg_12_line3 "                                 "
#endif
//____________________________ dlg 12 �� ������� ____________________________
#ifdef   language_rus
#define dlg_12_line0 "      �������� ���� ������?      " //32 
#define dlg_12_line1 "��� "						
#define dlg_12_line2 " �� "
#define dlg_12_line3 "                                 "
#endif
//____________________________ dlg 12 �� �������������� ______________________
#ifdef   language_trl
#define dlg_12_line0 "      OCHISTIT VES ZHURNAL?      "
#define dlg_12_line1 "NET "						
#define dlg_12_line2 " DA "
#define dlg_12_line3 "                                 "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define dlg_13_width 31									// �� 32 ��������
#define dlg_13_pos 0									// ������� � �������� �� ������ ����
#define dlg_13_big_pos 8
#define dlg_13_big_width 3
#define dlg_13_entry_pos 20								// ������� ��������� ������ � ������ ������

//____________________________ dlg 13 �� ����������__________________________
#ifdef   language_eng
#define dlg_13_line0 "    CLEAR THE ENTRY       ?      "
#define dlg_13_line1 " NO "
#define dlg_13_line2 "YES "
#define dlg_13_line3 "                                 "
#endif
//____________________________ dlg 13 �� ������� ____________________________
#ifdef   language_rus
#define dlg_13_line0 "     ������� ������       ?      " //32
#define dlg_13_line1 "��� "
#define dlg_13_line2 " �� "
#define dlg_13_line3 "                                 "
#endif
//____________________________ dlg 13 �� �������������� ______________________
#ifdef   language_trl
#define dlg_13_line0 "      UDALIT ZAPIS        ?      "
#define dlg_13_line1 "NET "
#define dlg_13_line2 " DA "
#define dlg_13_line3 "                                 "
#endif
//////////////////////////////////////////////////////////////////////////////////////
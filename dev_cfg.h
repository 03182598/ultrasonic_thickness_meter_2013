//������ �����������    verHa+verHb . verSa+verSb  ==  ������ H01.S01
#define verHA 0
#define verHb 2

#define verSa 0
#define verSb 3


 /// ���������� 
#define keyup 7
#define keydown 8
#define keyenter 9
#define keyrezim 4
#define keynastr 5
#define keyzero 2
#define keypep 1
#define keymem 6
#define key_off 1

#define LF 10 /// ������� ������
#define CR 13 /// ������� �������


#define M00err 0/// ������ 00 uart   -- ��� ����� �������
#define M01err 1/// ������ 01 uart	 -- ��� ������ �����	
#define M02err 2/// ������ 02 uart	 -- �������� ��������� �������� ������� ��� ��������� ������ �� �������
#define M03err 3/// ������ 03 uart	 -- ������������ ������ ������ (������ ���� ascii ������ �������)
#define END_S  4/// ����� ��������	�������� �������  , ������ ������ ��� ����
#define GET_SN 5/// ��������� ����� �������
#define W_OK  6 /// �������� ������� ���������
#define FF0err 7/// ������ �������� �����
#define BOKV 8 /// ����� �����
#define BTOT 9 /// ������� �����

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
////
#define LowSPEED 100 //// ����������� �������� ���
#define HISPEED 9999 ///  ������������ �������� ���

#define CALVL 6043 /// �������� � 3 �� �������.

#define stbokh  15000 /// ��������� �������� ��������� ������� � ������� �����  ����� ��� ������� ������ 
#define stbokl  7500 //// ����� ��� ������� ����������.

#define maxPEP 9/// ������������ ����� �������� � �������


#define step_speedX  12//40 //// ��� ��������� �������� �������� 000 
#define step_speed0  18//40 18//// ��� ��������� �������� �������� 
#define step_speeda  250 //// ��� ���������  �������� �������� 

#define dkeyl 150 // �������� �� ���������� long
#define dkeysh 50 // �������� �� ���������� short
#define dkeyout 15 // �������� �� ������ �� ����  

#define step_speedZ  180 //// 180 ��� ���������  �������� �������� 

#define step_apx 50/// ��� ��������� �� ��������� �������� ���������
#define readfilest 370 // ��� ��������� ����� ����� � ��������� ������
#define readfilestE 500	/// ��� �������� ��������



#define RAZBRH_low 31  /// ������� ������� �����������
#define RAZBRH_hi 30000

#define RAZBRL_low 30
#define RAZBRL_hi 29990

#define NONIUSL 0	//  ������� ������	// -5.00��
#define NONIUSH 1000 /// +5.00��

#define DIFFHI 30000 /// ������� ������� ���� 300.0��
#define DIFFLO 30 /// ������ ������� ���� 0.30��


#define SCANMAX 65000 /// ���� ���� ������ ��� ������������ 


#define MaxHiS 30000 /// ������������ ������� ��� ���������� �� �������
#define MinHiS 10 /// ����������� ������� ��� ���������� �� �������

#define calobr3mm 3185 /// ���� ������� 3�� ������� 1-6
#define calobr5mm 5308 /// ���� ������� ������ 7
#define calobr20mm 21233 /// ���� ������� ������� 8-9



#define STAT (unsigned int*)0x0000   // ��������� ��� ���������, ���� ������ ������

//#define SNUMS 0x0002 /// �������� ����� ������� word
//#define NARAB 0x0004 /// ��������� �� �����	dword

#define VELMEM (unsigned int*)0x0010 // �������� ��� 
#define NUMDATC (unsigned char*)0x1A  // ����� ������� ���
#define MODES (unsigned char*)0x0020  // ��������� �������  �� ���� � ������� ������
#define MEMCFG (unsigned int*)0x02A  // ����������� ������ ������ ���������
#define MEMPNT (unsigned int*)0x030  // ��������� ������ �� �������

#define NASTR (unsigned char*)0x035 // ����� ���������

#define CALIBD (unsigned int*)0x130 // ������� �������� ���������� ���� 

#define BRIGHT (unsigned char*)0x38 /// ������� �������� �������.

#define VEL1 (unsigned int*)0X040 //�������� ���������1
#define VEL2 (unsigned int*)0X042 //�������� ���������2
#define VEL3 (unsigned int*)0X044 //�������� ���������3
#define VEL4 (unsigned int*)0X046 //�������� ���������4
#define VEL5 (unsigned int*)0X048 //�������� ���������5
#define VEL6 (unsigned int*)0X04A //�������� ���������6
#define VEL7 (unsigned int*)0X04C //�������� ���������7
#define VEL8 (unsigned int*)0X04E //�������� ���������8
#define VEL9 (unsigned int*)0X050 //�������� ���������9
#define VEL10 (unsigned int*)0X052 //�������� ���������10


#define AMP1 (unsigned char*)0X054 //�������� ���������1
#define AMP2 (unsigned char*)0X056 //�������� ���������2
#define AMP3 (unsigned char*)0X058 //�������� ���������3
#define AMP4 (unsigned char*)0X05A //�������� ���������4
#define AMP5 (unsigned char*)0X05C //�������� ���������5
#define AMP6 (unsigned char*)0X05E //�������� ���������6
#define AMP7 (unsigned char*)0X060 //�������� ���������7
#define AMP8 (unsigned char*)0X062 //�������� ���������8
#define AMP9 (unsigned char*)0X064 //�������� ���������9
#define AMP10 (unsigned char*)0X066 //�������� ���������10


#define DATCH1 (unsigned char*)0X070 //������ ���������1
#define DATCH2 (unsigned char*)0X071 //������ ���������2
#define DATCH3 (unsigned char*)0X072 //������ ���������3
#define DATCH4 (unsigned char*)0X073 //������ ���������4
#define DATCH5 (unsigned char*)0X074 //������ ���������5
#define DATCH6 (unsigned char*)0X075 //������ ���������6
#define DATCH7 (unsigned char*)0X076 //������ ���������7
#define DATCH8 (unsigned char*)0X077 //������ ���������8
#define DATCH9 (unsigned char*)0X078 //������ ���������9
#define DATCH10 (unsigned char*)0X079 //������ ���������10

#define MODE1 (unsigned char*)0x080 //����� ������ ���������1
#define MODE2 (unsigned char*)0x081 //����� ������ ���������2
#define MODE3 (unsigned char*)0x082 //����� ������ ���������3
#define MODE4 (unsigned char*)0x083 //����� ������ ���������4
#define MODE5 (unsigned char*)0x084 //����� ������ ���������5
#define MODE6 (unsigned char*)0x085 //����� ������ ���������6
#define MODE7 (unsigned char*)0x086 //����� ������ ���������7
#define MODE8 (unsigned char*)0x087 //����� ������ ���������8
#define MODE9 (unsigned char*)0x088 //����� ������ ���������9
#define MODE10 (unsigned char*)0x089 //����� ������ ���������10



#define CALB1 0x08A /// ���������� � ����� 1
#define CALB2 0x08C /// ���������� � ����� 2
#define CALB3 0x08E /// ���������� � ����� 3
#define CALB4 0x090 /// ���������� � ����� 4
#define CALB5 0x092 /// ���������� � ����� 5
#define CALB6 0x094 /// ���������� � ����� 6
#define CALB7 0x096 /// ���������� � ����� 7
#define CALB8 0x098 /// ���������� � ����� 8
#define CALB9 0x09A /// ���������� � ����� 9
#define CALB10 0x09C /// ���������� � ����� 10

#define BEEP_MODE 0x09E //// ���������� �����



#define RAZB_H1 0x0A0 /// ������ ���� ��� ��� ����������� � ���������1 word
#define RAZB_L1 0x0A2
#define RAZB_H2 0x0A4 /// ������ ���� ��� ��� ����������� � ���������2
#define RAZB_L2 0x0A6
#define RAZB_H3 0x0A8 /// ������ ���� ��� ��� ����������� � ���������3
#define RAZB_L3 0x0AA
#define RAZB_H4 0x0AC /// ������ ���� ��� ��� ����������� � ���������4
#define RAZB_L4 0x0AE
#define RAZB_H5 0x0B0 /// ������ ���� ��� ��� ����������� � ���������5
#define RAZB_L5 0x0B2
#define RAZB_H6 0x0B4 /// ������ ���� ��� ��� ����������� � ���������6
#define RAZB_L6 0x0B6
#define RAZB_H7 0x0B8 /// ������ ���� ��� ��� ����������� � ���������7
#define RAZB_L7 0x0BA
#define RAZB_H8 0x0BC /// ������ ���� ��� ��� ����������� � ���������8
#define RAZB_L8 0x0BE
#define RAZB_H9 0x0C0 /// ������ ���� ��� ��� ����������� � ���������9
#define RAZB_L9 0x0C2
#define RAZB_H10 0x0C4 /// ������ ���� ��� ��� ����������� � ���������10
#define RAZB_L10 0x0C6


	///// ��������� ����� �������     ������ 3.2.1.0.  4 ����� ���� �� ������.
	
#define ZNUM0 0x110 /// ������ ������ ������� 0
#define ZNUM1 0x111	/// ������ ������ ������� 1
#define ZNUM2 0x112	/// ������ ������ ������� 2
#define ZNUM3 0x113	/// ������ ������ ������� 3

#define TNAR 0x120 /// DWORD ���������   1�� ��� 1������   ���� ����� 71582.7882 ������ ����� 




#define DIFFU1 0x0D0 /// ����� ���� ������ � ��������� 1 word
#define DIFFU2 0x0D2 /// ����� ���� ������ � ��������� 2
#define DIFFU3 0x0D4 /// ����� ���� ������ � ��������� 3
#define DIFFU4 0x0D6 /// ����� ���� ������ � ��������� 4
#define DIFFU5 0x0D8 /// ����� ���� ������ � ��������� 5
#define DIFFU6 0x0DA /// ����� ���� ������ � ��������� 6
#define DIFFU7 0x0DC /// ����� ���� ������ � ��������� 7
#define DIFFU8 0x0DE /// ����� ���� ������ � ��������� 8
#define DIFFU9 0x0E0 /// ����� ���� ������ � ��������� 9
#define DIFFU10 0x0E2 /// ����� ���� ������ � ��������� 10


#define DIFFP1 (unsigned char*)0x0E4 /// ���������� � ���� ������ � ��������� 1 byte
#define DIFFP2 (unsigned char*)0x0E5 /// ���������� � ���� ������ � ��������� 2
#define DIFFP3 (unsigned char*)0x0E6 /// ���������� � ���� ������ � ��������� 3
#define DIFFP4 (unsigned char*)0x0E7 /// ���������� � ���� ������ � ��������� 4
#define DIFFP5 (unsigned char*)0x0E8 /// ���������� � ���� ������ � ��������� 5
#define DIFFP6 (unsigned char*)0x0E9 /// ���������� � ���� ������ � ��������� 6
#define DIFFP7 (unsigned char*)0x0EA /// ���������� � ���� ������ � ��������� 7
#define DIFFP8 (unsigned char*)0x0EB /// ���������� � ���� ������ � ��������� 8
#define DIFFP9 (unsigned char*)0x0EC /// ���������� � ���� ������ � ��������� 9
#define DIFFP10 (unsigned char*)0x0ED /// ���������� � ���� ������ � ��������� 10


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

#define eeRD 0xA1 ///  ���������� �����  ��� ������ ������
#define eeWR 0xA0 ///  ���������� �����  ��� ������ ������

#define idel			  1 /// �������� i2c
#define SDA_LN            PH1                         //����� SDA
#define SCL_LN            PH2                         //����� SCL
#define I2C_PIN           PINH                        //���� �����
#define I2C_DDR           DDRH                        //���� �����������
#define I2C_PORT          PORTH                       //���� ������

#define IN_LN             0                           //����� �� ����
#define OUT_LN            1                           //����� �� �����

#define ACK               1                           //�������� ������������� ������ (�� ��������� ����)
#define NOT_ACK           0                           //�� ������������ ����� (��������� ����)

#define I2C_T             0.00001                     //������ �������� ������������� (1/I2C_T = ������� ����)
                                                      //��� ����������� ���������� ����

#define SDA PH1
#define SCL PH2



#define mSCL PJ1 /// ����� ���� ������
#define mSDA PJ0 /// ����� ������ 
#define EEPJ PORTJ
#define INPJ PINJ


#define SDLDAC PF5   //// ����� ���
#define SCLDAC PF6
#define	SYCDAC PF7

#define BEEPX PE4
//.EQU BEEPX= 4 //porte 4 out

#define BEEPM0 PE5
//.EQU BEEPM0= 5 //porte 5 out
#define BEEPM1 PE6
//.EQU BEEPM1= 6 //porte 6 out

#define KEY_RES PE7
//.EQU KEY_RES= 7 //porte 7 out

#define KEY_OK PL2
//.EQU KEY_OK= 2 //portj 2 out

#define KEY_PORT PINL        /////// ���� ���������� PJ3-PJ6

#define ONKEY PF3      //// ������� ������� ������� ���������.   

#define EXTPOWER PK5 /// ����� 0 - ���������� ������� ������� !!!

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






/*
 * measuring.h
 *
 *  Created on: 14.04.2009
 *      Author: Izon
 */


#ifndef MEASURING_H_
#define MEASURING_H_

	extern volatile unsigned char nastr;
	volatile unsigned char keypressed_short;
	volatile unsigned int main_value; //long
	volatile unsigned char dot_pos;
	const unsigned char big_font_16[];
	
	void show_msg_15(unsigned char);
	unsigned char num2str_right(unsigned long, unsigned char *);
	void Draw_big_font (unsigned char,unsigned char, const unsigned char*,unsigned char,unsigned char, const unsigned char*, unsigned char, unsigned char);

	
	
unsigned short ADC_convert(void);
unsigned short int ReadX (void); 
void cfgr_load(unsigned char amp, unsigned char nastr);

unsigned int get_counter(void);
unsigned long GET_MESINT (unsigned char, unsigned char);
unsigned long FAST_GET_MESINT (unsigned char numd,unsigned char clr);

void vrch(unsigned char amp);
void loadamp(unsigned char amp);

void ZG(void);
void BEEP(unsigned char);
void HI_volts(void);
void USART_Init( unsigned int);
void USART_SEND_Byte(unsigned char sb); //// Передача байта

unsigned int IZMERENIE (unsigned char status, unsigned short velos, unsigned char datchnum, unsigned char nastr, unsigned char amp, unsigned char vb, unsigned int calib,unsigned char mf,unsigned int mp, unsigned char typefile);
//unsigned int IZMERENIE (unsigned char status, unsigned short velos, unsigned char datchnum,  unsigned char amp, unsigned char vb, unsigned int calib,unsigned char mf,unsigned int mp, unsigned char typefile);
unsigned int RAZBRAKOVKA (unsigned char status, unsigned short velos, unsigned char datchnum, unsigned char nastr, unsigned char amp, unsigned char vb, unsigned int calib, unsigned int RAZBH, unsigned int RAZBHL,unsigned char mf,unsigned int mp, unsigned char typefile);
unsigned int SKANIROV (unsigned char status, unsigned short velos, unsigned char datchnum, unsigned char nastr, unsigned char amp, unsigned char vb, unsigned int calib, unsigned char,unsigned char mf,unsigned int mp, unsigned char typefile);
unsigned int DIFFERNC (unsigned char status, unsigned short velos, unsigned char datchnum, unsigned char nastr, unsigned char amp, unsigned char vb, unsigned int calib, unsigned int DIFFU, unsigned char DIFFP,unsigned char mf,unsigned int mp, unsigned char typefile);
unsigned int NONIUS (unsigned char status, unsigned short velos, unsigned char datchnum, unsigned char nastr, unsigned char amp, unsigned char vb, unsigned int calib,  unsigned int NONIUSU, unsigned char NONIUSP,unsigned char mf,unsigned int mp, unsigned char typefile);
void velset (unsigned char num);
void ampset (unsigned char num);
//void calibzero (unsigned char nastr, unsigned char dach);
void calibzero ( unsigned char,unsigned char);
void calibhig (unsigned char nastr, unsigned char dach);
//void calibhig ( unsigned char dach);

volatile unsigned char autoplusm(unsigned char st);

unsigned char pepmenu (unsigned char nastr);
unsigned char mmenu(unsigned char, unsigned char);
unsigned char rmenu(unsigned char );
unsigned char regulmenu(unsigned char num);
unsigned char kalibmenu (unsigned char nastr);
unsigned long calculmes (unsigned int calib,unsigned int velos, unsigned char dach, unsigned char nastr); //// измерить и пересчитать измерения

//unsigned long calculmes (unsigned int calib,unsigned int velos, unsigned char dach); //// измерить и пересчитать измерения

unsigned long FAST_calculmes (unsigned int calib, unsigned int velos, unsigned char dach); 

void delayx (unsigned char val);

#endif /* MEASURING_H_ */




/*
 * display.h
 *
 *  Created on: 03.04.2009
 *      
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
void show_twpos(unsigned char num, unsigned char xmm, unsigned char ymm);
void ZP_draw_zwuk(unsigned char num); /// Рисовать меню звука

unsigned char ask_disp(void);////// Передать состояние есть ли обмен с дисплеем
void brset(void); // Регулировка яркости -- подпрограмма 
void ZPset(void); /// Управление звуком
unsigned char BRIVAL(void); ////Вычислить яркость дисплея
void digitbuf(unsigned long num); 

void put_int_to_num_buffer(unsigned int, unsigned char doten);
void put_int_to_cnum_buffer(unsigned int);
void put_int_to_bnum_buffer(unsigned int num, unsigned char pos);

void show_bnum_buffer(unsigned char pos, unsigned int mnoj);

unsigned char show_FORMmenu(unsigned char);

void Show_Logo(void);///// Показать заставку луча

void renew_display(void);
void renew_bat(void);
void draw_dline(void);
void display_driver(void);
void show_acont(unsigned char);
void clr_bat(void);
void clr_mmsdiv(void);
void show_bat100(void);
void show_bat75(void);
void show_bat50(void);
void show_bat25(void);
void show_bat0(void);
void show_all(void);
void zapret(void);
void show_num_buffer(void);
void show_cnum_buffer(void);
void show_SELmenu(unsigned char num); /// Меню выбора файла
void put_int_to_snum_buffer(unsigned int num);
void show_snum_buffer(void);

void show_hi_str(void);
void show_dimension(unsigned char);
void show_dot(unsigned char);
void show_simbol(unsigned char);
void show_battery(unsigned char);
void show_intro(void);
void show_lamp(void);
void show_msdiv(void);
void show_mmdiv(void);
void print_number(unsigned char);
void print_hi_simbol(unsigned char, unsigned char);
void show_dot(unsigned char num);
void print_dimension(unsigned char);
void print_hi_dimension(unsigned char);
void print_dot(unsigned char);
void print_simbol(unsigned char);
void print_battery(unsigned char);
void print_intro3(unsigned char);
void print_intro1(unsigned char);
void print_intro_num(unsigned char);
void clear_ram(unsigned char);
void show_video(unsigned char, unsigned char, unsigned char, unsigned char);
void place_in_ram(unsigned char, unsigned char, unsigned char, unsigned char);
void oled_on(void);
void cls(void);
void send_command(unsigned char);
void send_data(unsigned char);
void send_8pixels(unsigned char);
void send_2pixels(unsigned char);

void display_delay(unsigned int);
void draw_dachnum (unsigned char num, unsigned char pos);
void show_roja(void);
void show_hicons(unsigned char);
void show_mpos(unsigned char num, unsigned char xmm, unsigned char ymm);
void show_wpos(unsigned char num, unsigned char xmm, unsigned char ymm);
void show_upos(unsigned char num, unsigned char xmm, unsigned char ymm);
void show_wposx(unsigned char num, unsigned char xmm, unsigned char ymm);

void menu_cursor(unsigned char pos);
void show_dmenu(unsigned char dachik);
void show_nmenu(unsigned char nast);
void show_msmin(unsigned char);

void menu_wcursor(unsigned char pos,unsigned char mode);
void show_wmenu(unsigned char num);
void show_wnmenu(unsigned char num);
void show_MEMmenu(unsigned char num,unsigned char mf,unsigned int mp, unsigned char tf);////// Нарисовать меню ПАМЯТЬ

void show_pepmenu(unsigned char num);
void show_cmenu(unsigned char num);

void draw_hline(void);
void draw_nastrn (unsigned char num);
void draw_samp(unsigned char amp);
void draw_smem(unsigned char file, unsigned int frees, unsigned char typefile);
void draw_batl(unsigned char vb);
void show_batEXT(void);//// Внешнее питание
void draw_caldatch (unsigned char num);

void draw_pepsel(unsigned char num);   

void draw_CLASSMODE(unsigned char SM);  /////////////  Нарисоватиь параметры ячейки файла при сохранении 

void draw_nastrsel(unsigned char num);   

void draw_rezsel(unsigned char num); 
void draw_memoline (unsigned char num, unsigned char xp, unsigned char yp);
void show_intro(void);

void draw_razb_p(unsigned int hilev,unsigned int lolev); /// отобразить пределы в разбраковке
void draw_non_d(signed int levd);
void draw_diff_u(unsigned int val);
void draw_scan_min(unsigned int val);


void draw_smm(unsigned char pos);

void draw_spsim (unsigned char type);
void draw_smdot(unsigned char pos, unsigned char ypos);/// отобразить точку в блоке параметров режимов

void DDS_LOAD(unsigned long tdword);
void DDS_CLK(void);
void DDS_SINIT(void);
void DDS_SD(unsigned char tbb);
void DDS_SF(unsigned long);

void DAC_CLK(void);
void DAC_SD(unsigned char);

void draw_sminus(unsigned char pos); //// Нарисовать маленький минус блока параметров
void draw_bminus(unsigned char yes, unsigned char lr); //// Нарисовать большой минус  1 нарисовать 0 стререть // lr 0 4 симаола 1- 3 символа

void SIG_UP(unsigned char im);  /// Сигн разбраковки порога
void show_inv_num_buffer(unsigned char clr); /// инверсный буфер
void show_inv_dot(unsigned char num);
void print_ndot(unsigned char num);
void put_int_to_invnum_buffer(unsigned int num);



#endif /* DISPLAY_H_ */

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
//=================== интерфейсы =================//
#define false 0x00
#define true 0xFF
#define SetBit(Port,BitNo) (Port) |= (1<<(BitNo))
#define ResetBit(Port,BitNo) (Port) &= ~(1<<(BitNo))
#define TestBit(Port,No) (((Port)&(1<<(No)))==0?false:true)

#define CS	3
#define SDA 4
#define SCL 5

///////////////////////////////////////////////////////////////////////////////////// из devcfg.h
//ВЕРСИЯ ТОЛЩИНОМЕРА    verHa+verHb . verSa+verSb  ==  Версия H01.S01
#define verHA 0
#define verHb 2
#define verSa 0
#define verSb 5

/// клавиатура
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

#define LF 10				// Перевод строки
#define CR 13				// Перевод каретки

#define M00err 0			// Ошибка 00 uart   -- Нет такой команды
#define M01err 1			// Ошибка 01 uart	 -- Нет такого файла
#define M02err 2			// Ошибка 02 uart	 -- Превышен временной интервал запроса или потерянны данные из команды
#define M03err 3			// Ошибка 03 uart	 -- Неправильный формат данных (вместо цифр ascii другие символы)
#define END_S  4			// Конец передачи	Передано успешно  , список файлов или файл
#define GET_SN 5			// Прочитать номер прибора
#define W_OK   6			// Операция успешно выполнена
#define FF0err 7			// Ошибка передачи файла
#define BOKV   8			// Конец блока
#define BTOT   9			// ТаймАут блока

//// Команды различаемые прибором
/*
!! 1 символ вызывает расшифровку ветки команд. после него нужна задержка до 1.5сек  для обработки

S % * * * *  Записать в память ****- серийный номер 4 цифры (Чтобы команда была исполнена нужно войти в меню настройки и удерживать кнопку память)

T  - Узнать наработку прибора (возвращает сразу)

J - Узнать файловую организацию  (возвращает сразу)   1 строчка количество файлов в приборе, следующии строки (их кол во равно числу файлов) указывают
сколько ячеек использовано в файле. если 0 файл чист.  нумерация файлов с 00 до 99

L % * * прочитать файл ** номер файла.  Выдается список построчный с 00000 ячейки файла и до последней. даже если в конце нули c
разделением на блоки блок 400 строк. после приходит B** - признак конца блока и номер блока, для продолжения передачи посылается z если другой символ
Вызывается ошибка передачи файла FF0.  блоков нет в файлах по 300ячеек. в файле 600ячеек блок 1 и после команды B**-z придет END
конец файла

номер блока B** имеет номер от 10 до макс 59  где реально 1й блок номер 10 это 00блок  11блок это 1блок  59блок 49блок

20000ячеек / 400 = 50блоков   00-49   = 10-59.    в программе ПК номер -10.

При передаче файл передается целиком, также передаются (удаленные ячейки) поэтому длинну файла с корректной длинной записи необходимо узнать
по команде J

P - текущяя толщина на дисплее прибора

новые изменения блок 400 строк память 20000яч сохраняются ячейки в трех байтах. толщ и редим в котором было сохранено.
формат передачи  X01234  X - режим символом

*/

#define LowSPEED 100					// Минимальная скорость УЗК
#define HISPEED 9999					// Максимальная скорость УЗК
#define CALVL 6043						// скорость в 3 мм образце.
#define stbokh  15000					// Параметры моргания надписями уровней и порогов сбоку  число при котором гаснет
#define stbokl  7500					// число при котором зажигается.
#define maxPEP 9						// Максимальное число датчиков в приборе

#define high_resolution 100				// порог толщины в мм для смены разрешения основного значения

#define step_speedX  12					// 40 // шаг прокрутки числовых значений 000
#define step_speed0  18					// 40 18// шаг прокрутки числовых значений
#define step_speeda  250				// шаг прокрутки  значений усиления

#define key_read_delay 1				// частота считывания клавиатуры 0,001*4M/256=15Гц 1000 2084  0
#define key_repeat 15					// задержка нажатия кнопки 15
#define Prescaler 0x01

#define step_speedZ  180				// 180 шаг прокрутки  значений усиления

#define step_apx 50						// шаг прокрутки из программы быстрорй прокрутки
#define readfilest 370					// шаг прокрутки ячеек файла в просмотре памяти
#define readfilestE 500					// шаг скорости удаления



#define RAZBRH_low 31					// границы уровней разбраковки
#define RAZBRH_hi 30000

#define RAZBRL_low 30
#define RAZBRL_hi 29990

#define NONIUSL 0						//  Уровень нониус	// -5.00мм
#define NONIUSH 1000					// +5.00мм

#define DIFFHI 30000					// Верхний уровень дифф 300.0мм
#define DIFFLO 30						// Нижний уровень дифф 0.30мм


#define SCANMAX 65000					// макс знач тощины при сканировании


#define MaxHiS 30000					// максимальная толщина при калибровке по толщине
#define MinHiS 10						// минимальная толщина при калибровке по толщине

#define calobr3mm 3185					// тест образец 3мм датчики 1-6 3185
#define calobr5mm 5402					// 5467 5308		// тест образей 5 мм датчик 7
#define calobr20mm 21611				//21233		// тест образец датчики 8-9

#define vel3mm 6043						// скорость в тестовом образце 3 мм
#define vel5mm	5930					// скорость в тестовом образце 5 мм
#define vel20mm 5920					// скорость в тестовом образце 20мм



#define STAT (unsigned int*)0x0000		// Состояние при включении, если чистая память

//#define SNUMS 0x0002					// Серийный Номер прибора word
//#define NARAB 0x0004					// Наработка на отказ	dword

#define VELMEM  (unsigned int*) 0x0010		// скорость УЗК
#define NUMDATC (unsigned char*)0x1A		// Номер датчика ТИП
#define MODES   (unsigned char*)0x0020		// Состояние прибора  по меню и режимам работы
#define MEMCFG  (unsigned int*) 0x02A		// Организация блоков памяти измерений
#define MEMPNT  (unsigned int*) 0x030		// Указатель адреса по ячейкам
#define NASTR   (unsigned char*)0x035		// Номер настройки
#define CALIBD  (unsigned int*) 0x130		// Текущее значение калибровки 0
#define BRIGHT  (unsigned char*)0x38		// Текущее значение яркости.
#define MINUTES_OFF (unsigned char*)0x132	// автовыключение минут
#define VEL1  (unsigned int*)0X040 //CКОРОСТЬ НАСТРОЙКИ1
#define VEL2  (unsigned int*)0X042 //CКОРОСТЬ НАСТРОЙКИ2
#define VEL3  (unsigned int*)0X044 //CКОРОСТЬ НАСТРОЙКИ3
#define VEL4  (unsigned int*)0X046 //CКОРОСТЬ НАСТРОЙКИ4
#define VEL5  (unsigned int*)0X048 //CКОРОСТЬ НАСТРОЙКИ5
#define VEL6  (unsigned int*)0X04A //CКОРОСТЬ НАСТРОЙКИ6
#define VEL7  (unsigned int*)0X04C //CКОРОСТЬ НАСТРОЙКИ7
#define VEL8  (unsigned int*)0X04E //CКОРОСТЬ НАСТРОЙКИ8
#define VEL9  (unsigned int*)0X050 //CКОРОСТЬ НАСТРОЙКИ9
#define VEL10 (unsigned int*)0X052 //CКОРОСТЬ НАСТРОЙКИ10

#define AMP1  (unsigned char*)0X054 //УСИЛЕНИЕ НАСТРОЙКИ1
#define AMP2  (unsigned char*)0X056 //УСИЛЕНИЕ НАСТРОЙКИ2
#define AMP3  (unsigned char*)0X058 //УСИЛЕНИЕ НАСТРОЙКИ3
#define AMP4  (unsigned char*)0X05A //УСИЛЕНИЕ НАСТРОЙКИ4
#define AMP5  (unsigned char*)0X05C //УСИЛЕНИЕ НАСТРОЙКИ5
#define AMP6  (unsigned char*)0X05E //УСИЛЕНИЕ НАСТРОЙКИ6
#define AMP7  (unsigned char*)0X060 //УСИЛЕНИЕ НАСТРОЙКИ7
#define AMP8  (unsigned char*)0X062 //УСИЛЕНИЕ НАСТРОЙКИ8
#define AMP9  (unsigned char*)0X064 //УСИЛЕНИЕ НАСТРОЙКИ9
#define AMP10 (unsigned char*)0X066 //УСИЛЕНИЕ НАСТРОЙКИ10

#define DATCH1  (unsigned char*)0X070 //Датчик НАСТРОЙКИ1
#define DATCH2  (unsigned char*)0X071 //Датчик НАСТРОЙКИ2
#define DATCH3  (unsigned char*)0X072 //Датчик НАСТРОЙКИ3
#define DATCH4  (unsigned char*)0X073 //Датчик НАСТРОЙКИ4
#define DATCH5  (unsigned char*)0X074 //Датчик НАСТРОЙКИ5
#define DATCH6  (unsigned char*)0X075 //Датчик НАСТРОЙКИ6
#define DATCH7  (unsigned char*)0X076 //Датчик НАСТРОЙКИ7
#define DATCH8  (unsigned char*)0X077 //Датчик НАСТРОЙКИ8
#define DATCH9  (unsigned char*)0X078 //Датчик НАСТРОЙКИ9
#define DATCH10 (unsigned char*)0X079 //Датчик НАСТРОЙКИ10

#define MODE1  (unsigned char*)0x080 //Режим работы настройки1
#define MODE2  (unsigned char*)0x081 //Режим работы настройки2
#define MODE3  (unsigned char*)0x082 //Режим работы настройки3
#define MODE4  (unsigned char*)0x083 //Режим работы настройки4
#define MODE5  (unsigned char*)0x084 //Режим работы настройки5
#define MODE6  (unsigned char*)0x085 //Режим работы настройки6
#define MODE7  (unsigned char*)0x086 //Режим работы настройки7
#define MODE8  (unsigned char*)0x087 //Режим работы настройки8
#define MODE9  (unsigned char*)0x088 //Режим работы настройки9
#define MODE10 (unsigned char*)0x089 //Режим работы настройки10

#define CALB1  0x08A // Калибровка в настр 1
#define CALB2  0x08C // Калибровка в настр 2
#define CALB3  0x08E // Калибровка в настр 3
#define CALB4  0x090 // Калибровка в настр 4
#define CALB5  0x092 // Калибровка в настр 5
#define CALB6  0x094 // Калибровка в настр 6
#define CALB7  0x096 // Калибровка в настр 7
#define CALB8  0x098 // Калибровка в настр 8
#define CALB9  0x09A // Калибровка в настр 9
#define CALB10 0x09C // Калибровка в настр 10

#define BEEP_MODE 0x09E // Разрешение звука

#define RAZB_H1  0x0A0 // Пороги Верх Низ для разбраковки в настройке1 word
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

// Заводской Номер прибора     формат 3.2.1.0.  4 байта байт на символ.

#define ZNUM0 0x110 // Символ номера прибора 0
#define ZNUM1 0x111	// Символ номера прибора 1
#define ZNUM2 0x112	// Символ номера прибора 2
#define ZNUM3 0x113	// Символ номера прибора 3
#define TNAR  0x120 // DWORD Наработки   1ед мзр 1минута   макс число 71582.7882 тысячи часов

#define DIFFU1 0x0D0 // Порог Дифф режима в настройке 1 word
#define DIFFU2 0x0D2 // Порог Дифф режима в настройке 2
#define DIFFU3 0x0D4 // Порог Дифф режима в настройке 3
#define DIFFU4 0x0D6 // Порог Дифф режима в настройке 4
#define DIFFU5 0x0D8 // Порог Дифф режима в настройке 5
#define DIFFU6 0x0DA // Порог Дифф режима в настройке 6
#define DIFFU7 0x0DC // Порог Дифф режима в настройке 7
#define DIFFU8 0x0DE // Порог Дифф режима в настройке 8
#define DIFFU9 0x0E0 // Порог Дифф режима в настройке 9
#define DIFFU10 0x0E2 // Порог Дифф режима в настройке 10

#define DIFFP1  (unsigned char*)0x0E4 // Полярность в дифф режиме в настройке 1 byte
#define DIFFP2  (unsigned char*)0x0E5 // Полярность в дифф режиме в настройке 2
#define DIFFP3  (unsigned char*)0x0E6 // Полярность в дифф режиме в настройке 3
#define DIFFP4  (unsigned char*)0x0E7 // Полярность в дифф режиме в настройке 4
#define DIFFP5  (unsigned char*)0x0E8 // Полярность в дифф режиме в настройке 5
#define DIFFP6  (unsigned char*)0x0E9 // Полярность в дифф режиме в настройке 6
#define DIFFP7  (unsigned char*)0x0EA // Полярность в дифф режиме в настройке 7
#define DIFFP8  (unsigned char*)0x0EB // Полярность в дифф режиме в настройке 8
#define DIFFP9  (unsigned char*)0x0EC // Полярность в дифф режиме в настройке 9
#define DIFFP10 (unsigned char*)0x0ED // Полярность в дифф режиме в настройке 10

#define NONIUSU1 0x0F0 /// Поправка уровень для режима нониус в настройке 1 word
#define NONIUSU2 0x0F2 /// Поправка уровень для режима нониус в настройке 2
#define NONIUSU3 0x0F4 /// Поправка уровень для режима нониус в настройке 3
#define NONIUSU4 0x0F6 /// Поправка уровень для режима нониус в настройке 4
#define NONIUSU5 0x0F8 /// Поправка уровень для режима нониус в настройке 5
#define NONIUSU6 0x0FA /// Поправка уровень для режима нониус в настройке 6
#define NONIUSU7 0x0FC /// Поправка уровень для режима нониус в настройке 7
#define NONIUSU8 0x0FE /// Поправка уровень для режима нониус в настройке 8
#define NONIUSU9 0x100 /// Поправка уровень для режима нониус в настройке 9
#define NONIUSU10 0x102 /// Поправка уровень для режима нониус в настройке 10

#define NONIUSP1 (unsigned char*)0x104 /// Полярность поправки для режима нониус в настройке 1 byte
#define NONIUSP2 (unsigned char*)0x105 /// Полярность поправки для режима нониус в настройке 2
#define NONIUSP3 (unsigned char*)0x106 /// Полярность поправки для режима нониус в настройке 3
#define NONIUSP4 (unsigned char*)0x107 /// Полярность поправки для режима нониус в настройке 4
#define NONIUSP5 (unsigned char*)0x108 /// Полярность поправки для режима нониус в настройке 5
#define NONIUSP6 (unsigned char*)0x109 /// Полярность поправки для режима нониус в настройке 6
#define NONIUSP7 (unsigned char*)0x10A /// Полярность поправки для режима нониус в настройке 7
#define NONIUSP8 (unsigned char*)0x10B /// Полярность поправки для режима нониус в настройке 8
#define NONIUSP9 (unsigned char*)0x10C /// Полярность поправки для режима нониус в настройке 9
#define NONIUSP10 (unsigned char*)0x10D /// Полярность поправки для режима нониус в настройке 10

#define i2cdel	asm volatile("nop"); asm volatile("nop"); asm volatile("nop");asm volatile("nop"); asm volatile("nop"); asm volatile("nop");

#define eeRD 0xA1			// аппаратный адрес  для чтения еепром
#define eeWR 0xA0			// аппаратный адрес  для записи еепром

#define idel 1				// Задержка i2c
#define SDA_LN PH1          // линия SDA
#define SCL_LN PH2          // линия SCL
#define I2C_PIN PINH		// порт входа
#define I2C_DDR DDRH		// порт направления
#define I2C_PORT PORTH		// порт выхода

#define IN_LN 0				//линия на вход
#define OUT_LN 1			//линия на выход

#define ACK 1				//посылать подтверждение приема (не последний байт)
#define NOT_ACK 0			//не подтверждать прием (последний байт)

#define I2C_T 0.00001		//период импульса синхронизации (1/I2C_T = частота шины)
//при программной реализации шины

//! #define SDA PH1
//! #define SCL PH2

#define mSCL PJ1			// линия клок еепром
#define mSDA PJ0			// линия данных
#define EEPJ PORTJ
#define INPJ PINJ

#define SDLDAC PF5			// Линии ЦАП
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

#define KEY_PORT PINL       // Порт клавиатуры PJ3-PJ6
#define ONKEY PF3			// Признак нажатия клавишы включения.
#define EXTPOWER PK5		// Когда 0 - подключено внешнее питание !!!

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
#define nonius_half_range 500			// половина диапазона Нониуса 0-499 отрицательные, 500-1000 положительные
#define range_switching_threshold 10000 // если более 100мм то 0,1 иначе 0,01
#define long_max 0xffffffff
#define int_max  0xffff
#define lowlim 60						// 0.6 мм
#define uplim 50000						// 500 мм
///////////////////////////////////////////////////////////////////////////////////////
#define clear_color 15
#define back_color_const  9
#define half_color 12
#define front_color 0
#define inverse_color 16
#define fnt_width_8 8					// ширина шрифта в точках
#define fnt_width_16 16					// ширина шрифта в точках
#define scrol_pos 31					// положение полосы прокрутки
#define limits_pos 27					// положение границ ввода

#define number_offset 48				// смещение цифр в таблице ascii 
#define number_dot_offset 179			// смещение цифр в таблице ascii 
#define dot 1							// есть точка в строке
#define nodot 0							// нет точки в строке
#define nobigdot 0xff					// нет точки в большом шрифте

#define delay_8sec 72					// задержка в 8 секунд 
#define delay_5sec 60					// задержка в 4 секунды 
#define delay_4sec 36					// задержка в 4 секунды 
#define delay_3sec 26					// задержка в 3 секунды 
#define delay_2sec 18					// задержка в 2 секунды 9
#define delay_1sec 8					// задержка в 1 секунду 8
#define delay_05sec 4					// задержка в 0.5 секунды 4

#define key_pwr_limit 10				// задержка удержания кнопки выключения 30
#define bright_speed 20					// задержка "гашения" экрана при вкл/выкл
//____________________ положения точек вывода на экране [measurement] _________
#define measure_pos 6					// позиция основного измерения main_value
#define measure_raw 1					// строка основного измерения 
#define pep_pos 0						// позиция типа ПЭП в строке
#define pep_raw 0						// строка названия датчика
#define velocity_pos 2					// позиция скорости
#define velocity_raw 3					// строка скорости
#define velocity_lim_pos 27				// позиция границ изменения скорости
#define journal_pos 21					// позиция: страница журнала + номер измерения 0..31
#define journal_raw 3					// строка журнала


//_____________________________ параметры пунктов меню ________________________
#define item2show 3						// количество пунктов меню для отображения 
#define item2show_file 4				// количество пунктов меню для отображения
#define menu_modes_length 5				// количество пунктов в меню "режимы"
#define func_delay 30					// задержка задач функций 30
#define acont_delay 0x00FF			// задержка пропадения АК при сканировании
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

#define page_numb_max 100				// максимальное количество страниц в журнале
#define page_numb_min 0					// минимальное количество страниц в журнале
#define page_size_max 1000				// максимальный размер страницы (в шт записей) ограничено размером памяти
#define scr_raw 4						// количество строк на экране "Журнал"
#define scr_col 31						// количество символов в строке на экране "Журнал"
#define focus_raw 1						// номер строки с фокусом: 0 1 2 3

#define journal_row_num 125
#define journal_col_num 16
#define journal_buf    journal_row_num*journal_col_num
#define entry_size 3					// количество байт в записи
#define entry_offset   page_numb_max*4	// 4 байта для смещения страницы
#define journal_addr 0x140
#define journal_commands 2				// количество команд в списке журнала
#define contents journal_addr+0x04		// смещение оглавления
#define pages_addr contents+page_numb_max*4	// смещение страницы 0 (начало журнала)
//_____________________________________________________________________________
#define language_rus					// выбор языка меню: language_rus, language_eng, language_trl.
#define mode_numb 5						// число пунктов меню режимы

#define maket_build						// переворот экрана и кнопка питания, звук включен по умолчанию 
										//#define rotate_screen	// переворот экрана, если не надо - закоментарить
 
//____________________________ меню режимов на английском _____________________
#define menu_modes_width 12				// по 12 символов
#define menu_modes_big_pos 2			// для больших букв
#define menu_modes_pos 10				// позиция в символах от левого края
#define modes_numb 5					// количество пунктов меню режимы
#ifdef   language_eng
		#define menu_modes_line0 " MEASUREMENT"				
		#define menu_modes_line1 "  SCANNING  "
		#define menu_modes_line2 "    GRADE   "
		#define menu_modes_line3 "  DEVIATION " 
		#define menu_modes_line4 "   NONIUS   "
#endif
//____________________________ меню режимов на русском ________________________
#ifdef   language_rus
		#define menu_modes_line0 "  ИЗМЕРЕНИЕ "	
		#define menu_modes_line1 "СКАНИРОВАНИЕ"
		#define menu_modes_line2 " РАЗБРАКОВКА"
		#define menu_modes_line3 " ОТКЛОНЕНИЕ "
		#define menu_modes_line4 "   НОНИУС   "


#endif
//____________________________ меню режимов на транслитерации _________________
#ifdef   language_trl
		#define menu_modes_line0 "  IZMERENIE "
		#define menu_modes_line1 "SKANIROVANIE"
		#define menu_modes_line2 " RAZBRAKOVKA"
		#define menu_modes_line3 " OTKLONENIE "
		#define menu_modes_line4 "   NONIUS   "

#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ меню настроек на английском _____________________
#define menu_settings_width 15								// по 20 символов
#define menu_settings_pos 9									// позиция в символах от левого края
#define menu_settings_big_pos 0								// для больших букв
#define settings_numb 16									// количество пунктов меню настройки
#define align_settings 0									// выравнивание в меню режимов
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
//____________________________ меню настроек на русском ________________________
#ifdef   language_rus
		#define menu_settings_line0   "   НАСТРОЙКА 1 "
		#define menu_settings_line1   "   НАСТРОЙКА 2 "
		#define menu_settings_line2   "   НАСТРОЙКА 3 "
		#define menu_settings_line3   "   НАСТРОЙКА 4 "
		#define menu_settings_line4   "   НАСТРОЙКА 5 "
		#define menu_settings_line5   "   НАСТРОЙКА 6 "
		#define menu_settings_line6   "   НАСТРОЙКА 7 "
		#define menu_settings_line7   "   НАСТРОЙКА 8 "
		#define menu_settings_line8   "   НАСТРОЙКА 9 "
		#define menu_settings_line9   "ПОЛИЭТИЛЕН>25ММ" //16
		#define menu_settings_line10  " АВТОВЫКЛЮЧЕНИЕ" //автовыключение
		#define menu_settings_line11  "    СИСТЕМА    "
		#define menu_settings_line12  "     ЭКРАН     "
		#define menu_settings_line13  "     ЗВУК      "
		#define menu_settings_line14  "    УСИЛЕНИЕ   "
		#define menu_settings_line15  " СБРОС НАСТРОЕК"
		
#endif
//____________________________ меню настроек на транслитерации _________
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
//____________________________ меню ПЭП на английском __________________
#define menu_pep_width 19								// по 18 символов
#define menu_pep_pos 6									// позиция в символах от левого края
#define menu_pep_big_pos 0
#define pep_numb 9										// количество датчиков
#ifdef   language_eng
		#define menu_pep_line0   "P112-10.0-6/2-T-003"//18
		#define menu_pep_line1   "P112-5.0-10/2-T-003"
		#define menu_pep_line2   "P112-2.5-12/2-T-003"
		#define menu_pep_line3   " P112-2.5Т-12/2-B  "
		#define menu_pep_line4   " P112-5.0Т-12/2-B  "
		#define menu_pep_line5   "  P112-2.5-12/2-A  "
		#define menu_pep_line6   "  P112-1.25-20/2-A "
		#define menu_pep_line7   "   P111-1.25-K20   "
		#define menu_pep_line8   "   P111-1.25-P20   "
#endif
//____________________________ меню ПЭП на русском _____________________
#ifdef   language_rus
		#define menu_pep_line0   "П112-10.0-6/2-Т-003"//0
		#define menu_pep_line1   "П112-5.0-10/2-Т-003"//1
		#define menu_pep_line2   "П112-2.5-12/2-Т-003"//2
		#define menu_pep_line3   " П112-2.5Т-12/2-Б  "//3 высокотемпературный
		#define menu_pep_line4   " П112-5.0Т-12/2-Б  "//4 высокотемпературный
		#define menu_pep_line5   " П112-2.5-12/2-А   "//5
		#define menu_pep_line6   " П112-1.25-20/2-А  "//6
		#define menu_pep_line7   " П111-1.25-К20     "//7
		#define menu_pep_line8   " П111-1.25-П20     "//8
#endif
//____________________________ меню ПЭП на транслитерации ______________
#ifdef   language_trl
		#define menu_pep_line0   "P112-10.0-6/2-T-003"//18
		#define menu_pep_line1   "P112-5.0-10/2-T-003"
		#define menu_pep_line2   "P112-2.5-12/2-T-003"
		#define menu_pep_line3   " P112-2.5Т-12/2-B  "
		#define menu_pep_line4   " P112-5.0Т-12/2-B  "
		#define menu_pep_line5   "  P112-2.5-12/2-A  "
		#define menu_pep_line6   "  P112-1.25-20/2-A "
		#define menu_pep_line7   "   P111-1.25-K20   "
		#define menu_pep_line8   "   P111-1.25-P20   "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ меню калибровка на английском ___________
#define menu_calibration_width 13							// по 13 символов
#define menu_calibration_pos 9								// позиция в символах от левого края
#define menu_calibration_big_pos 2							// позиция для больших букв
#define calibration_numb 3									// количество пунктов меню калибровка
#ifdef   language_eng
		#define menu_calibration_line0 "CALIBRATION 0"				
		#define menu_calibration_line1 "CALIBRATION V"
		#define menu_calibration_line2 "CALIBRATION H"		
#endif
//____________________________ меню калибровка на русском ______________
#ifdef   language_rus
		#define menu_calibration_line0 "КАЛИБРОВКА 0 "				
		#define menu_calibration_line1 "КАЛИБРОВКА V "
		#define menu_calibration_line2 "КАЛИБРОВКА H "		
#endif
//____________________________ меню калибровка на транслитерации _______
#ifdef   language_trl
		#define menu_calibration_line0 "KALIBROVKA 0 "
		#define menu_calibration_line1 "KALIBROVKA V "
		#define menu_calibration_line2 "KALIBROVKA H "		
#endif

/*
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 1 на английском______________________
#define msg_1_width 32							// по 32 символов
#define msg_1_pos 0								// позиция в символах от левого края
#ifdef   language_eng
		#define msg_1_line0 "                                "
		#define msg_1_line1 "            Hello,              "					//32
		#define msg_1_line2 "  which mode will be measured?  "
		#define msg_1_line3 "                                "
#endif
//____________________________ msg 1 на русском ________________________
#ifdef   language_rus
		#define msg_1_line0 "                                "
		#define msg_1_line1 "         Здравствуйте,          "					//32
		#define msg_1_line2 " В каком режиме будем измерять? "
		#define msg_1_line3 "                                "
#endif
//____________________________ msg 1 на транслитерации _________________
#ifdef   language_trl
		#define msg_1_line0 "                                "
		#define msg_1_line1 "         Zdravstvuite,          "					//32
		#define msg_1_line2 " V kakom rezime budem izmeryat? "
		#define msg_1_line3 "                                "
#endif*/
/*
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 2 на английском______________________
#define msg_2_width 32							// по 32 символов
#define msg_2_pos 0								// позиция в символах от левого края
#ifdef   language_eng
		#define msg_2_line0 "Welcome, the instrument is in the"
		#define msg_2_line1 "mode        MEASURING            "						//32
		#define msg_2_line2 "setting     POLYETHYLENE H>25 MM "
		#define msg_2_line3 "gain        25                   "
#endif
//____________________________ msg 2 на русском ________________________
#ifdef   language_rus
		#define msg_2_line0 "Здравствуйте, прибор находится   "
		#define msg_2_line1 "в режиме    ИЗМЕРЕНИЕ            "					//32
		#define msg_2_line2 "настройка   ПОЛИЭТИЛЕН H>25ММ    "
		#define msg_2_line3 "усиление    25                   "
#endif
//____________________________ msg 2 на транслитерации _________________
#ifdef   language_trl
		#define msg_2_line0 "Zdravstvuite, pribor nahoditsya  "
		#define msg_2_line1 "v rezime                         "						//32
		#define msg_2_line2 "nastroika                        "
		#define msg_2_line3 "usilenie                         "
#endif*/
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 5 на английском______________________
#define msg_5_width 32							// по 32 символов
#define msg_5_pos 0								// позиция в символах от левого края
#ifdef   language_eng
		#define msg_5_line0 "  SETTING                       "
		#define msg_5_line1 "     mode                       "
		#define msg_5_line2 "     gain                       "
		#define msg_5_line3 "                                "
#endif
//____________________________ msg 5 на русском ________________________
#ifdef   language_rus
		#define msg_5_line0 "НАСТРОЙКА                       "
		#define msg_5_line1 "    режим                       " //32
		#define msg_5_line2 " усиление                       "
		#define msg_5_line3 "                                "

#endif
//____________________________ msg 5 на транслитерации _________________
#ifdef   language_trl
		#define msg_5_line0 "NASTROIKA                       "
		#define msg_5_line1 "    rezim                       "
		#define msg_5_line2 " usilenie                       "
		#define msg_5_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 14 на английском______________________
#define msg_14_width 32							// по 32 символов
#define msg_14_pos 0							// позиция в символах от левого края
#ifdef   language_eng
		#define msg_14_line0 "   Ultrasonic thickness meter  "
		#define msg_14_line1 "     Version H02S05 UT-111     "
		#define msg_14_line2 "       Serial number           "
		#define msg_14_line3 "       Run time     hours      "
#endif
//____________________________ msg 14 на русском ________________________
#ifdef   language_rus
		#define msg_14_line0 "Ультразвуковой толщиномер УТ-111" //32
		#define msg_14_line1 "         Версия H02S05          "
		#define msg_14_line2 "      Заводской номер           "
		#define msg_14_line3 "      Наработка     часов       "
#endif
//____________________________ msg 14 на транслитерации __________________
#ifdef   language_trl
		#define msg_14_line0 "Ultrazvykovoi tolshinomer UT-111"
		#define msg_14_line1 "         Versia H02S05          "
		#define msg_14_line2 "      Zavodskoi nomer           "
		#define msg_14_line3 "      Narabotka     chasov      "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 15 на английском______________________
#define msg_15_width 32							// по 32 символов
#define msg_15_pos 0							// позиция в символах от левого края
#ifdef   language_eng
		#define msg_15_line0 "     Please, put the ultrasonic "
		#define msg_15_line1 "      transducer on the sample  "
		#define msg_15_line2 "		    thickness of    mm    "//calibration test blocks
		#define msg_15_line3 "                                "
#endif
//____________________________ msg 15 на русском ________________________
#ifdef   language_rus
		#define msg_15_line0 "                                "
		#define msg_15_line1 "    Установите, пожалуйста, ПЭП "
		#define msg_15_line2 "    на образец толщины    мм    "
		#define msg_15_line3 "                                "
#endif
//____________________________ msg 15 на транслитерации _________________
#ifdef   language_trl
		#define msg_15_line0 "                                "
		#define msg_15_line1 "    Ustanovite, pozaluista, PEP "
		#define msg_15_line2 "    na obrazec tolshini   mm    "
		#define msg_15_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 16 на английском______________________
#define msg_16_width 32							// по 32 символов
#define msg_16_pos 0							// позиция в символах от левого края
#ifdef   language_eng
		#define msg_16_line0 "                                 "
		#define msg_16_line1 " Zero calibration is performed,  "
		#define msg_16_line2 "   it is possible to measure     "
		#define msg_16_line3 "                                 "
#endif
//____________________________ msg 16 на русском ________________________
#ifdef   language_rus
		#define msg_16_line0 "                                 "
		#define msg_16_line1 "    Калибровка нуля выполнена,   "
		#define msg_16_line2 "    можно проводить измерения    "
		#define msg_16_line3 "                                 "
#endif
//____________________________ msg 16 на транслитерации _________________
#ifdef   language_trl
		#define msg_16_line0 "                                 "
		#define msg_16_line1 "  Kalibrovka nulya vipolnena,    "
		#define msg_16_line2 "   mozno provodit izmereniya     "
		#define msg_16_line3 "                                 "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 17 на английском______________________
#define msg_17_width 32							// по 32 символов
#define msg_17_pos 0							// позиция в символах от левого края
#ifdef   language_eng
		#define msg_17_line0 "                                "
		#define msg_17_line1 "  Ultrasonic velocity is set,   "
		#define msg_17_line2 "   it is possible to measure    "
		#define msg_17_line3 "                                "
#endif
//____________________________ msg 17 на русском ________________________
#ifdef   language_rus
		#define msg_17_line0 "                                "
		#define msg_17_line1 "    Скорость УЗК установлена    "
		#define msg_17_line2 "    можно проводить измерения   "
		#define msg_17_line3 "                                "
#endif
//____________________________ msg 17 на транслитерации _________________
#ifdef   language_trl
		#define msg_17_line0 "                                "
		#define msg_17_line1 "    Skorost UZK ustanovlena     "
		#define msg_17_line2 "    mozno provodit izmereniya   "
		#define msg_17_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 18 на английском______________________
#define msg_18_width 32							// по 32 символов
#define msg_18_pos 0							// позиция в символах от левого края
#ifdef   language_eng
		#define msg_18_line0 "                                "
		#define msg_18_line1 "  Please, enter the thickness   "
		#define msg_18_line2 " of the sample and press Enter  "
		#define msg_18_line3 "                                "
#endif
//____________________________ msg 18 на русском ________________________
#ifdef   language_rus
		#define msg_18_line0 "                                "
		#define msg_18_line1 " Введите, пожалуйста, значение  "
		#define msg_18_line2 " толщины образца и нажмите Enter"
		#define msg_18_line3 "                                "
#endif
//____________________________ msg 18 на транслитерации _________________
#ifdef   language_trl
		#define msg_18_line0 "                                "
		#define msg_18_line1 "Vvedite, pozaluista, znachehie  "
		#define msg_18_line2 "tolshini obrazca i nazmite Enter"
		#define msg_18_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 19 на английском______________________
#define msg_19_width 32							// по 32 символов
#define msg_19_pos 0							// позиция в символах от левого края
#ifdef   language_eng
#define msg_19_line0 "                                "
#define msg_19_line1 "     Please, put the ultrasonic "
#define msg_19_line2 "     transducer on the sample   "
#define msg_19_line3 "		                          "

#endif
//____________________________ msg 19 на русском ________________________
#ifdef   language_rus
#define msg_19_line0 "                                "
#define msg_19_line1 "     Установите, пожалуйста,    "
#define msg_19_line2 "     ПЭП на образец толщины     "
#define msg_19_line3 "                                "
#endif
//____________________________ msg 19 на транслитерации _________________
#ifdef   language_trl
#define msg_19_line0 "                                "
#define msg_19_line1 "     Ustanovite, pozaluista,    "
#define msg_19_line2 "     PEP na obrazec tolshini    "
#define msg_19_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 3 на английском_______________________
#define msg_3_width 32							// по 32 символов
#define msg_3_pos 0								// позиция в символах от левого края
#ifdef   language_eng
#define msg_3_line0 "                               "
#define msg_3_line1 "    Please, select the mode    "
#define msg_3_line2 "       and press Enter         "
#define msg_3_line3 "                               "
#endif
//____________________________ msg 3 на русском _________________________
#ifdef   language_rus
#define msg_3_line0 "                                " //32
#define msg_3_line1 "   Пожалуйста, выберите режим   "
#define msg_3_line2 "     и нажмите кнопку Enter     "
#define msg_3_line3 "                                "
#endif
//____________________________ msg 3 на транслитерации ___________________
#ifdef   language_trl
#define msg_3_line0 "                                "
#define msg_3_line1 "   Pozaluista, viberite rezim   "
#define msg_3_line2 "     i nazmite knopku Enter     "
#define msg_3_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 4 на английском________________________
#define msg_4_width 32							// по 32 символов
#define msg_4_pos 0								// позиция в символах от левого края
#ifdef   language_eng
#define msg_4_line0 "                      ULTRASONIC"
#define msg_4_line1 "          THICKNESS METER UT-111"
#define msg_4_line2 "                                "
#define msg_4_line3 "                   NPK LUCH 2013"
#endif
//____________________________ msg 4 на русском ___________________________
#ifdef   language_rus
#define msg_4_line0 "                  УЛЬТРАЗВУКОВОЙ" //32
#define msg_4_line1 "               ТОЛЩИНОМЕР УТ-111"
#define msg_4_line2 "                                "
#define msg_4_line3 "                    НПК ЛУЧ 2013"
#endif
//____________________________ msg 4 на транслитерации _____________________
#ifdef   language_trl
#define msg_4_line0 "                   ULTRAZVUKOVOI" //32
#define msg_4_line1 "              TOLSHINOMER UT-111"
#define msg_4_line2 "                                "
#define msg_4_line3 "                   NPK LUCH 2013"
#endif

/*
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 11 на русском____________________________
#define msg_30_width 31							// по 32 символов
#define msg_30_pos 0								// позиция в символах от левого края [001/999]
#define msg_30_numb 5
#ifdef   language_rus
		#define msg_30_line0 "Очистить Журнал                "
		#define msg_30_line1 "Новая страница                 "
		#define msg_30_line2 "[001]  3                       "
		#define msg_30_line3 "[002] 33                       "
		#define msg_30_line4 "[003]999                       "
#endif

//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 6 на русском_____________________________
#define msg_31_width 31							// по 32 символов
#define msg_31_pos 0								// позиция в символах от левого края
#ifdef   language_rus
		#define msg_31_line0 "1) 12.7мм                      "
		#define msg_31_line1 "2)  2.3мм                      "
		#define msg_31_line2 "3) 9.21мм                      "
		#define msg_31_line3 "4)301.3мм                      "
		#define msg_31_line4 "5)  5.1мм                      "
#endif
*/



/*
//////////////////////////////////////////////////////////////////////////////////////
//____________________________ msg 9 на английском__________________________
#define msg_9_width 32							// по 32 символов
#define msg_9_pos 0								// позиция в символах от левого края
#ifdef   language_eng
		#define msg_9_line0 "       Saving settings!          "
		#define msg_9_line1 "            Goodbye,             "						//32
		#define msg_9_line2 "       with best wishes!         "
		#define msg_9_line3 "                                 "
#endif
//____________________________ msg 9 на русском _____________________________
#ifdef   language_rus
		#define msg_9_line0 "       Сохранение настроек!      "
		#define msg_9_line1 "           До свидания,          "					//32
		#define msg_9_line2 "        всего Вам доброго!       "
		#define msg_9_line3 "                                 "
#endif
//____________________________ msg 9 на транслитерации ______________________
#ifdef   language_trl
		#define msg_9_line0 "      Sohranenie nastroek!       "
		#define msg_9_line1 "          Do svidaniya,          "						//32
		#define msg_9_line2 "        vsego vam dobrogo!       "
		#define msg_9_line3 "                                 "
#endif*/
////////////////////////////////////////////////////////////////////////////
//____________________________ msg_20 скорость измерена по известной толщине на английском ________________
#define msg_20_width 32										// по 32 символа
#define msg_20_pos 0										// позиция в символах от левого края
//#define reset_numb 2										// количество пунктов меню звук
#ifdef   language_eng
#define msg_20_line0 "        ULTRASONIC VELOCITY     "
#define msg_20_line1 "                                "
#define msg_20_line2 "                     m/s        "
#define msg_20_line3 "measured according to thickness "
#endif
//____________________________ msg_20 на русском ___________________
#ifdef   language_rus
#define msg_20_line0 "           СКОРОСТЬ УЗК         "
#define msg_20_line1 "                                "
#define msg_20_line2 "                     М/С        "
#define msg_20_line3 " измерено по известной толщине  "
#endif
//____________________________ msg_20 на транслитерации ____________
#ifdef   language_trl
#define msg_20_line0 "           SKOROST UZK          "
#define msg_20_line1 "                                "
#define msg_20_line2 "                     m/s        "
#define msg_20_line3 " izmereno po izvestnoy tolshine "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define msg_21_width 32							// по 32 символов
#define msg_21_pos 0								// позиция в символах от левого края
//____________________________ msg 21 на английском________________________
#ifdef   language_eng
	#define msg_21_line0 "      Page  [   ] was addied,    " 
	#define msg_21_line1 "       All measurements are      "
	#define msg_21_line2 "         will saved in it        "
	#define msg_21_line3 "                                 "
#endif
//____________________________ msg 21 на русском ___________________________
#ifdef   language_rus
	#define msg_21_line0 "   Страница [   ] добавлена,     " 
	#define msg_21_line1 "      Все изменения будут        "
	#define msg_21_line2 "       сохранятся в ней          "
	#define msg_21_line3 "                                 "
#endif
//____________________________ msg 21 на транслитерации _____________________
#ifdef   language_trl
	#define msg_21_line0 "   Stranica [   ] dobavlena,     " 
	#define msg_21_line1 "      Vse izmeneniya budut       "
	#define msg_21_line2 "       sohranyatsya v nei        "
	#define msg_21_line3 "                                 "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define msg_22_width 32							// по 32 символов
#define msg_22_pos 0							// позиция в символах от левого края
//____________________________ msg 22 на английском______________________
#ifdef   language_eng
#define msg_22_line0 "                                "
#define msg_22_line1 " Zero calibration NOT performed,"
#define msg_22_line2 "   zero calibration defaults    "
#define msg_22_line3 "                                "
#endif
//____________________________ msg 22 на русском ________________________
#ifdef   language_rus
#define msg_22_line0 "                                "
#define msg_22_line1 " Калибровка нуля НЕ выполнена,  "
#define msg_22_line2 "     значение по умолчанию      "
#define msg_22_line3 "                                "
#endif
//____________________________ msg 22 на транслитерации _________________
#ifdef   language_trl
#define msg_22_line0 "                                "
#define msg_22_line1 "  Kalibrovka nulya NE vipolnena,"
#define msg_22_line2 "    Kalibrovka po umolchaniu    "
#define msg_22_line3 "                                "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define msg_23_width 32							// по 32 символов
#define msg_23_pos 0							// позиция в символах от левого края
//____________________________ msg 23 на английском______________________
#ifdef   language_eng
#define msg_23_line0 "New Page                        "
#define msg_23_line1 "Clear Journal  [   /    ]       "
#endif
//____________________________ msg 23 на русском ________________________
#ifdef   language_rus
#define msg_23_line0 "Новая Страница                  "
#define msg_23_line1 "Очистить Журнал[   /    ]       "
#endif
//____________________________ msg 23 на транслитерации _________________
#ifdef   language_trl
#define msg_23_line0 "Novaya Stranitsa                "
#define msg_23_line1 "Ochistit Jurnal[   /    ]       "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define dlg_1_width 32							// по 32 символов
#define dlg_1_pos 0								// позиция в символах от левого края
//____________________________ dlg_1 на английском____________________________
#ifdef   language_eng
#define dlg_1_line0 "           CORRECTION $         "
#define dlg_1_line1 "                          +5.00 "						//32
#define dlg_1_line2 "                   mm     -5.00 "
#define dlg_1_line3 "                                "
#endif
//____________________________ dlg 1 на русском ______________________________
#ifdef   language_rus
#define dlg_1_line0 "           ПОПРАВКА $           "
#define dlg_1_line1 "                          +5.00 "					//32
#define dlg_1_line2 "                   мм     -5.00 "
#define dlg_1_line3 "                                "
#endif
//____________________________ dlg 1 на транслитерации ________________________
#ifdef   language_trl
#define dlg_1_line0 "           POPRAVKA $           "
#define dlg_1_line1 "                          +5.00 "						//32
#define dlg_1_line2 "                   mm     -5.00 "
#define dlg_1_line3 "                                "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define dlg_2_width 32							// по 32 символов
#define dlg_2_pos 0								// позиция в символах от левого края
//____________________________ dlg_2 на английском____________________________
#ifdef   language_eng
#define dlg_2_line0 "           BASIC LEVEL          "
#define dlg_2_line1 "                           0.60 "						//32
#define dlg_2_line2 "                   mm     500.0 "
#define dlg_2_line3 "                                "
#endif
//____________________________ dlg 1 на русском ______________________________
#ifdef   language_rus
#define dlg_2_line0 "         БАЗОВЫЙ УРОВЕНЬ        "
#define dlg_2_line1 "                           0.60 "					//32
#define dlg_2_line2 "                   мм     500.0 "
#define dlg_2_line3 "                                "
#endif
//____________________________ dlg 1 на транслитерации ________________________
#ifdef   language_trl
#define dlg_2_line0 "         BAZOVII UROVEN         "
#define dlg_2_line1 "                           0.60 "						//32
#define dlg_2_line2 "                   mm     500.0 "
#define dlg_2_line3 "                                "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define dlg_3_width 32							// по 32 символов
#define dlg_3_pos 0								// позиция в символах от левого края
//____________________________ dlg_3 на английском_____________________________
#ifdef   language_eng
#define dlg_3_line0 "           LOWER LIMIT          "
#define dlg_3_line1 "                          500.0 "						//32
#define dlg_3_line2 "                   mm      0.60 "
#define dlg_3_line3 "                                "
#endif
//____________________________ dlg 3 на русском _______________________________
#ifdef   language_rus
#define dlg_3_line0 "         НИЖНИЙ ПРЕДЕЛ          "
#define dlg_3_line1 "                          500.0 "					//32
#define dlg_3_line2 "                   мм      0.60 "
#define dlg_3_line3 "                                "
#endif
//____________________________ dlg 3 на транслитерации ________________________
#ifdef   language_trl
#define dlg_3_line0 "         NIZNII PREDEL          "
#define dlg_3_line1 "                          500.0 "						//32
#define dlg_3_line2 "                   mm      0.60 "
#define dlg_3_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
#define dlg_4_width 32							// по 32 символов
#define dlg_4_pos 0								// позиция в символах от левого края
//____________________________ dlg_4 на английском_____________________________
#ifdef   language_eng
#define dlg_4_line0 "           UPPER LIMIT          "
#define dlg_4_line1 "                          500.0 "						//32
#define dlg_4_line2 "                   mm      0.60 "
#define dlg_4_line3 "                                "
#endif
//____________________________ dlg 4 на русском _______________________________
#ifdef   language_rus
#define dlg_4_line0 "         ВЕРХНИЙ ПРЕДЕЛ         "
#define dlg_4_line1 "                          500.0 "					//32
#define dlg_4_line2 "                   мм      0.60 "
#define dlg_4_line3 "                                "
#endif
//____________________________ dlg 4 на транслитерации ________________________
#ifdef   language_trl
#define dlg_4_line0 "         VERHNII PREDEL         "
#define dlg_4_line1 "                          500.0 "						//32
#define dlg_4_line2 "                   mm      0.60 "
#define dlg_4_line3 "                                "
#endif
//////////////////////////////////////////////////////////////////////////////////////
#define dlg_5_width 31							// по 32 символов
#define dlg_5_pos 0								// позиция в символах от левого края
#define ee_minutes_off_min 0					// 0=никогда
#define ee_minutes_off_max 15
//____________________________ dlg 5 на английском__________________________
#ifdef   language_eng
#define dlg_5_line0 "          AUTO POWER OFF         "
#define dlg_5_line1 "                             15  "						//32
#define dlg_5_line2 "                     min      0  "
#define dlg_5_line3 "        without the using        "
#endif
//____________________________ dlg 5 на русском ____________________________
#ifdef   language_rus
#define dlg_5_line0 "          АВТОВЫКЛЮЧЕНИЕ         " // автовыключение прибора
#define dlg_5_line1 "                             15  "						//32
#define dlg_5_line2 "                     мин      0  "
#define dlg_5_line3 "        при неиспользовании      "
#endif
//____________________________ dlg 5 на транслитерации ______________________
#ifdef   language_trl
#define dlg_5_line0 "          AUTOVIKLUCHENIE        "
#define dlg_5_line1 "                             15  "						//32
#define dlg_5_line2 "                     min      0  "
#define dlg_5_line3 "         pri neispolzovanii      "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define dlg_6_width 12										// по 32 символов
#define dlg_6_big_width 12									// по 32 символов
#define dlg_6_pos 9											// позиция для малых букв в символах от левого края
#define dlg_6_big_pos 2										// для больших букв
#define dlg_6_numb 2										// количество пунктов яркости
#define brightness_max 1
#define brightness_min 0
//____________________________ dlg_6 яркость на английском ______________
#ifdef   language_eng
#define dlg_6_line0 "   SCREEN   "
#define dlg_6_line1 "   INDOORS  "
#define dlg_6_line2 "   OUTSIDE  "
#define dlg_6_line3 "            "
#endif
//____________________________ dlg_6 яркость на русском _________________
#ifdef   language_rus
#define dlg_6_line0 "   ЭКРАН    "
#define dlg_6_line1 "В ПОМЕЩЕНИИ "
#define dlg_6_line2 " НА СОЛНЦЕ  "
#define dlg_6_line3 "            "
#endif
//____________________________ dlg_6 яркость на транслитерации __________
#ifdef   language_trl
#define dlg_6_line0 "   EKRAN    "
#define dlg_6_line1 "V POMESHENII"
#define dlg_6_line2 " NA SOLNCE  "
#define dlg_6_line3 "            "
#endif
//////////////////////////////////////////////////////////////////////////////////////
#define dlg_7_width 32										// по 32 символа
#define dlg_7_pos 0											// позиция в символах от левого края
#define dlg_7_big_pos 7										// позиция больших символов в символах от левого края
#define dlg_7_big_width 4									//
#define sound_numb 2										// количество пунктов меню звук
//____________________________ dlg_7 sound на английском ________________
#ifdef   language_eng
#define dlg_7_line0 "             SOUND                 "
#define dlg_7_line1 "OFF "
#define dlg_7_line2 " ON "
#define dlg_7_line3 "                                   "
#endif
//____________________________ dlg_7 sound на русском ___________________
#ifdef   language_rus
#define dlg_7_line0 "              ЗВУК                 "
#define dlg_7_line1 "ВЫКЛ"
#define dlg_7_line2 " ВКЛ"
#define dlg_7_line3 "                                   "
#endif
//____________________________ dlg_7 sound на транслитерации ____________
#ifdef   language_trl
#define dlg_7_line0 "              ZVUK                 "
#define dlg_7_line1 "OFF "
#define dlg_7_line2 " ON "
#define dlg_7_line3 "                                   "
#endif
//////////////////////////////////////////////////////////////////////////////////////

#define dlg_8_width 32								// по 32 символа
#define dlg_8_pos 0									// позиция в символах от левого края
//____________________________ dlg_8 sound на английском ________________
#ifdef   language_eng
#define dlg_8_line0 "              GAIN             "
#define dlg_8_line1 "                             40"
#define dlg_8_line2 "                             10"
#define dlg_8_line3 "                               "
#endif
//____________________________ dlg_8 sound на русском ___________________
#ifdef   language_rus
#define dlg_8_line0 "            УСИЛЕНИЕ           "
#define dlg_8_line1 "                             40"
#define dlg_8_line2 "                             10"
#define dlg_8_line3 "                               "
#endif
//____________________________ dlg_8 sound на транслитерации ____________
#ifdef   language_trl
#define dlg_8_line0 "            USILENIE           "
#define dlg_8_line1 "                             40"
#define dlg_8_line2 "                             10"
#define dlg_8_line3 "                               "
#endif
////////////////////////////////////////////////////////////////////////////
#define dlg_9_width 32										// по 32 символа
#define dlg_9_pos 0											// позиция в символах от левого края
#define dlg_9_big_pos 8										// позиция больших символов в символах от левого края
#define dlg_9_big_width 4									//
//____________________________ dlg_9 sound на английском ________________
#ifdef   language_eng
#define dlg_9_line0 "    RESET SETTINGS TO DEFAULTS?    "
#define dlg_9_line1 "NO  "
#define dlg_9_line2 "YES "
#define dlg_9_line3 "                                   "
#endif
//____________________________ dlg_9 sound на русском ___________________
#ifdef   language_rus
#define dlg_9_line0 "     СБРОСИТЬ ВСЕ НАСТРОЙКИ?       "
#define dlg_9_line1 "НЕТ "
#define dlg_9_line2 " ДА "
#define dlg_9_line3 "                                   "
#endif
//____________________________ dlg_9 sound на транслитерации ____________
#ifdef   language_trl
#define dlg_9_line0 "     SBROSIT VSE NASTROIKI?        "
#define dlg_9_line1 "NET "
#define dlg_9_line2 "DA  "
#define dlg_9_line3 "                                   "
#endif
////////////////////////////////////////////////////////////////////////////
//____________________________ dlg_10 скорость УЗК на английском ________________
#define dlg_10_width 32										// по 32 символа
#define dlg_10_pos 0											// позиция в символах от левого края
#ifdef   language_eng
#define dlg_10_line0 "        ULTRASONIC VELOCITY       "
#define dlg_10_line1 "                           9999"
#define dlg_10_line2 "                    M/S     100"
#define dlg_10_line3 "                                  "
#endif
//____________________________ dlg_10 скорость УЗК на русском ___________________
#ifdef   language_rus
#define dlg_10_line0 "          СКОРОСТЬ УЗК          "
#define dlg_10_line1 "                           9999 "
#define dlg_10_line2 "                    М/С     100 "
#define dlg_10_line3 "                                "
#endif
//____________________________ dlg_10скорость УЗК на транслитерации ____________
#ifdef   language_trl
#define dlg_10_line0 "         SKOROST UZK            "
#define dlg_10_line1 "                           9999 "
#define dlg_10_line2 "                    M/S     100 "
#define dlg_10_line3 "                                "
#endif

////////////////////////////////////////////////////////////////////////////
#define dlg_11_width 31										// по 32 символа
#define dlg_11_pos 0										// позиция в символах от левого края
//____________________________ dlg_11 Толщина известная на английском ________________
#ifdef   language_eng
#define dlg_11_line0 "         KNOWN THICKNESS       "
#define dlg_11_line1 "                          500.0"
#define dlg_11_line2 "                    MM    0.60"
#define dlg_11_line3 "                               "
#endif
//____________________________ dlg_11 Толщина известная на русском ___________________
#ifdef   language_rus
#define dlg_11_line0 "        ТОЛЩИНА ИЗВЕСТНАЯ      "
#define dlg_11_line1 "                          500.0"
#define dlg_11_line2 "                    ММ     0.60"
#define dlg_11_line3 "                               "
#endif
//____________________________ dlg_11 Толщина известная на транслитерации ____________
#ifdef   language_trl
#define dlg_11_line0 "        TOLSHINA IZVESTNAYA    "
#define dlg_11_line1 "                          500.0"
#define dlg_11_line2 "                    MM     0.60"
#define dlg_11_line3 "                               "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define dlg_12_width 31									// по 32 символов
#define dlg_12_pos 0									// позиция в символах от левого края
#define dlg_12_big_pos 8	
#define dlg_12_big_width 3				
//____________________________ dlg 12 на английском__________________________
#ifdef   language_eng
#define dlg_12_line0 "         CLEAR THE LOG?          "
#define dlg_12_line1 " NO "						
#define dlg_12_line2 "YES "
#define dlg_12_line3 "                                 "
#endif
//____________________________ dlg 12 на русском ____________________________
#ifdef   language_rus
#define dlg_12_line0 "      ОЧИСТИТЬ ВЕСЬ ЖУРНАЛ?      " //32 
#define dlg_12_line1 "НЕТ "						
#define dlg_12_line2 " ДА "
#define dlg_12_line3 "                                 "
#endif
//____________________________ dlg 12 на транслитерации ______________________
#ifdef   language_trl
#define dlg_12_line0 "      OCHISTIT VES ZHURNAL?      "
#define dlg_12_line1 "NET "						
#define dlg_12_line2 " DA "
#define dlg_12_line3 "                                 "
#endif

//////////////////////////////////////////////////////////////////////////////////////
#define dlg_13_width 31									// по 32 символов
#define dlg_13_pos 0									// позиция в символах от левого края
#define dlg_13_big_pos 8
#define dlg_13_big_width 3
#define dlg_13_entry_pos 20								// позиция удаляемой записи в первой строке

//____________________________ dlg 13 на английском__________________________
#ifdef   language_eng
#define dlg_13_line0 "    CLEAR THE ENTRY       ?      "
#define dlg_13_line1 " NO "
#define dlg_13_line2 "YES "
#define dlg_13_line3 "                                 "
#endif
//____________________________ dlg 13 на русском ____________________________
#ifdef   language_rus
#define dlg_13_line0 "     УДАЛИТЬ ЗАПИСЬ       ?      " //32
#define dlg_13_line1 "НЕТ "
#define dlg_13_line2 " ДА "
#define dlg_13_line3 "                                 "
#endif
//____________________________ dlg 13 на транслитерации ______________________
#ifdef   language_trl
#define dlg_13_line0 "      UDALIT ZAPIS        ?      "
#define dlg_13_line1 "NET "
#define dlg_13_line2 " DA "
#define dlg_13_line3 "                                 "
#endif
//////////////////////////////////////////////////////////////////////////////////////
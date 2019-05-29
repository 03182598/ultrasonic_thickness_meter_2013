//ВЕРСИЯ ТОЛЩИНОМЕРА    verHa+verHb . verSa+verSb  ==  Версия H01.S01
#define verHA 0
#define verHb 2

#define verSa 0
#define verSb 3


 /// клавиатура 
#define keyup 7
#define keydown 8
#define keyenter 9
#define keyrezim 4
#define keynastr 5
#define keyzero 2
#define keypep 1
#define keymem 6
#define key_off 1

#define LF 10 /// Перевод строки
#define CR 13 /// Перевод каретки


#define M00err 0/// Ошибка 00 uart   -- Нет такой команды
#define M01err 1/// Ошибка 01 uart	 -- Нет такого файла	
#define M02err 2/// Ошибка 02 uart	 -- Превышен временной интервал запроса или потерянны данные из команды
#define M03err 3/// Ошибка 03 uart	 -- Неправильный формат данных (вместо цифр ascii другие символы)
#define END_S  4/// Конец передачи	Передано успешно  , список файлов или файл
#define GET_SN 5/// Прочитать номер прибора
#define W_OK  6 /// Операция успешно выполнена
#define FF0err 7/// Ошибка передачи файла
#define BOKV 8 /// Конец блока
#define BTOT 9 /// ТаймАут блока

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
////
#define LowSPEED 100 //// Минимальная скорость УЗК
#define HISPEED 9999 ///  Максимальная скорость УЗК

#define CALVL 6043 /// скорость в 3 мм образце.

#define stbokh  15000 /// Параметры моргания надписями уровней и порогов сбоку  число при котором гаснет 
#define stbokl  7500 //// число при котором зажигается.

#define maxPEP 9/// Максимальное число датчиков в приборе


#define step_speedX  12//40 //// шаг прокрутки числовых значений 000 
#define step_speed0  18//40 18//// шаг прокрутки числовых значений 
#define step_speeda  250 //// шаг прокрутки  значений усиления 

#define dkeyl 150 // задержка на клавиатуре long
#define dkeysh 50 // задержка на клавиатуре short
#define dkeyout 15 // задержка на выходе из меню  

#define step_speedZ  180 //// 180 шаг прокрутки  значений усиления 

#define step_apx 50/// шаг прокрутки из программы быстрорй прокрутки
#define readfilest 370 // шаг прокрутки ячеек файла в просмотре памяти
#define readfilestE 500	/// шаг скорости удаления



#define RAZBRH_low 31  /// границы уровней разбраковки
#define RAZBRH_hi 30000

#define RAZBRL_low 30
#define RAZBRL_hi 29990

#define NONIUSL 0	//  Уровень нониус	// -5.00мм
#define NONIUSH 1000 /// +5.00мм

#define DIFFHI 30000 /// Верхний уровень дифф 300.0мм
#define DIFFLO 30 /// Нижний уровень дифф 0.30мм


#define SCANMAX 65000 /// макс знач тощины при сканировании 


#define MaxHiS 30000 /// максимальная толщина при калибровке по толщине
#define MinHiS 10 /// минимальная толщина при калибровке по толщине

#define calobr3mm 3185 /// тест образец 3мм датчики 1-6
#define calobr5mm 5308 /// тест образей датчик 7
#define calobr20mm 21233 /// тест образец датчики 8-9



#define STAT (unsigned int*)0x0000   // Состояние при включении, если чистая память

//#define SNUMS 0x0002 /// Серийный Номер прибора word
//#define NARAB 0x0004 /// Наработка на отказ	dword

#define VELMEM (unsigned int*)0x0010 // скорость УЗК 
#define NUMDATC (unsigned char*)0x1A  // Номер датчика ТИП
#define MODES (unsigned char*)0x0020  // Состояние прибора  по меню и режимам работы
#define MEMCFG (unsigned int*)0x02A  // Организация блоков памяти измерений
#define MEMPNT (unsigned int*)0x030  // Указатель адреса по ячейкам

#define NASTR (unsigned char*)0x035 // Номер настройки

#define CALIBD (unsigned int*)0x130 // Текущее значение калибровки нуля 

#define BRIGHT (unsigned char*)0x38 /// Текущее значение яркости.

#define VEL1 (unsigned int*)0X040 //сКОРОСТЬ НАСТРОЙКИ1
#define VEL2 (unsigned int*)0X042 //сКОРОСТЬ НАСТРОЙКИ2
#define VEL3 (unsigned int*)0X044 //сКОРОСТЬ НАСТРОЙКИ3
#define VEL4 (unsigned int*)0X046 //сКОРОСТЬ НАСТРОЙКИ4
#define VEL5 (unsigned int*)0X048 //сКОРОСТЬ НАСТРОЙКИ5
#define VEL6 (unsigned int*)0X04A //сКОРОСТЬ НАСТРОЙКИ6
#define VEL7 (unsigned int*)0X04C //сКОРОСТЬ НАСТРОЙКИ7
#define VEL8 (unsigned int*)0X04E //сКОРОСТЬ НАСТРОЙКИ8
#define VEL9 (unsigned int*)0X050 //сКОРОСТЬ НАСТРОЙКИ9
#define VEL10 (unsigned int*)0X052 //сКОРОСТЬ НАСТРОЙКИ10


#define AMP1 (unsigned char*)0X054 //УСИЛЕНИЕ НАСТРОЙКИ1
#define AMP2 (unsigned char*)0X056 //УСИЛЕНИЕ НАСТРОЙКИ2
#define AMP3 (unsigned char*)0X058 //УСИЛЕНИЕ НАСТРОЙКИ3
#define AMP4 (unsigned char*)0X05A //УСИЛЕНИЕ НАСТРОЙКИ4
#define AMP5 (unsigned char*)0X05C //УСИЛЕНИЕ НАСТРОЙКИ5
#define AMP6 (unsigned char*)0X05E //УСИЛЕНИЕ НАСТРОЙКИ6
#define AMP7 (unsigned char*)0X060 //УСИЛЕНИЕ НАСТРОЙКИ7
#define AMP8 (unsigned char*)0X062 //УСИЛЕНИЕ НАСТРОЙКИ8
#define AMP9 (unsigned char*)0X064 //УСИЛЕНИЕ НАСТРОЙКИ9
#define AMP10 (unsigned char*)0X066 //УСИЛЕНИЕ НАСТРОЙКИ10


#define DATCH1 (unsigned char*)0X070 //Датчик НАСТРОЙКИ1
#define DATCH2 (unsigned char*)0X071 //Датчик НАСТРОЙКИ2
#define DATCH3 (unsigned char*)0X072 //Датчик НАСТРОЙКИ3
#define DATCH4 (unsigned char*)0X073 //Датчик НАСТРОЙКИ4
#define DATCH5 (unsigned char*)0X074 //Датчик НАСТРОЙКИ5
#define DATCH6 (unsigned char*)0X075 //Датчик НАСТРОЙКИ6
#define DATCH7 (unsigned char*)0X076 //Датчик НАСТРОЙКИ7
#define DATCH8 (unsigned char*)0X077 //Датчик НАСТРОЙКИ8
#define DATCH9 (unsigned char*)0X078 //Датчик НАСТРОЙКИ9
#define DATCH10 (unsigned char*)0X079 //Датчик НАСТРОЙКИ10

#define MODE1 (unsigned char*)0x080 //Режим работы настройки1
#define MODE2 (unsigned char*)0x081 //Режим работы настройки2
#define MODE3 (unsigned char*)0x082 //Режим работы настройки3
#define MODE4 (unsigned char*)0x083 //Режим работы настройки4
#define MODE5 (unsigned char*)0x084 //Режим работы настройки5
#define MODE6 (unsigned char*)0x085 //Режим работы настройки6
#define MODE7 (unsigned char*)0x086 //Режим работы настройки7
#define MODE8 (unsigned char*)0x087 //Режим работы настройки8
#define MODE9 (unsigned char*)0x088 //Режим работы настройки9
#define MODE10 (unsigned char*)0x089 //Режим работы настройки10



#define CALB1 0x08A /// Калибровка в настр 1
#define CALB2 0x08C /// Калибровка в настр 2
#define CALB3 0x08E /// Калибровка в настр 3
#define CALB4 0x090 /// Калибровка в настр 4
#define CALB5 0x092 /// Калибровка в настр 5
#define CALB6 0x094 /// Калибровка в настр 6
#define CALB7 0x096 /// Калибровка в настр 7
#define CALB8 0x098 /// Калибровка в настр 8
#define CALB9 0x09A /// Калибровка в настр 9
#define CALB10 0x09C /// Калибровка в настр 10

#define BEEP_MODE 0x09E //// Разрешение звука



#define RAZB_H1 0x0A0 /// Пороги Верх Низ для разбраковки в настройке1 word
#define RAZB_L1 0x0A2
#define RAZB_H2 0x0A4 /// Пороги Верх Низ для разбраковки в настройке2
#define RAZB_L2 0x0A6
#define RAZB_H3 0x0A8 /// Пороги Верх Низ для разбраковки в настройке3
#define RAZB_L3 0x0AA
#define RAZB_H4 0x0AC /// Пороги Верх Низ для разбраковки в настройке4
#define RAZB_L4 0x0AE
#define RAZB_H5 0x0B0 /// Пороги Верх Низ для разбраковки в настройке5
#define RAZB_L5 0x0B2
#define RAZB_H6 0x0B4 /// Пороги Верх Низ для разбраковки в настройке6
#define RAZB_L6 0x0B6
#define RAZB_H7 0x0B8 /// Пороги Верх Низ для разбраковки в настройке7
#define RAZB_L7 0x0BA
#define RAZB_H8 0x0BC /// Пороги Верх Низ для разбраковки в настройке8
#define RAZB_L8 0x0BE
#define RAZB_H9 0x0C0 /// Пороги Верх Низ для разбраковки в настройке9
#define RAZB_L9 0x0C2
#define RAZB_H10 0x0C4 /// Пороги Верх Низ для разбраковки в настройке10
#define RAZB_L10 0x0C6


	///// Заводской Номер прибора     формат 3.2.1.0.  4 байта байт на символ.
	
#define ZNUM0 0x110 /// Символ номера прибора 0
#define ZNUM1 0x111	/// Символ номера прибора 1
#define ZNUM2 0x112	/// Символ номера прибора 2
#define ZNUM3 0x113	/// Символ номера прибора 3

#define TNAR 0x120 /// DWORD Наработки   1ед мзр 1минута   макс число 71582.7882 тысячи часов 




#define DIFFU1 0x0D0 /// Порог Дифф режима в настройке 1 word
#define DIFFU2 0x0D2 /// Порог Дифф режима в настройке 2
#define DIFFU3 0x0D4 /// Порог Дифф режима в настройке 3
#define DIFFU4 0x0D6 /// Порог Дифф режима в настройке 4
#define DIFFU5 0x0D8 /// Порог Дифф режима в настройке 5
#define DIFFU6 0x0DA /// Порог Дифф режима в настройке 6
#define DIFFU7 0x0DC /// Порог Дифф режима в настройке 7
#define DIFFU8 0x0DE /// Порог Дифф режима в настройке 8
#define DIFFU9 0x0E0 /// Порог Дифф режима в настройке 9
#define DIFFU10 0x0E2 /// Порог Дифф режима в настройке 10


#define DIFFP1 (unsigned char*)0x0E4 /// Полярность в дифф режиме в настройке 1 byte
#define DIFFP2 (unsigned char*)0x0E5 /// Полярность в дифф режиме в настройке 2
#define DIFFP3 (unsigned char*)0x0E6 /// Полярность в дифф режиме в настройке 3
#define DIFFP4 (unsigned char*)0x0E7 /// Полярность в дифф режиме в настройке 4
#define DIFFP5 (unsigned char*)0x0E8 /// Полярность в дифф режиме в настройке 5
#define DIFFP6 (unsigned char*)0x0E9 /// Полярность в дифф режиме в настройке 6
#define DIFFP7 (unsigned char*)0x0EA /// Полярность в дифф режиме в настройке 7
#define DIFFP8 (unsigned char*)0x0EB /// Полярность в дифф режиме в настройке 8
#define DIFFP9 (unsigned char*)0x0EC /// Полярность в дифф режиме в настройке 9
#define DIFFP10 (unsigned char*)0x0ED /// Полярность в дифф режиме в настройке 10


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

#define eeRD 0xA1 ///  аппаратный адрес  для чтения еепром
#define eeWR 0xA0 ///  аппаратный адрес  для записи еепром

#define idel			  1 /// Задержка i2c
#define SDA_LN            PH1                         //линия SDA
#define SCL_LN            PH2                         //линия SCL
#define I2C_PIN           PINH                        //порт входа
#define I2C_DDR           DDRH                        //порт направления
#define I2C_PORT          PORTH                       //порт выхода

#define IN_LN             0                           //линия на вход
#define OUT_LN            1                           //линия на выход

#define ACK               1                           //посылать подтверждение приема (не последний байт)
#define NOT_ACK           0                           //не подтверждать прием (последний байт)

#define I2C_T             0.00001                     //период импульса синхронизации (1/I2C_T = частота шины)
                                                      //при программной реализации шины

#define SDA PH1
#define SCL PH2



#define mSCL PJ1 /// линия клок еепром
#define mSDA PJ0 /// линия данных 
#define EEPJ PORTJ
#define INPJ PINJ


#define SDLDAC PF5   //// Линии ЦАП
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

#define KEY_PORT PINL        /////// Порт клавиатуры PJ3-PJ6

#define ONKEY PF3      //// Признак нажатия клавишы включения.   

#define EXTPOWER PK5 /// Когда 0 - подключено внешнее питание !!!

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






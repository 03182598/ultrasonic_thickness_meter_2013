//// СТРУКТУРА ВНЕШНЕЙ ПАМЯТИ 

/*efine ftype_1		30000 /// количество ячеек памяти в типе файла
#define ftype_2		15000
#define ftype_5		6000
#define ftype_10	3000
#define ftype_20	1500
#define ftype_50	600
#define ftype_100	300*/

#define memstart	500 /// Отступ в 1к ячейку 2КБ   от начала памяти.  дальше идут файлы

#define pointstart 	300 /// Адрес откуда начинаются указатели положения курсора в файлах  последняя ячейка 900 при максимальном количестве файлов 100 


#define fname 10 //// адрес хранения номера текущего файла в еепром и2с

#define tfile 20 ///  Тип файлов  ячейка указатель кол ва файлов

/*#define f1m30  1 // 1файл 30000яч
#define f2m15  2 // 2 файла 15000
#define f5m06  5 // 5 файлов 6000
#define f10m03 10 // 10 файлов 3000
#define f20m01 20 // 20 файлов 1500
#define f50m06 50 // 50 файлов 600
#define f100m3 100 // 100 файлов 300*/

 //// для отображения и длинны файла
 
#define v1m30  20000 // 1файл 30000яч

/*#define v2m15  15000 // 2 файла 15000
#define v5m06  6000 // 5 файлов 6000
#define v10m03 3000 // 10 файлов 3000
#define v20m01 1500 // 20 файлов 1500
#define v50m06 600 // 50 файлов 600
#define v100m3 300 // 100 файлов 300*/

#define blockSIZE 400 /// Длинна блока для передачи в ПК - число строк




//// CLASSMODE //// Символ ASCII указывающий на режим работы и его состояние для записи в новый тип памяти 20000 яч ///

#define CMCLR 'c'    //// Ячейка пуста
#define CMIZMER 'I'  /// Измерение
#define CMSCANR 'S'  /// Сканирование
#define CMNONIU 'N'  /// НОНИУС
#define CMDIFFP 'D'  /// ДИФФЕРЕНЦИАЛЬНЫЙ +
#define CMDIFFM 'M'  /// ДИФФЕРЕНЦ -
#define CMRAZBR 'R'  /// Разбраковка в диапазоне 
#define CMRAZBL 'L'  /// Разбраковка - значение ниже нижнего порога  НП+
#define CMRAZBH 'H'  /// Разбраковка - Значен выше верхнего порога  ВП+



void SendUT(void);
void Send_NARU(void);
void RWN(void); //// Запись номера прибора
void SENDUFORG(void);
//void SENDUFILE(void);
void SCRCL(void);/// CR CL
void LBS(unsigned int num); /// 
void LBSX(unsigned long num);
void SEND_ST(unsigned char); /// Передача Состояния
void SEND_VOLT(unsigned int val); /// Передача напряжениния питания
void wrnar(unsigned long nar);
unsigned long TNARAB(void);

void CLRMEMALL(void); /// Очистка всей памяти 
void SFM(void); /// Выбор файла
void FCLR(void);/// Очистка файла
void MF(void); /// Меню форматирования
unsigned char WR_FILE (unsigned long val);/// Запись в ячейку измерения

void RFILE(void); /// просмотр файла
void FORMAT(unsigned char tf); 
unsigned char filetype(void);  /// прочитать ТИП файлов
void wfiletype(unsigned char i);  ///Записать Тип файлов 

void WR_SNUM(unsigned char a ,unsigned char b ,unsigned char c , unsigned char d);
unsigned int rfd(unsigned char mp,unsigned char tf);
void wfilename(unsigned char i);
unsigned char filename(void);
void vf_disp(unsigned int val, unsigned char mf,unsigned int mp,unsigned char tf);  /// отобразить на дисплее ячейку файла.

void initmem(void);
unsigned long corrector (unsigned long vals,unsigned char dach);

unsigned long cord1 (unsigned long val);
unsigned long cord2 (unsigned long val);
unsigned long cord3 (unsigned long val);
unsigned long cord4 (unsigned long val);
unsigned long cord5 (unsigned long val);
unsigned long cord6 (unsigned long val);
unsigned long cord7 (unsigned long val);
unsigned long cord8 (unsigned long val);
unsigned long cord9 (unsigned long val);

unsigned long zav_num;

volatile unsigned int main_value; //long


unsigned long readWEE(unsigned int ADR);
unsigned char readEE(unsigned int ADR); // int

void MEMORY_MEN(unsigned char mode); //// Режим память


void clraEE(void);

void writeWEE(unsigned int ADR,unsigned long val); 
//void writeWEE(unsigned long val, unsigned int ADR);

//void writeWEE(unsigned char *, unsigned int, unsigned char,unsigned char,unsigned char);

void writeEE(unsigned int ADR, unsigned int val); 
void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_tx(unsigned char byte);

unsigned char i2c_rx(unsigned char last_byte);

unsigned char in_sda(void);
void sda_io(unsigned char io_c);
void scl_set(unsigned char set_c);
void sda_set(unsigned char set_c);

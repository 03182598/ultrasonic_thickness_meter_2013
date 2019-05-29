unsigned long timerab(void);
//void ctm(void); /// сброс счетчика
void RPM(void);/// Чтение параметров из еепром
void RPR(void);//// Параметры для режимов
void CONFR(void);
unsigned char AMPR (void); //// Узнать усиление
unsigned char SNUMWR(unsigned char i);
void read_caibrext(void);//// прочитать калибровку
unsigned int Read_Disp(void);
unsigned char TOTRS(unsigned char st);
void CLRTR(void); /// Обнуление наработки


unsigned char READ_CLASSM(void); //// Вернуть режим работы - состояние для памяти


void WR_CLASSM(unsigned char val); //// Записать состояние в режим работы для памяти


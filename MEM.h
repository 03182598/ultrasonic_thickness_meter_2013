//// ��������� ������� ������ 

/*efine ftype_1		30000 /// ���������� ����� ������ � ���� �����
#define ftype_2		15000
#define ftype_5		6000
#define ftype_10	3000
#define ftype_20	1500
#define ftype_50	600
#define ftype_100	300*/

#define memstart	500 /// ������ � 1� ������ 2��   �� ������ ������.  ������ ���� �����

#define pointstart 	300 /// ����� ������ ���������� ��������� ��������� ������� � ������  ��������� ������ 900 ��� ������������ ���������� ������ 100 


#define fname 10 //// ����� �������� ������ �������� ����� � ������ �2�

#define tfile 20 ///  ��� ������  ������ ��������� ��� �� ������

/*#define f1m30  1 // 1���� 30000��
#define f2m15  2 // 2 ����� 15000
#define f5m06  5 // 5 ������ 6000
#define f10m03 10 // 10 ������ 3000
#define f20m01 20 // 20 ������ 1500
#define f50m06 50 // 50 ������ 600
#define f100m3 100 // 100 ������ 300*/

 //// ��� ����������� � ������ �����
 
#define v1m30  20000 // 1���� 30000��

/*#define v2m15  15000 // 2 ����� 15000
#define v5m06  6000 // 5 ������ 6000
#define v10m03 3000 // 10 ������ 3000
#define v20m01 1500 // 20 ������ 1500
#define v50m06 600 // 50 ������ 600
#define v100m3 300 // 100 ������ 300*/

#define blockSIZE 400 /// ������ ����� ��� �������� � �� - ����� �����




//// CLASSMODE //// ������ ASCII ����������� �� ����� ������ � ��� ��������� ��� ������ � ����� ��� ������ 20000 �� ///

#define CMCLR 'c'    //// ������ �����
#define CMIZMER 'I'  /// ���������
#define CMSCANR 'S'  /// ������������
#define CMNONIU 'N'  /// ������
#define CMDIFFP 'D'  /// ���������������� +
#define CMDIFFM 'M'  /// ��������� -
#define CMRAZBR 'R'  /// ����������� � ��������� 
#define CMRAZBL 'L'  /// ����������� - �������� ���� ������� ������  ��+
#define CMRAZBH 'H'  /// ����������� - ������ ���� �������� ������  ��+



void SendUT(void);
void Send_NARU(void);
void RWN(void); //// ������ ������ �������
void SENDUFORG(void);
//void SENDUFILE(void);
void SCRCL(void);/// CR CL
void LBS(unsigned int num); /// 
void LBSX(unsigned long num);
void SEND_ST(unsigned char); /// �������� ���������
void SEND_VOLT(unsigned int val); /// �������� ������������ �������
void wrnar(unsigned long nar);
unsigned long TNARAB(void);

void CLRMEMALL(void); /// ������� ���� ������ 
void SFM(void); /// ����� �����
void FCLR(void);/// ������� �����
void MF(void); /// ���� ��������������
unsigned char WR_FILE (unsigned long val);/// ������ � ������ ���������

void RFILE(void); /// �������� �����
void FORMAT(unsigned char tf); 
unsigned char filetype(void);  /// ��������� ��� ������
void wfiletype(unsigned char i);  ///�������� ��� ������ 

void WR_SNUM(unsigned char a ,unsigned char b ,unsigned char c , unsigned char d);
unsigned int rfd(unsigned char mp,unsigned char tf);
void wfilename(unsigned char i);
unsigned char filename(void);
void vf_disp(unsigned int val, unsigned char mf,unsigned int mp,unsigned char tf);  /// ���������� �� ������� ������ �����.

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

void MEMORY_MEN(unsigned char mode); //// ����� ������


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

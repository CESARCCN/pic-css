#define ADXL345_WRITE   0XA6  
#define ADXL345_READ    0XA7
#define DEVID           0X00     
#define BW_RATE         0X2C   
#define POWER_CTL       0X2D 
#define DATA_FORMAT     0X31
#define DATA_XL         0X32
#define DATA_XH         0X33 
#define DATA_YL         0X34
#define DATA_YH         0X35
#define DATA_ZL         0X36
#define DATA_ZH         0X37

#define ODR3200         0X0F 
#define ODR1600         0X0E 
#define ODR800          0X0D 
#define ODR400          0X0C 
#define ODR200          0X0B 
#define ODR100          0X0A 
#define ODR50           0X09 
#define ODR25           0X08 
#define ODR12_5         0X07
#define ODR6_25         0X06
#define ODR3_13         0X05
#define ODR1_56         0X04
#define ODR0_78         0X03
#define ODR0_39         0X02
#define ODR0_20         0X01
#define ODR0_10         0X00
//POWER_CTL 
#define LINK            0X20   
#define NOLINK          0X00   
#define AUTO_SLEEP      0X10   
#define NOAUTO_SLEEP    0X00   
#define MEASURE_ON      0X08   
#define MEASURE_OFF     0X00   
#define SLEEP           0X04
#define NO_SLEEP        0X00   
#define WAKEUP8HZ 0X00  
#define WAKEUP4HZ 0X01      
#define WAKEUP2HZ 0X02   
#define WAKEUP1HZ 0X03   
/////////////////////////////   

#define R2G    0X00      
#define R4G    0X01   
#define R8G    0X02
#define R16G   0X03           
//funciones          
void adxl345_config();
int adxl345_id();  
float adxl345_dato_Zeje(char eje);  


                  

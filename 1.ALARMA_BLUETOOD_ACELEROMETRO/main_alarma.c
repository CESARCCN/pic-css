#include <main_alarma.h>   
#use i2c(Master,Fast,sda=PIN_C4,scl=PIN_C3,force_hw)  
#use RS232 (BAUD=9600, BITS=8, PARITY=N, XMIT=PIN_c6, RCV=PIN_C7)  //Comunicación Serie  
#include "ADXL345.c"
#include "i2c_Flex_LCD.c"
#bit bocina=0x08.0 //puerto D PIN 0
#bit luces=0x08.1 //puerto D PIN 1

                       
float ax,ay,az;        
int id;                
int8 temp;            
char clave;
void configuracion(void);
void iniciar_alarma(void); 
void test_alarma(void); 
void desactivar_alarma(void); 
                    
#INT_RDA
void dato_recibido_isr()
{                     
   clave=getc();               
   temp=1;         
   
}


void main()          
{                      
   configuracion();   
                     
                     
   //printf(lcd_putc,"\fProbando"); 
   //delay_ms(1000);
                    
   //leer el registro id         
                  
   adxl345_config(); 
   printf("***************************\n\r");
   printf("*****MENU ALARMA*****\n\r");
   printf("***************************\n\r");
   printf("TEST DE ALARMA PRESIONE 1:\n\r");
   printf("ACTIVAR ALARMA PRESIONE 2:\n\r");
   printf("DESACTIVAR ALARMA PRESIONE 3:\n\r");
   printf(lcd_putc,"\f**MENU ALARMA***"); 
   lcd_gotoxy(1,2);
   printf(lcd_putc,"1  2  3");
   delay_ms(1000);
                              
   while(1) 
   { 
                        
      if(temp)                  
      {                         
         switch (clave)
         {
            case '1':
            output_low(PIN_B0);
            lcd_gotoxy(1,1);           
            printf("1: Iniciando Test\n\r");  
            printf(lcd_putc,"\f1:IniciandoTest"); 
            test_alarma();
            delay_ms(300);
            temp=0;  
            break;      
                     
            case '2':
            output_low(PIN_B0);
            lcd_gotoxy(1,1);           
            printf("2: Iniciando Alarma\n\r");  
            printf(lcd_putc,"\f2:IniciandoAlarma"); 
            iniciar_alarma();
            delay_ms(300);
            temp=0;           
            break;
                         
            case '3':           
            output_high(PIN_B0); 
            lcd_gotoxy(1,2);          
            printf("3: Alarma Desactivada\n\r"); 
            printf(lcd_putc,"\f3:AlarmaDesactivada");
            delay_ms(300);
            temp=0;
            break;  
            
            default:                 
            lcd_gotoxy(1,2);           
            printf(lcd_putc,"no es una opcion");
            printf("no es una opcion\n\r");      
            delay_ms(1000);  
            temp=0; 
            reset_cpu();
            break;             
           
         } 
      }
  
   }      
  
}  
//////////configurar inicio/////////
void configuracion()//Función de configuración
        
{
   lcd_init(0x4E,16,2); 
   lcd_backlight_led(ON); //Enciende la luz de Fondo
   lcd_clear();              
   set_tris_d(0x00);  
   output_d(0x00);  
   output_low(PIN_B0);                                            //Establecemos a nivel bajo el bit RB0
   output_low(PIN_B1);                                            //Establecemos a nivel bajo el bit RB1
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL); 
  
   //return 0;             
}                    
/////////////////////////      
void iniciar_alarma()
{
   //preguntar clave  
   //inicia Set de giroscopio
   
   while(1)            
   { 
     ax=adxl345_dato_eje('x');       
     ay=adxl345_dato_eje('y'); 
     az=adxl345_dato_eje('z');          
                                  
     printf(lcd_putc,"\fx=%f y=%f\n",ax,ay);  //envia datos al lcd por i2c
     printf(lcd_putc,"z=%f",az); 
     delay_ms(100);                                           
     printf("x=%f y=%f z=%f \r\n",ax, ay, az);//envia datos por uart 
     delay_ms(100); 
   }                      
   //si se activa alarma
   //prende luces y bocina avisa por uart
   //solicita clave
   //pregunta si desactiva alarma 
   //
  
}     
void test_alarma()         
{ 
  //test de bateria                
  //test de giroscopio  
  id=adxl345_id();  
  printf(lcd_putc,"ID=%x",id);
  printf("***TEST DE ACELEROMETRO***\n\r");
  delay_ms(1000);
  printf("ID ADXL1345=%x\n\r",id);
  delay_ms(1000);          
  ax=adxl345_dato_eje('x');       
  ay=adxl345_dato_eje('y'); 
  az=adxl345_dato_eje('z');          
                               
  printf(lcd_putc,"\fx=%f y=%f\n",ax,ay);  //envia datos al lcd por i2c
  printf(lcd_putc,"z=%f",az); 
  delay_ms(100);                                           
  printf("x=%f y=%f z=%f \r\n",ax, ay, az);//envia datos por uart 
  delay_ms(100);  
   
  //test de bocinas  
  printf("***TEST DE SONIDO***\n\r"); 
  delay_ms(1000);
  for(int8 i=0;i<4;i++)
  {
      bocina=~bocina;                
      delay_ms(100);
      printf("bocina= %d \n\r",i); 
  }
       
  //test de luces  
  printf("***TEST DE LUCES***\n\r"); 
  delay_ms(1000);        
  for(int8 t=0;t<4;t++)
  {
      luces=~luces;                
      delay_ms(100);
      printf("luces= %d \n\r",t); 
  }  
  //fin de test  
  printf("***FIN DE TEST***\n\r"); 
  delay_ms(1000);

}                          
void desactivar_alarma()         
{                             
   //desactiva alarma
   //reinicia
}


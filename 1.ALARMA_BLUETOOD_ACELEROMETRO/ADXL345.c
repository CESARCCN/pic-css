#include "ADXL345.h"   

int adxl345_id()
{ 
   int id;
   i2c_start();    
   i2c_write(ADXL345_WRITE);//slave addr+/w   
   i2c_write(DEVID);      
   i2c_start();        
   i2c_write(ADXL345_READ);           
   id=i2c_read(0); //lee el dato y envia noack
   i2c_stop();     
   return id;  
}   
                     
void adxl345_config()
{  
   //configurar bw_rate
   i2c_start(); 
   i2c_write(ADXL345_WRITE);//slave addr+/w
   i2c_write(BW_RATE);                 
   i2c_write(ODR200);  
   i2c_stop();         
   //configurar el power_ctl
   i2c_start();
   i2c_write(ADXL345_WRITE);//slave addr+/w 
   i2c_write(POWER_CTL);                 
   i2c_write(MEASURE_ON|WAKEUP4HZ);   
   i2c_stop();       
   //configurar el data_format            
   i2c_start();              
   i2c_write(ADXL345_WRITE);//slave addr+/w 
   i2c_write(DATA_FORMAT);                 
   i2c_write(R2G);          
   i2c_stop();  
                     
}    

float adxl345_dato_eje(char eje)  
{        
                         
   signed int16 x,y,z;   
   int xl,xh,yl,yh,zl,zh; 
   float ax,ay,az;        
   i2c_start();              
   i2c_write(ADXL345_WRITE);//slave addr+/w 
   i2c_write(DATA_XL);
   i2c_start();    
   i2c_write(ADXL345_READ);
   xl=i2c_read(1);
   xh=i2c_read(1);     
   yl=i2c_read(1);        
   yh=i2c_read(1);
   zl=i2c_read(1);     
   zh=i2c_read(0);      
   i2c_stop(); 
   x=make16(xh,xl);     
   y=make16(yh,yl);  
   z=make16(zh,zl);  
      
   ax=x*0.00390625;    
   ay=y*0.00390625;
   az=z*0.00390625;  
    
    switch(eje)
    {        
      
      case 'x':   
         return ax; 
         break;
      case 'y':       
         return ay;     
         break;
      case 'z':  
         return az;
         break;
      
    }      
   

}

 

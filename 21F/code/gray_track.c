#include "headfile.h"

void gray_init()
{
	gpio_init(GPIO_A, Pin_11, IU);   // D1
	gpio_init(GPIO_B, Pin_13, IU);   // D2
	gpio_init(GPIO_B, Pin_4, IU);   // D3
	gpio_init(GPIO_B, Pin_15, IU);   // D4
	gpio_init(GPIO_A, Pin_8 , IU);   // D5
	gpio_init(GPIO_C, Pin_13, IU);   // D6
	gpio_init(GPIO_A, Pin_15, IU);   // D7
	gpio_init(GPIO_C, Pin_15, IU);   // D8
}

void track()                        //1234 5678
{
        if((D4 == 0)&&(D5 == 0))        //1110 0111
        {
            motor_target_set(525,525);      
        }
        else if((D4 == 0)&&(D5 != 0))   //1110 1111
        {
            motor_target_set(515,525);       
        }
        else if((D4 != 0)&&(D5 == 0))   //1111 0111
        {
            motor_target_set(525,515);       
        }
        else if((D3 != 0)&&(D4 == 0))   //1100 1111
        {
            motor_target_set(508,520);        
        }
        else if((D5 == 0)&&(D6 == 0))   //1111 0011
        {
            motor_target_set(520,500);        
        }
        else if((D3 == 0)&&(D4 != 0))   //1101 1111
        {
            motor_target_set(500,520);        
        }
        else if((D5 != 0)&&(D6 == 0))   //1111 1011
        {
            motor_target_set(520,500);        
        }
        else if((D2 == 0)&&(D3 == 0))   //1001 1111
        {
            motor_target_set(440,550);        
        }
        else if((D6 == 0)&&(D7 == 0))   //1111 1001
        {
            motor_target_set(550,440);        
        }
        else if((D2 == 0)&&(D3 != 0))   //1011 1111
        {
            motor_target_set(430,570);        
        }
        else if((D6 != 0)&&(D7 == 0))  //1111 1101
        {
            motor_target_set(570,430);         
        }
        else if((D1 == 0)&&(D2 == 0))   //0011 1111
        {
            motor_target_set(380,580);         
        }
        else if((D7 == 0)&&(D8 == 0))   //1111 1100
        {
            motor_target_set(600,330);        
        }
        else if((D1 == 0)&&(D2 != 0))   //0111 1111
        {
            motor_target_set(350,570);         
        }    
        else if((D7 !=0)&&(D8 == 0))    //1111 1110
        {
            motor_target_set(570,90);         
        }
        else                            //1111 1111
        {
            motor_target_set(525,525);        
        }
}

unsigned char digtal(unsigned char channel)//1-8	  获取X通道数字值
{
	u8 value = 0;
	switch(channel) 
	{
		case 1:  
			if(gpio_get(GPIO_A, Pin_11) == 1) value = 1;
			else value = 0;  
			break;  
		case 2: 
			if(gpio_get(GPIO_B, Pin_13) == 1) value = 1;
			else value = 0;  
			break;  
		case 3: 
			if(gpio_get(GPIO_B, Pin_4) == 1) value = 1;
			else value = 0;  
			break;   
		case 4:  
			if(gpio_get(GPIO_B, Pin_15) == 1) value = 1;
			else value = 0;  
			break;   
		case 5:
			if(gpio_get(GPIO_A, Pin_8) == 1) value = 1;
			else value = 0;  
			break;
		case 6:  
			if(gpio_get(GPIO_C, Pin_13) == 1) value = 1;
			else value = 0;  
			break;  
		case 7: 
			if(gpio_get(GPIO_A, Pin_15) == 1) value = 1;
			else value = 0;  
			break;  
 		case 8: 
 			if(gpio_get(GPIO_C, Pin_15) == 1) value = 1;
 			else value = 0;  
 			break;   
	}
	return value; 
}


#include "headfile.h"

void gray_init()
{
	gpio_init(GPIO_B, Pin_12, IU);   // D1
	gpio_init(GPIO_B, Pin_13, IU);   // D2
	gpio_init(GPIO_B, Pin_14, IU);   // D3
	gpio_init(GPIO_B, Pin_15, IU);   // D4
	gpio_init(GPIO_A, Pin_8 , IU);   // D5
	gpio_init(GPIO_C, Pin_13, IU);   // D6
	gpio_init(GPIO_C, Pin_14, IU);   // D7
	gpio_init(GPIO_C, Pin_15, IU);   // D8
}

void track()                        //1234 5678
{
        if((D4 == 0)&&(D5 == 0))        //1110 0111
        {
            motor_target_set(338,338);
        }
        else if((D4 == 0)&&(D5 != 0))   //1110 1111
        {
            motor_target_set(225,270);
        }
        else if((D4 != 0)&&(D5 == 0))   //1111 0111
        {
            motor_target_set(270,225);  
        }
        else if((D3 != 0)&&(D4 == 0))   //1100 1111
        {
            motor_target_set(203,293);
        }
        else if((D5 == 0)&&(D6 == 0))   //1111 0011
        {
            motor_target_set(293,203);
        }
        else if((D3 == 0)&&(D4 != 0))   //1101 1111
        {
            motor_target_set(203,293);
        }
        else if((D5 != 0)&&(D6 == 0))   //1111 1011
        {
<<<<<<< Updated upstream
            motor_target_set(293,203);
=======
            motor_target_set(293,183);
>>>>>>> Stashed changes
        }
        else if((D2 == 0)&&(D3 == 0))   //1001 1111
        {
            motor_target_set(180,338);
        }
        else if((D6 == 0)&&(D7 == 0))   //1111 1001
        {
<<<<<<< Updated upstream
            motor_target_set(338,180);
=======
            motor_target_set(338,80);
>>>>>>> Stashed changes
        }
        else if((D2 == 0)&&(D3 != 0))   //1011 1111
        {
            motor_target_set(150,338);
        }
        else if((D6 != 0)&&(D7 == 0))   //1111 1101
        {
<<<<<<< Updated upstream
            motor_target_set(338,180);
        }
        else if((D1 == 0)&&(D2 == 0))   //0011 1111
        {
            motor_target_set(50,450);
=======
            motor_target_set(338,0);
        }
        else if((D1 == 0)&&(D2 == 0))   //0011 1111
        {
            motor_target_set(0,450);
>>>>>>> Stashed changes
        }
        else if((D7 == 0)&&(D8 == 0))   //1111 1100
        {
            motor_target_set(450,90);
        }
        else if((D1 == 0)&&(D2 != 0))   //0111 1111
        {
<<<<<<< Updated upstream
            motor_target_set(-40,500);
=======
            motor_target_set(-60,520);
>>>>>>> Stashed changes
        }    
        else if((D7 !=0)&&(D8 == 0))    //1111 1110
        {
            motor_target_set(500,0);
        }
        else                            //1111 1111
        {
            motor_target_set(338,338);
        }
}

unsigned char digtal(unsigned char channel)//1-8	  获取X通道数字值
{
	u8 value = 0;
	switch(channel) 
	{
		case 1:  
			if(gpio_get(GPIO_B, Pin_12) == 1) value = 1;
			else value = 0;  
			break;  
		case 2: 
			if(gpio_get(GPIO_B, Pin_13) == 1) value = 1;
			else value = 0;  
			break;  
		case 3: 
			if(gpio_get(GPIO_B, Pin_14) == 1) value = 1;
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
			if(gpio_get(GPIO_C, Pin_14) == 1) value = 1;
			else value = 0;  
			break;  
 		case 8: 
 			if(gpio_get(GPIO_C, Pin_15) == 1) value = 1;
 			else value = 0;  
 			break;   
	}
	return value; 
}


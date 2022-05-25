#include "tm4c123gh6pm.h"
#include <stdint.h>
	
int main()
{
	unsigned char key ;
	
	Systick_Init();
	sw_init();
	SW1_interrupt_init();
  sw3_init();
  SW3_interrupt_init();
	keypad_init ();
	lcd_init();
	rgb_init ();
	Buzzer_init();
	lcd_4bits_cmd(0x1);
  lcd_4bits_cmd(0x80);
	
	delay_milli(100);
	
	while(1)
	{
		lcd_4bits_cmd(0x1);
		LCD_String("enter a choice");
	  lcd_4bits_cmd(0xc0);
	  LCD_String("to begin cooking");
		do
			{
				key = get_key();
			} while(key==0);
			
		delay_milli(100);
		switch (key)
		{
			 case 'A' :
			
        pop_corn();
				break;
			 
			 
			 case 'B' :
				 
				 beef();
			   break;
			 
			 
			 case 'C' :
				 
				 chicken();
			   break;
			 
			 
			 case 'D' :
				 
				 cooking_time();
			   break;
			 
			 
			 default :
				 lcd_4bits_cmd(0x1);
				 LCD_String("wrong input");
		   	 delay_milli(3000);
			   break;

		}
	}
}

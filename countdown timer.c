void LCD_String_countdown (int mm ,int m , int ss , int s)
{
	while(1)
	{
		GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R |= 0x0E; //turning on the array of leds
		lcd_4bits_cmd(0x1);
		LCD_String("      ");
	        lcd_4bits_data( mm + 48);
	        lcd_4bits_data( m + 48);
                lcd_4bits_data(':');
	        lcd_4bits_data( ss + 48);
	        lcd_4bits_data( s + 48);
			
		if(s>0)
		{	
		  s   -= 1 ;
		}
		else if(s==0 & ss > 0)
		{
			ss -= 1;
		  s   = 9 ;
		}
		else if(s==0 & ss==0 & m>0)
		{
			m -=1;
			ss=5;
			s=9;
		}
		else if(s==0 & ss==0 & m==0 & mm>0)
		{
			mm-=1;
			m=9;
			ss=5;
			s=9;
		}
		else if(s==0 & ss==0 & m==0 & mm==0)
		{
			Buzzer_Blink();
			GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R &=~ 0x0E; //turning off the array of leds
			return;
		}
		
		delay_milli(250); //_______________________________________250 only for testing, change to 1000 before submission		
	}
}

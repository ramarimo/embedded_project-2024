void beef()
{
	int total_time , m , ss , s;
	unsigned char key ;
	int sw1, sw2;

	lcd_4bits_cmd(0x1);
	LCD_String("      beef");
	delay_milli(1000);
	loop_beef: lcd_4bits_cmd(0x1);
	LCD_String("enter number of");
	lcd_4bits_cmd(0xc0);
	LCD_String("kilos(1~9) ");
	lcd_4bits_cmd(0x0f);
	
	do
	{
		key = get_key();
		delay_milli(100);
			
	} while(key==0 );
	
	if(48>key | key>58)
		{
			lcd_4bits_cmd(0x1);
			LCD_String("wrong input");
			lcd_4bits_cmd(0x0c);
		  delay_milli(2000);
			goto loop_beef;
		}
	else if(48<key & key<58)
		{
		lcd_4bits_data(key);
		lcd_4bits_cmd(0x0c);
		LCD_String("kilo");
		delay_milli(200);
			
			while(1)
	{
	
				sw1 = sw_input() & 0x10;
		    sw2 = sw_input() & 0x1;
	
		
		
		
		 if (sw1 ==0x0)
		{
			goto loop_beef;
		}
		else if(sw2 ==0x0)
		{
			total_time = 30 * (key - 48);
			m = total_time/60;
			ss = (total_time - m*60)/10;
			s=0;
			LCD_String_countdown(0,m,ss,s);
			return;
		}
			
		} 
	
	
}
	}

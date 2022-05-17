void beef() 
{
  int total time , m ,ss , s;
  unsigned char key;
  lcd_4bits_cmd(0x1);
  LCD_string("      beef");
  delay_milli(1000);
 lcd_4bits_cmd(0x1);
  LCD_String("enter number of");
  lcd_4bits_cmd(0xc0);
	LCD_String("kilos(1~9) ");
	lcd_4bits_cmd(0x0f);
	
	do
	{
		key = get_key();
		delay_milli(100);
		if(48<key<58)
		{
		lcd_4bits_data(key);
		lcd_4bits_cmd(0x0c);
		LCD_String("kilo");
		delay_milli(2000);
		} 
		else
		{
			lcd_4bits_cmd(0x1);
			LCD_String("wrong input");
		  delay_milli(3000);
			beef();
			return;
		}
			
	} while(key==0);
	total_time = 30 * (key - 48);
	m = total_time/60;
	ss = (total_time - m*60)/10;
	s=0;
	LCD_String_countdown(0,m,ss,s);
	
}
  

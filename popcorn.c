
void pop_corn ()
{
	
	lcd_4bits_cmd(0x1);		
	LCD_String("    Pop corn");
	delay_milli(3000);
	
	lcd_4bits_cmd(0x1);
	
	LCD_String_countdown(0,1,0,0);
	
}

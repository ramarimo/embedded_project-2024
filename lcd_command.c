void lcd_write4bits (unsigned char data , unsigned char control)
{
	data     &=0xf0;
	control  &=0x0f;
	GPIO_PORTB_DATA_R = data|control;
	GPIO_PORTB_DATA_R = data|control| 4;
	delay_micro(0);
	GPIO_PORTB_DATA_R  = data;
}
void lcd_4bits_cmd (unsigned char command)
{
	lcd_write4bits(command & 0xf0 , 0);
	lcd_write4bits(command << 4   , 0);
	if (command < 4)
	
		delay_milli(2);
		else
		delay_micro(40);
	}
void lcd_4bits_data (unsigned char data) // print 1 char
{
	lcd_write4bits(data & 0xf0 , 1);
	lcd_write4bits(data << 4   , 1);
	delay_micro(40);
}

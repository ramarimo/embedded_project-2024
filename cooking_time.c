void cooking_time ()
{
	int key1 ,key2, key3 , key4;
	int total_time ,sw , sw1 , sw2;
	lcd_4bits_cmd(0x1);
	LCD_String("cooking time?");
	lcd_4bits_cmd(0xc0);
	LCD_String("max(30:00) ");
	LCD_String("00:0 ");
	
	lcd_4bits_cmd(0xcf);
	lcd_4bits_cmd(0x0f);
	delay_milli(500);
	while(1)
	{
		key1 = get_key();
		delay_milli(100);
		if(key1!=0)
		{
		lcd_4bits_cmd(0x1);
	  LCD_String("cooking time?");
	  lcd_4bits_cmd(0xc0);
	  LCD_String("max(30:00) ");
		LCD_String("00:0");
		lcd_4bits_data(key1);
	  lcd_4bits_cmd(0xcf);
		lcd_4bits_cmd(0x0f);
		delay_milli(250);
		break;
		} 
	} 
	
	delay_milli(200);
	
	
	
	while(1)
	{ 
		
		sw1 = sw_input() & 0x10;
		delay_milli(100);
		key2 = get_key();
		delay_milli(100);
		if(sw1==0x0)
		{
			lcd_4bits_cmd(0x1);
			LCD_String("00:0");
			lcd_4bits_data(key1);
			LCD_String("  press sw2");
	    		lcd_4bits_cmd(0xcf);
	
		  	delay_milli(100);
		  	lcd_4bits_cmd(0xc0);
			LCD_String("to start");
			lcd_4bits_cmd(0x0c);
			delay_milli(100);
			do
			{
				sw = sw_input();
				delay_milli(100);
				sw1 = sw & 0x10;
				sw2 = sw & 0x1;
			} while(sw==0x11);
			if(sw1 == 0)
				return;
			else if (sw2 ==0 )
			{
				LCD_String_countdown(0,0,0,key1 - 48);
				return;
				}
				
			
			
		
		}
			
		
		delay_milli(100);
		if(key2!=0)
		{
		lcd_4bits_cmd(0x1);
	  LCD_String("cooking time?");
	  lcd_4bits_cmd(0xc0);
	  LCD_String("max(30:00) ");
		LCD_String("00:");	
		lcd_4bits_data(key1);
		lcd_4bits_data(key2);
		lcd_4bits_cmd(0xcf);
		lcd_4bits_cmd(0x0f);
		delay_milli(250);  
		break;	
		} 
	} 
	
	delay_milli(250);
	
	while(1)
	{
		sw1 = sw_input() & 0x10;
		
		key3 = get_key();
		if(sw1==0x0)
		{
			lcd_4bits_cmd(0x1);
			
			LCD_String("00:");
		lcd_4bits_data(key1);
			lcd_4bits_data(key2);
			LCD_String("  press sw2");
	  
		lcd_4bits_cmd(0x0f);
		delay_milli(100);
		lcd_4bits_cmd(0xc0);
			
			LCD_String("to start");
			lcd_4bits_cmd(0x0c);
			delay_milli(100);
			
			do
			{
				sw = sw_input();
				delay_milli(100);
				sw1 = sw & 0x10;
				sw2 = sw & 0x1;
			} while(sw==0x11);
			if(sw1 == 0)
				return;
			else if (sw2 ==0 )
			{
				LCD_String_countdown(0,0,key1 - 48 , key2 - 48);
				return;
				}
			
			

		}
		
		delay_milli(100);
		if(key3!=0)
		{
		lcd_4bits_cmd(0x1);
	  LCD_String("cooking time?");
	  lcd_4bits_cmd(0xc0);
	  LCD_String("max(30:00) ");
		LCD_String("0");	
		lcd_4bits_data(key1);
		LCD_String(":");	
		lcd_4bits_data(key2);	
		lcd_4bits_data(key3);
		lcd_4bits_cmd(0xcf);
		lcd_4bits_cmd(0x0f);
		delay_milli(250);
			break;
		} 
	} 
	
	delay_milli(200);
	
	
	while(1)
	{
		sw1 = sw_input() & 0x10;
		key4 = get_key();
		
		if(sw1==0x0)
		{
			delay_milli(200);
			lcd_4bits_cmd(0x1);
			
			LCD_String("0");
		lcd_4bits_data(key1);
			LCD_String(":");
			lcd_4bits_data(key2);
			lcd_4bits_data(key3);
			
			LCD_String("  press sw2");
	 
		lcd_4bits_cmd(0x0f);
		delay_milli(100);
		lcd_4bits_cmd(0xc0);
			
			
			
			
			LCD_String("to start");
			lcd_4bits_cmd(0x0c);
			
			delay_milli(100);
			
			do
			{
				sw = sw_input();
				delay_milli(100);
				sw1 = sw & 0x10;
				sw2 = sw & 0x1;
			} while(sw==0x11);
			if(sw1 == 0)
				return;
			else if (sw2 ==0 )
			{
				LCD_String_countdown(0,key1 - 48 , key2 - 48,key3 - 48 );
				return;
				}
			

		}
		
		delay_milli(100);
		if(key4!=0)
		{
			lcd_4bits_cmd(0x1);
	    LCD_String("cooking time?");
	    lcd_4bits_cmd(0xc0);
	    LCD_String("max(30:00) ");
			lcd_4bits_data(key1);	
			lcd_4bits_data(key2);
			LCD_String(":");
			lcd_4bits_data(key3);
			lcd_4bits_data(key4);
			delay_milli(1000);
			
			total_time = (key1-48)*10*60 + (key2-48)*60 + (key3-48)*10 + (key4-48) ;
			if(total_time>(30*60) | key1<48 | key1>57 | key2<48 | key2>57 | key3<48 | key3>57 | key4<48 | key4>57 )
			{
				lcd_4bits_cmd(0x1);
				LCD_String("     ERROR");
				lcd_4bits_cmd(0xc0);
				LCD_String("max time 30:00");
				lcd_4bits_cmd(0x0c); ///////cursor blinking off
				delay_milli(3000);
				return;
			}
			else
			{
				lcd_4bits_cmd(0x1);
			
			
		lcd_4bits_data(key1);
			
			lcd_4bits_data(key2);
				LCD_String(":");
			lcd_4bits_data(key3);
				lcd_4bits_data(key4);
			
			LCD_String("  press sw2");
	 
		lcd_4bits_cmd(0x0f);
		delay_milli(100);
		lcd_4bits_cmd(0xc0);
			
			
			
			
			LCD_String("to start");
			lcd_4bits_cmd(0x0c);
			delay_milli(100);
			
			do
			{
				sw = sw_input();
				delay_milli(100);
				sw1 = sw & 0x10;
				sw2 = sw & 0x1;
			} while(sw==0x11);
			if(sw1 == 0)
				return;
			else if (sw2 ==0 )
			{
				LCD_String_countdown(key1 - 48 , key2 - 48, key3 - 48 , key4 - 48);
				return;
				}
			
				
			
				
				
		} 
	} 
	
	
			
			

	
	
}
	}

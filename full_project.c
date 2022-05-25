#include "tm4c123gh6pm.h"
#include <stdint.h>
 // key pad row      gpioe
 // key pad coloumn  gpioc

char timer_on=1;    //1 means timer works normally, 0 means stop the timer and return to ideal state
char helper=1;      //a variable used to fix a bug in gpioe & gpiof handlers


void Systick_Init (void)
{
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0xffffff;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x5;
}

void Systick_Wait (unsigned long delay)
{
	NVIC_ST_RELOAD_R = delay -1 ;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R&0x10000)==0){}
}

void delay_micro ( unsigned long delay)
{
	unsigned long i;
	for( i=0 ; i<delay ; i++)
	{
		Systick_Wait (16);
	}
}

void delay_milli ( unsigned long delay)
{
	unsigned long i;
	for( i=0 ; i<delay ; i++)
	{
		Systick_Wait (16000);   
	}
}


unsigned char sw_input (void)
{
	return GPIO_PORTF_DATA_R & 0x11;
}

void SW1_interrupt_init(void)
{
	__disable_irq();                //disable interrupts globaly
	
  GPIO_PORTF_IS_R &= ~ 0x10;
  GPIO_PORTF_IEV_R &= ~ 0x10;
	GPIO_PORTF_IBE_R &= ~ 0x10;
	GPIO_PORTF_ICR_R &= ~ 0x10;
	GPIO_PORTF_IM_R |= 0x10;
  NVIC_PRI7_R= (NVIC_PRI7_R &0xFF00FFFF)| 0x00A00000;   //priority 5
	NVIC_EN0_R |=(1 << 30);
}
void GPIOF_Handler()
{
	int sw =0x11 ;
	delay_milli(200);
	while(sw==0x11)
	{
		GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x0E;  //togling the leds until sw1 or sw2 is pressed
		delay_milli(100);
		sw = sw_input();
		
		if(helper==0)
			break;
		
		if(sw==0x10)
		{
			timer_on=1;
		}
		else if(sw==0x01)
		{
			timer_on=0;
			delay_milli(200);
		}
		
	}
	GPIO_PORTF_ICR_R |= 0x10;
}
void Buzzer_init()
{
	//buzzer connceted to pinE5
	SYSCTL_RCGCGPIO_R |= 0x10;
  while((SYSCTL_PRGPIO_R &= 0x10)==0);
	GPIO_PORTE_CR_R |= 0x20;
	GPIO_PORTE_AFSEL_R &= ~0x20;
	GPIO_PORTE_PCTL_R &=~ 0xf00000;
	GPIO_PORTE_AMSEL_R &=~0x20;
	GPIO_PORTE_DEN_R |= 0x20;
	GPIO_PORTE_DIR_R |= 0x20;
}
void blink()
{
		    
GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R |= 0x0E;
delay_milli(500);
	GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R &=~ 0x0E;
				
				
	}

void Buzzer()
{
	
GPIO_PORTE_DATA_R |= 0x20;    //buzzer on 
blink();
GPIO_PORTE_DATA_R &= ~0x20;   //buzzer off
	  
 }

void Buzzer_Blink()
{ 
char y;
							
for(y=0;y<3;y++)
{
Buzzer();
delay_milli(500);
}
								
	}
void rgb_init ()
{
	SYSCTL_RCGCGPIO_R |= 0x20;
  while((SYSCTL_PRGPIO_R &= 0x20)==0);
	GPIO_PORTF_CR_R |= 0xe;
	GPIO_PORTF_AFSEL_R &= ~0xe;
	GPIO_PORTF_PCTL_R &=~ 0xfff0;
	GPIO_PORTF_AMSEL_R &=~0xe;
	GPIO_PORTF_DEN_R |= 0xe;
	GPIO_PORTF_DIR_R |= 0xe;
}
void sw_init()
{
	SYSCTL_RCGCGPIO_R |= 0x20;
  while((SYSCTL_PRGPIO_R &= 0x20)==0);
	GPIO_PORTF_LOCK_R = 0x4C4F434B ;
	GPIO_PORTF_CR_R |= 0x11 ;
	GPIO_PORTF_AFSEL_R &= ~0x11;
	GPIO_PORTF_PCTL_R &= ~0xf000f;
	GPIO_PORTF_AMSEL_R &= ~0x11;
	GPIO_PORTF_DEN_R |= 0x11;
	GPIO_PORTF_DIR_R &= ~0x11;
	GPIO_PORTF_PUR_R |= 0x11;
}


void sw3_init()
{
	//sw3 connceted to pinE4
	SYSCTL_RCGCGPIO_R |= 0x10;
  while((SYSCTL_PRGPIO_R &= 0x10)==0);
	GPIO_PORTE_CR_R |= 0x10;
	GPIO_PORTE_AFSEL_R &= ~0x10;
	GPIO_PORTE_PCTL_R &=~ 0xf0000;
	GPIO_PORTE_AMSEL_R &=~0x10;
	GPIO_PORTE_DEN_R |= 0x10;
	GPIO_PORTE_DIR_R &= ~0x10;
}
int sw3_input ()
{
	 return GPIO_PORTE_DATA_R & 0x10;
}
void SW3_interrupt_init(void){
__disable_irq();                                //disable interrupts globaly
GPIO_PORTE_IS_R &= ~ 0x10;
GPIO_PORTE_IEV_R &= ~ 0x10;
GPIO_PORTE_IBE_R &= ~ 0x10;
GPIO_PORTE_ICR_R &= ~ 0x10;
GPIO_PORTE_IM_R |= 0x10;
NVIC_PRI1_R= (NVIC_PRI1_R &0xFFFFFF00)| 0x20;    //priority 1
NVIC_EN0_R |=(1 << 4);

}
void GPIOE_Handler()
{
	int sw , sw3 ;
	__disable_irq();       //disable the interrupts globaly to avoid going to GPIOF_Handler when pressing sw1
	delay_milli(200);
	while(1)
	{
		
		GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R ^ 0x0E;   //toggling the leds until sw1 or sw2 is pressed
		sw = sw_input();
		sw3 = sw3_input();
		delay_milli(100);
		
		if(helper==0)     //handling a bug  
			break;
		
		if(sw3==0x00)     //do nothing until the door is closed
		{
		}
		
		else if(sw==0x10)
		{
			timer_on=1;
			break;
			
		}
		else if(sw==0x01)
		{
			
			timer_on=0;
			delay_milli(200);
			break;
			
		}
		
	}
	GPIO_PORTE_ICR_R |= 0x10;
}
void keypad_init ()
{
	SYSCTL_RCGCGPIO_R |= 0x4;
  while((SYSCTL_PRGPIO_R &= 0x4)==0) ; //port c
	
	SYSCTL_RCGCGPIO_R |= 0x10;
  while((SYSCTL_PRGPIO_R &= 0x10)==0) ; //porte
	
	GPIO_PORTE_DIR_R |=0xf;
	GPIO_PORTE_DEN_R |=0xf;
	GPIO_PORTE_ODR_R |=0XF;
	
	GPIO_PORTC_DIR_R &=~ 0xf0;
	GPIO_PORTC_DEN_R |= 0xf0;
	GPIO_PORTC_PUR_R |= 0xf0;
	
}
unsigned char get_key ()
{
	const unsigned char keypad [4][4]={ {'1','2','3','A'},
																			{'4','5','6','B'},
																			{'7','8','9','C'},
																			{'*','0','#','D'} };
	uint8_t row , col ;
	GPIO_PORTE_DATA_R &=~ 0xf;
	col = GPIO_PORTC_DATA_R & 0xf0;
	if (col == 0xf0)
		return 0 ;
	while(1)
	{
		row=0 ;
	  GPIO_PORTE_DATA_R = 0xe;
		delay_micro(10);
		col = GPIO_PORTC_DATA_R &0xf0;
		if(col != 0xf0)
			break;
		
		row=1 ;
	  GPIO_PORTE_DATA_R = 0xd;
		delay_micro(10);
		col = GPIO_PORTC_DATA_R &0xf0;
		if(col != 0xf0)
			break;
		
		row=2 ;
	  GPIO_PORTE_DATA_R = 0xb;
		delay_micro(10);
		col = GPIO_PORTC_DATA_R &0xf0;
		
		if(col != 0xf0)
			break;
		
		row=3 ;
	  GPIO_PORTE_DATA_R = 0x7;
		delay_micro(10);
		col = GPIO_PORTC_DATA_R &0xf0;
		if(col != 0xf0)
			break;
		
		return 0;
	}
	if(col == 0xe0)
		return keypad[row][0];
	
	if(col == 0x0d0)
		return keypad[row][1];
	
	if(col == 0x0b0)
		return keypad[row][2];
	
	if(col == 0x070)
		return keypad[row][3];
	return 0 ;
}
																								

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
	


void lcd_init ()
{
	SYSCTL_RCGCGPIO_R |= 0x2;
  while((SYSCTL_PRGPIO_R &= 0x2)==0) ;
	GPIO_PORTB_DIR_R |= 0xff;
	GPIO_PORTB_DEN_R |=0xff;
	GPIO_PORTB_PCTL_R &=~ 0xffffffff;
	GPIO_PORTB_LOCK_R=0x4C4F434B;
	
	lcd_4bits_cmd(0x28);
	lcd_4bits_cmd(0x06); //Increment cursor (shift cursor to right) automatically
	lcd_4bits_cmd(0x01); //Clear display screen
	lcd_4bits_cmd(0x0c); //Display on, cursor off ( 0x0f if you want the cursor to blink)
  
}

void LCD_String (char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)  /* Send each char of string till the NULL */
	{
		if (i==16)
		{
			lcd_4bits_cmd(0xc0);
		}
		lcd_4bits_data(str[i]);  /* Call LCD data write */
		
		}
			
}
void LCD_String_countdown (int mm ,int m , int ss , int s)
{
    timer_on=1;
    helper=0;
    __enable_irq();

    while(timer_on==1)
    {
        helper=1;
        __enable_irq();
        GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R |= 0x0E;
        lcd_4bits_cmd(0x1);
      LCD_String("      ");
        lcd_4bits_data( mm + 48);
      lcd_4bits_data( m + 48);
        lcd_4bits_data(':');
      lcd_4bits_data( ss + 48);
      lcd_4bits_data( s + 48);
        delay_milli(1000); 

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
            __disable_irq();
            GPIO_PORTF_DATA_R &=~ 0x0E;
            return;
        }

    }
    __disable_irq();
    GPIO_PORTF_DATA_R &=~ 0x0E;
    return;
}
 
void pop_corn ()
{
    int sw1, sw2;


    lcd_4bits_cmd(0x1);        
    LCD_String("    Pop corn");

    while(1)
    {
        sw1 = sw_input() & 0x10;
        sw2 = sw_input() & 0x1;
        delay_milli(100);

        if(sw1==0x0 )
            {
                return;
            }
        else if (sw2 ==0 )
            {
                lcd_4bits_cmd(0x0c); ///////cursor blinking off
                lcd_4bits_cmd(0x1);
          LCD_String_countdown(0,1,0,0);
                return;
            }

        }

}
void pop_corn ()
{
	int sw1, sw2;
	
	
	lcd_4bits_cmd(0x1);		
	LCD_String("    Pop corn");
	
	while(1)
	{
		sw1 = sw_input() & 0x10;
		sw2 = sw_input() & 0x1;
		delay_milli(100);
		
		if(sw1==0x0 )
			{
				return;
			}
		else if (sw2 ==0 )
			{
				lcd_4bits_cmd(0x0c); //cursor blinking off
				lcd_4bits_cmd(0x1);
	      LCD_String_countdown(0,1,0,0);
				return;
			}
			
		}
	
}
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
void chicken()
{
	int total_time , m , ss , s;
	unsigned char key ;
	int sw1, sw2;
	
	lcd_4bits_cmd(0x1);
	LCD_String("    chicken");
	delay_milli(1000);
	loop_chicken: lcd_4bits_cmd(0x1);
	LCD_String("enter number of");
	lcd_4bits_cmd(0xc0);
	LCD_String("kilos(1~9) ");
	lcd_4bits_cmd(0x0f);
	

do
	{
		key = get_key();
		delay_milli(100);
			
	} while(key==0);

	if(48>key | key>58)
		{
			lcd_4bits_cmd(0x1);
			LCD_String("wrong input");
			lcd_4bits_cmd(0x0c);
		  delay_milli(2000);
			goto loop_chicken;
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
			goto loop_chicken;
		}
		else if(sw2 ==0x0)
		{
			total_time = 12 * (key - 48);
			m  = total_time/60;
			ss = (total_time - m*60)/10;
			s  = (total_time - m*60) - ((total_time - m*60)/10)*10 ;                      
			LCD_String_countdown(0,m,ss,s);
			return;
			}
		}
	}
}
void cooking_time ()
{
	int key1 ,key2, key3 , key4;
	int total_time ,sw , sw1 , sw2;
	lcd_4bits_cmd(0x1);
	LCD_String("cooking time?");
	lcd_4bits_cmd(0xc0);
	LCD_String("max(30:00) ");
	LCD_String("  :  ");
	
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
		LCD_String("  : ");
		lcd_4bits_data(key1);
	  lcd_4bits_cmd(0xcf);
		lcd_4bits_cmd(0x0f);
		delay_milli(250);
		break;
		} 
	} 
	
	delay_milli(100);
	
	while(1)
	{ 
		
		sw1 = sw_input() & 0x10;
		sw2 = sw_input() & 0x1;
		key2 = get_key();
		if(sw1==0x0 )
		{
			cooking_time ();
			return;
		}
		else if(key1<48 | key1>57)
		{
			lcd_4bits_cmd(0x1);
			LCD_String("     ERROR");
			lcd_4bits_cmd(0xc0);
			lcd_4bits_cmd(0x0c); //cursor blinking off
			delay_milli(3000);
			cooking_time();
			return;
		}
		else if (sw2 ==0 )
			{
				lcd_4bits_cmd(0x0c); //cursor blinking off
				LCD_String_countdown(0,0,0,key1 - 48);
				return;
			}
		
		delay_milli(100);
		if(key2!=0)
		{
			lcd_4bits_cmd(0x1);
			LCD_String("cooking time?");
			lcd_4bits_cmd(0xc0);
			LCD_String("max(30:00) ");
			LCD_String("  :");	
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
		sw2 = sw_input() & 0x1;
		key3 = get_key();
		if(sw1==0x0 )
		{
				cooking_time();
				return;
		}
		else if( key2<48 | key2>57)
		{
			  lcd_4bits_cmd(0x1);
				LCD_String("     ERROR");
				lcd_4bits_cmd(0xc0);
				lcd_4bits_cmd(0x0c); //cursor blinking off
				delay_milli(3000);
			  cooking_time();
				return;
		}
		else if (sw2 ==0 )
			{
				lcd_4bits_cmd(0x0c); //cursor blinking off
				LCD_String_countdown(0,0,key1 - 48 , key2 - 48);
				return;
				}
		else if(key3!=0)
		{
			lcd_4bits_cmd(0x1);
			LCD_String("cooking time?");
			lcd_4bits_cmd(0xc0);
			LCD_String("max(30:00) ");
			LCD_String(" ");	
			lcd_4bits_data(key1);
			LCD_String(":");	
			lcd_4bits_data(key2);	
			lcd_4bits_data(key3);
			lcd_4bits_cmd(0xcf);
			lcd_4bits_cmd(0x0f);
			delay_milli(100);
			break;
		} 
	} 
	
	delay_milli(250);
	
	
	while(1)
	{
		sw1 = sw_input() & 0x10;
		sw2 = sw_input() & 0x1;
		key4 = get_key();
		
		if(sw1==0x0  )
		{
				cooking_time();
				return;
		}
		else if( key3<48 | key3>57)
		{
			lcd_4bits_cmd(0x1);
			LCD_String("     ERROR");
			lcd_4bits_cmd(0xc0);
			lcd_4bits_cmd(0x0c); //cursor blinking off
			delay_milli(3000);
			cooking_time();
			return;
		}
		else if (sw2 ==0 )
		{
				lcd_4bits_cmd(0x0c); //cursor blinking off
				LCD_String_countdown(0,key1 - 48 , key2 - 48,key3 - 48 );
				return;
		}
		
		else if(key4!=0)
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
			break;
		}
	}
		delay_milli(200);
		while(1)
		{
			sw1 = sw_input() & 0x10;
		  sw2 = sw_input() & 0x1;
			total_time = (key1-48)*10*60 + (key2-48)*60 + (key3-48)*10 + (key4-48) ;
			delay_milli(100);
			if ( key4<48 | key4>57)
				{
					lcd_4bits_cmd(0x1);
				LCD_String("     ERROR");
				lcd_4bits_cmd(0xc0);
				lcd_4bits_cmd(0x0c); //cursor blinking off
				delay_milli(3000);
				cooking_time();
				return;
				}
			else if(total_time>(30*60)  )
			{
				lcd_4bits_cmd(0x1);
				LCD_String("     ERROR");
				lcd_4bits_cmd(0xc0);
				LCD_String("max time 30:00");
				lcd_4bits_cmd(0x0c); //cursor blinking off
				delay_milli(3000);
				cooking_time();
				return;
			}
				else if(sw1==0x0  )
				{
					cooking_time();
					return;
				}
				 
				
				else if (sw2 ==0 )
		{
				lcd_4bits_cmd(0x0c); //cursor blinking off
				LCD_String_countdown(key1 - 48 , key2 - 48,key3 - 48 , key4 - 48 );
				
				return;
			}	
		} 
	} 
	
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

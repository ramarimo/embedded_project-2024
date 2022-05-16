#include "tm4c123gh6pm.h"
#define NVIC_ST_CURRENT_R (*((volatile unsigned long *)0xE000E018))
#define NVIC_ST_CTRL_R (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R (*((volatile unsigned long *)0xE000E014))
#include "Io.h"
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
		    
				GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R ^ 0x0E;
				delay_milli(500);
				GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R ^ 0x0E;
				
				
	}

void Buzzer()
	{
	
		GPIO_PORTE_DATA_R |= 0x20;
	  blink();
	  GPIO_PORTE_DATA_R &= ~0x20;
	  
 }
void Buzzer_Blink()
	{ 
							int y;
							
									for(y=0;y<3;y++)
									{
										Buzzer();
										delay_milli(500);
									}
								
	}

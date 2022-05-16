#include "tm4c123gh6pm.h"
#define NVIC_ST_CURRENT_R (*((volatile unsigned long *)0xE000E018))
#define NVIC_ST_CTRL_R (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R (*((volatile unsigned long *)0xE000E014))
#include "Io.h"
/*void SystemInit(void){
SYSCTL_RCGCGPIO_R |=0x20;
while ((SYSCTL_PRGPIO_R & 0x20) == 0);
GPIO_PORTF_LOCK_R= 0x4C4F434B;
GPIO_PORTF_CR_R|=0x0E;
GPIO_PORTF_AFSEL_R &= ~0x0E;
GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
GPIO_PORTF_AMSEL_R&=~0x0E;
GPIO_PORTF_DIR_R|=0x0E;
GPIO_PORTF_DEN_R|=0x0E;
GPIO_PORTF_DATA_R |= 0x0E;
}*/

void SystemInit(void){
SYSCTL_RCGCGPIO_R |=0x20;
while ((SYSCTL_PRGPIO_R & 0x20) == 0);
GPIO_PORTE_LOCK_R= 0x4C4F434B;
GPIO_PORTE_CR_R|=0x08;
GPIO_PORTE_AFSEL_R &= ~0x08;
GPIO_PORTE_PCTL_R &= ~0x08;
GPIO_PORTE_AMSEL_R&=~0x08;
GPIO_PORTE_DIR_R|=0x08;
GPIO_PORTE_DEN_R|=0x08;
GPIO_PORTE_DATA_R |= 0x08;
}
void SysTick_Init(void){
NVIC_ST_CTRL_R = 0;
NVIC_ST_RELOAD_R = 0x00FFFFFF;
NVIC_ST_CTRL_R = 0x00000005;
}
void SysTick_wait(unsigned long delay){
NVIC_ST_RELOAD_R = delay-1;
NVIC_ST_CURRENT_R=0;
while ((NVIC_ST_CTRL_R &0x00010000)==0){}
}
void delay(unsigned long time ){//tnady 3la el time delay 3s
int i;
for(i =0 ; i<time ;i++){
SysTick_wait(16000); // 1msec
}
}
void blink(){while(1){
GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R ^ 0x0E;
delay(1000);// time =1sec
GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R ^ 0x0E;
delay(1000);
break;
}
}

void Buzzer(){
	
		GPIO_PORTE_DATA_R |= 0x08;
	blink();
	//delay1sec
	GPIO_PORTE_DATA_R &= ~0x08;
	
		
}

void timer(){ 
int y;
	int min , sec;
if( sec==0 && min ==0){
	for(y=0;y<3;y++){
	Buzzer();
	delay(1000);
	

}
}
}


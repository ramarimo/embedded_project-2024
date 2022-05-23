void SW1_interrupt_init(void){
//SYSCTL_RCGCGPIO_R |=0x20;
//while ((SYSCTL_PRGPIO_R & 0x20) == 0);
//GPIO_PORTF_LOCK_R= 0x4C4F434B;
//GPIO_PORTF_CR_R|=0x11;
//GPIO_PORTF_AFSEL_R &= ~0x11;
//GPIO_PORTF_PCTL_R &= ~0x000F000F;
//GPIO_PORTF_AMSEL_R&=~0x11;
//GPIO_PORTF_DIR_R|=0x11;
//GPIO_PORTF_DEN_R|=0x11;
//GPIO_PORTF_PUR_R|=0x11;
//GPIO_PORTF_DATA_R |= 0x11;
	
	__disable_irq();
	
GPIO_PORTF_IS_R &= ~ 0x10;
GPIO_PORTF_IEV_R &= ~ 0x10;
	GPIO_PORTF_IBE_R &= ~ 0x10;
	GPIO_PORTF_ICR_R &= ~ 0x10;
	GPIO_PORTF_IM_R |= 0x10;
NVIC_PRI7_R= (NVIC_PRI7_R &0xFF00FFFF)| 0x00A00000;   //priority 5 
	NVIC_EN0_R |=(1 << 30);
//EnableInterrupts();
//__enable_irq();

}

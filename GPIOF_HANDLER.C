
void GPIOF_Handler()
{
	int sw =0x11 ;
	//GPIO_PORTF_ICR_R |= 0x10;
	
	delay_milli(200);
	while(sw==0x11)
	{
		GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R ^ 0x0E;
		delay_milli(100);
		sw = sw_input();
		
		
		if(sw==0x10)
		{
			k=1;
			
			
		}
		if(sw==0x01)
		{
			
			k=0;
			GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R | 0x0E;
			delay_milli(200);
		}
		
		
		
		
	}
	GPIO_PORTF_ICR_R |= 0x10;
}

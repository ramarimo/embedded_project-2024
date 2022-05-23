void GPIOE_Handler()
{
	int sw =0x11 , sw3 ;
	//GPIO_PORTE_ICR_R |= 0x10;
	__disable_irq();
	delay_milli(200);
	while(1)
	{
		
		GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R ^ 0x0E;
		
		sw = sw_input();
		sw3 = sw3_input();
		delay_milli(100);
		
		if(sw3==0x00)
		{
		}
		
		else if(sw==0x10)
		{
			k=1;
			
			break;
			
			
		}
		else if(sw==0x01)
		{
			
			k=0;
			
			//GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R | 0x0E;
			//delay_milli(200);
			break;
		}
		
		
		
		
	}
	GPIO_PORTE_ICR_R |= 0x10;
}

void switches(void) {
	
		  
			//char external_button=SW3();
			if ((SW2 == 0x0)&&(external_button==1)) {         //;{                //sw2 must be pressed and the door must be closed
				
					GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R&0x11) | 0x11;
			    OVEN_ON();                                                          //start cooking>>timer starts counting
				  while((GPIO_PORTF_DATA_R&0x10) !=0x00);                             //&&(external_button==1));the oven is cooking as long as the condition satisfied
				GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R&0x11) | 0x11;
				  OVEN_PAUSE();		                                                     //oven_pause       //if the door is opened pause the cooking
          while((GPIO_PORTF_DATA_R&0x11) !=0x00);				 
          button = SW1_2();                                                   //keep remaining time//clear sw1;
			  	while(button ==0x11);                                               //wait until another button is pressed
                                  
			  	   if (button==0x10){                                               //when sw2 is pressed resume cooking as long as the door is closed
					                                                                    //while(external_button==1){
					     	OVEN_ON();							                                      //RESUME
						    
				                     	 }
					                                                  
					  else if (button==0x01){                          // if sw1 is pressed again the oven is off
					    	OVEN_OFF();
                						}
					}
			else 
				RGB(0);
						 
					}
						
					



int main(){

SystemInit();
RGB(0x00);
delay_ms(200);
while (1) {
	switches();
}



}

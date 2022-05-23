void delay_milli ( unsigned long delay)
{
	unsigned long i;
	for( i=0 ; i<delay ; i++)
	{
		Systick_Wait (16000);   
	}
}

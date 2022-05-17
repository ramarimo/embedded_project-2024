unsigned char SW1(){
return GPIO_PORTF_DATA_R & 0x10;
}
unsigned char SW2(){
return GPIO_PORTF_DATA_R & 0x01;
}

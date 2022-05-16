#define NVIC_ST_CURRENT_R (*((volatile unsigned long *)0xE000E018))
#define NVIC_ST_CTRL_R (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R (*((volatile unsigned long *)0xE000E014))

void systick_Init(void){
  NVIC_ST_CTRL_R = 0;
  NVIC_ST_RELOAD_R = 0x00666666;
  NVIC_ST_CTRL_R = 00000005;
}
VOID Systick_WAIt(unsigned long delay){
  NVIC_ST_RELOAD_R = delay - 1;
  NVIC_ST_CURRENT_R = 0;
  while ((NVIC_ST_CTRL_R&0x00010000) == 0);
}

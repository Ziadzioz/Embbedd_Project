#include "tm4c123gh6pm.h"
/*
void PORTC_init(void){
	SYSCTL_RCGCGPIO_R|= 0x03;  //Activate clk for Port C
	while((SYSCTL_PRGPIO_R &0x03)== 0){}; //Wait Clk
		//GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTC_CR_R|= 0xFF;
		GPIO_PORTC_DIR_R|=0xFF;
		GPIO_PORTC_DEN_R|= 0xFF;
		GPIO_PORTC_AMSEL_R&= ~0xFF;
		GPIO_PORTC_DATA_R=0x00; //as default value
}
void PORTE_init(void){
	// using pe0 ,pe1 ,pe2 as indictors for the Three _Segment
	SYSCTL_RCGCGPIO_R|= 0x10;  //Activate clk for Port E
	while((SYSCTL_PRGPIO_R &0x10)== 0){}; //Wait Clk
		//GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTE_CR_R|= 0xFF;
		GPIO_PORTE_DIR_R|=0x07;
		GPIO_PORTE_DEN_R|= 0x07;
		GPIO_PORTE_AMSEL_R&= ~0x07;
		GPIO_PORTE_DATA_R=0x0; //as default value
}
void ThreeSegemnt(int distance )
{
	 seg1 = distance % 10;
	 distance = distance / 10;
	 seg2 = distance % 10;
	 seg3 = distance / 10;
}	
void Three7Segment(int Select, int Digit )
{
	GPIO_PORTE_DATA_R = Select;
	Seven_Segment(seg);
}

void Seven_Segment(char seg)
{
	char seven_Segment_table[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x4F};
	 int length = sizeof(seven_Segment_table)/sizeof(seven_Segment_table[0]);
	char index;
	for(int i=0,i<length,i++)
	{
	 Seven_Segment_Read(index)
		 if(seg == seven_Segment_table[i])
		 {
			  index = i;
			  break;
		 }
	}
}
void Seven_Segment_Read( int index)
{
	 GPIO_PORTC_DATA_R = seven_Segment_table[index];
}
*/

void PORTF_init(void){
	SYSCTL_RCGCGPIO_R|= 0x20;  //Activate clk for Port F
	while((SYSCTL_PRGPIO_R &0x20)== 0){}; //Wait Clk
		GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTF_CR_R|= 0x0E;
		GPIO_PORTF_DIR_R|=0x0E;
		GPIO_PORTF_DEN_R|= 0x0E;
		GPIO_PORTF_AMSEL_R&= ~0x0E;
}
//
void led_on (char color){
	GPIO_PORTF_DATA_R &= ~0x0E; // Turn leds of if they are on
	if(color == 'r'){
		GPIO_PORTF_DATA_R |= 0x02; //Red led turns on when input is 'r'
	}else if(color == 'b'){
		GPIO_PORTF_DATA_R |= 0x04; //Blue led turns on when input is 'b'
	}else{
		GPIO_PORTF_DATA_R |= 0x08; //Otherwise Green led turns on
	}
	 
}

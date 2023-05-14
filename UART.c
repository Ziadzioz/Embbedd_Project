#include "stdint.h"
#include "Tm4c123gh6pm.h"

//UART0 initialization function:

void initials_UART5(unsigned clk , unsigned baudrate){ //clk is 16 Mhz, baudrate is 9600
	 SYSCTL_RCGCUART_R |= 0x20;
	 SYSCTL_RCGCGPIO_R |= 0x10;
	 GPIO_PORTE_AMSEL_R &= ~0x30;
	 GPIO_PORTE_AFSEL_R |= 0x30;
	 GPIO_PORTE_PCTL_R |= 0x001100000;
	 GPIO_PORTE_DEN_R |= 0x30;
	 
	 UART5_CTL_R &= ~0x1;
	 UART5_IBRD_R = 104;
	 UART5_FBRD_R = 11;
	 UART5_LCRH_R = 0x70;
	 UART5_CTL_R = 0x301;
	 
	 GPIO_PORTE_AFSEL_R |= 0x30;
	 GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) + 0x00110000;
	 GPIO_PORTE_DEN_R |= 0x30;
	 GPIO_PORTE_AMSEL_R = 0x0;
	
	}

// UART0 input function
char UART5_Inchar(void){
  while((UART5_FR_R & UART_FR_RXFE) != 0);
	 return(char)(UART5_DR_R &0xFF);
 }

 // UART0 output function
void UART5_Outchar(char data){
  while((UART5_FR_R & 0x20) != 0);
	 UART5_DR_R = data;
 }

//(if needed) function to get data from gps through UART0:
/*
void get_gpsdata0(char *gpsdata){
 char character;
	 int i;
	 for( i=0; i<80 ; i++){//data length(100) should be adjusted to the length of data recieved from gps
	 character = UART0_Inchar();
		 if (character != '\r'){
		 gpsdata[i]= character;
			 UART0_Outchar(gpsdata[i]);
		 }
		 else if (character =='\r' || i ==100){break;}
	 }
 }
 */
 //char gpsdata[100]={};



// systick Timer initialization function:
 void initials_systick(void){
 NVIC_ST_CTRL_R=0;
 NVIC_ST_RELOAD_R=0x00FFFFFF;
 NVIC_ST_CURRENT_R=0;
 NVIC_ST_CTRL_R=0x00000005;
 }
 
 void systick_delay(uint32_t delay){
	 NVIC_ST_RELOAD_R=delay-1;
	 	NVIC_ST_CURRENT_R=0;
	 while ((NVIC_ST_CTRL_R&0x00010000)==0){}
 }
 
 //to be used systick Timer delay function (input is in micro seconds):
 void systick_wait(uint32_t micro_seconds){
	 int i;
	 for( i=0; i<micro_seconds; i++){
	 systick_delay(16);
	 } 
 }


 // UART1 initialization function:
void initials_UART1(unsigned clk , unsigned baudrate){ //clk is 16 Mhz, baudrate is 9600
	 unsigned BRD;
	 SYSCTL_RCGCUART_R |= 0x0002;  // enable clock for UART1
	 SYSCTL_RCGCGPIO_R |= 0x0003;  // activate clock for port C
	 UART1_CTL_R &= ~0x0001;
	 BRD = ((clk<<2)+(baudrate<<1))/baudrate;
	 UART1_IBRD_R = BRD>>6; //integer part of BRD value
	 UART1_FBRD_R = BRD&63; //float part of BRD value
	 UART1_LCRH_R =0x0070;  // 8 bit, no parity bits, one stop, FIFOs
	 UART1_CTL_R = 0x0301;  // enable RXE, TXE and UART
	 GPIO_PORTC_AFSEL_R |= 0x03;  //Use PC0,PC1 alternate function 
	 GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFFFFFF00)|0x00000011;
	 GPIO_PORTC_DEN_R = 0x03;  //enable digital in port C0,C1
	 GPIO_PORTC_DIR_R = 0x02 ;    //Rx:PC0  Tx:PC1
	 GPIO_PORTC_AMSEL_R &= ~0x03;  // disable analog in port C0,C1
 }

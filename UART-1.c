#include "stdint.h"
#include "Tm4c123gh6pm.h"

//UART0 initialization function:

void initials_UART0(unsigned clk , unsigned baudrate){ //clock is (unknown), baudrate is to be= 9600
	 unsigned BRD;
	 SYSCTL_RCGCUART_R |= 0x0001;  // enable clock for UART0
	 SYSCTL_RCGCGPIO_R |= 0x0001;  // activate clock for port A
	 UART0_CTL_R &= ~0x0001;
	 BRD = ((clk<<2)+(baudrate<<1))/baudrate;
	 UART0_IBRD_R = BRD>>6;
	 UART0_FBRD_R = BRD&63;
	 UART0_LCRH_R =0x0070;  // 8 bit, no parity bits, one stop, FIFOs
	 UART0_CTL_R = 0x0301;  // enable RXE, TXE and UART
	 GPIO_PORTA_AFSEL_R |= 0x03;  //Use PA0,PA1 alternate function 
	 GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)|0x00000011;
	 GPIO_PORTA_DEN_R = 0x03;  //enable digital in port B0,B1
	 GPIO_PORTB_DIR_R |= 0x02 ;    //Rx:PA0  Tx:PA1
	 GPIO_PORTA_AMSEL_R &= ~0x03;  // disable analog in port A0,A1
 }

// UART0 input function
char UART0_Inchar(void){
  while((UART0_FR_R & 0x10) != 0);
	 return(char)(UART0_DR_R &0xFF);
 }

 // UART0 output function
void UART0_Outchar(char data){
  while((UART0_FR_R & 0x20) != 0);
	 UART0_DR_R = data;
 }

//(if needed) function to get data from gps through UART0:
/*
void get_gpsdata0(char *gpsdata){
 char character;
	 int i;
	 for( i=0; i<100 ; i++){//data length(100) should be adjusted to the length of data recieved from gps
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
 NVIC_ST_RELOAD_R=0x00F42402;
 NVIC_ST_CURRENT_R=0;
 NVIC_ST_CTRL_R=0x00000005;
 }
 
 void systick_delay(uint32_t delay){
	 NVIC_ST_RELOAD_R=delay-1;
	 	NVIC_ST_CURRENT_R=0;
	 while ((NVIC_ST_CTRL_R&0x00010000)==0){}
 }
 
 //systick Timer delay function:
 void systick_wait(uint32_t seconds){
	 int i;
	 for( i=0; i<seconds; i++){
	 systick_delay(16000000);} //clock is (unknown), need to be adjusted
 }


 // UART1 initialization function:
void initials_UART1(unsigned clk , unsigned baudrate){ //clock is (unknown), baudrate is to be= 9600
	 unsigned BRD;
	 SYSCTL_RCGCUART_R |= 0x0002;  // enable clock for UART1
	 SYSCTL_RCGCGPIO_R |= 0x0004;  // activate clock for port C
	 UART1_CTL_R &= ~0x0001;
	 BRD = ((clk<<2)+(baudrate<<1))/baudrate;
	 UART1_IBRD_R = BRD>>6; //integer part of BRD value
	 UART1_FBRD_R = BRD&63; //float part of BRD value
	 UART1_LCRH_R =0x0070;  // 8 bit, no parity bits, one stop, FIFOs
	 UART1_CTL_R = 0x0301;  // enable RXE, TXE and UART
	 GPIO_PORTC_AFSEL_R |= 0x30; //Use PC4,PC5 alternate function 
	 GPIO_PORTC_PCTL_R = (GPIO_PORTB_PCTL_R&0xFF00FFFF)|0x00220000;
	 GPIO_PORTC_DEN_R = 0x30;  //enable digital in port B0,B1
	 GPIO_PORTC_DIR_R |= 0x10 ;    //Rx:PC4  Tx:PC5
	 GPIO_PORTC_AMSEL_R &= ~0x30;  // disable analog in port B0,B1
 }

 // UART1 input function:
 
char UART1_Inchar(void){
  while((UART1_FR_R & 0x10) != 0);
	 return(char)(UART1_DR_R &0xFF);
 }

 // UART1 output function:
 
void UART1_Outchar(char data){
  while((UART1_FR_R & 0x20) != 0);
	 UART1_DR_R = data;
 }

//(if needed) function to get data from gps through UART0:
/*
void get_gpsdata1(char *gpsdata){
 char character;
	 int i;
	 for( i=0; i<100 ; i++){//data length(100) should be adjusted to the length of data recieved from gps
	 character = UART1_Inchar();
		 if (character != '\r'){
		 gpsdata[i]= character;
			 UART1_Outchar(gpsdata[i]);
		 }
		 else if (character =='\r' || i ==100){break;}
	 }
 }
 
 char gpsdata[100]={"listend"}; //End of data stream */
 
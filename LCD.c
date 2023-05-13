//lcd.c
#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "GPS.h"
#include "string.h"
#include "stdint.h"
#include "UART.h"

 void LCD_sendCommand(char command)
 {
GPIO_PORTB_DATA_R &=0xFC;    /*Instruction Mode RS=0 /write data to LCD so RW=0 */
/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
GPIO_PORTB_DATA_R = ((GPIO_PORTB_DATA_R & 0x0F) | (command & 0xF0));
GPIO_PORTB_DATA_R |=0X04;/*enable=1*/
systick_wait(40);//delay 40us 
GPIO_PORTB_DATA_R &=0xFB;/*enable =0*/
/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
 GPIO_PORTB_DATA_R = ((	GPIO_PORTB_DATA_R & 0x0F) | ((command<< 4)&0xF0));/*write data*/
GPIO_PORTB_DATA_R |=0X04;/*enable=1*/
systick_wait(40);
GPIO_PORTB_DATA_R &=0xFB;/*enable =0*/
if(command<4)
systick_wait(2000);//delay 2ms	 
else 
systick_wait(40);//delay 40us
}

void LCD_data(char data) // distance
{GPIO_PORTA_DATA_R|=RS_ON;
GPIO_PORTB_DATA_R=data;
GPIO_PORTA_DATA_R|=EN_ON;
  //hena fy delay 
	//turnoff enable 
GPIO_PORTA_DATA_R|=0x00;
}

//to output a complete string
void LCD_outstring(char *pt){
while(*pt!=0){

LCD_data(*pt);
	pt++;
}
}


void LCD_init(void){
 
	 SYSCTL_RCGCGPIO_R |= 0x02; /* activate Port B */
  while((SYSCTL_PRGPIO_R&=0x00000002) == 0){};/*waite to activate*/ 
  GPIO_PORTB_AMSEL_R &= 0;         /* Disable Analog on PORTB*/
  GPIO_PORTB_PCTL_R   &= 0x00000000;   /* Clear PMCx bits for  PORTB to use it as GPIO pin */
  GPIO_PORTB_DIR_R    |= 0xFF;         /* Configure PORTB as output pin */
  GPIO_PORTB_AFSEL_R &= 0x0;         /* Disable alternative function on PORTB */
  GPIO_PORTB_DEN_R   |= 0xFF;         /* Enable Digital I/O onPORTB */
  GPIO_PORTB_DATA_R   &= 0x0;         /* Clear data in PORT B */
systick_wait(20000);//delay 20ms
LCD_sendCommand(0X30);//wakeup
systick_wait(5000); //DELAY 5mS
LCD_sendCommand(0X30);//wakeup
systick_wait(100);//DELAY 40uS
LCD_sendCommand(0X30);//wakeup
systick_wait(40);//DELAY 40uS
LCD_sendCommand(0x20); /* use 4-bit data mode */
systick_wait(40);//DELAY 40uS
 LCD_sendCommand(0X28); /* Select 4-bit Mode of LCD */
 LCD_sendCommand(0X06); /* clear whatever is written on display */
 LCD_sendCommand(0X01); /* shift cursor right */
 LCD_sendCommand(0X0F);  /* Enable Display and cursor blinking */
 }


void float_to_char_array(float value, char* char_array, int array_size)
	{

    sprintf(char_array, "%f", value);                               
}


/*
int main()
{
init_LCD();
while(1)
{
LCD_command(clear_screen); //clear
LCD_command(Beginning_1st_line); //first bit 3la el right 
LCD_data(dist);//hena el distance function
}

}
	*/
//test 2

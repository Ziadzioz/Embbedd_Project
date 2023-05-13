#include "GPS.h"
#include "tm4c123gh6pm.h"
#include "bit_utilies.h"
#include <math.h>
#include <string.h>
#include "stdint.h"
//#include "LCD.h"
#include "UART.h"
#include "GPIO.h"
#include <stdio.h>
#include <stdlib.h>
double dest_lat =  30.253349;
	double dest_long =31.466982;
	double dist;
double remaining_displacement;
	double current_position[2]= {0};
 double previous_position[2]= {0};
  //char number[8];
int main(){
	initials_UART5(16000000 , 9600);
	initials_systick();
	initials_PORTF();
	//init_LCD();
	//LCD_outstring ("hello ");
 
	
	while (1){
	
 GPS_read (current_position) ;
	
  if (previous_position [0]==0 | previous_position [1]==0){
 previous_position [0]= current_position [0]; 
 previous_position [1]= current_position [1] ; 
 
 }
 dist += Distance_calculate( previous_position [1] , previous_position [0], current_position [1] ,current_position [0]);
 previous_position [0]= current_position [0] ;
previous_position [1]= current_position [1] ;
 
 
	remaining_displacement	=Distance_calculate(previous_position [0] , previous_position [1] ,30.253684, 31.466645 );  
 
 if (remaining_displacement<=5){    
   //LCD_outstring ("Target Reached"); 	 
	 GPIO_PORTF_DATA_R |= 0X08; //greenledon
	 systick_wait(700); //delay
 }
 
 //else if  (remaining_displacement < 5){
	// GPIO_PORTF_DATA_R |= 0X0C ; // YELLOW ON)
 //delay 1sec 
	 
	

//float_to_char_array(dist, number, sizeof(number));
//void LCD_init(void);
//	LCD_outstring ("Distance: ");
//LCD_outstring (number);
//systick_wait(400); 

 //}
	 
	 
 else {
	 GPIO_PORTF_DATA_R |= 0X02 ;// RED ON
 //delay 1 sec 
 systick_wait(700);
	 
	//float_to_char_array(dist, number, sizeof(number));
//void LCD_init(void);
	// LCD_outstring ("Distance: /n");
//LCD_outstring (number);
	 
 }
 } }

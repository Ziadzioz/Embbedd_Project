#include "GPS.h"
#include "tm4c123gh6pm.h"
#include "bit_utilies.h"
#include <math.h>
#include <string.h>
#include "stdint.h"

#include "UART.h"
#include "GPIO.h"
#include <stdio.h>
#include <stdlib.h>
double dest_lat =  30.2539319;
	double dest_long =31.4667558;

double remaining_displacement;
extern	double currentlat;
extern	double currentlong;

	
int main(){
	initials_UART5(16000000 , 9600);
	initials_systick();
	initials_PORTF();
		
	while (1){
 GPS_read () ;
	
 
	remaining_displacement	= GPS_getDistance(TODEG(currentlat) , TODEG(currentlong), dest_lat ,dest_long  );  
 
 if (remaining_displacement < 10)
	 {    
  
	 GPIO_PORTF_DATA_R |= 0X08; //greenledon
	
 
	 }
 else {
	 GPIO_PORTF_DATA_R |= 0X02 ;// RED ON


 }
 } 
}


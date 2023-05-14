//Distance Function 
//check the output of the gps 
//read data from gps 
//cut the output of the gps 
//collect the data into 2D array
#include "GPS.h"
#include "tm4c123gh6pm.h"
#include "bit_utilies.h"
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "GPIO.h"
#include "UART.h"
const double PI = 3.14159265359 ;


 char GPS_OUTPUT[80];
 char GPS_logname[]= "$GPRMC," ;  
 
  char *token;  
char *Null; 
 char formated_GPS[12][20];
 char token_strings_counter = 0;
 char counter =0;
 int i;


float To_RAD(float angle){     //convert to radian 
   return ( angle* PI/180 );
}

  double Distance_calculate( double  current_lat , double current_long, double destination_lat,double destination_long){ //distance between two points
		
		
  double current_long_rad = To_RAD(current_long);
		
  double current_lat_rad = To_RAD(current_lat);
		
  double  destination_lond_rad = To_RAD(destination_long);
	
  double destination_lat_rad= To_RAD(destination_lat);
		
		//difference 
  double long_diff = current_long - destination_long;
  double  lat_diff = current_lat - destination_lat ;
		  
		//calculations to return the distance
		
		
  float a = pow (sin(lat_diff/2),2 ) + cos(current_lat_rad)*cos(destination_lat_rad)*pow(sin( long_diff/2),2);
	
  float  c = 2 *atan2(sqrt(a),sqrt(1-a));
		return(6371000*c); 		
	}
	
	
	char data ;
	char UART_GETCHAR(){              //get char 
	while ((UART5_FR_R & UART_FR_RXFE)!= 0){}
		
				 data= GET_REG(UART5_DR_R);//&0xFF

	return data;
	}
	
	
 void GPS_read (double position[2]){

char receivedchar = 0;
	char flag=1;
	do {
		flag=1;
		for( i=0 ; i<7 ;i++){
		if (UART_GETCHAR()!= GPS_logname[i]){  //chect the correct logname of the GPSoutput 
		flag=0;
			break;
		}
		}
}while(flag==0); 
	strcpy(GPS_OUTPUT, "");       //initialization gps array
 do{
	
	receivedchar = UART_GETCHAR(); 
	GPS_OUTPUT [counter ++] = receivedchar;
 }while (receivedchar!='*');        //cut the output of the gps 
   
	 token= strtok(	GPS_OUTPUT , ",");
	 do{  
		
		 strcpy(formated_GPS[ token_strings_counter],token);
		 token = strtok(Null,",");
		  token_strings_counter++;
	 }while(token != Null);                   //collect the output into 2D array
	 

	 if (strcmp(formated_GPS[1],"A")){
		 if (strcmp(formated_GPS[3],"N")==0){
			position[0] = atof(formated_GPS[2]);}
		 else {
			 position[0] = -atof(formated_GPS[2]);   
		 }
		 if (strcmp(formated_GPS[5],"5")==0){
	 position[1] = atof(formated_GPS[4]) ;}
		 else{
		position[1]  = - atof(formated_GPS[4]);
		 }
	
	 }
else {
 GPS_read (position);
 }
 
 }


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

	char flag=1;
 char GPS_OUTPUT[80];
 char GPS_logname[]= "$GPRMC," ;  
 char receivedchar = 0;
  char *token;  
char *Null; 
 char formated_GPS[12][20];
 char token_strings_counter = 0;
 char counter =0;
 int i;

double currentlat ;
double currentlong ;

double TODEG(double number){

return (int)(number/100)+( number-(int)(number/100)*100)/60.0;
}





double degToRad(double angle){     //convert to radian 
   return ( angle* PI/180 );
}
 
	double GPS_getDistance(double currentLat,double currentLong,double previousLat,double previousLong){
    double lat1 = degToRad(currentLat);
    double long1 = degToRad(currentLong);
    double lat2 = degToRad(previousLat);
    double long2 = degToRad(previousLong);
    double latdiff = lat2 - lat1;
    double longdiff = long2 - long1;

    double a= pow(sin(latdiff/2),2)+cos(lat1)*cos(lat2)*pow(sin(longdiff/2),2); // Haversine formula: a = sin²(?f/2) + cos f1 · cos f2 · sin²(??/2)
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return 6371000*c;   //in meters
}
	

	char UART_GETCHAR(){              //get char 
	while ((UART5_FR_R & UART_FR_RXFE)!= 0){}
		
return GET_REG(UART5_DR_R);//&0xFF	
	}
	
	
 void GPS_read (){



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
	 

	 if (strcmp(formated_GPS[1],"A"))
		 {
		 if (strcmp(formated_GPS[3],"N")==0)
			 {
		currentlat = atof(formated_GPS[2]);
			 }
		 else {
				currentlat = -atof(formated_GPS[2]);   
		 }
		 if (strcmp(formated_GPS[5],"5")==0)
			 {
 currentlong = atof(formated_GPS[4]) ;
			 }
		 else{
		currentlong = - atof(formated_GPS[4]);
		 }
		
	 }
	 
 }
 

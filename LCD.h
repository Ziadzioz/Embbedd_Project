//lcd.h
#ifndef LCD
#define LCD

#define wakeup      					0x30
#define eight_bit_mode				0x38
#define incremental_cursor		0x06
#define clear_screen     			0x01
#define display_on   					0x0F
#define RS_RW_OFF      				0x60
#define EN_ON      						0x80
#define RS_ON      						0x20
#define Beginning_1st_line		0x80

//Functions

 void LCD_sendCommand(char command);
void LCD_data(char data);
void init_LCD(void);
void float_to_char_array(float value, char* char_array, int array_size);
	 void LCD_outstring(char *pt);
#endif

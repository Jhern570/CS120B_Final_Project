void f_display(unsigned char on,unsigned short temp_f,unsigned short des_temp_f){
	LCD_ClearScreen();
        LCD_DisplayString(1,"TEMP:");
        Temp_Value(temp_f);
        LCD_DisplayString(11,"F");
        LCD_DisplayString(14,"FAN");
        LCD_DisplayString(17,"DSRD:");
        DSRD_Value(des_temp_f);
        LCD_DisplayString(27,"F");

	if(on == 0){
        	LCD_DisplayString(30,"OFF");
        }
        else{
                 LCD_DisplayString(31,"ON");
        }
}
void c_display(unsigned char on,unsigned short temp_c,unsigned short des_temp_c){
	LCD_ClearScreen();
        LCD_DisplayString(1,"TEMP:");
        Temp_Value(temp_c);
        LCD_DisplayString(11,"C");
        LCD_DisplayString(14,"FAN");
        LCD_DisplayString(17,"DSRD:");
        DSRD_Value(des_temp_c);
        LCD_DisplayString(27,"C");

	if(on == 0){
      		  LCD_DisplayString(30,"OFF");
        }
        else{
                  LCD_DisplayString(31,"ON");
        }
}

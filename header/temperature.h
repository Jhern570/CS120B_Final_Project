
unsigned short GetCelsius(unsigned short celsius){
        unsigned short temp;
	double r;
	double v;
	double a = 0.001129148;
        double b = 0.000234125;
	double c = 0.0000000876741;
		
	

	r = log(10000 / ((1024/(double)celsius) - 1));

        r  = (1 / (a + (b  + (c * r * r ))*r)) - 273.15;

        return (unsigned short)r;
}

unsigned short GetFahrenheit(unsigned short f){
        unsigned short temp;
        short celsius;

        celsius = GetCelsius(f);
        temp = ((celsius * 1.8) + 32);

        return temp;
}

void Temp_Value(unsigned short t){
	unsigned char i = 9; 
	while(t != 0){
        	unsigned short v = t % 10;
                LCD_Cursor(i--);
                LCD_WriteData(v + '0');
                t /= 10;
        }
}

void DSRD_Value(unsigned short t){
	unsigned char i = 25; 
        while(t != 0){
                unsigned short v = t % 10;
                LCD_Cursor(i--);
                LCD_WriteData(v + '0');
                t /= 10;
        }
}

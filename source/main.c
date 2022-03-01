/*	Author: Julio Hernandez
 *  Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Custom Project
 *	Demo: https://youtu.be/-8mM-Nxei8I
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
//#include "../header/ADC.h"
#include "../header/timer.h"
#include "../header/io.h"
#include "../header/temperature.h"
#include "../header/temp_display.h"
#endif
#define mux0 ~((1 << REFS1) | (1 << REFS0) | (1 << ADLAR) | (1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0))

unsigned short adc;


void ADC_x(){
        ADMUX = mux0;
        ADCSRA = (1 << ADEN) | (1 << ADIE);
        ADC_init();
}

void ADC_y(){
        //ADMUX = (1<<MUX0);
        ADCSRA |= (1 << ADEN) | (1 << ADIE);
	ADC_init();
}

void ADC_t(){
	
        //ADMUX = (1 << MUX2) | (1 << MUX0);
        ADCSRA = (1 << ADEN) | (1 << ADIE);
        //DIDR0 = (1<<ADC0D) | (1<<ADC1D);
	//_delay_us(10);
        ADC_init();

}
void ADC_init(){
        ADCSRA |= (1 << ADSC);
}
ISR(ADC_vect){
        adc = ADC;
	ADMUX++;
}

typedef struct task_obj {	
	signed char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int (*TickFct)(int);
} task;

//************ GLOBAL VARIABLES**************************// 
// Jotstick //
unsigned short x;
unsigned short y;
unsigned char z;
unsigned char b;
//*********//

// Temperature //
unsigned short temp_f;
unsigned short temp_c;
unsigned short temp_adc;
unsigned short des_temp_f = 0x48;// default desired temp
unsigned short des_temp_c = 0x16;// default desired temp
unsigned char switch_temp = 0;
//************//

unsigned char j = 0;
unsigned char on = 0;

//*******************************************************//
enum JoyStickSM {wait, x_plus, x_minus, y_plus, y_minus};
int Joystick(int state){// will update values for joystick x and y
	static unsigned char i;

	switch(state){
		case wait:
			if(x < 500 && (y >= 500 && y <= 600)){
        			if(switch_temp == 1){
                			switch_temp = 0;;
        			}
				state = x_minus;
			}
			else if(x > 600  && (y >= 500 && y <= 600)){
        			if(switch_temp == 0){
                			switch_temp = 1;
        			}
				state = x_plus;
			}
			else if(y < 500 && (x >= 500 && x <= 600)){
        			if(des_temp_f != 90){
                			des_temp_f++;
        			}
				if(des_temp_c != 32){
                                        des_temp_c++;
                                }
				i = 0;
				state = y_minus; 
			}
			else if(y > 600  && (x >= 500 && x <= 600)){
        			if(des_temp_f != 63){
                			des_temp_f--;
        			}
				if(des_temp_c != 17){
                                        des_temp_c--;
                                }
				i = 0;
				state = y_plus;
			}
			else{
				state  = wait;
			}
			break;
		case x_minus:
		       if(x < 500 && (y >= 500 && y <= 600)){
                                state = x_minus;
                        }
	       		else{
		 		state = wait;
			}		
			break;
		case x_plus:
                       if(x > 500 && (y >= 500 && y <= 600)){
                                state = x_plus;
                        }
                        else{
                                state = wait;
                        }
                        break;
		case y_minus:
			i++;
                       if(y < 500 && (y >= 500 && y <= 600)){
				if(i == 10){
			        	if(des_temp_f != 99){
                                        	des_temp_f++;
                                	}
                                	if(des_temp_c != 39){
                                        	des_temp_c++;
                                	}
					i = 0;
				}	
                                state = y_minus;
                        }
                        else{
                                state = wait;
                        }
                        break;
		case y_plus:
		       i++;
                       if(y > 500 && (y >= 500 && y <= 600)){
                               if(i == 10){
				      if(des_temp_f != 59){
                                        des_temp_f--;
                                	}
                                	if(des_temp_c != 10){
                                        	des_temp_c--;
                                	}
                                	i = 0;
			       }	
			       state = y_plus;
                        }
                        else{
                                state = wait;
                        }
                        break;
		default:
			state = wait;
			break;
	}
	return state;
}

enum ZButtonSM {wait_z,press,release};
int ZButton(int state){
	b = 0x01 & ~(PINB);
	switch(state){
		case wait_z:
			if(b == 1){
			       z = 1;
			       state = press;
			}
	 		else{
				state = wait_z;
			}
			break;
		case press:
			if(b ==1){
				state = press;
			}
			else if(b == 0 && z == 1){
				state = release;
			}
			else{
				state = wait_z;
			}
			break;
		case release:
			if(b == 1){
				z = 0;
				state = press;
			}
			else{
				state = release;
			}
			break;
		default:
			state = wait_z;
			z = 0;
			break;
	}
	return state;	
}
enum ThermistorSM{start_t, fahrenheit, celsius};
int Thermistor(int state){// will update the value of the thermosistor every second
	switch(state){
		case start_t:
			state = fahrenheit;
			break;
		case fahrenheit:
			//ADC_t();
			//temp_adc = adc;
			//temp_adc = 356;
			temp_f = GetFahrenheit(temp_adc);
			on = (temp_f > des_temp_f) ? 1 : 0;
				
			state = (switch_temp == 0) ? fahrenheit : celsius;
			break;
		case celsius:
			//ADC_t();
			//temp_adc = adc;
			//temp_adc = 356;
			temp_c = GetCelsius(temp_adc);
			on = (temp_c > des_temp_c) ? 1 : 0;
			
			state = (switch_temp == 0) ? fahrenheit : celsius;
			break;
		default:
			state = start_t;
			break;
	}
	return state;
}

enum LCDScreenSM {start_l,fahrenheit_dis, celsius_dis, fan_on,fan_off};

int LCDScreen(int state){// it will display the temperature of the room and the desired temp; it will also dislay for 3 second when the fan is on and off
	
	switch(state){
		case start_l:
			j++;
			LCD_ClearScreen();
			LCD_DisplayString(5,"CS-120B");
			LCD_DisplayString(19,"CUSTOM PROJECT");
			state = (j != 2) ? start_l : fahrenheit_dis;
			break;
		case fahrenheit_dis:
		        f_display(on,temp_f,des_temp_f);	
			state = (switch_temp == 0) ? fahrenheit_dis : celsius_dis;
                        break;
		case celsius_dis:
			c_display(on,temp_c,des_temp_c);
			state = (switch_temp == 0) ? fahrenheit_dis : celsius_dis;                        
                        break;
		default:
			state = start_l;
			break;
	}
	return state;

}

enum FanSM{start_f,f_on, f_off};
int Fan(int state){// it will turn on the fan when the temperature is higher than the desired temp
	switch(state){
		case start_f:
			state = f_off;
			break;
		case f_on:
			
			if(on == 1 && z == 0){
				state = f_on;
			}
			else{	
				PORTB = (0x01 & 0xFF);

				state = f_off;
			}
			break;
		case f_off:
			
			if(on == 1 && z == 1){
				state = f_off;
			}
			else if(on == 1 && z == 0){
				PORTB = 0x81 & 0xFF;
				state = f_on;
			}
			else{
				state = f_off;
			}
			break;
		default:
			state = start_f;
			break;
	}
	return state;
}
int main(void) {
    DDRA = 0x00; PORTA = 0xFF;//A is input
    DDRB = 0xFE; PORTB = 0x01;//B is output
    DDRC = 0xFF; PORTC = 0x00;//C is output
    DDRD = 0xFF; PORTD = 0x00;//D is output

    static task task1, task2, task3,task4, task5;
    task *tasks[] = {&task1, &task2, &task3, &task4, &task5};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    const char start = -1;

    task1.state = start;
    task1.period = 100;
    task1.elapsedTime = task1.period;
    task1.TickFct = &Joystick;

    task2.state = start;
    task2.period = 1000;
    task2.elapsedTime = task2.period;
    task2.TickFct = &Thermistor;

    task3.state = start;
    task3.period = 500;
    task3.elapsedTime = task3.period;
    task3.TickFct = &LCDScreen;

    task4.state = start;
    task4.period = 500;
    task4.elapsedTime = task4.period;
    task4.TickFct = &Fan;
    
    task5.state = start;
    task5.period = 100;
    task5.elapsedTime = task5.period;
    task5.TickFct = &ZButton;

    TimerSet(100);
    TimerOn();
    LCD_init();
    unsigned char i;
    while (1) {
	
	ADC_x();
	_delay_us(100);
        x = adc;
	_delay_us(100);
        ADC_y();
	_delay_us(100);
        y = adc;
	_delay_us(100);
	ADC_t();
	_delay_us(150);
	temp_adc = adc;
	_delay_us(100);
	for(i = 0; i < numTasks; i++){
		if(tasks[i]->elapsedTime == tasks[i]->period){
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 100;
	}
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

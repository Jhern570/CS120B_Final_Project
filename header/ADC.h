#define mux0 ~((1 << REFS1) | (1 << REFS0) | (1 << ADLAR) | (1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0))

unsigned short adc;

void ADC_init(){
        ADCSRA |= (1 << ADSC);
}

void ADC_x(){
	ADMUX = mux0;
        ADCSRA = (1 << ADEN) | (1 << ADIE);
	ADC_init();
}

void ADC_y(){
	ADMUX = (1<<MUX0);
	ADCSRA |= (1 << ADEN) | (1 << ADIE);
}

void ADC_t(){
	ADMUX = (1<<MUX2) | (1<<MUX0);
        ADCSRA = (1 << ADEN) | (1 << ADIE);
	DIDR0 = (1<<ADC0D) | (1<<ADC1D);
	ADC_init();

}

ISR(ADC_vect){
	adc = ADC;
}

unsigned short GetADC(){
	return adc;
}

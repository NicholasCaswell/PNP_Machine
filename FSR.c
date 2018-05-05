#include <avr/io.h>
#include <avr/interrupt.h>

#define P_Sensor	6
#define P_LED		0

volatile uint8_t P_Conf = 0;
volatile uint16_t Pressure_val = 0x0000;

void adcSetUp(){
	//////////////////////////////////////// Setup I/O Ports
	DDRC &= ~(1 << P_Sensor);							// Set ADC0 to input
	PORTC |= (1 << P_Sensor);							// Pull-up resistor
	DDRB  |= (1 << P_LED);								// LED to output

	//////////////////////////////////////// Setup ADC0
	ADMUX  &=~(1 << MUX3);			//(0)	Sets ADMUX to ADC6
	ADMUX  |= (1 << MUX2);			//(1)
	ADMUX  |= (1 << MUX1);			//(1)
	ADMUX  &=~(1 << MUX0);			//(0)
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADATE);
	ADCSRA |= (1 << ADIE);
	ADCSRA |= (1 << ADPS1);
	ADCSRA |= (1 << ADPS0);
	ADCSRA |= (1 << ADPS2);
	ADMUX  |= (1 << REFS0);
	ADMUX  |= (1 << REFS1);
	
	ADCSRB = (0b000<<ADTS0);
	sei();
	ADCSRA |= (1 << ADSC);
}

int FSR(void)
{
    //while (1) 
    //{
		adcSetUp();
		PORTB &= ~(1 << P_LED);
		if(ADC < 0x0200 || Pressure_val < 0x0200)
		{
			P_Conf = 1;
			//PORTB |= (1 << P_LED);
			return 1;
		}
		else
		{
			P_Conf = 0;
			//PORTB &= ~(1 << P_LED);
			return 0;
		}
	//}
}



ISR(ADC_vect)
{
	Pressure_val = ADC;
}



/*//////////////////////////////////////// Setup I/O Ports
	DDRC &= ~(1 << P_Sensor);							// Set ADC0 to input
	PORTC |= (1 << P_Sensor);							// Pull-up resistor
	DDRB  |= (1 << P_LED);								// LED to output

	//////////////////////////////////////// Setup ADC0
	ADMUX  &=~(1 << MUX3);			//(0)	Sets ADMUX to ADC6
	ADMUX  |= (1 << MUX2);			//(1)	
	ADMUX  |= (1 << MUX1);			//(1)	
	ADMUX  &=~(1 << MUX0);			//(0)	
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADATE);
	ADCSRA |= (1 << ADIE);
	ADCSRA |= (1 << ADPS1);
	ADCSRA |= (1 << ADPS0);
	ADCSRA |= (1 << ADPS2);
	ADMUX  |= (1 << REFS0);
	ADMUX  |= (1 << REFS1);
	
	ADCSRB = (0b000<<ADTS0);
	sei();
	ADCSRA |= (1 << ADSC);
	*/
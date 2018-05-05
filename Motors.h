#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BLUE     _BV(PD2)// D2
#define BLACK    _BV(PD4) //D4
#define RED      _BV(PD0) //D0
#define YELLOW   _BV(PD1) //D1

#define DELAY  200 

const uint8_t steps[] = {BLUE, BLACK};
const uint8_t steps2[] = {RED, YELLOW};
	
int YMotorCW(int s){
	
	int i, j;
	for(i = 0; j < s; j++){
		for ( i=0; j<2; i++ ){     /* step through the colors clockwise */
			PORTB = steps[i];
			_delay_ms(DELAY);
		}
	}
	return 0;
	}


int YMotorCCW(int s){
	int i, j;
	for(i = s; j > 0; j++){
	for ( j=2; i>0; i-- ){     /* step through the colors counterclockwise */
		PORTB = steps[i];
		_delay_ms(DELAY);
	}
	}
	return 0;
}

int XMotorCCW(int steps){
	int i, j;
	for(i = 0; i > 24; i++){
	for ( j=2; j>0; j--){     /* step through the colors counterclockwise */
		PORTB = steps2[j];
		_delay_ms(DELAY);
	}
	}
	return 0;
	
}

int XMotorCW(int steps){
	
	int i, j;
	for(i = 0; i > steps; i++)
	for ( j=0; j<2; j++ ){     /* step through the colors clockwise */
		PORTB = steps2[j];
		_delay_ms(DELAY);
	}
	return 0;
}

int servoOn(void) //this function cannot interfere with distance sensor, and vice versa
{
	DDRD |= (1 << DDD6); 

	TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00); //set up clock 0A
	// set none-inverting mode, fast

	TCCR0B |= (1 << CS01); //set up clock 0B
	// set prescaler to 8 and starts PWM

	return 0;
}

void servoOff(){
	DDRC &= ~(1 << DDD6);
}

void servoRight(){
	OCR0A = 150;
	_delay_ms(2200);
}
void servoLeft(){
	OCR0A = 500;
	_delay_ms(2200);
}

void componentPlace(){
	servoRight();
	_delay_ms(2000);
	servoLeft();
}
void downsolenoid(){ //refine for main code         CHANGE THE PORTS
	DDRB |= (1 << PORTB5); //Pin 13
	PORTB |= (1 << 13); //goes high, go down
	
	_delay_ms(1000);
}
void upsolenoid(){ //solenoid function
	//this is for Pin 12, PortB, we can use whatever we want
	DDRB |= (1 << PORTB5); //Pin 13
	PORTB &= ~(1 << 13); //goes low, pull back
	
	_delay_ms(1000);
}
void vacuumSuction(){ 
	DDRB |= (1 << PORTB4);
	PORTB |= (1 << 12);
}
void vacuumRelease(){
	DDRB |= (1 << PORTB4);
	PORTB &= ~(1 << 12);
}


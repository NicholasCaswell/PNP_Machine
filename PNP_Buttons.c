#include "I2C.h"
#include "LCD_I2C.h"
#include "I2C.c"
#include "LCD_I2C.c"
#define B_UP 5		//PD5
#define B_DWN 6		//PD6
#define B_LEFT 7	//PD7
#define B_RIGHT 0	//PB0
#define B_GND 1		//PB1

volatile uint8_t Bpad[4] = {0, 0, 0, 0};								// Array to indicate which buttons are currently pressed
	
	void setButtonOne(){
		PORTD &= ~(1 << B_UP);										// Set up to LOW
		PORTD |= (1 << B_DWN) | (1 << B_LEFT);						// Set down and left to LOW
		PORTB |= (1 << B_RIGHT);										// Set right to LOW
		PORTB |= (1 << B_RIGHT);										// Set right to LOW		Repeated for extra clock cycles
		PORTC &= ~(1 << PORTC0);										// Set UP LED to OFF
	}
	
	void setButtonTwo(){
		PORTD &= ~(1 << B_DWN);										// Set down to LOW
		PORTD |= (1 << B_UP) | (1 << B_LEFT);						// Set up and left to LOW
		PORTB |= (1 << B_RIGHT);										// Set right to LOW
		PORTC &= ~(1 << PORTC1);										// Set down LED to OFF
	}
	
	void setButtonThree(){
		PORTD &= ~(1 << B_LEFT);										// Set left to LOW
		PORTD |= (1 << B_DWN) | (1 << B_UP);							// Set up and down to LOW
		PORTB |= (1 << B_RIGHT);										// Set right to LOW
		PORTC &= ~(1 << PORTC2);
	}
	void setButtonFour(){
		PORTB &= ~(1 << B_RIGHT);									// Set right to LOW
		PORTD |= (1 << B_UP) | (1 << B_DWN) | (1 << B_LEFT);			// Set up, down, and left to LOW
		PORTC &= ~(1 << PORTC3);
	}

int Buttons()
{
/////////////////////////////////////////////////////////////////////////////////////////////////// SETUP
	DDRB &= ~(1 << B_GND);											// Set D2 to input
	PORTB |= (1 << B_GND);											// turn On Pull-up Resistor (Active Low)


	DDRD |= (1 << B_UP) | (1 << B_DWN) | (1 << B_LEFT);				// Set up/down/left to outputs
	PORTD &= ~((1 << B_UP) | (1 << B_DWN) | (1 << B_LEFT));			// Set all to LOW
	DDRB |= (1 << B_RIGHT);											// Set right to output
	PORTB &= ~(1 << B_RIGHT);										// Set to LOW

	DDRC = 0xff;														// Set LED ports to output
	PORTC = 0x00;													// Initialize LEDS off
	
			setButtonOne();
			LCD_putstring("Press Up For");
			LCD_GotoXY(1, 0);
			LCD_putstring("Placement");
			_delay_ms(4000);
			LCD_ClrScr();
			LCD_GotoHome();
			LCD_putstring("Verification");
			_delay_ms(2000);
		if(PINB & (1 << B_GND))										// Check for UP condition
		{															// If true(button unpressed)
			Bpad[0] = 0;												// Set Bpad[up] to unpressed(0)
			//PORTC &= ~(1 << PORTC0);									// Set UP LED to OFF
			
		}
		else															// If false(button pressed)
		{
			Bpad[0] = 1;												// Set Bpad[up] to pressed(1)
			//PORTC |= (1 << PORTC0);										// Set UP LED to ON
			LCD_ClrScr();
			LCD_putstring("Next...");
			_delay_ms(2000);
			LCD_ClrScr();
		}
		setButtonTwo();
		LCD_putstring("Press Up For");
			LCD_GotoXY(1, 0);
			LCD_putstring("Component");
			_delay_ms(4000);
			LCD_ClrScr();
			LCD_GotoHome();
			LCD_putstring("Verification");
			_delay_ms(2000);
		if(PINB & (1 << B_GND))										// Check for down condition
		{															// If true(button unpressed)
			Bpad[1] = 0;												// Set Bpad[down] to unpressed(0)
			//PORTC &= ~(1 << PORTC1);									// Set down LED to OFF
		}
		else															// If false(button pressed)
		{
			Bpad[1] = 1;												// Set Bpad[down] to pressed(1)
			//PORTC |= (1 << PORTC1);                                   // Set down LED to ON
			LCD_ClrScr();
			LCD_putstring("Next...");
			_delay_ms(2000);
			LCD_ClrScr();
		}
		setButtonThree();
		LCD_putstring("Press Up For");
			LCD_GotoXY(1, 0);
			LCD_putstring("Component");
			_delay_ms(4000);
			LCD_ClrScr();
			LCD_GotoHome();
			LCD_putstring("Verification");
			_delay_ms(2000);
		if(PINB & (1 << B_GND))										// Check for left condition
		{															// If true(button unpressed)
			Bpad[2] = 0;												// Set Bpad[left] to unpressed(0)
			PORTC &= ~(1 << PORTC2);									// Set left LED to OFF
		}
		else															// If false(button pressed)
		{
			Bpad[2] = 1;												// Set Bpad[left] to pressed(1)
			//PORTC |= (1 << PORTC2);									// Set left LED to ON
			LCD_ClrScr();
			LCD_putstring("Next...");
			_delay_ms(2000);
			LCD_ClrScr();
		}
		setButtonFour();
		LCD_putstring("Press Up For");
			LCD_GotoXY(1, 0);
			LCD_putstring("Component");
			_delay_ms(4000);
			LCD_ClrScr();
			LCD_GotoHome();
			LCD_putstring("Verification");
			_delay_ms(2000);
		if(PINB & (1 << B_GND))										// Check for right condition
		{															// If true(button unpressed)
			Bpad[3] = 0;												// Set Bpad[right] to unpressed(0)
			//PORTC &= ~(1 << PORTC3);									// Set right LED to OFF
		}
		else															// If false(button pressed)
		{
			Bpad[3] = 1;												// Set Bpad[right] to pressed(1)
			//PORTC |= (1 << PORTC3);									// Set right LED to ON
			LCD_ClrScr();
			LCD_putstring("Next...");
			_delay_ms(2000);
			LCD_ClrScr();
		}
		return 1;
		
		
}
	
	
		
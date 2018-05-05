/*
 * PNP_Machine_Final.c
 *
 * Created: 12/8/2017 10:54:44 AM
 * Author : Nicholas Caswell
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include "Motors.h"
//#include "distanceSensor.h"

#include "PNP_Buttons.c"
#include "FSR.c"


//int main(void);

int main(void)
{
	TWI_Init();
	sei();
	LCD_Init();
	//TODO: fix servo placement
	//fix FSR
	//fix DistanceSensor, if still applicable
	//integrate buttons
	
	DDRB = 0xff;      
	PORTC = 0x00; //input
	DDRC = 0xff; //internal pullup resistors
    /* Replace with your application code */
	
	servoOn(); //other components should have separate set up functions
	
	int buttonRet = Buttons();
	
	if (buttonRet == 1){
		/*Begin Process Code */
		
		LCD_putstring("Welcome to");
		LCD_GotoXY(1, 0);
		LCD_putstring("MATLAB");
		_delay_ms(2000);
		LCD_ClrScr();
		LCD_putstring("Beginning Process...");
		_delay_ms(2000);
		LCD_ClrScr();
		LCD_GotoHome();
		
		//first component
		LCD_putstring("Placing First");
		LCD_GotoXY(1, 0);
		LCD_putstring("Component...");
		XMotorCCW(10);
		YMotorCCW(10);
		downsolenoid();
		//vacuum on, drive vacuum pin high
		vacuumSuction();
		//if pressure change, upsolenoid()
		while(FSR() == 1){
			continue;
		}
		upsolenoid();
		XMotorCCW(26);
		YMotorCCW(14);
		servoLeft();
		servoOff();
		downsolenoid();
		vacuumRelease(); //vacuum release
		
		LCD_ClrScr();
		//steppers go home
		XMotorCW(36);
		YMotorCW(24);
		_delay_ms(2000);
		LCD_GotoHome();
		
		//second component
		servoOn(); //turn servo back on
		LCD_putstring("Placing Second");
		LCD_GotoXY(1, 0);
		LCD_putstring("Component...");
		XMotorCCW(10);
		YMotorCCW(10);
		downsolenoid();
		//vacuum on, drive vacuum pin high
		vacuumSuction();
		//if pressure change, upsolenoid()
		while(FSR() == 1){
			continue;
		}
		upsolenoid();
		XMotorCW(26);
		YMotorCW(14);
		servoRight();
		servoLeft();
		servoOff();
		downsolenoid();
		vacuumRelease(); //vacuum release
		
		LCD_ClrScr();
		//steppers go home
		XMotorCW(36);
		YMotorCW(24);
		_delay_ms(2000);
		LCD_GotoHome();
		
		//third component
		servoOn(); //turn servo back on
		LCD_putstring("Placing Second");
		LCD_GotoXY(1, 0);
		LCD_putstring("Component...");
		XMotorCCW(10);
		YMotorCCW(10);
		downsolenoid();
		//vacuum on, drive vacuum pin high
		vacuumSuction();
		//if pressure change, upsolenoid()
		while(FSR() == 1){
			continue;
		}
		upsolenoid();
		XMotorCW(26);
		YMotorCW(14);
		servoRight();
		servoLeft();
		servoOff();
		downsolenoid();
		vacuumRelease(); //vacuum release
		LCD_GotoHome();
		
		LCD_ClrScr();
		LCD_putstring("Placements");
		LCD_GotoXY(1, 0);
		LCD_putstring("Complete");
		_delay_ms(3000);
		LCD_ClrScr();
		LCD_putstring("Goodbye");
		servoOff();
		LCD_BacklightOff();
	}			
}


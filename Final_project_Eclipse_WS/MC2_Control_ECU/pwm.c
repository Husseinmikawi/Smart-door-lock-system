/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: source file for the PWM driver
 *
 * Author: Hussein Ahmed
 *
 *******************************************************************************/
#include"pwm.h"
#include<avr/io.h>
#include"gpio.h"
#include"std_types.h"


/*******************************************************************************
 *                      Functions definitions                                   *
 *******************************************************************************/
/* Description:
 * The function responsible for trigger the Timer0 with the PWM Mode.
 * Setup the compare value based on the required input duty cycle
 * The generated PWM signal frequency will be 500Hz to control the DC Motor speed. */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	/* convert percentage value to the provided value */
	if(duty_cycle>0)
	{
		duty_cycle=(uint8)((1.0*duty_cycle/100)*255);
	}
	TCNT0 = 0; //Set Timer Initial value

	OCR0  = duty_cycle; // Set Compare Values

	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_ENABLE_PIN_ID, PIN_OUTPUT);

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<6) | (1<<3) | (1<<5) | (1<<1);

}


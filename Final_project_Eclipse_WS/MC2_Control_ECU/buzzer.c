/******************************************************************************
 *
 * Module: buzzer
 *
 * File Name: buzzer.c
 *
 * Description: header file for the buzzer driver
 *
 * Author: Hussein Ahmed
 *
 *******************************************************************************/

#include"gpio.h"


/*******************************************************************************
 *                      Functions definitions                                   *
 *******************************************************************************/
/* Description:
 * Setup the direction for the buzzer pin as output pin through the GPIO driver.
 * Turn off the buzzer through the GPIO. */
void Buzzer_init(void)
{
	/* set PA0 as output pin*/
	GPIO_setupPinDirection(PORTA_ID, PIN0_ID, PIN_OUTPUT);
	/* write LOGIC_LOW(0) on PA0*/
	GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_LOW);
}

/* Description:
 * Function to enable the Buzzer through the GPIO.*/
void Buzzer_on(void)
{
	/* write LOGIC_HIGH(1) on PA0*/
	GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_HIGH);

}

/* Description:
 * Function to disable the Buzzer through the GPIO.*/
void Buzzer_off(void)
{
	/* write LOGIC_LOW(0) on PA0*/
	GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_LOW);
}

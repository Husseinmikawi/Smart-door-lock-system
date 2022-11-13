/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.c
 *
 * Description: source file for the timer1 driver
 *
 * Author: Hussein Ahmed
 *
 *******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include"std_types.h"
#include "timer1.h"

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions definitions                                   *
 *******************************************************************************/
/* Description:
 * Function to initialize the Timer driver */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCNT1 = Config_Ptr->initial_value;		/* Set timer1 initial count to zero */

	if(Config_Ptr->mode==NORMAL_MODE)
	{
		TIMSK&=~(1<<OCIE1A); /* disable compare mode interrupt*/
		TIMSK |= (1<<TOIE1);/* Enable normal mode interrupt*/
	}
	else if (Config_Ptr->mode==COMPARE_MODE)
	{
		TIMSK&=~(1<<TOIE1);/* disable normal mode interrupt*/
		OCR1A = Config_Ptr->compare_value;     /* Set the Compare value  */

		TIMSK |= (1<<OCIE1A); /* Enable Timer1 Compare A Interrupt */
	}


	/* Configure timer control register TCCR1A
	 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
	 * 2. FOC1A=1 FOC1B=1
	 * 3. CTC & normal Modes WGM10=0 WGM11=0 (Modes Number 0&4)
	 */
	TCCR1A = (1<<FOC1A)|(1<<FOC1B);

	/* Configure timer control register TCCR1B
	 * 1. CTC Mode WGM12=1 WGM13=0
	 * 2. Prescaler = Config_Ptr->prescaler
	 */
	TCCR1B = (Config_Ptr->mode) | (Config_Ptr->prescaler);
}

/* Description:
 * Function to disable the Timer1. */
void Timer1_deInit(void)
{
	TIMSK=0;
	TCCR1A=0;
	TCCR1B=0;
	OCR1A=0;
	TCNT1=0;

}

/* Description:
 * Function to set the Call Back function address. */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

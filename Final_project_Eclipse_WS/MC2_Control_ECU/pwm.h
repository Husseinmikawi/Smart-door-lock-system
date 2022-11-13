/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for the PWM driver
 *
 * Author: Hussein Ahmed
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_MOTOR_PORT_ID           PORTB_ID
#define DC_MOTOR_ENABLE_PIN_ID     PIN3_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/* Description:
 * The function responsible for trigger the Timer0 with the PWM Mode.
 * Setup the compare value based on the required input duty cycle
 * The generated PWM signal frequency will be 500Hz to control the DC Motor speed. */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */

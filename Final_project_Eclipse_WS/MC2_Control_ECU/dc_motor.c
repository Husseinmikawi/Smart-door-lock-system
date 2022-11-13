/******************************************************************************
 *
 * Module: DC-motor
 *
 * File Name: dc_motor.c
 *
 * Description: source file for the DC-motor driver
 *
 * Author: Hussein Ahmed
 *
 *******************************************************************************/
#include"gpio.h"
#include"dc_motor.h"
#include"pwm.h"

/**********************************************************************************
 * 								 Functions Definitions						      *
 **********************************************************************************/
/*
 * Description :
 * The Function responsible for setup the direction for the two
   motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_INPUT1_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_INPUT2_ID, PIN_OUTPUT);

	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INPUT1_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INPUT2_ID, LOGIC_LOW);
}

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or
   stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{

	switch(state)
	{
	case STOP:
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INPUT1_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INPUT2_ID, LOGIC_LOW);
		break;
	case CLOCK_WISE:
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INPUT1_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INPUT2_ID, LOGIC_LOW);
		break;
	case ANTI_CLOCK_WISE:
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INPUT1_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_INPUT2_ID, LOGIC_HIGH);
		break;
	}
	PWM_Timer0_Start(speed);
	}



/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.h
 *
 * Description: header file for the timer1 driver
 *
 * Author: Hussein Ahmed
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK,CLOCK_BY_1,CLOCK_BY_8,CLOCK_BY_64,CLOCK_BY_256,CLOCK_BY_1024
}Timer1_Prescaler;

typedef enum
{
	NORMAL_MODE,COMPARE_MODE=0X08
}Timer1_Mode;

typedef struct {
	uint16 initial_value;
	uint16 compare_value;
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/* Description:
 * Function to initialize the Timer driver */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
/* Description:
 * Function to disable the Timer1. */
void Timer1_deInit(void);
/* Description:
 * Function to set the Call Back function address. */
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER1_H_ */

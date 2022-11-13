/*
 ================================================================================================
 Name        : MC2_Control_ECU.c
 Author      : Hussein Ahmed
 Description : control the mc2 ECU
 Date        : 4/11/2022
 ================================================================================================
 */
#include"uart_Hus.h"
#include"std_types.h"
#include"twi.h"
#include"external_eeprom.h"
#include<util/delay.h>
#include"dc_motor.h"
#include"buzzer.h"
#include "timer1.h"
#include <avr/io.h>

#define MC1_READY 0x10
#define UNMATCHED 0XFF
#define MATCHED   0X0F

static volatile uint8 g_tick=0; /* global variable to increment with every 3 sec by timer1 interrupt*/

/*function called by timer1*/
void delay_3SEC(void)
{
	g_tick++;
}

int main(void)
{
	SREG|=(1<<7); /* enable Global interrupt*/
	uint8 i,menu,j=0;
	uint8 pass_matching_state = MATCHED;
	uint8 arr1[7];/* array to store the pass sent by UART*/
	uint8 arr2[7];/* array to store the pass sent by UART*/

	TWI_ConfigType twi_config = {0x01,0x02}; /* create a structure to configure TWI*/

	/* create a structure to configure the timer 1 with require mode and step time
		 * 0 initial value
		 * compare value =23437
		 * CPU frequency divided by 1024 prescale
		 * timer compare mode
		 */
	Timer1_ConfigType Timer_Conf={0,23437,CLOCK_BY_1024,COMPARE_MODE,};


	/* Set the Call back function pointer in the timer driver */
	Timer1_setCallBack(delay_3SEC);

	/* Initialize UART,TWI,DCMotor and Buzzer drivers */
	UART_init(&g_uartConfiguration);
	TWI_init(&twi_config);
	DcMotor_Init();
	Buzzer_init();

	while(1)
	{
		pass_matching_state=MATCHED;
		/* wait until the MC1 finished its operations and it is start sending*/
		while(UART_recieveByte() != MC1_READY){}
		UART_receiveString(arr1);/* Receive first pass and store it in array1*/
		UART_receiveString(arr2);/* Receive second pass and store it in array2*/

		for(i=0;i<7;i++)
		{
			if(arr1[i] != arr2[i]) /* if any elements in the passes is not matched*/
			{
				pass_matching_state = UNMATCHED; /* save unmatched in pass_matching_state*/
				break; /* break the current loop*/
			}
		}

		UART_sendByte(MC1_READY);/* send MC1_READY to the HMI ECU to notice him i'm start sending*/
		UART_sendByte(pass_matching_state); /* send the matching state*/

		if(pass_matching_state == MATCHED)
		{
			/* save the matched pass in the EEPROM*/
			for(i=0;i<5;i++)
			{
				EEPROM_writeByte((0x0310+i), arr1[i]);
				_delay_ms(10);
			}
			/* loop to repeat receiving the pass 3 times*/
			j=0;
			while(j<3)
			{
				pass_matching_state=MATCHED;
				while(UART_recieveByte() != MC1_READY){}
				UART_receiveString(arr1); /* receive the menu pass*/
				menu=UART_recieveByte();/* receive the running operation symbol*/
				/* check if the sent pass matched with saved pass in the EEPROM */
				for(i=0;i<5;i++)
				{
					EEPROM_readByte((0x0310+i), &arr2[i]); /* store the saved pass in EEPROM in arra2*/
					if(arr1[i] !=arr2[i] )/* if the passes is not matched*/
					{
						pass_matching_state = UNMATCHED;
						break;/* break the current loop*/
					}
				}

				UART_sendByte(MC1_READY);
				UART_sendByte(pass_matching_state);
				if((pass_matching_state == MATCHED)&& (menu=='+'))
				{

					/*turn on the motor CW with 100% of its maximum speed.*/
					DcMotor_Rotate(CLOCK_WISE,100);
					Timer1_init(&Timer_Conf); /* Initialize timer 1*/
					while(g_tick!=5){}/* wait until the g_tick increment to 5 (5*3=15SEC)*/
					g_tick=0;/* clear the g_tick for next time*/
					/*turn off the motor*/
					DcMotor_Rotate(STOP,0);
					while(g_tick!=1){}/* wait until the g_tick increment to 1 (1*3=3SEC)*/
					g_tick=0;/* clear the g_tick for next time*/
					/*turn on the motor CW with 100% of its maximum speed.*/
					DcMotor_Rotate(ANTI_CLOCK_WISE,100);
					while(g_tick!=5){}/* wait until the g_tick increment to 5 (5*3=15SEC)*/
					g_tick=0;/* clear the g_tick for next time*/
					Timer1_deInit();/* deinit timer 1*/
					/*stop the motor*/
					DcMotor_Rotate(STOP,0);
					break;/* break the current loop*/

				}
				else if((pass_matching_state == MATCHED)&& (menu=='-'))
				{
					break;/* break the current loop*/

				}
				else if((pass_matching_state == UNMATCHED))
				{
					j++;/* increment the loop index*/
					continue; /* skip this iteration*/
				}
			}
			/* if the pass unmatched 3 times do the following code*/
			if(j==3)
			{
				UART_sendByte(MC1_READY);
				UART_sendByte(UNMATCHED);
				Buzzer_on(); /* turn on the buzzer*/
				Timer1_init(&Timer_Conf);/* Initialize timer 1*/
				while(g_tick!=20){}/* wait until the g_tick increment to 20 (20*3=60SEC=1minute)*/
				g_tick=0;/* clear the g_tick for next time*/
				Timer1_deInit();/* deinit timer 1*/
				Buzzer_off();/* turn off the buzzer*/
				j=0;
				continue;

			}
		}
		else if(pass_matching_state == UNMATCHED)
			continue;/* skip this iteration*/


	}

}


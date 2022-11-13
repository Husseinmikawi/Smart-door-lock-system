 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Hussein Ahmed
 *
 *******************************************************************************/

#ifndef UART_HUS_H_
#define UART_HUS_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	DISABLED,EVEN_PARITY=0x20,ODD_PARITY=0x30
}UART_parityMode;

typedef enum
{
	_1_BIT,_2_BIT
}UART_stopBitNumber;

typedef enum
{
	_5_BIT,_6_BIT,_7_BIT,_8_BIT,_9_BIT=7
}UART_characterSize;

typedef struct
{
	UART_parityMode     parity;
	UART_stopBitNumber  stop_bit;
	UART_characterSize  data_size;
	uint32              baud_rate;
}UART_configuration;

/**********************************************************************************
 * 						Extern public global variables 						      *
 **********************************************************************************/
extern UART_configuration g_uartConfiguration;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_configuration *config_ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_HUS_H_ */

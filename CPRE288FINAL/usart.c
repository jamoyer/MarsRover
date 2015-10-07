/**
* @file usart.c
* @brief Includes functions related to USART communication.
*   Call serial_init() first.
*
* @author Jacob Moyer, 
*         Ed Droesch, 
*         Aaron Pederson, & 
*         Matthew Backes
*
* @date 12/13/2013
*/

#include <avr/io.h>
#include "lcd.h"
#include "util.h"
#include "usart.h"

/**
* Returns a byte from the USART connection.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
char USART_Receive()
{
    while ((UCSR0A & 0b10000000) == 0)
    ;
    return UDR0;
}

/**
* Initializes the USART connection.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
void usart_init()
{
    ///57600 baud rate
     unsigned int baud = 16000000/(16*57600)-1;

    /// Set baud rate
    UBRR0H = (unsigned char) (baud >> 8);
    UBRR0L = (unsigned char)baud;
    /// Enable normal speed mode
    UCSR0A = 0b00000000;
    /// Set frame format: 8 data bits, 1 stop bits
    UCSR0C = 0b00000110;
    /// Enable receiver and transmitter
    UCSR0B = 0b00011000;
}/**
* Transmits a byte through the USART connection.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @param data   The character to transmit.
* @date 12/13/2013
*/void serial_putc(char data){    while((UCSR0A & 0b00100000)==0);    UDR0 =data;}/**
* Transmits a string of characters through the USART connection.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @param x  The name of the array of characters to transmit.
* @date 12/13/2013
*/void string_tran(char x[]){    for(int i =0; x[i]!='\0'; i++)    {        serial_putc(x[i]);    }}
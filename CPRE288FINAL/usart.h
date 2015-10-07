/**
* @file usart.h
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
#ifndef USART_H
#define USART_H
    char USART_Receive();
    void usart_init();
    void serial_putc(char data);
    void string_tran(char x[]);
#endif
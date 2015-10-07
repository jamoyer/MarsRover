/**
* @file ping.c
* @brief Includes functions for using the ping sensor.
* Call ping_init() and then use getPingDistance() to
* get the distance from the ping sensor.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "lcd.h"
#include "open_interface.h"
#include "util.h"
#include "ping.h"

volatile unsigned int falling;
volatile unsigned int rising;
volatile unsigned int pingDone;
volatile unsigned int overflows;

#define SPEED_OF_SOUND 340
#define CLOCK_TIME .000004

/**
* Sends a ping and returns the distance.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
unsigned int getPingDistance()
{
    falling = 0;
    rising = 0;
    pingDone = 0;
    overflows = 0;
    unsigned int total =0;
    unsigned int distance =0;

    send_pulse();
    while(pingDone);
    total = overflows;
    total = total << 16;
    total += falling-rising;
    distance = (unsigned int) (total * CLOCK_TIME * SPEED_OF_SOUND * 100 *2);
    return distance;
}

/**
* Sends a pulse.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
void send_pulse()
{
    DDRD |= 0x10;           /// set PD4 as output
    PORTD |= 0x10;          /// set PD4 to high
    wait_ms(1);             /// wait
    PORTD &= 0xEF;          /// set PD4 to low
    DDRD &= 0xEF;           /// set PD4 as input
    TCCR1B = 0b11000011;    ///setting timer to capture rising edge and set prescaler to 64
    pingDone=1;             ///sets pingDone for use in the interrupt
}/**
* Initializes the ping sensor. Call this before using other functions
* in this file.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/void ping_init(){    ///sets timer and interrupts and disables A and C registers    TCCR1A = 0;
    TCCR1C = 0;    TIMSK |= 0b00100100;}
/**
* Detects events for the ping and records the timer value accordingly.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
ISR(TIMER1_CAPT_vect)
{
    ///detects ping being sent
    if(pingDone==1)
    {
        rising = ICR1;          ///stores the rising time
        pingDone = 2;           ///sets pingDone for use in next interrupt
        TCCR1B = 0b10000100;    ///sets register to detect falling edge
    }
    ///detects ping returning
    else if(pingDone ==2)
    {
        falling = ICR1;         ///stores the falling time
        pingDone=0;             ///sets pingDone for use in next pulse
    }
}

/**
* Counts the number of times the counter has overflowed.
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
ISR(TIMER1_OVF_vect)
{
    overflows++;
}
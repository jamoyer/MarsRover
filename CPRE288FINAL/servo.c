/**
* @file servo.c
* @brief  Includes functions related to the servo motor.
*         Call servo_init() before use.
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
#include "lcd.h"
#include "util.h"
#include "servo.h"

///Use CORRECTION to calibrate the servo motor's position for each robot, 
///if the robot is sent to 0 degrees but is actually a higher degree, make CORRECTION a lower value
///if the robot is sent to 0 degrees but is actually a lower degree, make CORRECTION a higher value
#define CORRECTION -100
#define MINIMUM 1200 + CORRECTION
#define MAXIMUM 4800
#define TOP 21500
#define WAIT_TIME 0

/**
* Initializes the servo motor.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
void servo_init()
{
    OCR3A = TOP-1;
    OCR3B = ((MAXIMUM-MINIMUM)/2)-1;
    TCCR3A = 0b00100011;    //sets toggle and sets wgm for fast PWM mode
    TCCR3B = 0b00011010;    //sets wgm for fast PWM mode and sets prescaler
    DDRE |= _BV(4);
}

/**
* Moves the servo motor to the specified degree.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
* @param degree From 0 to 180, the angle to position the servo motor.
* @date 12/13/2013
*/
void move_servo_by_degree(unsigned int degree)
{
    unsigned int pulse_width;
    
    pulse_width = (unsigned int)(MINIMUM+(MAXIMUM-MINIMUM)*(degree/180.0));
    
    OCR3B = pulse_width-1;

    wait_ms(WAIT_TIME);
}/**
* Moves the servo motor according to the counter. Not recommended for use.
* Use move_servo_by_degree() instead.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
* @param counter    This value moves the servo motor.
* @date 12/13/2013
*/void move_servo_by_counter(unsigned int counter){    OCR3B = counter-1;
    lprintf("%d",OCR3B);
    wait_ms(500);}
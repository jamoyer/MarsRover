/**
* @file servo.h
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
#ifndef SERVO_H
#define SERVO_H
    void servo_init();
    void move_servo_by_degree(unsigned int degree);
    void move_servo_by_counter(unsigned int counter);
#endif
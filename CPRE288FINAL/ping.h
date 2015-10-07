/**
* @file ping.h
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
#ifndef PING_C
#define PING_C
    void send_pulse();
    void ping_init();
    unsigned int getPingDistance();
#endif
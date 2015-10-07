/**
* @file ir.h
* @brief Includes functions for the IR sensor.
* Call ADC_init() first, then use getDist to get the distance from the
* IR sensor.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
#ifndef IR_H
#define IR_H
    void ADC_init();
    unsigned int ADC_read(char channel);
    int getAvgRead();
    unsigned int getDist();
#endif
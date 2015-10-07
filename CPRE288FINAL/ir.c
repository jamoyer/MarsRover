/**
* @file ir.c
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

#include <avr/io.h>
#include "lcd.h"
#include "util.h"
#include "ir.h"
#include <math.h>

/**
* Initializes the infrared Sensor.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
void ADC_init()
{
    // REFS=11, ADLAR=0, MUX don’t care
    ADMUX = _BV(REFS1) | _BV(REFS0);
    
    // ADEN=1, ADFR=0, ADIE=0, ADSP=111
    // others don’t care
    // See page 246 of user guide
    ADCSRA = _BV(ADEN) | (7<<ADPS0);
}

/**
* Returns the distance of the nearest object according to the IR sensor
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
unsigned int getDist()
{
    return (19437*(pow(getAvgRead(),-1.089)));
}

/**
* Gets the distance read from the ADCW register. For use within this file only.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
* @param channel    The channel to use.
* @date 12/13/2013
*/
unsigned int ADC_read(char channel)
{
    ADMUX |= (channel & 0x1F);
    ADCSRA |= _BV(ADSC);
    while (ADCSRA & _BV(ADSC))
    {}
    return ADCW;
}/**
* Averages 5 readings of ADC_read. For use within this file only.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/int getAvgRead(){    int numReadings = 5;    int waitTime = 25;    int total = 0;    for(int i=0;i<numReadings;i++){        total += ADC_read(2);        wait_ms(waitTime);    }    return total/numReadings;}
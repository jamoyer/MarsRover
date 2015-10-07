/**
* @file scan.c
* @brief Brings together the servo motor, ping sensor, USART, and IR sensor
* to a usable scan feature that scans a full 180 degree sweep in front of
* the servo and transmits the data over usart. Call scan_init() before 
* using full_scan().
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
#include "ir.h"
#include "servo.h"
#include "usart.h"
#include <math.h>

#define PI 3.141592653

typedef struct
{
    unsigned int angle;
    unsigned int width;
    unsigned int distance;
} object;

/**
* Initializes all things required for the fullScan function.
* Call this before using fullScan.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
void scan_init()
{
   servo_init();
   ADC_init();
   usart_init();
   ping_init();
}

/**
* Scans from 0 to 180 degrees using the both the IR sensor and the Ping sensor
* and sends the information back using usart.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
void fullScan()
{
    string_tran("Degrees\tIR Distance (cm)\tSonar Distance (cm)\n\r");
    
    unsigned int pings[90];
    unsigned int irs[90];
    char message[60]="";
    ///goes through and scans all ir and ping values at every 2 degrees
    ///prints them to putty
    for(int i=0; i<91;i++)
    {
        move_servo_by_degree(i*2);
        irs[i] = getDist();
        pings[i] = getPingDistance();
        sprintf(message,"\n%03d\t\t%03d\t\t%03d \r",i*2,irs[i],pings[i]);
        string_tran(message);
    }
    ///repositions the servo to 0 degrees
    move_servo_by_degree(0);
    wait_ms(400);
    
    object objects[20];
    for(int i=0;i<21;i++)
    {
        objects[i].width = 9999;
        objects[i].angle = 9999;
        objects[i].distance = 9999;
    }
    int j=0;
    ///determines where all the objects are in the previously scanned arrays
    ///stores the angle and the width of the objects into the "objects[]" array
    for(int i=3; i<91;i++)
    {
        ///finds an object within 500 cm of robot
        if(irs[i]<100)
        {
            int startIndex = i;
            ///continues until it finds the end edge of this object
            while(irs[i]<100)
            {
                i++;
            }
            int endIndex = i-1;
            
            if(endIndex-startIndex<2)
            {
                continue;
            }
            ///the objects angle is the middle angle of this object
            objects[j].angle=(endIndex+startIndex);
            int midIndex = (endIndex+startIndex)/2;
            int distance = pings[midIndex];
            objects[j].distance = distance;
            objects[j].width = (unsigned int) 2 * distance * tan((((endIndex-startIndex)*2*PI)/180.0)/2);
            j++;
        }
    }
    for(int i=0;i<j;i++)
    {
        char message[50];
        sprintf(message,"Object at Angle: %d, Width: %d, Distance: %d\n\r",objects[i].angle, objects[i].width, objects[i].distance);
        string_tran(message);
    }
    
}

/**
* Use this main to calibrate the correction value in the servo.c.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
* @param degree The position in degrees to move the servo to.
* @date 12/13/2013
*/
void calibrate_servo(int degree)
{
    move_servo_by_degree(degree);
    wait_ms(500);
}
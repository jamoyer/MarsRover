/**
* @file CPRE288FINAL.c
* @brief The main function runs the project and includes the main loop.
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
#include "scan.h"

#define FORWARD_DISTANCE 20
#define BACKWARD_DISTANCE -10
#define ROTATE_DEGREES 45

void initializer();
int sensors = 0;

/**
* The main loop which waits for commands via blue tooth and
* then acts based on commands received.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
void main()
{
    ///Initializes the open_interface struct to be used throughout the program.
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    initializer();
    char key =0;

    ///Waits for commands from the USART connection,
    ///Then performs the command and returns that the command was performed.
    while(1)
    {
        char message[32] = "";
        key = USART_Receive();
        
        ///Returns what the current tape sensor is reading.
        if (key == 'p')
        {
            oi_update(sensor_data);
            sprintf(message,"sensor->signal =%d\r\n",(int)sensor_data->cliff_frontleft_signal);
            string_tran(message);
        }
        
        ///Moves the servo motor to the 0 degree position.
        if(key == 'c')
        {
            calibrate_servo(0);
        }
        
        ///Scans 0 - 180 degrees in front of the robot and returns the readings,
        ///it also guesses where objects are and returns their angle and width.
        if(key == 'j')
        {
            fullScan();
            string_tran("Scan Complete.\r\n");
        }
        
        ///Moves FORWARD_DISTANCE centimeters forward.
        if(key =='w')
        {
            sprintf(message,"Moved %d\r\n",move(sensor_data, FORWARD_DISTANCE,&sensors));
            string_tran(message);
        }
        
        ///Moves BACKWARD_DISTANCE centimeters backwards.
        if(key=='s')
        {
            sprintf(message,"Moved %d\r\n",move(sensor_data, BACKWARD_DISTANCE,&sensors));
            string_tran(message);
        }
        
        ///Rotates ROTATE_DEGREES counterclockwise.
        if(key=='a')
        {
            turn_CCW(sensor_data,ROTATE_DEGREES);
            sprintf(message,"Rotated %d\r\n",ROTATE_DEGREES);
            string_tran(message);
        }
        
        ///Rotates ROTATE_DEGREES clockwise.
        if(key=='d')
        {
            turn_CCW(sensor_data,-ROTATE_DEGREES);
            sprintf(message,"Rotated %d\r\n",-ROTATE_DEGREES);
            string_tran(message);
        }
        
        ///Plays the Morrowind theme song.
        if(key=='r')
        {
            play_morrowind();
            string_tran("Playing song.");
        }            
    }
}

/**
* Initializes all sensors.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/
void initializer()
{
    scan_init();
    lcd_init();
}
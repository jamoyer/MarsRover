/**
* @file movement.c
* @brief Controls movement of the robot.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @date 12/13/2013
*/

#include "util.h"
#include "open_interface.h"
#include "movement.h"
#include <math.h>

#define MOVE_SPEED 200
#define TAPE_THRESHOLD 700
#define BACKWARD_DISTANCE -10

/**
* Moves the robot forward centimeters distance and stops and immediately backs up  if any sensor has been hit.
* Returns the distance the robot has traveled in centimeters.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
* @param *sensor    The robot struct with all the current data.
* @param centimeters    The distance to move the robot forward in centimeters.
* @param *sensors    Each bit in sensors corresponds to a sensor being triggered: bit 0: bumper_left, bit 1: bumper_right, bit 2: cliff_left, bit 3: cliff_frontleft, bit 4: cliff_frontright, bit 5: cliff_right
* @date 12/13/2013
*/
int move(oi_t *sensor, int centimeters, unsigned int* sensors)
{
    char stop = 0;                                        
    int sum= 0;
    ///Moves forward or backward depending on whether or not centimeters is positive or negative.
    if(centimeters>0)
    {
        ///Moves forward and continually checks to see if it has traveled the correct distance.
        oi_set_wheels(MOVE_SPEED, MOVE_SPEED);
        while (sum < (centimeters*10) && !stop)
        {
            oi_update(sensor);
            sum += sensor->distance;
            *sensors = 0;
            if (checksensors(sensor,sensors)) 
            {
                ///If sensors have been triggered, it moves BACKWARD_DISTANCE and updates sum accordingly.
                oi_set_wheels(0, 0);  
                move(sensor,BACKWARD_DISTANCE,sensors);
				sum += BACKWARD_DISTANCE*10;
                stop = 1;
                printSensors(sensors);
            }
        }
    }

    else if(centimeters<0)
    {
        oi_set_wheels(-MOVE_SPEED, -MOVE_SPEED);
        while (sum > (centimeters*10))
        {
            sum += (sensor->distance);
            oi_update(sensor);
        }
    }
    /// stop
    oi_set_wheels(0, 0);            
    return sum/10;
}

/**
* Updates sensors if any sensors have been triggered.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
* @param *sensor    The robot struct with all the current data.
* @param *sensors   Each bit in sensors corresponds to a sensor being triggered: bit 0:
                    bumper_left, bit 1: bumper_right, bit 2: cliff_left, bit 3: cliff_frontleft,
                    bit 4: cliff_frontright, bit 5: cliff_right, bits 6-9: Tape Sensors
* @date 12/13/2013
*/
int checksensors(oi_t *sensor, int * sensors)
{
    *sensors |= sensor->bumper_left;
    *sensors |= (sensor->bumper_right)<<1;
    *sensors |= (sensor->cliff_left)<<2;
    *sensors |= (sensor->cliff_frontleft)<<3;
    *sensors |= (sensor->cliff_frontright)<<4;
    *sensors |= (sensor->cliff_right)<<5;
    
    if(sensor->cliff_left_signal > TAPE_THRESHOLD)
    {
        *sensors |= 1<<6;
    }
    if(sensor->cliff_frontleft_signal > TAPE_THRESHOLD)
    {
        *sensors |= 1<<7;
    }
    if(sensor->cliff_frontright_signal > TAPE_THRESHOLD)
    {
        *sensors |= 1<<8;
    }
    if(sensor->cliff_right_signal > TAPE_THRESHOLD)
    {
        *sensors |= 1<<9;
    }
    
    return *sensors;
}

/**
* Displays which sensors have been triggered, if any.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
*
* @param *sensors   Each bit in sensors corresponds to a sensor being triggered: bit 0:
                    bumper_left, bit 1: bumper_right, bit 2: cliff_left, bit 3: cliff_frontleft,
                    bit 4: cliff_frontright, bit 5: cliff_right, bits 6-9: Tape Sensors
* @date 12/13/2013
*/
void printSensors(int * sensors)
{
    ///Bumper Left
    if(*sensors & 0b00000001)
    {
        string_tran("Bumper Left Tripped.\n\r");
    }
    
    ///Bumper Right
    if(*sensors & 0b00000010)
    {
        string_tran("Bumper Right Tripped.\n\r");
    }
    ///cliff left
    if(*sensors & 0b00000100)
    {
        string_tran("Cliff Left Tripped\n\r");
    }
    ///cliff front left
    if(*sensors & 0b00001000)
    {
        string_tran("Cliff Front Left Tripped\n\r");
    }
    ///cliff front right
    if(*sensors & 0b00010000)
    {
        string_tran("Cliff Front Right Tripped\n\r");
    }
    ///cliff right
    if(*sensors & 0b00100000)
    {
        string_tran("Cliff Right Tripped\n\r");
    }
    ///tape left
    if(*sensors & 0b01000000)
    {
        string_tran("Tape Left Tripped\n\r");
    }
    ///tape Front left
    if(*sensors & 0b10000000)
    {
        string_tran("Tape Front Left Tripped\n\r");
    }
    ///tape Front Right
    if(*sensors & 0b100000000)
    {
        string_tran("Tape Front Right Tripped\n\r");
    }
    ///tape Right
    if(*sensors & 0b1000000000)
    {
        string_tran("Tape Right Tripped\n\r");
    }
    string_tran("\n------------------------\n\r");
}

/**
* Updates sensors if any sensors have been triggered.
*
* @author Jacob Moyer,
*         Ed Droesch,
*         Aaron Pederson, &
*         Matthew Backes
* @param *sensor    The robot struct with all the current data.
* @param degrees     The number of degrees counterclockwise to turn the robot.
* @date 12/13/2013
*/
void turn_CCW(oi_t *sensor, int degrees)
{
    int total_angle = 0;
    /// 17/40 is calibration factor for robot 1
    /// 38/40 is calibration factor for robot 10
    degrees = (degrees * 38)/40;  
    if(degrees>0)
    {
        /// turn left full; turn opposite speed
        oi_set_wheels(MOVE_SPEED, -(MOVE_SPEED)); 
        while( total_angle < degrees)
        {
            oi_update(sensor);
            total_angle += sensor->angle;
        }
        /// stop
        oi_set_wheels(0, 0); 
    }
    
    else if(degrees<0){
        /// turn opposite; turn right full speed
        oi_set_wheels(-(MOVE_SPEED), MOVE_SPEED); 
        while( total_angle> degrees)
        {
            oi_update(sensor);
            total_angle += sensor->angle;
        }
        /// stop
        oi_set_wheels(0, 0); 
    }    
}
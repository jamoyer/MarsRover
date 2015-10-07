/**
* @file movement.h
* @brief Controls movement of the robot.
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
    move(oi_t *sensor, int centimeters, unsigned int* sensors);
    checksensors(oi_t *sensor, int * sensors);
    void printSensors(int * sensors);
    void turn_CCW(oi_t *sensor, int degrees);
#endif
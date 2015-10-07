/**
* @file scan.h
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
#ifndef SCAN_H_
#define SCAN_H_
    void scan_init();
    void fullScan();
    void calibrate_servo(int degree);
#endif
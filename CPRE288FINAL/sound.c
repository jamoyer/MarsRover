/**
* @file sound.c
* @brief Plays the theme song from "The Elder Scrolls III: Morrowind".
*
* @author Ed Droesch
*
* @date 12/13/2013
*/

#include "util.h"
#include "open_interface.h"
#include <avr/io.h>

void play_morrowind()
{
    oi_t* robot = oi_alloc();
    oi_init(robot);
 
    int length = 41;
    char notes[] =    {60,62,63,63,65,67,67,70,65,67,65,63,62,60,60,62,63,63,65,67,67,70,72,70,74,72,72,74,75,74,72,70,68,67,65,63,67,65,63,62,60};
    char durations[] = {24,24,96,24,24,96,24,24,72,12,12,24,24,96,24,24,96,24,24,96,24,24,96,36,12,96,36,12,48,48,48,48,48,48,96,24,24,96,24,24,144}; //1/64 sec
    
    oi_load_song(1,length, notes, durations);
    oi_play_song(1);
}
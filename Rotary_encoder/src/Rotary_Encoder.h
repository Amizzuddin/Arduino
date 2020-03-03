/*Rotary Encoder Library for arduino, Created by Amizzuddin, Oct 25 2019*/

#ifndef Rotary_Encoder_H
#define Rotary_Encoder_H

#include "Arduino.h"

class  Rotary_Encoder{
 public:
	/****************************************
     * This is initialize function 			*
     ****************************************/
    Rotary_Encoder(int CLK, int DT);
	
	
    /****************************************
     * This functions will return 			*
     * -1(knob = ~C/W) and 1(knob = C/W)	*
     ****************************************/
    byte ticks();

 private:
    int _clk, _dt;
	byte _read=0;
	byte _turn[2] = {0};				//0=CW & 1=ACW unsigned!
};

#endif
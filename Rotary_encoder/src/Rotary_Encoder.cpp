/*HCSR04(ultrasonic sensor) Library for arduino, Created by Amizzuddin, Oct 19 2019*/

#include "Arduino.h"
#include "Rotary_Encoder.h"

Rotary_Encoder::Rotary_Encoder(int CLK, int DT){
	_clk = CLK;
	_dt = DT;

	pinMode(_clk, INPUT);
    pinMode(_dt, INPUT);
}

byte Rotary_Encoder::ticks(){
	
	bool clkstate = digitalRead(_clk);
	bool dtstate = digitalRead(_dt);
	int motion = 0;							//clockwise = +1, a.clockwise = -1, no motion = 0
	//store the state (contains previous DT and CLK state (MSB) and current DT and CLK state (LSB)
	_read = (_read << 1) | clkstate;
	_read = (_read << 1) | dtstate;
	_read &= B1111;
	
	//compare the previous and current state
	byte test = ((_read & B00001100) >> 2) ^ (_read & B00000011);

	if( test != 0 ){												//as long there is change of state
		switch(_read){												//defines the type of motion
			case 7: case 1: case 8: case 14: motion=-1; break;
			case 11: case 2: case 4: case 13: motion=1; break;
		}
		if( motion < 0){
			_turn[1]++;
			if(_turn[0] > 0){
				_turn[0]--;
			}
		}
		if ( motion > 0){
			_turn[0]++;
			if(_turn[1] > 0){
				_turn[1]--;
			}
		}
		//check both turn for clockwise and ~clockwise state steps
		if( _turn[0] == 4 || _turn[1] == 4){				//if reach one cycle(4 state stae steps)
			_turn[0] = 0;
			_turn[1] = 0;
			return 1;
		}
		else{												//have not reach one cycle
			return 0;
		}
	}
	return 0;
}
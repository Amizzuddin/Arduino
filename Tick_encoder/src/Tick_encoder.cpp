/************************************************************************************************************************
 * This program is design for RACE curicullum                                                                  *
 * 1) Encoder wheel, 1 rotation = 20 ticks = 21cm = 210mm                                                                  *
 * 2)                                                 *
 * **********************************************************************************************************************/
#include <arduino.h>
#include "tick_encoder.h"

tick_encoder::tick_encoder(byte pin){
    _pin = pin;
}

void tick_encoder::initialize(){
    pinMode(_pin, INPUT);
    en_state = digitalRead(_pin) << 1;
    tick_state = (en_state == 0) ? 4 : 10;
    // Serial.print("Initial: ");
    // Serial.println(left_encoder.en_state, BIN);
}

byte tick_encoder::ticks(){
    en_state = (en_state & 0x0E) | digitalRead(_pin);
    if( ((en_state & 0x02) >> 1) != (en_state & 0x01) ){
        en_state <<= 1;
        // Serial.print(en_state, BIN);
        // Serial.print(",");
        if((en_state & 0x0E) == tick_state){
            return 1;
        }
        // else{
        //     //may want to add other statement to report half click
        // }
    }
    return 0;
}
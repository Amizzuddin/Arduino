/************************************************************************************************************************
 * This program is design for RACE curicullum                                                                  *
 * 1) Encoder wheel, 1 rotation = 20 ticks = 21cm = 210mm                                                                  *
 * 2)                                                 *
 * **********************************************************************************************************************/
#ifndef tick_encoder_H
#define tick_encoder_H

class tick_encoder{
    public:
        byte en_state = 0; //to store the state of the encoder

        /********************************************************
         * pin           encoder input pin                      *
         ********************************************************/
        tick_encoder(byte pin);

        /********************************************************
         * Initialize the pinMode of the encoder input          *
         ********************************************************/
        void initialize();

        /********************************************************
         * Return counts the number of successful ticks         *
         ********************************************************/
        byte ticks();

    private:
        byte _pin;  // memory to store the pin number
        byte tick_state = 0; //increment only en_state match with this state    
};
#endif
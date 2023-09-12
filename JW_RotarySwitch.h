#ifndef JW_ROTARYSWITCH_H
#define JW_ROTARYSWITCH_H

#include "Arduino.h"

#define JWRS_NONE       0x0
#define JWRS_CW         0x1
#define JWRS_CCW        0x2

#define JWRS_MULTIPLIER     0.75
#define JWRS_INVALID_POS    255


class JW_RotarySwitch
{
    public:
        JW_RotarySwitch(uint8_t, uint8_t, uint16_t);
        void init();
        void process();
        void resetState();
        bool IsCW(int, int);
        uint8_t findPosition(uint16_t);
        uint16_t readValAvg();

        uint8_t pin;
        uint8_t numpos;
        uint8_t position;
        uint8_t state;
        uint16_t value;
        uint16_t maxval;
        uint16_t segment;
        uint16_t tolerance;
};

#endif

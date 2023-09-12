#include "Arduino.h"
#include "JW_RotarySwitch.h"


JW_RotarySwitch::JW_RotarySwitch(uint8_t _pin, uint8_t _num, uint16_t _maxval) : pin { _pin }, numpos { _num }, maxval { _maxval }
{

}


void JW_RotarySwitch::init()
{
    pinMode(pin, INPUT_PULLUP);
    state = JWRS_NONE;
    segment = maxval / (numpos-1);
    tolerance = segment * JWRS_MULTIPLIER;
}


void JW_RotarySwitch::process()
{
    uint8_t oldpos = position, tmp;

    value = analogRead(pin);
    tmp = findPosition(value);
    if (tmp == JWRS_INVALID_POS) {
        return;
    }
    position = tmp;
    if (position != oldpos) {
        if (IsCW(oldpos, position)) {
            state = JWRS_CW;
        } else {
            state = JWRS_CCW;
        }
    }
}


bool JW_RotarySwitch::IsCW(int oldval, int newval)
{
    int MAX = numpos;
    int MID = numpos / 2;
    int old_max = ((oldval + MID) - (oldval + MAX)) % MAX;
    int old_new = (newval - (oldval + MAX)) % MAX;

    return (old_max <= MID) != (old_new > old_max);
}


uint8_t JW_RotarySwitch::findPosition(uint16_t _val)
{
  for (int i = 0; i < numpos; i++) {
    if (_val < (i*segment) + tolerance) {
      return i;
    }
  }
  return 0;
}


void JW_RotarySwitch::resetState()
{
    state = JWRS_NONE;
}


uint16_t JW_RotarySwitch::readValAvg()
{
    value = analogRead(pin);
    for(int i = 0; i < 100 ; i++) {
        value = (value + analogRead(pin)) / 2;
    }

    return value;
}

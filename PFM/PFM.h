#ifndef PFM_h
#define PFM_h
#include "Arduino.h"

static volatile int _counter;


class PFM
{
  private:
    int _pin;
    int _min;
    int _max;
    static void _intFunction();
    unsigned long _millisOld;
    int _valueC; // value send (coded)
    int _valueD; // value returned (decoded)
    int _valueOld;
    int _delta;
  public:
    PFM(int pin, int mode, int  min, int max); // CONSTRUCTOR
    void code(int value); // start code (modulation from 1024 to 6144 Hz)
    void codeStop(); // stop code
    void decodeReset(); // reset decode (pulses counter set to 0)
    int decode(); // read last decoded value (every 200ms library create new value)
    void update(); // refresh in loop
};
#endif

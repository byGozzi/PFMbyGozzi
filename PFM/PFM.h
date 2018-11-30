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
    PFM(int pin, int mode, int  min, int max);
    void code(int value);
    void codeStop();
    void decodeReset();
    int decode();
    void update();
};
#endif
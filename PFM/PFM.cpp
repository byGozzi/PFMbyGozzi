#include "PFM.h"

// CONSTRUCTOR
// PFM::PFM  (int pin, int mode, int min, int max)
// where  pin = pin used to code or decode (interrupt capable)
//        mode = 0 code ; mode = 1 decode (interrupt capable)
//        min = min value to code/decode
//        max = max value to code/decode
// decode -32000 if no connection
PFM::PFM(int pin, int mode, int  min, int max) // code->mode=0; decode->mode=1
{
  _pin = pin;
  _min = min; _max = max;
  // code (mode=0)
  if (mode == 0) {}
  // decode (mode=1)
  if (mode == 1) {
    // attachInterrupt(interrupt, intFunction, RISING);
    attachInterrupt(digitalPinToInterrupt(pin), _intFunction, RISING);
    // Serial.begin(9600);
    // Serial.println("OK");
    _counter = 0;
  }
}

void PFM::code(int value)
{
  if (value < _min)value = _min;
  if (value > _max)value = _max;
  int _valueC = map(value, _min, _max, 1024, 6144); // modulation from 1024 to 1024+(1024*5) Hz
  tone(_pin, _valueC);
}

void PFM::codeStop()
{
  noTone(_pin);
}

void PFM::decodeReset()
{
  _counter=0;
}


int PFM::decode()
{
  return _valueOld;//
}


void PFM::update()  
{
  // put it in loop ()
    int _delta = millis() - _millisOld; // read counter every 200ms
    if (_delta >= 200) {
    _millisOld = millis();
    _valueD = _counter * 5;
    _valueD = map(_valueD, 1024, 6144, _min, _max); // modulation from 1024 to 1024+(1024*5) Hz
   if (_counter==0) _valueD=-32000; // disconnected
    _valueOld = _valueD;
    _counter = 0;
  }
}

void PFM::_intFunction()
{
  _counter++;
}

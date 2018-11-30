/*
  Test library PFM byGozzi
  In Arduino Nano connect pin 13 (simulate code) and pin 2 (simulate decode)
  Range value 0-600
  Modulation from 1024 to 6144 Hz. Read counter every 200ms
*/

#include <PFM.h>
#include <Metro.h>

//PFM::PFM  (int pin, int mode, int min, int max)
// where  pin = pin used to code or decode (interrupt capable)
//        mode = 0 code ; mode = 1 decode (interrupt capable)
//        min = min value to code/decode
//        max = max value to code/decode
PFM myPFMcode(13, 0, 0, 600); // code
PFM myPFMdecode(2, 1, 0, 600); // decode

Metro secMetro(1000);
int temp = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("OK");
  myPFMcode.code(300);
  delay(1000);
  myPFMcode.codeStop();
  delay(1000);
  myPFMcode.code(300);
  delay(1000);
  myPFMcode.codeStop();
  myPFMcode.decodeReset();
}
void loop() {
  myPFMdecode.update();
  if (secMetro.check() == 1) {
    myPFMcode.code(temp); temp = temp + 10;
    if (temp > 600) temp = 1;
    Serial.println(myPFMdecode.decode());
  }
}

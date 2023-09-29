#include "SevSeg.h"

#define TIMER7S 250
#define BOMB_DEFAULT 8888

SevSeg sevseg; //Initiate a seven segment controller object

unsigned long timer7s = 0;
int value = BOMB_DEFAULT;

void setup() {
  // put your setup code here, to run once:
  byte numDigits = 4;  
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = 0; 
  // variable above indicates that 4 resistors were placed on the digit pins.
  // set variable to 1 if you want to use 8 resistors on the segment pins.
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() >= timer7s + TIMER7S){
    timer7s = millis();
    sevseg.setNumber(value, 0);
    
    value -= 1;
    if (0 == value) value = BOMB_DEFAULT;
  }

  sevseg.refreshDisplay(); // Must run repeatedly


}

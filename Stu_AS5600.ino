#include "Stu_AS5600_D.h"
#include <I2C.h>

Stu_AS5600 test;

void setup(){
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.print(F("Starting..."));
  test.begin();

  Serial.println(F("Done"));
}


void loop(){
  //Serial.print(test.getRawAngle(), BIN);
  //test.getRawAngle();
  switch(test.getAGC()){
      case MH:
        Serial.println(F("Magnet Too CLOSE!!!"));
        Serial.println();
        break;

      case ML:
        Serial.println(F("Magnet Too FAR!!!"));
        Serial.println();
        break;

      case MD:
        Serial.println(F("Magnet Detected"));
        Serial.print(F("Raw Angle: "));
        Serial.println(test.getRawAngle());
        Serial.print(F("Filtered Angle: "));
        Serial.println(test.getAngle());
        Serial.println();
        break;

      case READ_ERROR:
        Serial.println(F("READ ERROR!!!"));
        break;
  }

  //Serial.print(F(" , "));
  //Serial.println(test.getAngle(), BIN);
  delay(500);
}

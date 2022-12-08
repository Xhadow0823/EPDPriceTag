#include <Arduino.h>

inline void clearSerial1Buffer() {
  Serial1.flush(); while(Serial1.read()>= 0){}
}

//#define readS1WriteToS0_SHOWCODE

void readS1WriteToS0() {
  delay(100);
  bool first = true;
  Serial.print("> ");
  while(Serial1.available()) {
    char ch = Serial1.read();
    Serial.print( (char)ch );
    #ifdef readS1WriteToS0_SHOWCODE
      Serial.print( String('(') + (short)ch + String(") ") );
     #endif
  }
  Serial.println();
}
/**
 * EPDPriceTag
 * main.cpp
 * Eric W.
 * 2022.12.08
*/
#include <Arduino.h>
#include <epd.h>
// #include <defaultDemo.h>
#include <gvm.h>
#include <actionTable.h> // IMPORTANT

// Waveshare 4.3 UART EPD pin : LEONARDO pin  
// VCC:  5V
// GND:  GND
// RST:  3
// WAKE: 2
// DIN:  TX
// DOUT: RX

// Waveshare 4.3 UART EPD pin : ESP32-S3 pin  
// VCC:  3.3V
// GND:  GND
// RST:  3
// WAKE: 8
// DIN:  U1TX
// DOUT: U1RX

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  epd_init();
  epd_wakeup();
  epd_reset();
  epd_set_memory(MEM_NAND);
}


void loop() {
  Serial.println("GVM START");
  char rawCodingTable[] = "5 0 1 0 0 0 1 1 1 1 1 0 1 0 1 1 2 2 1 0 2 0 1 1 3 3 1 0 3 0 1 1 4 4 1 0 4 0 1 1 0 ";
  gvm( rawCodingTable );
  Serial.println("GVM DONE");

  static bool flag = 0;
  while (1) {
    digitalWrite(LED_BUILTIN, flag);
    flag = !flag;
    delay(500);
  }
}
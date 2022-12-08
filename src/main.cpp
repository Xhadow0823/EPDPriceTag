/**
 * EPDPriceTag
 * main.cpp
 * Eric W.
 * 2022.12.08
*/
#include <Arduino.h>
#include <epd.h>
#include <defaultDemo.h>

// Waveshare 4.3 UART EPD pin : LEONARDO pin  
// VCC:  5V
// GND:  GND
// RST:  3
// WAKE: 2
// DIN:  TX
// DOUT: RX

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  epd_init();
  epd_wakeup();
  epd_set_memory(MEM_TF);
  // epd_set_memory(MEM_NAND);
}

// 粗大的法國麵包
const unsigned char title[] = {0xB4,0xD6,0xB4,0xF3,0xB5,0xC4,0xB7,0xA8,0x87,0xF8,0xFC,0x49,0xB0,0xFC, '\0'};

void loop() {
  // put your main code here, to run repeatedly:
  epd_clear();
  // base_draw();

  epd_clear();
  epd_disp_bitmap("QR.BMP", 50, 200);
  epd_udpate();
  delay(3000);

  epd_set_memory(MEM_NAND);  // 要切換回來才可用GBK

  epd_set_color(BLACK, WHITE);
  epd_fill_rect(20, 20, 780, 160);

  epd_set_color(WHITE, BLACK);
  epd_set_ch_font(GBK64);
  epd_set_en_font(ASCII64);
  epd_disp_string(title, 50, 60);
  epd_udpate();
  delay(3000);


  epd_set_color(BLACK, WHITE);
  epd_set_ch_font(GBK48);
  epd_set_en_font(ASCII48);
  epd_disp_string("C8763C876300", 60, 500);
  epd_udpate();
  delay(1000);

  const unsigned char now[] = { 0xAC,0x46,0xD4,0xDA,0xD6,0xBB,0xD2,0xAA ,  '\0'};
  const unsigned char price[] = { 0x4E,0x54,0x24,0x33,0x2C,0x39,0x39,0x39, '\0'};
  epd_set_color(BLACK, WHITE);
  epd_set_ch_font(GBK64);
  epd_set_en_font(ASCII64);
  epd_disp_string(now, 500, 400);
  epd_disp_string(price, 540, 480);
  epd_udpate();
  delay(1000);
  

  epd_enter_stopmode();

  static bool flag = 0;
  while (1) {
    digitalWrite(LED_BUILTIN, flag);
    flag = !flag;
    delay(500);
  }
}
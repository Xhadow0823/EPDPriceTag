#include <Arduino.h>
#include <epd.h>

// ==================== GVM GLOBAL VARIABLE ====================
unsigned int a, b, c, d, e, f;
// ==================== GVM GLOBAL VARIABLE END ====================

// ==================== GVM CUSTOM ACTIONS ====================
// global variables
const unsigned char title[] = {0xB4,0xD6,0xB4,0xF3,0xB5,0xC4,0xB7,0xA8,0x87,0xF8,0xFC,0x49,0xB0,0xFC, '\0'};
const unsigned char snCode[] = "C8763C876300";
const unsigned char description[] = { 0xAC,0x46,0xD4,0xDA,0xD6,0xBB,0xD2,0xAA ,  '\0'};
const unsigned char priceText[] = { 0x4E,0x54,0x24,0x33,0x2C,0x39,0x39,0x39, '\0'};

void wakeUpEPD() {
  Serial.println("[wakeUpEPD]");
  epd_wakeup();
  delay(1000);
}

void fetchConfig() {
  Serial.println("[fetchConfig]");
  // OK
  // do nothing
  delay(1000);
}

// void updateEPD(unsigned int mode = 0) {
void updateEPD() {
  Serial.print("[updateEPD]");
  unsigned int mode = a;
  Serial.print(" mode = ");
  Serial.println(a);

  epd_set_memory(MEM_NAND);
  epd_clear();
  
  switch(mode) {
    case 0:
    {
      // draw title bar
      epd_set_color(BLACK, WHITE);
      epd_fill_rect(20, 20, 780, 160);
      // draw title text
      epd_set_color(WHITE, BLACK);
      epd_set_ch_font(GBK64);
      epd_set_en_font(ASCII64);
      epd_disp_string(title, 50, 60);
      // draw qr code
      epd_set_memory(MEM_TF);
      epd_disp_bitmap("QR.BMP", 50, 200);
      epd_set_memory(MEM_NAND);
      // draw SN code
      epd_set_color(BLACK, WHITE);
      epd_set_ch_font(GBK48);
      epd_set_en_font(ASCII48);
      epd_disp_string(snCode, 60, 500);
      // draw description
      epd_set_color(BLACK, WHITE);
      epd_set_ch_font(GBK64);
      epd_set_en_font(ASCII64);
      epd_disp_string(description, 500, 400);
      // draw price
      epd_disp_string(priceText, 540, 480);
    }
    break;
    case 1:
    {
      // draw title bar
      epd_set_color(BLACK, WHITE);
      epd_draw_rect(20, 20, 780, 160);
      // draw title text
      epd_set_color(BLACK, WHITE);
      epd_set_ch_font(GBK64);
      epd_set_en_font(ASCII64);
      const unsigned char title[] = {0xAC,0x46,0xD4,0xDA,0xCE,0xD2,0xD3,0xD0,0xB1,0xF9,0xE4,0xBF,0xC1,0xDC, '\0'};
      epd_disp_string(title, 170, 60);
      // draw xian zai wo you bing qi lin 
      epd_set_memory(MEM_TF);
      epd_disp_bitmap("ICECREAM.BMP", (800-712)/2, 200-20);
      delay(100);
    }
    break;
    case 2:
    {
      // draw banana.bmp
      epd_set_memory(MEM_TF);
      epd_disp_bitmap("BANANA.BMP", 0, 0);
      delay(100);
    }
    break;
  }

  epd_udpate();
  delay(1000);
}

void nextMode() {
  Serial.println("[nextMode]");
  a = (a+1)%3;
  delay(1000);
}

// void sleepEPD(int durationMin = 8 * 60) {
void sleepEPD() {
  Serial.print("[sleepEPD]");
  unsigned int durationS = 5;
  Serial.print(" duration = ");  Serial.println(durationS);

  // set some logics...
  epd_enter_stopmode();
  // REPLACE THE DELAY FUNCTION !!
  delay(durationS * 1000);
}
// ==================== GVM CUSTOM ACTIONS END ====================

unsigned int getFruitSayFruitReturn87(unsigned int fruit) {
    delay(1000);
    Serial.print("Fruit = ");  Serial.println(fruit);
    delay(3000);
    return (unsigned int)87;
}

unsigned int sayBeachReturn87(void) {
    a = 102;  b = 101;
    delay(1000);
    Serial.println("Beach");
    delay(3000);
    return (unsigned int)87;
}

//                      0          1            2          3         4           5                         6
void* actionTable[] = { wakeUpEPD, fetchConfig, updateEPD, nextMode, sleepEPD,   getFruitSayFruitReturn87, sayBeachReturn87 };
// /*********************************************************************************************************
// *
// * File                : Arduino-epd
// * Hardware Environment: 
// * Build Environment   : Arduino
// * Version             : V1.6.1
// * By                  : WaveShare
// *
// *                                  (c) Copyright 2005-2015, WaveShare
// *                                       http://www.waveshare.net
// *                                       http://www.waveshare.com
// *                                          All Rights Reserved
// * Modification By Eric W.  2022/11/14
// *********************************************************************************************************/

// #include "epd.h"
// #include "UI.h"
// #include <Arduino.h>
// #include "utilities.h"
// #include "defaultDemo.h"

// const int led = LED_BUILTIN;                           //user led

// void setup(void)
// {
//   pinMode(led, OUTPUT);
//   digitalWrite(led, LOW);
  
//   epd_init();
//   epd_wakeup();
//   epd_set_memory(MEM_NAND);

// }

// void loop(void)
// {
//   epd_clear();
//   // ItemList.draw();
//   // StatusBar.draw();
//   // ButtonPanel.draw();
//   // epd_udpate();
//   // delay(10000);

//   epd_clear();
  
//   static unsigned char color, bkColor;
//   color=DARK_GRAY;  bkColor=WHITE;
  
//   epd_set_color(color, bkColor);

//   static int l, r, t, b;
//   l=0; r=799; t=0; b=599;

// a4:
//   static int x0, x1, y0, y1;
//   x0=l; y0=t; x1=r; y1=b;

//   epd_draw_line(x0, y0, x1, y1);
//   delay(10);

//   x0=800-l; y0=b; x1=r; y1=t;

//   epd_draw_line(x0, y0, x1, y1);
//   delay(10);

//   // l=l+2;  t=t+2;  b=b-2;
//   l=l+5;  t; r; b=b-5;

//   if(l<599)
//     goto a4;
//   if(l>=599)
//     goto a9;

// a9:
//   epd_udpate();
  
//   // base_draw();
//   // draw_text_demo();
//   // draw_bitmap_demo();

//   epd_enter_stopmode();

//   char flag = 0;
//   while (1)
//   {
//     if(flag)
//     {
//       flag = 0;
//       digitalWrite(led, LOW);
//     }
//     else
//     {
//       flag = 1;
//       digitalWrite(led, HIGH);
//     }
//     delay(500);
//   }
// }

#include "epd.h"
#include <Arduino.h>

/*******************************************************************************
* Function Name  : void base_draw(void)
* Description    :
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void base_draw(void)
{
  int i, j;

  /*
  draw pixel
  */
  epd_set_color(BLACK, WHITE);  // fix black bg issue
  epd_clear();
  for (j = 0; j < 600; j += 50)
  {
    for (i = 0; i < 800; i += 50)
    {
      epd_draw_pixel(i, j);
      epd_draw_pixel(i, j + 1);
      epd_draw_pixel(i + 1, j);
      epd_draw_pixel(i + 1, j + 1);
    }
  }
  epd_udpate();
  delay(3000);

  /*
  draw line
  */
  epd_set_color(BLACK, WHITE);  // fix black bg issue
  epd_clear();
  for (i = 0; i < 800; i += 100)
  {
    epd_draw_line(0, 0, i, 599);
    epd_draw_line(799, 0, i, 599);
  }
  epd_udpate();
  delay(3000);

  /*
  fill rect
  */
  epd_set_color(BLACK, WHITE);  // fix black bg issue
  epd_clear();
  epd_set_color(BLACK, WHITE);
  epd_fill_rect(10, 10, 100, 100);

  epd_set_color(DARK_GRAY, WHITE);
  epd_fill_rect(110, 10, 200, 100);

  epd_set_color(GRAY, WHITE);
  epd_fill_rect(210, 10, 300, 100);

  epd_udpate();
  delay(3000);

  /*
  draw circle
  */
  epd_set_color(BLACK, WHITE);
  epd_clear();
  for (i = 0; i < 300; i += 40)
  {
    epd_draw_circle(399, 299, i);
  }
  epd_udpate();
  delay(3000);

  /*
  fill circle
  */
  epd_clear();
  for (j = 0; j < 6; j++)
  {
    for (i = 0; i < 8; i++)
    {
      epd_fill_circle(50 + i * 100, 50 + j * 100, 50);
    }
  }
  epd_udpate();
  delay(3000);

  /*
  draw triangle
  */
  epd_clear();
  for (i = 1; i < 5; i++)
  {
    epd_draw_triangle(399, 249 - i * 50, 349 - i * 50, 349 + i * 50, 449 + i * 50, 349 + i * 50);
  }
  epd_udpate();
  delay(3000);
}

void draw_text_demo(void)
{
  // char buff[] = {'G', 'B', 'K', '3', '2', ':', ' ', 0x8E, 0xD6, 0xC4, 0xE3, 0xC4, 0xEF, 0xca, 0xc0, 0xbd, 0xe7, 0};
  // epd_set_color(BLACK, WHITE);
  // epd_clear();
  // epd_set_ch_font(GBK32);
  // epd_set_en_font(ASCII32);
  // epd_disp_string(buff, 0, 50);
  // epd_disp_string("ASCII32: Hello, World!", 0, 300);

  // epd_set_ch_font(GBK48);
  // epd_set_en_font(ASCII48);
  // buff[3] = '4';
  // buff[4] = '8';
  // epd_disp_string(buff, 0, 100);
  // epd_disp_string("ASCII48: Hello, World!", 0, 350);

  // epd_set_ch_font(GBK64);
  // epd_set_en_font(ASCII64);
  // buff[3] = '6';
  // buff[4] = '4';
  // epd_disp_string(buff, 0, 160);
  // epd_disp_string("ASCII64: Hello, World!", 0, 450);


  epd_udpate();
  delay(3000);
}

void draw_bitmap_demo(void)
{
  epd_clear();
  epd_disp_bitmap("PIC4.BMP", 0, 0);
  epd_udpate();
  delay(5000);

  epd_clear();
  epd_disp_bitmap("PIC2.BMP", 0, 100);
  epd_disp_bitmap("PIC3.BMP", 400, 100);
  epd_udpate();
  delay(5000);

  epd_clear();
  epd_disp_bitmap("PIC7.BMP", 0, 0);
  epd_udpate();
}
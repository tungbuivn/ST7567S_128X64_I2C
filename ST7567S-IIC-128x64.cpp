#include "ST7567S-IIC-128x64.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

ST7567S_IIC::ST7567S_IIC(uint16_t w, uint16_t h) : GFXcanvas1(w, h)
{
 
}
void ST7567S_IIC::render()
{

  for (int row = 0; row < HEIGHT / 8; row++)
  {
    WriteByte_command(0xb0 + row);
    WriteByte_command(0x00);
    WriteByte_command(0x10);
    for (int col = 0; col < WIDTH; col++)
    {
      WriteByte_dat(buffer[row * WIDTH + col]); // row=bit0--bit7, display off
    }
  }
}

/******************************************
 * Write a command to LCD.
 * Define instructions on page 23 of the ST7567A data sheet.
 *******************************************/
void ST7567S_IIC::WriteByte_command(int dat)
{
  Wire.beginTransmission(addr); // transmit to device 0x3f
  Wire.write(0x00);             // Co=0,A0=0. data= Co-A0-0-0-0-0-0-0.
  Wire.write(dat);              // sends restart command.
  Wire.endTransmission();       // stop transmitting
}

/******************************************
 * Init the LCD.
 * This initialization function is called when using LCD.
 *******************************************/

void ST7567S_IIC::Init()
{
  Wire.begin();

  delay(10);

  WriteByte_command(0xE2); // Internal reset
  delay(10);
  WriteByte_command(0xA2); // 0xa2 LCD bias ratio is 1/9; 0xa3 is bias ratio 1/7; 128X64=1/9

  //// normal screen
  WriteByte_command(0xA0); //(0xa0-0xa1 is ADC direction selection) 0xa0 is segment forward, 0xa1 is segment reverse
  WriteByte_command(0xC8); // com output mode drive direction is reverse
  //// flip screen
  // WriteByte_command(0xA1);    // may be bug, loss first 4 bits in each row
  // WriteByte_command(0xC0);

  // WriteByte_command(0xA7);    // 0xA6 Normal, 0xA7 Inverse

  //********Adjust display brightness********
  WriteByte_command(0x25); // 0x20-0x27 is the internal Rb/Ra resistance adjustment setting of V5 voltage RR=4.5V
  // WriteByte_command(0x24);    // only 0x25 and 0x24 is ok
  WriteByte_command(0x81); // Electricity Mode Settings
  WriteByte_command(0x20);

  WriteByte_command(0x2C); // Internal Power Supply Control Mode
  WriteByte_command(0x2E);
  WriteByte_command(0x2F);
  // Clear(false);                        //initalize DDRAM

  WriteByte_command(0xAF);
  WriteByte_command(0x40);
}

/******************************************
 * Write a data to LCD.
 * Define instructions on page 23 of the ST7567A data sheet.
 *******************************************/
void ST7567S_IIC::WriteByte_dat(int dat)
{
  Wire.beginTransmission(addr); // transmit to device 0x7e
  Wire.write(0x40);             // Co=0,A0=1. data= Co-A0-0-0-0-0-0-0.
  Wire.write(dat);              // sends data.
  Wire.endTransmission();       // stop transmitting
}

void ST7567S_IIC::drawPixel(int16_t x, int16_t y, uint16_t color)
{

  if (buffer)
  {
    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
      return;
    int16_t t;
    switch (rotation)
    {
    case 1:
      t = x;
      x = WIDTH - 1 - y;
      y = t;
      break;
    case 2:
      x = WIDTH - 1 - x;
      y = HEIGHT - 1 - y;
      break;
    case 3:
      t = x;
      x = y;
      y = HEIGHT - 1 - t;
      break;
    }

    int paging = (y / 8);
    int ny = y & 7;
    int bytePos = paging * WIDTH + x;
    if (bytePos < WIDTH * HEIGHT)
    {
      int b = buffer[bytePos];
      int v = (color ? 0 : 1) << (7 - ny);
      if (v != 0)
        b = b | 1 << (ny);
      else
        b = b & (0xFF ^ (1 << (ny)));

      buffer[bytePos] = b;
    }
  }
}

void ST7567S_IIC::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
  for (int i = 0; i < w; i++)
  {
    drawPixel(x + i, y, color);
  }
}
void ST7567S_IIC::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
  for (int i = 0; i < h; i++)
  {
    drawPixel(x, y + i, color);
  }
}

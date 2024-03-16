/******************************
 * original code from
 * URL: https://github.com/mworkfun/ST7567A_128X32DOT_LCD
 * 
 *  
 * Modify for LCD ST7567S 128x64
 * screen:
 * x-----------------------> +
 * y                    |
 * |                    |
 * |---------------------
 * | 
 * v +
 *  
 ******************************/
#ifndef ST7567S_IIC_128x64_H
#define ST7567S_IIC_128x64_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>


class ST7567S_IIC:public GFXcanvas1 {
  public:
   ST7567S_IIC(uint16_t w, uint16_t h);
  
    // LCD is driven by ST7567A IC.
    // Define instructions on page 37 of the ST7567A data sheet.
    enum ST7567A_C {
      displayON  = 0xaf,  //display on.
      displayOFF = 0xae,  //display off.
      
      startLine  = 0x40,  //Set display start line.
      restart    = 0xe2,  //restart command.
      seg        = 0xa0,  //Set scan direction of SEG, SEG = 1-0-1-0-0-0-0-MX; 
                          //MX=1-->reverse direction, MX=0-->normal direction.

      INV_normal = 0xa6,  //normal display.
      AP_normal  = 0xa4,  //normal display.
      
      BS         = 0xa3,  //select bias setting, bias = 1-0-1-0-0-0-1-BS, BS(0)=1/9,  BS(1)=1/7(at 1/65 duty).
      com        = 0xc8,  //Set output direction of COM, COM = 1-1-0-0-MY-X-X-X;
                          //MY=1-->reverse direction, MY=0-->normal direction.
                          
      powerCon1  = 0x2c,  //Controls the built-in power circuits;
      powerCon2  = 0x2e,  //Define instructions on page 43 of the ST7567A data sheet.
      powerCon3  = 0x2f,

      /********Adjust display brightness********/
      regRatio   = 0x22,  //Controls the regulation ratio of the built-in regulator;
                          //Define instructions on page 43 of the ST7567A data sheet.
      EV1        = 0x81,  //Define instructions on page 44 of the ST7567A data sheet.
      EV2        = 0x30,  

      /**********entension command set**********/
      exit_EC    = 0xfe,  //exit extension command set.
      enter_EC   = 0xff,  //enter extension command set.

      DSM_ON     = 0x72,  //display setting mode on.
      DSM_OFF    = 0x70,  //display setting mode off.
      DT         = 0xd6,  //set the display duty, DT=33.
      BA         = 0x90,  //BA=1/9, selects LCD bias ratio for the internal voltage follower to drive the LCD. 
                          //This command has priority over the Bias Select (BS).
      FR         = 0x9d,  //specifies the frame rate for duty.

      RMW        = 0xe0,  //Read-modify-Write command on page 42 of ST7567A datasheet.
      END        = 0xee,
    };
    
    
    void WriteByte_command(int dat);      //Write a command to LCD.
    void WriteCont_command(int str[]);    //Continuously write commands to LCD.
    void Init();                          //This initialization function is called when using LCD.
    void WriteByte_dat(int dat);          //Write a data to RAM.
    void WriteCont_dat(int str[]);        //Continuously write data to RAM.
   
    // override adafruit function
    void render();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void drawFastHLine(int16_t x, int16_t y, int16_t w,
                                  uint16_t color) ;
    void drawFastVLine(int16_t x, int16_t y, int16_t h,
                                  uint16_t color);
   
  private:
    int addr = 0x3f;  //Address of LCD device.
   
};

#endif

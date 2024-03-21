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

#include "ST7567S-IIC-128x64.h"

#include <GFX_fonts/arial6pt7b.h>
GFXfont font=arial6pt7b;
//create an lcd object.
ST7567S_IIC Lcd;



/////////////////////////////////////////////////////////
void setup() {
  delay(2000)
  Lcd.Init();
   
  Lcd.fillScreen(0xff);
  Lcd.setRotation(0);
  Lcd.setFont(&font);
  Lcd.drawRect(10,10,50,30,1);
  // Lcd.drawPixel(1,1,1);
  Lcd.setCursor(0,font.yAdvance);
  Lcd.drawCircle(64,32,10,1);
  Lcd.print(F("Xin Chao")); 

  Lcd.render();
}

/////////////////////////////////////////////////////////
void loop() {

  

}

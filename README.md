# ST7567S_128X64_I2C on STM32
I2C communication protocol, used to drive the ST7567S 128*64 pixels LCD. 



<img src="doc/128X64_I2C_ST7567S_back.png" style="max-width: 25%;">

## references

|                       |                                                                                                                                    |
|-----------------------|------------------------------------------------------------------------------------------------------------------------------------|
| font custom           | https://tchapi.github.io/Adafruit-GFX-Font-Customiser/                                                                             |
| adafruit gfx          | https://github.com/adafruit/Adafruit-GFX-Library                                                                                   |
| font convert from ttf | offline tool: https://github.com/adafruit/Adafruit-GFX-Library/tree/master/fontconvert<br>online tool:https://rop.nl/truetype2gfx/ | 




2024/03/18:
  - This code tested on STM31F01CCU
  - Refactor code to use adafruit_gfx library

2022-05-28
  - correct bug in "ClearPixel"
  - import DrawLine, draw_circle_section and draw_circle from U8G2 (https://github.com/olikraus/u8g2)


original code from  https://github.com/mworkfun/ST7567A_128X32DOT_LCD

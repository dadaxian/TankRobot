#include <Adafruit_NeoPixel.h>




#pragma once
#include <c:\Program Files (x86)\Arduino\libraries\Adafruit_NeoPixel-master\Adafruit_NeoPixel.h>





void setRed();

void setPurple();

void setGreen();

void setYellow();

void setOrange();

void Led_init();

void setColor(uint8_t r, uint8_t g, uint8_t b);

void setColor(uint8_t color);

void setBlink(uint8_t r, uint8_t g, uint8_t b, uint16_t blinkTime, uint16_t delayTime);
void setBlink(uint8_t color, uint16_t blinkTime, uint16_t delayTime);

#include"led.h"
#include "Arduino.h"
#include "ColorJudge.h"

int ledPin = 49;

Adafruit_NeoPixel *pixels;

void setRed()
{
	pixels->setPixelColor(0, 255, 0, 0);
	pixels->show();
}
void setPurple()
{
	pixels->setPixelColor(0, 255, 0, 255);
	pixels->show();
}
void setGreen()
{
	pixels->setPixelColor(0, 0, 255, 0);
	pixels->show();
}
void setYellow()
{
	pixels->setPixelColor(0, 255, 255, 0);
	pixels->show();
}
void setOrange()
{
	pixels->setPixelColor(0, 255, 128, 43);
	pixels->show();
}


void Led_init()
{

	pixels = new Adafruit_NeoPixel(1, ledPin, NEO_GRB + NEO_KHZ800);
	pixels->begin();

	setRed();
	delay(10);
	setPurple();
	delay(10);
	setGreen();
	delay(10);
	setOrange();
	delay(10);
	setYellow();
	delay(10);

	Serial3.println("LED init success!");
}
void setColor(uint8_t r, uint8_t g, uint8_t b)
{
	pixels->setPixelColor(0, r, g, b);
	pixels->show();
}
void setColor(uint8_t color)
{
	switch (color)
	{

	case RED:
		setColor(255, 0, 0);
		break;
	case White:
		setColor(255, 255, 255);
		break;
	case Green:
		setColor(0, 255, 0);
		break;
	default:
		break;

	}
}
void setBlink(uint8_t r, uint8_t g, uint8_t b, uint16_t blinkTime, uint16_t delayTime = 50)
{
	for (int i = 0; i < blinkTime; i++)
	{
		setColor(r, g, b);
		delay(delayTime);
		setColor(0, 0, 0);
		delay(delayTime);
	}
}
void setBlink(uint8_t color, uint16_t blinkTime, uint16_t delayTime = 50)
{
	for (int i = 0; i < blinkTime; i++)
	{
		setColor(color);
		delay(delayTime);
		setColor(0, 0, 0);
		delay(delayTime);
	}
}

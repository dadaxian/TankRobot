#include "arduino.h"
#include "keyBoard.h"
#include "GearMotor.h"
#include "led.h"
#include "ColorJudge.h"
uint8_t startFlag = 0;
//注册识别目标颜色
void ColorReg()
{
	printdbg("testing");
	unsigned char res = Tsc230::rgbTestWay2();

	aimColor = res;

	delay(100);
	setColor(res);
	delay(500);

	setBlink(res, 10, 20);
}
void KeyboardServe()
{
	int count = 0;
	while (count<10000)
	{
		count++;
		SetSpeed(0, 0);
		setGreen();
		delay(1);
		setRed();
		if (digitalRead(46) == 0)
		{
			while (digitalRead(46) == 0);
			setBlink(Green, 10, 30);

			startFlag = 1;
			break;

		}
		if (digitalRead(47) == 0)
		{
			while (digitalRead(47) == 0);
			setBlink(255, 255, 255, 5, 30);
			ColorReg();
			break;

		}
		if (digitalRead(48) == 0)
		{

		}


	}
}
void keyboard_init()
{

	Serial3.println("keyboard init success!");

	pinMode(19, INPUT_PULLUP);
	attachInterrupt(4, KeyboardServe, FALLING);

	pinMode(46, INPUT_PULLUP); //yellow
	pinMode(47, INPUT_PULLUP);//red
	pinMode(48, INPUT_PULLUP);//orange


}

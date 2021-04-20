#include "ColorJudge.h"
#include "arduino.h"
#include "MyMath.h"
#include "led.h"
#include "GearMotor.h"

int S0 = 36;//S0 S1 LL ???  LH 2%
int S1 = 37;//      HL 20%   HH 100%
int S2 = 38;//S2 S3 LL ???  LH ??? 
int S3 = 39;//      HL ??    HH ???
int OUT = 20;//??????????
int CSRGB = 0;//?????????????
int RGB[3] = { 0,0,0 };//??????????
int r, g, b;
unsigned char currentColor;//µ±Ç°ÑÕÉ«
unsigned char aimColor = RED;

Tsc230::Tsc230() {
	pinMode(S0, INPUT);
	pinMode(S1, INPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);
	pinMode(OUT, INPUT);
	attachInterrupt(5, rgbInterrupt, FALLING);
	outStrength(100);
	Serial3.println("TSC230 init Success!");
}

int  nothing(int x)
{
	if (Lcurrentspeed == 10086)
	{
		Serial3.print("fuck");
	}
	return 0;
}

void Tsc230::outStrength(int outStrength)//???¡Â????
{
	switch (outStrength)
	{
	case 0:
		digitalWrite(S0, LOW);
		digitalWrite(S1, LOW);
		break;
	case 2:
		digitalWrite(S0, LOW);
		digitalWrite(S1, HIGH);
		break;
	case 20:
		digitalWrite(S0, HIGH);
		digitalWrite(S1, LOW);
		break;
	case 100:
		digitalWrite(S0, HIGH);
		digitalWrite(S1, HIGH);
		break;
	default:
		digitalWrite(S0, LOW);
		digitalWrite(S1, LOW);
		break;
	}
}

void Tsc230::rgbTestWay1()
{
	CSRGB = 0;
	digitalWrite(S2, LOW);//???????????
	digitalWrite(S3, LOW);
	int ar = micros();
	ResetRGB();
	while (RGB[CSRGB] < 255) {
		Serial.print("");
	}
	ar = micros() - ar;
	Serial.print("R:");
	Serial.print(ar);

	CSRGB = 1;
	digitalWrite(S2, HIGH);//????????????
	digitalWrite(S3, HIGH);
	int ag = micros();
	ResetRGB();
	while (RGB[CSRGB] < 255) {
		Serial.print("");
	}
	ag = micros() - ag;
	Serial.print("G:");
	Serial.print(ag);

	CSRGB = 2;
	digitalWrite(S2, LOW);//????????????
	digitalWrite(S3, HIGH);
	int aB = micros();
	ResetRGB();
	while (RGB[CSRGB] < 255) {
		Serial.print("");
	}
	aB = micros() - aB;
	Serial.print("B:");
	Serial.println(aB);

	delay(1000);
}

unsigned char Tsc230::rgbTestWay2()
{
	int SumR = 0;
	int SumG = 0;
	int SumB = 0;
	for (int rgbtime = 0; rgbtime < 5; rgbtime++) {
		CSRGB = 0;
		digitalWrite(S2, LOW);//???????????
		digitalWrite(S3, LOW);
		ResetRGB();
		delay(10);
		r = RGB[CSRGB];// *0.3643;//0.3643=255/?????????r? ???
		feedshit(r);


		CSRGB = 1;
		digitalWrite(S2, HIGH);//??????????
		digitalWrite(S3, HIGH);
		ResetRGB();
		delay(10);
		g = RGB[CSRGB];
		feedshit(g);

		CSRGB = 2;
		digitalWrite(S2, LOW); //????????????
		digitalWrite(S3, HIGH);
		ResetRGB();
		delay(10);
		b = RGB[CSRGB]; // *0.255;
		feedshit(b);
		SumR += r;
		SumG += g;
		SumB += b;
	}



	int colorarray[3];
	colorarray[0] = r;
	colorarray[1] = g;
	colorarray[2] = b;

	for (int i = 0; i < 3; i++)
	{
		printval(colorarray[i]);
	}

	int max = getmax(colorarray, 3);
	int colorarrayRemaped[3];
	for (int i = 0; i < 3; i++)
	{
		colorarrayRemaped[i] = remap(colorarray[i], 0, max, 0, 255);
		printval(colorarrayRemaped[i]);
	}

	setColor(colorarrayRemaped[0], colorarrayRemaped[1], colorarrayRemaped[2]);





	if (r / (float)g > 1.7) {
		currentColor = RED;
		printdbg("Red");
		return RED;
	}
	if (SumG * 2 < SumB) {
		currentColor = White;
		printdbg("White");
		return White;
	}
	if (SumG * 2 > SumB) {
		currentColor = Green;
		printdbg("Green");
		return Green;
	}



}

void Tsc230::rgbInterrupt()
{
	RGB[CSRGB]++;
}

void Tsc230::ResetRGB()
{
	for (int i = 0; i < 3; i++)
		RGB[i] = 0;
}

bool Tsc230::isAimColor() {
	//Serial.println("color is ");
	for (int i = 0; i < 5; i++)
		rgbTestWay2();
	if (currentColor == aimColor)
		return 1;
	return 0;
}

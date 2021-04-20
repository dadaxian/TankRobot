#ifndef COLORJUDGE_H
#define COLORJUDGE_H

#define printval(x) Serial3.print(#x":\t"); Serial3.println(x);
#define printdbg(x) Serial3.println(x);

#include <MsTimer2.h>
#define IsRED 1.2<EigenValue<1.8
#define IsGreen  1.8<EigenValue
#define IsWhite EigenValue<1.2

#define RED 0x01
#define Green 0x02
#define Blue 0x03
#define White 0x04

extern int S0;//S0 S1 LL ???  LH 2%
extern int S1;//      HL 20%   HH 100%
extern int S2;//S2 S3 LL ???  LH ??? 
extern int S3;//      HL ??    HH ???
extern int OUT;//??????????
extern int CSRGB;//?????????????
extern int RGB[3];//??????????
extern int r, g, b;
extern unsigned char currentColor;//µ±Ç°ÑÕÉ«
extern unsigned char aimColor;
//#define __DEBUG

#ifdef __DEBUG
#define printf(x)  Serial.print(__LINE__);	Serial.print( " "#x":"); Serial.println(x);
#endif
#ifndef __DEBUG
#define feedshit(x) nothing(x);
#endif

#ifdef __DEBUG
#define printArs(x)  Serial.print(__LINE__);	Serial.print( " "#x":"); Serial.println(x);
#endif
#ifndef __DEBUG
#define printArs(x)  Serial.print(__LINE__);	Serial.print( " "#x":"); Serial.println(x);
#endif

int nothing(int x);

class Tsc230 {
public:
	Tsc230();

	static void outStrength(int outStrength);

	static void rgbTestWay1();

	static unsigned char rgbTestWay2();

	static void rgbInterrupt();

	static void ResetRGB();

	static bool isAimColor();
};



#endif
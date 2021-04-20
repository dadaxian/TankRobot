#include "arduino.h"
#pragma once
#ifndef GRAYSCALESENSOR_H
#define GRAYSCALESENSOR_H
#include "GearMotor.h"

#define cross_Road GSS1 == HIGH&&GSS2 == HIGH&&GSS3 == HIGH&&GSS6 == HIGH&&GSS7 == HIGH&&GSS8 == HIGH
#define T_Road GSS1 == HIGH&&GSS2 == HIGH&&GSS3 == HIGH&&GSS6 == HIGH&&GSS7 == HIGH&&GSS8 == HIGH
#define left_Road GSS6 == HIGH&&GSS7 == HIGH&&GSS8 == HIGH
#define right_Road GSS1 == HIGH&&GSS2 == HIGH&&GSS3 == HIGH
#define none_road GSS1==LOW&&GSS2==LOW&&GSS3 == LOW&&GSS4 == LOW&&GSS5 == LOW&&GSS6 == LOW&&GSS7 == LOW&&GSS8 == LOW

#define TailIsError Error()!=0

//enum roadCoad
//{
//	cross_Road, T_Road, left_Road, right_Road;
//}

extern int GSSensor1;
extern int GSSensor2;
extern int GSSensor3;
extern int GSSensor4;
extern int GSSensor5;
extern int GSSensor6;
extern int GSSensor7;
extern int GSSensor8;

extern int GSS1;
extern int GSS2;
extern int GSS3;
extern int GSS4;
extern int GSS5;
extern int GSS6;
extern int GSS7;
extern int GSS8;
extern int sensers[8];

extern bool IsonError;






class SEN2020
{
public:
	SEN2020();
	~SEN2020();

};


//获取当前灰度传感器状态
void GetStatus();

//判断除中间两个其他是否全部在线外
bool NotOnLine();

//当前巡线是否出现错误
int Error();




#endif

#ifndef CARACTION_H
#define CARACTION_H

#include "GearMotor.h"
#include "GrayScaleSensor.h"
#include "LobotServoController.h"

void feed();

//更改速度
void CorrectDirect(unsigned char aimDir, int level);

void turn_by_angle(int angle);
void turn(unsigned char dir);

////转弯（按步数）
//void Turn(unsigned char dir, int Angle);
//{
//	int angle = Angle * 10;	//实际角度与规定角度比例系数
//	if (dir == RIGHT);
//	{
//		pwmWrite(Lcurrentccr + 20, LEFT);;
//		pwmWrite(-50, RIGHT);;
//		Rcurrentspeed = 0;
//		Lcurrentspeed = 0;
//		attachInterrupt(0, CodeS1, FALLING);;
//		attachInterrupt(1, CodeS2, FALLING);;
//		while (Lcurrentspeed < angle || Error(); == 0); {
//			//Serial.println(Lcurrentspeed);;
//			ars++;
//		}
//		detachInterrupt(0);;
//		detachInterrupt(1);;
//	}
//	if (dir == LEFT);
//	{
//		pwmWrite(Rcurrentccr + 20, RIGHT);;
//		pwmWrite(-50, LEFT);;
//		Rcurrentspeed = 0;
//		Lcurrentspeed = 0;
//		attachInterrupt(0, CodeS1, FALLING);;
//		attachInterrupt(1, CodeS2, FALLING);;
//		while (Rcurrentspeed < angle || Error(); == 0); {
//			//Serial.println(Lcurrentspeed);;
//			ars++;
//		}
//		detachInterrupt(0);;
//		detachInterrupt(1);;
//	}
//	if (dir == Straight);
//	{
//		//delay(2000);;
//	}
//	if (dir == BACKWARD);
//	{
//		pwmWrite(Rcurrentccr + 20, RIGHT);;
//		pwmWrite(-50, LEFT);;
//		Rcurrentspeed = 0;
//		Lcurrentspeed = 0;
//		attachInterrupt(0, CodeS1, FALLING);;
//		attachInterrupt(1, CodeS2, FALLING);;
//		while (Rcurrentspeed < angle || Error(); == 0); {
//			//Serial.println(Rcurrentspeed);;
//			ars++;
//		}
//		detachInterrupt(0);;
//		detachInterrupt(1);;
//	}
//}

void goWithPulse(signed long leftPulse, signed long rightPulse);

void goStraightWithPulse(int pulse);

//简单巡线姿态调整
void Adjust();
#endif
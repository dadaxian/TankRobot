#ifndef CARACTION_H
#define CARACTION_H

#include "GearMotor.h"
#include "GrayScaleSensor.h"
#include "LobotServoController.h"

void feed();

//�����ٶ�
void CorrectDirect(unsigned char aimDir, int level);

void turn_by_angle(int angle);
void turn(unsigned char dir);

////ת�䣨��������
//void Turn(unsigned char dir, int Angle);
//{
//	int angle = Angle * 10;	//ʵ�ʽǶ���涨�Ƕȱ���ϵ��
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

//��Ѳ����̬����
void Adjust();
#endif
#pragma once
#ifndef GearMotor_H
#define GearMotor_H

#include "MsTimer2.h"

#define FORWARD 0x01
#define BACKWARD 0x00
#define STOP 0x04

#define RIGHT 0x01
#define LEFT 0x02
#define Straight 0x03
#define ALL 0x00

//�������Ż���
extern int ars ;

//�����������ӿڲ���
extern int inPwm1;//i1;��ǰ  ��֮ �Һ�
extern int inPwm2;
extern int inPwm3;//i3;��ǰ  ��֮ ���
extern int inPwm4;
extern int ENr;
extern int ENl;


//�������ӿ�
extern int LS1 ;
extern int RS1;

//��¼�ٶ�
extern int Rcurrentspeed;	
extern int Lcurrentspeed ;

//pwm���
extern int Rcurrentccr ;
extern int Lcurrentccr;

//�ٶȼ�¼�˲�����
extern bool avaFlag;//ƽ��ֵ��ǩ 1 ��2�� 0 ��һ��
extern int Rspeed ;//ƽ��ֵ
extern int Lspeed ;

//Ŀ���ٶ�
extern int RaimRpm;
extern int LaimRpm;
#define LIMIT(x,min,max) (x>max)?(x=max):((x<min)?(x=min):x)
void SetSpeed( int  left,  int right);

//�������
void pwmWrite( int value, unsigned char LOR);

//�ⲿ�жϷ����� 
void CodeS2();

void CodeS1();


//PID
extern float Rkp ;         //����ϵ�� �ӿ�ϵͳ����Ӧ
extern float Rki ;
extern float Rkd ;


extern double Rerror;
extern float RlastError ;
extern float RSUM ;


extern float RPout;
extern float RIout;
extern float RDout;
//extern float CurrentVol;
extern float Rk_out ;


void RpidControl();


extern float Lkp ;          //����ϵ�� �ӿ�ϵͳ����Ӧ
extern float Lki ;
extern float Lkd ;


extern double Lerror;
extern float LlastError ;
extern float LSUM ;


extern float LPout;
extern float LIout;
extern float LDout;
//extern float CurrentVol;
extern float Lk_out ;


void LpidControl();

void Tick();


class GearMotor
{
public:
	GearMotor();

	static void Move();

	static void Stop();

	static void setAimSpeed( int aimSpeedL,  int aimSpeedR);

	static void open_PID();
	
	static void close_PID();
};



#endif
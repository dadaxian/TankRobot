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

//编译器优化项
extern int ars ;

//电机驱动外设接口参数
extern int inPwm1;//i1;右前  反之 右后
extern int inPwm2;
extern int inPwm3;//i3;左前  反之 左后
extern int inPwm4;
extern int ENr;
extern int ENl;


//编码器接口
extern int LS1 ;
extern int RS1;

//记录速度
extern int Rcurrentspeed;	
extern int Lcurrentspeed ;

//pwm输出
extern int Rcurrentccr ;
extern int Lcurrentccr;

//速度记录滤波参数
extern bool avaFlag;//平均值标签 1 第2次 0 第一次
extern int Rspeed ;//平均值
extern int Lspeed ;

//目标速度
extern int RaimRpm;
extern int LaimRpm;
#define LIMIT(x,min,max) (x>max)?(x=max):((x<min)?(x=min):x)
void SetSpeed( int  left,  int right);

//电机操作
void pwmWrite( int value, unsigned char LOR);

//外部中断服务函数 
void CodeS2();

void CodeS1();


//PID
extern float Rkp ;         //比例系数 加快系统的响应
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


extern float Lkp ;          //比例系数 加快系统的响应
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
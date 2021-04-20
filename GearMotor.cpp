#include "arduino.h"
#include "GearMotor.h"

//编译器优化项
int ars = 0;

//电机驱动外设接口参数
int inPwm1 = 24; //i1=0;i2=1;右前  反之 右后
int inPwm2 = 25;
int inPwm3 = 23; //i3=0;i4=1;左前  反之 左后
int inPwm4 = 22;
int ENr = 5;
int ENl = 4;


//编码器接口
int LS1 = 2;
int RS1 = 3;

//记录速度
int Rcurrentspeed = 0;
int Lcurrentspeed = 0;

//pwm输出
int Rcurrentccr = 80;
int Lcurrentccr = 81;

//速度记录滤波参数
bool avaFlag = 0;//平均值标签 1 第2次 0 第一次
int Rspeed = 0;//平均值
int Lspeed = 0;

//目标速度
int RaimRpm = 0;
int LaimRpm = 0;
#define LIMIT(x,min,max) (x>max)?(x=max):((x<min)?(x=min):x)
void SetSpeed(int  left, int right)
{
	LIMIT(left, -255, 255);
	LIMIT(right, -255, 255);

	if (left>0)
	{
		digitalWrite(inPwm3, LOW);
		digitalWrite(inPwm4, HIGH);
	}
	else
	{
		digitalWrite(inPwm3, HIGH);
		digitalWrite(inPwm4, LOW);
		left = -left;
	}

	if (right>0)
	{
		digitalWrite(inPwm1, LOW);
		digitalWrite(inPwm2, HIGH);
	}
	else
	{
		digitalWrite(inPwm1, HIGH);
		digitalWrite(inPwm2, LOW);
		right = -right;
	}

	analogWrite(ENr, right);
	analogWrite(ENl, left);
}

//电机操作
void pwmWrite(int value, unsigned char LOR)
{
	if (value>0)
	{
		if (LOR == RIGHT)
		{
			digitalWrite(inPwm1, LOW);
			digitalWrite(inPwm2, HIGH);
			analogWrite(ENr, value);
		}
		else if (LOR == LEFT)
		{
			digitalWrite(inPwm3, LOW);
			digitalWrite(inPwm4, HIGH);
			analogWrite(ENl, value);
		}
		else if (LOR == ALL)
		{
			digitalWrite(inPwm1, LOW);
			digitalWrite(inPwm2, HIGH);
			digitalWrite(inPwm3, LOW);
			digitalWrite(inPwm4, HIGH);
			analogWrite(ENr, value);
			analogWrite(ENl, value);
		}
	}
	else if (value<0)
	{
		if (LOR == RIGHT)
		{
			digitalWrite(inPwm1, HIGH);
			digitalWrite(inPwm2, LOW);
			analogWrite(ENr, -value);
		}
		else if (LOR == LEFT)
		{
			digitalWrite(inPwm3, HIGH);
			digitalWrite(inPwm4, LOW);
			analogWrite(ENl, -value);
		}
		else
		{
			digitalWrite(inPwm1, HIGH);
			digitalWrite(inPwm2, LOW);
			digitalWrite(inPwm3, HIGH);
			digitalWrite(inPwm4, LOW);
			analogWrite(ENr, -value);
			analogWrite(ENl, -value);
		}
	}
	else if (-value == 0)
	{
		if (LOR == RIGHT)
		{
			digitalWrite(inPwm1, LOW);
			digitalWrite(inPwm2, LOW);
			analogWrite(ENr, -value);
		}
		else if (LOR == LEFT)
		{
			digitalWrite(inPwm3, LOW);
			digitalWrite(inPwm4, LOW);
			analogWrite(ENl, -value);
		}
		else
		{
			digitalWrite(inPwm1, LOW);
			digitalWrite(inPwm2, LOW);
			digitalWrite(inPwm3, LOW);
			digitalWrite(inPwm4, LOW);
			analogWrite(ENr, -value);
			analogWrite(ENl, -value);
		}
	}
}

//外部中断服务函数 
void CodeS2()
{
	Rcurrentspeed++;

}

void CodeS1()
{
	Lcurrentspeed++;

}


//PID
float Rkp = 0.6;         //比例系数 加快系统的响应
float Rki = 0.30;
float Rkd = 0.8;

double Rerror;
float RlastError = 0;
float RSUM = 0;


float RPout;
float RIout;
float RDout;
//float CurrentVol;
float Rk_out = 20;


void RpidControl()
{
	Rerror = RaimRpm - Rspeed;
	RPout = Rkp*Rerror;
	RSUM += Rerror;
	RIout = Rki*RSUM;
	RDout = Rkd*(Rerror - RlastError);

	RlastError = Rerror;

	Rcurrentccr = RPout + RIout + RDout;// +Rk_out;// +50;
	if (Rcurrentccr < 0) Rcurrentccr = 0;
	if (Rcurrentccr > 255) Rcurrentccr = 255;

	pwmWrite(Rcurrentccr, RIGHT);
}


float Lkp = 0.6;          //比例系数 加快系统的响应
float Lki = 0.30;
float Lkd = 0.8;

double Lerror;
float LlastError = 0;
float LSUM = 0;


float LPout;
float LIout;
float LDout;
//float CurrentVol;
float Lk_out = 20;


void LpidControl()
{
	Lerror = LaimRpm - Lspeed;
	LPout = Lkp*Lerror;
	LSUM += Lerror;
	LIout = Lki*LSUM;
	LDout = Lkd*(Lerror - LlastError);

	LlastError = Lerror;

	Lcurrentccr = LPout + LIout + LDout;// +Rk_out;// +50;
	if (Lcurrentccr < 0) Lcurrentccr = 0;
	if (Lcurrentccr > 255) Lcurrentccr = 255;

	pwmWrite(Lcurrentccr, LEFT);
}

void Tick()
{
	Serial.print("R:");
	Serial.print(Rcurrentspeed);
	Serial.print("L:");
	Serial.println(Lcurrentspeed);
	//if (avaFlag == 1)
	//{
	//	Rspeed += Rcurrentspeed;//算右边两次和
	//	Rspeed /= 2;

	//	//Serial.println(Rspeed); //输出右边速度

	//	//Serial.print(",");

	//	Lspeed += Lcurrentspeed;
	//	Lspeed /= 2;

	//	//Serial.println(Lspeed);
	//	RpidControl();
	//	LpidControl();

	//	Rspeed = 0;
	//	Lspeed = 0;

	//	avaFlag = 0;
	//}

	//if (avaFlag == 0)
	//{
	//	Rspeed += Rcurrentspeed;
	//	Lspeed += Lcurrentspeed;
	//	avaFlag = 1;
	//}

}



GearMotor::GearMotor() {
	//电机驱动初始化
	pinMode(inPwm1, OUTPUT);
	pinMode(inPwm2, OUTPUT);
	pinMode(inPwm3, OUTPUT);
	pinMode(inPwm4, OUTPUT);
	pinMode(ENr, OUTPUT);
	pinMode(ENl, OUTPUT);
	digitalWrite(ENr, LOW);
	digitalWrite(ENl, LOW);
}

void GearMotor::Move()
{
	pwmWrite(Lcurrentccr, LEFT);
	pwmWrite(Rcurrentccr, RIGHT);
}

void GearMotor::Stop()
{
	pwmWrite(0, ALL);
}

void GearMotor::setAimSpeed(int aimSpeedL, int aimSpeedR)
{
	RaimRpm = aimSpeedR;
	LaimRpm = aimSpeedL;
}

void GearMotor::open_PID() {
	attachInterrupt(0, CodeS1, FALLING);
	attachInterrupt(1, CodeS2, FALLING);
	//MsTimer2::set(1000, Tick);
	//MsTimer2::start();
}

void GearMotor::close_PID() {
	//detachInterrupt(0);
	//detachInterrupt(1);
	MsTimer2::stop();
}


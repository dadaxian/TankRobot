#include "carAction.h"
#include "GearMotor.h"
#include "GrayScaleSensor.h"
#include "LobotServoController.h"
extern int LStraightSpeed;
extern int RStraightSpeed;

void feed()
{
	if (Lcurrentspeed < -1)
	{
		Serial.print("  ");
	}
}

//更改速度
void CorrectDirect(unsigned char aimDir, int level)
{
	int pwmInL;
	int pwmInR;
	if (aimDir == RIGHT)
	{
		pwmInL = Lcurrentccr + level * 5;
		pwmInR = Rcurrentccr;// -level * 1;
		LIMIT(pwmInL, 0, 200);;
		LIMIT(pwmInR, 0, 200);
		//close_PID();
		pwmWrite(pwmInL, LEFT);
		pwmWrite(pwmInR, RIGHT);
		//open_PID();
	}
	if (aimDir == LEFT)
	{
		pwmInR = Rcurrentccr + level * 5;
		pwmInL = Lcurrentccr;// -level * 1;
		LIMIT(pwmInL, 0, 150);;
		LIMIT(pwmInR, 0, 150);
		//close_PID();
		pwmWrite(pwmInR, RIGHT);
		pwmWrite(pwmInL, LEFT);
		//open_PID();
	}
}

void turn_by_angle(int angle) {//右为正
	int turnSpeed = 80;
	int RanglePulse;
	int LanglePulse;
	int a;
	if (angle >= 0) {
		RanglePulse = (angle / 90.0) * 399;
		LanglePulse = (angle / 90.0) * 454;
		pwmWrite(turnSpeed, LEFT);
		pwmWrite(-turnSpeed, RIGHT);
		Rcurrentspeed = 0;
		Lcurrentspeed = 0;
		attachInterrupt(0, CodeS1, FALLING);
		attachInterrupt(1, CodeS2, FALLING);
		while (Lcurrentspeed < LanglePulse && Rcurrentspeed<RanglePulse) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		if (Lcurrentspeed < LanglePulse) {
			a = LanglePulse - Lcurrentspeed;
			pwmWrite(turnSpeed, LEFT);
		}

		else
		{
			a = Lcurrentspeed - LanglePulse;
			pwmWrite(-turnSpeed, LEFT);
		}

		Lcurrentspeed = 0;

		while (Lcurrentspeed < a) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		if (Rcurrentspeed < RanglePulse) {
			a = RanglePulse - Rcurrentspeed;
			pwmWrite(turnSpeed, RIGHT);
		}

		else
		{
			a = Rcurrentspeed - RanglePulse;
			pwmWrite(-turnSpeed, RIGHT);
		}
		Rcurrentspeed = 0;
		while (Rcurrentspeed < a) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		//detachInterrupt(0);
		//detachInterrupt(1);
	}
	else
	{
		RanglePulse = (-angle / 90.0) * 417;
		LanglePulse = (-angle / 90.0) * 377;
		pwmWrite(turnSpeed, RIGHT);
		pwmWrite(-turnSpeed, LEFT);
		Rcurrentspeed = 0;
		Lcurrentspeed = 0;
		attachInterrupt(0, CodeS1, FALLING);
		attachInterrupt(1, CodeS2, FALLING);
		while (Lcurrentspeed < LanglePulse && Rcurrentspeed<RanglePulse) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		if (Lcurrentspeed < LanglePulse) {
			a = LanglePulse - Lcurrentspeed;
			pwmWrite(turnSpeed, LEFT);
		}

		else
		{
			a = Lcurrentspeed - LanglePulse;
			pwmWrite(-turnSpeed, LEFT);
		}
		Lcurrentspeed = 0;
		while (Lcurrentspeed < a) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		if (Rcurrentspeed < RanglePulse) {
			a = RanglePulse - Rcurrentspeed;
			pwmWrite(turnSpeed, RIGHT);
		}

		else
		{
			a = Rcurrentspeed - RanglePulse;
			pwmWrite(-turnSpeed, RIGHT);
		}
		Rcurrentspeed = 0;
		while (Rcurrentspeed < a) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		//detachInterrupt(0);
		//detachInterrupt(1);
	}
}

void turn(unsigned char dir)
{
	int RanglePulse;
	int LanglePulse;
	int a;
	switch (dir)
	{
	case RIGHT:
		RanglePulse = 414;
		LanglePulse = 562;
		pwmWrite(100, LEFT);
		pwmWrite(-100, RIGHT);
		Rcurrentspeed = 0;
		Lcurrentspeed = 0;
		attachInterrupt(0, CodeS1, FALLING);
		attachInterrupt(1, CodeS2, FALLING);
		while (Lcurrentspeed < LanglePulse && Rcurrentspeed<RanglePulse) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		if (Lcurrentspeed < LanglePulse) {
			a = LanglePulse - Lcurrentspeed;
			pwmWrite(80, LEFT);
		}

		else
		{
			a = Lcurrentspeed - LanglePulse;
			pwmWrite(-80, LEFT);
		}

		Lcurrentspeed = 0;

		while (Lcurrentspeed < a) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		if (Rcurrentspeed < RanglePulse) {
			a = RanglePulse - Rcurrentspeed;
			pwmWrite(80, RIGHT);
		}

		else
		{
			a = Rcurrentspeed - RanglePulse;
			pwmWrite(-80, RIGHT);
		}
		Rcurrentspeed = 0;
		while (Rcurrentspeed < a) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		//detachInterrupt(0);
		//detachInterrupt(1);
		break;
	case LEFT:
		RanglePulse = 503;
		LanglePulse = 503;
		pwmWrite(90, RIGHT);
		pwmWrite(-100, LEFT);
		Rcurrentspeed = 0;
		Lcurrentspeed = 0;
		attachInterrupt(0, CodeS1, FALLING);
		attachInterrupt(1, CodeS2, FALLING);
		while (Lcurrentspeed < LanglePulse && Rcurrentspeed<RanglePulse) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		if (Lcurrentspeed < LanglePulse) {
			a = LanglePulse - Lcurrentspeed;
			pwmWrite(80, LEFT);
		}

		else
		{
			a = Lcurrentspeed - LanglePulse;
			pwmWrite(-80, LEFT);
		}
		Lcurrentspeed = 0;
		while (Lcurrentspeed < a) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		if (Rcurrentspeed < RanglePulse) {
			a = RanglePulse - Rcurrentspeed;
			pwmWrite(80, RIGHT);
		}

		else
		{
			a = Rcurrentspeed - RanglePulse;
			pwmWrite(-80, RIGHT);
		}
		Rcurrentspeed = 0;
		while (Rcurrentspeed < a) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		//detachInterrupt(0);
		//detachInterrupt(1);
		break;
	case BACKWARD:
		RanglePulse = 795;
		LanglePulse = 985;
		attachInterrupt(0, CodeS1, FALLING);
		attachInterrupt(1, CodeS2, FALLING);
		Rcurrentspeed = 0;
		Lcurrentspeed = 0;
		pwmWrite(-100, RIGHT);
		pwmWrite(100, LEFT);


		while (Lcurrentspeed < LanglePulse && Rcurrentspeed<RanglePulse) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		if (Lcurrentspeed < LanglePulse) {
			a = LanglePulse - Lcurrentspeed;
			pwmWrite(80, LEFT);
		}

		else
		{
			a = Lcurrentspeed - LanglePulse;
			pwmWrite(-80, LEFT);
		}
		Lcurrentspeed = 0;
		while (Lcurrentspeed < a) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		if (Rcurrentspeed < RanglePulse) {
			a = RanglePulse - Rcurrentspeed;
			pwmWrite(80, RIGHT);
		}

		else
		{
			a = Rcurrentspeed - RanglePulse;
			pwmWrite(-80, RIGHT);
		}
		Rcurrentspeed = 0;
		while (Rcurrentspeed < a) {
			Serial.print(ars);
		}
		pwmWrite(0, ALL);
		//detachInterrupt(0);
		//detachInterrupt(1);
		break;
	case Straight:
		break;
	case STOP:
		while (true)
		{
			pwmWrite(0, ALL);
		}
	default:
		break;
	}

}

////转弯（按步数）
//void Turn(unsigned char dir, int Angle)
//{
//	int angle = Angle * 10;	//实际角度与规定角度比例系数
//	if (dir == RIGHT)
//	{
//		pwmWrite(Lcurrentccr + 20, LEFT);
//		pwmWrite(-50, RIGHT);
//		Rcurrentspeed = 0;
//		Lcurrentspeed = 0;
//		attachInterrupt(0, CodeS1, FALLING);
//		attachInterrupt(1, CodeS2, FALLING);
//		while (Lcurrentspeed < angle || Error() == 0) {
//			//Serial.println(Lcurrentspeed);
//			ars++;
//		}
//		detachInterrupt(0);
//		detachInterrupt(1);
//	}
//	if (dir == LEFT)
//	{
//		pwmWrite(Rcurrentccr + 20, RIGHT);
//		pwmWrite(-50, LEFT);
//		Rcurrentspeed = 0;
//		Lcurrentspeed = 0;
//		attachInterrupt(0, CodeS1, FALLING);
//		attachInterrupt(1, CodeS2, FALLING);
//		while (Rcurrentspeed < angle || Error() == 0) {
//			//Serial.println(Lcurrentspeed);
//			ars++;
//		}
//		detachInterrupt(0);
//		detachInterrupt(1);
//	}
//	if (dir == Straight)
//	{
//		//delay(2000);
//	}
//	if (dir == BACKWARD)
//	{
//		pwmWrite(Rcurrentccr + 20, RIGHT);
//		pwmWrite(-50, LEFT);
//		Rcurrentspeed = 0;
//		Lcurrentspeed = 0;
//		attachInterrupt(0, CodeS1, FALLING);
//		attachInterrupt(1, CodeS2, FALLING);
//		while (Rcurrentspeed < angle || Error() == 0) {
//			//Serial.println(Rcurrentspeed);
//			ars++;
//		}
//		detachInterrupt(0);
//		detachInterrupt(1);
//	}
//}
int leftOffset = 0;
int rightOffset = 0;

void goWithPulse(signed long leftPulse, signed long rightPulse)
{
	leftPulse += leftOffset;
	rightPulse += rightOffset;

	int leftSpeed, rightSpeed;
	leftSpeed = rightSpeed = 100;
	if (leftPulse<0)
	{
		leftSpeed = -leftSpeed;
		leftPulse = -leftPulse;
	}
	if (rightPulse<0)
	{
		rightSpeed = -rightSpeed;
		rightPulse = -rightPulse;
	}

	Rcurrentspeed = 0;
	Lcurrentspeed = 0;
	attachInterrupt(0, CodeS1, FALLING);
	attachInterrupt(1, CodeS2, FALLING);
	bool leftFlag = 1;
	bool rightFlag = 1;
	while (leftFlag || rightFlag)
	{
		if (Lcurrentspeed >leftPulse)
		{
			leftFlag = 0;
		}
		if (Rcurrentspeed >rightPulse)
		{
			rightFlag = 0;
		}
		if (leftFlag)
		{
			pwmWrite(leftSpeed, LEFT);
		}
		else
		{
			pwmWrite(0, LEFT);
		}
		if (rightFlag)
		{
			pwmWrite(rightSpeed, RIGHT);
		}
		else
		{
			pwmWrite(0, RIGHT);
		}
		Serial3.print("left:");
		Serial3.print(Lcurrentspeed);

		Serial3.print("right:");
		Serial3.println(Rcurrentspeed);

	}

	if (Rcurrentspeed - rightPulse>3)
	{

		pwmWrite(-rightSpeed, RIGHT);

	}

	if (Lcurrentspeed - leftPulse>3)
	{

	}

	leftOffset = leftPulse - Lcurrentspeed;
	rightOffset = rightPulse - Rcurrentspeed;

	Serial3.print("leftoffset:");
	Serial3.print(leftOffset);

	Serial3.print("rightoffset:");
	Serial3.println(rightOffset);
}

void goStraightWithPulse(int pulse) {
	int a;
	int dirIndex;
	if (pulse < 0)
		dirIndex = -1;
	else
	{
		dirIndex = 1;
	}
	pwmWrite(LStraightSpeed * dirIndex, LEFT);
	pwmWrite(RStraightSpeed * dirIndex, RIGHT);
	Rcurrentspeed = 0;
	Lcurrentspeed = 0;
	attachInterrupt(0, CodeS1, FALLING);
	attachInterrupt(1, CodeS2, FALLING);
	while (Lcurrentspeed < pulse || Rcurrentspeed<pulse) {
		Serial.print(ars);
	}
	pwmWrite(0, ALL);

	if (Lcurrentspeed < pulse) {
		a = pulse - Lcurrentspeed;
		pwmWrite(80 * dirIndex, LEFT);
	}
	else
	{
		a = Lcurrentspeed - pulse;
		pwmWrite(-80 * dirIndex, LEFT);
	}

	Lcurrentspeed = 0;
	while (Lcurrentspeed < a) {
		Serial.print(ars);
	}
	pwmWrite(0, ALL);

	if (Rcurrentspeed < pulse) {
		a = pulse - Rcurrentspeed;
		pwmWrite(80 * dirIndex, RIGHT);
	}
	else
	{
		a = Rcurrentspeed - pulse;
		pwmWrite(-80 * dirIndex, RIGHT);
	}

	Rcurrentspeed = 0;
	while (Rcurrentspeed < a) {
		Serial.print(ars);
	}
	pwmWrite(0, ALL);

	//detachInterrupt(0);
	//detachInterrupt(1);
}

//简单巡线姿态调整
void Adjust() {
	//中间检测
	if (GSS4 == LOW&&GSS5 == HIGH&&NotOnLine() == 1) {//亮绿灯 绿布 low
		CorrectDirect(LEFT, 20);//*5 中右边离线 往右修正
		return;
	}

	if (GSS5 == LOW&&GSS4 == HIGH&&NotOnLine() == 1) {
		CorrectDirect(RIGHT, 20);//中左边离线 往左修正
		return;
	}

	//中两侧检测
	if (GSS3 == HIGH)
	{
		//myGearMotor.CorrectDirect(RIGHT, 9);
		pwmWrite(Lcurrentccr + 40, LEFT);
		pwmWrite(-80, RIGHT);
		return;
	}
	if (GSS6 == HIGH)
	{
		//myGearMotor.CorrectDirect(LEFT, 9);
		pwmWrite(Rcurrentccr + 40, RIGHT);
		pwmWrite(-80, LEFT);
		return;
	}
	if (GSS2 == HIGH) {
		pwmWrite(Lcurrentccr + 20, LEFT);
		pwmWrite(-60, RIGHT);
		return;
	}
	if (GSS7 == HIGH)
	{
		//myGearMotor.CorrectDirect(LEFT, 9);
		pwmWrite(Rcurrentccr + 20, RIGHT);
		pwmWrite(-60, LEFT);
		return;
	}
}
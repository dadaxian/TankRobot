
#include"GrayScaleSensor.h"

int GSSensor1 = 26;
int GSSensor2 = 27;
int GSSensor3 = 28;
int GSSensor4 = 29;
int GSSensor5 = 30;
int GSSensor6 = 31;
int GSSensor7 = 32;
int GSSensor8 = 33;

int GSS1;
int GSS2;
int GSS3;
int GSS4;
int GSS5;
int GSS6;
int GSS7;
int GSS8;
int sensers[8];


SEN2020::SEN2020()
{
	pinMode(GSSensor1, INPUT);
	pinMode(GSSensor2, INPUT);
	pinMode(GSSensor3, INPUT);
	pinMode(GSSensor4, INPUT);
	pinMode(GSSensor5, INPUT);
	pinMode(GSSensor6, INPUT);
	pinMode(GSSensor7, INPUT);
	pinMode(GSSensor8, INPUT);
	Serial3.println("SEN2020 init success!");
}

SEN2020::~SEN2020()
{
}

//获取当前灰度传感器状态
void GetStatus()
{
	sensers[0] = GSS1 = digitalRead(GSSensor1);
	sensers[1] = GSS2 = digitalRead(GSSensor2);
	sensers[2] = GSS3 = digitalRead(GSSensor3);
	sensers[3] = GSS4 = digitalRead(GSSensor4);
	sensers[4] = GSS5 = digitalRead(GSSensor5);
	sensers[5] = GSS6 = digitalRead(GSSensor6);
	sensers[6] = GSS7 = digitalRead(GSSensor7);
	sensers[7] = GSS8 = digitalRead(GSSensor8);
}

//判断除中间两个其他是否全部在线外
bool NotOnLine()
{
	if (GSS1 == LOW&&
		GSS2 == LOW&&
		GSS3 == LOW&&
		GSS6 == LOW&&
		GSS7 == LOW&&
		GSS8 == LOW
		)
		return 1;
	else
	{
		return 0;
	}
}

//当前巡线是否出现错误
int Error() {
	GetStatus();
	if (GSS1 == LOW&&
		GSS2 == LOW&&
		GSS3 == LOW&&
		GSS4 == HIGH&&//中右
		GSS5 == HIGH&&//中左
		GSS6 == LOW&&
		GSS7 == LOW&&
		GSS8 == LOW
		)
		return 0;
	else if (cross_Road)
		return 6;
	else if (T_Road)
	{
		return 5;
	}
	else if (left_Road) {
		return 4;
	}
	else if (right_Road) {
		return 3;
	}
	else if (none_road)
	{
		return 2;
	}
	else
		return 1;
}



bool IsonError = 0;


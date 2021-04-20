#pragma once
#include "arduino.h"
#include "HC_SR04.h"
#include"MyMath.h"

HC_SR04::HC_SR04(int trigPin, int echoPin) {
	this->echoPin = echoPin;
	this->trigPin = trigPin;
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
}
int HC_SR04::getDistance()
{
	//begin:

	// 产生一个10us的高脉冲去触发TrigPin
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	// 检测脉冲宽度，并计算出距离
	distance = pulseIn(echoPin, HIGH) * 10 / 58;
	//if (distance >= 20000)
	//	goto begin;
	return distance;
}
int HC_SR04::getDistanceAfterFilter(int item)
{
	int getDistanceAfterFilter_val = Moving_Median_int(distance, item);
	return getDistanceAfterFilter_val;
}

int HC_SR04::getDistanceAfterFilter() {
	int gdaVal;
	for (int getDA_i = 0; getDA_i < 10; getDA_i++) {
		gdaVal = Moving_Median_int(getDistance(), 1);
	}
	return gdaVal;
}


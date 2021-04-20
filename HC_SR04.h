#pragma once
class HC_SR04
{
public:
	HC_SR04(int trigPin, int echoPin);
	int getDistance();
	int getDistanceAfterFilter(int item);

	int getDistanceAfterFilter();

	int trigPin;
	int echoPin;
	int distance;//µ¥Î»MM


};

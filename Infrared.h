#ifndef INFRARED_H
#define INFRARED_H

#include "MyMath.h"
class Infrared{
public:
	Infrared(int pin);
	void test();
	int ValAfterFilter();
	 int Ain;

};




#endif

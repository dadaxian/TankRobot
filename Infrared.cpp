#include "Arduino.h"

#include "Infrared.h"



Infrared::	Infrared(int pin)
	{
		Ain = pin;
		Serial3.println("Infrared Senseor init success!");
	}
	void Infrared::test() {
		Serial3.println(analogRead(Ain));
		//Serial3.print(" ");
	}
	int Infrared::ValAfterFilter()
	{
		int val;
		for (int ValAfterFilter_i = 0; ValAfterFilter_i < 10; ValAfterFilter_i++)
			val = Moving_Median_int(analogRead(Ain), 3);
		//Serial3.println(val);
		return val;
	}
#include "MainMethod.h"
#include "MainMap.h"
extern MapNode* FullMap;
void setup() {
	CAR_Init();
	//myGearMotor.open_PID();
	attachInterrupt(0, CodeS1, FALLING);
	attachInterrupt(1, CodeS2, FALLING);
}

void loop() {
	/*int ld, rd;
	for (int dmi = 0; dmi < 10; dmi++) {
		LHC_SR04->getDistance();
		RHC_SR04->getDistance();
		ld = LHC_SR04->getDistanceAfterFilter(1);
		rd = RHC_SR04->getDistanceAfterFilter(2);
	}
	printval(ld);
	printval(rd);
	delay(500);*/
	/*LobotServoController::runActionGroup(7, 1);
	delay(500);
	LobotServoController::runActionGroup(8, 1); 
	delay(500);
	LobotServoController::runActionGroup(9, 1);
	delay(1000);*/
	//int ld = LHC_SR04->getDistance();
	//int rd = RHC_SR04->getDistance();
	//printval(LHC_SR04->getDistanceAfterFilter(1));
	//printval(RHC_SR04->getDistanceAfterFilter(2));//×óÓÒ´«¸ÐÆ÷²îÖµ
	//delay(500);
	//printval(Rcurrentspeed);
	//printval(Lcurrentspeed);
	//Trail_Only();
	//GetNextClosedestMaterial();
	//Trail_The_Map();
	//trailforCM(700);
	//SetSpeed(76, 60);
	//getOneMaterial();
	//turn(BACKWARD);
	//delay(500);
	Deathmaze();
	//Trail_The_Map();
	//myTsc230.rgbTestWay2();
	//maze();
}

void Trail_The_Map() {
	int index = 0;
	Rcurrentspeed = 0;
	Lcurrentspeed = 0;
	int errorCode = 0;
	MapNode* currentNode = FullMap;


	//turn(RIGHT);
	for (index = 0; index < 15; index++) {
		//trailforCM(currentNode->maxLength);
		switch (index)
		{
		case 0:
			trailforCM(500);
			break;
		case 1:
			trailforCM(170);
			break;
		case 2:
			trailforCM(800);
			break;
		case 3:
			maze();
			break;
		case 5:
			getOneMaterial();
			break;
		case 8:
			goThroughSpace();
			break;
		case 13:
			DropMaterial();
			break;
		default:
			break;
		}
		while (1) {

			errorCode = Error();
			if (errorCode < 3)
			{
				Trail_Only();	
			}
			else if (errorClass[errorCode] == mappClass[index])
			{
				break;
			}
		}
		pwmWrite(0, ALL);
		//goStraightWithPulse(150);
		turn(mapp[index]);
		goStraightWithPulse(150);
		
		myGearMotor.Move();
	}
}

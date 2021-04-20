#include "MainMethod.h"
#include "MainMap.h"
//地图
unsigned char mapp[] = {
	Straight,
	LEFT,
	LEFT,
	RIGHT,
	LEFT,
	LEFT,
	Straight,
	RIGHT,
	RIGHT,
	Straight,
	Straight,
	Straight,
	LEFT,
	LEFT,
	RIGHT,
	Straight,
	STOP };
//地图类型
unsigned char errorClass[] = { Normal
,NormalError
,None
,right_Road
,left_Road
,T_Road
,cross_Road };

unsigned char mappClass[] = {
	cross_Road,
	T_Road,
	left_Road,
	right_Road,
	cross_Road,
	cross_Road,
	right_Road,
	right_Road,
	right_Road,
	right_Road,
	right_Road,
	right_Road,
	left_Road,
	cross_Road,
	right_Road,
	cross_Road,
	T_Road
};

extern uint8_t startFlag;
//类定义
GearMotor myGearMotor;
SEN2020 mySen2020;
Maze myMaze;
Tsc230 myTsc230;
LobotServoController myLobotServoController;
HC_SR04 *LHC_SR04, *RHC_SR04;
Infrared* ir;

//整车初始化
void CAR_Init() {
	Serial.begin(9600);
	Serial3.begin(115200);
	//颜色传感器初始化（对象初始化中）

	//循迹传感器初始化（对象初始化中）

	//红外传感器初始化
	ir = new Infrared(A1);



	//串口初始化
	
	keyboard_init();
	Led_init();
	//机械臂位置初始化
	LobotServoController::runActionGroup(14, 1);
	delay(500);
	LobotServoController::runActionGroup(19, 1);
	delay(500);
	
	//双侧 中间传感器初始化
	LHC_SR04 = new HC_SR04(42, 43);
	RHC_SR04 = new HC_SR04(44, 45);

	myMaze.Init();//壁障 超声波初始化（必要）

	//WaitingForStart();
}

void WaitingForStart()
{
	while (!startFlag)
	{

		setRed();

		delay(100);
		setPurple();

		delay(100);
		setGreen();

		delay(100);
		setOrange();

		delay(100);
		setYellow();

		delay(100);
	}
	setColor(255, 255, 255);
}

//循迹
void Trail_Only() {
	if (Error() < 6 && Error() >= 0)
	{
		//	Adjust();
		getLines();
		getToLine();

	}
	else
	{
		pwmWrite(Rcurrentccr, RIGHT);
		pwmWrite(Lcurrentccr, LEFT);
	}
}

//壁障

unsigned char FirstLEFTturnDIRs[] = { LEFT,RIGHT,RIGHT,LEFT,LEFT,RIGHT,RIGHT,LEFT };
unsigned char FirstRIGHTturnDIRs[] = { RIGHT,LEFT,LEFT,RIGHT,RIGHT,LEFT,LEFT,RIGHT };
int rd;
int ld;
int pulseDif = 1000;
void correctDIR() {
	pulseDif = 100;
	int correctAngle = 8;
	while (pulseDif < -1 || pulseDif > 1) {
		int sonicDif = 10;
		//printval("123");
		for (int i = 0; i < 10; i++) {
			ld = LHC_SR04->getDistance();
			rd = RHC_SR04->getDistance();
			sonicDif = LHC_SR04->getDistanceAfterFilter(1) - RHC_SR04->getDistanceAfterFilter(2);//左右传感器差值
		}
		pulseDif = (atan(sonicDif / 13.5)) / 90.0 * 481;
		printval(pulseDif);
		turn_by_angle(pulseDif);
	}
}
void correctDIR1() {
	int correctDIR1Val;
	int offset = 0;
	while (1)
	{
		for (int i = 0; i < 10; i++) {
			ld = LHC_SR04->getDistance();
			rd = RHC_SR04->getDistance();
			correctDIR1Val = LHC_SR04->getDistanceAfterFilter(1) - RHC_SR04->getDistanceAfterFilter(2);//左右传感器差值
			correctDIR1Val += offset;
		}
		printval(correctDIR1Val);
		if (correctDIR1Val > -5 && correctDIR1Val < 5) {
			break;
		}
		if (correctDIR1Val > 0) {
			turn_by_angle(1);
		}
		if (correctDIR1Val < 0) {
			turn_by_angle(-1);
		}
	}
}

void trailforCM(int cm)
{
	int length = cm * 22 * 2;
	Rcurrentspeed = 0;
	Lcurrentspeed = 0;
	while (Rcurrentspeed + Lcurrentspeed < length)
	{
		Trail_Only();
	}
}
void maze()
{
	int turnTime;
	trailforCM(250);

	LobotServoController::runActionGroup(6, 1);//归中位
	delay(500);

	turnTime = 0;//记录转弯次数
	int testRange = 13;
	while (turnTime != 7)
	{
		setPurple();
		while (RHC_SR04->getDistanceAfterFilter() > 40 && LHC_SR04->getDistanceAfterFilter() > 40) {
			pwmWrite(myMaze.LMazeSpeed, LEFT);
			pwmWrite(myMaze.RMazeSpeed, RIGHT);
		}
		pwmWrite(0, ALL);
		if (turnTime > 0 && turnTime < 6) {
			setGreen();
			int ci = 0;
			while (ci < 5) {
				correctDIR1();
				ci++;
			}

		}
		unsigned char DIR = myMaze.GetDirection();
		turn(DIR);
		turnTime++;
		printval(turnTime);
	}

	goStraightWithPulse(650);
	unsigned char DIR = myMaze.GetDirection();
	turn(DIR);
	return;
	//while (turnTime != 7)
	//{
	//	int rangeData =myMaze.getRange();
	//	printval(rangeData);
	//	//Serial.println(rangeData);
	//	if (testRange - 3 < rangeData&&rangeData < testRange&&turnTime)
	//	{
	//		pwmWrite(0, ALL);
	//		if (turnTime < 6 && turnTime>0) {
	//			correctDIR();
	//		}
	//		unsigned char DIR = myMaze.GetDirection();
	//		turn(DIR);
	//		turnTime++;
	//	}
	//	if (rangeData < testRange - 5)
	//	{
	//		pwmWrite(-myMaze.LMazeSpeed, LEFT);
	//		pwmWrite(-myMaze.RMazeSpeed, RIGHT);
	//		delay(200);
	//	}
	//	else {
	//		pwmWrite(myMaze.LMazeSpeed, LEFT);
	//		pwmWrite(myMaze.RMazeSpeed, RIGHT);
	//	}
	//}


}
void Deathmaze() {
	int ld;
	int rd;
	trailforCM(250);

	LobotServoController::runActionGroup(6, 1);//归中位
	delay(500);

	setPurple();
	while (1) {
		for (int dmi = 0; dmi < 10; dmi++) {
			LHC_SR04->getDistance();
			RHC_SR04->getDistance();
			ld = LHC_SR04->getDistanceAfterFilter(1);
			rd = RHC_SR04->getDistanceAfterFilter(2);
		}
		if (ld < 150 || rd < 150) {
			break;
		}
			
		pwmWrite(myMaze.LMazeSpeed, LEFT);
		pwmWrite(myMaze.RMazeSpeed, RIGHT);
	}
	pwmWrite(0, ALL);
	unsigned char DIR = myMaze.GetDirection();
	if (DIR == LEFT) {
		int diri;
		for (diri = 0; diri < 6; diri++) {
			turn(FirstLEFTturnDIRs[diri]);
			while (1) {
				for (int dmi = 0; dmi < 10; dmi++) {
					LHC_SR04->getDistance();
					RHC_SR04->getDistance();
					ld = LHC_SR04->getDistanceAfterFilter(1);
					rd = RHC_SR04->getDistanceAfterFilter(2);
				}
				if (ld < 140 || rd < 140) {
					break;
				}

				pwmWrite(myMaze.LMazeSpeed, LEFT);
				pwmWrite(myMaze.RMazeSpeed, RIGHT);
			}
			pwmWrite(0, ALL);
			if (diri < 6)
			{
				setGreen();
				int ci = 0;
				while (ci < 5) {
					correctDIR1();
					ci++;
				}
			}
		}
		turn(FirstLEFTturnDIRs[diri++]);
		goStraightWithPulse(650);
		turn(FirstLEFTturnDIRs[diri]);
	}
	if (DIR == RIGHT) {
		int diri;
		for (diri = 0; diri < 6; diri++) {
			turn(FirstRIGHTturnDIRs[diri]);
			while (1) {
				for (int dmi = 0; dmi < 10; dmi++) {
					LHC_SR04->getDistance();
					RHC_SR04->getDistance();
					ld = LHC_SR04->getDistanceAfterFilter(1);
					rd = RHC_SR04->getDistanceAfterFilter(2);
				}
				if (ld < 140 || rd < 140) {
					break;
				}

				pwmWrite(myMaze.LMazeSpeed, LEFT);
				pwmWrite(myMaze.RMazeSpeed, RIGHT);
			}
			pwmWrite(0, ALL);
			if (diri <6)
			{
				setGreen();
				int ci = 0;
				while (ci < 5) {
					correctDIR1();
					ci++;
				}
			}
		}
		turn(FirstRIGHTturnDIRs[diri++]);
		goStraightWithPulse(650);
		turn(FirstRIGHTturnDIRs[diri]);
	}
	


}

//取物块
int distanceMin = 1000;//the least distance between car and the closedest material
int distances[140];//存放各个方向的距离值
int distancesIndex = 0;
bool isAimColor = 0;

void judgeColorAndProcess() {
	if (myTsc230.isAimColor()) {
		LobotServoController::run(putIn);
		isAimColor = 1;
	}

	else
	{
		isAimColor = 0;
		LobotServoController::run(drop);
	}

}
int towardsToAimMaterial(int interval, int time) {
	int len;//distance
	int maxi;
	int maxDistance;//temp max value
	int MaxDistancePos;
	int pos;
	int startPos = 900;
	int endPos = 1400;
	int Interval;

	//prepera for test
	LobotServoController::runActionGroup(22, 1);
	delay(2200);
	LobotServoController::moveServo(0, 800, 500);
	delay(800);
	Interval = map(interval, 0, 270, 500, 2500) - 500;



	for (int reviseTime = 0; reviseTime < 3; reviseTime++)
	{
		distancesIndex = 0;
		LobotServoController::moveServo(0, startPos, 500);
		delay(500);
		//test and getValues
		for (int i = startPos; i < endPos; i += Interval) {
			LobotServoController::moveServo(0, i, interval*time);
			delay((interval + 1) * time);
			distances[distancesIndex++] = ir->ValAfterFilter();
			printval(distances[distancesIndex - 1]);
		}

		//get the max distance and pos
		maxDistance = distances[0];
		maxi = 0;
		for (int i = 1; i < distancesIndex; i++) {
			if (distances[i] > maxDistance) {
				maxDistance = distances[i];
				maxi = i;
				distanceMin = maxDistance;
			}
		}

		//get the max value's pos rank 0-270
		MaxDistancePos = startPos + maxi*Interval;
		pos = map(MaxDistancePos, 500, 2500, 0, 270) - 8;//减去舵机的安装误差
		printval(pos);
		turn_by_angle(90 - pos);
	}
}
int getMaxlengthAngle(int interval, int time) {
	int len;//distance
	int maxi;

	//prepera for test
	LobotServoController::runActionGroup(22, 1);
	delay(2200);
	LobotServoController::moveServo(0, 800, 500);
	delay(800);
	int Interval = map(interval, 0, 270, 500, 2500) - 500;

	distancesIndex = 0;
	//test and getValues
	for (int i = 800; i < 1500; i += Interval) {
		LobotServoController::moveServo(0, i, interval*time);
		delay((interval + 1) * time);
		distances[distancesIndex++] = ir->ValAfterFilter();
		printval(distances[distancesIndex - 1]);
	}

	//get the max distance and pos
	int maxDistance = distances[0];
	maxi = 0;

	for (int i = 1; i < distancesIndex; i++) {
		if (distances[i] > maxDistance) {
			maxDistance = distances[i];
			maxi = i;
			distanceMin = maxDistance;
		}
	}

	//get the max value's pos rank 0-270
	int MaxDistancePos = 800 + maxi*Interval;
	printval(MaxDistancePos);
	return map(MaxDistancePos, 500, 2500, 0, 270) - 8;//减去舵机的安装误差
}

void getMaterial() {
	int len;
	LobotServoController::runActionGroup(22, 1);//保持探测姿态
	delay(1200);
	len = ir->ValAfterFilter();
	printval(len);
	if (len > 330)
	{
		LobotServoController::run(putUp);
		judgeColorAndProcess();
		LobotServoController::runActionGroup(6, 1);//归中
		delay(500);
		LobotServoController::runActionGroup(22, 1);//保持探测姿态
		delay(1300);
	}

}
void goAndGetMaterial() {
	int len;
	LobotServoController::runActionGroup(23, 1);
	delay(1200);
	while (1)
	{
		len = ir->ValAfterFilter();
		printval(len);
		if (len > 330)
		{
			LobotServoController::run(putUp);
			judgeColorAndProcess();
			LobotServoController::runActionGroup(6, 1);//归中
			delay(500);
			return;
		}
		else
		{
			goStraightWithPulse(5);
		}
		//delay(1000);
	}
}
void GetNextClosedestMaterial() {
	towardsToAimMaterial(1, 5);
	goAndGetMaterial();
}
void Material() {
	bool isFindAimColormaterial = 0;
	int judgeColorSum = 0;			//jing xiang pan duan wukuai geshu
									//int pickedUpMaterialSum = 0;


									/*while (Error() < 3) {
									Trail_Only();
									}*/
									/*turn(RIGHT);
									while (Error() != 2) {
									Trail_Only();
									}*/
									//turn(LEFT);

	while (isFindAimColormaterial == 0 && judgeColorSum < 3) {
		GetNextClosedestMaterial();
		judgeColorSum++;
		goStraightWithPulse(300);
		if (isAimColor == 1) {
			isFindAimColormaterial = 1;
			turn(LEFT);
			for (int i = 0; i < 2; i++) {
				GetNextClosedestMaterial();
				goStraightWithPulse(300);
			}
			turn(LEFT);
			for (int i = 0; i < judgeColorSum; i++) {
				GetNextClosedestMaterial();
				goStraightWithPulse(300);
			}
			turn(LEFT);
			GetNextClosedestMaterial();
			goStraightWithPulse(300);
			turn(RIGHT);
			goStraightWithPulse(500);
		}
	}
	while (1) {
		Trail_Only();
	}
}
void Material2() {

}
void getOneMaterial() {
	while (Error() < 5)
	{
		Trail_Only();
	}
	myGearMotor.Stop();
	GetNextClosedestMaterial();
	while (isAimColor == 0) {
		goAndGetMaterial();
	}
	turn(BACKWARD);
	while (Error()< 5) {
		goStraightWithPulse(5);
	}
	goStraightWithPulse(150);
	//Trail_Only();
}

//扔物块
void DropMaterial() {
	LobotServoController::runActionGroup(19, 1);
	delay(600);

	unsigned char colors[3];//from car's right to mid to left 0 1 2
	while (Error() < 3) {
		Trail_Only();
	}
	myGearMotor.Stop();

	LobotServoController::runActionGroup(26, 1);
	delay(600);
	colors[1] = myTsc230.rgbTestWay2();
	LobotServoController::runActionGroup(25, 1);
	delay(600);
	colors[0] = myTsc230.rgbTestWay2();
	LobotServoController::runActionGroup(27, 1);
	delay(600);
	colors[2] = myTsc230.rgbTestWay2();
	LobotServoController::runActionGroup(14, 1);
	delay(500);

	if (aimColor == colors[0]) {
		goStraightWithPulse(350);
		turn(LEFT);
		goStraightWithPulse(-20);
		LobotServoController::runActionGroup(20, 1);//放下货物
		delay(600);
		delay(1000);
		goStraightWithPulse(20);
		turn(LEFT);
		goStraightWithPulse(500);
		myGearMotor.Stop();
	}
	else if (aimColor == colors[1])
	{
		goStraightWithPulse(350);
		turn(BACKWARD);
		goStraightWithPulse(20);
		LobotServoController::runActionGroup(20, 1);//放下货物
		delay(600);
		delay(1000);
		goStraightWithPulse(500);
		myGearMotor.Stop();
	}
	else {
		goStraightWithPulse(350);
		turn(RIGHT);
		goStraightWithPulse(-20);
		LobotServoController::runActionGroup(20, 1);//放下货物
		delay(600);
		delay(1000);
		goStraightWithPulse(20);
		turn(RIGHT);
		goStraightWithPulse(500);
		myGearMotor.Stop();
	}

}

//穿越太空区
void goThroughSpace() {
	trailforCM(700);
}
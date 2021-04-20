#include "arduino.h"
#include "Maze.h"
int ltrig;
int lecho;
int rtrig;
int recho;


byte highByte = 0x00;   // Stores high byte from ranging
byte lowByte = 0x00;   // Stored low byte from ranging


int wideLenth[7];

int mazeHeadGroup[7] = { 5,4,3,6,7,8,9 };

int getMaxPulse(int a[], int n)
{
	int m = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] > a[m])
			m = i;
	}
	return m;
}


Maze::Maze() {
		RMazeSpeed = 80;
		LMazeSpeed = 80;
	}

	void Maze::setSpeed(int Rspeed, int Lspeed) {
		RMazeSpeed = Rspeed;
		LMazeSpeed = Lspeed;
	}

	void Maze::Init() {
		Wire.begin();						//??????·                          
		delay(100);                         // Waits to make sure everything is powered up before sending or receiving data

		Wire.beginTransmission(KS103ADDR);             // Start communticating with KS103
		Wire.write(Reg);                               // Send Reg
		Wire.write(0x71);  // Send 0x72 to set USB Power ????????
		Wire.endTransmission(6);

		Serial3.println("KS-103 init success!");
	}

	void Maze::test() {
		int rangeData = getRange();                      // Calls a function to get range
		Serial.print("rangeData");
		Serial.print(":");
		Serial.println(rangeData);
		//	Serial.print(" ");
		delay(100);
	}

	void Maze::goMaze()
	{
		LobotServoController::runActionGroup(6, 1);//归中位
		delay(500);

		int turnTime = 0;//记录转弯次数
		int testRange = 13;
		while (turnTime != 7)
		{
			int rangeData = getRange();
			//Serial.println(rangeData);
			if (testRange - 3 < rangeData&&rangeData < testRange)
			{
				pwmWrite(0, ALL);
				unsigned char DIR = GetDirection();
				turn(DIR);
				turnTime++;
			}
			if (rangeData < testRange - 5)
			{
				pwmWrite(-LMazeSpeed, LEFT);
				pwmWrite(-RMazeSpeed, RIGHT);
				delay(200);
			}
			else {
				pwmWrite(LMazeSpeed, LEFT);
				pwmWrite(RMazeSpeed, RIGHT);
			}
		}

		goStraightWithPulse(650);
		unsigned char DIR = GetDirection();
		turn(DIR);
	}

	unsigned char Maze::GetDirection()// 1是右边 0是左边 2是直走
	{
		int dir = 0;
		for (int i = 0; i < 7; i++) {
			LobotServoController::runActionGroup(mazeHeadGroup[i], 1);
			delay(500);
			int rangeData = getRange();
			wideLenth[i] = rangeData;

			//if (rangeData > 40)								//找到缺口，记录缺口大致方向跳出
			//{
			//	dir = i;														
			//	LobotServoController::runActionGroup(mazeHeadGroup[3], 1);
			//	delay(800);
			//	//myservo.write(90);
			//	break;
			//}
			//Serial.print(i);
			//Serial.print(":");
			//Serial.println(rangeData);
			//delay(100);
		}

		dir = getMaxPulse(wideLenth, 7);

		if (dir < 3)
		{
			LobotServoController::runActionGroup(mazeHeadGroup[3], 1);//最终回中
			delay(500);
			return RIGHT;
		}
		if (dir > 3)
		{
			LobotServoController::runActionGroup(mazeHeadGroup[3], 1);//最终回中
			delay(500);
			return LEFT;
		}
		LobotServoController::runActionGroup(mazeHeadGroup[3], 1);//最终回中
		delay(500);
		return  FORWARD;
	}

	int Maze::getRange() {                                    // This function gets a ranging from the SRF08

		int range = 0;

		Wire.beginTransmission(KS103ADDR);               // Start communticating with SRF08
		Wire.write(Reg);                                // Send Command Byte
		Wire.write(0xb4);                                // Send 0xb0 to start a ranging(0-5m)
		Wire.endTransmission();

		delay(100);                                     // Wait for ranging to be complete

		Wire.beginTransmission(KS103ADDR);              // start communicating with SRFmodule
		Wire.write(Reg);                                // Call the register for start of ranging data
		Wire.endTransmission();

		Wire.requestFrom(KS103ADDR, 2);                 // Request 2 bytes from SRF module
		while (Wire.available() < 2);                    // Wait for data to arrive
		highByte = Wire.read();                         // Get high byte
		lowByte = Wire.read();                          // Get low byte
														//Serial.println (lowByte, DEC); 
		range = ((highByte << 8) + lowByte) / 10;              // Put them together

		return(range);                                  // Returns Range
	}




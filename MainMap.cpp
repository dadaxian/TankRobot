#include "Arduino.h"
#include "MainMap.h"
#include "GearMotor.h"
#

MapNode FullMap[20] = {
	{ straight,NULL,430 },
	{ left,NULL,180 },
	{ left,NULL,100 },
	//{ straight,maze,255 },
	{ right,NULL,230 },
	{}
};
MapNode* currentNode;

int procedureLength = 0;
int straightSpeed = 90;

int LStraightSpeed = 76;
int RStraightSpeed = 60;

int lastLine = 0;
u8 linecount = 0;
int  lines[8];
extern int sensers[8];
//this function process snesers' data from bits to lines;
void getLines()
{
	linecount = 0;			//lines under the senser
	u8 currentLineCount = 0; //current sensers count actived by line
	u8 currentLineSum = 0;	//current sensers Number sum 
	u8 lineFlag = 0;				// current itearter is under the line 
									//	ConvertToArray(); //Convert senser data to senser[8] array
	for (int i = 0; i < 8; i++)
	{
		if (lineFlag == 1)
		{
			if (sensers[i] == 0)
			{
				lines[linecount++] = currentLineSum * 10 / currentLineCount;
				currentLineCount = 0;
				currentLineSum = 0;
				lineFlag = 0;
			}
			else if (sensers[i] == 1)
			{
				currentLineCount++;
				currentLineSum += i;
			}
		}
		else if (lineFlag == 0)
		{
			if (sensers[i] == 0)
			{
				continue;
			}
			else if (sensers[i] == 1)
			{
				lineFlag = 1;
				currentLineCount++;
				currentLineSum += i;
			}
		}
	}
	if (lineFlag == 1)
	{
		lines[linecount++] = currentLineSum * 10 / currentLineCount;
		currentLineCount = 0;
		currentLineSum = 0;
		lineFlag = 0;
	}
}
//#define dynamicPid;

//this function revise the car to the line 
//before run this function run function getLines() first;
void getToLine()   //revise to line 
{
	static u8 PidCount;
	static int OlderrVal;	//last time error sum
	static int pidOutSum;
	static int pidPOut;
	static int pidDout;
	pidOutSum = 0;
	pidPOut = 0;
	int Ep = (lines[0] - 35);
	float Kd;
	int Kp = 4;
	pidPOut = Kp*Ep;
	pidOutSum += pidPOut;
	if (PidCount++>50)
	{

		PidCount = 0;
#ifdef dynamicPid
		int kkd = 2;
		int kkp = 2;
		attachInterrupt(0, CodeS1, FALLING);
		attachInterrupt(1, CodeS2, FALLING);
		Kd = (Rcurrentspeed + Lcurrentspeed)*kkd;
#else
		Kd = 40;
#endif


		int d = 0;

		d = Ep - OlderrVal;
		OlderrVal = Ep;
		pidDout = Kd*d;
	}
	pidOutSum += pidDout;


	if (linecount == 1)
	{
		//LIMIT(speeddif, -80, 80);
		int lspeed = straightSpeed - pidOutSum;
		int rspeed = straightSpeed + pidOutSum;
		SetSpeed(lspeed, rspeed);
	}
	else if (linecount == 0)
	{
		//pidDout = 0;
		//printdbg("ERR NO LINE");
		SetSpeed(LStraightSpeed, RStraightSpeed);
	}
	else if (linecount > 1)
	{
		SetSpeed(LStraightSpeed, RStraightSpeed);
		//pidDout = 0;
		//printdbg("ERR TOO MUCH LINE");
	}
}

bool errorJudge()
{
	if (linecount == 1 && sensers[0] != HIGH&&sensers[7] != HIGH)
	{
		return 1;

	}
	else
	{
		return 0;
	}
}
CrossType getCurrentCrossType()//得到特殊结点
{
	if (linecount == 1)
	{
		if (sensers[0] == HIGH&&sensers[7] == HIGH)
		{
			return Tcross;
		}
		else if (sensers[0] == HIGH&&sensers[7] == LOW)
		{
			return right;
		}
		else if (sensers[0] == LOW&&sensers[7] == HIGH)
		{
			return left;
		}
		else
		{
			return ErrorNode;
		}
	}
	else
	{
		return ErrorNode;
	}
}
void CrossProcess()
{
	CrossType ct = getCurrentCrossType();
	CrossType ctnext = (currentNode + 1)->startCrossType;
	//	printdbg(ct);
	//printdbg(ctnext);

	if (ct == (currentNode + 1)->startCrossType)
	{

	}
	else
	{
		//printdbg("error type");
		while (1)
		{

		}
	}
}
//Normal Process on line
void TrailProcess()
{
	//GetStatus();

	getLines();
	if (errorJudge) //normal process
	{
		getToLine();
		if (linecount == 0)
		{
			//	goWithPulse(100, 100);
		}

	}
	else			//error process
	{
		CrossProcess();
	}

}
void ProcessMap()
{

}

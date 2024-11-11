
//cast function
void cast()
{
	displayBigTextLine(7,"Cast: Up*");
//uses touch sensor 1, motor D
	SensorType[S4] = sensorEV3_Touch;

	while(SensorValue[S4] != 1)
	{
			motor[motorD] = 50;
	}
	motor[motorD] = 0;

	setMotorBrakeMode(motorD, motorCoast);
	displayTextLine(11, "In coast");

}

void waitForFish()
{

}

void reelFish()
{

}

void reload()
{
	displayBigTextLine(9,"Reload: Down*");
		while(true)
	{
		motor[motorA] = -50;
	}
}

void interface()
{
	//displays all available options
	//name is either RobotFishii or FishyWishy3000
	displayBigTextLine(1,"FishyWishy :D");
	displayTextLine(4,"Please choose an option");
	displayTextLine(5,"with the direction buttons");
	displayBigTextLine(7,"Cast: Up");
	displayBigTextLine(9,"Reload: Down");
	displayBigTextLine(11,"Manual: Left");

	if(getButtonPress(buttonUp))
	{
		while(getButtonPress(buttonUp)) {}
		//clear screen and says reeling mode
		cast();
	}

		if(getButtonPress(buttonDown))
	{
		while(getButtonPress(buttonLeft)) {}
		//clear screen and says reeling mode
		reload();

	}

		if(getButtonPress(buttonLeft))
	{
		while(getButtonPress(buttonLeft)) {}
		//clear screen and says reeling mode
		manualMode();
	}


}

void manualMode()
{
	displayBigTextLine(11,"Manual: Left*");

	while (!getButtonPress(buttonEnter))
	{
		if(getButtonPress(buttonLeft))
		{
			while(getButtonPress(buttonLeft)) {motor[motorA] = -10;}
			//clear screen and says reeling mode
			motor[motorA] = 0;
		}

			if(getButtonPress(buttonRight))
		{
			while(getButtonPress(buttonRight)) {motor[motorA] = 10;}
			//clear screen and says reeling mode
			motor[motorA] = 0;
		}

			if(getButtonPress(buttonUp))
		{
			while(getButtonPress(buttonUp)) {motor[motorB] = 10;}
			//clear screen and says reeling mode
			motor[motorB] = 0;
		}

			if(getButtonPress(buttonDown))
		{
			while(getButtonPress(buttonDown)) {motor[motorB] = -10;}
			//clear screen and says reeling mode
			motor[motorB] = 0;
			displayTextLine(13, "out of function");
		}
	}

	displayTextLine(13, "out of function");

}

task main()
{
	//base of menu system
/*while(true)
{
	interface();
}*/
cast();

}

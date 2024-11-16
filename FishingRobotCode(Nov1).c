//cast function
void cast() //AR
{
	displayBigTextLine(7,"Cast: Up*");
	//uses touch sensor 1, motor D
	SensorType[S4] = sensorEV3_Touch;
	//CHECK
	motor[motorB] = -20;
	wait1Msec(1000);
	motor[motorB] = 0;
	while(SensorValue[S4] != 1)
	{
		motor[motorD] = -50;
	}
	motor[motorD] = 0;
	setMotorBrakeMode(motorD, motorCoast);
	motor[motorB] = 50;
	wait1Msec(2000);
	motor[motorB] = 0;
	motor[motorB] = -20;
	wait1Msec(1000);
	motor[motorB] = 0;
	wait1Msec(1000);
	displayTextLine(11, "In coast");

}
//WORKS
bool waitForFish(float timeLimit) // Liam Doyle
{
	// Reset Variables
	bool fishCaught = false;
	setMotorBrakeMode(motorD, motorCoast);
	clearTimer(T2);
	nMotorEncoder[motorD] = 0;

	while((time1(T2)/1000) != 5){} // Buffer period to allow lure to settle on table

	while(!fishCaught && (time1(T2)/1000) <= timeLimit){ // Poll for encoder movement or time limit
		if(nMotorEncoder[motorD] != 0){
			fishCaught = true;
		}
		displayTextLine(3,"%d", time1(T2));
	}

	return fishCaught;
}

//WORKS
void reelFish(bool fishCaught)
{
  if(fishCaught)
  {
	  motor[motorC] = 100;
	  wait1Msec(1000);
	  motor[motorC] = 0;
  }
  motor[motorD] = -100;
  while(SensorValue[S4] == 0) {}
  motor[motorD] = 0;
  motor[motorD] = 50;
  wait1Msec(1000);
  motor[motorD] = 0;
}

void reload()
{
	displayBigTextLine(9,"Reload: Down*");
		while(true)
	{
		motor[motorA] = -50;
	}
}

void manualFish() //AR
{
	eraseDisplay();
	displayBigTextLine(3,"Manual Fish Mode");
	wait1Msec(100);
	while(!getButtonPress(buttonEnter))
	{
		motor[motorC] = 0;
		motor[motorA] = 0;
	  while (getButtonPress(buttonUp))
		{
			motor[motorC] = 100;
		}
	
		while (getButtonPress(buttonDown))
		{
			motor[motorC] = -100;
		}
	
		while (getButtonPress(buttonLeft))
		{
			motor[motorA] = -100;
		}
	
		while (getButtonPress(buttonRight))
		{
			motor[motorA] = 100;
		}
	}

			/*if(getButtonPress(buttonDown))
		{
			while(getButtonPress(buttonDown)) {motor[motorB] = -10;}
			//clear screen and says reeling mode
			motor[motorB] = 0;
			displayTextLine(13, "out of function");
		}
	}

	displayTextLine(13, "out of function");
	
	*/

}


/*
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
		//manualMode();
	}


}
*/


void startUp()
{
	eraseDisplay();
  displayTextLine(4,"Is the robot in its startup configuration?");
  displayTextLine(5,"Up for Yes, Down for No");
  while(!getButtonPress(buttonAny))
  {}
  if(getButtonPress(buttonUp))
  {
	  nMotorEncoder[motorA] = 0;
	  nMotorEncoder[motorC] = 0;
	  resetGyro(S3);
  }
  else if(getButtonPress(buttonDown))
  {
  	eraseDisplay();
    displayTextLine(4,"Please adjust robot");
    displayTextLine(5,"to startup config");
    displayTextLine(6,"Press Enter when complete");
    while(!getButtonPress(buttonEnter))
    {
    	displayTextLine(2,"manualFish");
   		manualFish();
    }
    nMotorEncoder[motorA] = 0;
    nMotorEncoder[motorC] = 0;
    resetGyro(S3);
  }
  
   displayTextLine(10,"%d", nMotorEncoder[motorA]);
   displayTextLine(11,"%d", nMotorEncoder[motorC]);
  clearTimer(T1);
}

task main()
{
	//base of menu system
	SensorType[S3] = sensorEV3_Gyro;
	wait1Msec(50);

	SensorMode[S3] = modeEV3Gyro_Calibration;
	wait1Msec(50);

		resetGyro(S3);
		wait1Msec(50);
		
		startUp();
		eraseDisplay();
		displayBigTextLine(1,"Robot running...");
		bool test = false;
	while (!test && (time1(T1) <= 100000)
	{
		displayTextLine(4,"%d", time1(T1));
		cast();
		/*
		displayTextLine(1, "Gyro Degree");
		displayTextLine(2, "%f", getGyroDegrees(S3);
		displayTextLine(3, "Ultrasonic");
		displayTextLine(4, "%f", SensorValue[S2]);
		motor[motorC] = 0;
		motor[motorA] = 0;
		motor[motorD] = 0;
		motor[motorB] = 0;
		*/
		displayTextLine(3,"Wait for fish...");
		test = waitForFish(10);
		displayTextLine(1,"%f", test);
		reelFish(test);
	}
	
	displayTextLine(6,"Shutdown");
	//shutdown function

}

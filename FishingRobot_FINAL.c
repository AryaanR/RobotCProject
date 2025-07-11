void cast() //Aryaan Ray
{

	SensorType[S4] = sensorEV3_Touch;
	SensorType[S2] = sensorEV3_Ultrasonic
	//CHECK
	motor[motorB] = -20;
	wait1Msec(1000);
	motor[motorB] = 0;
	bool cast = 0;
	while(!cast)
	{
	while(SensorValue[S4] != 1)
	{
		motor[motorD] = 50;
	}
	motor[motorD] = 0;


		if(SensorValue[s2] > 15)
		{
		setMotorBrakeMode(motorD, motorCoast);
		motor[motorB] = 20;
		wait1Msec(400);
		motor[motorB] = 0;
		wait1Msec(1000)
		motor[motorB] = -20;
		wait1Msec(500);
		motor[motorB] = 0;
		wait1Msec(1000);
	//	displayTextLine(11, "In coast");
		displaybigTextLine(3, "")
		cast = 1;
		}
		else
		{
			displayBigTextLine(3, "Unsafe")
			motor[motorD] = 100;
      while(SensorValue[S4] == 0)
      {}
      motor[motorD] = 0;
      motor[motorD] = -100;
      wait1Msec(2000);
      motor[motorD] = 0;
		}
	}
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
	//	displayTextLine(3,"%d", time1(T2));
	}

	return fishCaught;
}

//WORKS
void reelFish(bool fishCaught) //Ian Martin
{
  if(fishCaught)
  {
	  motor[motorC] = 100;
	  wait1Msec(1000);
	  motor[motorC] = 0;
  }
  motor[motorD] = 100;
  while(SensorValue[S4] == 0) {}
  motor[motorD] = 0;
  motor[motorD] = -50;
  wait1Msec(1000);
  motor[motorD] = 0;
}

void manualFish() //Aryaan Ray
{
	eraseDisplay();
	displayBigTextLine(3,"Manual Mode");
	displayTextLine(5,"Press Enter when done");
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

		while (getButtonPress(buttonLeft)&& getGyroDegrees(S3) > -40)
		{
			motor[motorA] = -20;
		}

		while (getButtonPress(buttonRight)&& getGyroDegrees(S3) < 40)
		{
			motor[motorA] = 20;
		}
		eraseDisplay();
	}
/*
		if(getButtonPress(buttonDown))
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

void shutDown() //Rahul Patel
{
/*    if(fishCaught)
      {
            while((getGyroDegrees) != 0)
            {
                  if(getGyroDegrees < 0)
                  {
                        motor[motorA] = 20;
                  }
                  else
                  {
                        motor[motorA] = -20;
                  }
            }
            motor[motorA] = 0;

            while(abs(nMotorEncoder[motorC]) != 1800)
            {
                  motor[motorC] = 100;
            }
            motor[motorC] = 0;
      }*/

      while(nMotorEncoder[motorC]!=0)
      {
      	if (nMotorEncoder[motorC]>0)
      	{
        	motor[motorC] = -100;
     		}
     		else
     		{
        	motor[motorC] = 100;
      	}
      }

      motor[motorC] = 0;
      while((getGyroDegrees(S3)) != 0)
      {
            if(getGyroDegrees(S3) < 0)
            {
                  motor[motorA] = 10;
            }
            else
            {
                  motor[motorA] = -10;
            }
      }
      motor[motorA] = 0;
      motor[motorD] = 100;
      while(SensorValue[S4] == 0)
      {}
      motor[motorD] = 0;
      motor[motorD] = -100;
      wait1Msec(2000);
      motor[motorD] = 0;

      displayTextLine(4, "Operating Time:  %f", time1(T1));
}

void AutoFish()
{
	eraseDisplay();
	displayBigTextLine(1,"Robot running...");
	bool test = false;
	while (!test && (time1(T1) <= 100000) //&& !getButtonPress(buttonEnter))
	{
		//displayBigTextLine(3,"Time: %d", time1(T1));

		//displayTextLine(4,"%d", time1(T1));
		cast();

		//displayTextLine(3,"Wait for fish...");
		test = waitForFish(10);
		//displayTextLine(1,"%f", test);
		reelFish(test);
	}
	eraseDisplay();
	if (test == true)
	{
		displayBigTextLine(1,"Fish caught :DDD");
	}
	else
	{
		displayBigTextLine(1,"Fish not caught :(");
	}
}
bool interface() // Aryaan Ray
{
	//displays all available options
	//name is either RobotFishii or FishyWishy3000
	displayBigTextLine(1,"FishyWishy :D");
	displayTextLine(4,"Please choose an option");
	displayTextLine(5,"with the direction buttons");
	displayBigTextLine(7,"AutoFish: Right");
	displayBigTextLine(9,"Manual: Left");
while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight)) {}
	if(getButtonPress(buttonLeft))
	{
		while(getButtonPress(buttonLeft)) {}
		//clear screen and says reeling mode
		return true;
	//	AutoFish();
	}

	else if(getButtonPress(buttonRight))
	{
		while(getButtonPress(buttonRight)) {}
		//clear screen and says reeling mode
		return false;
	//	AutoFish();
	}
	else
	{
		displayTextLine(1,"wrong input, defaulted to autofish");
		wait1Msec(1000);
		return false;
	}

}



void startUp() //Rahul Patel
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

  // displayTextLine(10,"%d", nMotorEncoder[motorA]);
  // displayTextLine(11,"%d", nMotorEncoder[motorC]);
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

		//cast();

		startUp();
		bool isManual = interface();

		if(isManual)
		{
			manualFish();
		}
		AutoFish();

	eraseDisplay();
	displayBigTextLine(1, "Shutting down...");
	shutDown();


}

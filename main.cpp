#include "WPILib.h"
#include "Math.h"
#include <vector>

class Team3324 : public SimpleRobot
{
	Joystick stick1;
	Joystick stick2;
	RobotDrive driveTrain;
	Jaguar sweeper;
	Jaguar conveyor;
	Jaguar lazySusan;

public:
	Team3324(void):
		stick1(1),
		stick2(2),
		driveTrain(1, 2, 3 , 4);
		sweeper(5);
		conveyor(6);
		lazySusan(7);
		launcher1(8);
		launcher2(9);

	{
		myRobot.SetExpiration(0.1);
	}

	void Autonomous(void)
	{

	}

	void OperatorControl(void)
	{

		//Starts the sweeper to pick up balls
		sweeper.Set( 0.5 );

		//Starts the conveyor to transport balls
		conveyor.Set( 1 );

		while (IsOperatorControl())
		{

			//Uses a library function to drive using mechanum wheels with input from the joysticks
			driveTrain.MecanumDrive_Cartesian( stick1.GetX(), stick1.GetY(), stick2.GetX(), 0.0 );

			//Controls the sweeper in front of the robot: reverses the direction of the sweeper if a button is pressed
			if( stick1.GetRawButton( 4 ) ){
				
				sweeper.Set( -sweeper.Get() );

			}

			//Controls the conveyor system by stopping it until the trigger is pulled
			if( stick1.GetRawButton( 3 ) ){

				conveyor.Set( 0 );

			}	

			if( stick1.GetRawButton( 1 ) ){

				conveyor.Set( 1 );

			}		

			//We should put all of the image processing stuff into a function that returns two things in an array.
			//First, it returns how many pixels our turret is off of the center of the target.  
			//We use this to turn the target in one direction or another, or keep it still if it is within, say 5px of centered.
			//Next, we calculate the distance to the backboard using our image processing, and we feed this in to our launcher speed.
			
			vector<float> imgData = imgProcessing();
			
			if( imgData[0] > 5 ){

				lazySusan.Set( 0.5 );

			}
			else if( imgData[0] < -5 ){

				lazySusan.Set( -0.5 );	

			}
			else{

				lazySusan.Set( 0 );

			}

			//We need a function that can take these inputs and convert it into a number 0.0 - 1.0 for the motor speed
			//We need launch angle "a" to be in radians
 
			launcher1.Set( launchSpeed( imgData[1], launchAngle, heightDifference ) );
			launcher2.Set( launchSpeed( imgData[1], launchAngle, heightDifference ) );			


		}
	}

	float launchSpeed( float d, float a, float h ){

		float speedInFeet = ( d*32.15 ) / cos( a ) * sqrt( 1 / ( 2 * 32.15 * ( tan( a ) * d - h ) ) ) ;

	}

};

START_ROBOT_CLASS(Team3324);


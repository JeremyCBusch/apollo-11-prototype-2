/*****************************
 * Source File:
 *    main.cpp
 * Author:
 *    Jacob Morgan and Jeremy Busch
 * Summary:
 *    This file contains the test cases and main program direction for 
 *    the Apollo 11 simulator. 
 *****************************/

#include <cassert>
#include <iostream>
#include "lander.h"

#ifdef DEBUG
double roundTo2ndDecimal(double number) {
	return std::round(number * 100) / 100;
}
void testLander()
{
	// Prep
	double vVelocity = -10;
	double hVelocity = 0;
	double altitude = 100;
	double angle = 60;

	double weight = 15103.00;
	double gravity = -1.625;
	double vThrust = 45000.00;
	double hThrust = 450.00;
	// Action
	Lander l1(vVelocity, hVelocity, altitude, angle);
	// Test Result
	assert(l1.altitude == altitude);
	assert(l1.vVelocity == vVelocity);
	assert(l1.hVelocity == hVelocity);
	assert(l1.altitude == altitude);
	assert(l1.weight == weight);
	assert(l1.gravity == gravity);
	assert(l1.vThrust == vThrust);
	assert(l1.hThrust == hThrust);
}
void testIncrementTime()
{
	// Prep
	double vVelocity = -10;
	double hVelocity = 0;
	double altitude = 100;
	double angle = 60;
	Lander l1(vVelocity, hVelocity, altitude, angle);
	// Action
	l1.incrementTime(1);
	// Test Result
	assert(l1.seconds == 1);
	assert(roundTo2ndDecimal(l1.angle) == 60.00);
	assert(roundTo2ndDecimal(l1.xDisplacement) == 3.87);
	assert(roundTo2ndDecimal(l1.altitude) == 89.80);
	assert(roundTo2ndDecimal(l1.hVelocity) == 2.58);
	assert(roundTo2ndDecimal(l1.vVelocity) == -10.14);
	// Action
	l1.incrementTime(1);
	// Test Result
	assert(roundTo2ndDecimal(l1.seconds) == 2);
	assert(roundTo2ndDecimal(l1.xDisplacement) == 10.32);
	assert(roundTo2ndDecimal(l1.altitude) == 79.46);
	assert(roundTo2ndDecimal(l1.hVelocity) == 5.16);
	assert(roundTo2ndDecimal(l1.vVelocity) == -10.27);
	assert(roundTo2ndDecimal(l1.angle) == 60.00);

}
void testConvertDegreesToRadians()
{
	// Prep
	double vVelocity = -10;
	double hVelocity = 0;
	double altitude = 100;
	double angle = 60;
	Lander l1(vVelocity, hVelocity, altitude, angle);
	// Tests
	assert(roundTo2ndDecimal(l1.convertDegreesToRadians(10.0)) == roundTo2ndDecimal(0.174533));
	assert(roundTo2ndDecimal(l1.convertDegreesToRadians(100)) == roundTo2ndDecimal(1.74533));
	assert(roundTo2ndDecimal(l1.convertDegreesToRadians(1)) == roundTo2ndDecimal(0.0174533));
	assert(roundTo2ndDecimal(l1.convertDegreesToRadians(360)) == roundTo2ndDecimal(6.28319));
	assert(roundTo2ndDecimal(l1.convertDegreesToRadians(-60)) == roundTo2ndDecimal(-1.0472));
	assert(roundTo2ndDecimal(l1.convertDegreesToRadians(0)) == roundTo2ndDecimal(0));
}
void testGetHorizontalAcceleration()
{
	// Prep
	double vVelocity = -10;
	double hVelocity = 0;
	double altitude = 100;
	double angle = 60;
	Lander l1(vVelocity, hVelocity, altitude, angle);
}
void testComputeAcceleration()
{

}
void testComputeTotalVelocity()
{

}
void runTestSuite()
{
	testComputeTotalVelocity();
	testComputeAcceleration();
	testGetHorizontalAcceleration();
	testConvertDegreesToRadians();
	testIncrementTime();
	testLander();
}
#endif

double prompt(const char* output)
{
	double input;
	std::cout << output;
	std::cin >> input;
	return input;
}

int main()
{
#ifdef DEBUG
	std::cout << "Hello Debug" << std::endl;
	runTestSuite();

	std::cout << "Hard Landing" << std::endl;

	double vVelocity = -13.959;
	double hVelocity = 10.53;
	double altitude = 100.0;
	double angle = -45;
	Lander lander(vVelocity, hVelocity, altitude, angle);
	for (int i = 0; i < 5; i++)
	{
		lander.incrementTime(1);
		lander.displayStatus();
	}
	lander.changeAngle(0.0);
	for (int i = 0; i < 5; i++)
	{
		lander.incrementTime(1);
		lander.displayStatus();
	}

	std::cout << "\n\nCrash:\n";

	vVelocity = -15.000;
	hVelocity = -35.00;
	altitude = 207.77;
	angle = 90;
	Lander lander2(vVelocity, hVelocity, altitude, angle);
	for (int i = 0; i < 5; i++)
	{
		lander2.incrementTime(1);
		lander2.displayStatus();
	}
	lander2.changeAngle(45);
	for (int i = 0; i < 5; i++)
	{
		lander2.incrementTime(1);
		lander2.displayStatus();
	}

	std::cout << "\n\nArmstrong is awesome!:\n";

	vVelocity = -10.000;
	hVelocity = 10.00;
	altitude = 56.11;
	angle = -42.185;
	Lander lander3(vVelocity, hVelocity, altitude, angle);
	for (int i = 0; i < 5; i++)
	{
		lander3.incrementTime(1);
		lander3.displayStatus();
	}
	lander3.changeAngle(0);
	for (int i = 0; i < 5; i++)
	{
		lander3.incrementTime(1);
		lander3.displayStatus();
	}
#else
	std::cout << "Hello Live" << std::endl;

	double vVelocity = prompt("What is your vertical velocity (m/s)? ");
	double hVelocity = prompt("What is your horizontal velocity (m/s)? ");
	double altitude = prompt("What is your altitude (m)? ");
	double angle = prompt("What is the angle of the LM where 0 is up (degrees)? ");

	Lander lander(vVelocity, hVelocity, altitude, angle);

	for (int i = 0; i < 5; i++)
	{
		lander.incrementTime(1);
		lander.displayStatus();
	}

	lander.changeAngle(prompt("What is the new angle of the LM where 0 is up (degrees)? "));

	for (int i = 0; i < 5; i++)
	{
		lander.incrementTime(1);
		lander.displayStatus();
	}
#endif
	return 0;
}
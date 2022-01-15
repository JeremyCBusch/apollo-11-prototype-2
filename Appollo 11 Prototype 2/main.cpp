#define DEBU
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
	assert(roundTo2ndDecimal(l1.altitude) == 79.48);
	assert(roundTo2ndDecimal(l1.hVelocity) == 5.16);
	assert(roundTo2ndDecimal(l1.vVelocity) == -10.27);
	assert(roundTo2ndDecimal(l1.angle) == 60.00);

}
void testConvertDegreesToRadians()
{

}
void testGetHorizontalAcceleration()
{

}
void testComputeAcceleration()
{

}
void testGetHangTime()
{

}
void testComputeTotalVelocity()
{

}
void runTestSuite()
{
	testComputeTotalVelocity();
	testGetHangTime();
	testComputeAcceleration();
	testGetHorizontalAcceleration();
	testConvertDegreesToRadians();
	testIncrementTime();
	testLander();
}
#endif

int main()
{
#ifdef DEBUG
	std::cout << "Hello Debug" << std::endl;
	runTestSuite();
#else
	std::cout << "Hello Live" << std::endl;
	double vVelocity = -10.0;
	double hVelocity = 0.0;
	double altitude = 100.0;
	double angle = 60.0;
	Lander lander(vVelocity, hVelocity, altitude, angle);
	for (int i = 0; i < 5; i++)
	{
		lander.incrementTime(1);
		lander.displayStatus();
	}
	lander.changeAngle(-60.0);
	for (int i = 0; i < 5; i++)
	{
		lander.incrementTime(1);
		lander.displayStatus();
	}
#endif
	return 0;
}
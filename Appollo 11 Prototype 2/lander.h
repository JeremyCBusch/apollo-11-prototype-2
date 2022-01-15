#pragma once
#include <cassert>


class Lander
{
public:
	Lander(double vVelocity, double hVelocity, double altitude, double angle);
	void incrementTime(int);
	void displayStatus();
	void changeAngle(double angle);
#ifndef DEBUG
private:
#endif
	const double weight =  15103.00; // kg
	const double gravity =   -1.625; // m/s^2
	const double vThrust = 45000.00; // N
	const double hThrust =   450.00; // N

	double vVelocity;
	double hVelocity;
	double angle;
	double altitude;
	double xDisplacement = 0;
	double yDisplacement = 0;
	int seconds = 0;

	double convertDegreesToRadians(double degrees);
	double getVerticalAcceleration();
	double getHorizontalAcceleration();
	double computeAcceleration(double thrust, double weight, double gravity = 0.0);
	void updateVelocity(int seconds);
	double computeTotalVelocity();
	void updateAltitude();
	void updateHDisplacement();
};


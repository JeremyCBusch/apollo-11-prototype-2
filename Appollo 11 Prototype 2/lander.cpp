#include "lander.h"
#include <iostream>
#include <stdexcept>

Lander::Lander(double vVelocity, double hVelocity, double altitude, double angle)
{
	this->vVelocity = vVelocity;
	this->hVelocity = hVelocity;
	this->altitude = altitude;
	this->angle = angle;
}

void Lander::incrementTime(int seconds)
{
	this->seconds += seconds;

	updateVelocity(seconds);
	updateHDisplacement();
	updateAltitude();
}

void Lander::displayStatus()
{
	std::cout.setf(std::ios::fixed | std::ios::showpoint);
	std::cout.precision(2);
	std::cout 
		<< seconds << "s - x,y:(" 
		<< xDisplacement << ", " 
		<< altitude << ")m  dx, dy:("
		<< hVelocity << ", " 
		<< vVelocity << ")m / s  speed : "
		<< this->computeTotalVelocity() << "m / s  angle : "
		<< angle << "deg" << std::endl;
}

void Lander::changeAngle(double angle)
{
	this->angle = angle;
}

double Lander::convertDegreesToRadians(double degrees)
{
	const double pi = 3.14159265358979323846;
	return ((2 * pi * degrees) / 360);
}

double Lander::getVerticalAcceleration()
{
	double radians = convertDegreesToRadians(angle);
	double force = vThrust * cos(radians);
	return computeAcceleration(force, weight, gravity);
}

double Lander::getHorizontalAcceleration()
{
	double radians = convertDegreesToRadians(angle);
	double force = hThrust * sin(radians);
	return computeAcceleration(force, weight);
}

double Lander::computeAcceleration(double thrust, double weight, double gravity)
{
	assert(thrust > 0.0);
	assert(weight > 0.0);
	double acceleration = thrust / weight;

	assert(gravity <= 0.0);
	return gravity + acceleration;
}

void Lander::updateVelocity(int seconds)
{
	vVelocity = vVelocity + getVerticalAcceleration() * seconds;
	hVelocity = hVelocity + getHorizontalAcceleration() * seconds;
}

double Lander::computeTotalVelocity()
{
	return sqrt(vVelocity * vVelocity + hVelocity * hVelocity);
}

void Lander::updateAltitude()
{
	altitude = altitude + vVelocity;
}

void Lander::updateHDisplacement()
{
	xDisplacement = xDisplacement + hVelocity;
}

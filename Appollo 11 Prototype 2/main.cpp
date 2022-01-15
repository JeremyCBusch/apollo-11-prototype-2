#include "lander.h"
#include <iostream>
#include <cassert>
#include <cmath>

double convertDegreesToRadians(int degrees) {
	return ((2 * 3.14159265 * degrees) / 360);
}

double getVerticalAcceleration(double thrust, int angle) {
	double radians = convertDegreesToRadians(angle);
	return (thrust * cos(radians));
}

double getHorizontalAcceleration(double thrust, int angle) {
	double radians = convertDegreesToRadians(angle);
	return (thrust * sin(radians));
}


double computeAcceleration(double thrust, double weight, double gravity = 0.0)
{
	assert(thrust > 0.0);
	assert(weight > 0.0);
	double acceleration = thrust / weight;

	assert(gravity <= 0.0);
	return gravity + acceleration;
}

double hangTime(double altitude, double velocity, double acceleration)
{
	assert(altitude > 0.0);

	double time;

	double inner = velocity * velocity - 2 * acceleration * altitude;

	if (inner > 0)
		time = (-velocity + sqrt(inner)) / acceleration;
	else
		time = -1.0;

	return time;
}

double updateVelocity(double velocity, double acceleration, double time)
{
	return velocity + acceleration * time;
}

double computeTotalVelocity(double vVelocity, double hVelocity)
{
	return sqrt(vVelocity * vVelocity + hVelocity * hVelocity);
}

double prompt(const char* output)
{
	double input;
	std::cout << output;
	std::cin >> input;
	return input;
}

int main()
{
	double weight = 15103.00;
	double vThrust = 45000.00;
	double hThrust = 450.00;
	double gravity = -1.625;

	double vVelocity = prompt("What is your vertical velocity (m/s)? ");
	double hVelocity = prompt("What is your horizontal velocity (m/s)? ");
	double altitude = prompt("What is your altitude (m)? ");

	double vAcceleration = computeAcceleration(vThrust, weight, gravity);
	double hAcceleration = computeAcceleration(hThrust, weight);
	double time = hangTime(altitude, vVelocity, vAcceleration);

	vVelocity = updateVelocity(vVelocity, vAcceleration, time);
	hVelocity = updateVelocity(hVelocity, hAcceleration, time);

	double totalVelocity = computeTotalVelocity(vVelocity, hVelocity);

	std::cout.setf(std::ios::fixed | std::ios::showpoint);
	std::cout.precision(2);
	if (time < 0)
		std::cout << "\tYou will not land, but rather fly off into space.\n";
	else
	{
		std::cout << "Time to Landing: " << time << " s" << std::endl;
		std::cout << "Vertical Velocity: " << vVelocity << " m/s" << std::endl;
		std::cout << "Horizontal Velocity: " << hVelocity << " m/s" << std::endl;
		std::cout << "Total Velocity: " << totalVelocity << " m/s" << std::endl;
	}
	return 0;
}
#include "lander.h"
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;


double convertDegreesToRadians(double degrees) {
	const double pi = 3.14159265358979323846;
	return ((2 * pi * degrees) / 360);
}

double computeAcceleration(double thrust, double weight, double gravity = 0.0)
{
	assert(thrust > 0.0);
	assert(weight > 0.0);
	double acceleration = thrust / weight;

	assert(gravity <= 0.0);
	return gravity + acceleration;
}

double getVerticalAcceleration(double thrust, double angle, double weight, double gravity) {
	double radians = convertDegreesToRadians(angle);
	double force = thrust * cos(radians) + gravity;
	return computeAcceleration(force, weight, gravity);
}

double getHorizontalAcceleration(double thrust, double angle, double weight) {
	double radians = convertDegreesToRadians(angle);
	double force = thrust * sin(radians);
	return computeAcceleration(force, weight);
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

double updateHDisplacement(double hVelocity, double hDisplacement) {
	return (hDisplacement + hVelocity);
}

double updateAltitude(double vVelocity, double altitude) {
	return (altitude + vVelocity);
}

void getStatus(int second, double xDisplacement, double altitude, double hVelocity,double vVelocity, double totalVelocity, double angle)
{
	

	std::cout << second << "s - x,y:(" << xDisplacement << ", " << altitude << ")m  dx, dy:("
		<< hVelocity << ", " << vVelocity << ")m / s  speed : " << totalVelocity << "m / s  angle : "
		<< angle << "deg" << std::endl;

}

int main()
{
	double weight = 15103.00;
	double vThrust = 45000.00;
	double hThrust = 450.00;
	double gravity = -1.625;

	double xDisplacement = 0;
	double vAcceleration;
	double hAcceleration;
	double time;
	double totalVelocity;

	std::cout.setf(std::ios::fixed | std::ios::showpoint);
	std::cout.precision(2);

	double vVelocity = -10; //prompt("What is your vertical velocity (m/s)? ");
	double hVelocity = 0; //prompt("What is your horizontal velocity (m/s)? ");
	double altitude = 100; //prompt("What is your altitude (m)? ");
	double  angle = 60; //prompt("What is the angle of the LM where 0 is up (degrees)? ");

	
	// put this code block in the lander class later
	for (int intervals = 0; intervals < 2; intervals++) {
		for (int seconds = 1; seconds < 6; seconds++) {
			

			
			vAcceleration = getVerticalAcceleration(vThrust, angle, weight, gravity);
			hAcceleration = getHorizontalAcceleration(hThrust, angle, weight);

			cout << "horizontal acceleration: " << hAcceleration << endl;
			cout << "vertical acceleration: " << vAcceleration << endl;

			time = hangTime(altitude, vVelocity, vAcceleration);

			vVelocity = updateVelocity(vVelocity, vAcceleration, time);
			hVelocity = updateVelocity(hVelocity, hAcceleration, time);

			xDisplacement = updateHDisplacement(hVelocity, xDisplacement);
			altitude = updateAltitude(vVelocity, altitude);

			totalVelocity = computeTotalVelocity(vVelocity, hVelocity);
			getStatus(seconds, xDisplacement, altitude, hVelocity, vVelocity, totalVelocity, angle);
		}
		if (intervals < 1) {
			angle = prompt("What is the new angle of the LM where 0 is up (degrees)? ");
		}
	}
	// stop here
	
	
	/*if (time < 0)
		std::cout << "\tYou will not land, but rather fly off into space.\n";
	else
	{
		std::cout << "Time to Landing: " << time << " s" << std::endl;
		std::cout << "Vertical Velocity: " << vVelocity << " m/s" << std::endl;
		std::cout << "Horizontal Velocity: " << hVelocity << " m/s" << std::endl;
		std::cout << "Total Velocity: " << totalVelocity << " m/s" << std::endl;
	}
	return 0;*/
}
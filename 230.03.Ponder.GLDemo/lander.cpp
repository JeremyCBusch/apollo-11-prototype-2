/*****************************
 * Source File:
 *    lander.cpp
 * Author:
 *    Jacob Morgan and Jeremy Busch
 * Summary:
 *    This contains the definitions for the methods used by the Lander 
 *    class. 
 *****************************/

#include "lander.h"
#include <iostream>
#include <stdexcept>


 /*************************
  * LANDER
  * This constructor takes the initial vertical velocity, the initial 
  * horizontal velocity, the initial altitude, and the angle of the 
  * lander as parameters and sets the associated member variables 
  * accordingly.
  *************************/
Lander::Lander(double vVelocity, double hVelocity, double altitude, double angle) : 
	position(400, altitude)
{
	this->vVelocity = vVelocity;
	this->hVelocity = hVelocity;
	this->altitude = altitude;
	this->angle = angle;
	this->isThrusting = false;
	this->isThrustingLeft = false;
	this->isThrustingRight = false;
}

/*************************
 * INCREMENT TIME
 * This method increments the time forward by a specified number of 
 * seconds and then calculates what the new velocities and positions 
 * will be due to this change in time. 
 *************************/
void Lander::incrementTime(double seconds)
{
	this->time += seconds;

	updateVelocity(seconds);
	updateHDisplacement(seconds);
	updateAltitude(seconds);
}

/*************************
 * DISPLAY STATUS
 * This method displays the current status of the lander to the 
 * console.
 *************************/
void Lander::displayStatus()
{
	std::cout.setf(std::ios::fixed | std::ios::showpoint);
	std::cout.precision(2);
	std::cout 
		<< time << "s - x,y:(" 
		<< xDisplacement << ", " 
		<< altitude << ")m  dx, dy:("
		<< hVelocity << ", " 
		<< vVelocity << ")m / s  speed : "
		<< this->computeTotalVelocity() << "m / s  angle : "
		<< angle << "deg" << std::endl;
}

/*************************
 * CHANGE ANGLE
 * This method updates the angle of the lander.
 *************************/
void Lander::changeAngle(double angle)
{
	this->angle = angle;
}

/*************************
 * CONVERT DEGREES TO RADIANS
 * This method takes in a value in degrees and returns it in radians.
 *************************/
double Lander::convertDegreesToRadians(double degrees)
{
	const double pi = 3.14159265358979323846;
	return (2 * pi * degrees) / 360;
}

/*************************
 * GET VERTICAL ACCELERATION
 * This method returns the current vertical acceleration.
 *************************/
double Lander::getVerticalAcceleration()
{
	double radians = convertDegreesToRadians(angle);
	double force = 0;
	if (isThrusting)
	{
		force = vThrust* cos(radians);
	}
	return computeAcceleration(force, weight, gravity);
}

/*************************
 * GET HORIZONTAL ACCELERATION
 * This method returns the current horizontal acceleration.
 *************************/
double Lander::getHorizontalAcceleration()
{
	double radians = convertDegreesToRadians(angle);
	double force = 0;
	if (isThrusting)
		force = hThrust * sin(radians);
	return computeAcceleration(force, weight) * 100;
}


/*************************
 * GET FLIGHT STATUS
 * Returns if the lander is still in the air, crashed, or landed.
 *************************/
LanderStatus Lander::getFlightStatus(double groundElevation)
{
	return still_in_air;
}

/*************************
 * COMPUTE ACCELERATION
 * This method takes in the thrust, weight, and optionally gravity. It 
 * then calculates and returns the resulting acceleration.
 *************************/
double Lander::computeAcceleration(double thrust, double weight, double gravity)
{
	//assert(thrust > 0.0);
	assert(weight > 0.0);
	double acceleration = thrust / weight;

	assert(gravity <= 0.0);
	return gravity + acceleration;
}

/*************************
 * UPDATE VELOCITY
 * This method updates the vertical and horizontal velocity based on 
 * the amount that time has been incremented by.
 *************************/
void Lander::updateVelocity(double seconds)
{
	vVelocity = vVelocity + getVerticalAcceleration() * seconds;
	hVelocity = hVelocity + getHorizontalAcceleration() * seconds;
}

/*************************
 * COMPUTE TOTAL VELOCITY
 * This method computes the total velocity using the pythagorean
 * theorem on the vertical and horizontal velocity.
 *************************/
double Lander::computeTotalVelocity()
{
	return sqrt(vVelocity * vVelocity + hVelocity * hVelocity);
}

/*************************
 * UPDATE ALTITUDE
 * This method updates the altitude using the distance formula and the
 * amount that time was incremented by.
 *************************/
void Lander::updateAltitude(double seconds)
{
	altitude = altitude + (vVelocity * seconds + 0.5 * getVerticalAcceleration() * (seconds * seconds));
	position.setY(altitude);
}

/*************************
 * UPDATE X DISPLACEMENT
 * This method updates the horizontal displacement using the distance
 * formula and the amount that time was incremented by.
 *************************/
void Lander::updateHDisplacement(double seconds)
{
	xDisplacement = xDisplacement + (-1 * (hVelocity * seconds + 0.5 * getHorizontalAcceleration() * (seconds * seconds)));
	position.setX(xDisplacement);
}

/*************************
 * UPDATE ANGLE
 * This method updates the angle.
 *************************/
void Lander::incrementAngle(double angle)
{
	double angleAcceleration;
	if (isThrustingLeft) 
	{
		/*angleAcceleration = weight / 450;*/
		this->angle = this->angle - 1;
	}
	else if (isThrustingRight)
	{
		//angleAcceleration = (weight / 450) * -1;
		this->angle = this->angle + 1;
	}
	
	
	
	//this->angle += angle;
}
/*************************
 * SET VERTICAL THRUSTERS
 * This method sets the thrusters on or off and updates the acceleration.
 *************************/
void Lander::setVerticalThrusters(bool isThrusting)
{
	this->isThrusting = isThrusting;
}

void Lander::setLeftThruster(bool isThrusting)
{
	isThrustingLeft = isThrusting;
}

void Lander::setRightThruster(bool isThrusting)
{
	isThrustingRight = isThrusting;
}



/*************************
 * GET SPEED
 * returns the speed.
 *************************/
double Lander::getSpeed()
{
	return vVelocity;
}

/*************************
 * GET LM POSITION
 * Returns the LM position.
 *************************/
Point Lander::getLMPosition()
{
	return position;
}

double Lander::getAngle()
{
	return convertDegreesToRadians(angle);
}

int Lander::getWidth()
{
	return width;
}



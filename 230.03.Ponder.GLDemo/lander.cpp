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
  * accordingly
  *************************/
Lander::Lander(double vVelocity, double hVelocity, double altitude, double angle) : 
	position(400, altitude)
{
	this->vVelocity = vVelocity;
	this->hVelocity = hVelocity;
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
	updateVelocity(seconds);
	updateHDisplacement(seconds);
	updateAltitude(seconds);
	decrementFuel(seconds);
	incrementAngle();
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
	position.setY(position.getY() + (vVelocity * seconds + 0.5 * getVerticalAcceleration() * (seconds * seconds)));
}

/*************************
 * UPDATE X DISPLACEMENT
 * This method updates the horizontal displacement using the distance
 * formula and the amount that time was incremented by.
 *************************/
void Lander::updateHDisplacement(double seconds)
{
	position.setX(position.getX() +(-1 * (hVelocity * seconds + 0.5 * getHorizontalAcceleration() * (seconds * seconds))));
}

/*************************
 * UPDATE ANGLE
 * This method updates the angle.
 *************************/
void Lander::incrementAngle()
{
	double angleAcceleration;
	if (isThrustingLeft) 
	{
		/*angleAcceleration = weight / 450;*/
		this->angle = this->angle + 1;
	}
	else if (isThrustingRight)
	{
		//angleAcceleration = (weight / 450) * -1;
		this->angle = this->angle - 1;
	}
}
/*************************
 * DECREMENT FUEL
 * This method updates the amount of fuel based on if the thrusters are on
 *************************/
void Lander::decrementFuel(double seconds)
{
	if (isThrusting)
	{
		double fuelConsumed = 100.0 * seconds;
		fuel = fuel - fuelConsumed;
		weight = weight - fuelConsumed;
	}
	if (isThrustingLeft)
	{
		double fuelConsumed = 1 * seconds;
		fuel = fuel - fuelConsumed;
		weight = weight - fuelConsumed;
	}
	if (isThrustingRight)
	{
		double fuelConsumed = 1 * seconds;
		fuel = fuel - fuelConsumed;
		weight = weight - fuelConsumed;
	}
	if (fuel < 0.0)
		fuel = 0.0;
}
/*************************
 * SET VERTICAL THRUSTERS
 * This method sets the thrusters on or off and updates the acceleration.
 *************************/
void Lander::setVerticalThrusters(bool isThrusting)
{
	if (fuel > 0.0)
		this->isThrusting = isThrusting;
	else
		this->isThrusting = false;
}

/*************************
 * SET LEFT THRUSTERS
 * This method sets the left thruster on or off and updates the angle.
 *************************/
void Lander::setLeftThruster(bool isThrusting)
{
	if (fuel > 0.0)
		isThrustingLeft = isThrusting;
	else
		isThrustingLeft = false;
}

/*************************
 * SET RIGHT THRUSTERS
 * This method sets the right thruster on or off and updates the angle.
 *************************/
void Lander::setRightThruster(bool isThrusting)
{
	if (fuel > 0.0)
		isThrustingRight = isThrusting;
	else
		isThrustingLeft = false;
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

/*************************
 * GET ANGLE
 * Returns the LM angle
 *************************/
double Lander::getAngle()
{
	return convertDegreesToRadians(angle);
}

/*************************
 * GET WIDTH
 * Returns the LM width.
 *************************/
int Lander::getWidth()
{
	return width;
}

/*************************
 * GET FUEL
 * Returns the LM fuel.
 *************************/
double Lander::getFuel()
{
	return fuel;
}



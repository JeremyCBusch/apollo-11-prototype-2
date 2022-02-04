/*****************************
 * Header File:
 *    lander.h
 * Author:
 *    Jacob Morgan and Jeremy Busch
 * Summary:
 *    This file contains the declarations for the Lander class.
 *****************************/

#pragma once
// Delete the following line to run in live mode.
#define DEBUG
#include <cassert>
#include "Point.h"
enum LanderStatus
{
	still_in_air,
	landed,
	crashed
};

 /*************************
  * Lander:
  * This class represents the lander used during the Apollo mission. 
  * It can be used to see what the position, speed, vertical velocity, 
  * horizontal velocity, and angle of the lander are. You can increment 
  * the time that has passed by any number of seconds and it will 
  * update all of it's data to match the passing of time.
  *************************/
class Lander
{
public:
	// Constructor
	Lander(double vVelocity, double hVelocity, double altitude, double angle);
	// Update Data
	void incrementTime(double seconds);
	void changeAngle(double angle);
	void setVerticalThrusters(bool isThrusting);
	void setLeftThruster(bool isThrusting);
	void setRightThruster(bool isThrusting);
	// getters
	double getSpeed();
	Point getLMPosition();
	double getAngle();
	int getWidth();
	double getFuel();
private:
	// Constants
	double weight  = 15103.00; // kg
	const double gravity =   -1.625; // m/s^2
	const double vThrust = 45000.00; // N
	const double hThrust =   450.00; // N
	const int    width   =       20; // m
	
	// Variables
	double vVelocity;
	double hVelocity;
	double angle;
	Point position;
	bool isThrusting;
	bool isThrustingLeft;
	bool isThrustingRight;
	double fuel = 5000;
	// Calculations
	double computeAcceleration(double thrust, double weight, double gravity = 0.0);
	double convertDegreesToRadians(double degrees);
	double computeTotalVelocity();
	double getVerticalAcceleration();
	double getHorizontalAcceleration();
	LanderStatus getFlightStatus(double groundElevation);
	// Update Variables
	void updateVelocity(double seconds);
	void updateAltitude(double seconds);
	void updateHDisplacement(double seconds);
	void incrementAngle();
	void decrementFuel(double seconds);

};


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
	void incrementTime(int seconds);
	void changeAngle(double angle);
	// Show Progress
	void displayStatus();
#ifndef DEBUG
private:
#endif
	// Constants
	const double weight =  15103.00; // kg
	const double gravity =   -1.625; // m/s^2
	const double vThrust = 45000.00; // N
	const double hThrust =   450.00; // N
	// Variables
	double vVelocity;
	double hVelocity;
	double angle;
	double altitude;
	double xDisplacement = 0;
	int seconds = 0;
	// Calculations
	double computeAcceleration(double thrust, double weight, double gravity = 0.0);
	double convertDegreesToRadians(double degrees);
	double computeTotalVelocity();
	double getVerticalAcceleration();
	double getHorizontalAcceleration();
	// Update Variables
	void updateVelocity(int seconds);
	void updateAltitude(int seconds);
	void updateHDisplacement(int seconds);
};


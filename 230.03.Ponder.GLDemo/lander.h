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
#include "uiDraw.h"

enum LanderStatus
{
	STILL_IN_AIR,
	HARD_LANDING,
	SOFT_LANDING,
	CRASHED
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
	Lander(Point ptUpperRight);
	// Update Data
	void incrementTime(double seconds);
	void changeAngle(double angle);
	void setVerticalThrusters(bool isThrusting);
	void setLeftThruster(bool isThrusting);
	void setRightThruster(bool isThrusting);
	void landed();
	void crashed();
	void reset(Point ptUpperRight);
	// getters
	int getWidth();
	double getFuel();
	double getSpeed();
	double getAngle();
	Point getPosition();
	LanderStatus getFlightStatus();
	//draw
	void draw(ogstream& gout, bool isUp, bool isRight, bool isLeft);
private:
	// Constants
	double weight =        15103.00; // kg
	const double gravity =   -1.625; // m/s^2
	const double vThrust = 45000.00; // N
	const double hThrust =   450.00; // N
	const int    width   =       20; // m
	// Variables
	double vVelocity;
	double hVelocity;
	double angle;
	Point position;
	bool isThrusting = false;
	bool isThrustingLeft = false;
	bool isThrustingRight = false;
	double fuel = 5000;
	LanderStatus status = STILL_IN_AIR;
	// Calculations
	double computeAcceleration(double thrust, double weight, double gravity = 0.0);
	double convertDegreesToRadians(double degrees);
	double computeTotalVelocity();
	double getVerticalAcceleration();
	double getHorizontalAcceleration();
	// Update Variables
	void updateVelocity(double seconds);
	void updateAltitude(double seconds);
	void updateHDisplacement(double seconds);
	void incrementAngle();
	void decrementFuel(double seconds);

};


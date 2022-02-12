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
#include "landerSettings.h"


 /*************************
  * LANDER
  * This constructor takes the initial vertical velocity, the initial 
  * horizontal velocity, the initial altitude, and the angle of the 
  * lander as parameters and sets the associated member variables 
  * accordingly
  *************************/
Lander::Lander(LanderSettings settings)
{
   reset(settings);
}

/*************************
 * INCREMENT TIME
 * This method increments the time forward by a specified number of 
 * seconds and then calculates what the new velocities and positions 
 * will be due to this change in time. 
 *************************/
void Lander::incrementTime(double seconds)
{
   if (getFlightStatus() == STILL_IN_AIR)
   {
   	  updateVelocity(seconds);
   	  updateHDisplacement(seconds);
   	  updateAltitude(seconds);
   	  decrementFuel(seconds);
   	  incrementAngle(seconds);
   }
}

/*************************
 * GET VERTICAL ACCELERATION
 * This method returns the current vertical acceleration.
 *************************/
double Lander::getVerticalAcceleration()
{
   double radians = angle;
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
   double radians = angle;
   double force = 0;
   if (isThrusting)
   	  force = hThrust * sin(radians);
   return computeAcceleration(force, weight) * 100;
}


/*************************
 * GET FLIGHT STATUS
 * Returns if the lander is still in the air, crashed, or landed.
 *************************/
LanderStatus Lander::getFlightStatus()
{
   return status;
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
void Lander::incrementAngle(double seconds)
{
   double angleAcceleration;
   if (isThrustingLeft) 
   {
   	  /*angleAcceleration = weight / 450;*/
   	  this->angle = this->angle + (0.5 * seconds);
   }
   else if (isThrustingRight)
   {
   	  //angleAcceleration = (weight / 450) * -1;
   	  this->angle = this->angle - (0.5 * seconds);
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
   {
   	  weight += abs(fuel);
   	  fuel = 0.0;
   }
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
 * LANDED
 * Signals to the lander that is has landed on the landing pad. The 
 * status of the lander will be updated according to the velocity during
 * the landing. 
 *************************/
void Lander::landed()
{
   if (abs(getSpeed()) > 4.0)
      this->status = CRASHED;
   else if (abs(getSpeed()) <= 2.0)
      this->status = SOFT_LANDING;
   else
      this->status = HARD_LANDING;
}

/*************************
 * CRASHED
 * Signals to the lander that it has crashed into the ground. Changes
 * the status accordingly.
 *************************/
void Lander::crashed()
{
   status = CRASHED;
}

/*************************
 * RESET
 * Resets the lander to new settings so another game can be played.
 *************************/
void Lander::reset(LanderSettings settings)
{
   fuel = settings.getFuel();
   hVelocity = settings.getHVelocity();
   vVelocity = settings.getVVelocity();
   angle = settings.getAngle();
   position.setX(settings.getPosition().getX());
   position.setY(settings.getPosition().getY());

   status = STILL_IN_AIR;
   isThrusting = false;
   isThrustingLeft = false;
   isThrustingRight = false;
   weight = 10103.00 + fuel;
}


/*************************
 * GET SPEED
 * returns the speed.
 *************************/
double Lander::getSpeed()
{
   return computeTotalVelocity();
}

/*************************
 * GET LM POSITION
 * Returns the LM position.
 *************************/
Point Lander::getPosition()
{
   return position;
}

/*************************
 * DRAW
 * Draws the lander on the screen and, if the lander is still 
 * flying and has fuel, its flame. 
 *************************/
void Lander::draw(ogstream& gout)
{
   //lander
   gout.drawLander(getPosition(), getAngle());
   
   if (getFlightStatus() == STILL_IN_AIR && getFuel() > 0.0)
   	  gout.drawLanderFlames
        (
           getPosition(), getAngle(), isThrusting, 
           isThrustingLeft, isThrustingRight
        );
}

/*************************
 * GET ANGLE
 * Returns the LM angle
 *************************/
double Lander::getAngle()
{
   return angle;
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



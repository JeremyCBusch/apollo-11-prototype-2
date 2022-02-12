#pragma once
#include "point.h"
#include <cassert>

enum AngleType {
   DEGREES, RADIANS
};

class LanderSettings
{
public:
	LanderSettings(Point ptUpperRight,
      double hVelocity = 0.0, double vVelocity = 0.0, 
      AngleType angleType = RADIANS, double angle = 0.0, 
      double fuel = 5000.0);
   void setPosition(Point position);
   void setHVelocity(double hVelocity);
   void setVVelocity(double vVelocity);
   void setAngle(AngleType angleType, double angle);
   void setFuel(double fuel);

   double getFuel();
   double getAngle();
   double getVVelocity();
   double getHVelocity();
   const Point & getPosition();
private:
   Point ptUpperRight;
   Point position;
   double hVelocity;
   double vVelocity;
   double angle;
   double fuel;
};


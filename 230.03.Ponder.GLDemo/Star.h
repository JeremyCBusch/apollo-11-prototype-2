#pragma once

#include "point.h"
#include "uiDraw.h"

/*************************
 * Star:
 * This class represents a star. Which has a position and increments phase.
 *************************/
class Star
{
public:
	// constructor
   Star(const Point& point);
   // output
   void draw(ogstream & gout);
private:
	// member variables
	unsigned char phase;
	Point point;
	// private method
	void incrementPhase();
};


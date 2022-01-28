#pragma once

#include "point.h"
/*************************
 * Star:
 * This class represents a star. Which has a position and increments phase.
 *************************/
class Star
{
public:
	Star(const Point& point, unsigned char phase);

	void incrementPhase();
	const Point& getPoint();
	unsigned char getPhase();
private:
	unsigned char phase;
	Point point;
};


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
	Star(const Point& point, unsigned char phase);

	const Point& getPoint();
	unsigned char getPhase();
	void draw(ogstream & gout);
private:
	unsigned char phase;
	Point point;
	void incrementPhase();
};


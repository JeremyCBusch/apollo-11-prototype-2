#include "Star.h"

Star::Star(const Point& point, unsigned char phase)
{
	this->point = Point(point.getX(), point.getY());
	this->phase = phase;
}

void Star::incrementPhase()
{
	phase++;
}

const Point& Star::getPoint()
{
	return point;
}

unsigned char Star::getPhase()
{
	return phase;
}

#include "Star.h"

Star::Star(const Point& upperRight)
{
	this->point = Point(random(0.0, upperRight.getX()), random(50.0, upperRight.getY()));
	this->phase = (unsigned char)random(0, 255);
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

void Star::draw(ogstream& gout)
{
	gout.drawStar(this->point, this-> phase);
	this->incrementPhase();
}

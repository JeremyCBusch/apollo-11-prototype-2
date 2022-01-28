#pragma once

#include "point.h"

class Star
{
public:
	Star(const Point& point, unsigned char phase)
	{
		this->point = Point(point.getX(), point.getY());
		this->phase = phase;
	}

	void incrementPhase()
	{
		phase++;
	}

	const Point & getPoint()
	{
		return point;
	}

	unsigned char getPhase()
	{
		return phase;
	}

private:
	unsigned char phase;
	Point point;
};


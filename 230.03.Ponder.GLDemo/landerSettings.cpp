#include "landerSettings.h"

LanderSettings::LanderSettings(Point ptUpperRight, double hVelocity, 
	double vVelocity, AngleType angleType, double angle, double fuel) :
	hVelocity(hVelocity), vVelocity(vVelocity), fuel(fuel),
	ptUpperRight(ptUpperRight.getX(), ptUpperRight.getY()),
	position
	(
		ptUpperRight.getX() - (ptUpperRight.getX() / 8),
		ptUpperRight.getY() - (ptUpperRight.getY() / 5)
	)
{
	assert(ptUpperRight.getX() > 0.0);
	assert(ptUpperRight.getY() > 0.0);
	setAngle(angleType, angle);
}

void LanderSettings::setPosition(Point position)
{
	assert(position.getY() >= (ptUpperRight.getY() / 2));
	this->position = position;
}

void LanderSettings::setHVelocity(double hVelocity)
{
	this->hVelocity = hVelocity;
}

void LanderSettings::setVVelocity(double vVelocity)
{
	this->vVelocity = vVelocity;
}

double convertDegreesToRadians(double degrees)
{
	const double pi = 3.14159265358979323846;
	return (2 * pi * degrees) / 360;
}

void LanderSettings::setAngle(AngleType angleType, double angle)
{
	if (angleType == DEGREES)
	{
		this->angle = convertDegreesToRadians(angle);
	}
	else if (angleType == RADIANS)
	{
		this->angle = angle;
	}
}

void LanderSettings::setFuel(double fuel)
{
	if (fuel < 0.0)
	{
		throw "Fuel cannot be a negative value";
	}
	this->fuel = fuel;
}

double LanderSettings::getFuel()
{
	return fuel;
}

double LanderSettings::getAngle()
{
	return angle;
}

double LanderSettings::getVVelocity()
{
	return vVelocity;
}

double LanderSettings::getHVelocity()
{
	return hVelocity;
}

const Point & LanderSettings::getPosition()
{
	return position;
}

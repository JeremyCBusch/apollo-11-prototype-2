#include "Star.h"

/*************************
 * STAR
 * Constructor for a star. Automatically chooses
 * a location in the sky within the bounds set by
 * its parameter. We know that they don't need to
 * follow any particular pattern so its location
 * is chosen randomly.
 *************************/
Star::Star(const Point& upperRight)
{
   this->point = Point(random(0.0, upperRight.getX()), random(50.0, upperRight.getY()));
   this->phase = (unsigned char)random(0, 255);
}

/*************************
 * INCREMENT PHASE
 * Increments the "phase" of the star. The phase
 * determines how brightly the star will shine. 
 *************************/
void Star::incrementPhase()
{
   phase++;
}

/*************************
 * DRAW
 * Draws the star on the screen in its next 
 * incremented phase.
 *************************/
void Star::draw(ogstream& gout)
{
   this->incrementPhase();
   gout.drawStar(this->point, this->phase);
}

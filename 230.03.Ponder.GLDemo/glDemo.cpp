/*************************************************************
 * 1. Name:
 *      Jacob Morgan, Jeremy Busch
 * 2. Assignment Name:
 *      Lab 04: Apollo 11 Visuals
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was integrating the LM with the graphicson the screen. We
 *      had lots of quirks with the lander going in the wrong direction and the lander only 
 *      starting at the left side of the screen.
 * 5. How long did it take for you to complete the assignment?
 *      4 hours
 *****************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "Star.h"
#include <vector>
#include "lander.h"
#include <cmath>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const double FPS = 10.0;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
    Demo(const Point& ptUpperRight) :
        ground(ptUpperRight),
        LM(1.16, 0.0, SCREEN_HEIGHT - (SCREEN_HEIGHT / 4.0), 0.0)
    {
        for (int i = 0; i < 50; i++)
        {
            ptStars.push_back(Star(Point(random(0.0, ptUpperRight.getX()), random(50.0, ptUpperRight.getY())), random(0, 255)));
        }
    }

    // this is just for test purposes.  Don't make member variables public!

    Point ptUpperRight;   // size of the screen
    Ground ground;
    vector<Star> ptStars;
    Lander LM;
    
};

/*************************
 * GET GROUND ELEVATION 
 * returns the distance between the lander and the ground.
 *************************/
double getGroundElevation(double x, double landerWidth)
{
    return 0.0;
}

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
    ogstream gout;

    

    // the first step is to cast the void pointer into a game object. This
    // is the first step of every single callback function in OpenGL. 
    Demo* pDemo = (Demo*)p;
    
    
    // move the ship around
    if (pUI->isRight())
        pDemo->LM.setRightThruster(true);
    else
        pDemo->LM.setRightThruster(false);
    if (pUI->isLeft())
        pDemo->LM.setLeftThruster(true);
    else
        pDemo->LM.setLeftThruster(false);
    if (pUI->isUp())
        pDemo->LM.setVerticalThrusters(true);
    else
        pDemo->LM.setVerticalThrusters(false);


    // check if we are still able to continue
    if (pDemo->ground.onPlatform(pDemo->LM.getLMPosition(), pDemo->LM.getWidth()))
    {
        // TODO: Check the velocity to see if it would be a soft, hard, or crash landing
        gout.setPosition(Point((SCREEN_WIDTH / 2.0) - 80, SCREEN_HEIGHT - 120.0));
        gout << "Landed at: " << abs(pDemo->LM.getSpeed()) << " m/s " << std::endl;
        if (abs(pDemo->LM.getSpeed()) > 4.0)
            gout << "      Crash Landing";
        else if (abs(pDemo->LM.getSpeed()) <= 2.0)
            gout << "      Soft Landing";
        else
            gout << "      Hard Landing";
    }
    else if (pDemo->ground.hitGround(pDemo->LM.getLMPosition(), pDemo->LM.getWidth()))
    {
        // TODO: Blow the thing up
        gout.setPosition(Point((SCREEN_WIDTH / 2.0) - 110, SCREEN_HEIGHT - 120.0));
        gout << "You crashed and killed Buzz Aldrin";
    }
    else
    {
        pDemo->LM.incrementTime(1.0 / FPS);
    }


    // draw our little stars
    for (Star & star : pDemo->ptStars)
    {
        star.draw(gout);
    }

    // draw the ground
    pDemo->ground.draw(gout);

    // draw the lander and its flames
    pDemo->LM.draw(gout, pUI->isUp(), pUI->isRight(), pUI->isLeft());

    // put some text on the screen
    // need to add speed fuel and altitude  
    

    //setting the text on the screen
    gout.setPosition(Point(30.0, SCREEN_HEIGHT - 45.0));
    gout << "The Jeremy Experience TM"  << "\n";
    gout.setPosition(Point(30.0, SCREEN_HEIGHT - 60.0));
    gout << "Fuel: " << pDemo->LM.getFuel() << "\n";
    gout.setPosition(Point(30.0, SCREEN_HEIGHT - 75.0));
    gout << "Altitude: " <<  pDemo->LM.getLMPosition().getY() << "\n";
    gout.setPosition(Point(30.0, SCREEN_HEIGHT - 90.0));
    gout << "Speed: " << abs(pDemo->LM.getSpeed()) << "\n";
    
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my Demo type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ PWSTR pCmdLine,
    _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
    // Initialize OpenGL
    Point ptUpperRight(SCREEN_WIDTH, SCREEN_HEIGHT);
    Interface ui(0, NULL,
        "Open GL Demo",
        ptUpperRight);

    // Initialize the game class
    Demo demo(ptUpperRight);

    // set everything into action
    ui.run(callBack, &demo);

    return 0;
}


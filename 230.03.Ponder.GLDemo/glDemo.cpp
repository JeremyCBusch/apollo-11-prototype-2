/*************************************************************
 * 1. Name:
 *      Jacob Morgan, Jeremy Busch
 * 2. Assignment Name:
 *      Lab 04: Apollo 11 Visuals
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      gettting the lander object created. We had an error where the header file wasn't put   
 *      in the header file folder that caused an error code that we didn't recognize.
 * 5. How long did it take for you to complete the assignment?
 *      3 hours
 *****************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "Star.h"
#include <vector>
#include "lander.h"
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
    Demo(const Point& ptUpperRight) :
        angle(0.0),
        ground(ptUpperRight),
        LM(1.16, 0.0, 0.0, 0.0)
    {
        for (int i = 0; i < 50; i++)
        {
            ptStars.push_back(Star(Point(random(0.0, ptUpperRight.getX()), random(50.0, ptUpperRight.getY())), random(0, 255)));
        }
    }

    // this is just for test purposes.  Don't make member variables public!

    Point ptUpperRight;   // size of the screen
    double angle;         // angle the LM is pointing
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
    
    pDemo->LM.incrementTime(1.0 / 30.0);
    if (pDemo->ground.onPlatform(pDemo->LM.getLMPosition(), pDemo->LM.getWidth()))
        std::cout << "We hit the ground boiz" << std::endl;
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
    
    pDemo->LM.incrementAngle(0.0);
    // draw our little stars
    for (Star & star : pDemo->ptStars)
    {
        gout.drawStar(star.getPoint(), star.getPhase());
        star.incrementPhase();
    }

    // draw the ground
    pDemo->ground.draw(gout);

    // draw the lander and its flames
    gout.drawLander(pDemo->LM.getLMPosition() /*position*/, pDemo->LM.getAngle() /*angle*/);
    gout.drawLanderFlames(pDemo->LM.getLMPosition(), pDemo->LM.getAngle(), /*angle*/
        pUI->isUp(), pUI->isLeft(), pUI->isRight());

    // put some text on the screen
    // need to add speed fuel and altitude  
    

    //setting the text on the screen
    gout.setPosition(Point(30.0, 755.0));
    gout << "The Jeremy Experience TM"  << "\n";
    gout.setPosition(Point(30.0, 740.0));
    gout << "Fuel: N/A" << "\n";
    gout.setPosition(Point(30.0, 725.0));
    gout << "Altitude: " <<  pDemo->LM.getLMPosition().getY() << "\n";
    gout.setPosition(Point(30.0, 710.0));
    gout << "Speed: " << pDemo->LM.getSpeed() << "\n";
    
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
    Point ptUpperRight(800.0, 800.0);
    Interface ui(0, NULL,
        "Open GL Demo",
        ptUpperRight);

    // Initialize the game class
    Demo demo(ptUpperRight);

    // set everything into action
    ui.run(callBack, &demo);

    return 0;
}


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
#include "game.h"
#include <cmath>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const double FPS = 10.0;

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
    Game* game = (Game*)p;
    game->update(pUI);
    game->draw(pUI);
    if (game->isGameOver() && pUI->isSpace())
        game->reset();
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
    Game game(ptUpperRight, FPS);

    // set everything into action
    ui.run(callBack, &game);

    return 0;
}


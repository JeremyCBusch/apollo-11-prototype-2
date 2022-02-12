/*************************************************************
 * 1. Name:
 *      Jacob Morgan, Jeremy Busch
 * 2. Assignment Name:
 *      Lab 06: Apollo 11 Simulation
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      We had a hard time finding a simeple bug. We didn't realize
 *      that we needed to pass in the angle of the lander to the 
 *      draw method in radians. Once we realized that was our issue,
 *      we didn't have too many problems.
 * 5. How long did it take for you to complete the assignment?
 *      4.5 hours
 *****************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "game.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const unsigned short BASE_FPS = 10;

/*************************************
 * CALLBACK
 * This function is called by open GL 30 times per second.
 * This function runs the core functionality of the game. 
 * It updates the game, draws it, and, if it is over and the
 * user presses space, resets the game. 
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   Game* game = (Game*)p;

   Controls controls;
   controls.up    = pUI->isUp();
   controls.down  = pUI->isDown();
   controls.left  = pUI->isLeft();
   controls.right = pUI->isRight();
   controls.space = pUI->isSpace();
   game->update(controls);
   game->draw();
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
   Game game(ptUpperRight, BASE_FPS);

   // set everything into action
   ui.run(callBack, &game);

   return 0;
}


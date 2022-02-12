#pragma once

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "Star.h"
#include <vector>
#include "lander.h"
#include <cmath>

/*************************
 * GAME
 * This class represents the game as a whole.
 * It controls the overall logic of the game
 * and controls what you see on the screen. 
 * It controls setup and takedown as well. 
 *************************/
class Game
{
public:
   // Constructors/Destructors
   Game() = delete;
   Game(const Point& ptUpperRight, int FPS);
   // Display
   void draw(const Interface* pUI);
   // Handle game logic
   void update(const Interface* pUI);
   bool isGameOver();
   // Start / Reset the game
   void reset();
private:
   // Variables
   Point ptUpperRight;   // size of the screen
   Ground ground;
   std::vector<Star> ptStars;
   Lander LM;
   int FPS;
   // Display
   ogstream gout;
   void displayStatus();
   void displayLMStats();
};

#pragma once

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "Star.h"
#include <vector>
#include "lander.h"
#include "difficulty.h"
#include <cmath>

struct Controls {
   bool space;
   bool up;
   bool down;
   bool left;
   bool right;
};

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
   Game(const Point& ptUpperRight, unsigned short FPS);
   // Display
   void draw();
   // Handle game logic
   void update(const Controls controls);
   bool isGameOver();
   // Start / Reset the game
   void reset();
private:
   // Variables
   Point ptUpperRight;   // size of the screen
   Ground ground;
   std::vector<Star> ptStars;
   Lander LM;
   unsigned short FPS;
   Difficulty difficulty;
   // Display
   ogstream gout;
   void displayStatus();
   void displayLMStats();
   void displayDifficulty();
   // Difficulty for next game
   void updateDifficulty(const Controls controls);
   // need this so the difficulty is only incremented once per press
   bool prevUp = false; 
   bool prevDn = false;
};


#include "game.h"
#include "landerSettings.h"

/*************************
 * GAME
 * Constructor for the game. Sets up the different 
 * objects that will appear on screen and settings 
 * which will dictate how the game will be played.
 *************************/
Game::Game(const Point& ptUpperRight, unsigned short FPS) : 
   LM(LanderSettings(ptUpperRight, 10.0, -2.0, DEGREES, 0.0)), 
   FPS(FPS), ptUpperRight(ptUpperRight), ground(ptUpperRight),
   difficulty(0)
{
   for (int i = 0; i < 50; i++)
   {
      ptStars.push_back(Star(ptUpperRight));
   }
}

/*************************
 * DRAW
 * Draws all game objects with visible interfaces
 * onto the screen. 
 *************************/
void Game::draw()
{
   // draw our little stars
   for (Star& star : ptStars)
   {
      star.draw(gout);
   }

   // draw the ground
   ground.draw(gout);

   // draw the lander and its flames
   LM.draw(gout);

   // put some text on the screen
   displayStatus();
   displayLMStats();
   if (isGameOver())
      displayDifficulty();
}

/*************************
 * UPDATE
 * This method handles the core logic of the game. 
 * Using the user's input and the amount of time 
 * that passes between frames, it updates positional
 * and relational data for each game object. 
 *************************/
void Game::update(const Controls controls)
{
   // move the ship around
   if (controls.right)
      LM.setRightThruster(true);
   else
      LM.setRightThruster(false);
   if (controls.left)
      LM.setLeftThruster(true);
   else
      LM.setLeftThruster(false);
   if (controls.up)
      LM.setVerticalThrusters(true);
   else
      LM.setVerticalThrusters(false);

   // see if we have landed or crashed yet
   if (ground.onPlatform(LM.getPosition(), LM.getWidth()))
      LM.landed();
   else if (ground.hitGround(LM.getPosition(), LM.getWidth()))
      LM.crashed();

   // update the position and speed of the lander
   LM.incrementTime(1.0 / (FPS - difficulty));

   if (isGameOver())
      updateDifficulty(controls);
}

/*************************
 * IS GAME OVER
 * Returns true if the game has ended.
 *************************/
bool Game::isGameOver()
{
   return LM.getFlightStatus() != STILL_IN_AIR;
}

/*************************
 * RESET
 * Resets all game objects to their default positions
 * so that the player is able to play the game again.
 *************************/
void Game::reset()
{
   ground.reset();
   LM.reset(LanderSettings(ptUpperRight, 10.0 * difficulty, -2.0 * difficulty, DEGREES, 330.0 - 4 * difficulty));
   ptStars.clear();
   for (int i = 0; i < 50; i++)
   {
      ptStars.push_back(Star(ptUpperRight));
   }
}

/*************************
 * DISPLAY STATUS
 * Displays the status of the lander if it has crashed or
 * landed. If landed it includes the velocity in it's status.
 *************************/
void Game::displayStatus()
{
   if (LM.getFlightStatus() == STILL_IN_AIR)
      return;
   else if (LM.getFlightStatus() == CRASHED)
   {
      gout.setPosition(Point((ptUpperRight.getX() / 2.0) - 110, ptUpperRight.getY() - 120.0));
      gout << "You crashed and killed Buzz Aldrin";
   }
   else
   {
      gout.setPosition(Point((ptUpperRight.getX() / 2.0) - 80, ptUpperRight.getY() - 100));
      gout << "Landed at: " << abs(LM.getSpeed()) << " m/s " << std::endl;
      if (LM.getFlightStatus() == HARD_LANDING)
         gout << "      Hard Landing";
      else
         gout << "      Soft Landing";
   }
   gout.setPosition(Point((ptUpperRight.getX() / 2.0) - 110, ptUpperRight.getY() - 135.0));
   gout << " Press the space bar to play again";
}

/*************************
 * DISPLAY LM STATS
 * Shows what the current state of the lander is at any 
 * given time in the upper left hand corner of the screen. 
 *************************/
void Game::displayLMStats()
{
   //setting the text on the screen
   gout.setPosition(Point(30.0, ptUpperRight.getX() - 45.0));
   gout << "The Jeremy Experience TM" << "\n";
   gout.setPosition(Point(30.0, ptUpperRight.getX() - 60.0));
   gout << "Fuel: " << LM.getFuel() << "\n";
   gout.setPosition(Point(30.0, ptUpperRight.getX() - 75.0));
   gout << "Altitude: " << LM.getPosition().getY() << "\n";
   gout.setPosition(Point(30.0, ptUpperRight.getX() - 90.0));
   gout << "Speed: " << abs(LM.getSpeed()) << "\n";
}

void Game::displayDifficulty()
{
   gout.setPosition(Point((ptUpperRight.getX() / 2.0) - 150.0, (ptUpperRight.getY() / 2.0) + 125));
   gout << "Select next rounds difficulty using your arrow keys:";
   gout.setPosition(Point((ptUpperRight.getX() / 2.0) - 60.0, (ptUpperRight.getY() / 2.0) + 105.0));
   gout << "Difficulty: " << difficulty.toString();

}

void Game::updateDifficulty(const Controls controls)
{
   if (controls.down && !prevDn)
   {
      difficulty++;
      prevDn = true;
   }
   else if (!controls.down)
      prevDn = false;
   if (controls.up && !prevUp)
   {
      difficulty--;
      prevUp = true;
   }
   else if (!controls.up)
      prevUp = false;
}

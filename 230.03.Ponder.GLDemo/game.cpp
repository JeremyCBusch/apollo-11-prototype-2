#include "game.h"

/*************************
 * GAME
 * Constructor for the game. Sets up the different 
 * objects that will appear on screen and settings 
 * which will dictate how the game will be played.
 *************************/
Game::Game(const Point& ptUpperRight, int FPS) : 
   ptUpperRight(ptUpperRight), ground(ptUpperRight), 
   LM(ptUpperRight), FPS(FPS)
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
void Game::draw(const Interface* pUI)
{
   // draw our little stars
   for (Star& star : ptStars)
   {
      star.draw(gout);
   }

   // draw the ground
   ground.draw(gout);

   // draw the lander and its flames
   LM.draw(gout, pUI->isUp(), pUI->isRight(), pUI->isLeft());

   // put some text on the screen
   displayStatus();
   displayLMStats();
}

/*************************
 * UPDATE
 * This method handles the core logic of the game. 
 * Using the user's input and the amount of time 
 * that passes between frames, it updates positional
 * and relational data for each game object. 
 *************************/
void Game::update(const Interface* pUI)
{
   // move the ship around
   if (pUI->isRight())
      LM.setRightThruster(true);
   else
      LM.setRightThruster(false);
   if (pUI->isLeft())
      LM.setLeftThruster(true);
   else
      LM.setLeftThruster(false);
   if (pUI->isUp())
      LM.setVerticalThrusters(true);
   else
      LM.setVerticalThrusters(false);

   // see if we have landed or crashed yet
   if (ground.onPlatform(LM.getPosition(), LM.getWidth()))
      LM.landed();
   else if (ground.hitGround(LM.getPosition(), LM.getWidth()))
      LM.crashed();

   // update the position and speed of the lander
   LM.incrementTime(1.0 / FPS);
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
   LM.reset(ptUpperRight);
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
      gout.setPosition(Point((ptUpperRight.getX() / 2.0) - 80, ptUpperRight.getY() - 101));
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

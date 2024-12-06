#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include "Food.h"  // Include the Food class header ******

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;

        Food food;  // Food object to store food information ****

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // is this one needed at all? Why or why not?
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        void incrementScore();
        
        // More methods should be added here
        void generateFood(const objPos& blockOff); // generate food avoiding blocks****
        objPos getFoodPos() const;  // get the position of the food****
        bool getLoseFlag() const; //new ------
        bool getExitFlag() const; //new -----
};

#endif
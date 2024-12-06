#include "GameMechs.h"
#include "MacUILib.h"

#include <cstdlib>  // For rand() and srand()****
#include <ctime>    // For time()******

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 40;
    boardSizeY = 20;

    srand(time(0));  // Seed the random number generator****
    food.generateFood(objPos(5, 5, '@'));  // (5, 5)****

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;

    srand(time(0));  // Seed the random number generator****
    food.generateFood(objPos(5, 5, '@'));  // Generate food at a random location****

}

// do you need a destructor?
GameMechs::~GameMechs()
{
    //nothing on the heap
    //destructir can stay empty for now
    if (food.foodPos.pos != nullptr) {
        delete food.foodPos.pos;
        food.foodPos.pos = nullptr;
    }
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput()
{
    if (MacUILib_hasChar()) //checks if there is any input character waiting to be processed
    {
        input = MacUILib_getChar(); //once hasChar confirms there is an input, getChar retrieved the character and stores it in a variable input
    
    }
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;   
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

// More methods should be added here
void GameMechs::generateFood(const objPos& blockOff) {
    int foodX, foodY;
    do {
        foodX = rand() % (boardSizeX-3)+2;  // x position
        foodY = rand() % (boardSizeY-3)+2;  // y position
    } while (foodX == blockOff.pos->x && foodY == blockOff.pos->y);  // Ensure food does not overlap with a block

    food.foodPos.pos->x = foodX;
    food.foodPos.pos->y = foodY;
}

objPos GameMechs::getFoodPos() const {
    return food.foodPos;
}

//Return the exit flag status ----
bool GameMechs::getExitFlag() const { 
        return exitFlag;  
    }

// Return the lose flag status ---
bool GameMechs::getLoseFlag() const { 
        return loseFlag;  
    }
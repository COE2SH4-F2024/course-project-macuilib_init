#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; // GLOBAL POINTER meant to instantiate a player object on the heap
GameMechs *myGM;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs();
    myPlayer = new Player(myGM); //created new object DESTROY IT IMMEDIATELEY
}

void GetInput(void)
{
    if(MacUILib_hasChar())
    {
        char input = MacUILib_getChar();
        myGM->setInput(input);
    }

    myPlayer->updatePlayerDir(); 
}

void RunLogic(void)
{
    char input = myGM->getInput();

    if (input == ' ')
    {
        myGM->setExitTrue();
    }

    if (input == 'i') //debugging
    {
        myGM->incrementScore();
    }

    if (input == 'l') //debugging
    {
        myGM->setLoseFlag();
        myGM->setExitTrue();
    }
    // Check loseFlag set to true ----
    if (myGM->getLoseFlag()) {
        MacUILib_printf("Game Over!\n");  // Print  "Game Over" ------
    }

    myPlayer->movePlayer();

    // FOOD LOGIC *****
    if (myPlayer->getPlayerPos()->getHeadElement().pos->x == myGM->getFoodPos().pos->x &&
        myPlayer->getPlayerPos()->getHeadElement().pos->y == myGM->getFoodPos().pos->y) 
    {
        myGM->incrementScore();  // Increase score
        myGM->generateFood(myPlayer->getPlayerPos()->getHeadElement());  // Generate new food
    }

    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    /*// Check loseFlag set to true ----
    if (myGM->getLoseFlag()) {
        MacUILib_printf("Game Over!\n");  // Print  "Game Over" ------
    } else {
        // continue with game ------*/
        objPosArrayList* snakeBody = myPlayer -> getPlayerPos();
        objPos foodPos = myGM->getFoodPos();  // Get food position from GameMechs****
    
    
    

    int i, j, k;

    const int boardX = myGM -> getBoardSizeX();
    const int boardY = myGM -> getBoardSizeY();

    for (i = 0; i < boardY; i++)
    {
        for (j = 0; j < boardX; j++)
        {
            if ((i == 0 || i == boardY-1) || (j == 0 || j == boardX-1))
            {
                MacUILib_printf("#"); // border
            }
            else 
            {
                bool partOfSnake = false;

                for (k = 0; k < snakeBody->getSize(); k++)
                {
                    objPos bodyPart = snakeBody->getElement(k);
                    if (i == bodyPart.pos->y && j == bodyPart.pos->x)
                    {
                        MacUILib_printf("%c", bodyPart.symbol); //print @ directly in the middle
                        partOfSnake = true;
                        break;
                        
                    }
                }

                if (!partOfSnake)
                {
                    if (i == foodPos.pos->y && j == foodPos.pos->x)  // Check for food position****
                    {
                      MacUILib_printf("%c", foodPos.symbol);  // Print food symbol *****  
                    }
                    else
                    {
                        MacUILib_printf(" ");
                    }
                }
            }
        }
        MacUILib_printf("\n");
    }
   

    MacUILib_printf("Score: %d\n", myGM->getScore());

    
}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen(); 

    //messages
    if(myGM->getLoseFlagStatus())  
    {
        MacUILib_printf("Game Over Loser!\n");
    } 
    else
    {
        MacUILib_printf("Game Over: You Left The Game.\n");
    }

   delete myPlayer;
    myPlayer = nullptr;
    delete myGM;
    myGM = nullptr;

    MacUILib_uninit();
}

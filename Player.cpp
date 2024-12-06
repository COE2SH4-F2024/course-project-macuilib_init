#include "Player.h"
#include <cstdlib>


Player::Player(GameMechs* thisGMRef) //constructor just initializes things
{
    mainGameMechsRef = thisGMRef;
    direction = STOP;

    // more actions to be included
    //initialize the player

    playerPosList = new objPosArrayList(); //INSTANTIATED!!

    //MORE CHANGES!!
    objPos initPos;
    initPos.pos = new Pos;
    initPos.pos->x = mainGameMechsRef -> getBoardSizeX() / 2;
    initPos.pos->y = mainGameMechsRef -> getBoardSizeY() / 2;
    initPos.symbol = '@';

    //ADDING HEAD POSITION
    playerPosList->insertHead(initPos);

}


Player::~Player() //destroys anything on the heap
{
    // delete any heap members here
    //no keyword "new" in the constructor
    //leave destructor empty FOR NOW
    for (int i = 0; i < playerPosList->getSize(); i++) {
        objPos element = playerPosList->getElement(i);
        delete element.pos;  // Free dynamically allocated `pos`
        element.pos = nullptr;
    }
    delete playerPosList;
    playerPosList = nullptr;
    
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList; //RETURN HEAD ELEMENT!!
}

void Player::updatePlayerDir()
{
    char input  = mainGameMechsRef -> getInput();
        // PPA3 input processing logic
    if ((input == ' ')||(input == 'i')||(input == 'l')) 
    {
        return;  // Do not process direction changes if spacebar is pressed 
    }      
        switch(input)
        {                      
            // Add more key processing here
            case 'w':
            case 'W':
                if (direction == LEFT || direction == RIGHT || direction == STOP)
                {
                    direction = UP;
                }
                break;

            case 'a':
            case 'A':
                if (direction == UP || direction == DOWN || direction == STOP)
                {
                    direction = LEFT;
                }
                break;

            case 's':
            case 'S':
                if (direction == LEFT || direction == RIGHT || direction == STOP)
                {
                    direction = DOWN;
                }
                break;
            
            case 'd':
            case 'D':
                if (direction == UP || direction == DOWN || direction == STOP)
                {
                    direction = RIGHT;
                }
                break;

            // Add more key processing here    
            default:
                break;
        }

    mainGameMechsRef->clearInput();

}

void Player::movePlayer()
{

    if (mainGameMechsRef->getLoseFlag()) {
        return;  // Stop movement if player loses ----
    }

    // PPA3 Finite State Machine logic

    const int boardX = mainGameMechsRef -> getBoardSizeX();
    const int boardY = mainGameMechsRef-> getBoardSizeY();

    objPos currHead = playerPosList->getHeadElement(); //GET THE CURRENT HEAD!!

    switch (direction) //wrap around
    {
        case UP:
            currHead.pos->y--; // decrementing to go up
            if (currHead.pos->y < 1) //if its too small
            {
                currHead.pos->y = boardY - 2; //wraparound changed to make sure it doesnt go into the boundary
            }
            break;
        
        case DOWN:
            currHead.pos->y++; 
            if (currHead.pos->y > boardY - 2) // if too big
            {
                currHead.pos->y = 1; //wraparound changed, if at 0 it goes into the boundary thats why you change it to 1
            }
            break;
        
        case LEFT:
            currHead.pos->x--;
            if (currHead.pos->x < 1)
            {
                currHead.pos->x = boardX - 2;
            }
            break;
        
        case RIGHT:
            currHead.pos->x++;
            if (currHead.pos->x >= boardX - 2)
            {
                currHead.pos->x = 1;
            }
            break;
        default:
            break;
    }

    // Check for collision--------
    if (checkSelfCollision()) {
        mainGameMechsRef->setLoseFlag();  // Set the lose flag if the snake collides ---
        mainGameMechsRef->setExitTrue();  // Exit the game if a collision happens ----
        return;  // Stop ---
    }

    objPos foodConsumed = mainGameMechsRef->getFoodPos();
    if ((currHead.pos->x == foodConsumed.pos->x) && (currHead.pos->y == foodConsumed.pos->y))
    {
        playerPosList->insertHead(currHead); //ADD THE NEW HEAD
        mainGameMechsRef->incrementScore();
        objPos headPos = playerPosList->getHeadElement();  // head position
        mainGameMechsRef->generateFood(headPos);  //  or relevant position
    }
    else
    {
        playerPosList->insertHead(currHead);
        playerPosList->removeTail();
    }

    //playerPosList->insertHead(currHead); //ADD THE NEW HEAD
    //playerPosList->removeTail(); 

}

// More methods to be added

//New Method --------
bool Player::checkSelfCollision() const {
    // head position of the player---
    objPos headPos = playerPosList->getHeadElement();
    
    // Iterate through the body ---
    for (int i = 1; i < playerPosList->getSize(); i++) {
        objPos bodySegment = playerPosList->getElement(i);
        
        // Check if the head collides ---
        if (headPos.pos->x == bodySegment.pos->x && headPos.pos->y == bodySegment.pos->y) {
            return true;  // Collision detected ---
        }
    }
    
    return false;  // No collision---
}

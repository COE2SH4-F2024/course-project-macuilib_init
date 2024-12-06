#include "Food.h"
#include <cstdlib>  // For rand()

// Generate food at a random position, ensuring it doesn't overlap with a block
void Food::generateFood(const objPos& blockOff) {
    int foodX, foodY;
    do {
        foodX = rand() % 10; 
        foodY = rand() % 10;  
    } while (foodX == blockOff.pos->x && foodY == blockOff.pos->y);  // Ensure food 

    foodPos.pos->x = foodX;
    foodPos.pos->y = foodY;
    foodPos.symbol = 'o';
}
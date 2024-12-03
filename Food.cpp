#include "Food.h"
#include <cstdlib>  // For rand()

// Generate food at a random position, ensuring it doesn't overlap with a block
void Food::generateFood(const objPos& blockOff) {
    int foodX, foodY;
    do {
        foodX = rand() % 10;  // Random x position within board size
        foodY = rand() % 10;  // Random y position within board size
    } while (foodX == blockOff.pos->x && foodY == blockOff.pos->y);  // Ensure food doesn't overlap with block

    foodPos.pos->x = foodX;
    foodPos.pos->y = foodY;
    foodPos.symbol = 'o';
}
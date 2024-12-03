#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"

class Food {
public:
    objPos foodPos;  // Stores the food position

    Food() {
        foodPos.pos = new Pos;
        foodPos.pos->x = 0;  // Initialize to (0,0) or a default location
        foodPos.pos->y = 0;
        foodPos.symbol = 'o';  // Food symbol
    }

    ~Food() {
        delete foodPos.pos;  // Free the dynamically allocated memory
    }

    void generateFood(const objPos& blockOff);  // Generate food at a random position
    objPos getFoodPos() const;  // Return food position
};

#endif // FOOD_H
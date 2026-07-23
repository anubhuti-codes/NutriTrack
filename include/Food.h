#ifndef FOOD_H
#define FOOD_H

#include <string>

class Food
{
private:
    std::string name;
    int calories;
    int protein;
    int carbs;
    int fat;

public:
    Food();

    Food(std::string name,
         int calories,
         int protein,
         int carbs,
         int fat);

    std::string getName() const;

    int getCalories() const;

    int getProtein() const;

    int getCarbs() const;

    int getFat() const;
};

#endif
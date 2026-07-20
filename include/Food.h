#ifndef FOOD_H
#define FOOD_H

#include <string>

using namespace std;

class Food
{
private:
    string name;
    int calories;
    int protein;
    int carbs;
    int fat;

public:
    Food();

    Food(string name,
         int calories,
         int protein,
         int carbs,
         int fat);

    string getName() const;

    int getCalories() const;

    int getProtein() const;

    int getCarbs() const;

    int getFat() const;
};

#endif
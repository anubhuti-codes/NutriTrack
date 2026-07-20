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

    string getName();

    int getCalories();

    int getProtein();

    int getCarbs();

    int getFat();
};

#endif
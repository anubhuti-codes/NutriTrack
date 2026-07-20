#include "../include/Food.h"

Food::Food()
{
    name = "";
    calories = 0;
    protein = 0;
    carbs = 0;
    fat = 0;
}

Food::Food(string name,
           int calories,
           int protein,
           int carbs,
           int fat)
{
    this->name = name;
    this->calories = calories;
    this->protein = protein;
    this->carbs = carbs;
    this->fat = fat;
}

string Food::getName() const
{
    return name;
}

int Food::getCalories() const
{
    return calories;
}

int Food::getProtein() const
{
    return protein;
}

int Food::getCarbs() const
{
    return carbs;
}

int Food::getFat() const
{
    return fat;
}
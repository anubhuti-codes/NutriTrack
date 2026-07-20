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

string Food::getName()
{
    return name;
}

int Food::getCalories()
{
    return calories;
}

int Food::getProtein()
{
    return protein;
}

int Food::getCarbs()
{
    return carbs;
}

int Food::getFat()
{
    return fat;
}
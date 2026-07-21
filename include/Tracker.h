#ifndef TRACKER_H
#define TRACKER_H

#include <vector>
#include <string>
#include "Food.h"

class Tracker
{
private:

    std::vector<Food> meals;

    int totalCalories;
    int totalProtein;
    int totalCarbs;
    int totalFat;
    int totalCaloriesBurned;
    int dailyGoal;

    std::vector<Food> foodDatabase;

public:

    Tracker(int goal = 2000);

    void addFood(const Food &food, int quantity = 1);

    void loadFoods();

    void displayFoods() const;

    Food* findFood(const std::string &input);

    void addMeal();

    void addExercise();

    void showExerciseSummary() const;

    void showReport() const;

    void setGoal(int goal);

    void saveHistory(const std::string &username) const;

    void reset();

};

#endif
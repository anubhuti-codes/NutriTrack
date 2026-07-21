#include "../include/Tracker.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cctype>
#include <algorithm>

using namespace std;

Tracker::Tracker(int goal)
{
    totalCalories = 0;
    totalProtein = 0;
    totalCarbs = 0;
    totalFat = 0;
    totalCaloriesBurned = 0;
    dailyGoal = goal;
}

void Tracker::setGoal(int goal)
{
    dailyGoal = goal;
}

void Tracker::addFood(const Food &food, int quantity)
{
    for(int i = 0; i < quantity; i++)
    {
        meals.push_back(food);
    }

    totalCalories += food.getCalories() * quantity;
    totalProtein += food.getProtein() * quantity;
    totalCarbs += food.getCarbs() * quantity;
    totalFat += food.getFat() * quantity;
}

void Tracker::loadFoods()
{
    foodDatabase.clear();

    ifstream file("data/foods.txt");

    if (!file.is_open())
    {
        cout << "Unable to open foods database.\n";
        return;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string name;
        string temp;

        getline(ss, name, ',');

        getline(ss, temp, ',');
        int calories = stoi(temp);

        getline(ss, temp, ',');
        int protein = stoi(temp);

        getline(ss, temp, ',');
        int carbs = stoi(temp);

        getline(ss, temp);
        int fat = stoi(temp);

        foodDatabase.push_back(
            Food(name, calories, protein, carbs, fat)
        );
    }

    file.close();
}

void Tracker::displayFoods() const
{
    cout << "\n========== FOOD DATABASE ==========\n";

    if(foodDatabase.empty())
    {
        cout << "No foods found.\n";
        return;
    }

    for(size_t i = 0; i < foodDatabase.size(); i++)
    {
        cout << i + 1 << ". "
             << left << setw(20) << foodDatabase[i].getName()
             << foodDatabase[i].getCalories()
             << " cal"
             << endl;
    }
}

Food* Tracker::findFood(const string &input)
{
    bool isNumber = true;

    for(char c : input)
    {
        if(!isdigit(c))
        {
            isNumber = false;
            break;
        }
    }

    if(isNumber)
    {
        int index = stoi(input);

        if(index >= 1 && index <= static_cast<int>(foodDatabase.size()))
        {
            return &foodDatabase[index - 1];
        }

        return nullptr;
    }

    string searchInput = input;

    transform(
        searchInput.begin(),
        searchInput.end(),
        searchInput.begin(),
        ::tolower
    );

    for(auto &food : foodDatabase)
    {
        string foodName = food.getName();

        transform(
            foodName.begin(),
            foodName.end(),
            foodName.begin(),
            ::tolower
        );

        if(foodName == searchInput)
        {
            return &food;
        }
    }

    return nullptr;
}

void Tracker::addMeal()
{
    displayFoods();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string input;

    cout << "\nEnter food number or name : ";

    getline(cin, input);

    Food *food = findFood(input);

    if(food == nullptr)
    {
        cout << "\nFood not found.\n";
        return;
    }

    int quantity;

    cout << "Enter quantity : ";

    cin >> quantity;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nInvalid quantity.\n";
        return;
    }

    if(quantity <= 0)
    {
        cout << "\nQuantity must be greater than 0.\n";
        return;
    }

    addFood(*food, quantity);

    cout << "\nFood Added Successfully.\n";
}

void Tracker::addExercise()
{
    int choice;
    int duration;
    int caloriesBurned = 0;

    cout << "\n========== EXERCISE TRACKER ==========\n";

    cout << "1. Walking\n";
    cout << "2. Running\n";
    cout << "3. Cycling\n";
    cout << "4. Skipping\n";

    cout << "\nChoose exercise : ";
    cin >> choice;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nInvalid choice.\n";
        return;
    }

    cout << "Enter duration in minutes : ";
    cin >> duration;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nInvalid duration.\n";
        return;
    }

    if(duration <= 0)
    {
        cout << "\nDuration must be greater than 0.\n";
        return;
    }

    switch(choice)
    {
        case 1:
            caloriesBurned = duration * 4;
            break;

        case 2:
            caloriesBurned = duration * 10;
            break;

        case 3:
            caloriesBurned = duration * 8;
            break;

        case 4:
            caloriesBurned = duration * 12;
            break;

        default:
            cout << "\nInvalid exercise choice.\n";
            return;
    }

    totalCaloriesBurned += caloriesBurned;

    cout << "\nExercise Added Successfully.\n";
    cout << "Calories Burned: "
         << caloriesBurned
         << " kcal\n";
}

void Tracker::showExerciseSummary() const
{
    cout << "\n========== EXERCISE SUMMARY ==========\n";

    cout << "Total Calories Burned: "
         << totalCaloriesBurned
         << " kcal\n";
}

void Tracker::showReport() const
{
    cout << "\n========== DAILY REPORT ==========\n";

    cout << left << setw(25)
         << "Daily Goal"
         << dailyGoal
         << " kcal"
         << endl;

    cout << left << setw(25)
         << "Calories Consumed"
         << totalCalories
         << " kcal"
         << endl;

    cout << left << setw(25)
         << "Calories Burned"
         << totalCaloriesBurned
         << " kcal"
         << endl;

    cout << left << setw(25)
         << "Net Calories"
         << totalCalories - totalCaloriesBurned
         << " kcal"
         << endl;

    cout << "\n---------- NUTRITION ----------\n";

    cout << left << setw(25)
         << "Protein"
         << totalProtein
         << " g"
         << endl;

    cout << left << setw(25)
         << "Carbohydrates"
         << totalCarbs
         << " g"
         << endl;

    cout << left << setw(25)
         << "Fat"
         << totalFat
         << " g"
         << endl;

    cout << "\n---------- GOAL STATUS ----------\n";

    if(totalCalories < dailyGoal)
    {
        cout << "Remaining Calories: "
             << dailyGoal - totalCalories
             << " kcal"
             << endl;
    }
    else if(totalCalories == dailyGoal)
    {
        cout << "Daily calorie goal reached!\n";
    }
    else
    {
        cout << "Goal exceeded by: "
             << totalCalories - dailyGoal
             << " kcal"
             << endl;
    }
}

void Tracker::saveHistory(const string &username) const
{
    ofstream file("data/history.txt",ios::app);

    if(file.is_open())
    {
        file<<"User : "<<username<<endl;

        file<<"Calories : "<<totalCalories<<endl;

        file<<"Protein : "<<totalProtein<<endl;

        file<<"Carbs : "<<totalCarbs<<endl;

        file<<"Fat : "<<totalFat<<endl;

        file<<"-------------------------"<<endl;

        file.close();

        cout<<"\nHistory Saved.\n";
    }
}

void Tracker::reset()
{
    meals.clear();

    totalCalories = 0;
    totalProtein = 0;
    totalCarbs = 0;
    totalFat = 0;

    totalCaloriesBurned = 0;
}

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
    dailyGoal = goal;
    lastExercise = "";
    lastExerciseMinutes = 0;
    lastCaloriesBurned = 0;
}

void Tracker::setGoal(int goal)
{
    dailyGoal = goal;
}

void Tracker::addFood(const Food &food, int quantity)
{
    if(quantity <= 0)
        return;

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

    if(!file.is_open())
    {
        cout << "Unable to open foods database.\n";
        return;
    }

    string line;

    while(getline(file, line))
    {
        if(line.empty())
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
             << left << setw(20)
             << foodDatabase[i].getName()
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
        if(!isdigit(static_cast<unsigned char>(c)))
        {
            isNumber = false;
            break;
        }
    }

    if(isNumber && !input.empty())
    {
        int index = stoi(input);

        if(index >= 1 &&
           index <= static_cast<int>(foodDatabase.size()))
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
        [](unsigned char c)
        {
            return static_cast<char>(tolower(c));
        }
    );

    for(auto &food : foodDatabase)
    {
        string foodName = food.getName();

        transform(
            foodName.begin(),
            foodName.end(),
            foodName.begin(),
            [](unsigned char c)
            {
                return static_cast<char>(tolower(c));
            }
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

    cout << "\nEnter food number or name: ";

    getline(cin, input);

    Food *food = findFood(input);

    if(food == nullptr)
    {
        cout << "\nFood not found.\n";
        return;
    }

    int quantity;

    cout << "Enter quantity: ";

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

void Tracker::showMealHistory() const
{
    cout << "\n========== TODAY'S MEALS ==========\n";

    if(meals.empty())
    {
        cout << "No meals added yet.\n";
        return;
    }

    for(size_t i = 0; i < meals.size(); i++)
    {
        cout << i + 1 << ". "
             << meals[i].getName()
             << " - "
             << meals[i].getCalories()
             << " kcal"
             << endl;
    }
}

void Tracker::removeMeal()
{
    if(meals.empty())
    {
        cout << "\nNo meals to remove.\n";
        return;
    }

    showMealHistory();

    int choice;

    cout << "\nEnter meal number to remove: ";

    cin >> choice;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nInvalid input.\n";
        return;
    }

    if(choice < 1 ||
       choice > static_cast<int>(meals.size()))
    {
        cout << "\nInvalid meal number.\n";
        return;
    }

    Food removedFood = meals[choice - 1];

    totalCalories -= removedFood.getCalories();
    totalProtein -= removedFood.getProtein();
    totalCarbs -= removedFood.getCarbs();
    totalFat -= removedFood.getFat();

    meals.erase(meals.begin() + (choice - 1));

    cout << "\n"
         << removedFood.getName()
         << " removed successfully.\n";
}

void Tracker::addExercise()
{
    int choice;
    int duration;

    cout << "\n========== EXERCISE TRACKER ==========\n";

    cout << "1. Walking\n";
    cout << "2. Running\n";
    cout << "3. Cycling\n";
    cout << "4. Skipping\n";

    cout << "\nChoose exercise: ";

    cin >> choice;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nInvalid input.\n";
        return;
    }

    if(choice < 1 || choice > 4)
    {
        cout << "\nInvalid exercise choice.\n";
        return;
    }

    cout << "Enter duration in minutes: ";

    cin >> duration;

    if(cin.fail() || duration <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nInvalid duration.\n";
        return;
    }

    int caloriesBurned = 0;
    string exerciseName;

    switch(choice)
    {
        case 1:
            exerciseName = "Walking";
            caloriesBurned = duration * 4;
            break;

        case 2:
            exerciseName = "Running";
            caloriesBurned = duration * 10;
            break;

        case 3:
            exerciseName = "Cycling";
            caloriesBurned = duration * 8;
            break;

        case 4:
            exerciseName = "Skipping";
            caloriesBurned = duration * 12;
            break;
    }

    lastExercise = exerciseName;
    lastExerciseMinutes = duration;
    lastCaloriesBurned = caloriesBurned;

    ofstream file("data/exercise.txt", ios::app);

    if(file.is_open())
    {
        file << exerciseName << ","
             << duration << ","
             << caloriesBurned
             << endl;

        file.close();
    }

    cout << "\nExercise Added Successfully.\n";

    cout << "Exercise: "
         << exerciseName
         << endl;

    cout << "Duration: "
         << duration
         << " minutes"
         << endl;

    cout << "Calories Burned: "
         << caloriesBurned
         << " kcal"
         << endl;
}

void Tracker::showExerciseSummary() const
{
    cout << "\n========== EXERCISE SUMMARY ==========\n";

    if(lastExercise.empty())
    {
        cout << "No exercise recorded in this session.\n";
        return;
    }

    cout << "Exercise: "
         << lastExercise
         << endl;

    cout << "Duration: "
         << lastExerciseMinutes
         << " minutes"
         << endl;

    cout << "Calories Burned: "
         << lastCaloriesBurned
         << " kcal"
         << endl;
}

void Tracker::calculateBMI()
{
    float weight;
    float height;

    cout << "\n========== BMI CALCULATOR ==========\n";

    cout << "Enter weight (kg): ";

    cin >> weight;

    if(cin.fail() || weight <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nInvalid weight.\n";
        return;
    }

    cout << "Enter height (meters): ";

    cin >> height;

    if(cin.fail() || height <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nInvalid height.\n";
        return;
    }

    float bmi = weight / (height * height);

    cout << fixed << setprecision(2);

    cout << "\nYour BMI: "
         << bmi
         << endl;

    if(bmi < 18.5)
    {
        cout << "Category: Underweight\n";
    }
    else if(bmi < 25)
    {
        cout << "Category: Normal Weight\n";
    }
    else if(bmi < 30)
    {
        cout << "Category: Overweight\n";
    }
    else
    {
        cout << "Category: Obese\n";
    }
}

void Tracker::showReport() const
{
    cout << "\n========== DAILY REPORT ==========\n";

    cout << left << setw(25)
         << "Calories Consumed:"
         << totalCalories
         << " kcal"
         << endl;

    cout << left << setw(25)
         << "Protein:"
         << totalProtein
         << " g"
         << endl;

    cout << left << setw(25)
         << "Carbohydrates:"
         << totalCarbs
         << " g"
         << endl;

    cout << left << setw(25)
         << "Fat:"
         << totalFat
         << " g"
         << endl;

    cout << "\n---------- EXERCISE ----------\n";

    cout << left << setw(25)
         << "Exercise:"
         << (lastExercise.empty() ? "None" : lastExercise)
         << endl;

    cout << left << setw(25)
         << "Calories Burned:"
         << lastCaloriesBurned
         << " kcal"
         << endl;

    cout << "\n---------- SUMMARY ----------\n";

    int netCalories = totalCalories - lastCaloriesBurned;

    cout << left << setw(25)
         << "Net Calories:"
         << netCalories
         << " kcal"
         << endl;
}

void Tracker::saveHistory(const string &username) const
{
    ofstream file("data/history.txt", ios::app);

    if(!file.is_open())
    {
        cout << "\nUnable to save history.\n";
        return;
    }

    int netCalories = totalCalories - lastCaloriesBurned;

    file << "\n====================================\n";
    file << "NUTRITION SESSION\n";
    file << "====================================\n";

    file << "User: "
         << username
         << endl;

    file << "Calories Consumed: "
         << totalCalories
         << " kcal"
         << endl;

    file << "Protein: "
         << totalProtein
         << " g"
         << endl;

    file << "Carbohydrates: "
         << totalCarbs
         << " g"
         << endl;

    file << "Fat: "
         << totalFat
         << " g"
         << endl;

    file << "Exercise: "
         << (lastExercise.empty() ? "None" : lastExercise)
         << endl;

    file << "Exercise Duration: "
         << lastExerciseMinutes
         << " minutes"
         << endl;

    file << "Calories Burned: "
         << lastCaloriesBurned
         << " kcal"
         << endl;

    file << "Net Calories: "
         << netCalories
         << " kcal"
         << endl;

    file << "====================================\n";

    file.close();

    cout << "\nHistory Saved Successfully.\n";
}

void Tracker::viewHistory() const
{
    ifstream file("data/history.txt");

    if(!file.is_open())
    {
        cout << "\nNo history found.\n";
        return;
    }

    cout << "\n========== NUTRITION HISTORY ==========\n";

    string line;

    bool hasHistory = false;

    while(getline(file, line))
    {
        cout << line << endl;

        if(!line.empty())
        {
            hasHistory = true;
        }
    }

    file.close();

    if(!hasHistory)
    {
        cout << "\nNo saved history available.\n";
    }
}

void Tracker::reset()
{
    meals.clear();

    totalCalories = 0;
    totalProtein = 0;
    totalCarbs = 0;
    totalFat = 0;

    lastExercise = "";
    lastExerciseMinutes = 0;
    lastCaloriesBurned = 0;
}
#include "../include/Tracker.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cctype>
#include <algorithm>

using namespace std;

Tracker::Tracker()
{
    totalCalories = 0;
    totalProtein = 0;
    totalCarbs = 0;
    totalFat = 0;
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

void Tracker::showReport() const
{
    cout<<"\n========== DAILY REPORT ==========\n";

    cout<<left<<setw(15)<<"Calories"<<totalCalories<<endl;
    cout<<left<<setw(15)<<"Protein"<<totalProtein<<" g"<<endl;
    cout<<left<<setw(15)<<"Carbs"<<totalCarbs<<" g"<<endl;
    cout<<left<<setw(15)<<"Fat"<<totalFat<<" g"<<endl;
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

    totalCalories=0;
    totalProtein=0;
    totalCarbs=0;
    totalFat=0;
}
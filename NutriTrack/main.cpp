#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class NutritionTracker {
private:
    string username;
    int dailyGoal;
    int totalCalories;
    int totalProtein;
    int totalCarbs;
    int totalFat;

public:
    NutritionTracker() {
        totalCalories = 0;
        totalProtein = 0;
        totalCarbs = 0;
        totalFat = 0;
        dailyGoal = 2000;
    }

    void registerUser() {
        cout << "\n===== REGISTER =====\n";
        cout << "Enter username: ";
        cin >> username;

        cout << "Enter daily calorie goal: ";
        cin >> dailyGoal;

        ofstream file("users.txt", ios::app);

        if (file.is_open()) {
            file << username << " " << dailyGoal << endl;
            file.close();
            cout << "\nRegistration Successful!\n";
        } else {
            cout << "Error saving user data.\n";
        }
    }

    void loginUser() {
        string searchUser;
        bool found = false;

        cout << "\n===== LOGIN =====\n";
        cout << "Enter username: ";
        cin >> searchUser;

        ifstream file("users.txt");

        if (file.is_open()) {
            while (file >> username >> dailyGoal) {
                if (username == searchUser) {
                    found = true;
                    break;
                }
            }

            file.close();

            if (found) {
                cout << "\nWelcome, " << username << "!\n";
                cout << "Daily Goal: " << dailyGoal << " calories\n";
            } else {
                cout << "\nUser not found.\n";
            }
        } else {
            cout << "No users registered yet.\n";
        }
    }

    void addMeal() {
        int choice;

        cout << "\n===== ADD MEAL =====\n";
        cout << "1. Apple\n";
        cout << "2. Rice\n";
        cout << "3. Milk\n";
        cout << "4. Egg\n";
        cout << "5. Banana\n";
        cout << "Choose food: ";
        cin >> choice;

        switch (choice) {
        case 1:
            totalCalories += 95;
            totalProtein += 1;
            totalCarbs += 25;
            totalFat += 0;
            cout << "Apple added!\n";
            break;

        case 2:
            totalCalories += 200;
            totalProtein += 4;
            totalCarbs += 45;
            totalFat += 1;
            cout << "Rice added!\n";
            break;

        case 3:
            totalCalories += 120;
            totalProtein += 8;
            totalCarbs += 12;
            totalFat += 5;
            cout << "Milk added!\n";
            break;

        case 4:
            totalCalories += 78;
            totalProtein += 6;
            totalCarbs += 1;
            totalFat += 5;
            cout << "Egg added!\n";
            break;

        case 5:
            totalCalories += 105;
            totalProtein += 1;
            totalCarbs += 27;
            totalFat += 0;
            cout << "Banana added!\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    }

    void showReport() {
        cout << "\n===== DAILY REPORT =====\n";

        cout << left << setw(20) << "Calories:"
             << totalCalories << endl;

        cout << left << setw(20) << "Protein:"
             << totalProtein << " g\n";

        cout << left << setw(20) << "Carbs:"
             << totalCarbs << " g\n";

        cout << left << setw(20) << "Fat:"
             << totalFat << " g\n";

        cout << left << setw(20) << "Goal:"
             << dailyGoal << " cal\n";

        cout << left << setw(20) << "Remaining:"
             << dailyGoal - totalCalories << " cal\n";
    }

    void calculateBMI() {
        float weight, height, bmi;

        cout << "\n===== BMI CALCULATOR =====\n";

        cout << "Enter weight (kg): ";
        cin >> weight;

        cout << "Enter height (meters): ";
        cin >> height;

        bmi = weight / (height * height);

        cout << "\nYour BMI is: " << fixed << setprecision(2) << bmi << endl;

        if (bmi < 18.5)
            cout << "Category: Underweight\n";
        else if (bmi < 25)
            cout << "Category: Normal Weight\n";
        else if (bmi < 30)
            cout << "Category: Overweight\n";
        else
            cout << "Category: Obese\n";
    }

    void saveHistory() {
        ofstream file("history.txt", ios::app);

        if (file.is_open()) {
            file << "User: " << username << endl;
            file << "Calories: " << totalCalories << endl;
            file << "Protein: " << totalProtein << " g\n";
            file << "Carbs: " << totalCarbs << " g\n";
            file << "Fat: " << totalFat << " g\n";
            file << "-------------------------\n";

            file.close();

            cout << "\nHistory saved successfully!\n";
        } else {
            cout << "Error saving history.\n";
        }
    }
};

int main() {
    NutritionTracker tracker;

    int choice;

    do {
        cout << "\n====================================\n";
        cout << "        NUTRITION TRACKER\n";
        cout << "====================================\n";

        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Add Meal\n";
        cout << "4. View Daily Report\n";
        cout << "5. BMI Calculator\n";
        cout << "6. Save History\n";
        cout << "7. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            tracker.registerUser();
            break;

        case 2:
            tracker.loginUser();
            break;

        case 3:
            tracker.addMeal();
            break;

        case 4:
            tracker.showReport();
            break;

        case 5:
            tracker.calculateBMI();
            break;

        case 6:
            tracker.saveHistory();
            break;

        case 7:
            cout << "\nThank you for using Nutrition Tracker!\n";
            break;

        default:
            cout << "\nInvalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}
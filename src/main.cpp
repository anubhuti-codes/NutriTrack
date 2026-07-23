#include <iostream>

#include "../include/User.h"
#include "../include/Tracker.h"

int main()
{
    User user;

    Tracker tracker;

    tracker.loadFoods();

    int choice;

    bool loggedIn = false;

    do
    {
        std::cout << "\n====================================\n";

        std::cout << "        NUTRITRACK\n";

        std::cout << "====================================\n";

        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Add Meal\n";
        std::cout << "4. View Meal History\n";
        std::cout << "5. Remove Meal\n";
        std::cout << "6. Add Exercise\n";
        std::cout << "7. Daily Report\n";
        std::cout << "8. Save History\n";
        std::cout << "9. View Saved History\n";
        std::cout << "10. View Profile\n";
        std::cout << "11. View Food Database\n";
        std::cout << "12. Exercise Summary\n";
        std::cout << "13. BMI Calculator\n";
        std::cout << "14. Exit\n";

        std::cout << "\nChoice: ";
        std::cin >> choice;

        switch(choice)
        {
        case 1:

            user.registerUser();

            break;

        case 2:

            loggedIn = user.loginUser();

            if(loggedIn)
            {
                tracker.setGoal(user.getGoal());

                std::cout << "Daily calorie goal loaded successfully.\n";
            }

            break;

        case 3:

            if(loggedIn)
                tracker.addMeal();
            else
                std::cout << "\nLogin First.\n";

            break;

        case 4:

            if(loggedIn)
                tracker.showMealHistory();
            else
                std::cout << "\nLogin First.\n";

            break;

        case 5:

            if(loggedIn)
                tracker.removeMeal();
            else
                std::cout << "\nLogin First.\n";

            break;

        case 6:

            if(loggedIn)
                tracker.addExercise();
            else
                std::cout << "\nLogin First.\n";

            break;

        case 7:

            if(loggedIn)
                tracker.showReport();
            else
                std::cout << "\nLogin First.\n";

            break;

        case 8:

            if(loggedIn)
                tracker.saveHistory(user.getUsername());
            else
                std::cout << "\nLogin First.\n";

            break;

        case 9:

            if(loggedIn)
                tracker.viewHistory();
            else
                std::cout << "\nLogin First.\n";

            break;

        case 10:

            if(loggedIn)
                user.displayProfile();
            else
                std::cout << "\nLogin First.\n";

            break;

        case 11:

            tracker.displayFoods();

            break;

        case 12:

            if(loggedIn)
                tracker.showExerciseSummary();
            else
                std::cout << "\nLogin First.\n";

            break;

        case 13:

            if(loggedIn)
                tracker.calculateBMI();
            else
                std::cout << "\nLogin First.\n";

            break;

        case 14:

            std::cout << "\nThank You.\n";

            break;

        default:

            std::cout << "\nInvalid Choice.\n";
        }

    } while(choice != 14);

    return 0;
}
#include <iostream>

#include "../include/User.h"
#include "../include/Tracker.h"

using namespace std;

int main()
{
    User user;

    Tracker tracker;

    tracker.loadFoods();

    int choice;

    bool loggedIn=false;

    do
    {
        cout<<"\n====================================\n";

        cout<<"        NUTRITRACK\n";

        cout<<"====================================\n";

        cout<<"1. Register\n";
        cout<<"2. Login\n";
        cout<<"3. Add Meal\n";
        cout<<"4. View Meal History\n";
        cout<<"5. Add Exercise\n";
        cout<<"6. Daily Report\n";
        cout<<"7. Save History\n";
        cout<<"8. View Profile\n";
        cout<<"9. View Food Database\n";
        cout<<"10. Exercise Summary\n";
        cout<<"11. Exit\n";

        cout<<"\nChoice : ";

        cin>>choice;

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

                cout << "Daily calorie goal loaded successfully.\n";
            }

            break;

        case 3:

            if(loggedIn)
                tracker.addMeal();
            else
                cout<<"\nLogin First.\n";

            break;

        case 4:

            if(loggedIn)
                tracker.showMealHistory();
            else
                cout<<"\nLogin First.\n";

            break;

        case 5:

            if(loggedIn)
                tracker.addExercise();
            else
                cout<<"\nLogin First.\n";

            break;

        case 6:

            tracker.showReport();

            break;

        case 7:

            tracker.saveHistory(user.getUsername());

            break;

        case 8:

            user.displayProfile();

            break;

        case 9:

            tracker.displayFoods();

            break;

        case 10:

            tracker.showExerciseSummary();

            break;

        case 11:

            cout<<"\nThank You.\n";

            break;

        default:

            cout<<"\nInvalid Choice\n";
        }

    }while(choice!=11);

    return 0;
}
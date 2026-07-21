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
        cout<<"4. Add Exercise\n";
        cout<<"5. Daily Report\n";
        cout<<"6. Save History\n";
        cout<<"7. View Profile\n";
        cout<<"8. View Food Database\n";
        cout<<"9. Exercise Summary\n";
        cout<<"10. Exit\n";

        cout<<"\nChoice : ";

        cin>>choice;

        switch(choice)
        {
        case 1:

            user.registerUser();

            break;

        case 2:

            loggedIn=user.loginUser();

            break;

        case 3:

            if(loggedIn)
                tracker.addMeal();
            else
                cout<<"\nLogin First.\n";

            break;

        case 4:

            if(loggedIn)
                tracker.addExercise();
            else
                cout<<"\nLogin First.\n";

            break;

        case 5:

            tracker.showReport();

            break;

        case 6:

            tracker.saveHistory(user.getUsername());

            break;

        case 7:

            user.displayProfile();

            break;

        case 8:

            tracker.displayFoods();

            break;

        case 9:

            tracker.showExerciseSummary();

            break;

        case 10:

            cout<<"\nThank You.\n";

            break;

        default:

            cout<<"\nInvalid Choice\n";
        }

    }while(choice!=10);

    return 0;
}
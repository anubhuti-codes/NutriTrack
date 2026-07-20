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
        cout<<"4. Daily Report\n";
        cout<<"5. Save History\n";
        cout<<"6. View Profile\n";
        cout<<"7. View Food Database\n";
        cout<<"8. Exit\n";

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

            tracker.showReport();

            break;

        case 5:

            tracker.saveHistory(user.getUsername());

            break;
        
        case 6:

            user.displayProfile();

            break;

        case 7:

            tracker.displayFoods();

            break;

        case 8:

            cout<<"\nThank You.\n";

            break;

        default:

            cout<<"\nInvalid Choice\n";
        }

    }while(choice!=8);

    return 0;
}
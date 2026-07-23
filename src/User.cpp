#include "../include/User.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

User::User()
{
    username = "";

    password = "";

    age = 0;

    gender = "";

    height = 0;

    weight = 0;

    dailyGoal = 2000;
}

void User::registerUser()
{

    cout<<"\n===== REGISTER =====\n";

    cout<<"Username : ";

    cin>>username;

    cout<<"Password : ";

    cin>>password;

    cout<<"Age : ";

    cin>>age;

    cout<<"Gender : ";

    cin>>gender;

    cout<<"Height (m): ";

    cin>>height;

    cout<<"Weight (kg): ";

    cin>>weight;

    cout<<"Daily Goal : ";

    cin>>dailyGoal;

    ofstream file("data/users.txt",ios::app);

    if(file.is_open())
    {

        file<<username<<" "

            <<password<<" "

            <<age<<" "

            <<gender<<" "

            <<height<<" "

            <<weight<<" "

            <<dailyGoal<<endl;

        file.close();

        cout<<"\nRegistration Successful!\n";

    }

    else
    {

        cout<<"\nError saving user.\n";

    }

}

bool User::loginUser()
{

    string searchUser;

    string searchPassword;

    bool found=false;

    cout<<"\n===== LOGIN =====\n";

    cout<<"Username : ";

    cin>>searchUser;

    cout<<"Password : ";

    cin>>searchPassword;

    ifstream file("data/users.txt");

    if(file.is_open())
    {

        while(file>>

              username>>

              password>>

              age>>

              gender>>

              height>>

              weight>>

              dailyGoal)
        {

            if(username==searchUser && password==searchPassword)
            {

                found=true;

                break;

            }

        }

        file.close();

    }

    if(found)
    {

        cout<<"\nLogin Successful!\n";

        return true;

    }

    cout<<"\nInvalid Username or Password\n";

    return false;

}

void User::displayProfile()
{

    cout<<"\n========== PROFILE ==========\n";

    cout<<"Username : "<<username<<endl;

    cout<<"Age : "<<age<<endl;

    cout<<"Gender : "<<gender<<endl;

    cout<<"Height : "<<height<<" m"<<endl;

    cout<<"Weight : "<<weight<<" kg"<<endl;

    cout<<"Daily Goal : "<<dailyGoal<<endl;

}

void User::updateProfile()
{

    cout<<"\nUpdate Weight : ";

    cin>>weight;

    cout<<"Update Daily Goal : ";

    cin>>dailyGoal;

    cout<<"\nProfile Updated.\n";

}

string User::getUsername()
{

    return username;

}

int User::getGoal()
{

    return dailyGoal;

}
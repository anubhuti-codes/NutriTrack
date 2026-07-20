#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User
{
private:

    string username;

    string password;

    int age;

    string gender;

    float height;

    float weight;

    int dailyGoal;

public:

    User();

    void registerUser();

    bool loginUser();

    void displayProfile();

    void updateProfile();

    string getUsername();

    int getGoal();

};

#endif
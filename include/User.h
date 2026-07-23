#ifndef USER_H
#define USER_H

#include <string>

class User
{
private:

    std::string username;

    std::string password;

    int age;

    std::string gender;

    float height;

    float weight;

    int dailyGoal;

public:

    User();

    void registerUser();

    bool loginUser();

    void displayProfile();

    void updateProfile();

    std::string getUsername();

    int getGoal();

};

#endif
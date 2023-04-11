#include "controller.h"
#include <iostream>
#include <string>

bool checkLogin(std::string login){
    return lookForData("Customer", "Login", login);
}

bool checkPassword(std::string password){
    return lookForData("Custimer", "Password", password);//add hash
}
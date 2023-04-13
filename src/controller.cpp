#include "controller.h"
#include <iostream>
#include <string>

bool checkLogin(std::string login, char *db){
    return lookForData(db, "Customer", "Login", login);
}

bool checkPassword(std::string password, char *db){
    return lookForData(db, "Custimer", "Password", password);//add hash
}
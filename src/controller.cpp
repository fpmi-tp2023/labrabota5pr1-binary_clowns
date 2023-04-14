#include "controller.h"
#include <iostream>
#include <string>

bool checkLogin(std::string login, char *db)
{
    return lookForData(db, "Customer", "Login", login);
}

bool checkPassword(std::string login, std::string password, char *db)
{
    std::string passwordFromDB = getCustomerPassword(db, login);
    return (password == passwordFromDB); // add hash
}

void createUser(std::string login, std::string password, char *db){
    return;
}
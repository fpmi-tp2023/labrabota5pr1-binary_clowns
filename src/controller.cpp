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

bool createUser(std::string login, std::string password, char *db){
    std::string* values = new std::string[3];
    values[0] = login;
    values[1] = password;
    values[2] = "0";
    if(insertOperation("Customer", values, 3, db)){
        return 1;
    }else{
        return 0;
    }
}
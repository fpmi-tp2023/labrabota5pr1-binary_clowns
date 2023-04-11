#include "controller.h"
#include <iostream>
#include <string>

bool checkLogin(std::string login){
    return  lookForData("Customer", "Login", login);
}
#include "model.h"
#include <iostream>

bool lookForData(char *db, std::string table, std::string column, std::string data)
{
    // query for finding login "SELECT EXISTS(SELECT *column* FROM *table* WHERE *column* = *data*)"
    return 0;
}

std::string getCustomerPassword(char *db, std::string login)
{
    std::string password;
    //"SELECT *password FROM Customer WHERE login = *login*"
    return password;
}
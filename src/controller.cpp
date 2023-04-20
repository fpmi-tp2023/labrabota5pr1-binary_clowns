#include "controller.h"
#include <iostream>
#include <string>

controller::controller(char *dbName){
    dbModel = new model(dbName);

}

bool controller::checkLogin(std::string login, char *db)
{
    return dbModel->lookForData(db, "Customer", "Login", login);
}

bool controller::checkPassword(std::string login, std::string password, char *db)
{
    std::string passwordFromDB = dbModel->getCustomerPassword(db, login);
    std::string hashPassword;
    //Transform(hashPassword, password);
    std::cout<<hashPassword<<"\n";
    return (hashPassword == passwordFromDB); // add hash
}

bool controller::createUser(std::string login, std::string password, char *db)
{
    std::string *values = new std::string[3];
    values[0] = login;
    values[1] = password;
    values[2] = "0";
    if (dbModel->insertOperation("Customer", values, 3, db))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
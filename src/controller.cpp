#include "controller.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>

controller::controller(char *dbName)
{
    dbModel = new model(dbName);
}

bool controller::checkLogin(std::string login)
{
    return dbModel->lookForData("Customer", "Login", login);
}

bool controller::checkPassword(std::string login, std::string password)
{
    std::string passwordFromDB = dbModel->getCustomerPassword(login);
    std::string hashPassword = md5(password);
    return (hashPassword == passwordFromDB);
}

bool controller::createUser(std::string login, std::string password)
{
    std::string *values = new std::string[3];
    values[0] = login;
    values[1] = md5(password);
    values[2] = "0";
    if (dbModel->insertOperation("Customer", values, 3))
    {
        delete values;
        return 1;
    }
    else
    {
        delete values;
        return 0;
    }
}

std::string controller::md5(const std::string &str)
{
    unsigned char hash[MD5_DIGEST_LENGTH];

    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, str.c_str(), str.size());
    MD5_Final(hash, &md5);

    std::stringstream ss;

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

bool controller::isAdmin(std::string login)
{
    return dbModel->checkAdmin(login);
}

std::string controller::mostPopularCompose()
{
    return dbModel->getMostPopularCompose();
}

int controller::getNumOfUrgentOrders()
{
    // number
    return 0;
}

std::string controller::getUsers()
{
    std::string info;
    std::vector<std::string> vectorFromDB = dbModel->getTableInfo("Customer");
    for (int i = 0; i < vectorFromDB.size(); i++)
    {
        info += vectorFromDB[i] + "\n";
    }
    return info;
}

void controller::giveAdmin(std::string login){
    dbModel->giveAdmin(login);
    return;
}
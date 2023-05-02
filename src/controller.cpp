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
    std::vector<std::string> values;
    values.push_back(login);
    values.push_back(md5(password));
    values.push_back("0");
    if (dbModel->insertOperation("Customer", values))
    {
        return 1;
    }
    else
    {
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

std::string controller::getFullTable(std::string tablename)
{
    std::string info;
    std::vector<std::string> vectorFromDB = dbModel->getTableInfo(tablename, "");
    for (int i = 0; i < vectorFromDB.size(); i++)
    {
        info += vectorFromDB[i] + "\n";
    }
    return info;
}

void controller::giveAdmin(std::string login)
{
    dbModel->giveAdmin(login);
    return;
}

bool controller::checkTable(std::string table)
{
    return dbModel->checkTable(table);
}

bool controller::checkColumn(std::string table, std::string column)
{
    return dbModel->checkColumn(table, column);
}

int controller::getNumOfColumns(std::string tableName)
{
    return stoi(dbModel->getNumOfColumns(tableName));
}

bool controller::deleteOperatin(std::string table, std::string conditions)
{
    return dbModel->deleteOperation(table, conditions);
}

bool controller::updateOperation(std::string table, std::vector<std::string> setColumns, std::string conditions)
{
    std::string columns;
    for (int i = 0; i < setColumns.size() - 1; i++)
    {
        columns += setColumns[i] + ", ";
    }
    columns += setColumns[setColumns.size() - 1];
    return dbModel->updateOperation(table, columns, conditions);
}

std::vector<std::string> controller::getColumnsNames(std::string tableName)
{
    return dbModel->getColumnsNames(tableName);
}

std::vector<std::string> controller::getPrymaryKeys(std::string tableName)
{
    return dbModel->getPrimaryKeys(tableName);
}

bool controller::lookInVector(std::string data, std::vector<std::string> vec)
{
    bool result = false;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == data)
        {
            result = true;
            break;
        }
    }
    return result;
}

bool controller::insertOperation(std::string table, std::vector<std::string> values)
{
    return dbModel->insertOperation(table, values);
}

bool controller::deleteUser(std::string login)
{
    return dbModel->deleteOperation("Customer", ("Login = '" + login + "';"));
}

bool controller::updateSQLSequence(std::string table, std::string column)
{
    return dbModel->updateSQLSequence(table, column);
}

std::vector<std::string> controller::mostPopularCompose()
{
    return dbModel->getMostPopularCompose();
}

std::vector<std::string> controller::urgentOrders()
{
    return dbModel->getUrgentOrders();
}

std::vector<std::string> controller::flowersInfo(std::string fDate, std::string sDate)
{
    return dbModel->getFlowersInfo(fDate, sDate);
}

std::vector<std::string> controller::soldCompose()
{
    return dbModel->getSoldCompose();
}
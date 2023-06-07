#include "controller.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>
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
    std::vector<std::string> columns;
    columns.push_back("Login");
    columns.push_back("Password");
    columns.push_back("Admin");
    return dbModel->insertOperation("Customer", values, columns);    
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

bool controller::giveAdmin(std::string login)
{
    return dbModel->giveAdmin(login);
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

int controller::getNumOfRows(std::string tableName)
{
    return stoi(dbModel->getNumOfRows(tableName));
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

bool controller::insertOperation(std::string table, std::vector<std::string> values, std::vector<std::string> columns)
{
    return dbModel->insertOperation(table, values, columns);
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

std::vector<std::string> controller::ordersByDate(std::string date)
{
    return dbModel->getDayOrdersInfo(date);
}

std::vector<std::string> controller::customerOrders(std::string fDate, std::string sDate, std::string login)
{
    return dbModel->getCustomerOrders(fDate, sDate, getIDByLogin(login));
}

std::string controller::getIDByLogin(std::string login)
{
    return dbModel->getIdByLogin(login);
}

bool controller::makeOrder(std::vector<std::pair<int, int>> order, std::string customerID)
{
    std::vector<std::string> values;
    std::vector<std::string> columns;
    bool isOk = true;
    values.push_back("DATE()");
    values.push_back("NULL");
    values.push_back(customerID);
    columns.push_back("Acceptance");
    columns.push_back("Completion");
    columns.push_back("CustomerID");
    dbModel->makeOrder(values);
    columns[0] = "CompositionAmount";
    columns[1] = "CompositionID";
    columns[2] = "OrderID";
    std::string id = dbModel->getNumOfRows("Order");
    for (int i = 0; i < order.size(); i++)
    {
        values[0] = std::to_string(order[i].second);
        values[1] = std::to_string(order[i].first);
        values[2] = id;
        if (dbModel->insertOperation("OrderComp", values, columns))
        {
            continue;
        }
        else
        {
            isOk = false;
        }
    }
    return isOk;
}

bool controller::checkComposeId(std::string data)
{
    return dbModel->lookForData("Composition", "ID", data);
}

bool controller::checkCostChanges(int flowerID, double newCost)
{
    double oldCost = std::stod(dbModel->getFlowerCost(std::to_string(flowerID)));
    std::vector<double> oldCosts;
    for (int i = 0; i <= stoi(dbModel->getMaxId("Composition")); i++)
    {
        if (checkComposeId(std::to_string(i)))
        {
            oldCosts.push_back(std::stod(dbModel->getComposeCost(std::to_string(i))));
        }
        else
        {
            oldCosts.push_back(0);
        }
    }
    dbModel->updateOperation("Flower", ("Price = '" + std::to_string(newCost) + "'"), ("ID = '" + std::to_string(flowerID) + "'"));
    for (int i = 0; i <= stoi(dbModel->getMaxId("Composition")); i++)
    {
        if (checkComposeId(std::to_string(i)))
        {
            double newCompCost = std::stod(dbModel->getComposeCost(std::to_string(i)));
            if (abs(oldCosts[i] - newCompCost) > oldCosts[i] * 0.1)
            {
                dbModel->updateOperation("Flower", ("Price = '" + std::to_string(oldCost) + "'"), ("ID = '" + std::to_string(flowerID) + "'"));
                return false;
            }
        }
    }
    return true;
}
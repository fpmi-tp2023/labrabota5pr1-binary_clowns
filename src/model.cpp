#include "model.h"
#include <iostream>

model::model(char *dbName)
{
    connectToDataBase(dbName);
}

void model::connectToDataBase(char *name)
{
    int result;
    result = sqlite3_open(name, &db);
    if (result)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
        db = nullptr;
    }
}

int model::lookForDataNCheckAdmin_callback(void *data, int argc, char **argv, char **azColName)
{
    bool &result = *(bool *)data;
    if (argv[0][0] == '0')
    {
        result = false;
    }
    else
    {
        result = true;
    }
    return 0;
}

bool model::lookForData(std::string table, std::string column, std::string data)
{
    // query for finding login "SELECT EXISTS(SELECT *column* FROM *table* WHERE *column* = *data*)"
    int result;
    bool callback_data;
    char *errMsg;
    std::string query = "SELECT EXISTS"
                        "(SELECT " +
                        column +
                        " FROM " + table +
                        " WHERE " + column + " = '" + data + "')";

    if (db == nullptr)
    {
        return 0;
    }
    result = sqlite3_exec(db, query.c_str(), lookForDataNCheckAdmin_callback, &callback_data, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
    }
    return callback_data;
}

std::string model::getCustomerPassword(std::string login)
{
    //"SELECT Password FROM Customer WHERE login = *login*"
    std::string query = "SELECT Password FROM Customer WHERE Login = '" + login + "';";
    return getStringFromDB(query);
}

bool model::insertOperation(std::string table, std::string *values, int numberOfValues)
{
    int result;
    std::string query = "INSERT INTO  " + table + " (Login, Password, Admin)\n"
                                                  "VALUES ('";
    for (int i = 0; i < numberOfValues - 1; i++)
    {
        query += values[i] + "', '";
    }
    query += values[numberOfValues - 1] + "' );";
    if (db == nullptr)
    {
        return 0;
    }
    result = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    if (result != SQLITE_OK)
    {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << "\n";
        return 0;
    }
    return 1;
}

bool model::checkAdmin(std::string login)
{
    int result;
    bool callback_data;
    char *errMsg;
    std::string query = "SELECT Admin FROM Customer WHERE Login = '" + login + "';";
    result = sqlite3_exec(db, query.c_str(), lookForDataNCheckAdmin_callback, &callback_data, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
    }
    return callback_data;
}

std::string model::getMostPopularCompose()
{
    std::string query;
    return getStringFromDB(query);
}

int model::getStringFromBD_callback(void *data, int argc, char **argv, char **azColName)
{
    std::string &result = *(std::string *)data;
    for (int i = 0; i < argc; i++)
    {
        result = argv[0];
    }
    return 0;
}

std::string model::getStringFromDB(std::string query)
{
    int result;
    std::string callback_data;
    char *errMsg;
    result = sqlite3_exec(db, query.c_str(), getStringFromBD_callback, &callback_data, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
    }
    return callback_data;
}
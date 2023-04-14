#include "model.h"
#include <iostream>

sqlite3 *connectToDataBase(char *name)
{
    sqlite3 *db;
    int result;
    result = sqlite3_open(name, &db);
    if (result)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
        db = nullptr;
    }
    return db;
}

bool lookForData(char *dbName, std::string table, std::string column, std::string data)
{
    // query for finding login "SELECT EXISTS(SELECT *column* FROM *table* WHERE *column* = *data*)"
    return 0; // true = exists
}

std::string getCustomerPassword(char *dbName, std::string login)
{
    std::string password;
    //"SELECT *password FROM Customer WHERE login = *login*"
    return password;
}

bool insertOperation(std::string table, std::string *values, int numberOfValues, char *dbName)
{
    int result;
    std::string query = "INSERT INTO  " + table + " (Login, Password, Admin)\n"
    "VALUES ('";
    for (int i = 0; i < numberOfValues - 1; i++)
    {
        query += values[i] + "', '";
    }
    query += values[numberOfValues - 1] + "' );";
    std::cout<<"Query: \n"<< query<<"\n";
    sqlite3 *db = connectToDataBase(dbName);
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
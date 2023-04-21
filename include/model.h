#include <iostream>
#include <string>
#include <sqlite3.h>
class model
{
public:
    model(char *dbName);
    void connectToDataBase(char *name);
    static int lookForDataNCheckAdmin_callback(void *data, int argc, char **argv, char **azColName);
    bool lookForData(std::string table, std::string column, std::string data);
    static int getCustomerPassword_callback(void *data, int argc, char **argv, char **azColName);
    std::string getCustomerPassword(std::string login);
    bool insertOperation(std::string table, std::string *values, int numberOfValues);
    bool checkAdmin(std::string login);

private:
    sqlite3 *db;
};
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

    static int getStringFromBD_callback(void *data, int argc, char **argv, char **azColName);
    std::string getStringFromDB(std::string query);

    std::string getCustomerPassword(std::string login);
    
    bool insertOperation(std::string table, std::string *values, int numberOfValues);

    bool checkAdmin(std::string login);

    std::string getMostPopularCompose();


private:
    sqlite3 *db;
};
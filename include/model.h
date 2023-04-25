#include <iostream>
#include <string>
#include <sqlite3.h>
#include <vector>

class model
{
public:
    model(char *dbName);

    void connectToDataBase(char *name);

    static int lookForDataNCheckAdmin_callback(void *data, int argc, char **argv, char **azColName);
    bool lookForData(std::string table, std::string column, std::string data);

    std::string getCustomerPassword(std::string login);

    bool insertOperation(std::string table, std::string *values, int numberOfValues);

    bool checkAdmin(std::string login);

    std::string getMostPopularCompose();

    std::vector<std::string> getTableInfo(std::string table, std::string conditions);

    void giveAdmin(std::string login);

    bool checkTable(std::string tableName);

    bool checkColumn(std::string tableName, std::string columnName);

    std::string model::getNumOfColumns(std::string tableName);

private:
    static int getSingleStringFromBD_callback(void *data, int argc, char **argv, char **azColName);
    std::string getSingleStringFromDB(std::string query);

    static int getTableView_callback(void *data, int argc, char **argv, char **azColName);
    std::vector<std::string> getTableView(std::string query);

    sqlite3 *db;
};
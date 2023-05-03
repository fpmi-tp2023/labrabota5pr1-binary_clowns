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

    bool insertOperation(std::string table, std::vector<std::string> values);

    bool checkAdmin(std::string login);

    std::vector<std::string> getTableInfo(std::string table, std::string conditions);

    void giveAdmin(std::string login);

    bool checkTable(std::string tableName);

    bool checkColumn(std::string tableName, std::string columnName);

    std::string getNumOfColumns(std::string tableName);

    bool deleteOperation(std::string tableName, std::string conditions);

    bool updateOperation(std::string tableName, std::string setString, std::string conditions);

    static int getColumnsNames_callback(void *data, int argc, char **argv, char **azColName);
    std::vector<std::string> getColumnsNames(std::string tableName);

    static int getPrimaryKeys_callback(void *data, int argc, char **argv, char **azColName);
    std::vector<std::string> getPrimaryKeys(std::string tableName);

    bool updateSQLSequence(std::string table, std::string column);

    std::vector<std::string> getMostPopularCompose();

    std::vector<std::string> getUrgentOrders();

    std::vector<std::string> getFlowersInfo(std::string fDate, std::string sDate);

    std::vector<std::string> getSoldCompose();
    
    std::vector<std::string> getCustomerOrders(std::string fDate, std::string sDate, std::string ID);

    std::string getIdByLogin(std::string login);

private:
    static int getSingleStringFromBD_callback(void *data, int argc, char **argv, char **azColName);
    std::string getSingleStringFromDB(std::string query);

    static int getTableView_callback(void *data, int argc, char **argv, char **azColName);
    std::vector<std::string> getTableView(std::string query);

    sqlite3 *db;
};
#include <iostream>
#include "model.h"
#include <vector>
#include <string>

class controller
{
public:
    controller(char *db);
    bool checkLogin(std::string login);
    bool checkPassword(std::string login, std::string password);
    bool createUser(std::string login, std::string password);
    std::string md5(const std::string &str);
    bool isAdmin(std::string login);
    std::string mostPopularCompose();
    std::string getFullTable(std::string tablename);
    void giveAdmin(std::string login);
    bool checkTable(std::string table);
    bool checkColumn(std::string table, std::string column);
    int getNumOfColumns(std::string table);
    bool deleteOperatin(std::string table, std::string conditions);
    bool updateOperation(std::string table, std::vector<std::string> setColumns, std::string conditions);
    std::vector<std::string> getColumnsNames(std::string tableName);
    std::vector<std::string> getPrymaryKeys(std::string tableName);
    bool lookInVector(std::string data, std::vector<std::string> vec);
    bool insertOperation(std::string table, std::vector<std::string> values);
    bool deleteUser(std::string login);
    bool updateSQLSequence(std::string table, std::string column);


private:
    model *dbModel;
};
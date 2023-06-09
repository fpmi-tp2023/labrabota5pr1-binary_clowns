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
    std::string getFullTable(std::string tablename);
    bool giveAdmin(std::string login);
    bool checkTable(std::string table);
    bool checkColumn(std::string table, std::string column);
    int getNumOfColumns(std::string table);
    int getNumOfRows(std::string table);
    bool deleteOperatin(std::string table, std::string conditions);
    bool updateOperation(std::string table, std::vector<std::string> setColumns, std::string conditions);
    std::vector<std::string> getColumnsNames(std::string tableName);
    std::vector<std::string> getPrymaryKeys(std::string tableName);
    bool lookInVector(std::string data, std::vector<std::string> vec);
    bool insertOperation(std::string table, std::vector<std::string> values, std::vector<std::string> columns);
    bool deleteUser(std::string login);
    bool updateSQLSequence(std::string table, std::string column);
    std::vector<std::string> mostPopularCompose();
    std::vector<std::string> urgentOrders();
    std::vector<std::string> flowersInfo(std::string fDate, std::string sDate);
    std::vector<std::string> soldCompose();
    std::vector<std::string> ordersByDate(std::string date);
    std::vector<std::string> customerOrders(std::string fDate, std::string sDate, std::string login);
    std::string getIDByLogin(std::string login);
    bool makeOrder(std::vector<std::pair<int,int>> order, std::string customerID);
    bool checkComposeId(std::string data);
    bool checkCostChanges(int flowerID, double newCost);

private:
    model *dbModel;
};
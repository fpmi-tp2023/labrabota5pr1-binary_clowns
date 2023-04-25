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

private:
    model *dbModel;
};
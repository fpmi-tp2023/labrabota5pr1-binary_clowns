#include <iostream>
#include "model.h"

class controller
{
public:
    controller(char *db);
    bool checkLogin(std::string login, char *db);
    bool checkPassword(std::string login, std::string password, char *db);
    bool createUser(std::string login, std::string password, char *db);
    std::string md5(const std::string &str);

private:
    model *dbModel;
};
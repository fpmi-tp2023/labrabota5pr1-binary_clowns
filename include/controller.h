#include <iostream>
#include <openssl/md5.h>
#include "model.h"

class controller
{
public:
    controller(char *db);
    bool checkLogin(std::string login, char *db);
    bool checkPassword(std::string login, std::string password, char *db);
    bool createUser(std::string login, std::string password, char *db);

private:
    model *dbModel;
};
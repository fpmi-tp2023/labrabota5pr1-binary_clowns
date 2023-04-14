#include <iostream>
#include "model.h"

bool checkLogin(std::string login, char *db);
bool checkPassword(std::string login, std::string password, char *db);
bool createUser(std::string login, std::string password, char *db);
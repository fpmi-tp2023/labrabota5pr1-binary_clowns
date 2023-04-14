#include <iostream>
#include <string>
#include <sqlite3.h>

sqlite3* connectToDataBase(char* name);
bool lookForData( char *Name, std::string table, std::string column, std::string data);
std::string getCustomerPassword( char *Name, std::string login);
bool insertOperation(std::string table, std::string* values, int numberOfValues, char* dbName);
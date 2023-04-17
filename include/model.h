#include <iostream>
#include <string>
#include <sqlite3.h>

sqlite3* connectToDataBase(char* name);
static int lookForData_callback(void *data, int argc, char **argv, char **azColName);
bool lookForData( char *dbName, std::string table, std::string column, std::string data);
static int getCustomerPassword_callback(void *data, int argc, char **argv, char **azColName);
std::string getCustomerPassword( char *Name, std::string login);
bool insertOperation(std::string table, std::string* values, int numberOfValues, char* dbName);
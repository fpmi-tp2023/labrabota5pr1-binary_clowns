#include "model.h"
#include <iostream>

model::model(char *dbName)
{
    connectToDataBase(dbName);
}

void model::connectToDataBase(char *name)
{
    int result;
    result = sqlite3_open(name, &db);
    if (result)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
        db = nullptr;
    }
}

int model::lookForDataNCheckAdmin_callback(void *data, int argc, char **argv, char **azColName)
{
    bool &result = *(bool *)data;
    if (argv[0][0] == '0')
    {
        result = false;
    }
    else
    {
        result = true;
    }
    return 0;
}

bool model::lookForData(std::string table, std::string column, std::string data)
{
    // query for finding login "SELECT EXISTS(SELECT *column* FROM *table* WHERE *column* = *data*)"
    int result;
    bool callback_data;
    char *errMsg;
    std::string query = "SELECT EXISTS"
                        "(SELECT " +
                        column +
                        " FROM " + table +
                        " WHERE " + column + " = '" + data + "')";

    if (db == nullptr)
    {
        return 0;
    }
    result = sqlite3_exec(db, query.c_str(), lookForDataNCheckAdmin_callback, &callback_data, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
    }
    delete errMsg;
    return callback_data;
}

std::string model::getCustomerPassword(std::string login)
{
    //"SELECT Password FROM Customer WHERE login = *login*"
    std::string query = "SELECT Password FROM Customer WHERE Login = '" + login + "';";
    return getSingleStringFromDB(query);
}

bool model::insertOperation(std::string table, std::vector<std::string> values)
{
    int result;
    char *errMsg;
    std::string query = "INSERT INTO  " + table + " (Login, Password, Admin)\n"
                                                  "VALUES ('";
    for (int i = 0; i < (values.size() - 1); i++)
    {
        query += values[i] + "', '";
    }
    query += values[(values.size() - 1)] + "' );";
    if (db == nullptr)
    {
        return 0;
    }
    result = sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
    if (errMsg)
    {
        std::cerr << "SQL error: " << errMsg << "\n";
        return 0;
    }
    return 1;
}

bool model::checkAdmin(std::string login)
{
    int result;
    bool callback_data;
    char *errMsg;
    std::string query = "SELECT Admin FROM Customer WHERE Login = '" + login + "';";
    result = sqlite3_exec(db, query.c_str(), lookForDataNCheckAdmin_callback, &callback_data, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
    }
    delete errMsg;
    return callback_data;
}

int model::getSingleStringFromBD_callback(void *data, int argc, char **argv, char **azColName)
{
    std::string &result = *(std::string *)data;
    result = argv[0];
    return 0;
}

std::string model::getSingleStringFromDB(std::string query)
{
    int result;
    std::string callback_data;
    char *errMsg;
    result = sqlite3_exec(db, query.c_str(), getSingleStringFromBD_callback, &callback_data, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
    }
    delete errMsg;
    return callback_data;
}

int model::getTableView_callback(void *data, int argc, char **argv, char **azColName)
{
    std::vector<std::string> &vec = *(std::vector<std::string> *)data;
    int i;
    std::string part;
    for (i = 0; i < argc; i++)
    {
        part += azColName[i];
        part += " : ";
        part += (argv[i] ? argv[i] : "NULL");
        part += "\n";
    }
    vec.push_back(part);
    return 0;
}

std::vector<std::string> model::getTableView(std::string query)
{
    int result;
    std::vector<std::string> callback_data;
    char *errMsg;
    result = sqlite3_exec(db, query.c_str(), getTableView_callback, &callback_data, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
    }
    delete errMsg;
    return callback_data;
}

std::vector<std::string> model::getTableInfo(std::string table, std::string conditions)
{
    std::string query = "SELECT * FROM " + table + conditions + ";";
    return getTableView(query);
}

bool model::checkTable(std::string tableName)
{
    int result;
    bool callback_data;
    char *errMsg;
    std::string query = "SELECT EXISTS"
                        "(SELECT name FROM sqlite_master WHERE type = 'table' AND name = '" +
                        tableName + "')";

    if (db == nullptr)
    {
        return 0;
    }
    result = sqlite3_exec(db, query.c_str(), lookForDataNCheckAdmin_callback, &callback_data, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
    }
    delete errMsg;
    return callback_data;
}

bool model::checkColumn(std::string tableName, std::string columnName)
{
    int result;
    bool callback_data;
    char *errMsg;
    std::string query = "SELECT COUNT(*) FROM pragma_table_info('" + tableName + "') WHERE name='" + columnName + "';";
    if (db == nullptr)
    {
        return 0;
    }
    result = sqlite3_exec(db, query.c_str(), lookForDataNCheckAdmin_callback, &callback_data, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
    }
    delete errMsg;
    return callback_data;
}

std::string model::getNumOfColumns(std::string tableName)
{
    std::string query = "SELECT COUNT(cid) FROM pragma_table_info('" + tableName + "');";
    return getSingleStringFromDB(query);
}

void model::giveAdmin(std::string login)
{
    std::string query = "UPDATE Customer SET Admin = '1' WHERE Login = '" + login + "';";
    int result;
    char *errMsg;
    result = sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
    }
    delete errMsg;
    return;
}

bool model::deleteOperation(std::string tableName, std::string conditions)
{
    std::string query = "DELETE FROM " + tableName + " WHERE " + conditions;
    int result;
    char *errMsg;
    result = sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
        delete errMsg;
        return 0;
    }
    else
    {
        delete errMsg;
        return 1;
    }
}

bool model::updateOperation(std::string tableName, std::string setString, std::string conditions)
{
    std::string query = "UPDATE " + tableName + " SET " + setString + " WHERE " + conditions;
    int result;
    char *errMsg;
    result = sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
        delete errMsg;
        return 0;
    }
    else
    {
        delete errMsg;
        return 1;
    }
}

int model::getColumnsNames_callback(void *data, int argc, char **argv, char **azColName)
{
    std::vector<std::string> &vec = *(std::vector<std::string> *)data;
    std::string part = argv[0];
    vec.push_back(part);
    return 0;
}

std::vector<std::string> model::getColumnsNames(std::string tableName)
{
    std::string query = "SELECT name FROM pragma_table_info('" + tableName + "');";
    int result;
    std::vector<std::string> callback_data;
    char *errMsg;
    result = sqlite3_exec(db, query.c_str(), getColumnsNames_callback, &callback_data, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
        delete errMsg;
    }
    return callback_data;
}

int model::getPrimaryKeys_callback(void *data, int argc, char **argv, char **azColName)
{
    std::vector<std::string> &vec = *(std::vector<std::string> *)data;
    char *nullValue = new char[1];
    nullValue[0] = '0';
    if (argv[5][0] != nullValue[0])
    {
        vec.push_back(argv[1]);
    }
    delete nullValue;
    return 0;
}

std::vector<std::string> model::getPrimaryKeys(std::string tableName)
{
    std::string query = "PRAGMA table_info(" + tableName + " )";
    int result;
    std::vector<std::string> callback_data;
    char *errMsg;
    result = sqlite3_exec(db, query.c_str(), getPrimaryKeys_callback, &callback_data, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
        delete errMsg;
    }
    return callback_data;
}

bool model::updateSQLSequence(std::string table, std::string column)
{
    std::string query = "UPDATE sqlite_sequence SET seq = (SELECT MAX(" +
                        column + ") FROM " + table + ") WHERE name = '" +
                        table + "';";
    int result;
    char *errMsg;
    result = sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
    if (errMsg)
    {
        std::cerr << errMsg << "\n";
        delete errMsg;
        return 0;
    }
    else
    {
        delete errMsg;
        return 1;
    }
}

std::vector<std::string> model::getMostPopularCompose()
{
    std::string query = "SELECT FlowerID, Flower.Name, FlowersAmount, Flower.Price, CompositionID, A.Name as CompositionName"
                        " FROM(SELECT * FROM FlowerComp"
                        " INNER JOIN Composition ON Composition.ID == FlowerComp.CompositionID)"
                        " A INNER JOIN Flower ON Flower.ID == A.FlowerID AND A.CompositionID == ("
                        "SELECT OrderComp.CompositionID "
                        "FROM OrderComp "
                        "GROUP BY OrderComp.CompositionID ORDER BY SUM(OrderComp.CompositionAmount) DESC LIMIT 1) ";
    return getTableView(query);
}

std::vector<std::string> model::getUrgentOrders()
{
    std::string query = "SELECT COUNT(ID) AS Amount, CAST(JULIANDAY(Completion) - JULIANDAY(Acceptance) AS INTEGER) as Days"
                        " FROM [Order]"
                        " GROUP BY (JULIANDAY(Completion) - JULIANDAY(Acceptance))"
                        " HAVING Completion != 'NULL';";
    return getTableView(query);
}

std::vector<std::string> model::getFlowersInfo(std::string fDate, std::string sDate)
{
    std::string query = "SELECT Flower.Kind, SUM(FlowersAmount * CompAmount) as TotalAmount"
                        " FROM FlowerComp"
                        " INNER JOIN ("
                        "SELECT OrderComp.CompositionID, OrderComp.OrderID, SUM(OrderComp.CompositionAmount) as CompAmount"
                        " FROM ("
                        "SELECT [Order].ID FROM [Order]"
                        " WHERE [Order].Completion != 'NULL' AND [Order].Completion > '" +
                        fDate +
                        "' AND [Order].Completion < '" + sDate + "'"
                                                                 ") A"
                                                                 " INNER JOIN OrderComp ON OrderComp.OrderID == A.ID"
                                                                 " GROUP BY OrderComp.CompositionID"
                                                                 ") F ON FlowerComp.CompositionID == F.CompositionID"
                                                                 " INNER JOIN Flower ON Flower.ID = FlowerComp.FlowerID"
                                                                 " GROUP BY Flower.Kind";
    return getTableView(query);
}
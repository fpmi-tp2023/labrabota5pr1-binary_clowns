#include <iostream>
#include <string>
#include "controller.h"

int main()
{
    char *db = "greenhouse.db";
    controller c(db);
    while (true)
    {
        bool authorized;
        int req;
        bool stop = false;
        std::string login, password;
        while (!stop)
        {
            std::cout << "You are not authorized\n1: sign in\n2: sign up\n0: exit\n";
            std::cin >> req;
            switch (req)
            {
            case 1:
                std::cout << "Enter your login:\n";
                std::cin >> login;
                std::cout << "Enter your password:\n";
                std::cin >> password;
                if (c.checkLogin(login))
                {
                    if (c.checkPassword(login, password))
                    {
                        stop = true;
                    }
                    else
                    {
                        std::cout << "Incorrect login or password!\n";
                    }
                }
                else
                {
                    std::cout << "Incorrect login or password!\n";
                }
                break;

            case 2:
                while (true)
                {
                    std::cout << "Write '!q' if you want to go back to main menu\nCreate your login\n";
                    std::cin >> login;
                    if (login == "!q")
                    {
                        stop = true;
                        break;
                    }
                    if (c.checkLogin(login))
                    {
                        std::cout << "This login is already occupied. Try another one!\n";
                    }
                    else
                    {
                        std::cout << "Create your password\n";
                        std::cin >> password;
                        break;
                    }
                }
                if (stop)
                {
                    stop = false;
                    break;
                }
                if (c.createUser(login, password))
                {
                    std::cout << "Success!\n";
                }
                else
                {
                    std::cout << "Something went wrong, please try again!\n";
                }
                break;

            case 0:
                return 0;
                break;

            default:
                std::cout << "Incorrect number, try again!\n";
                break;
            }
        }
        std::cout << "You are authorized as " << login << ". Welcome!\n";
        stop = false;
        bool is_admin = c.isAdmin(login);
        while (!stop)
        {
            if (is_admin)
            {
                std::string text = "What are you want to do?\n"
                                   "1: Change user \n"
                                   "2: Get information about all orders on day\n"
                                   "3: Information about the most popular composition\n"
                                   "4: Information about urgent orders\n"
                                   "5: Information about used flowers\n"
                                   "6: Information about all sold compositions\n"
                                   "7: Insert information into table\n"
                                   "8: Update/delete information\n"
                                   "9: Change price of a flower\n"
                                   "10: Give admin role by login\n"
                                   //"11: Delete user by login\n"
                                   "0: exit\n";
                std::cout << text;
                std::cin >> req;
                if (req == 0)
                {
                    return 0;
                }
                else if (req == 1)
                {
                    break;
                }
                else if (req == 2)
                {
                    // information about all orders(one day)
                    std::vector<std::string> result;
                    std::string date;
                    std::cout << "Enter date in format yyyy-mm-dd:\n";
                    std::cin >> date;
                    result = c.ordersByDate(date);
                    for (int i = 0; i < result.size(); i++)
                        std::cout << result[i] << "\n";
                }
                else if (req == 3)
                {
                    std::vector<std::string> result = c.mostPopularCompose();
                    std::cout << "Information about most popular composition:\n";
                    for (int i = 0; i < result.size(); i++)
                        std::cout << result[i] << "\n";
                }
                else if (req == 4)
                {
                    // urgent orders
                    std::vector<std::string> result = c.urgentOrders();
                    std::cout << "Information about urgent orders:\n";
                    for (int i = 0; i < result.size(); i++)
                        std::cout << result[i] << "\n";
                }
                else if (req == 5)
                {
                    // used flowers
                    std::vector<std::string> result;
                    std::string firstDate;
                    std::string secondDate;
                    std::cout << "Enter first date in format yyyy-mm-dd:\n";
                    std::cin >> firstDate;
                    std::cout << "Enter secondDate in format yyyy-mm-dd:\n";
                    std::cin >> secondDate;
                    result = c.flowersInfo(firstDate, secondDate);
                    std::cout << "Information about used flowers:\n";
                    for (int i = 0; i < result.size(); i++)
                        std::cout << result[i] << "\n";
                }
                else if (req == 6)
                {
                    // sold compositions
                    std::vector<std::string> result = c.soldCompose();
                    std::cout << "Information about sold compositions:\n";
                    for (int i = 0; i < result.size(); i++)
                        std::cout << result[i] << "\n";
                }
                else if (req == 7)
                {
                    // insert
                    std::string tablename;
                    while (true)
                    {
                        std::cout << "Choose table or type \"!q\" to go back to menu:\n";
                        std::cin >> tablename;
                        std::vector<std::string> columns;
                        std::vector<std::string> PK;
                        std::vector<std::string> values;
                        std::string value;
                        std::vector<std::string> columnsForInsert;
                        if (c.checkTable(tablename))
                        {
                            while (true)
                            {
                                values.clear();
                                columnsForInsert.clear();
                                columns = c.getColumnsNames(tablename);
                                PK = c.getPrymaryKeys(tablename);
                                std::cout << "Columns in that table:\n";
                                for (int i = 0; i < columns.size(); i++)
                                {
                                    std::cout << columns[i] << " ";
                                }
                                std::cout << "\nColumns with autoincriment(you cant insert something there):\n";
                                for (int i = 0; i < PK.size(); i++)
                                {
                                    std::cout << PK[i] << " ";
                                }
                                std::cout << "\n1:If you want to insert data\n0:If you want to go back\n";
                                std::cin >> req;
                                if (req == 1)
                                {
                                    for (int i = 0; i < columns.size(); i++)
                                    {
                                        if (!c.lookInVector(columns[i], PK))
                                        {
                                            std::cout << "Enter value for column " + columns[i] + ":\n";
                                            std::cin >> value;
                                            values.push_back(value);
                                            columnsForInsert.push_back(columns[i]);
                                        }
                                    }
                                    if (c.insertOperation(tablename, values, columnsForInsert))
                                    {
                                        std::cout << "Success!\n";
                                    }
                                    else
                                    {
                                        std::cout << "Something went wrong!\n";
                                    }
                                }
                                else if (req == 0)
                                {
                                    stop = true;
                                    break;
                                }
                                else
                                {
                                    std::cout << "Incorrect number, try again!\n";
                                }
                            }
                            if (stop)
                            {
                                stop = false;
                                break;
                            }
                        }
                        else if (tablename == "!q")
                        {
                            stop = true;
                            break;
                        }
                        else
                        {
                            std::cout << "No such table! Try again!\n";
                        }
                    }
                }
                else if (req == 8)
                {
                    while (true)
                    {
                        std::cout << "1:Update\n2:Delete\n0:Exit\n";
                        std::cin >> req;
                        std::string tablename;
                        if (req == 1 || req == 2)
                        {
                            while (true)
                            {
                                std::cout << "Choose table or type \"!q\" to go back to menu:\n";
                                std::cin >> tablename;
                                std::string column;
                                std::string data;
                                if (c.checkTable(tablename))
                                {
                                    std::cout << "Table:\n"
                                              << c.getFullTable(tablename);
                                    int numOfIterations;
                                    std::string condition;
                                    std::cout << "Enter condition like \"*column* = '*data*' or \"!q\" to exit\"\n";
                                    std::cin.ignore();
                                    getline(std::cin, condition);
                                    if (condition == "!q")
                                    {
                                        stop = true;
                                        break;
                                    }
                                    if (req == 1)
                                    {
                                        std::vector<std::string> values;
                                        while (true)
                                        {
                                            std::cout << "How many columns do you want to change?:\n";
                                            std::cin >> numOfIterations;
                                            if (numOfIterations >= 1 && numOfIterations <= c.getNumOfColumns(tablename))
                                            {
                                                break;
                                            }
                                            else
                                            {
                                                std::cout << "Number of columns must be greater then 0 and less then " << c.getNumOfColumns(tablename) + 1 << "! Try again!\n";
                                            }
                                        }
                                        for (int i = 1; i <= numOfIterations; i++)
                                        {
                                            while (true)
                                            {
                                                std::cout << i << " Value to change:\nColumn:\n";
                                                std::cin >> column;
                                                if (c.checkColumn(tablename, column))
                                                {
                                                    break;
                                                }
                                                else
                                                {
                                                    std::cout << "No such column! Try again!\n";
                                                }
                                            }
                                            std::cout << "Data:\n";
                                            std::cin >> data;
                                            values.push_back(column + " = '" + data + "'");
                                        }
                                        if (c.updateOperation(tablename, values, condition))
                                        {
                                            std::cout << "Success!\n";
                                        }
                                        else
                                        {
                                            std::cout << "Something went wrong!\n";
                                        }
                                    }
                                    else
                                    {
                                        if (c.deleteOperatin(tablename, condition) && c.updateSQLSequence(tablename, "ID"))
                                        {
                                            std::cout << "Success!\n";
                                        }
                                        else
                                        {
                                            std::cout << "Something went wrong!\n";
                                        }
                                    }
                                    stop = true;
                                    break;
                                }
                                else if (tablename == "!q")
                                {
                                    stop = true;
                                    break;
                                }
                                else
                                {
                                    std::cout << "No such table! Try again!\n";
                                }
                            }
                        }
                        else if (req == 0)
                        {
                            break;
                        }
                        else
                        {
                            std::cout << "Incorrect number, try again!\n";
                        }
                        if (stop)
                        {
                            stop = false;
                            break;
                        }
                    }
                }
                else if (req == 9)
                {
                    while (true)
                    {
                        double cost;
                        int flowerId;
                        std::cout << "Choose a flower:\n"
                                  << c.getFullTable("Flower");
                        std::cin >> flowerId;
                        if (flowerId > 0 && flowerId <= c.getNumOfRows("Flower"))
                        {
                            std::cout << "Enter new price:\n";
                            std::cin >> cost;
                            if (cost > 0)
                            {
                                if (c.checkCostChanges(flowerId, cost))
                                {
                                    std::cout << "Success!\n";
                                    break;
                                }
                                else
                                {
                                    std::cout << "You can't do it!\n";
                                    break;
                                }
                            }
                            else
                            {
                                std::cout << "Price must be greater than 0\n";
                            }
                        }
                        else
                        {
                            std::cout << "No such flower!\n";
                        }
                    }
                }
                else if (req == 10)
                {
                    std::cout << "Choose user to give him admin role:\n";
                    std::cout << c.getFullTable("Customer");
                    std::string userLogin;
                    std::cout << "Enter user's login:\n";
                    std::cin >> userLogin;
                    if (c.checkLogin(userLogin) && !c.isAdmin(userLogin))
                    {
                        c.giveAdmin(userLogin);
                        std::cout << "Success!\n";
                    }
                    else
                    {
                        std::cout << "No such user or user is already admin!\n";
                    }
                }
                /*else if (req == 11)
                {
                    std::string loginToDelete;
                    std::cout << c.getFullTable("Customer");
                    std::cout << "Choose user to delete:\n";
                    std::cin >> loginToDelete;
                    if (c.checkLogin(loginToDelete) && loginToDelete != login)
                    {
                        if (c.deleteUser(loginToDelete) && c.updateSQLSequence("Customer", "ID"))
                        {
                            std::cout << "Success!\n";
                        }
                    }
                    else
                    {
                        if (loginToDelete == login)
                        {
                            std::cout << "You can't delete yourself!\n";
                        }
                        else
                        {
                            std::cout << "There is no such user!\n";
                        }
                    }
                }*/
                else
                {
                    std::cout << "Incorrect number, try again!\n";
                }
            }
            else
            {
                std::string text = "What are you want to do?\n"
                                   "1: Change user \n"
                                   "2: Information about your orders(money)\n"
                                   "3: Make an order\n"
                                   "0: exit\n";
                std::cout << text;
                std::cin >> req;
                if (req == 0)
                {
                    return 0;
                }
                else if (req == 1)
                {
                    break;
                }
                else if (req == 2)
                {
                    std::vector<std::string> result;
                    std::string firstDate;
                    std::string secondDate;
                    std::cout << "Enter first date in format yyyy-mm-dd:\n";
                    std::cin >> firstDate;
                    std::cout << "Enter secondDate in format yyyy-mm-dd:\n";
                    std::cin >> secondDate;
                    result = c.customerOrders(firstDate, secondDate, login);
                    std::cout << "Information about your orders:\n";
                    for (int i = 0; i < result.size(); i++)
                        std::cout << result[i] << "\n";
                }
                else if (req == 3)
                {
                    // make order
                    std::vector<std::pair<int, int>> orderCompID;
                    while (true)
                    {
                        std::cout << "1:Add composition to order\n2:Send order\n0:Back to menu\n";
                        std::cin >> req;
                        if (req == 1)
                        {
                            int compID;
                            bool isInOrder = false;
                            std::cout << "Choose id of composition to add into order:\n";
                            std::cout << c.getFullTable("Composition");
                            std::cin >> compID;
                            if (c.checkComposeId(std::to_string(compID)))
                            {
                                for (int i = 0; i < orderCompID.size(); i++)
                                {
                                    if (orderCompID[i].first == compID)
                                    {
                                        isInOrder = true;
                                        orderCompID[i].second++;
                                        break;
                                    }
                                }
                                if (!isInOrder)
                                {
                                    orderCompID.push_back(std::make_pair(compID, 1));
                                }
                            }
                            else
                            {
                                std::cout << "No such ID\n";
                            }
                        }
                        else if (req == 2)
                        {
                            if (orderCompID.size() > 0)
                            {
                                if (c.makeOrder(orderCompID, c.getIDByLogin(login)))
                                {
                                    std::cout << "Success!\n";
                                }
                            }
                            else
                            {
                                std::cout << "Order is empty!\n";
                            }
                            break;
                        }
                        else if (req == 0)
                        {
                            break;
                        }
                        else
                        {
                            std::cout << "Incorrect number, try again!\n";
                        }
                    }
                }
                else
                {
                    std::cout << "Incorrect number, try again!\n";
                }
            }
        }
    }
}
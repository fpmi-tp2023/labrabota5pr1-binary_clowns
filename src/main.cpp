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
                                   "2: Information about orders\n"
                                   "3: Information about the most popular composition\n"
                                   "4: Information about urgent orders\n"
                                   "5: Information about used flowers\n"
                                   "6: Information about all sold compositions\n"
                                   "7: Insert information into table\n"
                                   "8: Update/delete information\n"
                                   "9: Change price of a flower\n"
                                   "10: Get information about all orders\n"
                                   "11: Delete user by login\n"
                                   "12: Give admin role by login\n"
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
                    // orders sum
                }
                else if (req == 3)
                {
                    // the most popular comp
                }
                else if (req == 4)
                {
                    // urgent orders
                }
                else if (req == 5)
                {
                    // used flowers
                }
                else if (req == 6)
                {
                    // sold compositions
                }
                else if (req == 7)
                {
                    // insert
                }
                else if (req == 8)
                {
                    // update/delete

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
                                std::vector<std::string> conditions;
                                std::string column;
                                std::string data;
                                if (c.checkTable(tablename))
                                {
                                    std::cout << "Table:\n"
                                              << c.getFullTable(tablename);
                                    int numOfIterations;
                                    while (true)
                                    {
                                        std::cout << "How many additional conditions do you want?:\n";
                                        std::cin >> numOfIterations;
                                        if (numOfIterations >= 1)
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            std::cout << "Number of conditions must be greater then 0! Try again!\n";
                                        }
                                    }
                                    for (int i = 1; i <= numOfIterations; i++)
                                    {
                                        while (true)
                                        {
                                            std::cout << i << "Condition:\nColumn:\n";
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
                                        conditions.push_back(column + " = '" + data + "'");
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
                                                std::cout << i << "Condition:\nColumn:\n";
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
                                            conditions.push_back(column + " = '" + data + "'");
                                        }
                                    }
                                    break;
                                }
                                else if (tablename == "!q")
                                {
                                    stop = true;
                                    break;
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
                    // Change price
                }
                else if (req == 10)
                {
                    // information about all orders(one day)
                }
                else if (req == 11)
                {
                    // delete user
                }
                else if (req == 12)
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
                else
                {
                    std::cout << "Incorrect number, try again!\n";
                }
            }
            else
            {
                std::string text = "What are you want to do?\n"
                                   "1: Change user \n"
                                   "2: Information about orders\n"
                                   "3: Make an order\n"
                                   "4: Get information about your orders\n"
                                   "5: Delete user\n"
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
                else if (req = 2)
                {
                    // orders sum
                }
                else if (req == 3)
                {
                    // make order
                }
                else if (req == 4)
                {
                    // info about user's orders
                }
                else if (req == 5)
                {
                    // Delete user
                }
                else
                {
                    std::cout << "Incorrect number, try again!\n";
                }
            }
        }
    }
}
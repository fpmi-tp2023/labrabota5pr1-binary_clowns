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
                if (c.checkLogin(login, db))
                {
                    if (c.checkPassword(login, password, db))
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
                    if (c.checkLogin(login, db))
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
                if (c.createUser(login, password, db))
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
        stop = false;
        bool is_admin; // check if user admin
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
                                   "8: Change columns in tables\n"
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
                else if (req = 2)
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
                }
                else if (req == 9)
                {
                    // Change price
                }
                else if (req == 10)
                {
                    // information about all orders(one day)
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
                else
                {
                    std::cout << "Incorrect number, try again!\n";
                }
            }
        }
    }
}
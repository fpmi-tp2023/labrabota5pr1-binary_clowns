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
                    std::cout << "1:Update\n2:Delete\n";
                    std::cin >> req;
                    while (true)
                    {
                        if (req == 1)
                        {
                            
                        }
                        else if (req == 2)
                        {
                            
                        }
                        else
                        {
                            std::cout << "Incorrect number, try again!\n";
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
                    std::cout << c.getUsers();
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
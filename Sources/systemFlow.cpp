#include "../Headers/systemFlow.h"

#include <fstream>
#include <vector>

void SystemFlow::runSystem() 
{
    while (true)
    {
        Account currentAccount;
        std::cout << "Welcome to ASKFM." << std::endl;
        while (currentAccount.get_id() == "-1")
        {
            std::cout << "1- Login" << std::endl;
            std::cout << "2- Signup" << std::endl;
            std::cout << "3- Exit" << std::endl;

            std::string choice;
            if (input_number(choice, {1, 3}))
            {
                if (choice == "1")
                {
                    login(currentAccount);
                }
                else if (choice == "2")
                {
                    signup(currentAccount);
                }
                else if (choice == "3")
                {
                    std::cout << "Thankd For Using ASKFM, Bye-Bye!" << std::endl;
                    return;
                }
            }
            else
            {
                continue;
            }
        }
        User currentUser(currentAccount); 
        this->view_mainMenu(currentUser) ;
    }
}

void SystemFlow::view_mainMenu(User &currentUser)
{
    while (true)
    {
        std::cout << "1- View All Users" << std::endl;
        std::cout << "2- View Questions You've Asked" << std::endl;
        std::cout << "3- View Questions Have been Asked To You" << std::endl;
        std::cout << "4- Show Feed" << std::endl;
        std::cout << "5- Back" << std::endl;

        std::string choice;
        if (!input_number(choice, {1, 5}))
        {
            continue;
        }
        if (choice == "1")
        {
            currentUser.view_allUsers();
        }
        else if (choice == "2")
        {
            currentUser.view_askAwayQuestions();
        }
        else if (choice == "3")
        {
            currentUser.view_askInQuestions();
        }
        else if (choice == "4")
        {
            currentUser.view_feed();
        }
        else if (choice == "5")
        {
            return;
        }
    }
}

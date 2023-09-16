#include "../Headers/signup.h"

#include <string>

void signup(Account &_account)
{
    std::string _id = "-1", _username, _password, _email, _name, _anonymouse;
    input_username(_username);
    input_password(_password);
    input_email(_email);
    input_name(_name);

    SystemBase systemBase;
    std::cout << "Do You Want To Recive Anonymouse Questions? " << std::endl;
    std::cout << "1- YES" << std::endl;
    std::cout << "2- NO" << std::endl;

    std::string anonymouseChoice;
    if (input_number(anonymouseChoice, {1, 2}) == false)
    {
        return;
    }
    if (anonymouseChoice == "1")
    {
        _anonymouse = "1";
    }
    else
    {
        _anonymouse = "0";
    }
    // check input is needed here.
    if (validate_email(_email) && validate_name(_name) && validate_password(_password) && validate_username(_username))
    {
        if (systemBase.userExist(_id, _username, _email, _password).first == false)
        {
            _id = systemBase.createNewAccount();
            _account.set_all(_id, _username, _password, _email, _name, _anonymouse);
            std::vector<std::string> details = _account.putOnVector();
            appendOnFile("Database/Accounts.txt", details);
        }
        else
        {
            std::cout << "Username OR Email Are Already Used Before" << std::endl;
            return;
        }
    }
    else
    {
        std::cout << "Invalid Input" << std::endl; 
    }
}
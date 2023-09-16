#include "../Headers/login.h"

void login(Account &_account)
{
    std::string _email, _password;
    input_email(_email);
    input_password(_password);
    SystemBase systemBase;
    std::pair<bool, std::string> check = systemBase.userExist("-1", "-1", _email, _password);
    if(check.first == false){
        std::cout << "Inccorect email or password, There is no such account with the given information." << std::endl ;

    }
    else{
        Account tem(check.second); 
        _account = tem;
    }
}

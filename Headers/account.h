#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

#include "helperFunctions.h"

class Account
{
private:
    std::string id;
    std::string username;
    std::string password;
    std::string email;
    std::string name;
    std::string anonymouse;

public:
    Account();
    Account(const std::string &_id, const std::string &_username, const std::string &_password, const std::string &_email, const std::string &_name, const std::string &_anonymouse);
    Account(const std::string &dataLine);
    // void operator<<() const ;
    std::string get_id() const;
    std::string get_username() const;
    std::string get_password() const;
    std::string get_email() const;
    std::string get_name() const;
    std::string get_anonymouse() const;
    bool allowAnonymouseQuestions() const;

    void set_id(const std::string &_id);
    void set_username(const std::string &_username);
    void set_password(const std::string &_password);
    void set_email(const std::string &_email);
    void set_name(const std::string &_name);
    void set_anonymouse(const std::string &_anonymouse);
    void set_all(const std::string &_id, const std::string &_username, const std::string &_password, const std::string &_email, const std::string &_name, const std::string &_anonymouse);
    void set_byID(const std::string &account_id) ;
    void printAccount() const;

    std::vector<std::string> putOnVector() const;
    std::string putOnString() const; 
};

#endif
#ifndef SYSTEMBASE_H
#define SYSTEMBASE_H

#include <string>
#include <vector>

#include "helperFunctions.h"

class SystemBase
{
private:
    std::string totalAccounts;
    std::string totalQuestions;

public:
    SystemBase();
    std::string get_totalAccounts() const;
    std::string get_totalQuestions() const;
    void set_totalAccounts(const std::string &_totalAccounts);
    void set_totalQuestions(const std::string &totalQuestions);
    void updateSystem() const;
    void fetchData();
    std::string createNewAccount();
    std::string createNewQuestion();
    std::pair<bool, std::string> userExist(const std::string &_id, const std::string &_username, const std::string &_email, const std::string &_password) const;    
    std::vector<std::string> putOnVector() const;

};

#endif
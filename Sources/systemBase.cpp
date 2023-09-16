#include "../Headers/systemBase.h"

SystemBase::SystemBase()
{
    this->fetchData();
}
std::string SystemBase::get_totalAccounts() const
{
    return this->totalAccounts;
}
std::string SystemBase::get_totalQuestions() const
{
    return this->totalQuestions;
}
void SystemBase::set_totalAccounts(const std::string &_totalAccounts)
{
    this->totalAccounts = _totalAccounts;
}
void SystemBase::set_totalQuestions(const std::string &_totalQuestions)
{
    this->totalQuestions = _totalQuestions;
}
std::vector<std::string> SystemBase::putOnVector() const
{
    std::vector<std::string> data;
    data.push_back(this->get_totalAccounts());
    data.push_back(this->get_totalQuestions());
    return data;
}

void SystemBase::updateSystem() const
{
    std::vector<std::string> systemData = this->putOnVector();
    writeOnFile("Database/SystemInformation.txt", systemData);
}
void SystemBase::fetchData()
{
    std::fstream file_System("Database/SystemInformation.txt");
    if (file_System.fail())
    {
        std::cerr << "Oops, Error While Fetching System Data." << std::endl;
        return;
    }
    std::string line;
    getline(file_System, line);
    std::vector<std::string> data = readLine(line);
    file_System.close();
    this->set_totalAccounts(data[0]);
    this->set_totalQuestions(data[1]);
}
std::string SystemBase::createNewAccount()
{
    std::string result = this->get_totalAccounts();
    std::string newTotalAccounts = std::to_string(std::stoi(result) + 1);
    this->set_totalAccounts(newTotalAccounts);
    this->updateSystem();
    return result;
}

std::string SystemBase::createNewQuestion()
{
    std::string result = this->get_totalQuestions();
    std::string newTotalQuestions = std::to_string(std::stoi(result) + 1);
    this->set_totalQuestions(newTotalQuestions);
    this->updateSystem();
    return result;
}

std::pair<bool, std::string> SystemBase::userExist(const std::string &_id, const std::string &_username, const std::string &_email, const std::string &_password) const
{
    std::pair<bool, std::string> result = {false, ""};

    std::fstream accountsFile("Database/Accounts.txt");
    if (accountsFile.fail())
    {
        std::cerr << "Oops, Error While Logging into Accounts File." << std::endl;
        return result;
    }
    std::string line;
    while (getline(accountsFile, line))
    {
        std::vector<std::string> accountData = readLine(line); 
        std::string account_id = accountData[0], account_username = accountData[1], account_password = accountData[2], account_email = accountData[3]; 
        if(((account_username == _username || account_email == _email) && account_password == _password) || account_id == _id)
        {
            result = {true, line} ;
            break ;
        }
    }
    accountsFile.close();
    return result;
}
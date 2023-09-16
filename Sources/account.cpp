#include "../Headers/account.h"

Account::Account(const std::string &_id, const std::string &_username, const std::string &_password, const std::string &_email, const std::string &_name, const std::string &_anonymouse)
    : id(_id), username(_username), password(_password), email(_email), name(_name), anonymouse(_anonymouse)
{
}
Account::Account()
{
    this->set_id("-1");
}

Account::Account(const std::string &dataLine)
{
    std::vector<std::string> dataVector = readLine(dataLine);
    std::string _id, _username, _password, _email, _name, _anonymouse;
    this->set_all(dataVector[0], dataVector[1], dataVector[2], dataVector[3], dataVector[4], dataVector[5]);
}

std::string Account::get_id() const
{
    return this->id;
}
std::string Account::get_username() const
{
    return this->username;
}
std::string Account::get_password() const
{
    return this->password;
}
std::string Account::get_email() const
{
    return this->email;
}
std::string Account::get_name() const
{
    return this->name;
}
std::string Account::get_anonymouse() const
{
    return this->anonymouse;
}
bool Account::allowAnonymouseQuestions() const
{
    return this->get_anonymouse() == "1";
}
void Account::set_id(const std::string &_id)
{
    this->id = _id;
}
void Account ::set_username(const std::string &_username)
{
    this->username = _username;
}
void Account ::set_password(const std::string &_password)
{
    this->password = _password;
}
void Account ::set_email(const std::string &_email)
{
    this->email = _email;
}
void Account ::set_name(const std::string &_name)
{
    this->name = _name;
}
void Account::set_anonymouse(const std::string &_anonymouse)
{
    this->anonymouse = _anonymouse;
}
void Account::set_all(const std::string &_id, const std::string &_username, const std::string &_password, const std::string &_email, const std::string &_name, const std::string &_anonymouse)
{
    this->set_id(_id);
    this->set_username(_username);
    this->set_password(_password);
    this->set_email(_email);
    this->set_name(_name);
    this->set_anonymouse(_anonymouse);
}
void Account::set_byID(const std::string &account_id)
{
    std::fstream accountsFile("Database/Accounts.txt");
    if (accountsFile.fail())
    {
        std::cerr << "Oops, Error Loading Accounts File." << std::endl;
        return;
    }
    std::string line;
    while (getline(accountsFile, line))
    {
        Account _account(line);
        if (_account.get_id() == account_id)
        {
            *this = _account;
            return;
        }
    }
}
std::vector<std::string> Account::putOnVector() const
{
    std::vector<std::string> data;

    data.push_back(this->get_id());
    data.push_back(this->get_username());
    data.push_back(this->get_password());
    data.push_back(this->get_email());
    data.push_back(this->get_name());
    data.push_back(this->get_anonymouse());

    return data;
}
std::string Account::putOnString() const
{
    std::string result = "";
    std::vector<std::string> data = this->putOnVector();
    for (int i = 0; i < (int)data.size(); i++)
    {
        result += data[i];
        result += wordsSplit;
    }
    return result;
}
void Account::printAccount() const
{
    std::cout << "ID: " << this->get_id() << "   Username: " << this->get_username() << "    Email: " << this->get_email() << "    Name: " << this->get_name() << "    ";
    std::cout << "AQ?: ";
    if (this->get_anonymouse() == "1")
        std::cout << "Yes";
    else
        std::cout << "No";
    std::cout << std::endl;
}
#include "../Headers/helperFunctions.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

std::vector<std::string> readLine(const std::string &line)
{
    std::vector<std::string> splitedLine;
    std::string tem = "";
    for (int i = 0; i < (int)line.size(); i++)
    {
        tem += line[i];
        if ((int)tem.size() >= (int)wordsSplit.size())
        {
            std::string check = tem.substr((int)tem.size() - (int)wordsSplit.size(), (int)wordsSplit.size());
            if (check == wordsSplit)
            {
                splitedLine.push_back(tem.substr(0, (int)tem.size() - (int)wordsSplit.size()));
                tem = "";
            }
        }
    }
    return splitedLine;
}

bool isNumber(const std::string &number)
{
    if ((int)number.size() == 0)
        return false;
    if (number[0] == '0')
        return false;
    for (int i = 0; i < (int)number.size(); i++)
    {
        if (!('0' <= number[i] && number[i] <= '9'))
            return false;
    }
    return true;
}

void appendOnFile(std::string filePath, std::vector<std::string> &details)
{
    std::ofstream outFile(filePath, std::ios::app);
    if (outFile.fail())
    {
        std::cerr << "Error Appending On File, System Faild!." << std::endl;
        return;
    }
    for (std::string tem : details)
    {
        outFile << tem << wordsSplit;
    }
    outFile << std::endl;
    outFile.close();
}

void writeOnFile(std::string filePath, std::vector<std::string> &details)
{
    std::ofstream outFile(filePath);
    if (outFile.fail())
    {
        std::cerr << "Error Writing On File,System Faild!.";
        return;
    }
    for (std::string tem : details)
    {
        outFile << tem << wordsSplit;
    }
    outFile.close();
}

void deleteFromFile(std::string filePath, std::string &stringToDelete)
{
    std::vector<std::string> hold;
    std::string line;
    std::fstream inFile(filePath);
    if (inFile.fail())
    {
        std::cerr << "Error Deleting From File, System Faild!" << std::endl;
        return;
    }
    while (getline(inFile, line))
    {
        if (line == stringToDelete)
            continue;
        hold.push_back(line);
    }
    inFile.close();
    writeOnFile(filePath, hold);
}
bool vectorExistInFile(std::string filePath, std::vector<std::string> &data)
{
    std::ifstream File(filePath);
    if (File.fail())
    {
        std::cerr << "Error Checking File, System Faild!" << std::endl;
        return false;
    }
    std::string line;
    bool found = false;
    while (getline(File, line))
    {
        std::vector<std::string> tem = readLine(line);
        if (tem == data)
        {
            found = true;
            break;
        }
    }
    File.close();
    return found;
}

void input_username(std::string &_username)
{
    std::cout << "Input username: ";
    getline(std::cin, _username);
}

void input_password(std::string &_password)
{
    std::cout << "Input password: ";
    getline(std::cin, _password);
}

void input_name(std::string &_name)
{
    std::cout << "Input name: ";
    getline(std::cin, _name);
}

void input_email(std::string &_email)
{
    std::cout << "Input email: ";
    getline(std::cin, _email);
}

bool input_number(std::string &number, std::pair<int, int> range)
{
    std::cout << "Input number in range " << range.first << "-" << range.second << ": ";
    getline(std::cin, number);
    if (isNumber(number))
    {
        int x = std::stoi(number);
        if (range.first <= x && x <= range.second)
            return true;
    }
    std::cout << "Invalid Input." << std::endl;
    return false;
}
std::string putOnString(std::vector<std::string> &data)
{
    std::string result = "";
    for (int i = 0; i < (int)data.size(); i++)
    {
        result += data[i];
        result += wordsSplit;
    }
    return result;
}
bool validate_email(const std::string &desired_email)
{
    return std::regex_match(desired_email, EMAIL_MATCH);
}
bool validate_password(const std::string &desired_password)
{
    return std::regex_match(desired_password, PASSWORD_MATCH);
}

bool validate_username(const std::string &desired_username)
{
    return std::regex_match(desired_username, USERNAME_MATCH);
}

bool validate_name(const std::string &desired_name)
{
    return std::regex_match(desired_name, NAME_MATCH);
}

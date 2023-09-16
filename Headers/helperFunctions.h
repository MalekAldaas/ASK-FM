#ifndef HELPER_FUNC_H
#define HELPER_FUNC_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

const std::string wordsSplit = "_!@#*w.w*&%#$__";
const std::regex NAME_MATCH = std::regex("[A-Za-z[:s:]]+");
const std::regex USERNAME_MATCH = std::regex("[A-Za-z0-94_.-]+");
const std::regex EMAIL_MATCH = std::regex("([A-Za-z0-9_.]+)(@)([A-Za-z]+)(.com)");
const std::regex PASSWORD_MATCH = std::regex("[A-Za-z0-9]+");

std::vector<std::string> readLine(const std::string &line);
void appendOnFile(std::string filePath, std::vector<std::string> &details);
void writeOnFile(std::string filePath, std::vector<std::string> &details);
void deleteFromFile(std::string filePath, std::string &stringToDelete);

void input_username(std::string &_username);
void input_password(std::string &_password);
void input_email(std::string &_email);
void input_name(std::string &_name);
bool input_number(std::string &number, std::pair<int, int> range);

bool isNumber(const std::string &number);
bool vectorExistInFile(std::string filePath, std::vector<std::string> &data);
bool validate_username(const std::string &);
bool validate_password(const std::string &);
bool validate_name(const std::string &);
bool validate_email(const std::string &);

std::string putOnString(std::vector<std::string> &data);

#endif
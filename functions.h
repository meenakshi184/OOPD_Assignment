#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <string>
using namespace std;

bool isNumeric(const std::string&);
std::string splitCSVLine(const std::string&, std::string*, int);
std::string splitLine(const std::string&, std::string*, int);
std::string splitString(const std::string&, std::string*, int);
bool isValidUserName(const std::string&);
std::string getField(const std::string&, int);

#endif

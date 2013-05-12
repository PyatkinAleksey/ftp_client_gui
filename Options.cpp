/* 
 * File:   Options.cpp
 * Author: Aleksey Pyatkin
 *
 * Created on 12.05.2013, 14:10
 */

#include "Options.h"

Options::Options() {
    char directory[MAX_PATH];
    
    configPath = "";
    GetCurrentDirectoryA(MAX_PATH, directory);
    configPath.append(directory).append("\\config.ini");
}

string Options::getParameter(string section, string parameter, string defaultValue) {
    char param[256];
    
    GetPrivateProfileStringA(section.c_str(), parameter.c_str(), defaultValue.c_str(), param, 100, configPath.c_str());
    
    return param;
}

int Options::getParameter(string section, string parameter, int defaultValue) {
    return GetPrivateProfileIntA(section.c_str(), parameter.c_str(), defaultValue, configPath.c_str());
}

void Options::setParameter(string section, string parameter, string value) {
    WritePrivateProfileStringA(section.c_str(), parameter.c_str(), value.c_str(), configPath.c_str());
}

void Options::setParameter(string section, string parameter, int value) {
    char buffer[256];
    
    itoa(value, buffer, 10);
    WritePrivateProfileStringA(section.c_str(), parameter.c_str(), buffer, configPath.c_str());
}
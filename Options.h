/* 
 * File:    Options.h
 * Author:  Aleksey Pyatkin
 *
 * Created on 12.05.2013, 13:05
 */

#pragma once

#include <windows.h>
#include <string>

using namespace std;

class Options {
        
    public:
        Options();
        string getParameter(string section, string parameter, string defaultValue);
        int getParameter(string section, string parameter, int defaultValue);
        void setParameter(string section, string parameter, string value);
        void setParameter(string section, string parameter, int value);
        
    private:
        string configPath;
    
};
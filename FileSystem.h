/* 
 * File:    Directories.h
 * Author:  Aleksey Pyatkin
 *
 * Created on 12.05.2013, 19:49
 */

#include <list>
#include <string>
#include <windows.h>

using namespace std;

class FileSystem {
    
    public:
        list<string> getGlobalEntities();
    
};
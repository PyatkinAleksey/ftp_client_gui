/* 
 * File:   Directories.cpp
 * Author: Aleksey Pyatkin
 *
 * Created on 12.05.2013, 19:52
 */

#include "FileSystem.h"

list<string> FileSystem::getGlobalEntities() {
    DWORD driveMask = GetLogicalDrives();
    list<string> globalEntities;
    string letter = "A:";
    
    while (driveMask) {
        if (driveMask & 1) {
            globalEntities.push_back(letter);
        }
        letter[0]++;
        driveMask >>= 1;
    }
    
    return globalEntities;
}

list<string> FileSystem::getFileNames(string path) {
    WIN32_FIND_DATAA findFile;
    HANDLE hFind = FindFirstFileA(path.append("\\*").c_str(), &findFile);
    list<string> fileNames;
    
    do {
        if (strcmp(findFile.cFileName, ".")) {
            fileNames.push_back(findFile.cFileName);
        }
    } while (FindNextFileA(hFind, &findFile));
    
    return fileNames;
}
/* 
 * File:   Directories.cpp
 * Author: Aleksey Pyatkin
 *
 * Created on 12.05.2013, 19:52
 */

#include "FileSystem.h"

/**
 * Получить список глобальных сущностей.
 * 
 * @return Список глобальных сущностей.
 */
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

/**
 * Получить список файлов и директорий.
 * 
 * @param path Путь, по которому нужно получить список.
 * 
 * @return Список файлов и директорий.
 */
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

/**
 * Проверка пути, файл или директорий.
 * 
 * @param path Путь.
 * 
 * @return 0 - каталог, другое - файл.
 */
int FileSystem::isFile(string path) {
    if (GetFileAttributesA(path.c_str()) & FILE_ATTRIBUTE_DIRECTORY) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * Создать директорию.
 * 
 * @param name Имя создаваемой директории.
 * 
 * @return 0 - не создана, другое - создана.
 */
int FileSystem::makeDirectory(string name) {
    return CreateDirectoryA(name.c_str(), 0);
}
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

/**
 * Класс для работы с файловой системой.
 */
class FileSystem {
    
    public:
        list<string> getGlobalEntities();       // Получить список глобальных сущностей
        list<string> getFileNames(string path); // Получить список файлов и директорий
        int isFile(string path);                // Проверка пути, файл или каталог
        int makeDirectory(string name);         // Создать директорию
        int deleteFile(string name);            // Удалить файл
        int deleteDirectory(string name);       // Удалить директорию
        int rename(string name);                // переименовать файл или директорию
    
};
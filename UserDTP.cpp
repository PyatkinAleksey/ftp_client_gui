/* 
 * File:   UserDTP.cpp
 * Author: Aleksey Pyatkin
 *
 * Created on 04.05.2013, 2:01
 */

#include <winsock2.h>
#include <ios>
#include "UserDTP.h"

/**
 * Инициализация пользовательского процесса передачи данных.
 */
UserDTP::UserDTP() {
    service = new Service();
    this->connected = 0;
}

/**
 * Установка локального пути для сохранения файлов, получаемых от сервера.
 * 
 * @param path Путь.
 */
void UserDTP::setLocalPath(string path) {
    this->localPath = path;
}

/**
 * Установка адреса сервера.
 * 
 * @param address Адрес сервера.
 */
void UserDTP::setAddress(string address) {
    this->address = address;
}

/**
 * Установка пути к файлу.
 * 
 * @param path Путь.
 */
void UserDTP::setPath(string path) {
    this->path = path;
}

/**
 * Установка порта для соединения по данным.
 * 
 * @param port Порт.
 */
void UserDTP::setPort(int port) {
    this->port = port;
}

/**
 * Установка типа передаваемых данных.
 * 
 * @param type Тип.
 */
void UserDTP::setType(string type) {
    this->type = type;
    if (type != "A N" && type != "I") {
        this->type = "A N";
    }
}

/**
 * Установить флаг использования пассивного режима.
 * 
 * @param passive Флаг (0 - активный режима, другое - пассивный).
 */
void UserDTP::setPassive(int passive) {
    this->passive = passive;
}

/**
 * Проверка, осуществлено ли соединение по данным.
 * 
 * @return 0 - нет соединения, другое - соединение установлено.
 */
int UserDTP::isConnected() {
    return connected;
}

/**
 * Открытие соединения по данным (прослушивающий сокет).
 */
void UserDTP::openConnection() {
    WSADATA wsaData;
    sockaddr_in dataAddress;
    
    if (isConnected()) {
        closeConnection();
    }
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != NO_ERROR) {
        service->printMessage(2, "Connection failed!");
        return;
    }
    dataSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (dataSocket == INVALID_SOCKET) {
        service->printMessage(2, "Invalid socket!");
        WSACleanup();
        return;
    }
    dataAddress.sin_family = AF_INET;
    if (passive) {
        dataAddress.sin_addr.s_addr = inet_addr(address.c_str());
        dataAddress.sin_port = htons(port);
        result = connect(dataSocket, (SOCKADDR*)&dataAddress, sizeof(dataAddress));
        if (result == SOCKET_ERROR) {
            service->printMessage(2, "Socket error!");
            result = closesocket(dataSocket);
            if (result == SOCKET_ERROR) {
                service->printMessage(2, "Socket error!");
            }
            WSACleanup();
            return;
        }
        connected = 1;
    } else {
        dataAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
        dataAddress.sin_port = htons(port);
        result = bind(dataSocket, (SOCKADDR*)&dataAddress, sizeof(dataAddress));
        if (result == SOCKET_ERROR) {
            service->printMessage(2, "Socket error!");
            result = closesocket(dataSocket);
            if (result == SOCKET_ERROR) {
                service->printMessage(2, "Socket error!");
            }
            WSACleanup();
            return;
        }
        if (listen(dataSocket, SOMAXCONN) == SOCKET_ERROR) {
            service->printMessage(2, "Socket error!");
            closesocket(dataSocket);
            WSACleanup();
            return;
        }
        acceptSocket = accept(dataSocket, NULL, NULL);
        if (acceptSocket == INVALID_SOCKET) {
            service->printMessage(2, "Invalid accept socket!");
            closesocket(dataSocket);
            WSACleanup();
            return;
        } else {
            connected = 1;
        }
    }
}

/**
 * Закрытие соединения по данным (прослушивающий сокет).
 */
void UserDTP::closeConnection() {
    closesocket(dataSocket);
    WSACleanup();
    connected = 0;
}

/**
 * Получить список имен файлов и директорий.
 * 
 * @return Массив имен файлов и директорий.
 */
list<string> UserDTP::fileList() {
    list<string> filelist;
    char *token;
    
    do {
        memset(buffer, 0, MAX_BUF_LEN);
        result = recv(dataSocket, buffer, MAX_BUF_LEN, 0);
        if (result > 0) {
            token = strtok(buffer, "\r\n");
            if (token != NULL && !filelist.empty()) {
                (*(--filelist.end())).append(token);
                token = strtok(NULL, "\r\n");
            }
            while (token != NULL) {
                filelist.push_back(token);
                token = strtok(NULL, "\r\n");
            }
        }
    } while (result > 0);
    
    return filelist;
}

/**
 * Выполнение передачи файлов от сервера.
 */
void UserDTP::retrieve() {
    ofstream stream;
    string fullPath = localPath;
    ios_base::openmode mode;

    if (type == "A N") {
        mode = ofstream::out;
    } else if (type == "I") {
        mode = ofstream::out | ofstream::binary;
    }
    stream.open(fullPath.c_str(), mode);
    do {
        memset(buffer, 0, MAX_BUF_LEN);
        if (type == "A N") {
            result = recv(dataSocket, buffer, MAX_BUF_LEN, 0);
        } else if (type == "I") {
            result = recv(dataSocket, &buffer[0], 1, 0);
        }
        if (result > 0) {
            if (strstr(buffer, "226 ")) {
                service->printMessage(0, buffer);
            }
            if (type == "A N") {
                stream << buffer;
            } else if (type == "I") {
                stream << buffer[0];
            }
        }
    } while(result > 0);
    stream.close();
    service->printMessage(1, "Transfer completed!\n" + path + " -> " + fullPath);
}

/**
 * Выполнение передачи файлов на сервер.
 */
void UserDTP::store() {
    ifstream stream;
    ios_base::openmode mode;
    
    if (type == "A N") {
        mode = ifstream::in;
    } else if (type == "I") {
        mode = ifstream::in | ofstream::binary;
    }
    stream.open(localPath.c_str(), mode);
    stream.seekg(0, stream.beg);
    do {
        memset(buffer, 0, MAX_BUF_LEN);
        if (type == "A N") {
            stream.read(buffer, MAX_BUF_LEN);
            result = send(dataSocket, buffer, stream.gcount(), 0);
            if (stream.eof()) {
                break;
            }
        } else if (type == "I") {
            int i = 0;
            while (!stream.eof() && (i < MAX_BUF_LEN)) {
                stream.read(&buffer[i], sizeof(char));
                i++;
            }
            if (stream.eof()) {
                result = send(dataSocket, buffer, i-1, 0);
                break;
            } else {
                result = send(dataSocket, buffer, i, 0);
            }
        }
        if (result <= 0) {
            service->printMessage(2, "Transfer error!");
            return;
        }
    } while (true);
    stream.close();
    closeConnection();
    service->printMessage(1, "Transfer completed!");
}

UserDTP::~UserDTP() {
    delete service;
}
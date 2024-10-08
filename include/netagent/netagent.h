#define WIN32_LEAN_AND_MEAN

#pragma once

#include <iostream>

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "FastCont/FastCont.h"
// #include <stdlib.h>

#define MAX_BUF_LEN 512

#define DEFAULT_PORT "27015"

struct ClientConnection;
class NetServer;


struct RecievedData {
    char data[MAX_BUF_LEN];
    int len = MAX_BUF_LEN;
};
struct ClientConnection {
    SOCKET socket = INVALID_SOCKET;
    RecievedData recieved;
};
class NetServer {
    SOCKET ListenSocket = INVALID_SOCKET;
    FastCont<ClientConnection> ClientSockets;

public:
    NetServer();
    ~NetServer();
    int acceptNewClient(); // return: -1 no_new_connection/error,  >= 0 ID of new accepted client
    int recieveData(int);
    int sendData(int, const char *, int);
    RecievedData *getLastData(int);
};

enum recieveData_ret {
    recieveData_SUCCESS = 0,
    recieveData_CONNECTION_CLOSED = -1
};

enum getConnectionStatus_ret {
    getConnectionStatus_GOOD = 0,
    getConnectionStatus_NO_HOST = -1,
    getConnectionStatus_ERR = -2,
};

enum recieveData_err {
    recieveData_OK = 0,
    recieveData_NO_NEW_DATA = -1,
    recieveData_CONN_CLOSED_BY_CLIENT_ERR = -2,
    recieveData_NO_CLIENT_ERR = -3,
    recieveData_ERR = -4,
};

#include "netagent/netagent_s.cpp"
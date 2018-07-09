//
// EPITECH PROJECT, 2018
// co
// File description:
// zappy
//

#pragma once
#include <string>
#include "lib-socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace Ui {
  class ConnectionHandler {
  public:
    ConnectionHandler();
    ~ConnectionHandler();
    void setIpandPort(std::string ip, std::string port);
    static void readSocket(std::string *, int);
    int getSocket();
  private:
    std::string _ip;
    size_t _port;
    socket_t _socket;
  };
};

//
// EPITECH PROJECT, 2018
// co
// File description:
// zappy
//

#include "ConnectionHandler.hpp"
#include <iostream>

Ui::ConnectionHandler::ConnectionHandler()
{
}

Ui::ConnectionHandler::~ConnectionHandler()
{
  destruct_socket(_socket);
}

void Ui::ConnectionHandler::setIpandPort(std::string ip, std::string port)
{
  const char *tmp;
  _ip = ip;
  _port = static_cast<size_t>(atoi(port.c_str()));
  tmp = _ip.c_str();
  _socket = create_socket((char*)tmp, _port, false);
  if (connect_socket(_socket) == true)
    std::cout << "connected" << '\n';
  else
    exit(42);
  write(_socket->fd, "GRAPHIC\n", 8);
}

int Ui::ConnectionHandler::getSocket()
{
  return _socket->fd;
  }

void Ui::ConnectionHandler::readSocket(std::string *buffer, int fd)
{
  char buff[512];
  struct timeval tv;

	tv.tv_sec = 1;
	tv.tv_usec = 0;
  while (*buffer != "seg\n") {
    std::string tmp;
    fd_set readf;
    FD_ZERO(&readf);
    FD_SET(fd, &readf);
    select(fd + 1, &readf, NULL, NULL, &tv);
    while (FD_ISSET(fd, &readf)) {
      int s = read(fd, buff, 512);
      buff[s] = 0;
      tmp = tmp + buff;
      *buffer = tmp;
      if (*buffer == "seg\n")
        return;
    }
    tmp.clear();
  }
}

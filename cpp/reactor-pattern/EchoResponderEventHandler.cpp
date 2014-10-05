#include <stdexcept>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include <netinet/in.h>

#include "EchoResponderEventHandler.hpp"

EchoResponderEventHandler::EchoResponderEventHandler(int fd):
  EventHandler(fd)
{
}

EchoResponderEventHandler::~EchoResponderEventHandler()
{
  close(_fd);
}

void EchoResponderEventHandler::handleEvent(uint32_t event) 
{
  if (event & EPOLLIN) {
    char msg[2048];
    memset(msg, 0, 2048);

    int readBytes = read(_fd, msg, 2048);

    if (readBytes < 0) {
      throw std::runtime_error("Cannot read from socket.");
    }

    int writtenBytes = write(_fd, msg, readBytes);

    if (writtenBytes < 0) {
      throw std::runtime_error("Cannot write to socket.");
    }
  } else {
    throw std::runtime_error("Bad event for responder.");
  }
}

#include <stdexcept>
#include <cstring>

#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include "AcceptorEventHandler.hpp"
#include "EchoResponderEventHandler.hpp"

AcceptorEventHandler::AcceptorEventHandler(int port, EpollReactor& reactor)
  : EventHandler(0), _port(port), _reactor(reactor) 
{
  _fd = socket(AF_INET, SOCK_STREAM, 0);
  
  if (_fd < 0) {
    throw std::runtime_error("Cannot create acceptor socket.");
  }

  int flags = fcntl(_fd, F_GETFL, 0);
  fcntl(_fd, F_SETFL, flags | O_NONBLOCK);

  struct sockaddr_in address;
  memset(&address, 0, sizeof(address));

  address.sin_family = AF_INET;
  address.sin_port = htons(_port);
  address.sin_addr.s_addr = INADDR_ANY;

  memcpy(&_address, &address, sizeof(address));
  _addressLength = sizeof(address);

  if (bind(_fd, &_address, _addressLength) < 0) {
    throw std::runtime_error("Cannot bind acceptor socket.");
  }

  if (listen(_fd, 1) != 0) {
    throw std::runtime_error("Cannot listen on acceptor socket.");
  }
}

AcceptorEventHandler::~AcceptorEventHandler()
{
  close(_fd);
}

void AcceptorEventHandler::handleEvent(uint32_t event)
{
  if (event & EPOLLIN) {
    struct sockaddr address;
    memset(&address, 0, sizeof(address));

    socklen_t addressLength = sizeof(address);

    int fd = accept(_fd, &address, &addressLength);

    if (fd < 0) {
      throw std::runtime_error("Cannot accept incoming connection.");
    }

    EpollReactor::EventHandler::Ptr handler(new EchoResponderEventHandler(fd));
    _reactor.registerHandler(handler);
  } else {
    throw std::runtime_error("Bad event for acceptor.");
  }
}

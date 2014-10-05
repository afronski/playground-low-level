#include <cstring>
#include <stdexcept>

#include <sys/epoll.h>

#include "EpollReactor.hpp"

EpollReactor::EpollReactor():
  _epollFd(-1), _maxEvents(100)
{
  _epollFd = epoll_create(_maxEvents);

  if (_epollFd < 0) {
    throw std::runtime_error("Epoll create failed.");
  }
}

EpollReactor::~EpollReactor()
{
  close(_epollFd);
}

void EpollReactor::registerHandler(EventHandler::Ptr eventHandler)
{
  int fd = eventHandler->getHandle();
  int option = EPOLL_CTL_ADD;

  epoll_event eventDescriptor;
  memset(&eventDescriptor, 0, sizeof(eventDescriptor));

  eventDescriptor.data.fd = fd;
  eventDescriptor.events |= EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP;

  if (epoll_ctl(_epollFd, option, fd, &eventDescriptor) < 0) {
    throw std::runtime_error("Add handler to epoll failed.");
  }

  _handlers[fd] = eventHandler;
}

void EpollReactor::removeHandler(int fd) 
{
  HandlersMap::iterator it = _handlers.find(fd);

  if (it == _handlers.end()) {
    throw std::runtime_error("Handler not found.");
  }

  if (epoll_ctl(_epollFd, EPOLL_CTL_DEL, fd, 0) < 0) {
    _handlers.erase(it);
    throw std::runtime_error("Cannot remove fd from epoll.");
  }

  _handlers.erase(it);
}

void EpollReactor::eventLoop() const 
{
  while (1) {
    boost::scoped_array<epoll_event> events(new epoll_event[_maxEvents]);
    memset(events.get(), 0, _maxEvents * sizeof(epoll_event));

    int eventsLength = 0;
    
    eventsLength = epoll_wait(_epollFd, events.get(), _maxEvents, -1);

    if (eventsLength < 0) {
      throw std::runtime_error("Epoll wait failed.");
    }

    for (int i = 0; i < eventsLength; ++i) {
      HandlersMap::const_iterator it = _handlers.find(events[i].data.fd);

      if (it != _handlers.end()) {
        it->second->handleEvent(events[i].events);
      } else {
        throw std::runtime_error("Epoll returned event for undefined handler.");
      }
    }
  }
}

EpollReactor::EventHandler::EventHandler(int fd):
  _fd(fd)
{
  if (fd < 0) {
    throw std::runtime_error("Invalid file descriptor passed to EventHandler.");
  }
}

EpollReactor::EventHandler::~EventHandler()
{
}

int EpollReactor::EventHandler::getHandle() const 
{
  return _fd;
}

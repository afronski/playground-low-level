#include <unistd.h>
#include <sys/epoll.h>

#include <boost/algorithm/string/predicate.hpp>

#include "KeyboardEventHandler.hpp"

KeyboardEventHandler::KeyboardEventHandler(const std::string& _fileName):
  EventHandler(0), _file(_fileName.c_str(), std::ofstream::out)
{
  if (!_file.is_open()) {
    throw std::runtime_error("Cannot open file.");
  }
}

KeyboardEventHandler::~KeyboardEventHandler()
{
  _file.close();
}

void KeyboardEventHandler::handleEvent(uint32_t event)
{
  if (event & EPOLLIN) {
    char toRead[1024];
    memset(toRead, 0, 1024);

    ssize_t readBytes = read(0, toRead, 1024);

    if (readBytes < 0) {
      throw std::runtime_error("Cannot read from keyboard handler.");
    }
    
    _file << toRead;
    
    if (boost::istarts_with(toRead, "exit")) {
      throw std::runtime_error("exit");
    }
  } else {
    throw std::runtime_error("Bad event for keyboard handler.");
  }
}

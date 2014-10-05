#ifndef __KEYBOARD_EVENT_HANDLER_HPP__
#define __KEYBOARD_EVENT_HANDLER_HPP__

#include <cstdint>
#include <string>
#include <fstream>

#include "EpollReactor.hpp"

class KeyboardEventHandler : public EpollReactor::EventHandler {
  public:
    KeyboardEventHandler(const std::string&);
    virtual ~KeyboardEventHandler();

    virtual void handleEvent(uint32_t);

  private:
    std::ofstream _file;
};

#endif

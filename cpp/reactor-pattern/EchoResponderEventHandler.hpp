#ifndef __ECHO_RESPONDER_EVENT_HANDLER_HPP__
#define __ECHO_RESPONDER_EVENT_HANDLER_HPP__

#include <cstdint>

#include "EpollReactor.hpp"

class EchoResponderEventHandler : public EpollReactor::EventHandler {
  public:
    explicit EchoResponderEventHandler(int fd);
    virtual ~EchoResponderEventHandler();
  
    virtual void handleEvent(uint32_t);
};

#endif

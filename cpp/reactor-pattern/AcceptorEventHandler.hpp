#ifndef __ACCEPTOR_EVENT_HANDLER_HPP__
#define __ACCEPTOR_EVENT_HANDLER_HPP__

#include <cstdint>

#include <netinet/in.h>

#include "EpollReactor.hpp"

class AcceptorEventHandler : public EpollReactor::EventHandler {
  public:
    AcceptorEventHandler(int, EpollReactor&);
    virtual ~AcceptorEventHandler();

    virtual void handleEvent(uint32_t);

  private:
    int _port;

    struct sockaddr _address;
    socklen_t _addressLength;
    
    EpollReactor& _reactor;
};

#endif

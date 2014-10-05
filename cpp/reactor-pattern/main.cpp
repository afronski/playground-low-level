#include <stdexcept>
#include <iostream>
#include <string>

#include "EpollReactor.hpp"

#include "KeyboardEventHandler.hpp"
#include "AcceptorEventHandler.hpp"

int main(int, char**)
{
  try {
    EpollReactor reactor;
    EpollReactor::EventHandler::Ptr keyboardHandler(
      new KeyboardEventHandler("log.txt")
    );

    EpollReactor::EventHandler::Ptr acceptorHandler(
      new AcceptorEventHandler(5050, reactor)
    );

    reactor.registerHandler(keyboardHandler);
    reactor.registerHandler(acceptorHandler);
    
    reactor.eventLoop();
  } catch(const std::runtime_error& rte) {
    std::cout << "Runtime exception: " << rte.what() << std::endl;
  } catch(const std::exception& exception) {
    std::cout << "Standard exception: " << exception.what() << std::endl;
  }

  return 0;
}

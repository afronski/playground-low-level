#ifndef __EPOLL_REACTOR_HPP__
#define __EPOLL_REACTOR_HPP__

#include <map>
#include <cstdint>

#include <boost/smart_ptr.hpp>

class EpollReactor {
  public:
    //
    // Base class for future event handlers implementation.
    //
    class EventHandler {
      public:
        typedef boost::shared_ptr<EventHandler> Ptr;
      
        explicit EventHandler(int);
        virtual ~EventHandler();

        int getHandle() const;
        virtual void handleEvent(uint32_t) = 0;

      protected:
        int _fd;

      private:
        // Non-copyable idiom.
        EventHandler(const EventHandler&);
        EventHandler& operator=(const EventHandler&);
    };

    EpollReactor();
    ~EpollReactor();

    void registerHandler(EventHandler::Ptr);
    void removeHandler(int);
    void eventLoop() const;

  private:
    // Non-copyable idiom.
    EpollReactor(const EpollReactor&);
    EpollReactor& operator=(const EpollReactor&);

    typedef std::map<int, EventHandler::Ptr> HandlersMap;
  
    int _epollFd;
    int _maxEvents;

    HandlersMap _handlers;
};

#endif

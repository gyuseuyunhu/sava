#ifndef ACCEPTEVENT_HPP
#define ACCEPTEVENT_HPP

#include "AEvent.hpp"

class AcceptEvent : public AEvent
{
  public:
    AcceptEvent(const Server &server);
    ~AcceptEvent();
    virtual int handle();
};

#endif
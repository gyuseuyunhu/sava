#ifndef WRITEEVENT_HPP
#define WRITEEVENT_HPP

#include "AEvent.hpp"
#include <unistd.h>

class WriteEvent : public AEvent
{
  private:
    std::string mMessage;
    int mWriteSize;
    int mResponseSize;
		int mStatus;

  public:
    WriteEvent(const Server &server, int clientSocket, std::string message, int status);
    virtual ~WriteEvent();
    virtual void handle();
};

#endif
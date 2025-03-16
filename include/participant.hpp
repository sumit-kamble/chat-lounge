#ifndef PARTICIPANT_HPP
#define PARTICIPANT_HPP

#include "message.hpp"
#include <memory>
class Participant
{
public:
    virtual void deliver(Message &message) = 0;
    virtual void write(Message &message) = 0;
    virtual ~Participant() = default;
};

typedef std::shared_ptr<Participant> ParticipantPointer;

#endif
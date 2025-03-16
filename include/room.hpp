#ifndef ROOM_HPP
#define ROOM_HPP

#include "participant.hpp"
#include <set>
#include <deque>

class Room
{
public:
    void join(ParticipantPointer participant);
    void leave(ParticipantPointer participant);
    void deliver(ParticipantPointer participantPointer, Message &message);

private:
    std::deque<Message> messageQueue;
    static constexpr int MaxParticipants = 100;
    std::set<ParticipantPointer> participants;
};

#endif

#include "room.hpp"

void Room::join(ParticipantPointer participant)
{
    this->participants.insert(participant);
}

void Room::leave(ParticipantPointer participant)
{
    this->participants.erase(participant);
}

void Room::deliver(ParticipantPointer participant, Message &message)
{
    messageQueue.push_back(message);
    while (!messageQueue.empty())
    {
        Message msg = messageQueue.front();
        messageQueue.pop_front();

        for (ParticipantPointer _participant : participants)
        {
            if (participant != _participant)
            {
                _participant->write(msg);
            }
        }
    }
}

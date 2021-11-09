#include "EventQ.h"

Event::Event(const Event &other):type(other.type), xPos(other.xPos),
yPos(other.yPos)
{

}

Event::Event(EVENT_TYPE type, float x, float y):type(type), xPos(x), yPos(y)
{

}


EventQ* EventQ::instance = nullptr;

std::queue<std::shared_ptr<Event>> EventQ::q;


EventQ::EventQ()
{

}

EventQ::~EventQ()
{
    if(instance)
    {
        delete instance;
        instance= nullptr;
    }
}

std::shared_ptr<Event> EventQ::pollEvent()
{
    auto ret = q.front();
    q.pop();
    return ret;
}

bool EventQ::isEmpty()
{
    return q.empty();
}

void EventQ::pushEvent(const Event &event)
{
    q.push(std::make_shared<Event>(event));
}

EventQ* EventQ::getInstance()
{
    if(instance == nullptr)
    {
        instance = new EventQ();
    }
    return instance;
}
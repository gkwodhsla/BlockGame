#pragma once
#include <queue>
#include <memory>

enum class EventType
{
    FINGER_DOWN,
    FINGER_UP,
    FINGER_SWIPE
};

class Event
{
public:
    Event() = delete;
    Event(const Event&);
    Event&operator=(const Event&) = delete;
    Event(EventType type, float x, float y);

public:
    const EventType type;
    float xPos = 0.0f;
    float yPos = 0.0f;
};

class EventQ final
{
public:
    EventQ(const EventQ&) = delete;
    EventQ&operator=(const EventQ&) = delete;
    virtual ~EventQ();

public:
    static std::shared_ptr<Event> pollEvent();
    static bool isEmpty();
    static void pushEvent(const Event& event);

public:
    static EventQ* getInstance();
    static EventQ* instance;

private:
    EventQ();

private:
    static std::queue<std::shared_ptr<Event>> q;
};
#pragma once

//커스텀 다운캐스팅을 위한 인터페이스를 제공하는 클래스이다.
class HObject
{
public:
    HObject() = default;
    HObject(const HObject&) = delete;
    HObject& operator=(const HObject&) = delete;
    virtual ~HObject() = 0;

public:
    inline void setID(void* newID)
    {
        id = newID;
    }
    inline void* getID() const
    {
        return id;
    }

public:
    void* id = nullptr;
};
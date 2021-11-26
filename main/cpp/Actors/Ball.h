#pragma once
#include "HActor.h"

class CircleCollisionComponent;
class ImageComponent;
class MovementComponent;
class ParticleComponent;
class Ball: public HActor
{
public:
    Ball();
    Ball(const Ball&) = delete;
    Ball&operator=(const Ball&) = delete;
    virtual ~Ball();

public:
    virtual void render() override;
    virtual void update(const float deltaTime) override;
    void setCollisionComp(float rad);

public:
    void setIsDirVecChangedRecently(bool isChanged){isDirVecChangedRecently = isChanged;}
    bool getIsDirVecChangedRecently()const {return isDirVecChangedRecently;}

public:
    ParticleComponent* ballParticle = nullptr;

private:
    ImageComponent* ballImg = nullptr;
    CircleCollisionComponent* collisionComp = nullptr;
    MovementComponent* ballMovement = nullptr;
    static const float ballSpeed;
    static const float deadLine;
    bool isDirVecChangedRecently = false;
    float dirCoolTime = 0.1f;
    static constexpr float maxDirCoolTime = 0.1f;
};
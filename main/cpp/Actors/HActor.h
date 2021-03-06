#pragma once

#include <utility>
#include <functional>
#include <vector>
#include "../Common/HObject.h"
#include "../Common/Common.h"
#include <glm/glm.hpp>
#include <GLES3/gl3.h>

class HComponent;
class HSceneComponent;

//액터는 월드에 배치되는 오브젝트이다.
//액터는 반드시 하나의 루트 컴포넌트를 가지고, 이 컴포넌트에
//다른 컴포넌트를 붙이는 방식으로 확장한다.
//액터는 트랜스폼 정보를 루트컴포넌트에 의존하며
//자식 컴포넌트의 트랜스폼은 부모 컴포넌트에 의존한다.
//또한 액터는 lifeTime을 가질 수 있고 별도 세팅을 하지 않는다면
//명시적으로 파괴하거나 레벨을 떠날 때 까지 존재한다.
//lifeTime이 0초가 됐을 때 default Action은 액터의 파괴이고,
//다양한 커스텀 함수를 등록할 수 있다.
class HActor: public HObject
{
public:
    HActor();
    HActor(const HActor&) = delete;
    HActor&operator=(const HActor&) = delete;
    virtual ~HActor() = 0;

public:
    void moveTo(const std::pair<float, float>& loc);
    void rotateActor(const float degree);
    virtual void render();
    virtual void update(const float deltaTime);

public:
    void setVisibility(const bool isVisible);
    bool getVisibility() const;
    HSceneComponent* getRootComponent() const;
    glm::vec2 getActorDirectionalVector() const;
    void setActorDirectionalVector(const glm::vec2& newDir);
    std::pair<float, float> getActorWorldLocation();
    std::pair<float, float> getActorWorldScale();
    void setActorWorldLocation(const float x, const float y);
    void setActorWorldScale(const float x, const float y);
    float getActorWorldRotation() const;
    void setActorTickable(const bool isTickable);
    bool getActorTickable() const;
    void setLifeTime(const float lifeTime);
    void setIsSetLifeTime(const bool isSetLifeTime);
    void registerFuncWhenActorLifeTimeZero(std::function<void()> func);
    bool getIsSetLifeTime() const;
    void setPendingKill(const bool newPendingKill);
    bool getPendingKill() const;
    void setEnableSubstepping(bool isEnable){isEnableSubstepping = isEnable;}
    bool getEnableSubstepping()const{return isEnableSubstepping;}
    void setSubsteppingNum(size_t num){subSteppingNum = num;}
    size_t getSubsteppingNum(){return subSteppingNum;}
    void bindVAO(){glBindVertexArray(VAO);}

protected:
    HSceneComponent* rootComponent;
    glm::vec2 dirVec;
    float lifeTime = 0.0f;
    bool visibility = true;
    bool tickable = true;
    bool isSetLifeTime = false;
    bool isPendingKill = false;
    bool isEnableSubstepping = false;
    size_t subSteppingNum = 0;

    template<typename T, typename ...Types>
    T* createComponent(Types ...args)
    {
        T* newItem = GlobalFunction::createNewObject<T>(args...);
        actorComponents.emplace_back(newItem);
        return newItem;
    }
    //이 함수를 통해 컴포넌트를 생성한다.

public:
    std::function<void()> destroyAction;

private:
    std::vector<HComponent*> actorComponents;
    GLuint VAO;
};

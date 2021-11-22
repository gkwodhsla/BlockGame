#include "HPrimitiveComponent.h"
#include "../Common/Framework.h"
#include "../Common/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
HPrimitiveComponent::HPrimitiveComponent()
{

}

HPrimitiveComponent::~HPrimitiveComponent()
{

}

void HPrimitiveComponent::update(const float deltaTime)
{
    HSceneComponent::update(deltaTime);
}

void HPrimitiveComponent::render()
{
    HSceneComponent::render();

    glm::mat4 worldTransform = glm::translate(glm::mat4(1.0f),
                                              glm::vec3(worldLocation.first,worldLocation.second,0.0f));
    worldTransform *= glm::rotate(glm::mat4(1.0f), glm::radians(worldRotation), glm::vec3(0.0f,0.0f,1.0f));
    worldTransform *= glm::scale(glm::mat4(1.0f),
                                 glm::vec3(worldScale.first,worldScale.second,0.0f));
    auto worldTransLoc = glGetUniformLocation(Framework::curRenderer->getProgramID(), "worldTrans");
    glUniformMatrix4fv(worldTransLoc, 1, GL_FALSE, glm::value_ptr(worldTransform));

    auto isFontDrawLoc = glGetUniformLocation(Framework::curRenderer->getProgramID(), "isDrawFont");
    glUniform1i(isFontDrawLoc, false);

    auto isParticleLoc = glGetUniformLocation(Framework::curRenderer->getProgramID(), "isInstanceDraw");
    glUniform1i(isParticleLoc, false);

    auto gTimeLoc = glGetUniformLocation(Framework::curRenderer->getProgramID(), "gTime");
    glUniform1f(gTimeLoc, Framework::accTime);
}

void HPrimitiveComponent::setVisibility(const bool isVisible)
{
    visibility = isVisible;
}

bool HPrimitiveComponent::getVisibility() const
{
    return visibility;
}



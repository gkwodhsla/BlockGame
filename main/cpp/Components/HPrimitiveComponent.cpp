#include "HPrimitiveComponent.h"
#include "../Common/Framework.h"
#include "../Common/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>

GLuint HPrimitiveComponent::worldTransLoc = -1;
GLuint HPrimitiveComponent::isFontDrawLoc = -1;
GLuint HPrimitiveComponent::isParticleLoc = -1;

HPrimitiveComponent::HPrimitiveComponent()
{
    if(worldTransLoc == -1)
    {
        worldTransLoc = glGetUniformLocation(Framework::curRenderer->getProgramID(), "worldTrans");
        isFontDrawLoc = glGetUniformLocation(Framework::curRenderer->getProgramID(), "isDrawFont");
        isParticleLoc = glGetUniformLocation(Framework::curRenderer->getProgramID(), "isInstanceDraw");
    }
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

    glUniformMatrix4fv(worldTransLoc, 1, GL_FALSE, glm::value_ptr(worldTransform));

    glUniform1i(isFontDrawLoc, false);

    glUniform1i(isParticleLoc, false);
}

void HPrimitiveComponent::setVisibility(const bool isVisible)
{
    visibility = isVisible;
}

bool HPrimitiveComponent::getVisibility() const
{
    return visibility;
}



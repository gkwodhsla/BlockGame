#pragma once
#include "HPrimitiveComponent.h"
#include <GLES3/gl3.h>

class ImageComponent: public HPrimitiveComponent
{
public:
    ImageComponent() = delete;
    ImageComponent(const ImageComponent&) = delete;
    ImageComponent& operator=(const ImageComponent&) = delete;
    ImageComponent(const char* filePath, const bool isCreateMipmap = true,
                   const GLbitfield magFilter = GL_LINEAR, const GLbitfield minFilter = GL_LINEAR_MIPMAP_LINEAR,
                   const GLbitfield wrappingModeS = GL_REPEAT, const GLbitfield wrappingModeT = GL_REPEAT);
    virtual ~ImageComponent();

public:
    void render() override;

public:
    void changeImage(const char* filePath, const bool isCreateMipmap, const GLbitfield magFilter,
                     const GLbitfield minFilter, const GLbitfield wrappingModeS, const GLbitfield wrappingModeT);
private:
    GLuint createTexture(const char* filePath, const bool isCreateMipmap, const GLbitfield magFilter,
                         const GLbitfield minFilter, const GLbitfield wrappingModeS, const GLbitfield wrappingModeT);

private:
    GLuint textureID = 0;
    GLuint VBO;
    GLuint width;
    GLuint height;
    static float rect[];
};
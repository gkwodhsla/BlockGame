#pragma once
#include "HPrimitiveComponent.h"

class PNG final : public HObject
{
public:
    PNG() = delete;
    PNG(const PNG&) = delete;
    PNG& operator=(const PNG&) = delete;
    PNG(const char* filePath, const bool isCreateMipmap = true,
                   const GLbitfield magFilter = GL_LINEAR, const GLbitfield minFilter = GL_NEAREST_MIPMAP_NEAREST,
                   const GLbitfield wrappingModeS = GL_REPEAT, const GLbitfield wrappingModeT = GL_REPEAT);
    virtual ~PNG();

public:
    void changeImage(const char* filePath, const bool isCreateMipmap, const GLbitfield magFilter,
                     const GLbitfield minFilter, const GLbitfield wrappingModeS, const GLbitfield wrappingModeT);
    GLuint getTextureID()const{return textureID;}

private:
    GLuint createTexture(const char* filePath, const bool isCreateMipmap, const GLbitfield magFilter,
                         const GLbitfield minFilter, const GLbitfield wrappingModeS, const GLbitfield wrappingModeT);

private:
    GLuint textureID = 0;
    GLuint width;
    GLuint height;
    bool isTintEnabled = false;
};




class ImageComponent: public HPrimitiveComponent
{
public:
    ImageComponent() = delete;
    ImageComponent(const ImageComponent&) = delete;
    ImageComponent& operator=(const ImageComponent&) = delete;
    ImageComponent(const char* filePath, HActor* owner, const bool isCreateMipmap = true,
                   const GLbitfield magFilter = GL_LINEAR, const GLbitfield minFilter = GL_LINEAR_MIPMAP_LINEAR,
                   const GLbitfield wrappingModeS = GL_REPEAT, const GLbitfield wrappingModeT = GL_REPEAT);
    virtual ~ImageComponent();

public:
    void render() override;

public:
    void changeImage(const char* filePath, const bool isCreateMipmap, const GLbitfield magFilter,
                     const GLbitfield minFilter, const GLbitfield wrappingModeS, const GLbitfield wrappingModeT);
    void changeImage(PNG* png){this->png = png;}
    void setTintEnabled(bool isEnabled);
    void setTintColor(const float r, const float g, const float b);

private:
    GLuint VBO;
    static const float rect[];
    PNG* png = nullptr;
    bool isTintEnabled = false;
    float tintR = 0.0f;
    float tintG = 0.0f;
    float tintB = 0.0f;
};
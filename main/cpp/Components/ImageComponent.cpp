#include "ImageComponent.h"
#include "../Common/Framework.h"
#include "../Common/Renderer.h"

#include <cstring>

GLuint ImageComponent::positionLoc = -1;
GLuint ImageComponent::texPosLoc = -1;
GLuint ImageComponent::texCoordLoc = -1;
GLuint ImageComponent::tintLoc = -1;

const float ImageComponent::rect[] =
        {
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,//아래 사각형
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f//위에 사각형
        };

ImageComponent::ImageComponent(const char *filePath, HActor*owner, const bool isCreateMipmap, GLbitfield magFilter,
                               GLbitfield minFilter, const GLbitfield wrappingModeS, const GLbitfield wrappingModeT)
{
    if(filePath==nullptr)
    {
        png = nullptr;
    }
    else
    {
        png = new PNG(filePath, isCreateMipmap, magFilter, minFilter, wrappingModeS, wrappingModeT);
    }
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect), nullptr, GL_STATIC_DRAW);
    void* ptr = glMapBufferRange(GL_ARRAY_BUFFER,0,sizeof(rect),GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_BUFFER_BIT);
    memcpy(ptr, rect, sizeof(rect));
    glUnmapBuffer(GL_ARRAY_BUFFER);
    ptr = nullptr;

    if(positionLoc == -1)
    {
        positionLoc = glGetAttribLocation(Framework::curRenderer->getProgramID(), "position");
        texPosLoc = glGetAttribLocation(Framework::curRenderer->getProgramID(), "inputTexPos");
        texCoordLoc = glGetUniformLocation(frameworkInst->curRenderer->getProgramID(), "uTexCoord");
        tintLoc = glGetUniformLocation(frameworkInst->curRenderer->getProgramID(), "tintColor");
    }

    glEnableVertexAttribArray(positionLoc);
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE,sizeof(float)*5, (GLvoid*)0);

    glEnableVertexAttribArray(texPosLoc);
    glVertexAttribPointer(texPosLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5,(GLvoid*)(sizeof(float)*3));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    setOwner(owner);
}

void ImageComponent::changeImage(const char *filePath, const bool isCreateMipmap, GLbitfield magFilter,
                                 GLbitfield minFilter, const GLbitfield wrappingModeS, const GLbitfield wrappingModeT)
{
    png->changeImage(filePath, isCreateMipmap, magFilter, minFilter, wrappingModeS, wrappingModeT);

    if(positionLoc == -1)
    {
        positionLoc = glGetAttribLocation(Framework::curRenderer->getProgramID(), "position");
        texPosLoc = glGetAttribLocation(Framework::curRenderer->getProgramID(), "inputTexPos");
        texCoordLoc = glGetUniformLocation(frameworkInst->curRenderer->getProgramID(), "uTexCoord");
        tintLoc = glGetUniformLocation(frameworkInst->curRenderer->getProgramID(), "tintColor");
    }
}

ImageComponent::~ImageComponent()
{
    if(png)
    {
        delete png;
        png = nullptr;
    }
    if(VBO)
    {
        glDeleteBuffers(1, &VBO);
    }
}

void ImageComponent::render()
{
    if(png)
    {
        HPrimitiveComponent::render();
        glBindTexture(GL_TEXTURE_2D, png->getTextureID());

        if(isTintEnabled)
            glUniform3f(tintLoc, tintR,tintG,tintB);
        else
            glUniform3f(tintLoc, 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void ImageComponent::setTintEnabled(bool isEnabled)
{
    isTintEnabled = isEnabled;
}

void ImageComponent::setTintColor(const float r, const float g, const float b)
{
    tintR = r;
    tintG = g;
    tintB = b;
}








PNG::PNG(const char *filePath, const bool isCreateMipmap, const GLbitfield magFilter,
         const GLbitfield minFilter, const GLbitfield wrappingModeS,
         const GLbitfield wrappingModeT)
{
    textureID = createTexture(filePath, isCreateMipmap, magFilter, minFilter, wrappingModeS, wrappingModeT);
}

PNG::~PNG()
{
    if(textureID)
    {
        glDeleteTextures(1,&textureID);
        textureID = 0;
    }
}

void PNG::changeImage(const char *filePath, const bool isCreateMipmap, const GLbitfield magFilter,
                      const GLbitfield minFilter, const GLbitfield wrappingModeS,
                      const GLbitfield wrappingModeT)
{
    if(textureID)
    {
        glDeleteTextures(1,&textureID);
        textureID = 0;
    }
    textureID = createTexture(filePath, isCreateMipmap, magFilter, minFilter, wrappingModeS, wrappingModeT);
}

GLuint PNG::createTexture(const char *filePath, const bool isCreateMipmap, const GLbitfield magFilter,
                   const GLbitfield minFilter, const GLbitfield wrappingModeS,
                   const GLbitfield wrappingModeT)
{
    size_t fileSize = 0;
    auto buffer = GlobalFunction::readFile(filePath, fileSize);

    std::vector<unsigned char> image;
    auto data = std::vector<unsigned char>(buffer, buffer+fileSize);
    GLuint error = lodepng::decode(image, width, height, data);
    if (error != 0)
    {
        PRINT_LOG(lodepng_error_text(error), %s);
        return -1;
    }

    GLuint temp;
    glGenTextures(1, &temp);

    glBindTexture(GL_TEXTURE_2D, temp);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    if(isCreateMipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingModeS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingModeT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    delete[] buffer;
    buffer = nullptr;

    //텍스처의 0번 슬롯을 활성화하고 해당 슬롯에 방금 만든 텍스처 바인드

    return temp;
}

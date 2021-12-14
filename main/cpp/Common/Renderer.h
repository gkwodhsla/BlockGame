#pragma once
#if defined(__ANDROID__) || defined(ANDROID)
#include <GLES3/gl3.h>
#elif defined(IOS)
#include <OpenGLES/ES3/gl.h>
#endif
#include <vector>
#include <bitset>

class Program;
class Camera2DComponent;

class Renderer
{
public:
    Renderer() = delete;
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(const char* VSPath, const char* FSPath);
    virtual ~Renderer();

public:
    void setClearColor(const float r, const float g, const float b, const float a);
    void enableGLFeature(const GLbitfield bit);
    void unableGLFeature(const GLbitfield bit);
    void addClearBit(const GLbitfield bit);
    void eraseClearBit(const GLbitfield bit);
    void changeProgram(const char* VSPath, const char* FSPath);
    void setCamera(Camera2DComponent*);
    void readyToDraw();
    const GLuint inline getProgramID() const {return programID;}

private:
    std::vector<GLuint> clearBits;
    Program* curProgram = nullptr;
    Camera2DComponent* curCamera = nullptr;
    GLuint programID = 0;
};